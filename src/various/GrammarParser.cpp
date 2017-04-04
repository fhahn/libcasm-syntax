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
#line 67 "../../obj/src/GrammarParser.yy" // lalr1.cc:413

    #include "src/Location.h"
    #include "src/Lexer.h"
    #include "src/Exceptions.h"
    #include "src/Logger.h"

    #include "../stdhl/cpp/Type.h"

    #undef yylex
    #define yylex lexer.nextToken

    static BasicType::Ptr createVoidType( Location& sourceLocation )
    {
        const auto type = libstdhl::get< libcasm_ir::VoidType >();
        const auto name = Ast::make< IdentifierNode >( sourceLocation, type->description() );
        const auto node = Ast::make< BasicType >( sourceLocation, name );
        node->setType( type );
        return node;
    }

    static BasicType::Ptr createRuleRefType( Location& sourceLocation )
    {
        const auto type = libstdhl::get< libcasm_ir::RuleReferenceType >();
        const auto name = Ast::make< IdentifierNode >( sourceLocation, type->description() );
        const auto node = Ast::make< BasicType >( sourceLocation, name );
        node->setType( type );
        return node;
    }

    static BasicType::Ptr createAgentType( Location& sourceLocation )
    {
        const auto name = Ast::make< IdentifierNode >( sourceLocation, "Agent" );
        const auto node = Ast::make< BasicType >( sourceLocation, name );
        return node;
    }

    static FunctionDefinition::Ptr createProgramFunction( Location& sourceLocation )
    {
        const auto agentType = createAgentType( sourceLocation );
        const auto ruleRefType = createRuleRefType( sourceLocation );

        const auto argTypes = Ast::make< Types >( sourceLocation );
        argTypes->add( agentType );

        const auto program = Ast::make< IdentifierNode >( sourceLocation, "program" );
        return Ast::make< FunctionDefinition >( sourceLocation, program, argTypes, ruleRefType );
    }

    static DirectCallExpression::Ptr createSelfBuiltinCall( Location& sourceLocation )
    {
        const auto self = libcasm_fe::Ast::make< IdentifierNode >( sourceLocation, "self" );
        const auto arguments = libcasm_fe::Ast::make< Expressions >( sourceLocation );
        return libcasm_fe::Ast::make< DirectCallExpression >( sourceLocation, self, arguments );
    }

    static Rule::Ptr wrapInBlockRule( const Rule::Ptr& rule )
    {
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

#line 123 "GrammarParser.cpp" // lalr1.cc:413


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

#line 31 "../../obj/src/GrammarParser.yy" // lalr1.cc:479
namespace libcasm_fe {
#line 209 "GrammarParser.cpp" // lalr1.cc:479

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
  Parser::Parser (Logger& log_yyarg, Lexer& lexer_yyarg, const std::string& filePath_yyarg, Specification::Ptr& result_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      log (log_yyarg),
      lexer (lexer_yyarg),
      filePath (filePath_yyarg),
      result (result_yyarg)
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
      case 139: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 140: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 141: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case 99: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 135: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 138: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 130: // CaseLabel
        value.move< Case::Ptr > (that.value);
        break;

      case 129: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 131: // CaseLabels
        value.move< Cases::Ptr > (that.value);
        break;

      case 100: // ComposedType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 121: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 128: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case 79: // Definition
      case 80: // AttributedDefinition
        value.move< Definition::Ptr > (that.value);
        break;

      case 81: // Definitions
        value.move< Definitions::Ptr > (that.value);
        break;

      case 91: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (that.value);
        break;

      case 119: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 92: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 123: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 84: // MaybeDefined
      case 103: // Atom
      case 112: // Term
      case 113: // Expression
        value.move< Expression::Ptr > (that.value);
        break;

      case 142: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case 116: // Terms
      case 117: // Arguments
      case 118: // TwoOrMoreArguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 101: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 133: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 82: // FunctionDefinition
      case 87: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 93: // Identifier
        value.move< IdentifierNode::Ptr > (that.value);
        break;

      case 120: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 134: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 132: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 115: // List
        value.move< ListExpression::Ptr > (that.value);
        break;

      case 94: // Identifiers
        value.move< NodeList< IdentifierNode >::Ptr > (that.value);
        break;

      case 83: // MaybeInitially
      case 89: // Initializers
      case 90: // MaybeInitializers
        value.move< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 96: // Parameters
      case 97: // MaybeParameters
        value.move< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 114: // Range
        value.move< RangeExpression::Ptr > (that.value);
        break;

      case 125: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 124: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 111: // RuleReference
        value.move< RuleReferenceAtom::Ptr > (that.value);
        break;

      case 126: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 136: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 127: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 78: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 98: // Type
        value.move< Type::Ptr > (that.value);
        break;

      case 85: // FunctionParameters
      case 86: // MaybeFunctionParameters
      case 102: // Types
        value.move< Types::Ptr > (that.value);
        break;

      case 104: // Undefined
        value.move< UndefAtom::Ptr > (that.value);
        break;

      case 122: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 88: // Initializer
      case 137: // UpdateRule
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 105: // Boolean
      case 106: // String
      case 107: // BitNumber
      case 108: // IntegerNumber
      case 109: // FloatingNumber
      case 110: // RationalNumber
        value.move< ValueAtom::Ptr > (that.value);
        break;

      case 95: // Variable
        value.move< VariableDefinition::Ptr > (that.value);
        break;

      case 67: // "binary"
      case 68: // "hexadecimal"
      case 69: // "integer"
      case 70: // "rational"
      case 71: // "floating"
      case 72: // "string"
      case 73: // "identifier"
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
      case 139: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case 140: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case 141: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (that.value);
        break;

      case 99: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 135: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 138: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 130: // CaseLabel
        value.copy< Case::Ptr > (that.value);
        break;

      case 129: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 131: // CaseLabels
        value.copy< Cases::Ptr > (that.value);
        break;

      case 100: // ComposedType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 121: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 128: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (that.value);
        break;

      case 79: // Definition
      case 80: // AttributedDefinition
        value.copy< Definition::Ptr > (that.value);
        break;

      case 81: // Definitions
        value.copy< Definitions::Ptr > (that.value);
        break;

      case 91: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (that.value);
        break;

      case 119: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 92: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 123: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 84: // MaybeDefined
      case 103: // Atom
      case 112: // Term
      case 113: // Expression
        value.copy< Expression::Ptr > (that.value);
        break;

      case 142: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (that.value);
        break;

      case 116: // Terms
      case 117: // Arguments
      case 118: // TwoOrMoreArguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 101: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 133: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 82: // FunctionDefinition
      case 87: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 93: // Identifier
        value.copy< IdentifierNode::Ptr > (that.value);
        break;

      case 120: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 134: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 132: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case 115: // List
        value.copy< ListExpression::Ptr > (that.value);
        break;

      case 94: // Identifiers
        value.copy< NodeList< IdentifierNode >::Ptr > (that.value);
        break;

      case 83: // MaybeInitially
      case 89: // Initializers
      case 90: // MaybeInitializers
        value.copy< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 96: // Parameters
      case 97: // MaybeParameters
        value.copy< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 114: // Range
        value.copy< RangeExpression::Ptr > (that.value);
        break;

      case 125: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 124: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 111: // RuleReference
        value.copy< RuleReferenceAtom::Ptr > (that.value);
        break;

      case 126: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 136: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 127: // SkipRule
        value.copy< SkipRule::Ptr > (that.value);
        break;

      case 78: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 98: // Type
        value.copy< Type::Ptr > (that.value);
        break;

      case 85: // FunctionParameters
      case 86: // MaybeFunctionParameters
      case 102: // Types
        value.copy< Types::Ptr > (that.value);
        break;

      case 104: // Undefined
        value.copy< UndefAtom::Ptr > (that.value);
        break;

      case 122: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 88: // Initializer
      case 137: // UpdateRule
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case 105: // Boolean
      case 106: // String
      case 107: // BitNumber
      case 108: // IntegerNumber
      case 109: // FloatingNumber
      case 110: // RationalNumber
        value.copy< ValueAtom::Ptr > (that.value);
        break;

      case 95: // Variable
        value.copy< VariableDefinition::Ptr > (that.value);
        break;

      case 67: // "binary"
      case 68: // "hexadecimal"
      case 69: // "integer"
      case 70: // "rational"
      case 71: // "floating"
      case 72: // "string"
      case 73: // "identifier"
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
      case 139: // Attribute
        yylhs.value.build< Attribute::Ptr > ();
        break;

      case 140: // Attributes
        yylhs.value.build< Attributes::Ptr > ();
        break;

      case 141: // BasicAttribute
        yylhs.value.build< BasicAttribute::Ptr > ();
        break;

      case 99: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 135: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 138: // CallRule
        yylhs.value.build< CallRule::Ptr > ();
        break;

      case 130: // CaseLabel
        yylhs.value.build< Case::Ptr > ();
        break;

      case 129: // CaseRule
        yylhs.value.build< CaseRule::Ptr > ();
        break;

      case 131: // CaseLabels
        yylhs.value.build< Cases::Ptr > ();
        break;

      case 100: // ComposedType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 121: // ConditionalExpression
        yylhs.value.build< ConditionalExpression::Ptr > ();
        break;

      case 128: // ConditionalRule
        yylhs.value.build< ConditionalRule::Ptr > ();
        break;

      case 79: // Definition
      case 80: // AttributedDefinition
        yylhs.value.build< Definition::Ptr > ();
        break;

      case 81: // Definitions
        yylhs.value.build< Definitions::Ptr > ();
        break;

      case 91: // DerivedDefinition
        yylhs.value.build< DerivedDefinition::Ptr > ();
        break;

      case 119: // DirectCallExpression
        yylhs.value.build< DirectCallExpression::Ptr > ();
        break;

      case 92: // EnumerationDefinition
        yylhs.value.build< EnumerationDefinition::Ptr > ();
        break;

      case 123: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 84: // MaybeDefined
      case 103: // Atom
      case 112: // Term
      case 113: // Expression
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 142: // ExpressionAttribute
        yylhs.value.build< ExpressionAttribute::Ptr > ();
        break;

      case 116: // Terms
      case 117: // Arguments
      case 118: // TwoOrMoreArguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 101: // FixedSizedType
        yylhs.value.build< FixedSizedType::Ptr > ();
        break;

      case 133: // ForallRule
        yylhs.value.build< ForallRule::Ptr > ();
        break;

      case 82: // FunctionDefinition
      case 87: // ProgramFunctionDefinition
        yylhs.value.build< FunctionDefinition::Ptr > ();
        break;

      case 93: // Identifier
        yylhs.value.build< IdentifierNode::Ptr > ();
        break;

      case 120: // IndirectCallExpression
        yylhs.value.build< IndirectCallExpression::Ptr > ();
        break;

      case 134: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 132: // LetRule
        yylhs.value.build< LetRule::Ptr > ();
        break;

      case 115: // List
        yylhs.value.build< ListExpression::Ptr > ();
        break;

      case 94: // Identifiers
        yylhs.value.build< NodeList< IdentifierNode >::Ptr > ();
        break;

      case 83: // MaybeInitially
      case 89: // Initializers
      case 90: // MaybeInitializers
        yylhs.value.build< NodeList< UpdateRule >::Ptr > ();
        break;

      case 96: // Parameters
      case 97: // MaybeParameters
        yylhs.value.build< NodeList< VariableDefinition >::Ptr > ();
        break;

      case 114: // Range
        yylhs.value.build< RangeExpression::Ptr > ();
        break;

      case 125: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 124: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 111: // RuleReference
        yylhs.value.build< RuleReferenceAtom::Ptr > ();
        break;

      case 126: // Rules
        yylhs.value.build< Rules::Ptr > ();
        break;

      case 136: // SequenceRule
        yylhs.value.build< SequenceRule::Ptr > ();
        break;

      case 127: // SkipRule
        yylhs.value.build< SkipRule::Ptr > ();
        break;

      case 78: // Specification
        yylhs.value.build< Specification::Ptr > ();
        break;

      case 98: // Type
        yylhs.value.build< Type::Ptr > ();
        break;

      case 85: // FunctionParameters
      case 86: // MaybeFunctionParameters
      case 102: // Types
        yylhs.value.build< Types::Ptr > ();
        break;

      case 104: // Undefined
        yylhs.value.build< UndefAtom::Ptr > ();
        break;

      case 122: // UniversalQuantifierExpression
        yylhs.value.build< UniversalQuantifierExpression::Ptr > ();
        break;

      case 88: // Initializer
      case 137: // UpdateRule
        yylhs.value.build< UpdateRule::Ptr > ();
        break;

      case 105: // Boolean
      case 106: // String
      case 107: // BitNumber
      case 108: // IntegerNumber
      case 109: // FloatingNumber
      case 110: // RationalNumber
        yylhs.value.build< ValueAtom::Ptr > ();
        break;

      case 95: // Variable
        yylhs.value.build< VariableDefinition::Ptr > ();
        break;

      case 67: // "binary"
      case 68: // "hexadecimal"
      case 69: // "integer"
      case 70: // "rational"
      case 71: // "floating"
      case 72: // "string"
      case 73: // "identifier"
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
#line 329 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::string& fileName = filePath.substr( filePath.find_last_of( "/\\" ) + 1 );
      const std::string& name = fileName.substr( 0, fileName.rfind( "." ) );

      const auto specificationName = make< IdentifierNode >( yylhs.location, name );
      result = Ast::make< Specification >( yylhs.location, specificationName, yystack_[0].value.as< Definitions::Ptr > () );
  }
#line 1241 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 341 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1249 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 345 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1257 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 349 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1265 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 353 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1273 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 361 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = yystack_[0].value.as< Definition::Ptr > ();
      definition->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< Definition::Ptr > () = definition;
  }
#line 1283 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 367 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< Definition::Ptr > ();
  }
