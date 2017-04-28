//
//  Copyright (c) 2014-2017 CASM Organization
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Florian Hahn
//                https://github.com/casm-lang/libcasm-fe
//
//  This file is part of libcasm-fe.
//
//  libcasm-fe is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  libcasm-fe is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with libcasm-fe. If not, see <http://www.gnu.org/licenses/>.
//

#ifndef _LIB_CASMFE_UPDATESET_H_
#define _LIB_CASMFE_UPDATESET_H_

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <vector>

#include <experimental/optional>

#include "ChainedHashMap.h"
#include "ProbingHashMap.h"
#include "RobinHoodHashMap.h"

/*struct UpdateSetDetails
{
    using Location = ;
    using Value = ;
    using LocationHash = std::hash< Location >;
    using LocationEquals = std::equal_to< Location >;
    using ValueEquals = std::equal_to< Value >;
};*/

template < typename Details >
class SequentialUpdateSet;

template < typename Details >
class ParallelUpdateSet;

/**
 * @brief Base class for all types of update-sets
 */
template < typename _Details >
class UpdateSet
{
  public:
    using Details = _Details;
    using Location = typename Details::Location;
    using Value = typename Details::Value;
    using Update = std::pair< Location, Value >;

  private:
    using UpdateHashMap = ChainedHashMap< Location, Value,
        typename Details::LocationHash, typename Details::LocationEquals >;

  public:
    using const_iterator = typename UpdateHashMap::const_iterator;

    /**
     * @brief The semantics of the update-set
     */
    enum class Semantics
    {
        Sequential, /**< Update-set with sequential execution semantics */
        Parallel    /**< Update-set with parallel execution semantics */
    };

    /**
     * @brief An exception which will be thrown when updates are in conflict
     */
    class Conflict : public std::logic_error
    {
      public:
        /**
         * Constructs a conflict exception
         *
         * @param conflictingUpdate Update which caused the conflict
         * @param existingUpdate Existing update for the same location as the
         *                       \a conflictingUpdate
         */
        Conflict(
            const Update& conflictingUpdate, const Update& existingUpdate )
        : std::logic_error( "conflict in update set" )
        , m_conflictingUpdate( conflictingUpdate )
        , m_existingUpdate( existingUpdate )
        {
        }

        /**
         * @return The update which caused the conflict
         */
        const Update& conflictingUpdate() const noexcept
        {
            return m_conflictingUpdate;
        }

        /**
         * @return The existing update for the same location as the conflicting
         *         update
         */
        const Update& existingUpdate() const noexcept
        {
            return m_existingUpdate;
        }

      private:
        Update m_conflictingUpdate;
        Update m_existingUpdate;
    };

  public:
    /**
     * Constructs an empty update-set
     *
     * @param initialSize The number of updates the update-set should be able to
     *                    handle without resizing
     * @param parent The parent update-set (if there is any)
     */
    explicit UpdateSet( std::size_t initialSize, UpdateSet* parent = nullptr )
    : m_set( initialSize )
    , m_parent( parent )
    {
    }

    /**
     * Destroys the update-set
     */
    virtual ~UpdateSet() = default;

    /**
     * @return The semantics of the update-set
     */
    virtual Semantics semantics() const noexcept = 0;

    /**
     * @return A boolean value indicating wheter the update-set is empty, i.e.
     *         wheter it doesn't contain updates
     */
    bool empty() const noexcept
    {
        return m_set.empty();
    }

    /**
     * @return The number of updates in the update-set
     */
    std::size_t size() const noexcept
    {
        return m_set.size();
    }

    /**
     * Request more space so that the update set can store an additional number
     * of \a size updates without intermediate resizing.
     *
     * @param size The additional number of updates the update-set should be
     *             able to handle without resizing
     */
    void reserveAdditionally( std::size_t size )
    {
        m_set.reserve( m_set.size() + size );
    }

    /**
     * Adds an update for the \a location with value \a value to the update-set.
     *
     * The handling of multiple updates for the same location depends on the
     * actual type of the update-set.
     *
     * @note The udpate-set will not take over the ownership of \a value or
     *        \a location.
     *
     * @param location The location of the update
     * @param value The value of the update
     *
     * @throws Conflict when the update-set is a parallel update-set, an update
     *         for the \a location exists already and the values of both updates
     *         are different
     */
    virtual void add( const Location& location, const Value& value ) = 0;

    /**
     * Adds an update \a update to the update-set.
     *
     * The handling of multiple updates for the same location depends on the
     * actual type of the update-set.
     *
     * @note The udpate-set will not take over the ownership of \a update.
     *
     * @param update The update which should be added
     *
     * @throws Conflict when the update-set is a parallel update-set, an update
     *         for the \a location exists already and the values of both updates
     *         are different
     */
    void add( const Update& update )
    {
        add( update.first, update.second );
    }

