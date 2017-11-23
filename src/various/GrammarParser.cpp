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

#line 37 "GrammarParser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "GrammarParser.tab.h"

// User implementation prologue.

#line 51 "GrammarParser.cpp" // lalr1.cc:412
// Unqualified %code blocks.
#line 87 "../../obj/src/GrammarParser.yy" // lalr1.cc:413

    #include "SourceLocation.h"
    #include "Lexer.h"
    #include "Exception.h"
    #include "Logger.h"

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

    static IdentifierPath::Ptr asIdentifierPath( const Identifier::Ptr& identifier )
    {
        const auto& location = identifier->sourceLocation();
        return Ast::make< IdentifierPath >( location, identifier );
    }

    static Rule::Ptr wrapInBlockRule( const Rule::Ptr& rule )
    {
        if( rule == nullptr )
        {
            // this can happen while recovering from a syntax error
            return nullptr;
        }

        if( (rule->id() == Node::ID::BLOCK_RULE )
                or (rule->id() == Node::ID::SEQUENCE_RULE ) )
        {
            return rule; // no need to wrap it
        }

        const auto& sourceLocation = rule->sourceLocation();
        const auto rules = Ast::make< Rules >( sourceLocation );
        rules->add( rule );
        return Ast::make< BlockRule >( sourceLocation, rules );
    }

#line 131 "GrammarParser.cpp" // lalr1.cc:413


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 49 "../../obj/src/GrammarParser.yy" // lalr1.cc:479
namespace libcasm_fe {
#line 217 "GrammarParser.cpp" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  Parser::Parser (Logger& log_yyarg, Lexer& lexer_yyarg, Specification& specification_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      log (log_yyarg),
      lexer (lexer_yyarg),
      specification (specification_yyarg)
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 159: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 158: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 160: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case 136: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 106: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 114: // CallExpression
        value.move< CallExpression::Ptr > (that.value);
        break;

      case 109: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 100: // CaseLabel
        value.move< Case::Ptr > (that.value);
        break;

      case 99: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 101: // CaseLabels
        value.move< Cases::Ptr > (that.value);
        break;

      case 120: // ChooseExpression
        value.move< ChooseExpression::Ptr > (that.value);
        break;

      case 104: // ChooseRule
        value.move< ChooseRule::Ptr > (that.value);
        break;

      case 137: // ComposedType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 119: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 98: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case 86: // AttributedDefinition
      case 87: // Definition
        value.move< Definition::Ptr > (that.value);
        break;

      case 85: // Definitions
        value.move< Definitions::Ptr > (that.value);
        break;

      case 89: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (that.value);
        break;

      case 115: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 88: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 93: // EnumeratorDefinition
        value.move< EnumeratorDefinition::Ptr > (that.value);
        break;

      case 94: // Enumerators
        value.move< Enumerators::Ptr > (that.value);
        break;

      case 122: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 111: // Term
      case 112: // Expression
      case 125: // Literal
      case 146: // MaybeDefined
        value.move< Expression::Ptr > (that.value);
        break;

      case 161: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case 110: // Terms
      case 140: // Arguments
      case 141: // TwoOrMoreArguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 139: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 103: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 91: // FunctionDefinition
      case 92: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 84: // Header
        value.move< HeaderDefinition::Ptr > (that.value);
        break;

      case 151: // Identifier
        value.move< Identifier::Ptr > (that.value);
        break;

      case 152: // IdentifierPath
        value.move< IdentifierPath::Ptr > (that.value);
        break;

      case 153: // DotSeparatedIdentifiers
        value.move< Identifiers::Ptr > (that.value);
        break;

      case 116: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 105: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 118: // LetExpression
        value.move< LetExpression::Ptr > (that.value);
        break;

      case 102: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 123: // List
        value.move< ListExpression::Ptr > (that.value);
        break;

      case 117: // MethodCallExpression
        value.move< MethodCallExpression::Ptr > (that.value);
        break;

      case 147: // MaybeInitially
      case 148: // Initializers
      case 150: // MaybeInitializers
        value.move< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 144: // Parameters
      case 145: // MaybeParameters
        value.move< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 124: // Range
        value.move< RangeExpression::Ptr > (that.value);
        break;

      case 133: // ReferenceLiteral
        value.move< ReferenceAtom::Ptr > (that.value);
        break;

      case 138: // RelationType
        value.move< RelationType::Ptr > (that.value);
        break;

      case 95: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 90: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 96: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 107: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 97: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 83: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 113: // TypeCastingExpression
        value.move< TypeCastingExpression::Ptr > (that.value);
        break;

      case 134: // Types
      case 142: // FunctionParameters
      case 143: // MaybeFunctionParameters
        value.move< Types::Ptr > (that.value);
        break;

      case 126: // UndefinedLiteral
        value.move< UndefAtom::Ptr > (that.value);
        break;

      case 121: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 108: // UpdateRule
      case 149: // Initializer
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 127: // BooleanLiteral
      case 128: // IntegerLiteral
      case 129: // RationalLiteral
      case 130: // DecimalLiteral
      case 131: // BitLiteral
      case 132: // StringLiteral
        value.move< ValueAtom::Ptr > (that.value);
        break;

      case 154: // Variable
      case 155: // TypedVariable
      case 156: // AttributedVariable
      case 157: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (that.value);
        break;

      case 135: // Type
        value.move< libcasm_fe::Ast::Type::Ptr > (that.value);
        break;

      case 71: // "binary"
      case 72: // "hexadecimal"
      case 73: // "integer"
      case 74: // "rational"
      case 75: // "decimal"
      case 76: // "string"
      case 77: // "identifier"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 159: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case 158: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case 160: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (that.value);
        break;

      case 136: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 106: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 114: // CallExpression
        value.copy< CallExpression::Ptr > (that.value);
        break;

      case 109: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 100: // CaseLabel
        value.copy< Case::Ptr > (that.value);
        break;

      case 99: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 101: // CaseLabels
        value.copy< Cases::Ptr > (that.value);
        break;

      case 120: // ChooseExpression
        value.copy< ChooseExpression::Ptr > (that.value);
        break;

      case 104: // ChooseRule
        value.copy< ChooseRule::Ptr > (that.value);
        break;

      case 137: // ComposedType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 119: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 98: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (that.value);
        break;

      case 86: // AttributedDefinition
      case 87: // Definition
        value.copy< Definition::Ptr > (that.value);
        break;

      case 85: // Definitions
        value.copy< Definitions::Ptr > (that.value);
        break;

      case 89: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (that.value);
        break;

      case 115: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 88: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 93: // EnumeratorDefinition
        value.copy< EnumeratorDefinition::Ptr > (that.value);
        break;

      case 94: // Enumerators
        value.copy< Enumerators::Ptr > (that.value);
        break;

      case 122: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 111: // Term
      case 112: // Expression
      case 125: // Literal
      case 146: // MaybeDefined
        value.copy< Expression::Ptr > (that.value);
        break;

      case 161: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (that.value);
        break;

      case 110: // Terms
      case 140: // Arguments
      case 141: // TwoOrMoreArguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 139: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 103: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 91: // FunctionDefinition
      case 92: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 84: // Header
        value.copy< HeaderDefinition::Ptr > (that.value);
        break;

      case 151: // Identifier
        value.copy< Identifier::Ptr > (that.value);
        break;

      case 152: // IdentifierPath
        value.copy< IdentifierPath::Ptr > (that.value);
        break;

      case 153: // DotSeparatedIdentifiers
        value.copy< Identifiers::Ptr > (that.value);
        break;

      case 116: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 105: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 118: // LetExpression
        value.copy< LetExpression::Ptr > (that.value);
        break;

      case 102: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case 123: // List
        value.copy< ListExpression::Ptr > (that.value);
        break;

      case 117: // MethodCallExpression
        value.copy< MethodCallExpression::Ptr > (that.value);
        break;

      case 147: // MaybeInitially
      case 148: // Initializers
      case 150: // MaybeInitializers
        value.copy< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 144: // Parameters
      case 145: // MaybeParameters
        value.copy< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 124: // Range
        value.copy< RangeExpression::Ptr > (that.value);
        break;

      case 133: // ReferenceLiteral
        value.copy< ReferenceAtom::Ptr > (that.value);
        break;

      case 138: // RelationType
        value.copy< RelationType::Ptr > (that.value);
        break;

      case 95: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 90: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 96: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 107: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 97: // SkipRule
        value.copy< SkipRule::Ptr > (that.value);
        break;

      case 83: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 113: // TypeCastingExpression
        value.copy< TypeCastingExpression::Ptr > (that.value);
        break;

