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

#include "TypeInferencePass.h"

#include "../pass/src/PassRegistry.h"
#include "../pass/src/PassResult.h"
#include "../pass/src/PassUsage.h"

#include "../Logger.h"
#include "../analyze/SymbolResolverPass.h"
#include "../ast/RecursiveVisitor.h"

#include "../stdhl/cpp/String.h"

#include "../casm-ir/src/Builtin.h"

using namespace libcasm_fe;
using namespace Ast;

char TypeInferencePass::id = 0;

static libpass::PassRegistration< TypeInferencePass > PASS(
    "ASTTypeInferencePass",
    "resolve all unknown types in the AST representation", "ast-check", 0 );

//
// TypeCheckVisitor
//

class TypeCheckVisitor final : public RecursiveVisitor
{
  public:
    TypeCheckVisitor( Logger& log, Namespace& symboltable );

    void visit( VariableDefinition& node ) override;

    void visit( DirectCallExpression& node ) override;

    void visit( CaseRule& node ) override;
    void visit( LetRule& node ) override;

    void visit( BasicType& node ) override;
    void visit( ComposedType& node ) override;
    void visit( RelationType& node ) override;
    void visit( FixedSizedType& node ) override;

    void visit( ExpressionCase& node ) override;
    void visit( DefaultCase& node ) override;

    u64 errors( void ) const;

  private:
    void push( VariableDefinition& identifier );
    void pop( VariableDefinition& identifier );

    Logger& m_log;
    u64 m_err;
    Namespace& m_symboltable;

    std::unordered_map< std::string, VariableDefinition* > m_id2var;
    std::stack< VariableDefinition* > m_stack;
    Expression* m_caseExpr = nullptr;
};

static const auto VOID = libstdhl::get< libcasm_ir::VoidType >();
static const auto RULEREF = libstdhl::get< libcasm_ir::RuleReferenceType >();
static const auto BOOLEAN = libstdhl::get< libcasm_ir::BooleanType >();
static const auto INTEGER = libstdhl::get< libcasm_ir::IntegerType >();
static const auto BIT_1 = libstdhl::get< libcasm_ir::BitType >( 1 );
static const auto STRING = libstdhl::get< libcasm_ir::StringType >();
static const auto FLOATING = libstdhl::get< libcasm_ir::FloatingType >();
static const auto RATIONAL = libstdhl::get< libcasm_ir::RationalType >();

static const std::unordered_map< std::string, libcasm_ir::Type::Ptr > basicTypes
    = {
        { "Void", VOID },

        { "RuleRef", RULEREF },

        { "Boolean", BOOLEAN },

        { "Integer", INTEGER },

        { "Bit", BIT_1 },

        { "String", STRING },

        { "Floating", FLOATING },

        { "Rational", RATIONAL },
      };

TypeCheckVisitor::TypeCheckVisitor( Logger& log, Namespace& symboltable )
: m_log( log )
, m_err( 0 )
, m_symboltable( symboltable )
{
}

void TypeCheckVisitor::visit( VariableDefinition& node )
{
    RecursiveVisitor::visit( node );

    if( not node.type() and node.variableType()->type() )
    {
        node.setType( node.variableType()->type() );
    }
}

