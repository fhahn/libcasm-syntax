//
//  Copyright (c) 2014-2016 CASM Organization
//  All rights reserved.
//
//  Developed by: Florian Hahn
//                Philipp Paulweber
//                Emmanuel Pescosta
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

#include <cmath>

#include "Ast.h"
#include "Driver.h"
#include "Symbols.h"

std::map< Builtin::Id, Builtin* > Builtin::id2obj;
std::map< std::string, Builtin* > Builtin::str2obj;

static bool built_in_intconstarg_to_retbittype( Builtin& self, Driver& driver,
    BuiltinAtom* atom, std::vector< Type* >& arguments, uint8_t len2check,
    uint8_t argpos )
{
    if( arguments.size() != len2check && "invalid argument length for builtin" )
    {
        return false;
    }

    ExpressionBase* expr_bitsize = atom->arguments->at( argpos );
    if( expr_bitsize->node_type_ != NodeType::INTEGER_ATOM )
    {
        driver.error( atom->arguments->at( 1 )->location,
            "second argument of '" + self.name
                + "' builtin must be a Integer constant" );
        return false;
    }

    INTEGER_T bitsize = static_cast< IntegerAtom* >( expr_bitsize )->val_;
    if( bitsize <= 0 or bitsize > 256 )
    {
        driver.error( atom->arguments->at( 1 )->location,
            "second argument of '" + self.name
                + "' builtin must be in the range from 1 to 256" );
        return false;
    }

    atom->return_type->bitsize = bitsize;
    return true;
}

static void built_in_funcarg_to_retbittype( Builtin& self, Driver& driver,
    BuiltinAtom* atom, std::vector< Type* >& arguments, uint8_t argpos )
{
    ExpressionBase* expr_bitsize = atom->arguments->at( argpos );
    atom->types[ argpos ]->bitsize = expr_bitsize->type_.bitsize;
}

static void built_in_check_bitargs( Builtin& self, Driver& driver,
    BuiltinAtom* atom, std::vector< Type* >& arguments )
{
    bool flag = false;
    for( int i = 0; i < 2; i++ )
    {
        built_in_funcarg_to_retbittype( self, driver, atom, arguments, i );

        if( atom->types[ i ]->bitsize <= 0 )
        {
            driver.error( atom->arguments->at( i )->location,
                "first argument of '" + self.name + "' has invalid Bit type '"
                    + atom->types[ i ]->to_str()
                    + "'!" );
            flag = true;
        }
    }

    if( flag )
    {
        return;
    }

    if( atom->types[ 0 ]->bitsize != atom->types[ 1 ]->bitsize )
    {
        driver.error( atom->location,
            "arguments of '" + self.name + "' have different Bit types: '"
                + atom->types[ 0 ]->to_str()
                + "' != '"
                + atom->types[ 1 ]->to_str()
                + "'" );
    }
}

//  { "builtinName"
//  , Builtin::Id::BUILTIN_ID
//  , { ... } possible return types
//  , { { ... possible 0. argument types
//      }
//    , { ... possible 1. argument types
//      }
//    }
//  , [] ( Type* ret, std::vector< Type* >& arg )
//    {
//        unification procedure for this builtin
//    }
//  , [] ( Driver& driver, BuiltinAtom* atom, Type* arguments[], uint16_t length
//  )
//    {
//        typecheck & type-patch procedure for this builtin
//    }
//  }