      case 134: // Types
      case 142: // FunctionParameters
      case 143: // MaybeFunctionParameters
        value.copy< Types::Ptr > (that.value);
        break;

      case 126: // UndefinedLiteral
        value.copy< UndefAtom::Ptr > (that.value);
        break;

      case 121: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 108: // UpdateRule
      case 149: // Initializer
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case 127: // BooleanLiteral
      case 128: // IntegerLiteral
      case 129: // RationalLiteral
      case 130: // DecimalLiteral
      case 131: // BitLiteral
      case 132: // StringLiteral
        value.copy< ValueAtom::Ptr > (that.value);
        break;

      case 154: // Variable
      case 155: // TypedVariable
      case 156: // AttributedVariable
      case 157: // TypedAttributedVariable
        value.copy< VariableDefinition::Ptr > (that.value);
        break;

      case 135: // Type
        value.copy< libcasm_fe::Ast::Type::Ptr > (that.value);
        break;

      case 71: // "binary"
      case 72: // "hexadecimal"
      case 73: // "integer"
      case 74: // "rational"
      case 75: // "decimal"
      case 76: // "string"
      case 77: // "identifier"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
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
    stack_symbol_type yyerror_range[3];

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
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex ());
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 159: // Attribute
        yylhs.value.build< Attribute::Ptr > ();
        break;

      case 158: // Attributes
        yylhs.value.build< Attributes::Ptr > ();
        break;

      case 160: // BasicAttribute
        yylhs.value.build< BasicAttribute::Ptr > ();
        break;

      case 136: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 106: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 114: // CallExpression
        yylhs.value.build< CallExpression::Ptr > ();
        break;

      case 109: // CallRule
        yylhs.value.build< CallRule::Ptr > ();
        break;

      case 100: // CaseLabel
        yylhs.value.build< Case::Ptr > ();
        break;

      case 99: // CaseRule
        yylhs.value.build< CaseRule::Ptr > ();
        break;

      case 101: // CaseLabels
        yylhs.value.build< Cases::Ptr > ();
        break;

      case 120: // ChooseExpression
        yylhs.value.build< ChooseExpression::Ptr > ();
        break;

      case 104: // ChooseRule
        yylhs.value.build< ChooseRule::Ptr > ();
        break;

      case 137: // ComposedType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 119: // ConditionalExpression
        yylhs.value.build< ConditionalExpression::Ptr > ();
        break;

      case 98: // ConditionalRule
        yylhs.value.build< ConditionalRule::Ptr > ();
        break;

      case 86: // AttributedDefinition
      case 87: // Definition
        yylhs.value.build< Definition::Ptr > ();
        break;

      case 85: // Definitions
        yylhs.value.build< Definitions::Ptr > ();
        break;

      case 89: // DerivedDefinition
        yylhs.value.build< DerivedDefinition::Ptr > ();
        break;

      case 115: // DirectCallExpression
        yylhs.value.build< DirectCallExpression::Ptr > ();
        break;

      case 88: // EnumerationDefinition
        yylhs.value.build< EnumerationDefinition::Ptr > ();
        break;

      case 93: // EnumeratorDefinition
        yylhs.value.build< EnumeratorDefinition::Ptr > ();
        break;

      case 94: // Enumerators
        yylhs.value.build< Enumerators::Ptr > ();
        break;

      case 122: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 111: // Term
      case 112: // Expression
      case 125: // Literal
      case 146: // MaybeDefined
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 161: // ExpressionAttribute
        yylhs.value.build< ExpressionAttribute::Ptr > ();
        break;

      case 110: // Terms
      case 140: // Arguments
      case 141: // TwoOrMoreArguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 139: // FixedSizedType
        yylhs.value.build< FixedSizedType::Ptr > ();
        break;

      case 103: // ForallRule
        yylhs.value.build< ForallRule::Ptr > ();
        break;

      case 91: // FunctionDefinition
      case 92: // ProgramFunctionDefinition
        yylhs.value.build< FunctionDefinition::Ptr > ();
        break;

      case 84: // Header
        yylhs.value.build< HeaderDefinition::Ptr > ();
        break;

      case 151: // Identifier
        yylhs.value.build< Identifier::Ptr > ();
        break;

      case 152: // IdentifierPath
        yylhs.value.build< IdentifierPath::Ptr > ();
        break;

      case 153: // DotSeparatedIdentifiers
        yylhs.value.build< Identifiers::Ptr > ();
        break;

      case 116: // IndirectCallExpression
        yylhs.value.build< IndirectCallExpression::Ptr > ();
        break;

      case 105: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 118: // LetExpression
        yylhs.value.build< LetExpression::Ptr > ();
        break;

      case 102: // LetRule
        yylhs.value.build< LetRule::Ptr > ();
        break;

      case 123: // List
        yylhs.value.build< ListExpression::Ptr > ();
        break;

      case 117: // MethodCallExpression
        yylhs.value.build< MethodCallExpression::Ptr > ();
        break;

      case 147: // MaybeInitially
      case 148: // Initializers
      case 150: // MaybeInitializers
        yylhs.value.build< NodeList< UpdateRule >::Ptr > ();
        break;

      case 144: // Parameters
      case 145: // MaybeParameters
        yylhs.value.build< NodeList< VariableDefinition >::Ptr > ();
        break;

      case 124: // Range
        yylhs.value.build< RangeExpression::Ptr > ();
        break;

      case 133: // ReferenceLiteral
        yylhs.value.build< ReferenceAtom::Ptr > ();
        break;

      case 138: // RelationType
        yylhs.value.build< RelationType::Ptr > ();
        break;

      case 95: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 90: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 96: // Rules
        yylhs.value.build< Rules::Ptr > ();
        break;

      case 107: // SequenceRule
        yylhs.value.build< SequenceRule::Ptr > ();
        break;

      case 97: // SkipRule
        yylhs.value.build< SkipRule::Ptr > ();
        break;

      case 83: // Specification
        yylhs.value.build< Specification::Ptr > ();
        break;

      case 113: // TypeCastingExpression
        yylhs.value.build< TypeCastingExpression::Ptr > ();
        break;

      case 134: // Types
      case 142: // FunctionParameters
      case 143: // MaybeFunctionParameters
        yylhs.value.build< Types::Ptr > ();
        break;

      case 126: // UndefinedLiteral
        yylhs.value.build< UndefAtom::Ptr > ();
        break;

      case 121: // UniversalQuantifierExpression
        yylhs.value.build< UniversalQuantifierExpression::Ptr > ();
        break;

      case 108: // UpdateRule
      case 149: // Initializer
        yylhs.value.build< UpdateRule::Ptr > ();
        break;

      case 127: // BooleanLiteral
      case 128: // IntegerLiteral
      case 129: // RationalLiteral
      case 130: // DecimalLiteral
      case 131: // BitLiteral
      case 132: // StringLiteral
        yylhs.value.build< ValueAtom::Ptr > ();
        break;

      case 154: // Variable
      case 155: // TypedVariable
      case 156: // AttributedVariable
      case 157: // TypedAttributedVariable
        yylhs.value.build< VariableDefinition::Ptr > ();
        break;

      case 135: // Type
        yylhs.value.build< libcasm_fe::Ast::Type::Ptr > ();
        break;

      case 71: // "binary"
      case 72: // "hexadecimal"
      case 73: // "integer"
      case 74: // "rational"
      case 75: // "decimal"
      case 76: // "string"
      case 77: // "identifier"
        yylhs.value.build< std::string > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 382 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      specification.setHeader( yystack_[1].value.as< HeaderDefinition::Ptr > () );
      specification.setDefinitions( yystack_[0].value.as< Definitions::Ptr > () );
  }
#line 1386 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 391 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
      definition->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< HeaderDefinition::Ptr > () = definition;
  }
#line 1396 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 397 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< HeaderDefinition::Ptr > () = Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
  }
#line 1404 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 405 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1414 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 411 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1424 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 421 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = yystack_[0].value.as< Definition::Ptr > ();
      definition->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< Definition::Ptr > () = definition;
  }
#line 1434 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 427 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< Definition::Ptr > ();
  }
#line 1442 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 431 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = nullptr;
  }
#line 1450 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 439 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1458 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 443 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1466 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 447 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1474 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 451 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1482 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 459 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< Identifier::Ptr > (), yystack_[1].value.as< Enumerators::Ptr > () );
  }