void TypeCheckVisitor::visit( DirectCallExpression& node )
{
    const auto& path = *node.identifier();

    if( not node.type() )
    {
        auto result = m_id2var.find( path.path() );
        if( result != m_id2var.end() )
        {
            node.setType( result->second->type() );
        }
        else
        {
            if( node.targetType() == CallExpression::TargetType::UNKNOWN )
            {
                assert( path.type() == IdentifierPath::Type::RELATIVE );
                assert( path.identifiers()->size() == 1 );
                // can only be a relative addressed enumeration constant

                if( not m_caseExpr )
                {
                    // we are not in a 'case' context ... check latest
                    // m_stack entry!
                    if( not m_stack.empty() )
                    {
                        const auto variable = m_stack.top();

                        const auto searchPath
                            = Ast::make< Identifiers >( node.sourceLocation() );

                        for( auto i :
                            *variable->variableType()->name()->identifiers() )
                        {
                            searchPath->add( i );
                        }

                        for( auto i : *path.identifiers() )
                        {
                            searchPath->add( i );
                        }

                        IdentifierPath identifierSearchPath(
                            searchPath, IdentifierPath::Type::ABSOLUTE );

                        try
                        {
                            auto symbol
                                = m_symboltable.find( identifierSearchPath );

                            node.setTargetType( symbol.targetType() );

                            assert( symbol.targetType()
                                    == CallExpression::TargetType::CONSTANT );

                            auto& definition
                                = static_cast< EnumerationDefinition& >(
                                    symbol.definition() );

                            assert( definition.type() );
                            node.setType( definition.type() );
                        }
                        catch( const std::domain_error& e )
                        {
                            // m_err++; // TODO: PPA: enable this
                            m_log.error( { node.sourceLocation() },
                                "unable to find symbol '"
                                    + identifierSearchPath.path()
                                    + "'" );
                        }
                    }
                    else
                    {
                        // m_err++; // TODO: PPA: enable this
                        m_log.error( { node.sourceLocation() },
                            "unable to resolve symbol '" + path.path() + "'" );
                    }
                }
                else if( m_caseExpr and m_caseExpr->type() )
                {
                    std::vector< std::string > parts;
                    libstdhl::String::split(
                        m_caseExpr->type()->name(), ".", parts );
                    parts.emplace_back( path.baseName() );

                    try
                    {
                        auto symbol = m_symboltable.find( parts );

                        node.setTargetType( symbol.targetType() );

                        assert( symbol.targetType()
                                == CallExpression::TargetType::CONSTANT );

                        auto& definition
                            = static_cast< EnumerationDefinition& >(
                                symbol.definition() );

                        assert( definition.type() );
                        node.setType( definition.type() );
                    }
                    catch( const std::domain_error& e )
                    {
                        // m_err++; // TODO: PPA: enable this
                        m_log.error( { node.sourceLocation() },
                            "unknown symbol '" + path.path() + "' found" );
                    }
                }
                else
                {
                    // m_err++; // TODO: PPA: enable this
                    m_log.error( { node.sourceLocation() },
                        "unknown symbol '" + path.path() + "' found" );
                }
            }
        }
    }

    // assert( node.targetType() != CallExpression::TargetType::UNKNOWN );

    RecursiveVisitor::visit( node );
}

void TypeCheckVisitor::visit( LetRule& node )
{
    node.variable()->accept( *this );
    push( *node.variable() );
    node.expression()->accept( *this );

    if( not node.variable()->type() and node.expression()->type() )
    {
        node.variable()->setType( node.expression()->type() );
    }

    node.rule()->accept( *this );
    pop( *node.variable() );
}

void TypeCheckVisitor::visit( CaseRule& node )
{
    // check the case expression itself
    node.expression()->accept( *this );

    // set case expression and its type
    assert( not m_caseExpr );
    m_caseExpr = node.expression().get();

    // iterate only over the expressions
    node.cases()->accept( *this );

    // clear case expression and its type
    assert( m_caseExpr );
    m_caseExpr = nullptr;

    // iterate over the case expression rules
    for( auto c : *node.cases() )
    {
        c->rule()->accept( *this );
    }
}

