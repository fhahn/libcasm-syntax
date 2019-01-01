//
//  Copyright (C) 2014-2019 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Florian Hahn
//                <https://github.com/casm-lang/libcasm-fe>
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
//  Additional permission under GNU GPL version 3 section 7
//
//  libcasm-fe is distributed under the terms of the GNU General Public License
//  with the following clarification and special exception: Linking libcasm-fe
//  statically or dynamically with other modules is making a combined work
//  based on libcasm-fe. Thus, the terms and conditions of the GNU General
//  Public License cover the whole combination. As a special exception,
//  the copyright holders of libcasm-fe give you permission to link libcasm-fe
//  with independent modules to produce an executable, regardless of the
//  license terms of these independent modules, and to copy and distribute
//  the resulting executable under terms of your choice, provided that you
//  also meet, for each linked independent module, the terms and conditions
//  of the license of that module. An independent module is a module which
//  is not derived from or based on libcasm-fe. If you modify libcasm-fe, you
//  may extend this exception to your version of the library, but you are
//  not obliged to do so. If you do not wish to do so, delete this exception
//  statement from your version.
//

#ifndef _LIBCASM_FE_IDENTIFIER_H_
#define _LIBCASM_FE_IDENTIFIER_H_

#include <libcasm-fe/ast/Node>
#include <libcasm-fe/ast/Token>

namespace libcasm_fe
{
    namespace Ast
    {
        class Identifier final : public Node
        {
          public:
            using Ptr = std::shared_ptr< Identifier >;

            explicit Identifier( const std::string& name );

            const std::string& name( void ) const;

            void setDoubleColon( const Token::Ptr& doubleColon );
            const Token::Ptr& doubleColon( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            std::string m_name;
            Token::Ptr m_doubleColon;
        };

        using Identifiers = NodeList< Identifier >;

        /**
         * @brief An identifier path is an identifier + namespaces.
         *
         * The identifier path can either be absolute or relative. The string of
         * a relative identifier path starts with a dot. All relative identifier
         * paths will later be resolved and converted into absolute paths.
         *
         * An absolute path "Color.Red" will be splitted into the namespaces
         * ["Color"] and identifier "Red". Furthermore the node will be marked
         * as NamespaceType.ABSOLUTE.
         *
         * A relative path ".Red" will be splitted into the namespaces [] and
         * identifier "Red". Furthermore the node will be marked as
         * NamespaceType.RELATIVE.
         */
        class IdentifierPath final : public Node
        {
          public:
            enum class Type
            {
                ABSOLUTE, /**< absolute namespace + identifier path */
                RELATIVE, /**< path started with a dot, needs to be resolved */
            };

          public:
            using Ptr = std::shared_ptr< IdentifierPath >;

            IdentifierPath( const Identifier::Ptr& identifier, Type type = Type::ABSOLUTE );

            /**
             * @param identifiers A list of identifiers (must not be empty)
             * @param type The type of the identifier path (default is ABSOLUTE)
             */
            IdentifierPath( const Identifiers::Ptr& identifiers, Type type = Type::ABSOLUTE );

            void addIdentifier( const Identifier::Ptr& identifier );

            Identifiers::Ptr identifiers( void ) const;
            Type type( void ) const;

            const std::string& baseName( void ) const;
            std::string baseDir( void ) const;
            std::string path( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Identifiers::Ptr m_identifiers;
            const Type m_type;
        };

        template < typename T, typename... Args >
        typename T::Ptr make( const SourceLocation& sourceLocation, Args&&... args )
        {
            auto node = std::make_shared< T >( std::forward< Args >( args )... );
            node->setSourceLocation( sourceLocation );
            return node;
        }
    }
}

#endif  // _LIBCASM_FE_IDENTIFIER_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