#line 1291 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 375 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1301 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 381 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1311 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 391 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto identifier = yystack_[6].value.as< IdentifierNode::Ptr > ();

      auto function = Ast::make< FunctionDefinition >( yylhs.location, identifier, yystack_[4].value.as< Types::Ptr > (), yystack_[2].value.as< Type::Ptr > () );
      function->setDefaultValue( yystack_[1].value.as< Expression::Ptr > () );

      // apply the name of the function declaration to the initializer functions
      auto initializers = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
      for (auto& initializer : *initializers) {
           initializer->function()->setIdentifier( identifier );
      }
      function->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = function;
  }
#line 1331 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 407 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1339 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 415 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1347 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 419 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1355 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 427 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1363 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 431 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 1371 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 439 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1381 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 445 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1391 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 455 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 1399 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 459 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 1407 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 467 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto programDefinition = createProgramFunction( yylhs.location );

      auto arguments = libcasm_fe::Ast::make< Expressions >( yylhs.location );

      // single execution agent case, use 'self' built-in!
      const auto self = createSelfBuiltinCall( yylhs.location );
      arguments->add( self );

      const auto program = libcasm_fe::Ast::make< DirectCallExpression >(
          yylhs.location, programDefinition->identifier(), arguments );

      const auto ruleReference = Ast::make< RuleReferenceAtom >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > () );

      auto initializers = Ast::make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( Ast::make< UpdateRule >( yylhs.location, program, ruleReference ) );
      programDefinition->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = programDefinition;
  }