void TypeCheckVisitor::visit( BasicType& node )
{
    if( not node.type() )
    {
        const auto& name = node.name()->baseName();

        auto result = basicTypes.find( name );
        if( result != basicTypes.end() )
        {
            node.setType( result->second );
        }
        else if( name.compare( "Agent" ) == 0 )
        {
            auto symbol = m_symboltable.find( "self" );
            assert(
                symbol.targetType() == CallExpression::TargetType::FUNCTION );
            auto& definition
                = static_cast< FunctionDefinition& >( symbol.definition() );

            if( not definition.returnType()->type() )
            {
                auto kind
                    = libstdhl::make< libcasm_ir::Enumeration >( "Agent" );

                kind->add( "default" );

                const auto type
                    = libstdhl::make< libcasm_ir::EnumerationType >( kind );

                definition.returnType()->setType( type );
            }

            node.setType( definition.returnType()->type() );
        }
        else
        {
            try
            {
                auto symbol = m_symboltable.find( node );

                assert( symbol.targetType()
                        == CallExpression::TargetType::ENUMERATION );

                auto& definition = static_cast< EnumerationDefinition& >(
                    symbol.definition() );

                assert( definition.type() );

                node.setType( definition.type() );
            }
            catch( const std::domain_error& e )
            {
                m_err++;
                m_log.error( { node.sourceLocation() },
                    "unknown type '" + name + "' found" );
            }
        }
    }

    RecursiveVisitor::visit( node );
}

void TypeCheckVisitor::visit( ComposedType& node )
{
#warning " TODO: List, Tuple etc. "
    RecursiveVisitor::visit( node );
}

void TypeCheckVisitor::visit( RelationType& node )
{
    RecursiveVisitor::visit( node );

    if( node.type() )
    {
        return;
    }

    const auto& name = node.name()->baseName();

    std::vector< libcasm_ir::Type::Ptr > argTypeList;
    for( auto argumentType : *node.argumentTypes() )
    {
        if( not argumentType->type() )
        {
            m_log.info( { argumentType->sourceLocation() },
                "TODO: '" + name + "' has a non-typed argument(s)" );
            return;
        }

        argTypeList.emplace_back( argumentType->type() );
    }

    if( name.compare( "RuleRef" ) == 0 )
    {
        if( node.returnType()->type() )
        {
            const auto type = libstdhl::make< libcasm_ir::RuleReferenceType >(
                node.returnType()->type(), argTypeList );
            node.setType( type );
        }
    }
    else if( name.compare( "FuncRef" ) == 0 )
    {
        if( node.returnType()->type() )
        {
            const auto type
                = libstdhl::make< libcasm_ir::FunctionReferenceType >(
                    node.returnType()->type(), argTypeList );
            node.setType( type );
        }
    }
    else
    {
        m_err++;
        m_log.error( { node.sourceLocation() },
            "unknown relation type '" + name + "' found" );
    }
}

void TypeCheckVisitor::visit( FixedSizedType& node )
{
    if( not node.type() )
    {
        const auto& name = node.name()->baseName();
        auto& expr = *node.size();

        if( name.compare( "Bit" ) == 0 )
        {
            if( expr.id() == Node::ID::VALUE_ATOM and expr.type()->isInteger() )
            {
                const auto& atom = static_cast< const ValueAtom& >( expr );

                const auto value
                    = std::static_pointer_cast< libcasm_ir::IntegerConstant >(
                        atom.value() );

                try
                {
                    auto type = libstdhl::get< libcasm_ir::BitType >( value );
                    node.setType( type );
                }
                catch( const std::domain_error& e )
                {
                    m_err++;
                    m_log.error( { expr.sourceLocation() }, e.what() );
                }
            }
            else
            {
                m_err++;
                m_log.error( { expr.sourceLocation() },
                    "unsupported expr for 'Bit' type, constant Integer value "
                    "expected" );
            }
        }
        else if( name.compare( "Integer" ) == 0 )
        {
            if( expr.id() == Node::ID::RANGE_EXPRESSION )
            {
                const auto& range_expr
                    = static_cast< const RangeExpression& >( expr );

                const auto& lhs = *range_expr.left();
                const auto& rhs = *range_expr.right();

                if( lhs.id() == Node::ID::VALUE_ATOM and lhs.type()->isInteger()
                    and rhs.id() == Node::ID::VALUE_ATOM
                    and rhs.type()->isInteger() )
                {
                    const auto& atom_lhs
                        = static_cast< const ValueAtom& >( lhs );

                    const auto& atom_rhs
                        = static_cast< const ValueAtom& >( rhs );

                    const auto ir_lhs = std::
                        static_pointer_cast< libcasm_ir::IntegerConstant >(
                            atom_lhs.value() );

                    const auto ir_rhs = std::
                        static_pointer_cast< libcasm_ir::IntegerConstant >(
                            atom_rhs.value() );

                    auto range_type = libstdhl::get< libcasm_ir::RangeType >(
                        ir_lhs, ir_rhs );

                    assert( not expr.type() );
                    expr.setType( range_type );

                    try
                    {
                        auto type = libstdhl::get< libcasm_ir::IntegerType >(
                            range_type );

                        node.setType( type );
                    }
                    catch( const std::domain_error& e )
                    {
                        m_err++;
                        m_log.error( { expr.sourceLocation() }, e.what() );
                    }
                }
            }
            else
            {
                m_err++;
                m_log.error( { expr.sourceLocation() },
                    "unsupported expr for 'Integer' type, only range "
                    "expressions are allowed, e.g. `Integer'[5..10]`" );
            }
        }
        else
        {
            m_err++;
            m_log.error( { node.sourceLocation() },
                "unknown type '" + name + "' found" );
        }
    }

    RecursiveVisitor::visit( node );
}

