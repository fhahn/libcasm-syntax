// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// First part of user declarations.

#line 37 "GrammarParser.cpp"  // lalr1.cc:404

#ifndef YY_NULLPTR
#if defined __cplusplus && 201103L <= __cplusplus
#define YY_NULLPTR nullptr
#else
#define YY_NULLPTR 0
#endif
#endif

#include "GrammarParser.tab.h"

// User implementation prologue.

#line 51 "GrammarParser.cpp"  // lalr1.cc:412
// Unqualified %code blocks.
#line 87 "../../obj/src/GrammarParser.yy"  // lalr1.cc:413

#include "Exception.h"
#include "Lexer.h"
#include "Logger.h"
#include "SourceLocation.h"

#include <libstdhl/Type>

#undef yylex
#define yylex lexer.nextToken

static BasicType::Ptr createVoidType( SourceLocation& sourceLocation )
{
    const auto type = libstdhl::Memory::get< libcasm_ir::VoidType >();
    const auto name = Ast::make< Identifier >( sourceLocation, type->description() );
    const auto path = Ast::make< IdentifierPath >( sourceLocation, name );
    const auto node = Ast::make< BasicType >( sourceLocation, path );
    node->setType( type );
    return node;
}

static BasicType::Ptr createRuleRefType( SourceLocation& sourceLocation )
{
    const auto type = libstdhl::Memory::get< libcasm_ir::RuleReferenceType >();
    const auto name = Ast::make< Identifier >( sourceLocation, type->description() );
    const auto path = Ast::make< IdentifierPath >( sourceLocation, name );
    const auto node = Ast::make< BasicType >( sourceLocation, path );
    node->setType( type );
    return node;
}

static BasicType::Ptr createAgentType( SourceLocation& sourceLocation )
{
    const auto name = Ast::make< Identifier >( sourceLocation, "Agent" );
    const auto path = Ast::make< IdentifierPath >( sourceLocation, name );
    const auto node = Ast::make< BasicType >( sourceLocation, path );
    return node;
}

static FunctionDefinition::Ptr createProgramFunction( SourceLocation& sourceLocation )
{
    const auto agentType = createAgentType( sourceLocation );
    const auto ruleRefType = createRuleRefType( sourceLocation );

    const auto argTypes = Ast::make< Types >( sourceLocation );
    argTypes->add( agentType );

    const auto program = Ast::make< Identifier >( sourceLocation, "program" );
    return Ast::make< FunctionDefinition >( sourceLocation, program, argTypes, ruleRefType );
}

static Rule::Ptr wrapInBlockRule( const Rule::Ptr& rule )
{
    if( rule == nullptr )
    {
        // this can happen while recovering from a syntax error
        return nullptr;
    }

    if( ( rule->id() == Node::ID::BLOCK_RULE ) or ( rule->id() == Node::ID::SEQUENCE_RULE ) )
    {
        return rule;  // no need to wrap it
    }

    const auto& sourceLocation = rule->sourceLocation();
    const auto rules = Ast::make< Rules >( sourceLocation );
    rules->add( rule );
    return Ast::make< BlockRule >( sourceLocation, rules );
}

#line 125 "GrammarParser.cpp"  // lalr1.cc:413

#ifndef YY_
#if defined YYENABLE_NLS && YYENABLE_NLS
#if ENABLE_NLS
#include <libintl.h>  // FIXME: INFRINGES ON USER NAME SPACE.
#define YY_( msgid ) dgettext( "bison-runtime", msgid )
#endif
#endif
#ifndef YY_
#define YY_( msgid ) msgid
#endif
#endif

#define YYRHSLOC( Rhs, K ) ( ( Rhs )[ K ].location )
    /* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
       If N is 0, then set CURRENT to the empty location which ends
       the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
#define YYLLOC_DEFAULT( Current, Rhs, N )                                 \
    do                                                                    \
        if( N )                                                           \
        {                                                                 \
            ( Current ).begin = YYRHSLOC( Rhs, 1 ).begin;                 \
            ( Current ).end = YYRHSLOC( Rhs, N ).end;                     \
        }                                                                 \
        else                                                              \
        {                                                                 \
            ( Current ).begin = ( Current ).end = YYRHSLOC( Rhs, 0 ).end; \
        }                                                                 \
    while( /*CONSTCOND*/ false )
#endif

// Suppress unused-variable warnings by "using" E.
#define YYUSE( E ) ( (void)( E ) )

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
#define YYCDEBUG   \
    if( yydebug_ ) \
    ( *yycdebug_ )

#define YY_SYMBOL_PRINT( Title, Symbol )     \
    do                                       \
    {                                        \
        if( yydebug_ )                       \
        {                                    \
            *yycdebug_ << Title << ' ';      \
            yy_print_( *yycdebug_, Symbol ); \
            *yycdebug_ << std::endl;         \
        }                                    \
    } while( false )

#define YY_REDUCE_PRINT( Rule )       \
    do                                \
    {                                 \
        if( yydebug_ )                \
            yy_reduce_print_( Rule ); \
    } while( false )

#define YY_STACK_PRINT()      \
    do                        \
    {                         \
        if( yydebug_ )        \
            yystack_print_(); \
    } while( false )

#else  // !YYDEBUG

#define YYCDEBUG \
    if( false )  \
    std::cerr
#define YY_SYMBOL_PRINT( Title, Symbol ) YYUSE( Symbol )
#define YY_REDUCE_PRINT( Rule ) static_cast< void >( 0 )
#define YY_STACK_PRINT() static_cast< void >( 0 )

#endif  // !YYDEBUG

#define yyerrok ( yyerrstatus_ = 0 )
#define yyclearin ( yyla.clear() )

#define YYACCEPT goto yyacceptlab
#define YYABORT goto yyabortlab
#define YYERROR goto yyerrorlab
#define YYRECOVERING() ( !!yyerrstatus_ )

#line 49 "../../obj/src/GrammarParser.yy"  // lalr1.cc:479
namespace libcasm_fe
{
#line 211 "GrammarParser.cpp"  // lalr1.cc:479

    /* Return YYSTR after stripping away unnecessary quotes and
       backslashes, so that it's suitable for yyerror.  The heuristic is
       that double-quoting is unnecessary unless the string contains an
       apostrophe, a comma, or backslash (other than backslash-backslash).
       YYSTR is taken from yytname.  */
    std::string Parser::yytnamerr_( const char* yystr )
    {
        if( *yystr == '"' )
        {
            std::string yyr = "";
            char const* yyp = yystr;

            for( ;; )
                switch( *++yyp )
                {
                    case '\'':
                    case ',':
                        goto do_not_strip_quotes;

                    case '\\':
                        if( *++yyp != '\\' )
                            goto do_not_strip_quotes;
                        // Fall through.
                    default:
                        yyr += *yyp;
                        break;

                    case '"':
                        return yyr;
                }
        do_not_strip_quotes:;
        }

        return yystr;
    }

    /// Build a parser object.
    Parser::Parser( Logger& log_yyarg, Lexer& lexer_yyarg, Specification& specification_yyarg )
    :
#if YYDEBUG
        yydebug_( false )
    , yycdebug_( &std::cerr )
    ,
#endif
        log( log_yyarg )
    , lexer( lexer_yyarg )
    , specification( specification_yyarg )
    {
    }

    Parser::~Parser()
    {
    }

    /*---------------.
    | Symbol types.  |
    `---------------*/

    // by_state.
    inline Parser::by_state::by_state()
    : state( empty_state )
    {
    }

    inline Parser::by_state::by_state( const by_state& other )
    : state( other.state )
    {
    }

    inline void Parser::by_state::clear()
    {
        state = empty_state;
    }

    inline void Parser::by_state::move( by_state& that )
    {
        state = that.state;
        that.clear();
    }

    inline Parser::by_state::by_state( state_type s )
    : state( s )
    {
    }

    inline Parser::symbol_number_type Parser::by_state::type_get() const
    {
        if( state == empty_state )
            return empty_symbol;
        else
            return yystos_[ state ];
    }

    inline Parser::stack_symbol_type::stack_symbol_type()
    {
    }

    inline Parser::stack_symbol_type::stack_symbol_type( state_type s, symbol_type& that )
    : super_type( s, that.location )
    {
        switch( that.type_get() )
        {
            case 162:  // Attribute
                value.move< Attribute::Ptr >( that.value );
                break;

            case 161:  // Attributes
                value.move< Attributes::Ptr >( that.value );
                break;

            case 163:  // BasicAttribute
                value.move< BasicAttribute::Ptr >( that.value );
                break;

            case 139:  // BasicType
                value.move< BasicType::Ptr >( that.value );
                break;

            case 109:  // BlockRule
                value.move< BlockRule::Ptr >( that.value );
                break;

            case 117:  // CallExpression
                value.move< CallExpression::Ptr >( that.value );
                break;

            case 112:  // CallRule
                value.move< CallRule::Ptr >( that.value );
                break;

            case 103:  // CaseLabel
                value.move< Case::Ptr >( that.value );
                break;

            case 102:  // CaseRule
                value.move< CaseRule::Ptr >( that.value );
                break;

            case 104:  // CaseLabels
                value.move< Cases::Ptr >( that.value );
                break;

            case 123:  // ChooseExpression
                value.move< ChooseExpression::Ptr >( that.value );
                break;

            case 107:  // ChooseRule
                value.move< ChooseRule::Ptr >( that.value );
                break;

            case 140:  // ComposedType
                value.move< ComposedType::Ptr >( that.value );
                break;

            case 122:  // ConditionalExpression
                value.move< ConditionalExpression::Ptr >( that.value );
                break;

            case 101:  // ConditionalRule
                value.move< ConditionalRule::Ptr >( that.value );
                break;

            case 89:  // AttributedDefinition
            case 90:  // Definition
                value.move< Definition::Ptr >( that.value );
                break;

            case 88:  // Definitions
                value.move< Definitions::Ptr >( that.value );
                break;

            case 92:  // DerivedDefinition
                value.move< DerivedDefinition::Ptr >( that.value );
                break;

            case 118:  // DirectCallExpression
                value.move< DirectCallExpression::Ptr >( that.value );
                break;

            case 91:  // EnumerationDefinition
                value.move< EnumerationDefinition::Ptr >( that.value );
                break;

            case 96:  // EnumeratorDefinition
                value.move< EnumeratorDefinition::Ptr >( that.value );
                break;

            case 97:  // Enumerators
                value.move< Enumerators::Ptr >( that.value );
                break;

            case 125:  // ExistentialQuantifierExpression
                value.move< ExistentialQuantifierExpression::Ptr >( that.value );
                break;

            case 114:  // Term
            case 115:  // Expression
            case 128:  // Literal
            case 149:  // MaybeDefined
                value.move< Expression::Ptr >( that.value );
                break;

            case 164:  // ExpressionAttribute
                value.move< ExpressionAttribute::Ptr >( that.value );
                break;

            case 113:  // Terms
            case 143:  // Arguments
            case 144:  // TwoOrMoreArguments
                value.move< Expressions::Ptr >( that.value );
                break;

            case 142:  // FixedSizedType
                value.move< FixedSizedType::Ptr >( that.value );
                break;

            case 106:  // ForallRule
                value.move< ForallRule::Ptr >( that.value );
                break;

            case 94:  // FunctionDefinition
            case 95:  // ProgramFunctionDefinition
                value.move< FunctionDefinition::Ptr >( that.value );
                break;

            case 87:  // Header
                value.move< HeaderDefinition::Ptr >( that.value );
                break;

            case 154:  // Identifier
                value.move< Identifier::Ptr >( that.value );
                break;

            case 155:  // IdentifierPath
                value.move< IdentifierPath::Ptr >( that.value );
                break;

            case 156:  // DotSeparatedIdentifiers
                value.move< Identifiers::Ptr >( that.value );
                break;

            case 119:  // IndirectCallExpression
                value.move< IndirectCallExpression::Ptr >( that.value );
                break;

            case 108:  // IterateRule
                value.move< IterateRule::Ptr >( that.value );
                break;

            case 121:  // LetExpression
                value.move< LetExpression::Ptr >( that.value );
                break;

            case 105:  // LetRule
                value.move< LetRule::Ptr >( that.value );
                break;

            case 126:  // List
                value.move< ListExpression::Ptr >( that.value );
                break;

            case 120:  // MethodCallExpression
                value.move< MethodCallExpression::Ptr >( that.value );
                break;

            case 150:  // MaybeInitially
            case 151:  // Initializers
            case 153:  // MaybeInitializers
                value.move< NodeList< UpdateRule >::Ptr >( that.value );
                break;

            case 147:  // Parameters
            case 148:  // MaybeParameters
                value.move< NodeList< VariableDefinition >::Ptr >( that.value );
                break;

            case 127:  // Range
                value.move< RangeExpression::Ptr >( that.value );
                break;

            case 136:  // ReferenceLiteral
                value.move< ReferenceAtom::Ptr >( that.value );
                break;

            case 141:  // RelationType
                value.move< RelationType::Ptr >( that.value );
                break;

            case 98:  // Rule
                value.move< Rule::Ptr >( that.value );
                break;

            case 93:  // RuleDefinition
                value.move< RuleDefinition::Ptr >( that.value );
                break;

            case 99:  // Rules
                value.move< Rules::Ptr >( that.value );
                break;

            case 110:  // SequenceRule
                value.move< SequenceRule::Ptr >( that.value );
                break;

            case 100:  // SkipRule
                value.move< SkipRule::Ptr >( that.value );
                break;

            case 86:  // Specification
                value.move< Specification::Ptr >( that.value );
                break;

            case 116:  // TypeCastingExpression
                value.move< TypeCastingExpression::Ptr >( that.value );
                break;

            case 137:  // Types
            case 145:  // FunctionParameters
            case 146:  // MaybeFunctionParameters
                value.move< Types::Ptr >( that.value );
                break;

            case 129:  // UndefinedLiteral
                value.move< UndefAtom::Ptr >( that.value );
                break;

            case 124:  // UniversalQuantifierExpression
                value.move< UniversalQuantifierExpression::Ptr >( that.value );
                break;

            case 111:  // UpdateRule
            case 152:  // Initializer
                value.move< UpdateRule::Ptr >( that.value );
                break;

            case 130:  // BooleanLiteral
            case 131:  // IntegerLiteral
            case 132:  // RationalLiteral
            case 133:  // DecimalLiteral
            case 134:  // BinaryLiteral
            case 135:  // StringLiteral
                value.move< ValueAtom::Ptr >( that.value );
                break;

            case 157:  // Variable
            case 158:  // TypedVariable
            case 159:  // AttributedVariable
            case 160:  // TypedAttributedVariable
                value.move< VariableDefinition::Ptr >( that.value );
                break;

            case 138:  // Type
                value.move< libcasm_fe::Ast::Type::Ptr >( that.value );
                break;

            case 72:  // "binary"
            case 73:  // "hexadecimal"
            case 74:  // "integer"
            case 75:  // "rational"
            case 76:  // "decimal"
            case 77:  // "string"
            case 78:  // "identifier"
                value.move< std::string >( that.value );
                break;

            default:
                break;
        }

        // that is emptied.
        that.type = empty_symbol;
    }