Builtin built_ins[] = { { "isSymbolic", Builtin::Id::IS_SYMBOLIC,
                            { TypeType::BOOLEAN }, { { TypeType::UNKNOWN } } }

    ,
    {
        "nth", Builtin::Id::NTH, { TypeType::UNKNOWN },
        { { TypeType::TUPLE_OR_LIST, TypeType::UNKNOWN },
            { TypeType::INTEGER } },
        []( Type* ret, std::vector< Type* >& arg ) {
            arg[ 0 ]->subtypes[ 0 ]->unify( ret );
        }
        // TODO: move 'nth' specific code from typecheckvisitor.cpp into this
        // lambda function here !!!
    }

    // {"cons", true},
    ,
    { "cons", Builtin::Id::CONS, { TypeType::LIST },
        { { TypeType::UNKNOWN }, { TypeType::LIST } },
        []( Type* ret, std::vector< Type* >& arg ) {
            arg[ 0 ]->unify( arg[ 1 ]->subtypes[ 0 ] );
            arg[ 1 ]->unify( ret );
        } }

    // {"app", true},
    ,
    { "app", Builtin::Id::APP, { TypeType::LIST },
        { { TypeType::UNKNOWN }, { TypeType::LIST } },
        []( Type* ret, std::vector< Type* >& arg ) {
            arg[ 0 ]->unify( arg[ 1 ]->subtypes[ 0 ] );
            arg[ 1 ]->unify( ret );
            // TODO: PPA: FIXME: maybe swap arg 0 and 1, wha? @fhahn ?
        } }

    // {"len", true},
    ,
    { "len", Builtin::Id::LEN, { TypeType::INTEGER }, { { TypeType::LIST } } }

    // {"tail", true},
    ,
    { "tail", Builtin::Id::TAIL, { TypeType::UNKNOWN }, { { TypeType::LIST } },
        []( Type* ret, std::vector< Type* >& arg ) { arg[ 0 ]->unify( ret ); } }

    // {"peek", true},
    ,
    { "peek", Builtin::Id::PEEK, { TypeType::UNKNOWN }, { { TypeType::LIST } },
        []( Type* ret, std::vector< Type* >& arg ) {
            arg[ 0 ]->subtypes[ 0 ]->unify( ret );
        } }

    // //===--- CASTING BUILT-INS ---====
    // // asInteger : Boolean  -> Integer // false -> 0, true -> 1, undef ->
    // undef
    // // asInteger : Floating -> Integer // cut of comma value to integer,
    // undef -> undef
    // // asInteger : Bit( n ) -> Integer // n is a integer constant, always use
    // unsigned semantics
    // // asInteger : e        -> Integer // e -> index(e), e !in index(e) ->
    // undef, undef -> undef
    // //                                 // 'e' is a enumeration value of type
    // 'e'
    // {"asInteger", true},
    ,
    { "asInteger", Builtin::Id::AS_INTEGER, { TypeType::INTEGER },
        { { TypeType::UNKNOWN, TypeType::BOOLEAN, TypeType::FLOATING,
            TypeType::BIT, TypeType::ENUM } } }

    // // asBoolean : Integer  -> Boolean // 0 -> false, other -> true
    // // asBoolean : Floating -> Boolean // SHALL NOT BE POSSIBLE !!! ERROR
    // // asBoolean : Bit( n ) -> Boolean // SHALL NOT BE POSSIBLE where n != 1
    // !!! ERROR
    // // asBoolean : Bit( 1 ) -> Boolean // 0b0 -> false, 0b1 -> true
    // // asBoolean : e        -> Boolean // SHALL NOT BE POSSIBLE !!! ERROR
    // //                                 // 'e' is a enumeration value of type
    // 'e'
    // {"asBoolean", true},
    ,
    {
        "asBoolean", Builtin::Id::AS_BOOLEAN, { TypeType::BOOLEAN },
        { { TypeType::UNKNOWN, TypeType::INTEGER, TypeType::BIT,
            TypeType::ENUM } }
        // PPA: TODO: FIXME: the Bit(1) check !!! see above!
    }

    // // asFloating : Integer  -> Floating // int to float converstion!
    // // asFloating : Boolean  -> Floating // false -> 0.0, true -> 1.0
    // // asFloating : Bit( n ) -> Floating // SHALL NOT BE POSSIBLE
    // // asFloating : e        -> Floating // e -> index(e).0, e !in index(e)
    // -> undef, undef -> undef
    // //                                   // 'e' is a enumeration value of
    // type 'e'
    // {"asFloating", true},
    ,
    { "asFloating", Builtin::Id::AS_FLOATING, { TypeType::FLOATING },
        { { TypeType::UNKNOWN, TypeType::INTEGER, TypeType::BOOLEAN,
            TypeType::BIT, TypeType::ENUM } } }

    // // asBit : Integer  * Integer (const, n) -> Bit( n ) // only possible if
    // integer fits into bit-width,
    // //                                                   // unsigned semantic
    // only which means e.g.:
    // //                                                   // -1 is a 64-bit
    // integer value and has to fit in at least Bit( 64 )
    // // asBit : Boolean  * Integer (const, n) -> Bit( n ) // false -> 0b0,
    // true -> 0b1
    // // asBit : Floating * Integer (const, n) -> Bit( n ) // SHALL NOT BE
    // POSSIBLE (YET! maybe later!)
    // // asBit : e        * Integer (const, n) -> Bit( n ) // only possible if
    // enum value 'e' fits into bit-width!

    ,
    { "asBit", Builtin::Id::AS_BIT, { TypeType::BIT },
        { { TypeType::UNKNOWN, TypeType::INTEGER, TypeType::BOOLEAN,
              TypeType::FLOATING, TypeType::ENUM },
            { TypeType::INTEGER } },
        []( Type* ret, std::vector< Type* >& arg ) { ret->unify( arg[ 1 ] ); },
        []( Builtin& self, Driver& driver, BuiltinAtom* atom,
            std::vector< Type* >& arguments ) {
            if( !built_in_intconstarg_to_retbittype(
                    self, driver, atom, arguments, 2, 1 ) )
            {
                return;
            }

            INTEGER_T bitsize = atom->return_type->bitsize;
            INTEGER_T value = -1;
            INTEGER_T value_bitsize = -1;

            ExpressionBase* expr_value = atom->arguments->at( 0 );
            if( expr_value->node_type_ == NodeType::INTEGER_ATOM )
            {
                value = static_cast< IntegerAtom* >( expr_value )->val_;
                double v = (double)value;
                v = floor( log2( v ) ) + 1;
                value_bitsize = (INTEGER_T)v;
            }
            else if( expr_value->node_type_ == NodeType::BOOLEAN_ATOM )
            {
                value_bitsize = 1;
            }
            else if( expr_value->node_type_ == NodeType::BUILTIN_ATOM )
            {
                value_bitsize = static_cast< BuiltinAtom* >(
                    expr_value )->return_type->bitsize;
            }
            else if( expr_value->node_type_ == NodeType::FUNCTION_ATOM )
            {
                driver.warning( atom->arguments->at( 0 )->location,
                    "first argument of 'asBit' builtin will be truncated to "
                    "bitsize '"
                        + std::to_string( bitsize )
                        + "'"
                    // "conversion from 'TYPE' to 'TYPE', possible loss of data"
                    // // PPA: use this message in the future
                    );

                return;
            }
            else
            {
                // assert( !"unimplemented value type for 'asBit' builtin to
                // check value bitsize fitting!" );
                value_bitsize = expr_value->type_.bitsize;
            }

            if( value_bitsize > bitsize )
            {
                driver.error( atom->arguments->at( 0 )->location,
                    "first argument of 'asBit' builtin does not fit into the "
                    "bitsize of '"
                        + std::to_string( bitsize )
                        + "'" );
            }
        } }

    // // asEnum : Integer  -> e // iff Integer value is in { indexes of e }
    // // asEnum : Boolean  -> e // SHALL NOT BE POSSIBLE
    // // asEnum : Floating -> e // SHALL NOT BE POSSIBLE
    // // asEnum : Bit( n ) -> e // iff Bit(n) value is in { indexes of e }
    // // // 'e' is a enumeration value of type 'e'
    // {"asEnum", true},
    ,
    { "asEnum", Builtin::Id::AS_ENUM, { TypeType::ENUM },
        { { TypeType::UNKNOWN, TypeType::INTEGER, TypeType::BOOLEAN,
            TypeType::FLOATING, TypeType::BIT } } }

    // // asString : Integer  -> String // SHALL NOT BE POSSIBLE !!! ERROR  -->
    // use 'dec'
    // // asString : Boolean  -> String // false -> "false", true -> "true"
    // // asString : Floating -> String // SHALL NOT BE POSSIBLE !!! ERROR  -->
    // use 'dec'
    // // asString : Bit( n ) -> String // SHALL NOT BE POSSIBLE !!! ERROR  -->
    // use 'dec'
    // // asString : e        -> String // string represenation of enum value
    // 'e'
    // {"asString", true},
    ,
    { "asString", Builtin::Id::AS_STRING, { TypeType::STRING },
        { {
            TypeType::UNKNOWN, TypeType::INTEGER, TypeType::FLOATING,
            TypeType::BIT, TypeType::ENUM
            //    , TypeType::RATIONAL
        } } }

    // // TODO: PPA: define a clear semantic for this type cast!
    // {"asRational", true},
    ,
    { "asRational", Builtin::Id::AS_RATIONAL, { TypeType::RATIONAL },
        { { TypeType::UNKNOWN, TypeType::INTEGER, TypeType::FLOATING,
            TypeType::RATIONAL } } }

    // //===--- STRINGIFY BUILT-INS ---====
    // // dec  : Integer  -> String  // decimal representation of integer
    // // dec  : Boolean  -> String  // decimal representation of boolean
    // // dec  : Floating -> String  // decimal representation of floating point
    // value
    // // dec  : Bit( n ) -> String  // decimal representation of bit-vector
    // // dec  : e        -> String  // decimal representation of enumeration
    // value of type 'e'
    // {"dec", true},
    ,
    { "dec", Builtin::Id::DEC, { TypeType::STRING },
        { {
            TypeType::UNKNOWN, TypeType::INTEGER, TypeType::BOOLEAN,
            TypeType::FLOATING, TypeType::BIT, TypeType::ENUM
            //    , TypeType::RATIONAL
        } } }

    // // hex  : Integer  -> String  // hexadecimal representation of integer
    // WITHOUT prefix '0x'
    // // hex  : Boolean  -> String  // hexadecimal representation of boolean
    // WITHOUT prefix '0x'
    // // hex  : Floating -> String  // hexadecimal representation of floating
    // point value WITHOUT prefix '0x'
    // // hex  : Bit( n ) -> String  // hexadecimal representation of bit-vector
    // WITHOUT prefix '0x'
    // // hex  : e        -> String  // hexadecimal representation of
    // enumeration value of type 'e' WITHOUT prefix '0x'
    // {"hex", true},
    ,
    { "hex", Builtin::Id::HEX, { TypeType::STRING },
        { {
            TypeType::UNKNOWN, TypeType::INTEGER, TypeType::BOOLEAN,
            TypeType::FLOATING, TypeType::BIT, TypeType::ENUM
            //    , TypeType::RATIONAL
        } } }

    // // bin  : Integer  -> String  // binary representation of integer WITHOUT
    // prefix '0b'
    // // bin  : Boolean  -> String  // binary representation of boolean WITHOUT
    // prefix '0b'
    // // bin  : Floating -> String  // binary representation of floating point
    // value WITHOUT prefix '0b'
    // // bin  : Bit( n ) -> String  // binary representation of bit-vector
    // WITHOUT prefix '0b'
    // // bin  : e        -> String  // binary representation of enumeration
    // value of type 'e' WITHOUT prefix '0b'
    // {"bin", true},
    ,
    { "bin", Builtin::Id::BIN, { TypeType::STRING },
        { {
            TypeType::UNKNOWN, TypeType::INTEGER, TypeType::BOOLEAN,
            TypeType::FLOATING, TypeType::BIT, TypeType::ENUM
            //    , TypeType::RATIONAL
        } } }

    // //===--- INTEGER MATH BUILT-INS ---====
    // // pow  : Integer * Integer -> Integer
    // // //     base      exponent
    // {"pow", true},
    ,
    { "pow", Builtin::Id::POW, { TypeType::INTEGER },
        { { TypeType::INTEGER }, { TypeType::INTEGER } } }

    // // rand : Integer * Integer -> Integer
    // // //     start     end
    // {"rand", true},
    ,
    { "rand", Builtin::Id::RAND, { TypeType::INTEGER },
        { { TypeType::INTEGER }, { TypeType::INTEGER } } }

    ////===--- BIT OPERATION BUILT-INS ---====

    //// zext  : Bit( n ) * Integer (const, m) -> Bit( m ) // zero extend to new
    /// size, if m < n then error!
    ,
    { "zext", Builtin::Id::ZEXT, { TypeType::BIT },
        { { TypeType::BIT }, { TypeType::INTEGER } },
        []( Type* ret, std::vector< Type* >& arg ) {},
        []( Builtin& self, Driver& driver, BuiltinAtom* atom,
            std::vector< Type* >& arguments ) {
            if( !built_in_intconstarg_to_retbittype(
                    self, driver, atom, arguments, 2, 1 ) )
            {
                return;
            }

            if( atom->return_type->bitsize < atom->types[ 0 ]->bitsize )
            {
                driver.error( atom->arguments->at( 0 )->location,
                    "cannot '" + self.name + "' from type '"
                        + atom->types[ 0 ]->to_str()
                        + "' to '"
                        + atom->return_type->to_str()
                        + "'!" );
            }
        } }

    //// sext  : Bit( n ) * Integer (const, m) -> Bit( m ) // sign extend to new
    /// size, if m < n then error!
    ,
    { "sext", Builtin::Id::SEXT, { TypeType::BIT },
        { { TypeType::BIT }, { TypeType::INTEGER } },
        []( Type* ret, std::vector< Type* >& arg ) {},
        []( Builtin& self, Driver& driver, BuiltinAtom* atom,
            std::vector< Type* >& arguments ) {
            if( !built_in_intconstarg_to_retbittype(
                    self, driver, atom, arguments, 2, 1 ) )
            {
                return;
            }

            if( atom->return_type->bitsize < atom->types[ 0 ]->bitsize )
            {
                driver.error( atom->arguments->at( 0 )->location,
                    "cannot '" + self.name + "' from type '"
                        + atom->types[ 0 ]->to_str()
                        + "' to '"
                        + atom->return_type->to_str()
                        + "'!" );
            }
        } }

    //// trunc : Bit( n ) * Integer (const, m) -> Bit( m ) // truncate to new
    /// size, if m > n then error!
    ,
    { "trunc", Builtin::Id::TRUNC, { TypeType::BIT },
        { { TypeType::BIT }, { TypeType::INTEGER } },
        []( Type* ret, std::vector< Type* >& arg ) {},
        []( Builtin& self, Driver& driver, BuiltinAtom* atom,
            std::vector< Type* >& arguments ) {
            if( !built_in_intconstarg_to_retbittype(
                    self, driver, atom, arguments, 2, 1 ) )
            {
                return;
            }

            built_in_funcarg_to_retbittype( self, driver, atom, arguments, 0 );

            if( atom->return_type->bitsize > atom->types[ 0 ]->bitsize )
            {
                driver.error( atom->arguments->at( 0 )->location,
                    "cannot '" + self.name + "' from type '"
                        + atom->types[ 0 ]->to_str()
                        + "' to '"
                        + atom->return_type->to_str()
                        + "'!" );
            }
        } }

    //// shl   : Bit( n ) * Integer  -> Bit( n ) // logic shift left of Integer
    /// value positions
    //// shl   : Bit( n ) * Bit( n ) -> Bit( n ) // logic shift left of Bit(n)
    /// value positions
    ,
    { "shl", Builtin::Id::SHL, { TypeType::BIT },
        { { TypeType::BIT },
            { TypeType::UNKNOWN, TypeType::INTEGER, TypeType::BIT } },
        []( Type* ret, std::vector< Type* >& arg ) {},
        []( Builtin& self, Driver& driver, BuiltinAtom* atom,
            std::vector< Type* >& arguments ) {
            built_in_funcarg_to_retbittype( self, driver, atom, arguments, 0 );

            atom->return_type->bitsize = atom->types[ 0 ]->bitsize;
        } }

    //// shr   : Bit( n ) * Integer  -> Bit( n ) // logic shift right of Integer
    /// value positions
    //// shr   : Bit( n ) * Bit( n ) -> Bit( n ) // logic shift right of Bit(n)
    /// value positions
    ,
    { "shr", Builtin::Id::SHR, { TypeType::BIT },
        { { TypeType::BIT },
            { TypeType::UNKNOWN, TypeType::INTEGER, TypeType::BIT } },
        []( Type* ret, std::vector< Type* >& arg ) {},
        []( Builtin& self, Driver& driver, BuiltinAtom* atom,
            std::vector< Type* >& arguments ) {
            built_in_funcarg_to_retbittype( self, driver, atom, arguments, 0 );

            atom->return_type->bitsize = atom->types[ 0 ]->bitsize;
        } }

    //// ashr  : Bit( n ) * Integer  -> Bit( n ) // arithmetic shift right of
    /// Integer value positions
    //// ashr  : Bit( n ) * Bit( n ) -> Bit( n ) // arithmetic shift right of
    /// Bit(n) value positions
    ,
    { "ashr", Builtin::Id::ASHR, { TypeType::BIT },
        { { TypeType::BIT },
            { TypeType::UNKNOWN, TypeType::INTEGER, TypeType::BIT } },
        []( Type* ret, std::vector< Type* >& arg ) {},
        []( Builtin& self, Driver& driver, BuiltinAtom* atom,
            std::vector< Type* >& arguments ) {
            built_in_funcarg_to_retbittype( self, driver, atom, arguments, 0 );

            atom->return_type->bitsize = atom->types[ 0 ]->bitsize;
        } }

    // // clz   : Bit( n ) -> Bit( n ) // count leading zeros
    // {"clz", true},

    // // clo   : Bit( n ) -> Bit( n ) // count leading ones
    // {"clo", true},

    // // cls   : Bit( n ) -> Bit( n ) // count leading sign bits
    // {"cls", true},

    //// lesu  : Bit( n ) * Bit( n ) -> Boolean // less than, unsigned
    ,
    { "lesu", Builtin::Id::LESU, { TypeType::BOOLEAN },
        { { TypeType::BIT }, { TypeType::BIT } },
        []( Type* ret, std::vector< Type* >& arg ) {},
        []( Builtin& self, Driver& driver, BuiltinAtom* atom,
            std::vector< Type* >& arguments ) {
            built_in_check_bitargs( self, driver, atom, arguments );
        } }

    //// less  : Bit( n ) * Bit( n ) -> Boolean // less than, signed
    ,
    { "less", Builtin::Id::LESS, { TypeType::BOOLEAN },
        { { TypeType::BIT }, { TypeType::BIT } },
        []( Type* ret, std::vector< Type* >& arg ) {},
        []( Builtin& self, Driver& driver, BuiltinAtom* atom,
            std::vector< Type* >& arguments ) {
            built_in_check_bitargs( self, driver, atom, arguments );
        } }

    //// lequ  : Bit( n ) * Bit( n ) -> Boolean // less equals than, unsigned
    ,
    { "lequ", Builtin::Id::LEQU, { TypeType::BOOLEAN },
        { { TypeType::BIT }, { TypeType::BIT } },
        []( Type* ret, std::vector< Type* >& arg ) {},
        []( Builtin& self, Driver& driver, BuiltinAtom* atom,
            std::vector< Type* >& arguments ) {
            built_in_check_bitargs( self, driver, atom, arguments );
        } }

    //// leqs  : Bit( n ) * Bit( n ) -> Boolean // less equals than, signed
    ,
    { "leqs", Builtin::Id::LEQS, { TypeType::BOOLEAN },
        { { TypeType::BIT }, { TypeType::BIT } },
        []( Type* ret, std::vector< Type* >& arg ) {},
        []( Builtin& self, Driver& driver, BuiltinAtom* atom,
            std::vector< Type* >& arguments ) {
            built_in_check_bitargs( self, driver, atom, arguments );
        } }

    //// greu  : Bit( n ) * Bit( n ) -> Boolean // greater than, unsigned
    ,
    { "greu", Builtin::Id::GREU, { TypeType::BOOLEAN },
        { { TypeType::BIT }, { TypeType::BIT } },
        []( Type* ret, std::vector< Type* >& arg ) {},
        []( Builtin& self, Driver& driver, BuiltinAtom* atom,
            std::vector< Type* >& arguments ) {
            built_in_check_bitargs( self, driver, atom, arguments );
        } }

    //// gres  : Bit( n ) * Bit( n ) -> Boolean // greater than, signed
    ,
    { "gres", Builtin::Id::GRES, { TypeType::BOOLEAN },
        { { TypeType::BIT }, { TypeType::BIT } },
        []( Type* ret, std::vector< Type* >& arg ) {},
        []( Builtin& self, Driver& driver, BuiltinAtom* atom,
            std::vector< Type* >& arguments ) {
            built_in_check_bitargs( self, driver, atom, arguments );
        } }

    //// gequ  : Bit( n ) * Bit( n ) -> Boolean // greater equals than, unsigned
    ,
    { "gequ", Builtin::Id::GEQU, { TypeType::BOOLEAN },
        { { TypeType::BIT }, { TypeType::BIT } },
        []( Type* ret, std::vector< Type* >& arg ) {},
        []( Builtin& self, Driver& driver, BuiltinAtom* atom,
            std::vector< Type* >& arguments ) {
            built_in_check_bitargs( self, driver, atom, arguments );
        } }

    //// geqs  : Bit( n ) * Bit( n ) -> Boolean // greater equals than, signed
    ,
    { "geqs", Builtin::Id::GEQS, { TypeType::BOOLEAN },
        { { TypeType::BIT }, { TypeType::BIT } },
        []( Type* ret, std::vector< Type* >& arg ) {},
        []( Builtin& self, Driver& driver, BuiltinAtom* atom,
            std::vector< Type* >& arguments ) {
            built_in_check_bitargs( self, driver, atom, arguments );
        } }

};