void TypeCheckVisitor::visit( ExpressionCase& node )
{
    // omit redundant traversal of rule(), see visit( CaseRule& )
    node.expression()->accept( *this );
}

void TypeCheckVisitor::visit( DefaultCase& node )
{
    // omit redundant traversal of rule(), see visit( CaseRule& )
}

u64 TypeCheckVisitor::errors( void ) const
{
    return m_err;
}

void TypeCheckVisitor::push( VariableDefinition& node )
{
    const auto& name = node.identifier()->name();

    auto result = m_id2var.emplace( name, &node );
    if( not result.second )
    {
        m_err++;
        m_log.error( { node.sourceLocation() },
            "symbol '" + name + "' already defined" );
    }
    m_stack.push( &node );
}

void TypeCheckVisitor::pop( VariableDefinition& node )
{
    const auto& name = node.identifier()->name();

    if( m_id2var.erase( name ) != 1 )
    {
        assert( !" internal error! " );
    }
    assert( m_stack.top() == &node );
    m_stack.pop();
}

//
// TypeInferenceVisitor
//

class TypeInferenceVisitor final : public RecursiveVisitor
{
  public:
    TypeInferenceVisitor( Logger& log, Namespace& symboltable );

    void visit( FunctionDefinition& node ) override;
    void visit( DerivedDefinition& node ) override;
    void visit( RuleDefinition& node ) override;

    void visit( ValueAtom& node ) override;
    void visit( RuleReferenceAtom& node ) override;
    void visit( UndefAtom& node ) override;
    void visit( DirectCallExpression& node ) override;
    void visit( IndirectCallExpression& node ) override;
    void visit( UnaryExpression& node ) override;
    void visit( BinaryExpression& node ) override;
    void visit( RangeExpression& node ) override;
    void visit( ListExpression& node ) override;
    void visit( ConditionalExpression& node ) override;
    void visit( UniversalQuantifierExpression& node ) override;
    void visit( ExistentialQuantifierExpression& node ) override;

    void visit( LetRule& node ) override;
    void visit( UpdateRule& node ) override;

    void assignment( const Node& node, TypedNode& lhs, TypedNode& rhs,
        const std::string& dst, const std::string& src );

    void annotate( const libcasm_ir::Annotation& annotation,
        const Node& node,
        const std::vector< Expression::Ptr >& expressions = {} );

    void inference(
        TypedNode& node, const std::vector< Expression::Ptr >& arguments = {} );

    void inference( FunctionDefinition& node );
    void inference( DerivedDefinition& node );
    void inference( RuleDefinition& node );

    void push( VariableDefinition& node );
    void pop( VariableDefinition& node );
    VariableDefinition& find( const IdentifierPath& node );