    inline Parser::stack_symbol_type& Parser::stack_symbol_type::operator=(
        const stack_symbol_type& that )
    {
        state = that.state;
        switch( that.type_get() )
        {
            case 162:  // Attribute
                value.copy< Attribute::Ptr >( that.value );
                break;

            case 161:  // Attributes
                value.copy< Attributes::Ptr >( that.value );
                break;

            case 163:  // BasicAttribute
                value.copy< BasicAttribute::Ptr >( that.value );
                break;

            case 139:  // BasicType
                value.copy< BasicType::Ptr >( that.value );
                break;

            case 109:  // BlockRule
                value.copy< BlockRule::Ptr >( that.value );
                break;

            case 117:  // CallExpression
                value.copy< CallExpression::Ptr >( that.value );
                break;

            case 112:  // CallRule
                value.copy< CallRule::Ptr >( that.value );
                break;

            case 103:  // CaseLabel
                value.copy< Case::Ptr >( that.value );
                break;

            case 102:  // CaseRule
                value.copy< CaseRule::Ptr >( that.value );
                break;

            case 104:  // CaseLabels
                value.copy< Cases::Ptr >( that.value );
                break;

            case 123:  // ChooseExpression
                value.copy< ChooseExpression::Ptr >( that.value );
                break;

            case 107:  // ChooseRule
                value.copy< ChooseRule::Ptr >( that.value );
                break;

            case 140:  // ComposedType
                value.copy< ComposedType::Ptr >( that.value );
                break;

            case 122:  // ConditionalExpression
                value.copy< ConditionalExpression::Ptr >( that.value );
                break;

            case 101:  // ConditionalRule
                value.copy< ConditionalRule::Ptr >( that.value );
                break;

            case 89:  // AttributedDefinition
            case 90:  // Definition
                value.copy< Definition::Ptr >( that.value );
                break;

            case 88:  // Definitions
                value.copy< Definitions::Ptr >( that.value );
                break;

            case 92:  // DerivedDefinition
                value.copy< DerivedDefinition::Ptr >( that.value );
                break;

            case 118:  // DirectCallExpression
                value.copy< DirectCallExpression::Ptr >( that.value );
                break;

            case 91:  // EnumerationDefinition
                value.copy< EnumerationDefinition::Ptr >( that.value );
                break;

            case 96:  // EnumeratorDefinition
                value.copy< EnumeratorDefinition::Ptr >( that.value );
                break;

            case 97:  // Enumerators
                value.copy< Enumerators::Ptr >( that.value );
                break;

            case 125:  // ExistentialQuantifierExpression
                value.copy< ExistentialQuantifierExpression::Ptr >( that.value );
                break;

            case 114:  // Term
            case 115:  // Expression
            case 128:  // Literal
            case 149:  // MaybeDefined
                value.copy< Expression::Ptr >( that.value );
                break;

            case 164:  // ExpressionAttribute
                value.copy< ExpressionAttribute::Ptr >( that.value );
                break;

            case 113:  // Terms
            case 143:  // Arguments
            case 144:  // TwoOrMoreArguments
                value.copy< Expressions::Ptr >( that.value );
                break;

            case 142:  // FixedSizedType
                value.copy< FixedSizedType::Ptr >( that.value );
                break;

            case 106:  // ForallRule
                value.copy< ForallRule::Ptr >( that.value );
                break;

            case 94:  // FunctionDefinition
            case 95:  // ProgramFunctionDefinition
                value.copy< FunctionDefinition::Ptr >( that.value );
                break;

            case 87:  // Header
                value.copy< HeaderDefinition::Ptr >( that.value );
                break;

            case 154:  // Identifier
                value.copy< Identifier::Ptr >( that.value );
                break;

            case 155:  // IdentifierPath
                value.copy< IdentifierPath::Ptr >( that.value );
                break;

            case 156:  // DotSeparatedIdentifiers
                value.copy< Identifiers::Ptr >( that.value );
                break;

            case 119:  // IndirectCallExpression
                value.copy< IndirectCallExpression::Ptr >( that.value );
                break;

            case 108:  // IterateRule
                value.copy< IterateRule::Ptr >( that.value );
                break;

            case 121:  // LetExpression
                value.copy< LetExpression::Ptr >( that.value );
                break;

            case 105:  // LetRule
                value.copy< LetRule::Ptr >( that.value );
                break;

            case 126:  // List
                value.copy< ListExpression::Ptr >( that.value );
                break;

            case 120:  // MethodCallExpression
                value.copy< MethodCallExpression::Ptr >( that.value );
                break;

            case 150:  // MaybeInitially
            case 151:  // Initializers
            case 153:  // MaybeInitializers
                value.copy< NodeList< UpdateRule >::Ptr >( that.value );
                break;

            case 147:  // Parameters
            case 148:  // MaybeParameters
                value.copy< NodeList< VariableDefinition >::Ptr >( that.value );
                break;

            case 127:  // Range
                value.copy< RangeExpression::Ptr >( that.value );
                break;

            case 136:  // ReferenceLiteral
                value.copy< ReferenceAtom::Ptr >( that.value );
                break;

            case 141:  // RelationType
                value.copy< RelationType::Ptr >( that.value );
                break;

            case 98:  // Rule
                value.copy< Rule::Ptr >( that.value );
                break;

            case 93:  // RuleDefinition
                value.copy< RuleDefinition::Ptr >( that.value );
                break;

            case 99:  // Rules
                value.copy< Rules::Ptr >( that.value );
                break;

            case 110:  // SequenceRule
                value.copy< SequenceRule::Ptr >( that.value );
                break;

            case 100:  // SkipRule
                value.copy< SkipRule::Ptr >( that.value );
                break;

            case 86:  // Specification
                value.copy< Specification::Ptr >( that.value );
                break;

            case 116:  // TypeCastingExpression
                value.copy< TypeCastingExpression::Ptr >( that.value );
                break;

            case 137:  // Types
            case 145:  // FunctionParameters
            case 146:  // MaybeFunctionParameters
                value.copy< Types::Ptr >( that.value );
                break;

            case 129:  // UndefinedLiteral
                value.copy< UndefAtom::Ptr >( that.value );
                break;

            case 124:  // UniversalQuantifierExpression
                value.copy< UniversalQuantifierExpression::Ptr >( that.value );
                break;

            case 111:  // UpdateRule
            case 152:  // Initializer
                value.copy< UpdateRule::Ptr >( that.value );
                break;

            case 130:  // BooleanLiteral
            case 131:  // IntegerLiteral
            case 132:  // RationalLiteral
            case 133:  // DecimalLiteral
            case 134:  // BinaryLiteral
            case 135:  // StringLiteral
                value.copy< ValueAtom::Ptr >( that.value );
                break;

            case 157:  // Variable
            case 158:  // TypedVariable
            case 159:  // AttributedVariable
            case 160:  // TypedAttributedVariable
                value.copy< VariableDefinition::Ptr >( that.value );
                break;

            case 138:  // Type
                value.copy< libcasm_fe::Ast::Type::Ptr >( that.value );
                break;

            case 72:  // "binary"
            case 73:  // "hexadecimal"
            case 74:  // "integer"
            case 75:  // "rational"
            case 76:  // "decimal"
            case 77:  // "string"
            case 78:  // "identifier"
                value.copy< std::string >( that.value );
                break;

            default:
                break;
        }

        location = that.location;
        return *this;
    }

    template < typename Base >
    inline void Parser::yy_destroy_( const char* yymsg, basic_symbol< Base >& yysym ) const
    {
        if( yymsg )
            YY_SYMBOL_PRINT( yymsg, yysym );
    }

#if YYDEBUG
    template < typename Base >
    void Parser::yy_print_( std::ostream& yyo, const basic_symbol< Base >& yysym ) const
    {
        std::ostream& yyoutput = yyo;
        YYUSE( yyoutput );
        symbol_number_type yytype = yysym.type_get();
        // Avoid a (spurious) G++ 4.8 warning about "array subscript is
        // below array bounds".
        if( yysym.empty() )
            std::abort();
        yyo << ( yytype < yyntokens_ ? "token" : "nterm" ) << ' ' << yytname_[ yytype ] << " ("
            << yysym.location << ": ";
        YYUSE( yytype );
        yyo << ')';
    }
#endif

    inline void Parser::yypush_( const char* m, state_type s, symbol_type& sym )
    {
        stack_symbol_type t( s, sym );
        yypush_( m, t );
    }

    inline void Parser::yypush_( const char* m, stack_symbol_type& s )
    {
        if( m )
            YY_SYMBOL_PRINT( m, s );
        yystack_.push( s );
    }

    inline void Parser::yypop_( unsigned int n )
    {
        yystack_.pop( n );
    }

#if YYDEBUG
    std::ostream& Parser::debug_stream() const
    {
        return *yycdebug_;
    }

    void Parser::set_debug_stream( std::ostream& o )
    {
        yycdebug_ = &o;
    }

    Parser::debug_level_type Parser::debug_level() const
    {
        return yydebug_;
    }

    void Parser::set_debug_level( debug_level_type l )
    {
        yydebug_ = l;
    }
#endif  // YYDEBUG

    inline Parser::state_type Parser::yy_lr_goto_state_( state_type yystate, int yysym )
    {
        int yyr = yypgoto_[ yysym - yyntokens_ ] + yystate;
        if( 0 <= yyr && yyr <= yylast_ && yycheck_[ yyr ] == yystate )
            return yytable_[ yyr ];
        else
            return yydefgoto_[ yysym - yyntokens_ ];
    }

    inline bool Parser::yy_pact_value_is_default_( int yyvalue )
    {
        return yyvalue == yypact_ninf_;
    }

    inline bool Parser::yy_table_value_is_error_( int yyvalue )
    {
        return yyvalue == yytable_ninf_;
    }

    int Parser::parse()
    {
        // State.
        int yyn;
        /// Length of the RHS of the rule being reduced.
        int yylen = 0;

        // Error handling.
        int yynerrs_ = 0;
        int yyerrstatus_ = 0;

        /// The lookahead symbol.
        symbol_type yyla;

        /// The locations where the error started and ended.
        stack_symbol_type yyerror_range[ 3 ];

        /// The return value of parse ().
        int yyresult;

        // FIXME: This shoud be completely indented.  It is not yet to
        // avoid gratuitous conflicts when merging into the master branch.
        try
        {
            YYCDEBUG << "Starting parse" << std::endl;

            /* Initialize the stack.  The initial state will be set in
               yynewstate, since the latter expects the semantical and the
               location values to have been already stored, initialize these
               stacks with a primary value.  */
            yystack_.clear();
            yypush_( YY_NULLPTR, 0, yyla );

            // A new symbol was pushed on the stack.
        yynewstate:
            YYCDEBUG << "Entering state " << yystack_[ 0 ].state << std::endl;

            // Accept?
            if( yystack_[ 0 ].state == yyfinal_ )
                goto yyacceptlab;

            goto yybackup;

            // Backup.
        yybackup:

            // Try to take a decision without lookahead.
            yyn = yypact_[ yystack_[ 0 ].state ];
            if( yy_pact_value_is_default_( yyn ) )
                goto yydefault;

            // Read a lookahead token.
            if( yyla.empty() )
            {
                YYCDEBUG << "Reading a token: ";
                try
                {
                    symbol_type yylookahead( yylex() );
                    yyla.move( yylookahead );
                }
                catch( const syntax_error& yyexc )
                {
                    error( yyexc );
                    goto yyerrlab1;
                }
            }
            YY_SYMBOL_PRINT( "Next token is", yyla );

            /* If the proper action on seeing token YYLA.TYPE is to reduce or
               to detect an error, take that action.  */
            yyn += yyla.type_get();
            if( yyn < 0 || yylast_ < yyn || yycheck_[ yyn ] != yyla.type_get() )
                goto yydefault;

            // Reduce or error.
            yyn = yytable_[ yyn ];
            if( yyn <= 0 )
            {
                if( yy_table_value_is_error_( yyn ) )
                    goto yyerrlab;
                yyn = -yyn;
                goto yyreduce;
            }

            // Count tokens shifted since error; after three, turn off error status.
            if( yyerrstatus_ )
                --yyerrstatus_;

            // Shift the lookahead token.
            yypush_( "Shifting", yyn, yyla );
            goto yynewstate;

        /*-----------------------------------------------------------.
        | yydefault -- do the default action for the current state.  |
        `-----------------------------------------------------------*/
        yydefault:
            yyn = yydefact_[ yystack_[ 0 ].state ];
            if( yyn == 0 )
                goto yyerrlab;
            goto yyreduce;

        /*-----------------------------.
        | yyreduce -- Do a reduction.  |
        `-----------------------------*/
        yyreduce:
            yylen = yyr2_[ yyn ];
            {
                stack_symbol_type yylhs;
                yylhs.state = yy_lr_goto_state_( yystack_[ yylen ].state, yyr1_[ yyn ] );
                /* Variants are always initialized to an empty instance of the
                   correct type. The default '$$ = $1' action is NOT applied
                   when using variants.  */
                switch( yyr1_[ yyn ] )
                {
                    case 162:  // Attribute
                        yylhs.value.build< Attribute::Ptr >();
                        break;

                    case 161:  // Attributes
                        yylhs.value.build< Attributes::Ptr >();
                        break;

                    case 163:  // BasicAttribute
                        yylhs.value.build< BasicAttribute::Ptr >();
                        break;

                    case 139:  // BasicType
                        yylhs.value.build< BasicType::Ptr >();
                        break;

                    case 109:  // BlockRule
                        yylhs.value.build< BlockRule::Ptr >();
                        break;

                    case 117:  // CallExpression
                        yylhs.value.build< CallExpression::Ptr >();
                        break;

                    case 112:  // CallRule
                        yylhs.value.build< CallRule::Ptr >();
                        break;

                    case 103:  // CaseLabel
                        yylhs.value.build< Case::Ptr >();
                        break;

                    case 102:  // CaseRule
                        yylhs.value.build< CaseRule::Ptr >();
                        break;

                    case 104:  // CaseLabels
                        yylhs.value.build< Cases::Ptr >();
                        break;

                    case 123:  // ChooseExpression
                        yylhs.value.build< ChooseExpression::Ptr >();
                        break;

                    case 107:  // ChooseRule
                        yylhs.value.build< ChooseRule::Ptr >();
                        break;

                    case 140:  // ComposedType
                        yylhs.value.build< ComposedType::Ptr >();
                        break;

                    case 122:  // ConditionalExpression
                        yylhs.value.build< ConditionalExpression::Ptr >();
                        break;

                    case 101:  // ConditionalRule
                        yylhs.value.build< ConditionalRule::Ptr >();
                        break;

                    case 89:  // AttributedDefinition
                    case 90:  // Definition
                        yylhs.value.build< Definition::Ptr >();
                        break;

                    case 88:  // Definitions
                        yylhs.value.build< Definitions::Ptr >();
                        break;

                    case 92:  // DerivedDefinition
                        yylhs.value.build< DerivedDefinition::Ptr >();
                        break;

                    case 118:  // DirectCallExpression
                        yylhs.value.build< DirectCallExpression::Ptr >();
                        break;

                    case 91:  // EnumerationDefinition
                        yylhs.value.build< EnumerationDefinition::Ptr >();
                        break;

                    case 96:  // EnumeratorDefinition
                        yylhs.value.build< EnumeratorDefinition::Ptr >();
                        break;

                    case 97:  // Enumerators
                        yylhs.value.build< Enumerators::Ptr >();
                        break;

                    case 125:  // ExistentialQuantifierExpression
                        yylhs.value.build< ExistentialQuantifierExpression::Ptr >();
                        break;

                    case 114:  // Term
                    case 115:  // Expression
                    case 128:  // Literal
                    case 149:  // MaybeDefined
                        yylhs.value.build< Expression::Ptr >();
                        break;

                    case 164:  // ExpressionAttribute
                        yylhs.value.build< ExpressionAttribute::Ptr >();
                        break;

                    case 113:  // Terms
                    case 143:  // Arguments
                    case 144:  // TwoOrMoreArguments
                        yylhs.value.build< Expressions::Ptr >();
                        break;

                    case 142:  // FixedSizedType
                        yylhs.value.build< FixedSizedType::Ptr >();
                        break;

                    case 106:  // ForallRule
                        yylhs.value.build< ForallRule::Ptr >();
                        break;

                    case 94:  // FunctionDefinition
                    case 95:  // ProgramFunctionDefinition
                        yylhs.value.build< FunctionDefinition::Ptr >();
                        break;

                    case 87:  // Header
                        yylhs.value.build< HeaderDefinition::Ptr >();
                        break;

                    case 154:  // Identifier
                        yylhs.value.build< Identifier::Ptr >();
                        break;

                    case 155:  // IdentifierPath
                        yylhs.value.build< IdentifierPath::Ptr >();
                        break;

                    case 156:  // DotSeparatedIdentifiers
                        yylhs.value.build< Identifiers::Ptr >();
                        break;

                    case 119:  // IndirectCallExpression
                        yylhs.value.build< IndirectCallExpression::Ptr >();
                        break;

                    case 108:  // IterateRule
                        yylhs.value.build< IterateRule::Ptr >();
                        break;

                    case 121:  // LetExpression
                        yylhs.value.build< LetExpression::Ptr >();
                        break;

                    case 105:  // LetRule
                        yylhs.value.build< LetRule::Ptr >();
                        break;

                    case 126:  // List
                        yylhs.value.build< ListExpression::Ptr >();
                        break;

                    case 120:  // MethodCallExpression
                        yylhs.value.build< MethodCallExpression::Ptr >();
                        break;

                    case 150:  // MaybeInitially
                    case 151:  // Initializers
                    case 153:  // MaybeInitializers
                        yylhs.value.build< NodeList< UpdateRule >::Ptr >();
                        break;

                    case 147:  // Parameters
                    case 148:  // MaybeParameters
                        yylhs.value.build< NodeList< VariableDefinition >::Ptr >();
                        break;

                    case 127:  // Range
                        yylhs.value.build< RangeExpression::Ptr >();
                        break;

                    case 136:  // ReferenceLiteral
                        yylhs.value.build< ReferenceAtom::Ptr >();
                        break;

                    case 141:  // RelationType
                        yylhs.value.build< RelationType::Ptr >();
                        break;

                    case 98:  // Rule
                        yylhs.value.build< Rule::Ptr >();
                        break;

                    case 93:  // RuleDefinition
                        yylhs.value.build< RuleDefinition::Ptr >();
                        break;

                    case 99:  // Rules
                        yylhs.value.build< Rules::Ptr >();
                        break;

                    case 110:  // SequenceRule
                        yylhs.value.build< SequenceRule::Ptr >();
                        break;

                    case 100:  // SkipRule
                        yylhs.value.build< SkipRule::Ptr >();
                        break;

                    case 86:  // Specification
                        yylhs.value.build< Specification::Ptr >();
                        break;

                    case 116:  // TypeCastingExpression
                        yylhs.value.build< TypeCastingExpression::Ptr >();
                        break;

                    case 137:  // Types
                    case 145:  // FunctionParameters
                    case 146:  // MaybeFunctionParameters
                        yylhs.value.build< Types::Ptr >();
                        break;

                    case 129:  // UndefinedLiteral
                        yylhs.value.build< UndefAtom::Ptr >();
                        break;

                    case 124:  // UniversalQuantifierExpression
                        yylhs.value.build< UniversalQuantifierExpression::Ptr >();
                        break;

                    case 111:  // UpdateRule
                    case 152:  // Initializer
                        yylhs.value.build< UpdateRule::Ptr >();
                        break;

                    case 130:  // BooleanLiteral
                    case 131:  // IntegerLiteral
                    case 132:  // RationalLiteral
                    case 133:  // DecimalLiteral
                    case 134:  // BinaryLiteral
                    case 135:  // StringLiteral
                        yylhs.value.build< ValueAtom::Ptr >();
                        break;

                    case 157:  // Variable
                    case 158:  // TypedVariable
                    case 159:  // AttributedVariable
                    case 160:  // TypedAttributedVariable
                        yylhs.value.build< VariableDefinition::Ptr >();
                        break;

                    case 138:  // Type
                        yylhs.value.build< libcasm_fe::Ast::Type::Ptr >();
                        break;

                    case 72:  // "binary"
                    case 73:  // "hexadecimal"
                    case 74:  // "integer"
                    case 75:  // "rational"
                    case 76:  // "decimal"
                    case 77:  // "string"
                    case 78:  // "identifier"
                        yylhs.value.build< std::string >();
                        break;

                    default:
                        break;
                }

                // Compute the default @$.
                {
                    slice< stack_symbol_type, stack_type > slice( yystack_, yylen );
                    YYLLOC_DEFAULT( yylhs.location, slice, yylen );
                }

                // Perform the reduction.
                YY_REDUCE_PRINT( yyn );
                try
                {
                    switch( yyn )
                    {
                        case 2:
#line 380 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            specification.setHeader(
                                yystack_[ 1 ].value.as< HeaderDefinition::Ptr >() );
                            specification.setDefinitions(
                                yystack_[ 0 ].value.as< Definitions::Ptr >() );
                        }
#line 1380 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 3:
#line 389 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definition =
                                Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
                            definition->setAttributes(
                                yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< HeaderDefinition::Ptr >() = definition;
                        }
#line 1390 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 4:
#line 395 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< HeaderDefinition::Ptr >() =
                                Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
                        }
#line 1398 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 5:
#line 403 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definitions = yystack_[ 1 ].value.as< Definitions::Ptr >();
                            definitions->add( yystack_[ 0 ].value.as< Definition::Ptr >() );
                            yylhs.value.as< Definitions::Ptr >() = definitions;
                        }
#line 1408 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 6:
#line 409 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definitions = Ast::make< Definitions >( yylhs.location );
                            definitions->add( yystack_[ 0 ].value.as< Definition::Ptr >() );
                            yylhs.value.as< Definitions::Ptr >() = definitions;
                        }
#line 1418 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 7:
#line 419 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definition = yystack_[ 0 ].value.as< Definition::Ptr >();
                            definition->setAttributes(
                                yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< Definition::Ptr >() = definition;
                        }
#line 1428 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 8:
#line 425 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< Definition::Ptr >();
                        }