#line 1432 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 488 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto programDefinition = createProgramFunction( yylhs.location );

      // apply the name of the program declaration to the initializer functions
      auto initializers = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
      for (auto& initializer : *initializers) {
          initializer->function()->setIdentifier( programDefinition->identifier() );
      }
      programDefinition->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = programDefinition;
  }
#line 1449 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 505 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = Ast::make< IdentifierNode >( yylhs.location, std::string() );
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, unknown, arguments );

      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1462 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 514 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[2].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = Ast::make< IdentifierNode >( yylhs.location, std::string() );
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, unknown, arguments );

      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1477 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 525 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = Ast::make< IdentifierNode >( yylhs.location, std::string() );
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, unknown, yystack_[2].value.as< Expressions::Ptr > () );

      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1489 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 537 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< NodeList< UpdateRule >::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1499 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 543 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = Ast::make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1509 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 553 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1517 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 557 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1525 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 565 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1533 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 573 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< NodeList< IdentifierNode >::Ptr > () );
  }
#line 1541 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 581 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierNode::Ptr > () = Ast::make< IdentifierNode >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1549 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 589 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< NodeList< IdentifierNode >::Ptr > ();
      identifiers->add( yystack_[0].value.as< IdentifierNode::Ptr > () );
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = identifiers;
  }
#line 1559 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 595 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< NodeList< IdentifierNode > >( yylhs.location );
      identifiers->add( yystack_[0].value.as< IdentifierNode::Ptr > () );
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = identifiers;
  }
#line 1569 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 605 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Type::Ptr > () );
  }
#line 1577 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 609 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > (), unresolvedType );
  }
#line 1586 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 618 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1596 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 624 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1606 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 634 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = yystack_[1].value.as< NodeList< VariableDefinition >::Ptr > ();
  }
#line 1614 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 638 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 1622 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 646 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 1630 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 650 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 1638 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 654 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 1646 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 662 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > () );
  }
#line 1654 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 670 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 1662 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 678 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1670 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 686 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1680 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 692 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1690 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 702 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RuleReferenceAtom::Ptr > ();
  }
#line 1698 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 706 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1706 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 710 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1714 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 714 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1722 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 718 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1730 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 722 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1738 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 726 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UndefAtom::Ptr > ();
  }
#line 1746 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 730 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1754 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 738 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefAtom::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 1762 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 746 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1771 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 751 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1780 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 760 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::get< libcasm_ir::StringConstant >( yystack_[0].value.as< std::string > () );
          yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 1796 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 776 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::BINARY );
          yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 1812 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 788 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::HEXADECIMAL );
          yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 1828 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 804 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::get< libcasm_ir::IntegerConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::DECIMAL );
          yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 1844 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 820 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::get< libcasm_ir::FloatingConstant >( yystack_[0].value.as< std::string > () );
          yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 1860 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 836 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::get< libcasm_ir::RationalConstant >( yystack_[0].value.as< std::string > () );
          yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 1876 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 852 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto ruleName = Ast::make< IdentifierNode >( yylhs.location, yystack_[0].value.as< std::string > () );
      yylhs.value.as< RuleReferenceAtom::Ptr > () = Ast::make< RuleReferenceAtom >( yylhs.location, ruleName );
  }
#line 1885 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 861 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 1893 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 865 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 1901 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 869 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 1909 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 873 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 1917 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 877 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 1925 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 881 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1933 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 885 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ListExpression::Ptr > ();
  }
#line 1941 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 889 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RangeExpression::Ptr > ();
  }
#line 1949 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 893 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1957 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 901 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1965 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 905 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1973 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 909 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 1981 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 913 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 1989 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 917 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 1997 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 921 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2005 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 925 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2013 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 929 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2021 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 933 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO call power builtin
  }
#line 2029 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 937 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2037 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 941 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2045 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 945 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2053 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 949 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2061 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 953 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2069 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 957 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2077 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 961 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2085 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 965 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2093 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 969 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2101 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 973 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO add implies instruction
  }
#line 2109 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 977 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2117 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 985 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeExpression::Ptr > () = Ast::make< RangeExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2125 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 993 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, expressions );
  }