    u64 errors( void ) const;

  private:
    Logger& m_log;
    u64 m_err;
    Namespace& m_symboltable;

    std::unordered_map< std::string, VariableDefinition* > m_id2var;

    std::unordered_map< const Node*, std::vector< libcasm_ir::Type::ID > >
        m_resultTypes;
};

TypeInferenceVisitor::TypeInferenceVisitor(
    Logger& log, Namespace& symboltable )
: m_log( log )
, m_err( 0 )
, m_symboltable( symboltable )
{
}

void TypeInferenceVisitor::visit( FunctionDefinition& node )
{
    RecursiveVisitor::visit( node );

    inference( node );
}

void TypeInferenceVisitor::visit( DerivedDefinition& node )
{
    for( const auto& argument : *node.arguments() )
    {
        push( *argument );
    }

    const auto type = node.returnType()->type();
    assert( type );
    m_resultTypes[ node.expression().get() ].emplace_back( type->id() );

    RecursiveVisitor::visit( node );

    inference( node );

    for( const auto& argument : *node.arguments() )
    {
        pop( *argument );
    }
}

void TypeInferenceVisitor::visit( RuleDefinition& node )
{
    for( const auto& argument : *node.arguments() )
    {
        push( *argument );
    }

    RecursiveVisitor::visit( node );

    inference( node );

    for( const auto& argument : *node.arguments() )
    {
        pop( *argument );
    }
}

void TypeInferenceVisitor::visit( ValueAtom& node )
{
    RecursiveVisitor::visit( node );
}

void TypeInferenceVisitor::visit( RuleReferenceAtom& node )
{
    RecursiveVisitor::visit( node );
}

void TypeInferenceVisitor::visit( UndefAtom& node )
{
    RecursiveVisitor::visit( node );
}

void TypeInferenceVisitor::visit( DirectCallExpression& node )
{
    const auto& path = *node.identifier();

    if( node.targetType() == CallExpression::TargetType::BUILTIN )
    {
        try
        {
            const auto& annotation
                = libcasm_ir::Annotation::find( path.baseName() );

            annotate( annotation, node, node.arguments()->data() );
        }
        catch( const std::domain_error& e )
        {
            m_err++;
            m_log.error( { node.sourceLocation() },
                             "unable to resolve built-in symbol '"
                             + path.path()
                             + "', due to missing annotation information from 'libcasm-ir'" );
        }
    }

    RecursiveVisitor::visit( node );

    switch( node.targetType() )
    {
        case CallExpression::TargetType::VARIABLE:
        {
            if( not node.type() )
            {
                inference( node );
                try
                {
                    auto& definition = find( *node.identifier() );
                    definition.setType( node.type() );
                }
                catch( const std::domain_error& e )
                {
                    assert( !" inconsistent symbol table! " );
                }
            }
            break;
        }
        case CallExpression::TargetType::BUILTIN:
        {
            assert( not node.type() );
            inference( node, node.arguments()->data() );
            break;
        }
        case CallExpression::TargetType::DERIVED:
        {
            assert( not node.type() );
            try
            {
                auto symbol = m_symboltable.find( node );
                assert( symbol.targetType()
                        == CallExpression::TargetType::DERIVED );

                auto& definition
                    = static_cast< DerivedDefinition& >( symbol.definition() );

                inference( definition );
                node.setType( definition.type() );
            }
            catch( const std::domain_error& e )
            {
                assert( !" inconsistent symbol table! " );
            }
            break;
        }
        case CallExpression::TargetType::FUNCTION:
        {
            assert( not node.type() );
            try
            {
                auto symbol = m_symboltable.find( node );
                assert( symbol.targetType()
                        == CallExpression::TargetType::FUNCTION );

                auto& definition
                    = static_cast< FunctionDefinition& >( symbol.definition() );

                inference( definition );
                node.setType( definition.type() );
            }
            catch( const std::domain_error& e )
            {
                assert( !" inconsistent symbol table! " );
            }
            break;
        }
        case CallExpression::TargetType::RULE:
        {
            assert( not node.type() );
            try
            {
                auto symbol = m_symboltable.find( node );
                assert(
                    symbol.targetType() == CallExpression::TargetType::RULE );

                auto& definition
                    = static_cast< RuleDefinition& >( symbol.definition() );

                inference( definition );
                node.setType( definition.type() );
            }
            catch( const std::domain_error& e )
            {
                assert( !" inconsistent symbol table! " );
            }
            break;
        }
        case CallExpression::TargetType::ENUMERATION:
        {
            if( not node.type() )
            {
                m_err++;
                m_log.error( { node.sourceLocation() }, "TODO: ENUMERATION" );
            }
            break;
        }
        case CallExpression::TargetType::CONSTANT:
        {
            if( not node.type() )
            {
                m_err++;
                m_log.error( { node.sourceLocation() }, "TODO: CONSTANT" );
            }
            break;
        }
        case CallExpression::TargetType::UNKNOWN:
        {
            assert( !" internal error" );
            break;
        }
    }
}