#line 1436 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 9:
#line 429 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() = nullptr;
                        }
#line 1444 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 10:
#line 437 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< EnumerationDefinition::Ptr >();
                        }
#line 1452 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 11:
#line 441 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< DerivedDefinition::Ptr >();
                        }
#line 1460 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 12:
#line 445 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< RuleDefinition::Ptr >();
                        }
#line 1468 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 13:
#line 449 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< FunctionDefinition::Ptr >();
                        }
#line 1476 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 14:
#line 457 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< EnumerationDefinition::Ptr >() =
                                Ast::make< EnumerationDefinition >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 1 ].value.as< Enumerators::Ptr >() );
                        }
#line 1484 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 15:
#line 465 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< DerivedDefinition::Ptr >() =
                                Ast::make< DerivedDefinition >(
                                    yylhs.location,
                                    yystack_[ 5 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 4 ].value.as< NodeList< VariableDefinition >::Ptr >(),
                                    yystack_[ 2 ].value.as< libcasm_fe::Ast::Type::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 1492 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 16:
#line 473 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RuleDefinition::Ptr >() = Ast::make< RuleDefinition >(
                                yylhs.location,
                                yystack_[ 3 ].value.as< Identifier::Ptr >(),
                                yystack_[ 2 ].value.as< NodeList< VariableDefinition >::Ptr >(),
                                createVoidType( yylhs.location ),
                                wrapInBlockRule( yystack_[ 0 ].value.as< Rule::Ptr >() ) );
                        }
#line 1501 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 17:
#line 478 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RuleDefinition::Ptr >() = Ast::make< RuleDefinition >(
                                yylhs.location,
                                yystack_[ 5 ].value.as< Identifier::Ptr >(),
                                yystack_[ 4 ].value.as< NodeList< VariableDefinition >::Ptr >(),
                                yystack_[ 2 ].value.as< libcasm_fe::Ast::Type::Ptr >(),
                                wrapInBlockRule( yystack_[ 0 ].value.as< Rule::Ptr >() ) );
                        }
#line 1510 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 18:
#line 487 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto identifier = yystack_[ 6 ].value.as< Identifier::Ptr >();

                            auto function = Ast::make< FunctionDefinition >(
                                yylhs.location,
                                identifier,
                                yystack_[ 4 ].value.as< Types::Ptr >(),
                                yystack_[ 2 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            function->setDefaultValue(
                                yystack_[ 1 ].value.as< Expression::Ptr >() );

                            // apply the name of the function declaration to the initializer
                            // functions
                            auto initializers =
                                yystack_[ 0 ].value.as< NodeList< UpdateRule >::Ptr >();
                            for( auto& initializer : *initializers )
                            {
                                initializer->function()->setIdentifier( identifier );
                            }
                            function->setInitializers( initializers );

                            yylhs.value.as< FunctionDefinition::Ptr >() = function;
                        }
#line 1530 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 19:
#line 503 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< FunctionDefinition::Ptr >() =
                                yystack_[ 0 ]
                                    .value.as< FunctionDefinition::Ptr >();  // `init` special case
                        }
#line 1538 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 20:
#line 511 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto singleAgentIdentifier =
                                Ast::make< Identifier >( yylhs.location, "$" );
                            auto singleAgentArguments =
                                libcasm_fe::Ast::make< Expressions >( yylhs.location );
                            const auto singleAgent = libcasm_fe::Ast::make< DirectCallExpression >(
                                yylhs.location, singleAgentIdentifier, singleAgentArguments );
                            singleAgent->setTargetType( CallExpression::TargetType::CONSTANT );

                            auto programDefinition = createProgramFunction( yylhs.location );
                            auto programArguments =
                                libcasm_fe::Ast::make< Expressions >( yylhs.location );
                            programArguments->add( singleAgent );
                            const auto program = libcasm_fe::Ast::make< DirectCallExpression >(
                                yylhs.location, programDefinition->identifier(), programArguments );
                            program->setTargetType( CallExpression::TargetType::FUNCTION );

                            const auto ruleReference = Ast::make< ReferenceAtom >(
                                yylhs.location, yystack_[ 0 ].value.as< IdentifierPath::Ptr >() );

                            auto initializers =
                                Ast::make< NodeList< UpdateRule > >( yylhs.location );
                            initializers->add(
                                Ast::make< UpdateRule >( yylhs.location, program, ruleReference ) );
                            programDefinition->setInitializers( initializers );

                            yylhs.value.as< FunctionDefinition::Ptr >() = programDefinition;
                        }
#line 1565 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 21:
#line 534 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto programDefinition = createProgramFunction( yylhs.location );

                            // apply the name of the program declaration to the initializer
                            // functions
                            auto initializers =
                                yystack_[ 1 ].value.as< NodeList< UpdateRule >::Ptr >();
                            for( auto& initializer : *initializers )
                            {
                                initializer->function()->setIdentifier(
                                    programDefinition->identifier() );
                            }
                            programDefinition->setInitializers( initializers );

                            yylhs.value.as< FunctionDefinition::Ptr >() = programDefinition;
                        }
#line 1582 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 22:
#line 551 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< EnumeratorDefinition::Ptr >() =
                                Ast::make< EnumeratorDefinition >(
                                    yylhs.location, yystack_[ 0 ].value.as< Identifier::Ptr >() );
                        }
#line 1590 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 23:
#line 555 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto enumerator = Ast::make< EnumeratorDefinition >(
                                yylhs.location, yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            enumerator->setAttributes(
                                yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< EnumeratorDefinition::Ptr >() = enumerator;
                        }
#line 1600 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 24:
#line 561 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< EnumeratorDefinition::Ptr >() = nullptr;
                        }
#line 1608 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 25:
#line 569 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto enumerators = yystack_[ 2 ].value.as< Enumerators::Ptr >();
                            enumerators->add(
                                yystack_[ 0 ].value.as< EnumeratorDefinition::Ptr >() );
                            yylhs.value.as< Enumerators::Ptr >() = enumerators;
                        }
#line 1618 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 26:
#line 575 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto enumerators = Ast::make< Enumerators >( yylhs.location );
                            enumerators->add(
                                yystack_[ 0 ].value.as< EnumeratorDefinition::Ptr >() );
                            yylhs.value.as< Enumerators::Ptr >() = enumerators;
                        }
#line 1628 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 27:
#line 589 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< SkipRule::Ptr >();
                        }
#line 1636 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 28:
#line 593 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< ConditionalRule::Ptr >();
                        }
#line 1644 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 29:
#line 597 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< CaseRule::Ptr >();
                        }
#line 1652 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 30:
#line 601 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< LetRule::Ptr >();
                        }
#line 1660 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 31:
#line 605 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< ForallRule::Ptr >();
                        }
#line 1668 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 32:
#line 609 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< ChooseRule::Ptr >();
                        }
#line 1676 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 33:
#line 613 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< IterateRule::Ptr >();
                        }
#line 1684 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 34:
#line 617 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< BlockRule::Ptr >();
                        }
#line 1692 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 35:
#line 621 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< SequenceRule::Ptr >();
                        }
#line 1700 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 36:
#line 625 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< UpdateRule::Ptr >();
                        }
#line 1708 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 37:
#line 629 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< CallRule::Ptr >();
                        }
#line 1716 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 38:
#line 637 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto rules = yystack_[ 1 ].value.as< Rules::Ptr >();
                            rules->add( yystack_[ 0 ].value.as< Rule::Ptr >() );
                            yylhs.value.as< Rules::Ptr >() = rules;
                        }
#line 1726 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 39:
#line 643 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto rules = Ast::make< Rules >( yylhs.location );
                            rules->add( yystack_[ 0 ].value.as< Rule::Ptr >() );
                            yylhs.value.as< Rules::Ptr >() = rules;
                        }
#line 1736 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 40:
#line 653 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SkipRule::Ptr >() =
                                Ast::make< SkipRule >( yylhs.location );
                        }
#line 1744 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 41:
#line 661 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ConditionalRule::Ptr >() = Ast::make< ConditionalRule >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1752 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 42:
#line 665 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ConditionalRule::Ptr >() = Ast::make< ConditionalRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< Expression::Ptr >(),
                                yystack_[ 2 ].value.as< Rule::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1760 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 43:
#line 673 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CaseRule::Ptr >() = Ast::make< CaseRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< Expression::Ptr >(),
                                yystack_[ 1 ].value.as< Cases::Ptr >() );
                        }
#line 1768 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 44:
#line 677 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CaseRule::Ptr >() = nullptr;
                        }
#line 1776 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 45:
#line 685 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Case::Ptr >() = Ast::make< DefaultCase >(
                                yylhs.location, yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1784 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 46:
#line 689 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Case::Ptr >() = Ast::make< DefaultCase >(
                                yylhs.location, yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1792 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 47:
#line 693 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Case::Ptr >() = Ast::make< ExpressionCase >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1800 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 48:
#line 701 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto cases = yystack_[ 1 ].value.as< Cases::Ptr >();
                            cases->add( yystack_[ 0 ].value.as< Case::Ptr >() );
                            yylhs.value.as< Cases::Ptr >() = cases;
                        }
#line 1810 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 49:
#line 707 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto cases = Ast::make< Cases >( yylhs.location );
                            cases->add( yystack_[ 0 ].value.as< Case::Ptr >() );
                            yylhs.value.as< Cases::Ptr >() = cases;
                        }
#line 1820 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 50:
#line 717 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< LetRule::Ptr >() = Ast::make< LetRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1828 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 51:
#line 725 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ForallRule::Ptr >() = Ast::make< ForallRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1836 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 52:
#line 729 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ForallRule::Ptr >() = Ast::make< ForallRule >(
                                yylhs.location,
                                yystack_[ 6 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 4 ].value.as< Expression::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1844 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 53:
#line 737 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ChooseRule::Ptr >() = Ast::make< ChooseRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1852 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 54:
#line 745 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< IterateRule::Ptr >() = Ast::make< IterateRule >(
                                yylhs.location, yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1860 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 55:
#line 753 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = Ast::make< BlockRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1868 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 56:
#line 757 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = Ast::make< BlockRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1876 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 57:
#line 761 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 1885 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 58:
#line 766 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 1894 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 59:
#line 775 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = Ast::make< SequenceRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1902 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 60:
#line 779 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = Ast::make< SequenceRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1910 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 61:
#line 783 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 1919 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 62:
#line 788 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 1928 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 63:
#line 797 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto function =
                                yystack_[ 2 ].value.as< DirectCallExpression::Ptr >();
                            function->setTargetType( CallExpression::TargetType::FUNCTION );
                            yylhs.value.as< UpdateRule::Ptr >() = Ast::make< UpdateRule >(
                                yylhs.location,
                                function,
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 1938 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 64:
#line 807 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< CallExpression::Ptr >(),
                                CallRule::Type::RULE_CALL );
                        }
#line 1946 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 65:
#line 811 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< CallExpression::Ptr >(),
                                CallRule::Type::FUNCTION_CALL );
                        }
#line 1954 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 66:
#line 823 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto expressions = yystack_[ 2 ].value.as< Expressions::Ptr >();
                            expressions->add( yystack_[ 0 ].value.as< Expression::Ptr >() );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 1964 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 67:
#line 829 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = Ast::make< Expressions >( yylhs.location );
                            expressions->add( yystack_[ 0 ].value.as< Expression::Ptr >() );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 1974 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 68:
#line 839 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 1982 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 69:
#line 843 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< TypeCastingExpression::Ptr >();
                        }
#line 1990 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 70:
#line 847 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< CallExpression::Ptr >();
                        }
#line 1998 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 71:
#line 851 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< LetExpression::Ptr >();
                        }
#line 2006 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 72:
#line 855 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ConditionalExpression::Ptr >();
                        }
#line 2014 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 73:
#line 859 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ChooseExpression::Ptr >();
                        }
#line 2022 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 74:
#line 863 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< UniversalQuantifierExpression::Ptr >();
                        }
#line 2030 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 75:
#line 867 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ExistentialQuantifierExpression::Ptr >();
                        }
#line 2038 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 76:
#line 871 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ListExpression::Ptr >();
                        }
#line 2046 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 77:
#line 875 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< RangeExpression::Ptr >();
                        }
#line 2054 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 78:
#line 879 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 2062 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 79:
#line 891 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 1 ].value.as< Expression::Ptr >();
                        }
#line 2070 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 80:
#line 895 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = nullptr;
                        }
#line 2078 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 81:
#line 899 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 2086 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 82:
#line 903 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< UnaryExpression >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::INV_INSTRUCTION );
                        }
#line 2094 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 83:
#line 907 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::ADD_INSTRUCTION );
                        }
#line 2102 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 84:
#line 911 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::SUB_INSTRUCTION );
                        }
#line 2110 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 85:
#line 915 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::MUL_INSTRUCTION );
                        }
#line 2118 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 86:
#line 919 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::DIV_INSTRUCTION );
                        }
#line 2126 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 87:
#line 923 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::MOD_INSTRUCTION );
                        }
#line 2134 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 88:
#line 927 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::POW_INSTRUCTION );
                        }
#line 2142 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 89:
#line 931 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::NEQ_INSTRUCTION );
                        }
#line 2150 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 90:
#line 935 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::EQU_INSTRUCTION );
                        }
#line 2158 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 91:
#line 939 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::LTH_INSTRUCTION );
                        }
#line 2166 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 92:
#line 943 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::GTH_INSTRUCTION );
                        }
#line 2174 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 93:
#line 947 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::LEQ_INSTRUCTION );
                        }
#line 2182 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 94:
#line 951 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::GEQ_INSTRUCTION );
                        }
#line 2190 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 95:
#line 955 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::OR_INSTRUCTION );
                        }
#line 2198 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 96:
#line 959 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::XOR_INSTRUCTION );
                        }
#line 2206 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 97:
#line 963 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::AND_INSTRUCTION );
                        }
#line 2214 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 98:
#line 967 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::IMP_INSTRUCTION );
                        }
#line 2222 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 99:
#line 971 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::IMP_INSTRUCTION );
                        }
#line 2230 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 100:
#line 975 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< UnaryExpression >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::NOT_INSTRUCTION );
                        }
#line 2238 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 101:
#line 983 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< TypeCastingExpression::Ptr >() =
                                Ast::make< TypeCastingExpression >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 2246 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 102:
#line 991 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallExpression::Ptr >() =
                                yystack_[ 0 ].value.as< DirectCallExpression::Ptr >();
                        }
#line 2254 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 103:
#line 995 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallExpression::Ptr >() =
                                yystack_[ 0 ].value.as< IndirectCallExpression::Ptr >();
                        }
#line 2262 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 104:
#line 999 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallExpression::Ptr >() =
                                yystack_[ 0 ].value.as< MethodCallExpression::Ptr >();
                        }
#line 2270 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 105:
#line 1007 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto arguments = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< DirectCallExpression::Ptr >() =
                                Ast::make< DirectCallExpression >(
                                    yylhs.location,
                                    yystack_[ 0 ].value.as< Identifier::Ptr >(),
                                    arguments );
                        }
#line 2279 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 106:
#line 1012 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< DirectCallExpression::Ptr >() =
                                Ast::make< DirectCallExpression >(
                                    yylhs.location,
                                    yystack_[ 1 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< Expressions::Ptr >() );
                        }
#line 2287 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 107:
#line 1020 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< IndirectCallExpression::Ptr >() =
                                Ast::make< IndirectCallExpression >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expressions::Ptr >() );
                        }
#line 2295 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 108:
#line 1028 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto arguments = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< MethodCallExpression::Ptr >() =
                                Ast::make< MethodCallExpression >(
                                    yylhs.location,
                                    yystack_[ 3 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Identifier::Ptr >(),
                                    arguments );
                        }
#line 2304 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 109:
#line 1033 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< MethodCallExpression::Ptr >() =
                                Ast::make< MethodCallExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< Expression::Ptr >(),
                                    yystack_[ 1 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< Expressions::Ptr >() );
                        }
#line 2312 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 110:
#line 1037 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto arguments = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< MethodCallExpression::Ptr >() =
                                Ast::make< MethodCallExpression >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< CallExpression::Ptr >(),
                                    yystack_[ 0 ].value.as< Identifier::Ptr >(),
                                    arguments );
                        }
#line 2321 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 111:
#line 1042 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< MethodCallExpression::Ptr >() =
                                Ast::make< MethodCallExpression >(
                                    yylhs.location,
                                    yystack_[ 3 ].value.as< CallExpression::Ptr >(),
                                    yystack_[ 1 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< Expressions::Ptr >() );
                        }
#line 2329 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 112:
#line 1046 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto unresolvedNamespace =
                                Ast::make< UnresolvedNamespace >( yylhs.location );
                            const auto arguments = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< MethodCallExpression::Ptr >() =
                                Ast::make< MethodCallExpression >(
                                    yylhs.location,
                                    unresolvedNamespace,
                                    yystack_[ 0 ].value.as< Identifier::Ptr >(),
                                    arguments );
                        }
#line 2339 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 113:
#line 1056 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< LetExpression::Ptr >() = Ast::make< LetExpression >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2347 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 114:
#line 1064 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ConditionalExpression::Ptr >() =
                                Ast::make< ConditionalExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< Expression::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2355 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 115:
#line 1072 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ChooseExpression::Ptr >() =
                                Ast::make< ChooseExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2363 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 116:
#line 1080 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UniversalQuantifierExpression::Ptr >() =
                                Ast::make< UniversalQuantifierExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2371 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 117:
#line 1088 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ExistentialQuantifierExpression::Ptr >() =
                                Ast::make< ExistentialQuantifierExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2379 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 118:
#line 1096 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< ListExpression::Ptr >() =
                                Ast::make< ListExpression >( yylhs.location, expressions );
                        }
#line 2388 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 119:
#line 1101 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ListExpression::Ptr >() = Ast::make< ListExpression >(
                                yylhs.location, yystack_[ 1 ].value.as< Expressions::Ptr >() );
                        }
#line 2396 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 120:
#line 1105 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ListExpression::Ptr >() = nullptr;
                        }
#line 2404 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 121:
#line 1113 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RangeExpression::Ptr >() = Ast::make< RangeExpression >(
                                yylhs.location,
                                yystack_[ 3 ].value.as< Expression::Ptr >(),
                                yystack_[ 1 ].value.as< Expression::Ptr >() );
                        }
#line 2412 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 122:
#line 1125 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< UndefAtom::Ptr >();
                        }
#line 2420 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 123:
#line 1129 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueAtom::Ptr >();
                        }
#line 2428 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 124:
#line 1133 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueAtom::Ptr >();
                        }
#line 2436 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 125:
#line 1137 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueAtom::Ptr >();
                        }
#line 2444 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 126:
#line 1141 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueAtom::Ptr >();
                        }
#line 2452 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 127:
#line 1145 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueAtom::Ptr >();
                        }
#line 2460 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 128:
#line 1149 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueAtom::Ptr >();
                        }
#line 2468 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 129:
#line 1153 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ReferenceAtom::Ptr >();
                        }
#line 2476 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 130:
#line 1161 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UndefAtom::Ptr >() =
                                Ast::make< UndefAtom >( yylhs.location );
                        }
#line 2484 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 131:
#line 1169 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto value =
                                libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
                            yylhs.value.as< ValueAtom::Ptr >() =
                                Ast::make< ValueAtom >( yylhs.location, value );
                        }
#line 2493 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 132:
#line 1174 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto value =
                                libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
                            yylhs.value.as< ValueAtom::Ptr >() =
                                Ast::make< ValueAtom >( yylhs.location, value );
                        }
#line 2502 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 133:
#line 1183 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            try
                            {
                                const auto value =
                                    libstdhl::Memory::get< libcasm_ir::IntegerConstant >(
                                        yystack_[ 0 ].value.as< std::string >(),
                                        libstdhl::Type::DECIMAL );
                                yylhs.value.as< ValueAtom::Ptr >() =
                                    Ast::make< ValueAtom >( yylhs.location, value );
                            }
                            catch( const std::domain_error& e )
                            {
                                throw syntax_error( yylhs.location, e.what() );
                            }
                        }
#line 2518 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 134:
#line 1199 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            try
                            {
                                const auto value =
                                    libstdhl::Memory::get< libcasm_ir::RationalConstant >(
                                        yystack_[ 0 ].value.as< std::string >() );
                                yylhs.value.as< ValueAtom::Ptr >() =
                                    Ast::make< ValueAtom >( yylhs.location, value );
                            }
                            catch( const std::domain_error& e )
                            {
                                throw syntax_error( yylhs.location, e.what() );
                            }
                        }
#line 2534 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 135:
#line 1215 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            try
                            {
                                const auto value =
                                    libstdhl::Memory::get< libcasm_ir::DecimalConstant >(
                                        yystack_[ 0 ].value.as< std::string >() );
                                yylhs.value.as< ValueAtom::Ptr >() =
                                    Ast::make< ValueAtom >( yylhs.location, value );
                            }
                            catch( const std::domain_error& e )
                            {
                                throw syntax_error( yylhs.location, e.what() );
                            }
                        }
#line 2550 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 136:
#line 1231 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            try
                            {
                                const auto value =
                                    libstdhl::Memory::get< libcasm_ir::BinaryConstant >(
                                        yystack_[ 0 ].value.as< std::string >(),
                                        libstdhl::Type::BINARY );
                                yylhs.value.as< ValueAtom::Ptr >() =
                                    Ast::make< ValueAtom >( yylhs.location, value );
                            }
                            catch( const std::domain_error& e )
                            {
                                throw syntax_error( yylhs.location, e.what() );
                            }
                        }
#line 2566 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 137:
#line 1243 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            try
                            {
                                const auto value =
                                    libstdhl::Memory::get< libcasm_ir::BinaryConstant >(
                                        yystack_[ 0 ].value.as< std::string >(),
                                        libstdhl::Type::HEXADECIMAL );
                                yylhs.value.as< ValueAtom::Ptr >() =
                                    Ast::make< ValueAtom >( yylhs.location, value );
                            }
                            catch( const std::domain_error& e )
                            {
                                throw syntax_error( yylhs.location, e.what() );
                            }
                        }
#line 2582 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 138:
#line 1259 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            try
                            {
                                const auto value =
                                    libstdhl::Memory::get< libcasm_ir::StringConstant >(
                                        yystack_[ 0 ].value.as< std::string >() );
                                yylhs.value.as< ValueAtom::Ptr >() =
                                    Ast::make< ValueAtom >( yylhs.location, value );
                            }
                            catch( const std::domain_error& e )
                            {
                                throw syntax_error( yylhs.location, e.what() );
                            }
                        }
#line 2598 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 139:
#line 1275 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ReferenceAtom::Ptr >() = Ast::make< ReferenceAtom >(
                                yylhs.location, yystack_[ 0 ].value.as< IdentifierPath::Ptr >() );
                        }
#line 2606 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 140:
#line 1287 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = yystack_[ 2 ].value.as< Types::Ptr >();
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2616 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 141:
#line 1293 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = Ast::make< Types >( yylhs.location );
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2626 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 142:
#line 1303 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< BasicType::Ptr >();
                        }
#line 2634 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 143:
#line 1307 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< ComposedType::Ptr >();
                        }
#line 2642 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 144:
#line 1311 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< RelationType::Ptr >();
                        }
#line 2650 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 145:
#line 1315 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< FixedSizedType::Ptr >();
                        }
#line 2658 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 146:
#line 1323 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BasicType::Ptr >() = Ast::make< BasicType >(
                                yylhs.location, yystack_[ 0 ].value.as< IdentifierPath::Ptr >() );
                        }
#line 2666 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 147:
#line 1331 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ComposedType::Ptr >() = Ast::make< ComposedType >(
                                yylhs.location,
                                yystack_[ 3 ].value.as< IdentifierPath::Ptr >(),
                                yystack_[ 1 ].value.as< Types::Ptr >() );
                        }
#line 2674 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 148:
#line 1339 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RelationType::Ptr >() = Ast::make< RelationType >(
                                yylhs.location,
                                yystack_[ 5 ].value.as< IdentifierPath::Ptr >(),
                                yystack_[ 3 ].value.as< Types::Ptr >(),
                                yystack_[ 1 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 2682 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 149:
#line 1347 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< FixedSizedType::Ptr >() = Ast::make< FixedSizedType >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< IdentifierPath::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2690 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 150:
#line 1359 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expressions::Ptr >() =
                                yystack_[ 1 ].value.as< Expressions::Ptr >();
                        }
#line 2698 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 151:
#line 1363 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expressions::Ptr >() = nullptr;
                        }
#line 2706 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 152:
#line 1367 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 2715 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 153:
#line 1376 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = yystack_[ 3 ].value.as< Expressions::Ptr >();
                            expressions->add( yystack_[ 1 ].value.as< Expression::Ptr >() );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 2725 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 154:
#line 1390 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = yystack_[ 2 ].value.as< Types::Ptr >();
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2735 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 155:
#line 1396 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = Ast::make< Types >( yylhs.location );
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2745 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 156:
#line 1406 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Types::Ptr >() = yystack_[ 0 ].value.as< Types::Ptr >();
                        }
#line 2753 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 157:
#line 1410 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Types::Ptr >() = Ast::make< Types >( yylhs.location );
                        }
#line 2761 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 158:
#line 1418 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto parameters =
                                yystack_[ 2 ].value.as< NodeList< VariableDefinition >::Ptr >();
                            parameters->add( yystack_[ 0 ].value.as< VariableDefinition::Ptr >() );
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() = parameters;
                        }