#line 2134 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 998 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2142 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 1006 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2152 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 1012 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2162 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1022 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2170 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1026 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2179 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1035 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = yystack_[1].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[3].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2189 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1045 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > (), arguments );
  }
#line 2198 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1050 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2206 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1058 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2214 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1066 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2222 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1074 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2230 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1082 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2238 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1090 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > (), createVoidType( yylhs.location ),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2247 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1095 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2256 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1104 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 2264 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1108 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 2272 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1112 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 2280 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1116 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 2288 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1120 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 2296 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1124 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 2304 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1128 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 2312 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1132 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 2320 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1136 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 2328 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1140 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 2336 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1148 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2346 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1154 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2356 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1164 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location );
  }
#line 2364 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1172 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2372 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1176 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2380 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1184 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< Cases::Ptr > () );
  }
#line 2388 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1192 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2396 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1196 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2404 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1200 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2412 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1208 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = yystack_[0].value.as< Cases::Ptr > ();
      cases->add( yystack_[1].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 2422 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1214 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 2432 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1224 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2440 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1232 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2448 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1240 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2456 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1248 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2464 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1252 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2472 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1260 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2480 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1264 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2488 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1272 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, yystack_[2].value.as< DirectCallExpression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2496 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1280 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2506 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1286 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2517 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1293 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2527 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1299 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2538 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1310 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< BasicAttribute::Ptr > ();
  }
#line 2546 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1314 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< ExpressionAttribute::Ptr > ();
  }
#line 2554 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1322 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = yystack_[2].value.as< Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2564 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1328 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2574 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1338 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > () );
  }