void TypeInferenceVisitor::visit( IndirectCallExpression& node )
{
    RecursiveVisitor::visit( node );

    if( not node.expression()->type() )
    {
        m_err++;
        m_log.error( { node.sourceLocation() },
            "unable to resolve type of indirect call expression" );
    }

    node.setType( node.expression()->type() );
}

void TypeInferenceVisitor::visit( UnaryExpression& node )
{
    const auto& annotation = libcasm_ir::Annotation::find( node.op() );

    annotate( annotation, node, { node.expression() } );

    RecursiveVisitor::visit( node );

    inference( node, { node.expression() } );
}

void TypeInferenceVisitor::visit( BinaryExpression& node )
{
    const auto& annotation = libcasm_ir::Annotation::find( node.op() );

    annotate( annotation, node, { node.left(), node.right() } );

    RecursiveVisitor::visit( node );

    inference( node, { node.left(), node.right() } );
}

void TypeInferenceVisitor::visit( RangeExpression& node )
{
    RecursiveVisitor::visit( node );
}
void TypeInferenceVisitor::visit( ListExpression& node )
{
    RecursiveVisitor::visit( node );
}
void TypeInferenceVisitor::visit( ConditionalExpression& node )
{
    RecursiveVisitor::visit( node );
}
void TypeInferenceVisitor::visit( UniversalQuantifierExpression& node )
{
    RecursiveVisitor::visit( node );
}
void TypeInferenceVisitor::visit( ExistentialQuantifierExpression& node )
{
    RecursiveVisitor::visit( node );
}

void TypeInferenceVisitor::visit( LetRule& node )
{
    push( *node.variable() );
    RecursiveVisitor::visit( node );
    pop( *node.variable() );

    assignment( node, *node.variable(), *node.expression(),
        "let variable '" + node.variable()->identifier()->name() + "'",
        "binding expression" );
}

void TypeInferenceVisitor::visit( UpdateRule& node )
{
    RecursiveVisitor::visit( node );

    assignment( node, *node.function(), *node.expression(), "updated function",
        "updating expression" );
}

void TypeInferenceVisitor::assignment( const Node& node, TypedNode& lhs,
    TypedNode& rhs, const std::string& dst, const std::string& src )
{
    if( not rhs.type() and rhs.id() == Node::ID::UNDEF_ATOM )
    {
        rhs.setType( lhs.type() );
    }

    const auto error_count = m_err;

    if( not lhs.type() )
    {
        m_err++;
        m_log.error(
            { lhs.sourceLocation() }, "unable to infer type of " + dst );
    }

    if( not rhs.type() )
    {
        m_err++;
        m_log.error(
            { rhs.sourceLocation() }, "unable to infer type of " + src );
    }

    if( error_count != m_err )
    {
        return;
    }

    if( lhs.type()->result() != rhs.type()->result() )
    {
        m_err++;
        m_log.error( { lhs.sourceLocation(), rhs.sourceLocation() },
            "type of " + dst + " does not match type of " + src + ": '"
                + lhs.type()->description()
                + "' != '"
                + rhs.type()->description()
                + "'" );
    }
}