#line 2771 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 159:
#line 1424 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto parameters =
                                Ast::make< NodeList< VariableDefinition > >( yylhs.location );
                            parameters->add( yystack_[ 0 ].value.as< VariableDefinition::Ptr >() );
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() = parameters;
                        }
#line 2781 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 160:
#line 1434 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() =
                                yystack_[ 1 ].value.as< NodeList< VariableDefinition >::Ptr >();
                        }
#line 2789 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 161:
#line 1438 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() = nullptr;
                        }
#line 2797 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 162:
#line 1442 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() =
                                Ast::make< NodeList< VariableDefinition > >( yylhs.location );
                        }
#line 2805 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 163:
#line 1454 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 1 ].value.as< Expression::Ptr >();
                        }
#line 2813 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 164:
#line 1458 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                Ast::make< UndefAtom >( yylhs.location );
                        }
#line 2821 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 165:
#line 1466 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() =
                                yystack_[ 1 ].value.as< NodeList< UpdateRule >::Ptr >();
                        }
#line 2829 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 166:
#line 1470 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() =
                                Ast::make< NodeList< UpdateRule > >( yylhs.location );
                        }
#line 2837 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 167:
#line 1478 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto initializers =
                                yystack_[ 2 ].value.as< NodeList< UpdateRule >::Ptr >();
                            initializers->add( yystack_[ 0 ].value.as< UpdateRule::Ptr >() );
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() = initializers;
                        }
#line 2847 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 168:
#line 1484 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto initializers =
                                Ast::make< NodeList< UpdateRule > >( yylhs.location );
                            initializers->add( yystack_[ 0 ].value.as< UpdateRule::Ptr >() );
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() = initializers;
                        }
#line 2857 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 169:
#line 1494 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            // the unknown function identifier will be replaced in
                            // FunctionDefinition
                            const auto arguments = Ast::make< Expressions >( yylhs.location );
                            const auto function = Ast::make< DirectCallExpression >(
                                yylhs.location, nullptr, arguments );
                            function->setTargetType( CallExpression::TargetType::FUNCTION );
                            yylhs.value.as< UpdateRule::Ptr >() = Ast::make< UpdateRule >(
                                yylhs.location,
                                function,
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2869 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 170:
#line 1502 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto arguments = Ast::make< Expressions >( yylhs.location );
                            arguments->add( yystack_[ 2 ].value.as< Expression::Ptr >() );

                            // the unknown function identifier will be replaced in
                            // FunctionDefinition
                            const auto function = Ast::make< DirectCallExpression >(
                                yylhs.location, nullptr, arguments );
                            function->setTargetType( CallExpression::TargetType::FUNCTION );
                            yylhs.value.as< UpdateRule::Ptr >() = Ast::make< UpdateRule >(
                                yylhs.location,
                                function,
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2883 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 171:
#line 1512 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            // the unknown function identifier will be replaced in
                            // FunctionDefinition
                            const auto function = Ast::make< DirectCallExpression >(
                                yylhs.location,
                                nullptr,
                                yystack_[ 2 ].value.as< Expressions::Ptr >() );
                            function->setTargetType( CallExpression::TargetType::FUNCTION );
                            yylhs.value.as< UpdateRule::Ptr >() = Ast::make< UpdateRule >(
                                yylhs.location,
                                function,
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2894 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 172:
#line 1523 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() =
                                yystack_[ 0 ].value.as< NodeList< UpdateRule >::Ptr >();
                        }
#line 2902 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 173:
#line 1527 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() =
                                Ast::make< NodeList< UpdateRule > >( yylhs.location );
                        }
#line 2910 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 174:
#line 1539 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Identifier::Ptr >() = Ast::make< Identifier >(
                                yylhs.location, yystack_[ 0 ].value.as< std::string >() );
                        }
#line 2918 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 175:
#line 1543 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Identifier::Ptr >() =
                                Ast::make< Identifier >( yylhs.location, "in" );
                        }
#line 2926 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 176:
#line 1551 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< IdentifierPath::Ptr >() = Ast::make< IdentifierPath >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< Identifiers::Ptr >(),
                                IdentifierPath::Type::ABSOLUTE );
                        }
#line 2934 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 177:
#line 1555 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto identifiers = Ast::make< Identifiers >( yylhs.location );
                            identifiers->add( yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            yylhs.value.as< IdentifierPath::Ptr >() = Ast::make< IdentifierPath >(
                                yylhs.location, identifiers, IdentifierPath::Type::RELATIVE );
                        }
#line 2944 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 178:
#line 1565 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto identifiers = yystack_[ 2 ].value.as< Identifiers::Ptr >();
                            identifiers->add( yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            yylhs.value.as< Identifiers::Ptr >() = identifiers;
                        }
#line 2954 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 179:
#line 1571 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto identifiers = Ast::make< Identifiers >( yylhs.location );
                            identifiers->add( yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            yylhs.value.as< Identifiers::Ptr >() = identifiers;
                        }
#line 2964 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 180:
#line 1585 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                        }
#line 2972 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 181:
#line 1589 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto unresolvedType =
                                Ast::make< UnresolvedType >( yylhs.location );
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                Ast::make< VariableDefinition >(
                                    yylhs.location,
                                    yystack_[ 0 ].value.as< Identifier::Ptr >(),
                                    unresolvedType );
                        }
#line 2981 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 182:
#line 1598 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                Ast::make< VariableDefinition >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 2989 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 183:
#line 1606 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto variable = yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                            variable->setAttributes( yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< VariableDefinition::Ptr >() = variable;
                        }
#line 2999 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 184:
#line 1612 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                        }
#line 3007 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 185:
#line 1620 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto variable = yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                            variable->setAttributes( yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< VariableDefinition::Ptr >() = variable;
                        }
#line 3017 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 186:
#line 1626 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                        }
#line 3025 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 187:
#line 1638 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto attributes = yystack_[ 2 ].value.as< Attributes::Ptr >();
                            attributes->add( yystack_[ 0 ].value.as< Attribute::Ptr >() );
                            yylhs.value.as< Attributes::Ptr >() = attributes;
                        }
#line 3035 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 188:
#line 1644 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto attributes = Ast::make< Attributes >( yylhs.location );
                            attributes->add( yystack_[ 0 ].value.as< Attribute::Ptr >() );
                            yylhs.value.as< Attributes::Ptr >() = attributes;
                        }
#line 3045 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 189:
#line 1653 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Attribute::Ptr >() =
                                yystack_[ 0 ].value.as< BasicAttribute::Ptr >();
                        }
#line 3053 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 190:
#line 1657 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Attribute::Ptr >() =
                                yystack_[ 0 ].value.as< ExpressionAttribute::Ptr >();
                        }
#line 3061 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 191:
#line 1665 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BasicAttribute::Ptr >() = Ast::make< BasicAttribute >(
                                yylhs.location, yystack_[ 0 ].value.as< Identifier::Ptr >() );
                        }