#line 1490 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 467 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1498 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 475 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as< Identifier::Ptr > (), yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > (), createVoidType( yylhs.location ),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 1507 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 480 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 1516 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 489 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto identifier = yystack_[6].value.as< Identifier::Ptr > ();

      auto function = Ast::make< FunctionDefinition >( yylhs.location, identifier, yystack_[4].value.as< Types::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > () );
      function->setDefaultValue( yystack_[1].value.as< Expression::Ptr > () );

      // apply the name of the function declaration to the initializer functions
      auto initializers = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
      for (auto& initializer : *initializers) {
           initializer->function()->setIdentifier( asIdentifierPath( identifier ) );
      }
      function->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = function;
  }
#line 1536 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 505 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1544 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 513 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto singleAgentIdentifier = Ast::make< Identifier >( yylhs.location, "$" );
      auto singleAgentArguments = libcasm_fe::Ast::make< Expressions >( yylhs.location );
      const auto singleAgent = libcasm_fe::Ast::make< DirectCallExpression >(
          yylhs.location, asIdentifierPath( singleAgentIdentifier ), singleAgentArguments );
      singleAgent->setTargetType( CallExpression::TargetType::CONSTANT );

      auto programDefinition = createProgramFunction( yylhs.location );
      auto programArguments = libcasm_fe::Ast::make< Expressions >( yylhs.location );
      programArguments->add( singleAgent );
      const auto program = libcasm_fe::Ast::make< DirectCallExpression >(
          yylhs.location, asIdentifierPath( programDefinition->identifier() ), programArguments );
      program->setTargetType( CallExpression::TargetType::FUNCTION );

      const auto ruleReference = Ast::make< ReferenceAtom >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );

      auto initializers = Ast::make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( Ast::make< UpdateRule >( yylhs.location, program, ruleReference ) );
      programDefinition->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = programDefinition;
  }
#line 1571 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 536 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto programDefinition = createProgramFunction( yylhs.location );

      // apply the name of the program declaration to the initializer functions
      auto initializers = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
      for (auto& initializer : *initializers) {
          initializer->function()->setIdentifier(
                asIdentifierPath( programDefinition->identifier() ) );
      }
      programDefinition->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = programDefinition;
  }
#line 1589 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 554 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumeratorDefinition::Ptr > () = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 1597 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 558 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerator = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
      enumerator->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< EnumeratorDefinition::Ptr > () = enumerator;
  }
#line 1607 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 564 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumeratorDefinition::Ptr > () = nullptr;
  }
#line 1615 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 572 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerators = yystack_[2].value.as< Enumerators::Ptr > ();
      enumerators->add( yystack_[0].value.as< EnumeratorDefinition::Ptr > () );
      yylhs.value.as< Enumerators::Ptr > () = enumerators;
  }
#line 1625 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 578 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerators = Ast::make< Enumerators >( yylhs.location );
      enumerators->add( yystack_[0].value.as< EnumeratorDefinition::Ptr > () );
      yylhs.value.as< Enumerators::Ptr > () = enumerators;
  }
#line 1635 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 592 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 1643 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 596 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 1651 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 600 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 1659 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 604 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 1667 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 608 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 1675 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 612 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ChooseRule::Ptr > ();
  }
#line 1683 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 616 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 1691 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 620 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 1699 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 624 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 1707 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 628 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 1715 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 632 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 1723 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 640 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1733 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 646 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1743 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 656 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location );
  }
#line 1751 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 664 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1759 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 668 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1767 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 676 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< Cases::Ptr > () );
  }
#line 1775 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 680 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = nullptr;
  }
#line 1783 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 688 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1791 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 692 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1799 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 696 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1807 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 704 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = yystack_[1].value.as< Cases::Ptr > ();
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1817 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 710 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1827 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 720 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1835 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 728 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1843 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 732 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[6].value.as< VariableDefinition::Ptr > (), yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1851 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 740 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1859 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 748 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1867 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 756 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1875 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 760 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1883 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 764 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1892 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 769 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1901 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 778 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1909 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 782 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1917 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 786 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1926 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 791 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1935 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 800 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto function = yystack_[2].value.as< DirectCallExpression::Ptr > ();
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1945 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 810 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), CallRule::Type::RULE_CALL );
  }
#line 1953 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 814 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), CallRule::Type::RULE_CALL );
  }
#line 1961 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 818 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), CallRule::Type::FUNCTION_CALL );
  }
#line 1969 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 822 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), CallRule::Type::FUNCTION_CALL );
  }
#line 1977 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 834 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 1987 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 840 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 1997 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 850 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2005 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 854 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< TypeCastingExpression::Ptr > ();
  }
#line 2013 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 858 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< CallExpression::Ptr > ();
  }
#line 2021 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 862 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< LetExpression::Ptr > ();
  }
#line 2029 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 866 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 2037 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 870 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ChooseExpression::Ptr > ();
  }
#line 2045 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 874 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 2053 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 878 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 2061 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 882 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ListExpression::Ptr > ();
  }
#line 2069 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 886 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RangeExpression::Ptr > ();
  }
#line 2077 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 890 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2085 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 902 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2093 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 906 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = nullptr;
  }
#line 2101 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 910 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2109 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 914 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 2117 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 918 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2125 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 922 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2133 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 926 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2141 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 930 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2149 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 934 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2157 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 938 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 2165 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 942 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2173 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 946 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2181 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 950 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2189 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 954 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2197 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 958 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2205 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 962 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2213 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 966 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2221 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 970 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2229 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 974 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2237 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 978 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2245 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 982 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2253 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 986 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2261 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 994 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< TypeCastingExpression::Ptr > () = Ast::make< TypeCastingExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2269 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1002 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallExpression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 2277 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1006 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallExpression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 2285 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1010 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallExpression::Ptr > () = yystack_[0].value.as< MethodCallExpression::Ptr > ();
  }
#line 2293 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1018 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      const auto identifierPath
          = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > (), IdentifierPath::Type::ABSOLUTE );
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, identifierPath, arguments );
  }
#line 2304 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1025 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto identifierPath
          = Ast::make< IdentifierPath >( yylhs.location, yystack_[1].value.as< Identifier::Ptr > (), IdentifierPath::Type::ABSOLUTE );
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, identifierPath, yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2314 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1035 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2322 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1043 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Identifier::Ptr > (), arguments );
  }
#line 2331 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1048 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2340 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1053 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedNamespace = Ast::make< UnresolvedNamespace >( yylhs.location );
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, unresolvedNamespace, yystack_[0].value.as< Identifier::Ptr > (), arguments );
  }
#line 2350 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1063 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetExpression::Ptr > () = Ast::make< LetExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2358 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1071 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2366 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1079 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseExpression::Ptr > () = Ast::make< ChooseExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2374 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1087 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2382 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1095 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2390 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1103 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, expressions );
  }
#line 2399 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1108 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2407 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1112 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = nullptr;
  }
#line 2415 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1120 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeExpression::Ptr > () = Ast::make< RangeExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2423 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1132 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UndefAtom::Ptr > ();
  }
#line 2431 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1136 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2439 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1140 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2447 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1144 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2455 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1148 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2463 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1152 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2471 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1156 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2479 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1160 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ReferenceAtom::Ptr > ();
  }
#line 2487 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1168 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefAtom::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 2495 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1176 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 2504 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1181 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 2513 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1190 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::IntegerConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::DECIMAL );
          yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2529 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1206 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::RationalConstant >( yystack_[0].value.as< std::string > () );
          yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2545 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1222 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::DecimalConstant >( yystack_[0].value.as< std::string > () );
          yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2561 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1238 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::BINARY );
          yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2577 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1250 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::HEXADECIMAL );
          yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2593 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1266 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::StringConstant >( yystack_[0].value.as< std::string > () );
          yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2609 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1282 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ReferenceAtom::Ptr > () = Ast::make< ReferenceAtom >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2617 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1294 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2627 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1300 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2637 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1310 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 2645 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1314 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2653 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1318 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< RelationType::Ptr > ();
  }
#line 2661 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1322 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 2669 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1330 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2677 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1338 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, yystack_[3].value.as< IdentifierPath::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 2685 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1346 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as< IdentifierPath::Ptr > (), yystack_[3].value.as< Types::Ptr > (), yystack_[1].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2693 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1354 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2701 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1366 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2709 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1370 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = nullptr;
  }
#line 2717 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1374 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2726 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1383 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = yystack_[3].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[1].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2736 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1397 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2746 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1403 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2756 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1413 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 2764 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1417 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 2772 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1425 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 2782 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1431 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 2792 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1441 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = yystack_[1].value.as< NodeList< VariableDefinition >::Ptr > ();
  }
#line 2800 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1445 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = nullptr;
  }