void TypeInferenceVisitor::annotate( const libcasm_ir::Annotation& annotation,
    const Node& node, const std::vector< Expression::Ptr >& expressions )
{
    auto result = m_resultTypes.find( &node );
    if( result != m_resultTypes.end() )
    {
        const auto& map = annotation.map();

        for( auto t : result->second )
        {
            for( std::size_t c = 0; c < expressions.size(); c++ )
            {
                const auto& map_expr = map.at( t ).at( c );

                std::copy( map_expr.begin(), map_expr.end(),
                    std::back_inserter(
                        m_resultTypes[ expressions[ c ].get() ] ) );
            }
        }

        const auto& map_res = annotation.resultTypes();
        std::vector< libcasm_ir::Type::ID > tmp = {};

        std::set_intersection( result->second.begin(), result->second.end(),
            map_res.begin(), map_res.end(), std::back_inserter( tmp ) );

        m_resultTypes[&node ] = std::move( tmp );
    }
    else
    {
        for( std::size_t c = 0; c < expressions.size(); c++ )
        {
            const auto& map_expr = annotation.argumentTypes( c );

            std::copy( map_expr.begin(), map_expr.end(),
                std::back_inserter( m_resultTypes[ expressions[ c ].get() ] ) );
        }

        const auto& map_res = annotation.resultTypes();

        std::copy( map_res.begin(), map_res.end(),
            std::back_inserter( m_resultTypes[&node ] ) );
    }
}

void TypeInferenceVisitor::inference(
    TypedNode& node, const std::vector< Expression::Ptr >& arguments )
{
    auto result = m_resultTypes.find( &node );
    if( result == m_resultTypes.end() )
    {
        m_err++;
        m_log.error(
            { node.sourceLocation() }, "unable to find type annotation" );
        return;
    }

    const auto& resTypes = result->second;

    if( resTypes.size() != 1 )
    {
        m_err++;
        m_log.warning(
            { node.sourceLocation() }, "multiple return types found!" );
        return;
    }

    switch( *resTypes.begin() )
    {
        case libcasm_ir::Type::VOID:
        {
            node.setType( VOID );
            break;
        }
        case libcasm_ir::Type::BOOLEAN:
        {
            node.setType( BOOLEAN );
            break;
        }
        case libcasm_ir::Type::INTEGER:
        {
            // TODO: PPA: check for ranged integers
            node.setType( INTEGER );
            break;
        }
        case libcasm_ir::Type::BIT:
        {
            // node.setType( Bit(n) ); // depends on other bit sizes
            assert( 0 ); // TODO: PPA:
            break;
        }
        case libcasm_ir::Type::STRING:
        {
            node.setType( STRING );
            break;
        }
        case libcasm_ir::Type::FLOATING:
        {
            node.setType( FLOATING );
            break;
        }
        case libcasm_ir::Type::RATIONAL:
        {
            node.setType( RATIONAL );
            break;
        }
        case libcasm_ir::Type::RULE_REFERENCE:
        {
            assert(
                0 ); // TODO: PPA: retrieve relation to construct RuleRef type
            // node.setType( ? );
            break;
        }
        case libcasm_ir::Type::FUNCTION_REFERENCE:
        {
            assert(
                0 ); // TODO: PPA: retrieve relation to construct FuncRef type
            // node.setType( ? );
            break;
        }
        default:
        {
            assert( 0 );
        }
    }

    if( not node.type() )
    {
        m_err++;
        m_log.error(
            { node.sourceLocation() }, "unable to resolve type of expression" );
    }
}