Symbol::Symbol(
    const std::string& name, const yy::location& location, SymbolType type )
: name( std::move( name ) )
, location( std::move( location ) )
, type( type )
{
}

// -------------------------------------------------------------------------
// Implementation of Function
// -------------------------------------------------------------------------

uint64_t Function::counter = 0;

Function::Function( const std::string name, const yy::location& location,
    const std::vector< Type* >& args, Type* return_type,
    std::vector< std::pair< ExpressionBase*, ExpressionBase* > >* init )
: Symbol( name, location, SymbolType::FUNCTION )
, arguments_( std::move( args ) )
, intitializers_( init )
, return_type_( return_type )
, id( counter )
, is_static( false )
, is_symbolic( false )
, checkArguments( false )
, checkReturnValue( false )
{

    counter += 1;
    initRangeCheck();
}

Function::Function( const std::string name, const yy::location& location,
    const std::vector< Type* >& args, ExpressionBase* expr, Type* return_type )
: Symbol( name, location, SymbolType::DERIVED )
, arguments_( std::move( args ) )
, derived( expr )
, return_type_( return_type )
, id( counter )
, is_static( false )
, is_symbolic( false )
{
    counter += 1;
    initRangeCheck();
}

Function::Function( const std::string name, const yy::location& location,
    ExpressionBase* expr, Type* return_type )