    /**
     * Searches for an update for the \a location in the update-set
     *
     * If the current update-set doesn't contain an update for the \a location,
     * the parent update-set will be searched.
     *
     * @param location The location of the update of interest
     *
     * @return The update value for the \a location if an update exists.
     */
    virtual std::experimental::optional< Value > lookup(
        const Location& location ) const noexcept
    {
        if( m_parent )
        {
            return m_parent->lookup( location );
        }

        return std::experimental::nullopt;
    }

    /**
     * Forks the current update-set
     *
     * @param semantics The Semantics of the forked update-set
     * @param initialSize The number of updates the update-set should be able to
     *                    handle without resizing
     *
     * @return A new update-set of type \a updateSetType with the current
     *         update-set as parent
     */
    std::unique_ptr< UpdateSet > fork(
        Semantics semantics, std::size_t initialSize )
    {
        switch( semantics )
        {
            case Semantics::Sequential:
                return std::unique_ptr< SequentialUpdateSet< Details > >(
                    new SequentialUpdateSet< Details >( initialSize, this ) );
            case Semantics::Parallel:
                return std::unique_ptr< ParallelUpdateSet< Details > >(
                    new ParallelUpdateSet< Details >( initialSize, this ) );
        }
    }

    /**
     * Merges all updates of the current update-set into its parent update-set
     *
     * @pre The update-set must have a parent update-set
     *
     * @throws Conflict when the parent update-set is a parallel update-set, an
     *         update for the \a location exists already in the parent
     * update-set and the values of both updates are different
     */
    void merge()
    {
        assert( m_parent != nullptr );

        if( m_parent->m_set.empty() )
        {
            std::swap( m_parent->m_set, m_set );
        }
        else
        {
            m_parent->reserveAdditionally( m_set.size() );
            const auto end = m_set.end();
            for( auto it = m_set.begin(); it != end; ++it )
            {
                m_parent->add( it.key(), it.value() );
            }
        }
    }

    /**
     * @return Iterator to the beginning of the update-set
     */
    const_iterator begin() const noexcept
    {
        return m_set.begin();
    }

    /**
     * @return Iterator to the end of the update-set
     */
    const_iterator end() const noexcept
    {
        return m_set.end();
    }

    /**
     * Searches for an update for the \a location in the current update-set
     *
     * An existing update will always be returned regardless of the type of
     * the update-set.
     *
     * @note In contrast to lookup() no recursive search will be performed.
     *
     * @param location The location of the update of interest
     *
     * @return The update value for the \a location if an update exists.
     */
    std::experimental::optional< Value > get(
        const Location& location ) const noexcept
    {
        const auto it = m_set.find( location );
        if( it != m_set.end() )
        {
            return it.value();
        }

        return std::experimental::nullopt;
    }

  protected:
    UpdateHashMap m_set;

  private:
    UpdateSet* const m_parent;
};

/**
 * @brief Update-set with sequential execution semantics
 */
template < typename Details >
class SequentialUpdateSet final : public UpdateSet< Details >
{
    using Super = UpdateSet< Details >;
    using Location = typename Super::Location;
    using Value = typename Super::Value;
    using Semantics = typename Super::Semantics;

  public:
    using Super::UpdateSet;

    /**
     * @return The semantics of the update-set
     */
    Semantics semantics() const noexcept override
    {
        return Semantics::Sequential;
    }

    /**
     * Adds an update for the \a location with value \a value to the update-set.
     *
     * If an update for the same location exists already then it will be
     * overwritten.
     *
     * @note The udpate-set will not take over the ownership of \a update.
     *
     * @param location The location of the update
     * @param value The value of the update
     */
    void add( const Location& location, const Value& value ) override
    {
        Super::m_set.insertOrAssign( location, value );
    }

    /**
     * Searches for an update for the \a location in the update-set
     *
     * If the current update-set doesn't contain an update for the \a location,
     * the parent update-set will be searched.
     *
     * @param location The location of the update of interest
     *
     * @return The update value for the \a location if an update exists.
     */
    std::experimental::optional< Value > lookup(
        const Location& location ) const noexcept override
    {
        const auto it = Super::m_set.find( location );
        if( it != Super::m_set.end() )
        {
            return it.value();
        }

        return Super::lookup( location );
    }
};

/**
 * @brief Update-set with parallel execution semantics
 */
template < typename Details >
class ParallelUpdateSet final : public UpdateSet< Details >
{
    using Super = UpdateSet< Details >;
    using Location = typename Super::Location;
    using Value = typename Super::Value;
    using Semantics = typename Super::Semantics;
    using Conflict = typename Super::Conflict;

  public:
    using Super::UpdateSet;

    /**
     * @return The semantics of the update-set
     */
    Semantics semantics() const noexcept override
    {
        return Semantics::Parallel;
    }