#line 2808 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1449 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 2816 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1461 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2824 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1465 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 2832 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1473 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 2840 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1477 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 2848 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1485 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< NodeList< UpdateRule >::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 2858 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1491 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = Ast::make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 2868 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1501 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2880 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1509 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[2].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2894 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1519 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, yystack_[2].value.as< Expressions::Ptr > () );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2905 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1530 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 2913 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1534 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 2921 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1546 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 2929 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1550 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, "in" );
  }
#line 2937 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1558 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifiers::Ptr > (), IdentifierPath::Type::ABSOLUTE );
  }
#line 2945 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 1562 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, identifiers, IdentifierPath::Type::RELATIVE );
  }
#line 2955 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 1572 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< Identifiers::Ptr > ();
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 2965 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 1578 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 2975 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 180:
#line 1592 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 2983 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 181:
#line 1596 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > (), unresolvedType );
  }
#line 2992 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 182:
#line 1605 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 3000 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 183:
#line 1613 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 3010 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 184:
#line 1619 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3018 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 185:
#line 1627 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 3028 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 186:
#line 1633 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3036 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 187:
#line 1645 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = yystack_[2].value.as< Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 3046 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 188:
#line 1651 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 3056 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 189:
#line 1660 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< BasicAttribute::Ptr > ();
  }
#line 3064 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 190:
#line 1664 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< ExpressionAttribute::Ptr > ();
  }