: Function( name, location, {}, expr, return_type )
{
}

void Function::initRangeCheck()
{
    checkReturnValue
        = not is_symbolic and return_type_->has_range_restriction();
    checkArguments = std::any_of( arguments_.cbegin(), arguments_.cend(),
        []( Type* arg ) { return arg->has_range_restriction(); } );
}

Function::~Function()
{
    arguments_.clear();
    if( intitializers_ != nullptr )
    {
        for( std::pair< ExpressionBase*, ExpressionBase* > e : *intitializers_ )
        {
            delete e.first;
            delete e.second;
        }
        delete intitializers_;
    }
}

const std::string Function::to_str() const
{
    std::string res = name;

    res = ": (";
    for( Type* t : arguments_ )
    {
        res += t->to_str() + ", ";
    }
    res += ")";
    res += "-> " + return_type_->to_str();
    return res;
}

bool Function::equals( Function* other ) const
{
    if( name != other->name )
    {
        return false;
    }

    if( arguments_.size() != other->arguments_.size() )
    {
        return false;
    }
    for( size_t i = 0; i < arguments_.size(); i++ )
    {
        if( arguments_[ i ] != other->arguments_[ i ] )
        {
            return false;
        }
    }
    return return_type_ == other->return_type_;
}

bool Function::is_builtin()
{
    if( Builtin::isBuiltin( name ) )
    {
        type = SymbolType::BUILTIN;
        return true;
    }
    return false;
}

