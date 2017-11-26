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

#include "FrameSizeDeterminationPass.h"

#include "../Logger.h"
#include "../ast/RecursiveVisitor.h"

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

#include <unordered_map>

using namespace libcasm_fe;
using namespace Ast;

char FrameSizeDeterminationPass::id = 0;

static libpass::PassRegistration< FrameSizeDeterminationPass > PASS(
    "ASTFrameSizeDeterminationPass",
    "determines the required size of call frames",
    "ast-frame-size-det",
    0 );

class FrameSizeDeterminationVisitor final : public RecursiveVisitor
{
  public:
    explicit FrameSizeDeterminationVisitor( libcasm_fe::Logger& log );

    void visit( FunctionDefinition& node ) override;
    void visit( DerivedDefinition& node ) override;
    void visit( RuleDefinition& node ) override;

    void visit( LetExpression& node ) override;
    void visit( ChooseExpression& node ) override;
    void visit( UniversalQuantifierExpression& node ) override;
    void visit( ExistentialQuantifierExpression& node ) override;

    void visit( LetRule& node ) override;
    void visit( ForallRule& node ) override;
    void visit( ChooseRule& node ) override;

  private:
    void pushLocal( VariableDefinition& identifier );
    void popLocal( void );
    void popLocals( std::size_t count );

  private:
    libcasm_fe::Logger& m_log;

    std::size_t m_numberOfLocals;
    std::size_t m_maxNumberOfLocals;
};

FrameSizeDeterminationVisitor::FrameSizeDeterminationVisitor( libcasm_fe::Logger& log )
: RecursiveVisitor()
, m_log( log )
, m_numberOfLocals( 0 )
, m_maxNumberOfLocals( 0 )
{
}

void FrameSizeDeterminationVisitor::visit( FunctionDefinition& node )
{
    m_maxNumberOfLocals = node.argumentTypes()->size();

    node.setMaximumNumberOfLocals( m_maxNumberOfLocals );

#ifndef NDEBUG
    m_log.debug(
        { node.sourceLocation() },
        "function '" + node.identifier()->name() + "' requires space for " +
            std::to_string( m_maxNumberOfLocals ) + " locals" );
#endif
}

void FrameSizeDeterminationVisitor::visit( DerivedDefinition& node )
{
    m_maxNumberOfLocals = 0;

    for( const auto& argument : *node.arguments() )
    {
        pushLocal( *argument );
    }

    node.expression()->accept( *this );

    popLocals( node.arguments()->size() );
    assert( m_numberOfLocals == 0 );

    node.setMaximumNumberOfLocals( m_maxNumberOfLocals );

#ifndef NDEBUG
    m_log.debug(
        { node.sourceLocation() },
        "derived '" + node.identifier()->name() + "' requires space for " +
            std::to_string( m_maxNumberOfLocals ) + " locals" );
#endif
}

void FrameSizeDeterminationVisitor::visit( RuleDefinition& node )
{
    m_maxNumberOfLocals = 0;

    for( const auto& argument : *node.arguments() )
    {
        pushLocal( *argument );
    }

    node.rule()->accept( *this );

    popLocals( node.arguments()->size() );
    assert( m_numberOfLocals == 0 );

    node.setMaximumNumberOfLocals( m_maxNumberOfLocals );

#ifndef NDEBUG
    m_log.debug(
        { node.sourceLocation() },
        "rule '" + node.identifier()->name() + "' requires space for " +
            std::to_string( m_maxNumberOfLocals ) + " locals" );
#endif
}

void FrameSizeDeterminationVisitor::visit( LetExpression& node )
{
    node.initializer()->accept( *this );

    pushLocal( *node.variable() );
    node.expression()->accept( *this );
    popLocal();
}

void FrameSizeDeterminationVisitor::visit( ChooseExpression& node )
{
    node.universe()->accept( *this );

    pushLocal( *node.variable() );
    node.expression()->accept( *this );
    popLocal();
}

void FrameSizeDeterminationVisitor::visit( UniversalQuantifierExpression& node )
{
    node.universe()->accept( *this );

    pushLocal( *node.predicateVariable() );
    node.proposition()->accept( *this );
    popLocal();
}

void FrameSizeDeterminationVisitor::visit( ExistentialQuantifierExpression& node )
{
    node.universe()->accept( *this );

    pushLocal( *node.predicateVariable() );
    node.proposition()->accept( *this );
    popLocal();
}

void FrameSizeDeterminationVisitor::visit( LetRule& node )
{
    node.expression()->accept( *this );

    pushLocal( *node.variable() );
    node.rule()->accept( *this );
    popLocal();
}

void FrameSizeDeterminationVisitor::visit( ForallRule& node )
{
    node.universe()->accept( *this );

    pushLocal( *node.variable() );
    node.condition()->accept( *this );
    node.rule()->accept( *this );
    popLocal();
}

void FrameSizeDeterminationVisitor::visit( ChooseRule& node )
{
    node.universe()->accept( *this );

    pushLocal( *node.variable() );
    node.rule()->accept( *this );
    popLocal();
}

void FrameSizeDeterminationVisitor::pushLocal( VariableDefinition& node )
{
    const std::size_t localIndex = m_numberOfLocals;
    node.setLocalIndex( localIndex );

    ++m_numberOfLocals;
    m_maxNumberOfLocals = std::max( m_maxNumberOfLocals, m_numberOfLocals );
}

void FrameSizeDeterminationVisitor::popLocal( void )
{
    popLocals( 1 );
}

void FrameSizeDeterminationVisitor::popLocals( std::size_t count )
{
    assert( m_numberOfLocals >= count );

    m_numberOfLocals -= count;
}

void FrameSizeDeterminationPass::usage( libpass::PassUsage& pu )
{
    pu.require< ConsistencyCheckPass >();
}

u1 FrameSizeDeterminationPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto data = pr.result< ConsistencyCheckPass >();
    const auto specification = data->specification();

    FrameSizeDeterminationVisitor visitor( log );
    specification->definitions()->accept( visitor );

    const auto errors = log.errors();
    if( errors > 0 )
    {
        log.debug( "found %lu error(s) during frame size determination", errors );
        return false;
    }

    pr.setResult< FrameSizeDeterminationPass >( data );

    return true;
}

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