#line 3069 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 192:
#line 1673 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ExpressionAttribute::Ptr >() =
                                Ast::make< ExpressionAttribute >(
                                    yylhs.location,
                                    yystack_[ 1 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 3077 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

#line 3081 "GrammarParser.cpp"  // lalr1.cc:859
                        default:
                            break;
                    }
                }
                catch( const syntax_error& yyexc )
                {
                    error( yyexc );
                    YYERROR;
                }
                YY_SYMBOL_PRINT( "-> $$ =", yylhs );
                yypop_( yylen );
                yylen = 0;
                YY_STACK_PRINT();

                // Shift the result of the reduction.
                yypush_( YY_NULLPTR, yylhs );
            }
            goto yynewstate;

        /*--------------------------------------.
        | yyerrlab -- here on detecting error.  |
        `--------------------------------------*/
        yyerrlab:
            // If not already recovering from an error, report this error.
            if( !yyerrstatus_ )
            {
                ++yynerrs_;
                error( yyla.location, yysyntax_error_( yystack_[ 0 ].state, yyla ) );
            }

            yyerror_range[ 1 ].location = yyla.location;
            if( yyerrstatus_ == 3 )
            {
                /* If just tried and failed to reuse lookahead token after an
                   error, discard it.  */

                // Return failure if at end of input.
                if( yyla.type_get() == yyeof_ )
                    YYABORT;
                else if( !yyla.empty() )
                {
                    yy_destroy_( "Error: discarding", yyla );
                    yyla.clear();
                }
            }

            // Else will try to reuse lookahead token after shifting the error token.
            goto yyerrlab1;

        /*---------------------------------------------------.
        | yyerrorlab -- error raised explicitly by YYERROR.  |
        `---------------------------------------------------*/
        yyerrorlab:

            /* Pacify compilers like GCC when the user code never invokes
               YYERROR and the label yyerrorlab therefore never appears in user
               code.  */
            if( false )
                goto yyerrorlab;
            yyerror_range[ 1 ].location = yystack_[ yylen - 1 ].location;
            /* Do not reclaim the symbols of the rule whose action triggered
               this YYERROR.  */
            yypop_( yylen );
            yylen = 0;
            goto yyerrlab1;

        /*-------------------------------------------------------------.
        | yyerrlab1 -- common code for both syntax error and YYERROR.  |
        `-------------------------------------------------------------*/
        yyerrlab1:
            yyerrstatus_ = 3;  // Each real token shifted decrements this.
            {
                stack_symbol_type error_token;
                for( ;; )
                {
                    yyn = yypact_[ yystack_[ 0 ].state ];
                    if( !yy_pact_value_is_default_( yyn ) )
                    {
                        yyn += yyterror_;
                        if( 0 <= yyn && yyn <= yylast_ && yycheck_[ yyn ] == yyterror_ )
                        {
                            yyn = yytable_[ yyn ];
                            if( 0 < yyn )
                                break;
                        }
                    }

                    // Pop the current state because it cannot handle the error token.
                    if( yystack_.size() == 1 )
                        YYABORT;

                    yyerror_range[ 1 ].location = yystack_[ 0 ].location;
                    yy_destroy_( "Error: popping", yystack_[ 0 ] );
                    yypop_();
                    YY_STACK_PRINT();
                }

                yyerror_range[ 2 ].location = yyla.location;
                YYLLOC_DEFAULT( error_token.location, yyerror_range, 2 );

                // Shift the error token.
                error_token.state = yyn;
                yypush_( "Shifting", error_token );
            }
            goto yynewstate;

            // Accept.
        yyacceptlab:
            yyresult = 0;
            goto yyreturn;

            // Abort.
        yyabortlab:
            yyresult = 1;
            goto yyreturn;

        yyreturn:
            if( !yyla.empty() )
                yy_destroy_( "Cleanup: discarding lookahead", yyla );

            /* Do not reclaim the symbols of the rule whose action triggered
               this YYABORT or YYACCEPT.  */
            yypop_( yylen );
            while( 1 < yystack_.size() )
            {
                yy_destroy_( "Cleanup: popping", yystack_[ 0 ] );
                yypop_();
            }

            return yyresult;
        }
        catch( ... )
        {
            YYCDEBUG << "Exception caught: cleaning lookahead and stack" << std::endl;
            // Do not try to display the values of the reclaimed symbols,
            // as their printer might throw an exception.
            if( !yyla.empty() )
                yy_destroy_( YY_NULLPTR, yyla );

            while( 1 < yystack_.size() )
            {
                yy_destroy_( YY_NULLPTR, yystack_[ 0 ] );
                yypop_();
            }
            throw;
        }
    }

    void Parser::error( const syntax_error& yyexc )
    {
        error( yyexc.location, yyexc.what() );
    }

    // Generate an error message.
    std::string Parser::yysyntax_error_( state_type yystate, const symbol_type& yyla ) const
    {
        // Number of reported tokens (one for the "unexpected", one per
        // "expected").
        size_t yycount = 0;
        // Its maximum.
        enum
        {
            YYERROR_VERBOSE_ARGS_MAXIMUM = 5
        };
        // Arguments of yyformat.
        char const* yyarg[ YYERROR_VERBOSE_ARGS_MAXIMUM ];

        /* There are many possibilities here to consider:
           - If this state is a consistent state with a default action, then
             the only way this function was invoked is if the default action
             is an error action.  In that case, don't check for expected
             tokens because there are none.
           - The only way there can be no lookahead present (in yyla) is
             if this state is a consistent state with a default action.
             Thus, detecting the absence of a lookahead is sufficient to
             determine that there is no unexpected or expected token to
             report.  In that case, just report a simple "syntax error".
           - Don't assume there isn't a lookahead just because this state is
             a consistent state with a default action.  There might have
             been a previous inconsistent state, consistent state with a
             non-default action, or user semantic action that manipulated
             yyla.  (However, yyla is currently not documented for users.)
           - Of course, the expected token list depends on states to have
             correct lookahead information, and it depends on the parser not
             to perform extra reductions after fetching a lookahead from the
             scanner and before detecting a syntax error.  Thus, state
             merging (from LALR or IELR) and default reductions corrupt the
             expected token list.  However, the list is correct for
             canonical LR with one exception: it will still contain any
             token that will not be accepted due to an error action in a
             later state.
        */
        if( !yyla.empty() )
        {
            int yytoken = yyla.type_get();
            yyarg[ yycount++ ] = yytname_[ yytoken ];
            int yyn = yypact_[ yystate ];
            if( !yy_pact_value_is_default_( yyn ) )
            {
                /* Start YYX at -YYN if negative to avoid negative indexes in
                   YYCHECK.  In other words, skip the first -YYN actions for
                   this state because they are default actions.  */
                int yyxbegin = yyn < 0 ? -yyn : 0;
                // Stay within bounds of both yycheck and yytname.
                int yychecklim = yylast_ - yyn + 1;
                int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
                for( int yyx = yyxbegin; yyx < yyxend; ++yyx )
                    if( yycheck_[ yyx + yyn ] == yyx && yyx != yyterror_ &&
                        !yy_table_value_is_error_( yytable_[ yyx + yyn ] ) )
                    {
                        if( yycount == YYERROR_VERBOSE_ARGS_MAXIMUM )
                        {
                            yycount = 1;
                            break;
                        }
                        else
                            yyarg[ yycount++ ] = yytname_[ yyx ];
                    }
            }
        }

        char const* yyformat = YY_NULLPTR;
        switch( yycount )
        {
#define YYCASE_( N, S ) \
    case N:             \
        yyformat = S;   \
        break
            YYCASE_( 0, YY_( "syntax error" ) );
            YYCASE_( 1, YY_( "syntax error, unexpected %s" ) );
            YYCASE_( 2, YY_( "syntax error, unexpected %s, expecting %s" ) );
            YYCASE_( 3, YY_( "syntax error, unexpected %s, expecting %s or %s" ) );
            YYCASE_( 4, YY_( "syntax error, unexpected %s, expecting %s or %s or %s" ) );
            YYCASE_( 5, YY_( "syntax error, unexpected %s, expecting %s or %s or %s or %s" ) );
#undef YYCASE_
        }

        std::string yyres;
        // Argument number.
        size_t yyi = 0;
        for( char const* yyp = yyformat; *yyp; ++yyp )
            if( yyp[ 0 ] == '%' && yyp[ 1 ] == 's' && yyi < yycount )
            {
                yyres += yytnamerr_( yyarg[ yyi++ ] );
                ++yyp;
            }
            else
                yyres += *yyp;
        return yyres;
    }

    const short int Parser::yypact_ninf_ = -201;

    const short int Parser::yytable_ninf_ = -156;

    const short int Parser::yypact_[] = {
        0,    -201, -16,  39,   267,  -201, -201, 1128, -13,  -201, -201, -201, -201, -201, -4,
        -16,  -16,  -16,  -16,  -16,  163,  -201, -201, -201, -201, -201, -201, -201, -1,   -1,
        -1,   1128, -1,   -201, -201, -201, 1128, 1128, 1128, 496,  559,  1,    -16,  -201, -201,
        -201, -201, -201, -201, 1940, -201, -201, -23,  -201, -201, -201, -201, -201, -201, -201,
        -201, -201, -201, -201, -201, -201, -201, -201, -201, -201, -201, -201, 15,   62,   -16,
        1191, -16,  -201, -201, 13,   29,   56,   29,   36,   3,    -201, -16,  71,   -201, -201,
        79,   107,  112,  1417, 113,  -201, -201, -201, 88,   1128, 1634, 84,   -201, 6,    1668,
        -201, -201, 1,    1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128, 1128,
        1128, 1128, 1128, 1128, 1128, -16,  622,  -201, -201, -201, 496,  1702, 70,   90,   -201,
        96,   -201, -16,  5,    92,   109,  -36,  1,    168,  43,   1,    1128, 1128, 1128, 1128,
        1128, -201, 1736, 98,   -201, -201, 1128, 1128, -201, -201, -201, -201, -201, -18,  1980,
        1974, 247,  925,  126,  126,  1448, 95,   95,   105,  105,  105,  -201, 925,  1448, 95,
        95,   15,   121,  -201, -37,  1940, 124,  1634, 1128, 1128, 1191, -201, -201, 134,  -16,
        -31,  71,   -201, -201, 1,    10,   990,  1,    -201, 131,  127,  -201, -16,  -201, 364,
        1561, 1299, 1493, 1600, 15,   -16,  1940, 1770, 1,    1128, -201, -201, -201, 1128, 1940,
        1940, -201, -201, 44,   -201, 9,    149,  -201, -16,  -201, -29,  -201, 690,  710,  -201,
        -1,   -1,   -1,   990,  -2,   1128, 1128, 1065, 774,  794,  -201, -201, -201, -201, -201,
        -201, -201, -201, -201, -201, -201, -201, -23,  129,  150,  1,    1,    -201, 1128, 1128,
        1128, 1128, 1128, -201, 15,   -201, -35,  61,   132,  -201, 1804, -16,  -201, 1128, 73,
        -201, 10,   188,  -201, 843,  187,  860,  159,  186,  189,  -201, -23,  1455, 1527, 1838,
        155,  909,  136,  926,  1128, 990,  -201, 195,  1940, 1940, 1940, 1940, 1940, -201, 1,
        -201, 1,    -201, -201, 1940, -16,  -201, -201, -201, -201, -201, -201, 1128, 1128, 1128,
        990,  167,  98,   -201, -201, -201, -201, 1940, -201, 169,  209,  -201, 170,  -201, 1219,
        1259, 1339, 198,  433,  1128, 176,  -201, -201, 990,  990,  1128, 990,  990,  178,  175,
        181,  -201, 1002, 1872, 1906, 1191, -201, -201, 1379, -201, -201, -201, 990,  990,  -201,
        -201, 990,  -201, 179,  990,  -201, -201, -201, -201, -201
    };

    const unsigned char Parser::yydefact_[] = {
        0,   4,   0,   0,   0,   175, 174, 191, 0,   188, 189, 190, 1,   9,   0,   0,   0,   0,
        0,   0,   0,   6,   8,   10,  11,  12,  13,  19,  0,   0,   0,   0,   0,   130, 132, 131,
        0,   0,   0,   0,   0,   0,   0,   136, 137, 133, 134, 135, 138, 192, 68,  69,  70,  102,
        103, 104, 71,  72,  73,  74,  75,  76,  77,  78,  122, 123, 124, 125, 126, 127, 128, 129,
        105, 0,   0,   173, 0,   179, 20,  176, 162, 0,   162, 0,   0,   5,   0,   181, 184, 180,
        0,   0,   0,   0,   0,   100, 81,  82,  0,   0,   0,   0,   118, 0,   67,  139, 112, 0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   106, 3,   187, 0,   169, 0,   172, 168, 0,   177, 0,   0,   0,   0,   0,   157, 0,
        0,   0,   0,   0,   0,   0,   0,   80,  0,   79,  120, 119, 0,   0,   101, 142, 143, 144,
        145, 146, 97,  95,  96,  99,  83,  84,  90,  91,  92,  85,  86,  87,  88,  98,  89,  93,
        94,  110, 0,   152, 0,   67,  0,   67,  0,   0,   0,   21,  178, 0,   0,   0,   0,   186,
        159, 0,   0,   0,   0,   155, 156, 0,   7,   0,   182, 0,   0,   0,   0,   0,   0,   0,
        66,  0,   157, 0,   111, 151, 150, 0,   170, 171, 167, 161, 0,   160, 0,   0,   24,  0,
        26,  0,   22,  0,   0,   40,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   16,  27,
        28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  65,  102, 0,   0,   0,   183, 0,   0,
        0,   0,   0,   107, 108, 121, 0,   141, 0,   149, 66,  0,   158, 0,   0,   14,  0,   0,
        39,  0,   0,   0,   0,   0,   0,   54,  64,  0,   0,   0,   0,   0,   0,   0,   0,   0,
        154, 164, 113, 116, 115, 114, 117, 109, 0,   147, 0,   153, 185, 15,  0,   25,  62,  60,
        38,  58,  56,  0,   0,   0,   0,   0,   0,   57,  55,  61,  59,  63,  17,  0,   166, 140,
        0,   23,  0,   0,   0,   41,  0,   0,   0,   18,  148, 0,   0,   0,   0,   0,   0,   0,
        0,   49,  0,   0,   0,   173, 50,  51,  0,   53,  42,  44,  0,   0,   43,  48,  0,   163,
        0,   0,   45,  46,  47,  165, 52
    };

    const short int Parser::yypgoto_[] = {
        -201, -201, -201, -201, 212,  91,   -201, -201, -201, -201, -201, -51,  -201, -143,
        -200, -201, -201, -201, -125, -201, -201, -201, -201, -201, -201, -201, -201, -201,
        -41,  -7,   -201, -201, 86,   7,    -201, -201, -201, -201, -201, -201, -201, -201,
        -201, -201, -201, -201, -201, -201, -201, -201, -201, -201, -201, -67,  -201, -201,
        -201, -201, -179, -201, -201, 23,   -201, 160,  -201, -201, -201, 53,   -117, 52,
        22,   -201, 46,   -134, -20,  27,   -14,  184,  -201, -201
    };

    const short int Parser::yydefgoto_[] = {
        -1,  3,   4,   20,  21,  22,  23,  24,  25,  26,  27,  234, 235, 288, 289, 251,
        252, 253, 361, 362, 254, 255, 256, 257, 258, 259, 260, 261, 103, 131, 50,  51,
        52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  65,  66,  67,
        68,  69,  70,  71,  276, 158, 159, 160, 161, 162, 127, 132, 204, 205, 195, 139,
        340, 351, 133, 134, 135, 72,  163, 79,  88,  89,  90,  198, 8,   9,   10,  11
    };

    const short int Parser::yytable_[] = {
        49,  5,   220, 1,   197, 84,  193, 201, 222, 91,  92,   232, 94,  5,   229, 5,   5,   156,
        5,   314, 285, 315, 5,   230, 93,  286, 5,   5,   202,  95,  96,  97,  100, 104, 73,  273,
        78,  218, 291, 12,  125, 74,  247, 219, 75,  86,  2,    76,  301, 303, 143, 194, 76,  155,
        7,   194, 233, 74,  250, 126, 156, 42,  6,   105, 137,  128, 77,  80,  81,  82,  83,  7,
        144, 138, 6,   203, 6,   6,   208, 6,   87,  87,  87,   6,   87,  184, 142, 6,   6,   186,
        207, 281, 152, 77,  106, 313, 197, 74,  74,  140, 295,  164, 165, 166, 167, 168, 169, 170,
        171, 172, 173, 174, 175, 176, 177, 178, 179, 180, -155, 185, 320, 145, 146, 187, 147, -155,
        7,   74,  136, 148, 150, 154, 231, 151, 189, 264, 112,  113, 7,   209, 210, 211, 212, 213,
        190, 191, 324, 318, 324, 216, 217, 277, 117, 118, 119,  120, 199, 200, 324, 77,  324, 215,
        338, -2,  13,  120, 221, 14,  15,  16,  17,  18,  14,   15,  16,  17,  18,  181, 223, 227,
        228, 224, 225, 117, 118, 119, 120, 347, 265, 192, 196,  266, 283, 305, 77,  304, 316, 77,
        306, 307, 322, 325, 327, 328, 333, 339, 329, 335, 263,  19,  366, 367, 279, 369, 370, 348,
        280, 349, 350, 284, 292, 293, 294, 357, 365, 372, 352,  371, 383, 380, 381, 373, 85,  382,
        206, 321, 384, 375, 297, 298, 299, 278, 141, 226, 263,  263, 7,   341, 378, 342, 263, 77,
        236, 267, 77,  263, 263, 282, 129, 87,  0,   308, 309,  310, 311, 312, 0,   274, 13,  0,
        77,  14,  15,  16,  17,  18,  319, 0,   0,   0,   0,    0,   196, 108, 0,   7,   0,   262,
        112, 113, 114, 0,   87,  87,  87,  0,   263, 337, 263,  0,   0,   0,   115, 116, 117, 118,
        119, 120, 263, 0,   263, 0,   263, 19,  122, 123, 124,  77,  77,  0,   344, 345, 346, 262,
        262, 0,   0,   0,   0,   262, 296, 0,   0,   196, 262,  262, 0,   263, 236, 0,   0,   363,
        364, 0,   0,   0,   0,   0,   368, 0,   0,   0,   0,    0,   0,   363, 0,   0,   0,   0,
        263, 263, 0,   263, 263, 0,   77,  0,   77,  0,   0,    0,   343, 0,   0,   262, 0,   262,
        0,   263, 263, 268, 0,   263, 0,   0,   263, 262, 0,    262, 0,   262, 0,   0,   0,   0,
        107, 0,   0,   0,   108, 109, 110, 111, 0,   112, 113,  114, 0,   0,   0,   0,   0,   0,
        0,   0,   262, 0,   0,   115, 116, 117, 118, 119, 120,  0,   0,   0,   0,   121, 0,   122,
        123, 124, 358, 0,   0,   0,   0,   262, 262, 0,   262,  262, 0,   0,   0,   0,   0,   28,
        5,   29,  30,  0,   0,   0,   31,  0,   262, 262, 0,    359, 262, 32,  0,   262, 33,  34,
        35,  0,   0,   0,   0,   36,  37,  38,  0,   39,  0,    40,  0,   0,   0,   0,   0,   360,
        41,  0,   0,   0,   0,   0,   0,   0,   0,   0,   42,   98,  0,   0,   0,   0,   0,   0,
        0,   43,  44,  45,  46,  47,  48,  6,   28,  5,   29,   30,  0,   0,   0,   31,  0,   0,
        0,   0,   0,   0,   32,  0,   0,   33,  34,  35,  0,    0,   0,   0,   36,  37,  38,  0,
        39,  0,   40,  0,   0,   0,   0,   0,   0,   41,  0,    0,   0,   99,  0,   0,   0,   0,
        0,   42,  101, 0,   0,   0,   0,   0,   0,   0,   43,   44,  45,  46,  47,  48,  6,   28,
        5,   29,  30,  0,   0,   0,   31,  0,   0,   0,   0,    0,   0,   32,  0,   0,   33,  34,
        35,  0,   0,   0,   0,   36,  37,  38,  0,   39,  0,    40,  102, 0,   0,   0,   0,   0,
        41,  0,   0,   0,   0,   0,   0,   0,   0,   0,   42,   182, 0,   0,   0,   0,   0,   0,
        0,   43,  44,  45,  46,  47,  48,  6,   28,  5,   29,   30,  0,   0,   0,   31,  0,   0,
        0,   0,   0,   0,   32,  0,   0,   33,  34,  35,  0,    0,   0,   0,   36,  37,  38,  0,
        39,  183, 40,  0,   0,   0,   0,   0,   0,   41,  0,    0,   0,   0,   0,   0,   0,   0,
        0,   42,  0,   0,   0,   0,   0,   287, 0,   0,   43,   44,  45,  46,  47,  48,  6,   237,
        0,   238, 0,   239, 240, 5,   241, 242, 243, 290, 244,  245, 0,   0,   246, 0,   0,   0,
        0,   237, 0,   238, 0,   239, 240, 5,   241, 242, 243,  0,   244, 245, 247, 0,   246, 0,
        248, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   42,  247, 0,
        0,   0,   248, 0,   249, 0,   0,   0,   0,   0,   0,    0,   6,   0,   0,   0,   0,   42,
        0,   300, 0,   0,   0,   0,   249, 0,   0,   0,   0,    237, 0,   238, 6,   239, 240, 5,
        241, 242, 243, 302, 244, 245, 0,   0,   246, 0,   0,    0,   0,   237, 0,   238, 0,   239,
        240, 5,   241, 242, 243, 0,   244, 245, 247, 0,   246,  0,   248, 0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   42,  247,  0,   0,   0,   248, 0,   249, 0,
        0,   0,   0,   0,   0,   0,   6,   0,   237, 323, 238,  42,  239, 240, 5,   241, 242, 243,
        249, 244, 245, 0,   0,   246, 0,   237, 6,   238, 326,  239, 240, 5,   241, 242, 243, 0,
        244, 245, 0,   0,   246, 247, 0,   0,   0,   248, 0,    0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   247, 0,   42,  0,   248, 0,   0,    0,   0,   249, 0,   0,   0,   0,
        0,   0,   237, 6,   238, 42,  239, 240, 5,   241, 242,  243, 249, 244, 245, 0,   0,   246,
        0,   237, 6,   238, 0,   239, 240, 5,   241, 242, 243,  0,   244, 245, 0,   0,   246, 247,
        0,   0,   0,   248, 334, 0,   0,   108, 109, 110, 0,    0,   112, 113, 114, 0,   247, 0,
        42,  0,   248, 0,   0,   0,   0,   249, 115, 116, 117,  118, 119, 120, 0,   6,   0,   42,
        0,   0,   122, 123, 124, 0,   249, 336, 0,   0,   0,    237, 0,   238, 6,   239, 240, 5,
        241, 242, 243, 0,   244, 245, 0,   0,   246, 0,   28,   5,   29,  30,  0,   0,   0,   31,
        0,   0,   0,   0,   359, 0,   32,  0,   247, 33,  34,   35,  248, 0,   0,   0,   36,  37,
        38,  0,   39,  0,   40,  0,   0,   374, 0,   42,  360,  41,  0,   0,   0,   0,   249, 0,
        0,   0,   0,   42,  0,   0,   6,   0,   0,   0,   0,    0,   43,  44,  45,  46,  47,  48,
        6,   28,  5,   29,  30,  0,   0,   0,   31,  0,   0,    0,   0,   0,   0,   32,  0,   0,
        33,  34,  35,  0,   0,   0,   0,   36,  37,  38,  0,    39,  0,   40,  0,   0,   0,   0,
        0,   0,   41,  0,   0,   0,   99,  0,   0,   0,   0,    0,   42,  0,   0,   0,   0,   0,
        0,   0,   0,   43,  44,  45,  46,  47,  48,  6,   28,   5,   29,  30,  0,   0,   0,   31,
        0,   0,   0,   0,   0,   0,   32,  0,   0,   33,  34,   35,  0,   0,   0,   0,   36,  37,
        38,  0,   39,  0,   40,  0,   0,   0,   0,   0,   0,    41,  0,   0,   0,   0,   0,   0,
        0,   0,   0,   42,  0,   0,   0,   0,   0,   0,   0,    0,   43,  44,  45,  46,  47,  48,
        6,   28,  5,   29,  30,  0,   0,   0,   31,  0,   0,    0,   0,   0,   0,   32,  0,   0,
        33,  34,  35,  0,   0,   0,   0,   36,  37,  38,  0,    130, 353, 40,  0,   0,   0,   0,
        0,   0,   41,  0,   0,   0,   0,   0,   0,   107, 0,    0,   42,  108, 109, 110, 111, 0,
        112, 113, 114, 43,  44,  45,  46,  47,  48,  6,   0,    0,   0,   0,   115, 116, 117, 118,
        119, 120, 354, 0,   0,   0,   121, 0,   122, 123, 124,  0,   355, 107, 0,   0,   0,   108,
        109, 110, 111, 0,   112, 113, 114, 0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0,
        115, 116, 117, 118, 119, 120, 270, 0,   0,   0,   121,  0,   122, 123, 124, 0,   0,   107,
        0,   0,   0,   108, 109, 110, 111, 0,   112, 113, 114,  0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   115, 116, 117, 118, 119, 120, 356,  0,   0,   0,   121, 0,   122, 123,
        124, 0,   0,   107, 0,   0,   0,   108, 109, 110, 111,  0,   112, 113, 114, 0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   115, 116, 117,  118, 119, 120, 379, 0,   0,   0,
        121, 0,   122, 123, 124, 0,   0,   107, 0,   0,   0,    108, 109, 110, 111, 0,   112, 113,
        114, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   115, 116, 117, 118, 119, 120,
        0,   149, 0,   0,   121, 0,   122, 123, 124, 107, 0,    0,   0,   108, 109, 110, 111, 0,
        112, 113, 114, 0,   0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   115, 116, 117, 118,
        119, 120, 0,   330, 0,   0,   121, 0,   122, 123, 124,  107, 0,   112, 113, 108, 109, 110,
        111, 0,   112, 113, 114, 0,   0,   0,   0,   115, 116,  117, 118, 119, 120, 0,   115, 116,
        117, 118, 119, 120, 123, 124, 271, 0,   121, 0,   122,  123, 124, 107, 0,   0,   0,   108,
        109, 110, 111, 0,   112, 113, 114, 0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0,
        115, 116, 117, 118, 119, 120, 331, 0,   0,   0,   121,  107, 122, 123, 124, 108, 109, 110,
        111, 0,   112, 113, 114, 0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   115, 116,
        117, 118, 119, 120, 0,   0,   269, 0,   121, 107, 122,  123, 124, 108, 109, 110, 111, 0,
        112, 113, 114, 0,   0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   115, 116, 117, 118,
        119, 120, 0,   0,   0,   0,   121, 0,   122, 123, 124,  272, 107, 0,   0,   0,   108, 109,
        110, 111, 0,   112, 113, 114, 0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   115,
        116, 117, 118, 119, 120, 0,   0,   0,   0,   121, 107,  122, 123, 124, 108, 109, 110, 111,
        0,   112, 113, 114, 0,   153, 0,   0,   0,   0,   0,    0,   0,   0,   0,   115, 116, 117,
        118, 119, 120, 0,   0,   0,   0,   121, 107, 122, 123,  124, 108, 109, 110, 111, 0,   112,
        113, 114, 0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,   115, 116, 117, 118, 119,
        120, 0,   157, 0,   0,   121, 107, 122, 123, 124, 108,  109, 110, 111, 0,   112, 113, 114,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    115, 116, 117, 118, 119, 120, 0,
        0,   0,   188, 121, 107, 122, 123, 124, 108, 109, 110,  111, 0,   112, 113, 114, 0,   214,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   115, 116,  117, 118, 119, 120, 0,   0,   0,
        0,   121, 107, 122, 123, 124, 108, 109, 110, 111, 0,    112, 113, 114, 0,   0,   0,   275,
        0,   0,   0,   0,   0,   0,   0,   115, 116, 117, 118,  119, 120, 0,   0,   0,   0,   121,
        107, 122, 123, 124, 108, 109, 110, 111, 0,   112, 113,  114, 0,   317, 0,   0,   0,   0,
        0,   0,   0,   0,   0,   115, 116, 117, 118, 119, 120,  0,   0,   0,   0,   121, 107, 122,
        123, 124, 108, 109, 110, 111, 0,   112, 113, 114, 0,    332, 0,   0,   0,   0,   0,   0,
        0,   0,   0,   115, 116, 117, 118, 119, 120, 0,   0,    0,   0,   121, 107, 122, 123, 124,
        108, 109, 110, 111, 0,   112, 113, 114, 0,   0,   0,    0,   0,   0,   376, 0,   0,   0,
        0,   115, 116, 117, 118, 119, 120, 0,   0,   0,   0,    121, 107, 122, 123, 124, 108, 109,
        110, 111, 0,   112, 113, 114, 0,   0,   0,   0,   0,    377, 0,   0,   0,   0,   0,   115,
        116, 117, 118, 119, 120, 0,   0,   0,   0,   121, 107,  122, 123, 124, 108, 109, 110, 111,
        0,   112, 113, 114, 0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   115, 116, 117,
        118, 119, 120, 0,   0,   0,   0,   121, 0,   122, 123,  124, 108, 0,   110, 0,   0,   112,
        113, 114, 0,   0,   0,   112, 113, 114, 0,   0,   0,    0,   0,   115, 116, 117, 118, 119,
        120, 115, 116, 117, 118, 119, 120, 122, 123, 124, 0,    0,   0,   122, 123, 124
    };

    const short int Parser::yycheck_[] = {
        7,   17,  181, 3,   138, 19,  1,   43,  45,  29,  30,  1,   32,  17,  45,  17,  17,  54,
        17,  54,  49,  56,  17,  54,  31,  54,  17,  17,  64,  36,  37,  38,  39,  40,  47,  214,
        14,  55,  238, 0,   63,  54,  44,  61,  48,  46,  46,  51,  248, 249, 47,  46,  51,  47,
        2,   46,  46,  54,  201, 44,  54,  63,  78,  41,  51,  3,   14,  15,  16,  17,  18,  19,
        86,  44,  78,  142, 78,  78,  145, 78,  28,  29,  30,  78,  32,  126, 50,  78,  78,  130,
        47,  47,  99,  41,  42,  274, 230, 54,  54,  43,  243, 108, 109, 110, 111, 112, 113, 114,
        115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 57,  126, 47,  50,  43,  130, 17,  64,
        74,  54,  76,  17,  17,  47,  199, 45,  64,  202, 41,  42,  86,  146, 147, 148, 149, 150,
        54,  49,  289, 281, 291, 156, 157, 218, 57,  58,  59,  60,  64,  48,  301, 107, 303, 63,
        305, 0,   1,   60,  45,  4,   5,   6,   7,   8,   4,   5,   6,   7,   8,   125, 54,  45,
        194, 188, 189, 57,  58,  59,  60,  330, 57,  137, 138, 64,  43,  43,  142, 66,  64,  145,
        265, 266, 12,  14,  43,  17,  49,  10,  17,  71,  201, 46,  353, 354, 219, 356, 357, 48,
        223, 48,  9,   233, 240, 241, 242, 25,  48,  50,  56,  49,  49,  372, 373, 50,  20,  376,
        143, 286, 379, 362, 245, 246, 247, 218, 82,  190, 237, 238, 194, 314, 365, 316, 243, 199,
        200, 207, 202, 248, 249, 230, 74,  207, -1,  268, 269, 270, 271, 272, -1,  215, 1,   -1,
        218, 4,   5,   6,   7,   8,   283, -1,  -1,  -1,  -1,  -1,  230, 36,  -1,  233, -1,  201,
        41,  42,  43,  -1,  240, 241, 242, -1,  289, 304, 291, -1,  -1,  -1,  55,  56,  57,  58,
        59,  60,  301, -1,  303, -1,  305, 46,  67,  68,  69,  265, 266, -1,  327, 328, 329, 237,
        238, -1,  -1,  -1,  -1,  243, 244, -1,  -1,  281, 248, 249, -1,  330, 286, -1,  -1,  348,
        349, -1,  -1,  -1,  -1,  -1,  355, -1,  -1,  -1,  -1,  -1,  -1,  362, -1,  -1,  -1,  -1,
        353, 354, -1,  356, 357, -1,  314, -1,  316, -1,  -1,  -1,  320, -1,  -1,  289, -1,  291,
        -1,  372, 373, 17,  -1,  376, -1,  -1,  379, 301, -1,  303, -1,  305, -1,  -1,  -1,  -1,
        32,  -1,  -1,  -1,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  330, -1,  -1,  55,  56,  57,  58,  59,  60,  -1,  -1,  -1,  -1,  65,  -1,  67,
        68,  69,  1,   -1,  -1,  -1,  -1,  353, 354, -1,  356, 357, -1,  -1,  -1,  -1,  -1,  16,
        17,  18,  19,  -1,  -1,  -1,  23,  -1,  372, 373, -1,  28,  376, 30,  -1,  379, 33,  34,
        35,  -1,  -1,  -1,  -1,  40,  41,  42,  -1,  44,  -1,  46,  -1,  -1,  -1,  -1,  -1,  52,
        53,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  63,  1,   -1,  -1,  -1,  -1,  -1,  -1,
        -1,  72,  73,  74,  75,  76,  77,  78,  16,  17,  18,  19,  -1,  -1,  -1,  23,  -1,  -1,
        -1,  -1,  -1,  -1,  30,  -1,  -1,  33,  34,  35,  -1,  -1,  -1,  -1,  40,  41,  42,  -1,
        44,  -1,  46,  -1,  -1,  -1,  -1,  -1,  -1,  53,  -1,  -1,  -1,  57,  -1,  -1,  -1,  -1,
        -1,  63,  1,   -1,  -1,  -1,  -1,  -1,  -1,  -1,  72,  73,  74,  75,  76,  77,  78,  16,
        17,  18,  19,  -1,  -1,  -1,  23,  -1,  -1,  -1,  -1,  -1,  -1,  30,  -1,  -1,  33,  34,
        35,  -1,  -1,  -1,  -1,  40,  41,  42,  -1,  44,  -1,  46,  47,  -1,  -1,  -1,  -1,  -1,
        53,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  63,  1,   -1,  -1,  -1,  -1,  -1,  -1,
        -1,  72,  73,  74,  75,  76,  77,  78,  16,  17,  18,  19,  -1,  -1,  -1,  23,  -1,  -1,
        -1,  -1,  -1,  -1,  30,  -1,  -1,  33,  34,  35,  -1,  -1,  -1,  -1,  40,  41,  42,  -1,
        44,  45,  46,  -1,  -1,  -1,  -1,  -1,  -1,  53,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  63,  -1,  -1,  -1,  -1,  -1,  1,   -1,  -1,  72,  73,  74,  75,  76,  77,  78,  11,
        -1,  13,  -1,  15,  16,  17,  18,  19,  20,  1,   22,  23,  -1,  -1,  26,  -1,  -1,  -1,
        -1,  11,  -1,  13,  -1,  15,  16,  17,  18,  19,  20,  -1,  22,  23,  44,  -1,  26,  -1,
        48,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  63,  44,  -1,
        -1,  -1,  48,  -1,  70,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  78,  -1,  -1,  -1,  -1,  63,
        -1,  1,   -1,  -1,  -1,  -1,  70,  -1,  -1,  -1,  -1,  11,  -1,  13,  78,  15,  16,  17,
        18,  19,  20,  1,   22,  23,  -1,  -1,  26,  -1,  -1,  -1,  -1,  11,  -1,  13,  -1,  15,
        16,  17,  18,  19,  20,  -1,  22,  23,  44,  -1,  26,  -1,  48,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  63,  44,  -1,  -1,  -1,  48,  -1,  70,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  78,  -1,  11,  12,  13,  63,  15,  16,  17,  18,  19,  20,
        70,  22,  23,  -1,  -1,  26,  -1,  11,  78,  13,  14,  15,  16,  17,  18,  19,  20,  -1,
        22,  23,  -1,  -1,  26,  44,  -1,  -1,  -1,  48,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  44,  -1,  63,  -1,  48,  -1,  -1,  -1,  -1,  70,  -1,  -1,  -1,  -1,
        -1,  -1,  11,  78,  13,  63,  15,  16,  17,  18,  19,  20,  70,  22,  23,  -1,  -1,  26,
        -1,  11,  78,  13,  -1,  15,  16,  17,  18,  19,  20,  -1,  22,  23,  -1,  -1,  26,  44,
        -1,  -1,  -1,  48,  49,  -1,  -1,  36,  37,  38,  -1,  -1,  41,  42,  43,  -1,  44,  -1,
        63,  -1,  48,  -1,  -1,  -1,  -1,  70,  55,  56,  57,  58,  59,  60,  -1,  78,  -1,  63,
        -1,  -1,  67,  68,  69,  -1,  70,  71,  -1,  -1,  -1,  11,  -1,  13,  78,  15,  16,  17,
        18,  19,  20,  -1,  22,  23,  -1,  -1,  26,  -1,  16,  17,  18,  19,  -1,  -1,  -1,  23,
        -1,  -1,  -1,  -1,  28,  -1,  30,  -1,  44,  33,  34,  35,  48,  -1,  -1,  -1,  40,  41,
        42,  -1,  44,  -1,  46,  -1,  -1,  49,  -1,  63,  52,  53,  -1,  -1,  -1,  -1,  70,  -1,
        -1,  -1,  -1,  63,  -1,  -1,  78,  -1,  -1,  -1,  -1,  -1,  72,  73,  74,  75,  76,  77,
        78,  16,  17,  18,  19,  -1,  -1,  -1,  23,  -1,  -1,  -1,  -1,  -1,  -1,  30,  -1,  -1,
        33,  34,  35,  -1,  -1,  -1,  -1,  40,  41,  42,  -1,  44,  -1,  46,  -1,  -1,  -1,  -1,
        -1,  -1,  53,  -1,  -1,  -1,  57,  -1,  -1,  -1,  -1,  -1,  63,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  72,  73,  74,  75,  76,  77,  78,  16,  17,  18,  19,  -1,  -1,  -1,  23,
        -1,  -1,  -1,  -1,  -1,  -1,  30,  -1,  -1,  33,  34,  35,  -1,  -1,  -1,  -1,  40,  41,
        42,  -1,  44,  -1,  46,  -1,  -1,  -1,  -1,  -1,  -1,  53,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  63,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  72,  73,  74,  75,  76,  77,
        78,  16,  17,  18,  19,  -1,  -1,  -1,  23,  -1,  -1,  -1,  -1,  -1,  -1,  30,  -1,  -1,
        33,  34,  35,  -1,  -1,  -1,  -1,  40,  41,  42,  -1,  44,  17,  46,  -1,  -1,  -1,  -1,
        -1,  -1,  53,  -1,  -1,  -1,  -1,  -1,  -1,  32,  -1,  -1,  63,  36,  37,  38,  39,  -1,
        41,  42,  43,  72,  73,  74,  75,  76,  77,  78,  -1,  -1,  -1,  -1,  55,  56,  57,  58,
        59,  60,  21,  -1,  -1,  -1,  65,  -1,  67,  68,  69,  -1,  31,  32,  -1,  -1,  -1,  36,
        37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        55,  56,  57,  58,  59,  60,  21,  -1,  -1,  -1,  65,  -1,  67,  68,  69,  -1,  -1,  32,
        -1,  -1,  -1,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,  60,  21,  -1,  -1,  -1,  65,  -1,  67,  68,
        69,  -1,  -1,  32,  -1,  -1,  -1,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,  60,  21,  -1,  -1,  -1,
        65,  -1,  67,  68,  69,  -1,  -1,  32,  -1,  -1,  -1,  36,  37,  38,  39,  -1,  41,  42,
        43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,  60,
        -1,  24,  -1,  -1,  65,  -1,  67,  68,  69,  32,  -1,  -1,  -1,  36,  37,  38,  39,  -1,
        41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,
        59,  60,  -1,  24,  -1,  -1,  65,  -1,  67,  68,  69,  32,  -1,  41,  42,  36,  37,  38,
        39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,  60,  -1,  55,  56,
        57,  58,  59,  60,  68,  69,  25,  -1,  65,  -1,  67,  68,  69,  32,  -1,  -1,  -1,  36,
        37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        55,  56,  57,  58,  59,  60,  27,  -1,  -1,  -1,  65,  32,  67,  68,  69,  36,  37,  38,
        39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,  56,
        57,  58,  59,  60,  -1,  -1,  29,  -1,  65,  32,  67,  68,  69,  36,  37,  38,  39,  -1,
        41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,
        59,  60,  -1,  -1,  -1,  -1,  65,  -1,  67,  68,  69,  31,  32,  -1,  -1,  -1,  36,  37,
        38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,
        56,  57,  58,  59,  60,  -1,  -1,  -1,  -1,  65,  32,  67,  68,  69,  36,  37,  38,  39,
        -1,  41,  42,  43,  -1,  45,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,  56,  57,
        58,  59,  60,  -1,  -1,  -1,  -1,  65,  32,  67,  68,  69,  36,  37,  38,  39,  -1,  41,
        42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,
        60,  -1,  62,  -1,  -1,  65,  32,  67,  68,  69,  36,  37,  38,  39,  -1,  41,  42,  43,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,  60,  -1,
        -1,  -1,  64,  65,  32,  67,  68,  69,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  45,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,  60,  -1,  -1,  -1,
        -1,  65,  32,  67,  68,  69,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  47,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,  60,  -1,  -1,  -1,  -1,  65,
        32,  67,  68,  69,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  45,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,  60,  -1,  -1,  -1,  -1,  65,  32,  67,
        68,  69,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  45,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  55,  56,  57,  58,  59,  60,  -1,  -1,  -1,  -1,  65,  32,  67,  68,  69,
        36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  50,  -1,  -1,  -1,
        -1,  55,  56,  57,  58,  59,  60,  -1,  -1,  -1,  -1,  65,  32,  67,  68,  69,  36,  37,
        38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  49,  -1,  -1,  -1,  -1,  -1,  55,
        56,  57,  58,  59,  60,  -1,  -1,  -1,  -1,  65,  32,  67,  68,  69,  36,  37,  38,  39,
        -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,  56,  57,
        58,  59,  60,  -1,  -1,  -1,  -1,  65,  -1,  67,  68,  69,  36,  -1,  38,  -1,  -1,  41,
        42,  43,  -1,  -1,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,
        60,  55,  56,  57,  58,  59,  60,  67,  68,  69,  -1,  -1,  -1,  67,  68,  69
    };

    const unsigned char Parser::yystos_[] = {
        0,   3,   46,  86,  87,  17,  78,  154, 161, 162, 163, 164, 0,   1,   4,   5,   6,   7,
        8,   46,  88,  89,  90,  91,  92,  93,  94,  95,  16,  18,  19,  23,  30,  33,  34,  35,
        40,  41,  42,  44,  46,  53,  63,  72,  73,  74,  75,  76,  77,  114, 115, 116, 117, 118,
        119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136,
        154, 47,  54,  48,  51,  154, 155, 156, 154, 154, 154, 154, 161, 89,  46,  154, 157, 158,
        159, 159, 159, 114, 159, 114, 114, 114, 1,   57,  114, 1,   47,  113, 114, 155, 154, 32,
        36,  37,  38,  39,  41,  42,  43,  55,  56,  57,  58,  59,  60,  65,  67,  68,  69,  63,
        44,  143, 3,   162, 44,  114, 144, 151, 152, 153, 154, 51,  44,  148, 43,  148, 50,  47,
        161, 50,  43,  17,  17,  24,  17,  45,  114, 45,  47,  47,  54,  62,  138, 139, 140, 141,
        142, 155, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114,
        114, 154, 1,   45,  113, 114, 113, 114, 64,  64,  54,  49,  154, 1,   46,  147, 154, 158,
        160, 64,  48,  43,  64,  138, 145, 146, 90,  47,  138, 114, 114, 114, 114, 114, 45,  63,
        114, 114, 55,  61,  143, 45,  45,  54,  114, 114, 152, 45,  161, 45,  54,  138, 1,   46,
        96,  97,  154, 11,  13,  15,  16,  18,  19,  20,  22,  23,  26,  44,  48,  70,  98,  100,
        101, 102, 105, 106, 107, 108, 109, 110, 111, 112, 117, 118, 138, 57,  64,  157, 17,  29,
        21,  25,  31,  143, 154, 47,  137, 138, 146, 114, 114, 47,  160, 43,  161, 49,  54,  1,
        98,  99,  1,   99,  159, 159, 159, 98,  117, 114, 114, 114, 1,   99,  1,   99,  66,  43,
        138, 138, 114, 114, 114, 114, 114, 143, 54,  56,  64,  45,  158, 114, 47,  96,  12,  12,
        98,  14,  14,  43,  17,  17,  24,  27,  45,  49,  49,  71,  71,  114, 98,  10,  149, 138,
        138, 154, 114, 114, 114, 98,  48,  48,  9,   150, 56,  17,  21,  31,  21,  25,  1,   28,
        52,  103, 104, 114, 114, 48,  98,  98,  114, 98,  98,  49,  50,  50,  49,  103, 50,  49,
        153, 21,  98,  98,  98,  49,  98
    };

    const unsigned char Parser::yyr1_[] = {
        0,   85,  86,  87,  87,  88,  88,  89,  89,  89,  90,  90,  90,  90,  91,  92,  93,  93,
        94,  94,  95,  95,  96,  96,  96,  97,  97,  98,  98,  98,  98,  98,  98,  98,  98,  98,
        98,  98,  99,  99,  100, 101, 101, 102, 102, 103, 103, 103, 104, 104, 105, 106, 106, 107,
        108, 109, 109, 109, 109, 110, 110, 110, 110, 111, 112, 112, 113, 113, 114, 114, 114, 114,
        114, 114, 114, 114, 114, 114, 114, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115,
        115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 116, 117, 117, 117, 118, 118, 119,
        120, 120, 120, 120, 120, 121, 122, 123, 124, 125, 126, 126, 126, 127, 128, 128, 128, 128,
        128, 128, 128, 128, 129, 130, 130, 131, 132, 133, 134, 134, 135, 136, 137, 137, 138, 138,
        138, 138, 139, 140, 141, 142, 143, 143, 143, 144, 145, 145, 146, 146, 147, 147, 148, 148,
        148, 149, 149, 150, 150, 151, 151, 152, 152, 152, 153, 153, 154, 154, 155, 155, 156, 156,
        157, 157, 158, 159, 159, 160, 160, 161, 161, 162, 162, 163, 164
    };

    const unsigned char Parser::yyr2_[] = {
        0, 2, 2, 4, 1, 2, 1, 4, 1, 1, 1, 1, 1, 1, 6, 7, 5, 7, 8, 1, 2, 4, 1, 4, 1, 3, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 4, 6, 6, 6, 3, 3, 3, 2, 1, 6, 6, 8, 6, 2, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 2, 2, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 3, 1, 1, 1, 1, 2, 5, 5, 6, 3, 4,
        2, 6, 6, 6, 6, 6, 2, 3, 3, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
        3, 1, 1, 1, 1, 1, 1, 4, 6, 3, 3, 3, 2, 5, 3, 1, 1, 0, 3, 1, 3, 3, 0, 4, 0, 4, 0, 3,
        1, 1, 3, 3, 1, 0, 1, 1, 1, 2, 3, 1, 1, 1, 3, 4, 1, 4, 1, 3, 1, 1, 1, 1, 2
    };

    // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
    // First, the terminals, then, starting at \a yyntokens_, nonterminals.
    const char* const Parser::yytname_[] = { "\"end of file\"",
                                             "error",
                                             "$undefined",
                                             "\"CASM\"",
                                             "\"init\"",
                                             "\"derived\"",
                                             "\"enumeration\"",
                                             "\"rule\"",
                                             "\"function\"",
                                             "\"initially\"",
                                             "\"defined\"",
                                             "\"seq\"",
                                             "\"endseq\"",
                                             "\"par\"",
                                             "\"endpar\"",
                                             "\"skip\"",
                                             "\"let\"",
                                             "\"in\"",
                                             "\"forall\"",
                                             "\"choose\"",
                                             "\"iterate\"",
                                             "\"do\"",
                                             "\"call\"",
                                             "\"if\"",
                                             "\"then\"",
                                             "\"else\"",
                                             "\"case\"",
                                             "\"of\"",
                                             "\"default\"",
                                             "\"holds\"",
                                             "\"exists\"",
                                             "\"with\"",
                                             "\"as\"",
                                             "\"undef\"",
                                             "\"false\"",
                                             "\"true\"",
                                             "\"and\"",
                                             "\"or\"",
                                             "\"xor\"",
                                             "\"implies\"",
                                             "\"not\"",
                                             "\"+\"",
                                             "\"-\"",
                                             "\"=\"",
                                             "\"(\"",
                                             "\")\"",
                                             "\"[\"",
                                             "\"]\"",
                                             "\"{\"",
                                             "\"}\"",
                                             "\":\"",
                                             "\"::\"",
                                             "\"_\"",
                                             "\"@\"",
                                             "\",\"",
                                             "\"<\"",
                                             "\">\"",
                                             "\"*\"",
                                             "\"/\"",
                                             "\"%\"",
                                             "\"^\"",
                                             "\"'\"",
                                             "\"..\"",
                                             "\".\"",
                                             "\"->\"",
                                             "\"=>\"",
                                             "\":=\"",
                                             "\"!=\"",
                                             "\"<=\"",
                                             "\">=\"",
                                             "\"{|\"",
                                             "\"|}\"",
                                             "\"binary\"",
                                             "\"hexadecimal\"",
                                             "\"integer\"",
                                             "\"rational\"",
                                             "\"decimal\"",
                                             "\"string\"",
                                             "\"identifier\"",
                                             "ABSOLUTE_PATH",
                                             "CALL_EXPRESSION",
                                             "PAREN_TERM",
                                             "UPLUS",
                                             "UMINUS",
                                             "CALL_WITHOUT_ARGS",
                                             "$accept",
                                             "Specification",
                                             "Header",
                                             "Definitions",
                                             "AttributedDefinition",
                                             "Definition",
                                             "EnumerationDefinition",
                                             "DerivedDefinition",
                                             "RuleDefinition",
                                             "FunctionDefinition",
                                             "ProgramFunctionDefinition",
                                             "EnumeratorDefinition",
                                             "Enumerators",
                                             "Rule",
                                             "Rules",
                                             "SkipRule",
                                             "ConditionalRule",
                                             "CaseRule",
                                             "CaseLabel",
                                             "CaseLabels",
                                             "LetRule",
                                             "ForallRule",
                                             "ChooseRule",
                                             "IterateRule",
                                             "BlockRule",
                                             "SequenceRule",
                                             "UpdateRule",
                                             "CallRule",
                                             "Terms",
                                             "Term",
                                             "Expression",
                                             "TypeCastingExpression",
                                             "CallExpression",
                                             "DirectCallExpression",
                                             "IndirectCallExpression",
                                             "MethodCallExpression",
                                             "LetExpression",
                                             "ConditionalExpression",
                                             "ChooseExpression",
                                             "UniversalQuantifierExpression",
                                             "ExistentialQuantifierExpression",
                                             "List",
                                             "Range",
                                             "Literal",
                                             "UndefinedLiteral",
                                             "BooleanLiteral",
                                             "IntegerLiteral",
                                             "RationalLiteral",
                                             "DecimalLiteral",
                                             "BinaryLiteral",
                                             "StringLiteral",
                                             "ReferenceLiteral",
                                             "Types",
                                             "Type",
                                             "BasicType",
                                             "ComposedType",
                                             "RelationType",
                                             "FixedSizedType",
                                             "Arguments",
                                             "TwoOrMoreArguments",
                                             "FunctionParameters",
                                             "MaybeFunctionParameters",
                                             "Parameters",
                                             "MaybeParameters",
                                             "MaybeDefined",
                                             "MaybeInitially",
                                             "Initializers",
                                             "Initializer",
                                             "MaybeInitializers",
                                             "Identifier",
                                             "IdentifierPath",
                                             "DotSeparatedIdentifiers",
                                             "Variable",
                                             "TypedVariable",
                                             "AttributedVariable",
                                             "TypedAttributedVariable",
                                             "Attributes",
                                             "Attribute",
                                             "BasicAttribute",
                                             "ExpressionAttribute",
                                             YY_NULLPTR };