void TypeInferenceVisitor::inference( FunctionDefinition& node )
{
    if( node.defaultValue()->id() == Node::ID::UNDEF_ATOM
        and not node.defaultValue()->type() )
    {
        node.defaultValue()->setType( node.returnType()->type() );
    }

    if( node.type() )
    {
        return;
    }

    std::vector< libcasm_ir::Type::Ptr > argTypeList;
    for( auto argumentType : *node.argumentTypes() )
    {
        if( not argumentType->type() )
        {
            m_log.info( { argumentType->sourceLocation() },
                "TODO: '" + node.identifier()->name()
                    + "' has a non-typed argument(s)" );
            return;
        }

        argTypeList.emplace_back( argumentType->type() );
    }

    const auto type = libstdhl::make< libcasm_ir::RelationType >(
        node.returnType()->type(), argTypeList );

    node.setType( type );
}

void TypeInferenceVisitor::inference( DerivedDefinition& node )
{
    if( node.type() )
    {
        return;
    }

    std::vector< libcasm_ir::Type::Ptr > argTypeList;
    for( auto argumentType : *node.arguments() )
    {
        if( not argumentType->type() )
        {
            m_log.info( { argumentType->sourceLocation() },
                "TODO: '" + node.identifier()->name()
                    + "' has a non-typed argument(s)" );
            return;
        }

        argTypeList.emplace_back( argumentType->type() );
    }

    const auto type = libstdhl::make< libcasm_ir::RelationType >(
        node.returnType()->type(), argTypeList );

    node.setType( type );
}

void TypeInferenceVisitor::inference( RuleDefinition& node )
{
    if( node.type() )
    {
        return;
    }

    std::vector< libcasm_ir::Type::Ptr > argTypeList;
    for( auto argumentType : *node.arguments() )
    {
        if( not argumentType->type() )
        {
            m_log.info( { argumentType->sourceLocation() },
                "TODO: '" + node.identifier()->name()
                    + "' has a non-typed argument(s)" );
            return;
        }

        argTypeList.emplace_back( argumentType->type() );
    }

    const auto type = libstdhl::make< libcasm_ir::RelationType >(
        node.returnType()->type(), argTypeList );

    node.setType( type );
}

void TypeInferenceVisitor::push( VariableDefinition& node )
{
    const auto& name = node.identifier()->name();

    auto result = m_id2var.emplace( name, &node );
    if( not result.second )
    {
        m_err++;
        m_log.error( { node.sourceLocation() },
            "symbol '" + name + "' already defined" );
    }
}

void TypeInferenceVisitor::pop( VariableDefinition& node )
{
    const auto& name = node.identifier()->name();

    if( m_id2var.erase( name ) != 1 )
    {
        assert( !" internal error! " );
    }
}

VariableDefinition& TypeInferenceVisitor::find( const IdentifierPath& node )
{
    auto result = m_id2var.find( node.baseName() );
    if( result == m_id2var.end() )
    {
        throw std::domain_error(
            "unable to find symbol '" + node.path() + "'" );
    }

    return *result->second;
}

u64 TypeInferenceVisitor::errors( void ) const
{
    return m_err;
}

//
// TypeInferencePass
//

void TypeInferencePass::usage( libpass::PassUsage& pu )
{
    pu.require< SymbolResolverPass >();
}

u1 TypeInferencePass::run( libpass::PassResult& pr )
{
    Logger log( &id, stream() );

    const auto data = pr.result< SymbolResolverPass >();
    const auto specification = data->specification();
    const auto symboltable = data->symboltable();

    TypeCheckVisitor typeCheck( log, *symboltable );
    specification->accept( typeCheck );

    const auto typChkErr = typeCheck.errors();
    if( typChkErr )
    {
        log.debug( "found %lu error(s) during type checking", typChkErr );
        return false;
    }

    TypeInferenceVisitor typeInfer( log, *symboltable );
    specification->accept( typeInfer );

    const auto typInfErr = typeInfer.errors();
    if( typInfErr )
    {
        log.debug( "found %lu error(s) during type inference", typInfErr );
        return false;
    }

    pr.setResult< TypeInferencePass >(
        libstdhl::make< Data >( specification ) );

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