enum_value_t::enum_value_t( const std::string* name, const uint16_t id )
: name( name )
, id( id )
{
}

Enum::Enum( const std::string& name, const yy::location& location )
: Symbol( name, location, Symbol::SymbolType::ENUM )
, mapping()
{
}

bool Enum::add_enum_element( const std::string& name )
{
    if( mapping.count( name ) == 0 )
    {
        mapping[ name ]
            = new enum_value_t( new std::string( name ), mapping.size() );
        return true;
    }
    else
    {
        return false;
    }
}

uint64_t Binding::counter = 0;

Binding::Binding( const std::string& name )
: Binding( name, Type( TypeType::UNKNOWN ) )
{
}

Binding::Binding( const std::string& name, Type t )
: id( counter )
, name( name )
, type( t )
{
    counter += 1;
}

SymbolTable::SymbolTable()
{
}

SymbolTable::~SymbolTable()
{

    // cleanup symbol table
    /* TODO: check if element wise cleanup is needed
    for (auto entry : table_) {
      delete entry.second;
    }
    */
}

size_t SymbolTable::size() const
{
    return table_.size();
}

void SymbolTable::add( Symbol* sym )
{
    add_or_throw( sym->name, sym );
}

bool SymbolTable::remove( const std::string& name )
{
    return table_.erase( name ) != 0;
}