#if YYDEBUG
    const unsigned short int Parser::yyrline_[] = {
        0,    379,  379,  388,  394,  402,  408,  418,  424,  428,  436,  440,  444,  448,  456,
        464,  472,  477,  486,  502,  510,  533,  550,  554,  560,  568,  574,  588,  592,  596,
        600,  604,  608,  612,  616,  620,  624,  628,  636,  642,  652,  660,  664,  672,  676,
        684,  688,  692,  700,  706,  716,  724,  728,  736,  744,  752,  756,  760,  765,  774,
        778,  782,  787,  796,  806,  810,  822,  828,  838,  842,  846,  850,  854,  858,  862,
        866,  870,  874,  878,  890,  894,  898,  902,  906,  910,  914,  918,  922,  926,  930,
        934,  938,  942,  946,  950,  954,  958,  962,  966,  970,  974,  982,  990,  994,  998,
        1006, 1011, 1019, 1027, 1032, 1036, 1041, 1045, 1055, 1063, 1071, 1079, 1087, 1095, 1100,
        1104, 1112, 1124, 1128, 1132, 1136, 1140, 1144, 1148, 1152, 1160, 1168, 1173, 1182, 1198,
        1214, 1230, 1242, 1258, 1274, 1286, 1292, 1302, 1306, 1310, 1314, 1322, 1330, 1338, 1346,
        1358, 1362, 1366, 1375, 1389, 1395, 1405, 1409, 1417, 1423, 1433, 1437, 1441, 1453, 1457,
        1465, 1469, 1477, 1483, 1493, 1501, 1511, 1522, 1526, 1538, 1542, 1550, 1554, 1564, 1570,
        1584, 1588, 1597, 1605, 1611, 1619, 1625, 1637, 1643, 1652, 1656, 1664, 1672
    };

    // Print the state stack on the debug stream.
    void Parser::yystack_print_()
    {
        *yycdebug_ << "Stack now";
        for( stack_type::const_iterator i = yystack_.begin(), i_end = yystack_.end(); i != i_end;
             ++i )
            *yycdebug_ << ' ' << i->state;
        *yycdebug_ << std::endl;
    }

    // Report on the debug stream that the rule \a yyrule is going to be reduced.
    void Parser::yy_reduce_print_( int yyrule )
    {
        unsigned int yylno = yyrline_[ yyrule ];
        int yynrhs = yyr2_[ yyrule ];
        // Print the symbols being reduced, and their result.
        *yycdebug_ << "Reducing stack by rule " << yyrule - 1 << " (line " << yylno
                   << "):" << std::endl;
        // The symbols being reduced.
        for( int yyi = 0; yyi < yynrhs; yyi++ )
            YY_SYMBOL_PRINT( "   $" << yyi + 1 << " =", yystack_[ ( yynrhs ) - ( yyi + 1 ) ] );
    }
#endif  // YYDEBUG

#line 49 "../../obj/src/GrammarParser.yy"  // lalr1.cc:1167
}  // libcasm_fe
#line 4071 "GrammarParser.cpp"               // lalr1.cc:1167
#line 1678 "../../obj/src/GrammarParser.yy"  // lalr1.cc:1168

void Parser::error( const SourceLocation& location, const std::string& message )
{
    log.error( { location }, message, Code::SyntaxError );
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