#line 3072 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 191:
#line 1672 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 3080 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 192:
#line 1680 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3088 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 3092 "GrammarParser.cpp" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
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
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
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
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

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
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short int Parser::yypact_ninf_ = -162;

  const short int Parser::yytable_ninf_ = -156;

  const short int
  Parser::yypact_[] =
  {
      -1,  -162,     4,     5,   158,  -162,  -162,   993,    44,  -162,
    -162,  -162,  -162,  -162,    -6,     4,     4,     4,     4,     4,
     125,  -162,  -162,  -162,  -162,  -162,  -162,  -162,    -5,    -5,
      -5,   993,    -5,  -162,  -162,  -162,   993,   993,   993,   520,
     582,    -3,     4,  -162,  -162,  -162,  -162,  -162,  -162,  1810,
    -162,  -162,  -162,  -162,  -162,  -162,  -162,  -162,  -162,  -162,
    -162,  -162,  -162,  -162,  -162,  -162,  -162,  -162,  -162,  -162,
    -162,  -162,   -36,    20,     4,  1055,     4,  -162,  -162,   -13,
       7,    17,     7,   -11,   104,  -162,     4,    19,  -162,  -162,
      27,    35,    70,  1327,    71,  -162,  -162,  -162,    39,   993,
    1546,    49,  -162,   114,  1579,  -162,  -162,    -3,   993,   993,
     993,   993,   993,   993,   993,   993,   993,   993,   993,   993,
     993,     4,   993,   993,   993,   993,   644,  -162,  -162,  -162,
     520,  1612,    51,    45,  -162,    78,  -162,     4,     2,    65,
     105,   -26,    -3,   193,   121,    -3,   993,   993,   993,   993,
     993,  -162,  1645,  -162,  -162,  -162,   993,   993,  -162,  -162,
    -162,  -162,  -162,   118,  1910,  1876,  1904,  1843,   163,   163,
    1357,    79,    79,    93,    93,    93,  -162,   -36,  1843,  1357,
      79,    79,   109,  -162,   -10,  1810,   117,  1546,   993,   993,
    1055,  -162,  -162,   135,     4,     1,    19,  -162,  -162,    -3,
       9,   909,    -3,  -162,   119,   124,  -162,     4,  -162,  1101,
    1475,  1212,  1402,  1513,   -36,  1810,  1678,    -3,   993,  -162,
    -162,  -162,   993,  1810,  1810,  -162,  -162,   126,  -162,    -2,
     145,  -162,     4,  -162,   -31,  -162,   682,   721,  -162,    -5,
      -5,    -5,   909,    -4,   993,   993,   133,   755,   791,  -162,
    -162,  -162,  -162,  -162,  -162,  -162,  -162,  -162,  -162,  -162,
    -162,   127,  -162,   148,    -3,    -3,  -162,   993,   993,   993,
     993,   993,  -162,  -162,   -17,   -29,   132,  -162,  1711,     4,
    -162,   993,   130,  -162,     9,   190,  -162,   360,   189,   827,
     162,   191,   195,  -162,  -162,  -162,  1364,  1435,   164,   861,
     153,   875,   993,   909,  -162,   214,  1810,  1810,  1810,  1810,
    1810,    -3,  -162,    -3,  -162,  -162,  1810,     4,  -162,  -162,
    -162,  -162,  -162,  -162,   993,   993,   993,   909,   179,  -162,
    -162,  -162,  -162,  1810,  -162,   180,   221,  -162,   176,  -162,
    1134,  1173,  1251,   208,   458,   993,   186,  -162,  -162,   909,
     909,   993,   909,   909,   187,   185,   194,  -162,   931,  1744,
    1777,  1055,  -162,  -162,  1290,  -162,  -162,  -162,   909,   909,
    -162,  -162,   909,  -162,   192,   909,  -162,  -162,  -162,  -162,
    -162
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     4,     0,     0,     0,   175,   174,   191,     0,   188,
     189,   190,     1,     9,     0,     0,     0,     0,     0,     0,
       0,     6,     8,    10,    11,    12,    13,    19,     0,     0,
       0,     0,     0,   130,   132,   131,     0,     0,     0,     0,
       0,     0,     0,   136,   137,   133,   134,   135,   138,   192,
      70,    71,    72,   104,   105,   106,    73,    74,    75,    76,
      77,    78,    79,    80,   122,   123,   124,   125,   126,   127,
     128,   129,   107,     0,     0,   173,     0,   179,    20,   176,
     162,     0,   162,     0,     0,     5,     0,   181,   184,   180,
       0,     0,     0,     0,     0,   102,    83,    84,     0,     0,
       0,     0,   118,     0,    69,   139,   112,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   108,     3,   187,
       0,   169,     0,   172,   168,     0,   177,     0,     0,     0,
       0,     0,   157,     0,     0,     0,     0,     0,     0,     0,
       0,    82,     0,    81,   120,   119,     0,     0,   103,   142,
     143,   144,   145,   146,    99,    97,    98,   101,    85,    86,
      92,    93,    94,    87,    88,    89,    90,   110,   100,    91,
      95,    96,     0,   152,     0,    69,     0,    69,     0,     0,
       0,    21,   178,     0,     0,     0,     0,   186,   159,     0,
       0,     0,     0,   155,   156,     0,     7,     0,   182,     0,
       0,     0,     0,     0,     0,    68,     0,   157,     0,   111,
     151,   150,     0,   170,   171,   167,   161,     0,   160,     0,
       0,    24,     0,    26,     0,    22,     0,     0,    40,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    16,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    66,    67,     0,     0,     0,   183,     0,     0,     0,
       0,     0,   109,   121,     0,   141,     0,   149,    68,     0,
     158,     0,     0,    14,     0,     0,    39,     0,     0,     0,
       0,     0,     0,    54,    64,    65,     0,     0,     0,     0,
       0,     0,     0,     0,   154,   164,   113,   116,   115,   114,
     117,     0,   147,     0,   153,   185,    15,     0,    25,    62,
      60,    38,    58,    56,     0,     0,     0,     0,     0,    57,
      55,    61,    59,    63,    17,     0,   166,   140,     0,    23,
       0,     0,     0,    41,     0,     0,     0,    18,   148,     0,
       0,     0,     0,     0,     0,     0,     0,    49,     0,     0,
       0,   173,    50,    51,     0,    53,    42,    44,     0,     0,
      43,    48,     0,   163,     0,     0,    45,    46,    47,   165,
      52
  };

  const short int
  Parser::yypgoto_[] =
  {
    -162,  -162,  -162,  -162,   219,    97,  -162,  -162,  -162,  -162,
    -162,   -41,  -162,  -143,  -154,  -162,  -162,  -162,  -113,  -162,
    -162,  -162,  -162,  -162,  -162,  -162,  -162,  -162,   -69,    -7,
    -162,  -162,  -162,    67,    98,  -162,  -162,  -162,  -162,  -162,
    -162,  -162,  -162,  -162,  -162,  -162,  -162,  -162,  -162,  -162,
    -162,  -162,  -162,  -117,  -162,  -162,  -162,  -162,  -161,  -162,
    -162,    29,  -162,   167,  -162,  -162,  -162,    61,  -109,    48,
       6,  -162,    46,  -134,   -23,    25,   -18,   182,  -162,  -162
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     3,     4,    20,    21,    22,    23,    24,    25,    26,
      27,   233,   234,   286,   287,   250,   251,   252,   357,   358,
     253,   254,   255,   256,   257,   258,   259,   260,   103,   131,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,   274,   158,   159,   160,   161,   162,   127,   132,
     204,   205,   195,   139,   336,   347,   133,   134,   135,    72,
     163,    79,    88,    89,    90,   198,     8,     9,    10,    11
  };

  const short int
  Parser::yytable_[] =
  {
      49,    84,     1,   193,   197,    12,    91,    92,   126,    94,
     231,     5,     5,     5,     5,     5,   219,   201,   283,     5,
      78,     5,   284,   128,    93,   203,     5,  -155,   208,    95,
      96,    97,   100,   104,  -155,   221,   311,   202,   312,   142,
     246,    86,    75,   156,   194,     2,   228,   105,   194,   137,
       7,   138,   147,   272,   229,   232,    76,   184,   249,    76,
     140,   186,    77,    80,    81,    82,    83,     7,   144,   145,
     146,     6,     6,     6,     6,     6,    87,    87,    87,     6,
      87,     6,   230,   289,   151,   263,     6,   148,   150,    77,
     106,    73,   152,   299,   301,   197,   154,    74,   190,   293,
     275,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   189,   178,   179,   180,   181,   185,
     112,   113,     7,   187,   136,    -2,    13,   191,   199,    14,
      15,    16,    17,    18,     7,   117,   118,   119,   120,   209,
     210,   211,   212,   213,   321,   315,   321,   304,   305,   215,
     216,   143,   120,   200,   220,    77,   321,    74,   321,    13,
     334,   155,    14,    15,    16,    17,    18,   156,   207,   177,
     222,    19,   217,   279,    74,   264,   227,   317,   218,    74,
     226,   223,   224,    74,   343,   192,   196,   265,   281,    99,
      77,   303,   302,    77,   337,   313,   338,    14,    15,    16,
      17,    18,   319,   322,    19,   324,   362,   363,   325,   365,
     366,   277,   326,   329,   282,   278,   290,   291,   292,   117,
     118,   119,   120,   331,   335,   376,   377,   344,   345,   378,
     346,   348,   380,   353,   361,   368,   367,   296,   297,    85,
     206,   379,     7,   318,   369,   371,   276,    77,   235,   141,
      77,   225,   374,   266,   280,    87,   129,     0,     0,     0,
     306,   307,   308,   309,   310,    77,     0,     0,   261,     0,
       0,     0,     0,     0,   316,     0,     0,   196,     0,     0,
       7,     0,     0,     0,     0,     0,     0,    87,    87,    87,
       0,     0,     0,     0,     0,   333,     0,     0,     0,   262,
       0,     0,     0,   261,   261,     0,     0,     0,     0,   261,
     294,     0,    77,    77,   261,   261,     0,   340,   341,   342,
       0,     0,     0,     0,     0,     0,     0,   196,     0,     0,
       0,     0,   235,     0,   262,   262,     0,   359,   360,     0,
     262,   295,     0,     0,   364,   262,   262,     0,     0,     0,
       0,   359,     0,     0,   261,     0,   261,     0,     0,    77,
       0,    77,     0,     0,     0,   339,   261,     0,   261,     0,
     261,   236,   320,   237,     0,   238,   239,     5,   240,   241,
     242,     0,   243,   244,     0,   262,   245,   262,     0,     0,
       0,     0,     0,     0,   261,     0,     0,   262,     0,   262,
       0,   262,     0,     0,   246,     0,     0,     0,   247,     0,
       0,     0,     0,     0,     0,     0,   261,   261,     0,   261,
     261,     0,     0,     0,     0,   262,     0,     0,     0,   248,
       0,     0,     0,     0,     0,   261,   261,     6,     0,   261,
       0,     0,   261,     0,     0,     0,     0,   262,   262,     0,
     262,   262,     0,     0,     0,     0,     0,     0,     0,   354,
       0,     0,     0,     0,     0,     0,   262,   262,     0,     0,
     262,     0,     0,   262,    28,     5,    29,    30,     0,     0,
       0,    31,     0,     0,     0,     0,   355,     0,    32,     0,
       0,    33,    34,    35,     0,     0,     0,     0,    36,    37,
      38,     0,    39,     0,    40,     0,     0,     0,     0,   356,
      41,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      42,    98,     0,     0,     0,     0,     0,     0,     0,    43,
      44,    45,    46,    47,    48,     6,    28,     5,    29,    30,
       0,     0,     0,    31,     0,     0,     0,     0,     0,     0,
      32,     0,     0,    33,    34,    35,     0,     0,     0,     0,
      36,    37,    38,     0,    39,     0,    40,     0,     0,     0,
       0,     0,    41,     0,     0,     0,    99,     0,     0,     0,
       0,     0,    42,   101,     0,     0,     0,     0,     0,     0,
       0,    43,    44,    45,    46,    47,    48,     6,    28,     5,
      29,    30,     0,     0,     0,    31,     0,     0,     0,     0,
       0,     0,    32,     0,     0,    33,    34,    35,     0,     0,
       0,     0,    36,    37,    38,     0,    39,     0,    40,   102,
       0,     0,     0,     0,    41,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    42,   182,     0,     0,     0,     0,
       0,     0,     0,    43,    44,    45,    46,    47,    48,     6,
      28,     5,    29,    30,     0,     0,     0,    31,     0,     0,
       0,     0,     0,     0,    32,     0,     0,    33,    34,    35,
       0,     0,     0,   285,    36,    37,    38,     0,    39,   183,
      40,     0,     0,   236,     0,   237,    41,   238,   239,     5,
     240,   241,   242,     0,   243,   244,    42,     0,   245,     0,
       0,     0,     0,     0,     0,    43,    44,    45,    46,    47,
      48,     6,   288,     0,     0,     0,   246,     0,     0,     0,
     247,     0,   236,     0,   237,     0,   238,   239,     5,   240,
     241,   242,     0,   243,   244,     0,     0,   245,     0,     0,
       0,   248,     0,     0,     0,     0,   298,     0,     0,     6,
       0,     0,     0,     0,     0,   246,   236,     0,   237,   247,
     238,   239,     5,   240,   241,   242,     0,   243,   244,     0,
       0,   245,     0,     0,     0,     0,     0,     0,     0,     0,
     248,     0,   300,     0,     0,     0,     0,     0,     6,   246,
       0,     0,   236,   247,   237,     0,   238,   239,     5,   240,
     241,   242,     0,   243,   244,     0,     0,   245,     0,     0,
       0,     0,     0,     0,   248,     0,     0,     0,     0,     0,
       0,     0,     6,     0,     0,   246,     0,     0,   236,   247,
     237,   323,   238,   239,     5,   240,   241,   242,     0,   243,
     244,     0,     0,   245,     0,     0,     0,     0,     0,     0,
     248,     0,     0,     0,     0,     0,     0,     0,     6,     0,
       0,   246,   236,     0,   237,   247,   238,   239,     5,   240,
     241,   242,     0,   243,   244,     0,   236,   245,   237,     0,
     238,   239,     5,   240,   241,   242,   248,   243,   244,     0,
       0,   245,     0,     0,     6,   246,     0,     0,     0,   247,
     330,     0,     0,     0,     0,     0,     0,     0,     0,   246,
     236,     0,   237,   247,   238,   239,     5,   240,   241,   242,
     248,   243,   244,     0,     0,   245,     0,     0,     6,     0,
       0,     0,     0,     0,   248,   332,     0,    28,     5,    29,
      30,     0,     6,   246,    31,     0,     0,   247,     0,   355,
       0,    32,     0,     0,    33,    34,    35,     0,     0,     0,
       0,    36,    37,    38,     0,    39,     0,    40,   248,     0,
     370,     0,   356,    41,     0,     0,     6,     0,     0,     0,
       0,     0,     0,    42,     0,     0,     0,     0,     0,     0,
       0,     0,    43,    44,    45,    46,    47,    48,     6,    28,
       5,    29,    30,     0,     0,     0,    31,     0,     0,     0,
       0,     0,     0,    32,     0,     0,    33,    34,    35,     0,
       0,     0,     0,    36,    37,    38,     0,    39,     0,    40,
       0,     0,     0,     0,     0,    41,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    42,     0,     0,     0,     0,
       0,     0,     0,     0,    43,    44,    45,    46,    47,    48,
       6,    28,     5,    29,    30,     0,     0,     0,    31,     0,
       0,     0,     0,     0,     0,    32,     0,     0,    33,    34,
      35,     0,     0,     0,     0,    36,    37,    38,     0,   130,
       0,    40,     0,     0,     0,     0,     0,    41,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    42,   267,     0,
       0,     0,     0,     0,     0,     0,    43,    44,    45,    46,
      47,    48,     6,   107,     0,     0,     0,   108,   109,   110,
     111,     0,   112,   113,   114,     0,     0,     0,     0,     0,
       0,   349,     0,     0,     0,   115,   116,   117,   118,   119,
     120,     0,     0,   121,     0,   122,   107,   123,   124,   125,
     108,   109,   110,   111,     0,   112,   113,   114,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   115,   116,
     117,   118,   119,   120,   350,     0,   121,     0,   122,     0,
     123,   124,   125,     0,   351,   107,     0,     0,     0,   108,
     109,   110,   111,     0,   112,   113,   114,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   115,   116,   117,
     118,   119,   120,   269,     0,   121,     0,   122,     0,   123,
     124,   125,     0,     0,   107,     0,     0,     0,   108,   109,
     110,   111,     0,   112,   113,   114,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   115,   116,   117,   118,
     119,   120,   352,     0,   121,     0,   122,     0,   123,   124,
     125,     0,     0,   107,     0,     0,     0,   108,   109,   110,
     111,     0,   112,   113,   114,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   115,   116,   117,   118,   119,
     120,   375,     0,   121,     0,   122,     0,   123,   124,   125,
       0,     0,   107,     0,     0,     0,   108,   109,   110,   111,
       0,   112,   113,   114,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   115,   116,   117,   118,   119,   120,
       0,   149,   121,     0,   122,     0,   123,   124,   125,   107,
       0,     0,     0,   108,   109,   110,   111,     0,   112,   113,
     114,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   115,   116,   117,   118,   119,   120,     0,   327,   121,
       0,   122,     0,   123,   124,   125,   107,     0,   112,   113,
     108,   109,   110,   111,     0,   112,   113,   114,     0,     0,
       0,   115,   116,   117,   118,   119,   120,     0,   115,   116,
     117,   118,   119,   120,   124,   125,   121,   270,   122,     0,
     123,   124,   125,     0,   107,     0,     0,     0,   108,   109,
     110,   111,     0,   112,   113,   114,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   115,   116,   117,   118,
     119,   120,   328,     0,   121,     0,   122,   107,   123,   124,
     125,   108,   109,   110,   111,     0,   112,   113,   114,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   115,
     116,   117,   118,   119,   120,     0,     0,   121,     0,   122,
       0,   123,   124,   125,   268,     0,     0,   107,     0,     0,
       0,   108,   109,   110,   111,     0,   112,   113,   114,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   115,
     116,   117,   118,   119,   120,     0,     0,   121,     0,   122,
       0,   123,   124,   125,   271,   107,     0,     0,     0,   108,
     109,   110,   111,     0,   112,   113,   114,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   115,   116,   117,
     118,   119,   120,     0,     0,   121,     0,   122,   107,   123,
     124,   125,   108,   109,   110,   111,     0,   112,   113,   114,
       0,   153,     0,     0,     0,     0,     0,     0,     0,     0,
     115,   116,   117,   118,   119,   120,     0,     0,   121,     0,
     122,   107,   123,   124,   125,   108,   109,   110,   111,     0,
     112,   113,   114,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   115,   116,   117,   118,   119,   120,     0,
     157,   121,     0,   122,   107,   123,   124,   125,   108,   109,
     110,   111,     0,   112,   113,   114,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   115,   116,   117,   118,
     119,   120,     0,     0,   121,   188,   122,   107,   123,   124,
     125,   108,   109,   110,   111,     0,   112,   113,   114,     0,
     214,     0,     0,     0,     0,     0,     0,     0,     0,   115,
     116,   117,   118,   119,   120,     0,     0,   121,     0,   122,
     107,   123,   124,   125,   108,   109,   110,   111,     0,   112,
     113,   114,     0,     0,     0,   273,     0,     0,     0,     0,
       0,     0,   115,   116,   117,   118,   119,   120,     0,     0,
     121,     0,   122,   107,   123,   124,   125,   108,   109,   110,
     111,     0,   112,   113,   114,     0,   314,     0,     0,     0,
       0,     0,     0,     0,     0,   115,   116,   117,   118,   119,
     120,     0,     0,   121,     0,   122,   107,   123,   124,   125,
     108,   109,   110,   111,     0,   112,   113,   114,     0,     0,
       0,     0,     0,     0,   372,     0,     0,     0,   115,   116,
     117,   118,   119,   120,     0,     0,   121,     0,   122,   107,
     123,   124,   125,   108,   109,   110,   111,     0,   112,   113,
     114,     0,     0,     0,     0,     0,   373,     0,     0,     0,
       0,   115,   116,   117,   118,   119,   120,     0,     0,   121,
       0,   122,   107,   123,   124,   125,   108,   109,   110,   111,
       0,   112,   113,   114,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   115,   116,   117,   118,   119,   120,
       0,     0,   121,     0,   122,     0,   123,   124,   125,   108,
     109,   110,     0,     0,   112,   113,   114,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   115,   116,   117,
     118,   119,   120,     0,     0,     0,     0,     0,     0,   123,
     124,   125,   108,     0,   110,     0,     0,   112,   113,   114,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     115,   116,   117,   118,   119,   120,     0,     0,     0,     0,
     108,     0,   123,   124,   125,   112,   113,   114,     0,     0,
       0,   112,   113,   114,     0,     0,     0,     0,   115,   116,
     117,   118,   119,   120,   115,   116,   117,   118,   119,   120,
     123,   124,   125,     0,     0,     0,   123,   124,   125
  };

  const short int
  Parser::yycheck_[] =
  {
       7,    19,     3,     1,   138,     0,    29,    30,    44,    32,
       1,    17,    17,    17,    17,    17,   177,    43,    49,    17,
      14,    17,    53,     3,    31,   142,    17,    56,   145,    36,
      37,    38,    39,    40,    63,    45,    53,    63,    55,    50,
      44,    46,    48,    53,    46,    46,    45,    41,    46,    62,
       2,    44,    17,   214,    53,    46,    62,   126,   201,    62,
      43,   130,    14,    15,    16,    17,    18,    19,    86,    50,
      43,    77,    77,    77,    77,    77,    28,    29,    30,    77,
      32,    77,   199,   237,    45,   202,    77,    17,    17,    41,
      42,    47,    99,   247,   248,   229,    47,    53,    53,   242,
     217,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,    63,   122,   123,   124,   125,   126,
      41,    42,    74,   130,    76,     0,     1,    49,    63,     4,
       5,     6,     7,     8,    86,    56,    57,    58,    59,   146,
     147,   148,   149,   150,   287,   279,   289,   264,   265,   156,
     157,    47,    59,    48,    45,   107,   299,    53,   301,     1,
     303,    47,     4,     5,     6,     7,     8,    53,    47,   121,
      53,    46,    54,    47,    53,    56,   194,    47,    60,    53,
      45,   188,   189,    53,   327,   137,   138,    63,    43,    56,
     142,    43,    65,   145,   311,    63,   313,     4,     5,     6,
       7,     8,    12,    14,    46,    43,   349,   350,    17,   352,
     353,   218,    17,    49,   232,   222,   239,   240,   241,    56,
      57,    58,    59,    70,    10,   368,   369,    48,    48,   372,
       9,    55,   375,    25,    48,    50,    49,   244,   245,    20,
     143,    49,   194,   284,    50,   358,   217,   199,   200,    82,
     202,   190,   361,   207,   229,   207,    74,    -1,    -1,    -1,
     267,   268,   269,   270,   271,   217,    -1,    -1,   201,    -1,
      -1,    -1,    -1,    -1,   281,    -1,    -1,   229,    -1,    -1,
     232,    -1,    -1,    -1,    -1,    -1,    -1,   239,   240,   241,
      -1,    -1,    -1,    -1,    -1,   302,    -1,    -1,    -1,   201,
      -1,    -1,    -1,   236,   237,    -1,    -1,    -1,    -1,   242,
     243,    -1,   264,   265,   247,   248,    -1,   324,   325,   326,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   279,    -1,    -1,
      -1,    -1,   284,    -1,   236,   237,    -1,   344,   345,    -1,
     242,   243,    -1,    -1,   351,   247,   248,    -1,    -1,    -1,
      -1,   358,    -1,    -1,   287,    -1,   289,    -1,    -1,   311,
      -1,   313,    -1,    -1,    -1,   317,   299,    -1,   301,    -1,
     303,    11,    12,    13,    -1,    15,    16,    17,    18,    19,
      20,    -1,    22,    23,    -1,   287,    26,   289,    -1,    -1,
      -1,    -1,    -1,    -1,   327,    -1,    -1,   299,    -1,   301,
      -1,   303,    -1,    -1,    44,    -1,    -1,    -1,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   349,   350,    -1,   352,
     353,    -1,    -1,    -1,    -1,   327,    -1,    -1,    -1,    69,
      -1,    -1,    -1,    -1,    -1,   368,   369,    77,    -1,   372,
      -1,    -1,   375,    -1,    -1,    -1,    -1,   349,   350,    -1,
     352,   353,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,    -1,    -1,    -1,    -1,    -1,   368,   369,    -1,    -1,
     372,    -1,    -1,   375,    16,    17,    18,    19,    -1,    -1,
      -1,    23,    -1,    -1,    -1,    -1,    28,    -1,    30,    -1,
      -1,    33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,
      42,    -1,    44,    -1,    46,    -1,    -1,    -1,    -1,    51,
      52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      62,     1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      72,    73,    74,    75,    76,    77,    16,    17,    18,    19,
      -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    -1,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    -1,    44,    -1,    46,    -1,    -1,    -1,
      -1,    -1,    52,    -1,    -1,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    62,     1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    71,    72,    73,    74,    75,    76,    77,    16,    17,
      18,    19,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    -1,    -1,    33,    34,    35,    -1,    -1,
      -1,    -1,    40,    41,    42,    -1,    44,    -1,    46,    47,
      -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    62,     1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    71,    72,    73,    74,    75,    76,    77,
      16,    17,    18,    19,    -1,    -1,    -1,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    -1,    -1,    33,    34,    35,
      -1,    -1,    -1,     1,    40,    41,    42,    -1,    44,    45,
      46,    -1,    -1,    11,    -1,    13,    52,    15,    16,    17,
      18,    19,    20,    -1,    22,    23,    62,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,
      76,    77,     1,    -1,    -1,    -1,    44,    -1,    -1,    -1,
      48,    -1,    11,    -1,    13,    -1,    15,    16,    17,    18,
      19,    20,    -1,    22,    23,    -1,    -1,    26,    -1,    -1,
      -1,    69,    -1,    -1,    -1,    -1,     1,    -1,    -1,    77,
      -1,    -1,    -1,    -1,    -1,    44,    11,    -1,    13,    48,
      15,    16,    17,    18,    19,    20,    -1,    22,    23,    -1,
      -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      69,    -1,     1,    -1,    -1,    -1,    -1,    -1,    77,    44,
      -1,    -1,    11,    48,    13,    -1,    15,    16,    17,    18,
      19,    20,    -1,    22,    23,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    77,    -1,    -1,    44,    -1,    -1,    11,    48,
      13,    14,    15,    16,    17,    18,    19,    20,    -1,    22,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,
      -1,    44,    11,    -1,    13,    48,    15,    16,    17,    18,
      19,    20,    -1,    22,    23,    -1,    11,    26,    13,    -1,
      15,    16,    17,    18,    19,    20,    69,    22,    23,    -1,
      -1,    26,    -1,    -1,    77,    44,    -1,    -1,    -1,    48,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,
      11,    -1,    13,    48,    15,    16,    17,    18,    19,    20,
      69,    22,    23,    -1,    -1,    26,    -1,    -1,    77,    -1,
      -1,    -1,    -1,    -1,    69,    70,    -1,    16,    17,    18,
      19,    -1,    77,    44,    23,    -1,    -1,    48,    -1,    28,
      -1,    30,    -1,    -1,    33,    34,    35,    -1,    -1,    -1,
      -1,    40,    41,    42,    -1,    44,    -1,    46,    69,    -1,
      49,    -1,    51,    52,    -1,    -1,    77,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    71,    72,    73,    74,    75,    76,    77,    16,
      17,    18,    19,    -1,    -1,    -1,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    -1,    -1,    33,    34,    35,    -1,
      -1,    -1,    -1,    40,    41,    42,    -1,    44,    -1,    46,
      -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,    76,
      77,    16,    17,    18,    19,    -1,    -1,    -1,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    -1,    44,
      -1,    46,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    72,    73,    74,
      75,    76,    77,    32,    -1,    -1,    -1,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    17,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    -1,    -1,    62,    -1,    64,    32,    66,    67,    68,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    21,    -1,    62,    -1,    64,    -1,
      66,    67,    68,    -1,    31,    32,    -1,    -1,    -1,    36,
      37,    38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    21,    -1,    62,    -1,    64,    -1,    66,
      67,    68,    -1,    -1,    32,    -1,    -1,    -1,    36,    37,
      38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    21,    -1,    62,    -1,    64,    -1,    66,    67,
      68,    -1,    -1,    32,    -1,    -1,    -1,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    21,    -1,    62,    -1,    64,    -1,    66,    67,    68,
      -1,    -1,    32,    -1,    -1,    -1,    36,    37,    38,    39,
      -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      -1,    24,    62,    -1,    64,    -1,    66,    67,    68,    32,
      -1,    -1,    -1,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    -1,    24,    62,
      -1,    64,    -1,    66,    67,    68,    32,    -1,    41,    42,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    -1,    54,    55,
      56,    57,    58,    59,    67,    68,    62,    25,    64,    -1,
      66,    67,    68,    -1,    32,    -1,    -1,    -1,    36,    37,
      38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    27,    -1,    62,    -1,    64,    32,    66,    67,
      68,    36,    37,    38,    39,    -1,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    -1,    -1,    62,    -1,    64,
      -1,    66,    67,    68,    29,    -1,    -1,    32,    -1,    -1,
      -1,    36,    37,    38,    39,    -1,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    -1,    -1,    62,    -1,    64,
      -1,    66,    67,    68,    31,    32,    -1,    -1,    -1,    36,
      37,    38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    -1,    -1,    62,    -1,    64,    32,    66,
      67,    68,    36,    37,    38,    39,    -1,    41,    42,    43,
      -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    -1,    -1,    62,    -1,
      64,    32,    66,    67,    68,    36,    37,    38,    39,    -1,
      41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    -1,
      61,    62,    -1,    64,    32,    66,    67,    68,    36,    37,
      38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    -1,    -1,    62,    63,    64,    32,    66,    67,
      68,    36,    37,    38,    39,    -1,    41,    42,    43,    -1,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    -1,    -1,    62,    -1,    64,
      32,    66,    67,    68,    36,    37,    38,    39,    -1,    41,
      42,    43,    -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    -1,    -1,
      62,    -1,    64,    32,    66,    67,    68,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    -1,    -1,    62,    -1,    64,    32,    66,    67,    68,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    -1,    -1,    62,    -1,    64,    32,
      66,    67,    68,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    -1,    -1,    62,
      -1,    64,    32,    66,    67,    68,    36,    37,    38,    39,
      -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      -1,    -1,    62,    -1,    64,    -1,    66,    67,    68,    36,
      37,    38,    -1,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      67,    68,    36,    -1,    38,    -1,    -1,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,
      36,    -1,    66,    67,    68,    41,    42,    43,    -1,    -1,
      -1,    41,    42,    43,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    54,    55,    56,    57,    58,    59,
      66,    67,    68,    -1,    -1,    -1,    66,    67,    68
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    46,    83,    84,    17,    77,   151,   158,   159,
     160,   161,     0,     1,     4,     5,     6,     7,     8,    46,
      85,    86,    87,    88,    89,    90,    91,    92,    16,    18,
      19,    23,    30,    33,    34,    35,    40,    41,    42,    44,
      46,    52,    62,    71,    72,    73,    74,    75,    76,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   151,    47,    53,    48,    62,   151,   152,   153,
     151,   151,   151,   151,   158,    86,    46,   151,   154,   155,
     156,   156,   156,   111,   156,   111,   111,   111,     1,    56,
     111,     1,    47,   110,   111,   152,   151,    32,    36,    37,
      38,    39,    41,    42,    43,    54,    55,    56,    57,    58,
      59,    62,    64,    66,    67,    68,    44,   140,     3,   159,
      44,   111,   141,   148,   149,   150,   151,    62,    44,   145,
      43,   145,    50,    47,   158,    50,    43,    17,    17,    24,
      17,    45,   111,    45,    47,    47,    53,    61,   135,   136,
     137,   138,   139,   152,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   151,   111,   111,
     111,   111,     1,    45,   110,   111,   110,   111,    63,    63,
      53,    49,   151,     1,    46,   144,   151,   155,   157,    63,
      48,    43,    63,   135,   142,   143,    87,    47,   135,   111,
     111,   111,   111,   111,    45,   111,   111,    54,    60,   140,
      45,    45,    53,   111,   111,   149,    45,   158,    45,    53,
     135,     1,    46,    93,    94,   151,    11,    13,    15,    16,
      18,    19,    20,    22,    23,    26,    44,    48,    69,    95,
      97,    98,    99,   102,   103,   104,   105,   106,   107,   108,
     109,   115,   116,   135,    56,    63,   154,    17,    29,    21,
      25,    31,   140,    47,   134,   135,   143,   111,   111,    47,
     157,    43,   158,    49,    53,     1,    95,    96,     1,    96,
     156,   156,   156,    95,   115,   116,   111,   111,     1,    96,
       1,    96,    65,    43,   135,   135,   111,   111,   111,   111,
     111,    53,    55,    63,    45,   155,   111,    47,    93,    12,
      12,    95,    14,    14,    43,    17,    17,    24,    27,    49,
      49,    70,    70,   111,    95,    10,   146,   135,   135,   151,
     111,   111,   111,    95,    48,    48,     9,   147,    55,    17,
      21,    31,    21,    25,     1,    28,    51,   100,   101,   111,
     111,    48,    95,    95,   111,    95,    95,    49,    50,    50,
      49,   100,    50,    49,   150,    21,    95,    95,    95,    49,
      95
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    82,    83,    84,    84,    85,    85,    86,    86,    86,
      87,    87,    87,    87,    88,    89,    90,    90,    91,    91,
      92,    92,    93,    93,    93,    94,    94,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    96,    96,
      97,    98,    98,    99,    99,   100,   100,   100,   101,   101,
     102,   103,   103,   104,   105,   106,   106,   106,   106,   107,
     107,   107,   107,   108,   109,   109,   109,   109,   110,   110,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   113,   114,   114,   114,   115,   115,   116,
     117,   117,   117,   118,   119,   120,   121,   122,   123,   123,
     123,   124,   125,   125,   125,   125,   125,   125,   125,   125,
     126,   127,   127,   128,   129,   130,   131,   131,   132,   133,
     134,   134,   135,   135,   135,   135,   136,   137,   138,   139,
     140,   140,   140,   141,   142,   142,   143,   143,   144,   144,
     145,   145,   145,   146,   146,   147,   147,   148,   148,   149,
     149,   149,   150,   150,   151,   151,   152,   152,   153,   153,
     154,   154,   155,   156,   156,   157,   157,   158,   158,   159,
     159,   160,   161
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     4,     1,     2,     1,     4,     1,     1,
       1,     1,     1,     1,     6,     7,     5,     7,     8,     1,
       2,     4,     1,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     4,     6,     6,     6,     3,     3,     3,     2,     1,
       6,     6,     8,     6,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     3,     1,     1,     1,     1,     2,     5,
       3,     4,     2,     6,     6,     6,     6,     6,     2,     3,
       3,     5,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       3,     1,     1,     1,     1,     1,     1,     4,     6,     3,
       3,     3,     2,     5,     3,     1,     1,     0,     3,     1,
       3,     3,     0,     4,     0,     4,     0,     3,     1,     1,
       3,     3,     1,     0,     1,     1,     1,     2,     3,     1,
       1,     1,     3,     4,     1,     4,     1,     3,     1,     1,
       1,     1,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"CASM\"", "\"init\"",
  "\"derived\"", "\"enumeration\"", "\"rule\"", "\"function\"",
  "\"initially\"", "\"defined\"", "\"seq\"", "\"endseq\"", "\"par\"",
  "\"endpar\"", "\"skip\"", "\"let\"", "\"in\"", "\"forall\"",
  "\"choose\"", "\"iterate\"", "\"do\"", "\"call\"", "\"if\"", "\"then\"",
  "\"else\"", "\"case\"", "\"of\"", "\"default\"", "\"holds\"",
  "\"exists\"", "\"with\"", "\"as\"", "\"undef\"", "\"false\"", "\"true\"",
  "\"and\"", "\"or\"", "\"xor\"", "\"implies\"", "\"not\"", "\"+\"",
  "\"-\"", "\"=\"", "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"",
  "\":\"", "\"_\"", "\"@\"", "\",\"", "\"<\"", "\">\"", "\"*\"", "\"/\"",
  "\"%\"", "\"^\"", "\"'\"", "\"..\"", "\".\"", "\"->\"", "\"=>\"",
  "\":=\"", "\"!=\"", "\"<=\"", "\">=\"", "\"{|\"", "\"|}\"", "\"binary\"",
  "\"hexadecimal\"", "\"integer\"", "\"rational\"", "\"decimal\"",
  "\"string\"", "\"identifier\"", "ABSOLUTE_PATH", "UPLUS", "UMINUS",
  "CALL_WITHOUT_ARGS", "$accept", "Specification", "Header", "Definitions",
  "AttributedDefinition", "Definition", "EnumerationDefinition",
  "DerivedDefinition", "RuleDefinition", "FunctionDefinition",
  "ProgramFunctionDefinition", "EnumeratorDefinition", "Enumerators",
  "Rule", "Rules", "SkipRule", "ConditionalRule", "CaseRule", "CaseLabel",
  "CaseLabels", "LetRule", "ForallRule", "ChooseRule", "IterateRule",
  "BlockRule", "SequenceRule", "UpdateRule", "CallRule", "Terms", "Term",
  "Expression", "TypeCastingExpression", "CallExpression",
  "DirectCallExpression", "IndirectCallExpression", "MethodCallExpression",
  "LetExpression", "ConditionalExpression", "ChooseExpression",
  "UniversalQuantifierExpression", "ExistentialQuantifierExpression",
  "List", "Range", "Literal", "UndefinedLiteral", "BooleanLiteral",
  "IntegerLiteral", "RationalLiteral", "DecimalLiteral", "BitLiteral",
  "StringLiteral", "ReferenceLiteral", "Types", "Type", "BasicType",
  "ComposedType", "RelationType", "FixedSizedType", "Arguments",
  "TwoOrMoreArguments", "FunctionParameters", "MaybeFunctionParameters",
  "Parameters", "MaybeParameters", "MaybeDefined", "MaybeInitially",
  "Initializers", "Initializer", "MaybeInitializers", "Identifier",
  "IdentifierPath", "DotSeparatedIdentifiers", "Variable", "TypedVariable",
  "AttributedVariable", "TypedAttributedVariable", "Attributes",
  "Attribute", "BasicAttribute", "ExpressionAttribute", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   381,   381,   390,   396,   404,   410,   420,   426,   430,
     438,   442,   446,   450,   458,   466,   474,   479,   488,   504,
     512,   535,   553,   557,   563,   571,   577,   591,   595,   599,
     603,   607,   611,   615,   619,   623,   627,   631,   639,   645,
     655,   663,   667,   675,   679,   687,   691,   695,   703,   709,
     719,   727,   731,   739,   747,   755,   759,   763,   768,   777,
     781,   785,   790,   799,   809,   813,   817,   821,   833,   839,
     849,   853,   857,   861,   865,   869,   873,   877,   881,   885,
     889,   901,   905,   909,   913,   917,   921,   925,   929,   933,
     937,   941,   945,   949,   953,   957,   961,   965,   969,   973,
     977,   981,   985,   993,  1001,  1005,  1009,  1017,  1024,  1034,
    1042,  1047,  1052,  1062,  1070,  1078,  1086,  1094,  1102,  1107,
    1111,  1119,  1131,  1135,  1139,  1143,  1147,  1151,  1155,  1159,
    1167,  1175,  1180,  1189,  1205,  1221,  1237,  1249,  1265,  1281,
    1293,  1299,  1309,  1313,  1317,  1321,  1329,  1337,  1345,  1353,
    1365,  1369,  1373,  1382,  1396,  1402,  1412,  1416,  1424,  1430,
    1440,  1444,  1448,  1460,  1464,  1472,  1476,  1484,  1490,  1500,
    1508,  1518,  1529,  1533,  1545,  1549,  1557,  1561,  1571,  1577,
    1591,  1595,  1604,  1612,  1618,  1626,  1632,  1644,  1650,  1659,
    1663,  1671,  1679
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 49 "../../obj/src/GrammarParser.yy" // lalr1.cc:1167
} // libcasm_fe
#line 4067 "GrammarParser.cpp" // lalr1.cc:1167
#line 1685 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


void Parser::error( const SourceLocation& location, const std::string& message )
{
    log.error( {location}, message, Code::SyntaxError );
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