void SymbolTable::add_enum_element( const std::string& name, Enum* enum_ )
{
    add_or_throw( name, enum_ );
}

Symbol* SymbolTable::get( const std::string& name ) const
{
    const auto it = table_.find( name );
    return ( it != table_.cend() ) ? it->second : nullptr;
}

Function* SymbolTable::get_function( const std::string& name ) const
{
    // TODO split Function and Derived symbols?
    Symbol* sym = get( name );
    if( sym && ( sym->type == Symbol::SymbolType::FUNCTION
                   || sym->type == Symbol::SymbolType::DERIVED ) )
    {
        return reinterpret_cast< Function* >( sym );
    }
    else
    {
        return nullptr;
    }
}

Enum* SymbolTable::get_enum( const std::string& name ) const
{
    // TODO split Function and Derived symbols?
    Symbol* sym = get( name );
    if( sym && sym->type == Symbol::SymbolType::ENUM )
    {
        return reinterpret_cast< Enum* >( sym );
    }
    else
    {
        return nullptr;
    }
}

void SymbolTable::add_or_throw( const std::string& name, Symbol* sym )
{
    const auto result = table_.emplace( name, sym );

    if( not result.second )
    {
        const auto it = result.first;
        Symbol* existingSymbol = it->second;

        throw CompiletimeException(
            { &sym->location, &existingSymbol->location },
            "redefinition of '" + name + "'",
            libcasm_fe::Codes::IdentifierAlreadyUsed );
    }
}