#line 2582 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1346 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2590 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2594 "GrammarParser.cpp" // lalr1.cc:859
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


  const signed char Parser::yypact_ninf_ = -125;

  const signed char Parser::yytable_ninf_ = -1;

  const short int
  Parser::yypact_[] =
  {
      49,    17,    63,   -37,   -54,   -54,   -54,   -54,   -54,  -125,
    -125,    17,  -125,  -125,  -125,  -125,  -125,  -125,   646,  -125,
    -125,    22,    52,    22,    48,   702,  -125,   -12,  -125,  -125,
    -125,   -54,   702,   -54,  -125,  -125,  -125,   702,   702,   702,
     478,   534,    25,  -125,  -125,  -125,  -125,  -125,  -125,  -125,
      50,    53,    57,  -125,  -125,  -125,  -125,  -125,  -125,  -125,
    -125,  -125,  1017,  -125,  -125,  -125,    43,  -125,  -125,  -125,
    -125,  -125,   -54,    45,    66,   -29,   -54,   478,  1234,    80,
     -54,    65,    97,   792,   100,  -125,  -125,  -125,   702,   986,
    -125,  1048,     8,  -125,   646,  -125,   590,  -125,   702,   702,
     702,   702,   702,   702,   702,   702,   702,   702,   702,   702,
     702,   702,   702,   702,   702,   702,  -125,   -16,   -54,   -54,
     385,   -54,    67,    60,    20,  -125,  -125,  -125,  -125,  1079,
    -125,  -125,   -54,   702,   702,   702,  1110,  -125,   702,   702,
    -125,   702,  -125,  -125,  1234,    15,  1315,  1265,    70,   171,
      35,    35,   369,   159,   159,    71,    71,    71,  -125,  1234,
     369,   159,   159,  1234,  -125,   -54,    90,  -125,   -13,   385,
     385,  -125,   -54,   -54,   385,   -24,   702,   702,    81,   385,
     385,    76,  -125,  -125,  -125,  -125,  -125,  -125,  -125,  -125,
    -125,  -125,  -125,  -125,    98,   -54,   -54,   -54,   702,  -125,
     924,   861,   955,    57,    19,  1141,  1234,  -125,  -125,   702,
    -125,   -54,  -125,    -5,   319,   118,   143,  -125,  -125,  -125,
     827,   893,    29,   372,   702,   385,  -125,   151,  -125,    44,
    1296,   702,   702,   702,  -125,  -125,  -125,  1234,  -125,  -125,
    -125,  -125,   702,   702,   385,   121,  -125,  -125,  1234,  -125,
     122,   155,   -54,  -125,  -125,  1234,  -125,   726,   757,   147,
     422,   702,   126,  -125,  -125,   385,   385,   385,   125,   130,
    1172,   422,   127,  1203,   646,  -125,  -125,  -125,   385,   385,
     385,  -125,  -125,  -125,   132,  -125,  -125,  -125,  -125
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,     0,     0,     8,
      10,     2,     3,    12,     4,     6,     5,     1,    29,    32,
      21,    40,     0,    40,     0,   149,   148,     0,   145,   146,
       9,     0,     0,     0,    57,    59,    58,     0,     0,     0,
       0,     0,     0,    61,    62,    63,    65,    64,    60,    27,
      28,     0,   104,    75,    55,    56,    54,    50,    51,    52,
      53,    49,    23,    72,    74,    73,     0,    67,    68,    69,
      70,    71,     0,     0,     0,     0,    20,     0,   150,     0,
       0,    36,     0,     0,     0,    95,    77,    78,     0,     0,
      97,   100,     0,    66,     0,    22,     0,   105,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    38,     0,     0,     0,
       0,     0,    19,     0,    44,    18,    41,    42,    43,     0,
       7,   147,     0,     0,     0,     0,     0,    76,     0,     0,
      98,     0,    26,   102,   100,     0,    93,    91,    92,    94,
      79,    80,    86,    87,    88,    81,    82,    83,    84,    24,
      85,    89,    90,    25,    39,     0,     0,    34,     0,     0,
       0,   124,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   142,   144,   110,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,     0,     0,     0,     0,     0,    35,
       0,     0,     0,     0,     0,     0,    99,   101,    37,     0,
      31,     0,   123,     0,     0,     0,     0,   135,   141,   143,
       0,     0,     0,     0,     0,     0,    17,    16,    48,     0,
      46,     0,     0,     0,   106,   103,    96,    30,    33,   139,
     122,   137,     0,     0,     0,     0,   136,   138,   140,   111,
       0,    14,     0,    45,   108,   107,   109,     0,     0,   125,
       0,     0,     0,    11,    47,     0,     0,     0,     0,     0,
       0,   132,     0,     0,    29,   133,   134,   126,     0,     0,
       0,   131,   127,    15,     0,   128,   129,   130,    13
  };

  const short int
  Parser::yypgoto_[] =
  {
    -125,  -125,   103,   173,  -125,  -125,  -125,  -125,  -125,  -125,
    -125,    93,  -125,   -86,  -125,  -125,    -3,  -125,    -7,  -125,
     166,   -89,  -125,  -125,  -125,  -125,  -125,  -125,  -125,  -125,
    -125,  -125,  -125,  -125,  -125,    42,  -125,  -125,  -125,   -81,
      -6,  -125,    16,    84,  -125,  -125,  -125,  -125,   102,  -124,
    -125,  -125,  -125,  -125,   -71,  -125,  -125,  -125,  -125,  -125,
    -125,  -125,   123,  -125,  -125,  -125
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,     9,    10,    11,    12,   263,   251,   122,   123,
      13,    49,    50,    51,    14,    15,    52,   168,    82,   117,
      73,   125,   126,   127,   128,   229,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    92,
      97,    66,    67,    68,    69,    70,    71,    16,   212,   213,
     184,   185,   186,   271,   272,   187,   188,   189,   190,   191,
     192,   193,    26,    27,    28,    29
  };

  const unsigned short int
  Parser::yytable_[] =
  {
      20,    21,    22,    23,    24,    25,   169,   239,   170,    18,
     171,   172,   120,   173,   174,   145,   175,   176,   178,    19,
     177,     3,     4,     5,     6,     7,    84,   164,    81,   166,
      81,   121,   194,    79,   210,   165,    19,   178,   211,    80,
     169,   179,   170,   199,   171,   172,   214,   173,   174,    19,
     175,   176,     1,   140,   177,   222,   223,   204,   207,   141,
     180,     8,   235,    17,    72,   116,   141,    78,    19,    81,
     141,   178,   197,   124,    83,   179,   246,    25,   198,    85,
      86,    87,    89,    91,     3,     4,     5,     6,     7,   107,
     108,   109,   110,    74,   180,   252,    76,   253,    93,    96,
      95,    94,    19,   115,    98,   118,   226,   227,   228,   102,
     103,   104,   119,   132,   133,   124,   167,   135,   124,   129,
     196,   195,   105,   106,   107,   108,   109,   110,   110,   124,
     136,   209,   112,   113,   114,    88,   181,   224,   144,   225,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   208,   242,
     243,   250,    81,   264,   262,   215,   216,   260,   261,    81,
      81,   267,   274,   278,   282,   200,   201,   202,   279,   288,
     144,   205,   130,   206,    30,   181,   181,   142,   284,    75,
     181,   218,   124,   124,   124,   181,   181,   234,   102,   103,
     281,     0,     0,   131,   182,    98,    99,   100,   238,     0,
     102,   103,   104,   107,   108,   109,   110,     0,   220,   221,
       0,     0,   183,   105,   106,   107,   108,   109,   110,   181,
     181,     0,     0,   112,   113,   114,     0,     0,   181,   181,
     230,   181,     0,     0,     0,     0,     0,     0,     0,   124,
       0,   237,     0,   182,   182,     0,     0,     0,   182,   219,
     181,     0,     0,   182,   182,     0,   248,     0,     0,     0,
       0,     0,     0,   254,   255,   256,   217,     0,     0,     0,
       0,   181,   181,   181,   257,   258,     0,     0,     0,     0,
       0,     0,     0,     0,   181,   181,   181,   182,   182,     0,
       0,     0,   270,   273,     0,     0,   182,   182,     0,   182,
       0,     0,     0,   270,     0,   240,   240,     0,     0,     0,
       0,     0,     0,     0,   240,   240,     0,   249,   182,     0,
     169,     0,   170,   241,   171,   172,     0,   173,   174,     0,
     175,   176,     0,     0,   177,     0,   259,     0,     0,   182,
     182,   182,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   178,   182,   182,   182,   179,     0,   275,   276,   277,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     285,   286,   287,   169,   180,   170,     0,   171,   172,     0,
     173,   174,    19,   175,   176,     0,   169,   177,   170,     0,
     171,   172,     0,   173,   174,     0,   175,   176,   102,   103,
     177,     0,     0,     0,   178,     0,     0,     0,   179,     0,
       0,   105,   106,   107,   108,   109,   110,   178,     0,     0,
       0,   179,   113,   114,     0,     0,     0,   180,   247,     0,
      31,     0,     0,     0,    32,    19,     0,     0,     0,   268,
     180,    33,     0,    34,    35,    36,     0,     0,    19,     0,
      37,    38,    39,     0,    77,     0,    41,     0,     0,     0,
       0,   269,    42,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    43,
      44,    45,    46,    47,    48,    19,    31,     0,     0,     0,
      32,     0,     0,     0,     0,     0,     0,    33,     0,    34,
      35,    36,     0,     0,     0,     0,    37,    38,    39,     0,
      77,     0,    41,     0,     0,     0,     0,     0,    42,     0,
       0,     0,    88,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    43,    44,    45,    46,    47,
      48,    19,    31,     0,     0,     0,    32,     0,     0,     0,
       0,     0,     0,    33,     0,    34,    35,    36,     0,     0,
       0,     0,    37,    38,    39,     0,    77,     0,    41,    90,
       0,     0,     0,     0,    42,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    43,    44,    45,    46,    47,    48,    19,    31,     0,
       0,     0,    32,     0,     0,     0,     0,     0,     0,    33,
       0,    34,    35,    36,     0,     0,     0,     0,    37,    38,
      39,     0,    77,   143,    41,     0,     0,     0,     0,     0,
      42,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    43,    44,    45,
      46,    47,    48,    19,    31,     0,     0,     0,    32,     0,
       0,     0,     0,     0,     0,    33,     0,    34,    35,    36,
       0,     0,     0,     0,    37,    38,    39,     0,    40,     0,
      41,     0,     0,     0,     0,     0,    42,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    43,    44,    45,    46,    47,    48,    19,
      31,     0,     0,     0,    32,     0,     0,     0,     0,     0,
       0,    33,     0,    34,    35,    36,     0,     0,     0,     0,
      37,    38,    39,   265,    77,     0,    41,     0,     0,     0,
       0,     0,    42,     0,     0,     0,     0,     0,     0,     0,
      98,    99,   100,   101,     0,   102,   103,   104,     0,    43,
      44,    45,    46,    47,    48,    19,     0,   266,   105,   106,
     107,   108,   109,   110,     0,     0,     0,     0,   112,   113,
     114,    98,    99,   100,   101,     0,   102,   103,   104,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   105,
     106,   107,   108,   109,   110,   134,     0,     0,     0,   112,
     113,   114,     0,     0,     0,     0,    98,    99,   100,   101,
       0,   102,   103,   104,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   105,   106,   107,   108,   109,   110,
     244,     0,     0,     0,   112,   113,   114,     0,     0,     0,
       0,    98,    99,   100,   101,     0,   102,   103,   104,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   105,
     106,   107,   108,   109,   110,   232,     0,     0,     0,   112,
     113,   114,     0,     0,     0,    98,    99,   100,   101,     0,
     102,   103,   104,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   105,   106,   107,   108,   109,   110,   245,
       0,     0,     0,   112,   113,   114,     0,    98,    99,   100,
     101,     0,   102,   103,   104,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   105,   106,   107,   108,   109,
     110,     0,   231,     0,     0,   112,   113,   114,    98,    99,
     100,   101,     0,   102,   103,   104,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   105,   106,   107,   108,
     109,   110,     0,     0,     0,   233,   112,   113,   114,    98,
      99,   100,   101,     0,   102,   103,   104,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   105,   106,   107,
     108,   109,   110,     0,     0,     0,     0,   112,   113,   114,
      98,    99,   100,   101,     0,   102,   103,   104,     0,   137,
       0,     0,     0,     0,     0,     0,     0,   138,   105,   106,
     107,   108,   109,   110,     0,     0,     0,     0,   112,   113,
     114,    98,    99,   100,   101,     0,   102,   103,   104,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   105,
     106,   107,   108,   109,   110,     0,     0,   111,     0,   112,
     113,   114,    98,    99,   100,   101,     0,   102,   103,   104,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     105,   106,   107,   108,   109,   110,     0,   139,     0,     0,
     112,   113,   114,    98,    99,   100,   101,     0,   102,   103,
     104,     0,   137,     0,     0,     0,     0,     0,     0,     0,
       0,   105,   106,   107,   108,   109,   110,     0,     0,     0,
       0,   112,   113,   114,    98,    99,   100,   101,     0,   102,
     103,   104,     0,   203,     0,     0,     0,     0,     0,     0,
       0,     0,   105,   106,   107,   108,   109,   110,     0,     0,
       0,     0,   112,   113,   114,    98,    99,   100,   101,     0,
     102,   103,   104,     0,     0,     0,   236,     0,     0,     0,
       0,     0,     0,   105,   106,   107,   108,   109,   110,     0,
       0,     0,     0,   112,   113,   114,    98,    99,   100,   101,
       0,   102,   103,   104,     0,     0,     0,     0,     0,     0,
     280,     0,     0,     0,   105,   106,   107,   108,   109,   110,
       0,     0,     0,     0,   112,   113,   114,    98,    99,   100,
     101,     0,   102,   103,   104,     0,     0,     0,     0,     0,
     283,     0,     0,     0,     0,   105,   106,   107,   108,   109,
     110,     0,     0,     0,     0,   112,   113,   114,    98,    99,
     100,   101,     0,   102,   103,   104,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   105,   106,   107,   108,
     109,   110,     0,     0,     0,     0,   112,   113,   114,    98,
       0,   100,     0,     0,   102,   103,   104,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   105,   106,   107,
     108,   109,   110,     0,     0,     0,     0,   112,   113,   114,
      98,    99,   100,   101,     0,   102,   103,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   105,     0,
       0,   108,   109,   110,   102,   103,   104,     0,   112,   113,
     114,     0,     0,     0,     0,     0,     0,   105,   106,   107,
     108,   109,   110,     0,     0,     0,     0,   112,   113,   114
  };

  const short int
  Parser::yycheck_[] =
  {
       3,     4,     5,     6,     7,     8,    11,    12,    13,    46,
      15,    16,    41,    18,    19,    96,    21,    22,    42,    73,
      25,     4,     5,     6,     7,     8,    33,    43,    31,   118,
      33,    60,   121,    45,    47,    51,    73,    42,    51,    51,
      11,    46,    13,   132,    15,    16,   170,    18,    19,    73,
      21,    22,     3,    45,    25,   179,   180,   138,    43,    51,
      65,    44,    43,     0,    42,    72,    51,    25,    73,    72,
      51,    42,    52,    76,    32,    46,    47,    80,    58,    37,
      38,    39,    40,    41,     4,     5,     6,     7,     8,    54,
      55,    56,    57,    41,    65,    51,    48,    53,    73,    42,
      47,    51,    73,    60,    34,    60,   195,   196,   197,    39,
      40,    41,    46,    48,    17,   118,   119,    17,   121,    77,
      60,    54,    52,    53,    54,    55,    56,    57,    57,   132,
      88,    41,    62,    63,    64,    54,   120,    61,    96,    41,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   165,    41,
      17,    10,   165,   252,     9,   172,   173,    46,    46,   172,
     173,    24,    46,    48,    47,   133,   134,   135,    48,    47,
     138,   139,    79,   141,    11,   169,   170,    94,   274,    23,
     174,   175,   195,   196,   197,   179,   180,   203,    39,    40,
     271,    -1,    -1,    80,   120,    34,    35,    36,   211,    -1,
      39,    40,    41,    54,    55,    56,    57,    -1,   176,   177,
      -1,    -1,   120,    52,    53,    54,    55,    56,    57,   213,
     214,    -1,    -1,    62,    63,    64,    -1,    -1,   222,   223,
     198,   225,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   252,
      -1,   209,    -1,   169,   170,    -1,    -1,    -1,   174,   175,
     244,    -1,    -1,   179,   180,    -1,   224,    -1,    -1,    -1,
      -1,    -1,    -1,   231,   232,   233,   174,    -1,    -1,    -1,
      -1,   265,   266,   267,   242,   243,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   278,   279,   280,   213,   214,    -1,
      -1,    -1,   260,   261,    -1,    -1,   222,   223,    -1,   225,
      -1,    -1,    -1,   271,    -1,   213,   214,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   222,   223,    -1,   225,   244,    -1,
      11,    -1,    13,    14,    15,    16,    -1,    18,    19,    -1,
      21,    22,    -1,    -1,    25,    -1,   244,    -1,    -1,   265,
     266,   267,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    42,   278,   279,   280,    46,    -1,   265,   266,   267,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     278,   279,   280,    11,    65,    13,    -1,    15,    16,    -1,
      18,    19,    73,    21,    22,    -1,    11,    25,    13,    -1,
      15,    16,    -1,    18,    19,    -1,    21,    22,    39,    40,
      25,    -1,    -1,    -1,    42,    -1,    -1,    -1,    46,    -1,
      -1,    52,    53,    54,    55,    56,    57,    42,    -1,    -1,
      -1,    46,    63,    64,    -1,    -1,    -1,    65,    66,    -1,
      18,    -1,    -1,    -1,    22,    73,    -1,    -1,    -1,    27,
      65,    29,    -1,    31,    32,    33,    -1,    -1,    73,    -1,
      38,    39,    40,    -1,    42,    -1,    44,    -1,    -1,    -1,
      -1,    49,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      68,    69,    70,    71,    72,    73,    18,    -1,    -1,    -1,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    31,
      32,    33,    -1,    -1,    -1,    -1,    38,    39,    40,    -1,
      42,    -1,    44,    -1,    -1,    -1,    -1,    -1,    50,    -1,
      -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,
      72,    73,    18,    -1,    -1,    -1,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    29,    -1,    31,    32,    33,    -1,    -1,
      -1,    -1,    38,    39,    40,    -1,    42,    -1,    44,    45,
      -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    68,    69,    70,    71,    72,    73,    18,    -1,
      -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,    29,
      -1,    31,    32,    33,    -1,    -1,    -1,    -1,    38,    39,
      40,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,
      50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,
      70,    71,    72,    73,    18,    -1,    -1,    -1,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    29,    -1,    31,    32,    33,
      -1,    -1,    -1,    -1,    38,    39,    40,    -1,    42,    -1,
      44,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    72,    73,
      18,    -1,    -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    29,    -1,    31,    32,    33,    -1,    -1,    -1,    -1,
      38,    39,    40,    17,    42,    -1,    44,    -1,    -1,    -1,
      -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      34,    35,    36,    37,    -1,    39,    40,    41,    -1,    67,
      68,    69,    70,    71,    72,    73,    -1,    20,    52,    53,
      54,    55,    56,    57,    -1,    -1,    -1,    -1,    62,    63,
      64,    34,    35,    36,    37,    -1,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      53,    54,    55,    56,    57,    23,    -1,    -1,    -1,    62,
      63,    64,    -1,    -1,    -1,    -1,    34,    35,    36,    37,
      -1,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    52,    53,    54,    55,    56,    57,
      23,    -1,    -1,    -1,    62,    63,    64,    -1,    -1,    -1,
      -1,    34,    35,    36,    37,    -1,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      53,    54,    55,    56,    57,    24,    -1,    -1,    -1,    62,
      63,    64,    -1,    -1,    -1,    34,    35,    36,    37,    -1,
      39,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    53,    54,    55,    56,    57,    26,
      -1,    -1,    -1,    62,    63,    64,    -1,    34,    35,    36,
      37,    -1,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    53,    54,    55,    56,
      57,    -1,    28,    -1,    -1,    62,    63,    64,    34,    35,
      36,    37,    -1,    39,    40,    41,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    52,    53,    54,    55,
      56,    57,    -1,    -1,    -1,    30,    62,    63,    64,    34,
      35,    36,    37,    -1,    39,    40,    41,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    53,    54,
      55,    56,    57,    -1,    -1,    -1,    -1,    62,    63,    64,
      34,    35,    36,    37,    -1,    39,    40,    41,    -1,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    52,    53,
      54,    55,    56,    57,    -1,    -1,    -1,    -1,    62,    63,
      64,    34,    35,    36,    37,    -1,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      53,    54,    55,    56,    57,    -1,    -1,    60,    -1,    62,
      63,    64,    34,    35,    36,    37,    -1,    39,    40,    41,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      52,    53,    54,    55,    56,    57,    -1,    59,    -1,    -1,
      62,    63,    64,    34,    35,    36,    37,    -1,    39,    40,
      41,    -1,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    53,    54,    55,    56,    57,    -1,    -1,    -1,
      -1,    62,    63,    64,    34,    35,    36,    37,    -1,    39,
      40,    41,    -1,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    52,    53,    54,    55,    56,    57,    -1,    -1,
      -1,    -1,    62,    63,    64,    34,    35,    36,    37,    -1,
      39,    40,    41,    -1,    -1,    -1,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    53,    54,    55,    56,    57,    -1,
      -1,    -1,    -1,    62,    63,    64,    34,    35,    36,    37,
      -1,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    -1,    -1,    -1,    52,    53,    54,    55,    56,    57,
      -1,    -1,    -1,    -1,    62,    63,    64,    34,    35,    36,
      37,    -1,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,
      47,    -1,    -1,    -1,    -1,    52,    53,    54,    55,    56,
      57,    -1,    -1,    -1,    -1,    62,    63,    64,    34,    35,
      36,    37,    -1,    39,    40,    41,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    52,    53,    54,    55,
      56,    57,    -1,    -1,    -1,    -1,    62,    63,    64,    34,
      -1,    36,    -1,    -1,    39,    40,    41,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    53,    54,
      55,    56,    57,    -1,    -1,    -1,    -1,    62,    63,    64,
      34,    35,    36,    37,    -1,    39,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,
      -1,    55,    56,    57,    39,    40,    41,    -1,    62,    63,
      64,    -1,    -1,    -1,    -1,    -1,    -1,    52,    53,    54,
      55,    56,    57,    -1,    -1,    -1,    -1,    62,    63,    64
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    78,     4,     5,     6,     7,     8,    44,    79,
      80,    81,    82,    87,    91,    92,   124,     0,    46,    73,
      93,    93,    93,    93,    93,    93,   139,   140,   141,   142,
      80,    18,    22,    29,    31,    32,    33,    38,    39,    40,
      42,    44,    50,    67,    68,    69,    70,    71,    72,    88,
      89,    90,    93,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   118,   119,   120,   121,
     122,   123,    42,    97,    41,    97,    48,    42,   112,    45,
      51,    93,    95,   112,    95,   112,   112,   112,    54,   112,
      45,   112,   116,    73,    51,    47,    42,   117,    34,    35,
      36,    37,    39,    40,    41,    52,    53,    54,    55,    56,
      57,    60,    62,    63,    64,    60,    95,    96,    60,    46,
      41,    60,    85,    86,    93,    98,    99,   100,   101,   112,
      79,   139,    48,    17,    23,    17,   112,    43,    51,    59,
      45,    51,    88,    43,   112,   116,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,    43,    51,    98,    93,    94,    11,
      13,    15,    16,    18,    19,    21,    22,    25,    42,    46,
      65,   119,   120,   125,   127,   128,   129,   132,   133,   134,
     135,   136,   137,   138,    98,    54,    60,    52,    58,    98,
     112,   112,   112,    43,   116,   112,   112,    43,    95,    41,
      47,    51,   125,   126,   126,    95,    95,   125,   119,   120,
     112,   112,   126,   126,    61,    41,    98,    98,    98,   102,
     112,    28,    24,    30,   117,    43,    45,   112,    93,    12,
     125,    14,    41,    17,    23,    26,    47,    66,   112,   125,
      10,    84,    51,    53,   112,   112,   112,   112,   112,   125,
      46,    46,     9,    83,    98,    17,    20,    24,    27,    49,
     112,   130,   131,   112,    46,   125,   125,   125,    48,    48,
      48,   131,    47,    47,    90,   125,   125,   125,    47
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    77,    78,    79,    79,    79,    79,    80,    80,    81,
      81,    82,    82,    83,    83,    84,    84,    85,    85,    86,
      86,    87,    87,    88,    88,    88,    89,    89,    90,    90,
      91,    92,    93,    94,    94,    95,    95,    96,    96,    97,
      97,    98,    98,    98,    99,   100,   101,   102,   102,   103,
     103,   103,   103,   103,   103,   103,   103,   104,   105,   105,
     106,   107,   107,   108,   109,   110,   111,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   114,   115,   115,   116,
     116,   117,   117,   118,   119,   119,   120,   121,   122,   123,
     124,   124,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   126,   126,   127,   128,   128,   129,   130,   130,
     130,   131,   131,   132,   133,   134,   135,   135,   136,   136,
     137,   138,   138,   138,   138,   139,   139,   140,   140,   141,
     142
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     1,     1,     1,     1,     4,     1,     2,
       1,     8,     1,     4,     0,     4,     0,     3,     1,     1,
       0,     2,     4,     1,     3,     3,     3,     1,     1,     0,
       7,     6,     1,     3,     1,     3,     1,     3,     1,     3,
       0,     1,     1,     1,     1,     4,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     5,     2,     3,     3,
       1,     3,     2,     5,     1,     2,     5,     6,     6,     6,
       5,     7,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     4,     6,     6,     3,     3,
       3,     2,     1,     6,     6,     2,     3,     3,     3,     3,
       3,     2,     1,     2,     1,     1,     1,     3,     1,     1,
       2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"CASM\"", "\"init\"",
  "\"derived\"", "\"enum\"", "\"rule\"", "\"function\"", "\"initially\"",
  "\"defined\"", "\"seq\"", "\"endseq\"", "\"par\"", "\"endpar\"",
  "\"skip\"", "\"let\"", "\"in\"", "\"forall\"", "\"iterate\"", "\"do\"",
  "\"call\"", "\"if\"", "\"then\"", "\"else\"", "\"case\"", "\"of\"",
  "\"default\"", "\"holds\"", "\"exists\"", "\"with\"", "\"undef\"",
  "\"false\"", "\"true\"", "\"and\"", "\"or\"", "\"xor\"", "\"implies\"",
  "\"not\"", "\"+\"", "\"-\"", "\"=\"", "\"(\"", "\")\"", "\"[\"", "\"]\"",
  "\"{\"", "\"}\"", "\":\"", "\"_\"", "\"@\"", "\",\"", "\"<\"", "\">\"",
  "\"*\"", "\"/\"", "\"%\"", "\"^\"", "\"'\"", "\"..\"", "\"->\"",
  "\":=\"", "\"!=\"", "\"<=\"", "\">=\"", "\"{|\"", "\"|}\"", "\"binary\"",
  "\"hexadecimal\"", "\"integer\"", "\"rational\"", "\"floating\"",
  "\"string\"", "\"identifier\"", "UPLUS", "UMINUS", "CALL_WITHOUT_ARGS",
  "$accept", "Specification", "Definition", "AttributedDefinition",
  "Definitions", "FunctionDefinition", "MaybeInitially", "MaybeDefined",
  "FunctionParameters", "MaybeFunctionParameters",
  "ProgramFunctionDefinition", "Initializer", "Initializers",
  "MaybeInitializers", "DerivedDefinition", "EnumerationDefinition",
  "Identifier", "Identifiers", "Variable", "Parameters", "MaybeParameters",
  "Type", "BasicType", "ComposedType", "FixedSizedType", "Types", "Atom",
  "Undefined", "Boolean", "String", "BitNumber", "IntegerNumber",
  "FloatingNumber", "RationalNumber", "RuleReference", "Term",
  "Expression", "Range", "List", "Terms", "Arguments",
  "TwoOrMoreArguments", "DirectCallExpression", "IndirectCallExpression",
  "ConditionalExpression", "UniversalQuantifierExpression",
  "ExistentialQuantifierExpression", "RuleDefinition", "Rule", "Rules",
  "SkipRule", "ConditionalRule", "CaseRule", "CaseLabel", "CaseLabels",
  "LetRule", "ForallRule", "IterateRule", "BlockRule", "SequenceRule",
  "UpdateRule", "CallRule", "Attribute", "Attributes", "BasicAttribute",
  "ExpressionAttribute", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   328,   328,   340,   344,   348,   352,   360,   366,   374,
     380,   390,   406,   414,   418,   426,   430,   438,   444,   454,
     458,   466,   487,   504,   513,   524,   536,   542,   552,   556,
     564,   572,   580,   588,   594,   604,   608,   617,   623,   633,
     637,   645,   649,   653,   661,   669,   677,   685,   691,   701,
     705,   709,   713,   717,   721,   725,   729,   737,   745,   750,
     759,   775,   787,   803,   819,   835,   851,   860,   864,   868,
     872,   876,   880,   884,   888,   892,   900,   904,   908,   912,
     916,   920,   924,   928,   932,   936,   940,   944,   948,   952,
     956,   960,   964,   968,   972,   976,   984,   992,   997,  1005,
    1011,  1021,  1025,  1034,  1044,  1049,  1057,  1065,  1073,  1081,
    1089,  1094,  1103,  1107,  1111,  1115,  1119,  1123,  1127,  1131,
    1135,  1139,  1147,  1153,  1163,  1171,  1175,  1183,  1191,  1195,
    1199,  1207,  1213,  1223,  1231,  1239,  1247,  1251,  1259,  1263,
    1271,  1279,  1285,  1292,  1298,  1309,  1313,  1321,  1327,  1337,
    1345
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


#line 31 "../../obj/src/GrammarParser.yy" // lalr1.cc:1167
} // libcasm_fe
#line 3400 "GrammarParser.cpp" // lalr1.cc:1167
#line 1351 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


void Parser::error( const Location& location, const std::string& message )
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