    /**
     * Adds an update for the \a location with value \a value to the update-set.
     *
     * @note The udpate-set will not take over the ownership of \a update.
     *
     * @param location The location of the update
     * @param value The value of the update
     *
     * @throws Conflict when an update for the \a location exists already and
     *         the values of both updates are different
     */
    void add( const Location& location, const Value& value ) override
    {
        const auto result = Super::m_set.insert( location, value );
        if( !result.second )
        {
            const auto it = result.first;
            const auto& existingValue = it.value();

            static const typename Details::ValueEquals equals{};

            if( not equals( value, existingValue ) )
            {
                throw Conflict(
                    { location, value }, { location, existingValue } );
            }
        }
    }
};

/**
 * @brief An helper for convenient forking and merging of update-sets
 */
template < typename UpdateSet >
class UpdateSetManager
{
    using Location = typename UpdateSet::Location;
    using Value = typename UpdateSet::Value;

  public:
    /**
     * Constructs an empty update-set manager
     */
    UpdateSetManager()
    : m_updateSets()
    {
    }

    /**
     * Adds an update for the \a location with value \a value to the current
     * update-set.
     *
     * The handling of multiple updates for the same location depends on the
     * actual type of the update-set.
     *
     * @note The udpate-set will not take over the ownership of \a update.
     *
     * @pre The update-set manager must not be empty
     *
     * @param location The location of the update
     * @param value The value of the update
     *
     * @throws Conflict when the update-set is a parallel update-set, an update
     *         for the \a location exists already and the values of both updates
     *         are different
     */
    void add( const Location& location, const Value& value )
    {
        currentUpdateSet()->add( location, value );
    }

    /**
     * Searches for an update for the \a location in the current update-set
     *
     * If the current update-set doesn't contain an update for the \a location,
     * the parent update-set will be searched.
     *
     * @param location The location of the update of interest
     *
     * @return The update value for the \a location if an update exists.
     */
    std::experimental::optional< Value > lookup(
        const Location& location ) const noexcept
    {
        if( m_updateSets.empty() )
        {
            return std::experimental::nullopt;
        }
        else
        {
            return currentUpdateSet()->lookup( location );
        }
    }

    /**
     * Forks the current update-set or creates a new update-set if the
     * update-set manager is empty
     *
     * @post The forked update-set is the new "current update-set" and the size
     *       of the update-set manager is increased by one
     *
     * @param semantics The semantics of the forked update-set
     * @param initialSize The number of updates the update-set should be able to
     *                    handle without resizing
     */
    void fork(
        typename UpdateSet::Semantics semantics, std::size_t initialSize )
    {
        if( m_updateSets.empty() )
        {
            switch( semantics )
            {
                case UpdateSet::Semantics::Sequential:
                    m_updateSets.emplace_back(
                        new SequentialUpdateSet< typename UpdateSet::Details >(
                            initialSize ) );
                    break;
                case UpdateSet::Semantics::Parallel:
                    m_updateSets.emplace_back(
                        new ParallelUpdateSet< typename UpdateSet::Details >(
                            initialSize ) );
                    break;
            }
        }
        else
        {
            m_updateSets.emplace_back(
                currentUpdateSet()->fork( semantics, initialSize ) );
        }
    }

    /**
     * Merges all updates of the current update-set into its parent update-set
     *
     * The merge will only be performed if there is more than one update-set in
     * the update-set manager.
     *
     * @post If an merge has been performed the size of the update-set manager
     *       is decreased by one
     *
     * @throws Conflict when the parent update-set is a parallel update-set, an
     *         update for the \a location exists already in the parent
     * update-set
     *         and the values of both updates are different
     */
    void merge()
    {
        if( size() < 2 )
        {
            return;
        }

        currentUpdateSet()->merge();
        m_updateSets.pop_back();
    }

    /**
     * Removes all update-sets from the update-set manager
     */
    void clear()
    {
        m_updateSets.clear();
    }

    /**
     * @pre The update-set manager must not be empty
     *
     * @return The current update-set of the update-set manager, i.e. the
     *         update-set on top of the update-set stack.
     */
    UpdateSet* currentUpdateSet() const
    {
        assert( not m_updateSets.empty() );
        return m_updateSets.back().get();
    }

    /**
     * @return The number of update-sets in the update-set manager
     */
    std::size_t size() const noexcept
    {
        return m_updateSets.size();
    }

  private:
    std::vector< std::unique_ptr< UpdateSet > > m_updateSets;
};

template < typename UpdateSet >
class UpdateSetForkGuard
{
  public:
    UpdateSetForkGuard( UpdateSetManager< UpdateSet >* manager,
        typename UpdateSet::Semantics semantics, std::size_t initialSize )
    : m_manager( manager )
    {
        if( manager->currentUpdateSet()->semantics() != semantics )
        {
            manager->fork( semantics, initialSize );
            m_wasForked = true;
        }
        else
        {
            m_wasForked = false;
        }
    }

    ~UpdateSetForkGuard()
    {
        if( m_wasForked )
        {
            m_manager->merge();
        }
    }

  private:
    UpdateSetManager< UpdateSet >* m_manager;
    bool m_wasForked;
};

#endif // _LIB_CASMFE_UPDATESET_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
