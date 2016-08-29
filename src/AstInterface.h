//  
//  Copyright (c) 2014-2016 CASM Organization
//  All rights reserved.
//  
//  Developed by: Florian Hahn
//                Philipp Paulweber
//                Emmanuel Pescosta
//                https://github.com/ppaulweber/libcasm-fe
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

#ifndef _LIB_CASMFE_ASTINTERFACE_H_
#define _LIB_CASMFE_ASTINTERFACE_H_

#include "Driver.h"
#include "Visitor.h"
#include "AstDumpVisitor.h"

/**
   @brief    TODO
   
   TODO
*/
namespace libcasm_fe
{
    template<class T> class AstInterface // : public CasmAST
    {
    public:
        
        void visit_init( InitNode* node )
        {
        }
        
        void visit_specification( SpecificationNode* node )
        {
        }
        
        void visit_body_elements( AstNode* node )
        {
        }
        
        void visit_function_def( FunctionDefNode* node, const std::vector<std::pair<T, T>>& inits )
        {
        }
        
        void visit_derived_function_atom_pre( FunctionAtom* node, T args[], uint16_t argc )
        {
        }
        
        void visit_derived_def_pre( FunctionDefNode* node )
        {
        }
        
        void visit_derived_def( FunctionDefNode* node, T expr )
        {
        }
        
        virtual void visit_rule( RuleNode* node ) = 0;
        virtual void visit_rule_post( RuleNode* node ) = 0;
        
        void visit_skip(AstNode* node)
        {
        }
        
        void visit_statements( AstNode* node )
        {
        }
        
        void visit_parblock( AstNode* node )
        {
        }
        
        void visit_seqblock( AstNode* node )
        {
        }
        
        void visit_forall_pre( AstNode* node )
        {
        }
        
        void visit_forall_post( AstNode* node )
        {
        }
        
        void visit_iterate( AstNode* node )
        {
        }
        
        void visit_update( UpdateNode* node, T func, T expr )
        {
        }
    
        void visit_update_dumps( UpdateNode* node, T func, T expr )
        {
        }
    
        void visit_call_pre( CallNode* node )
        {
        }
    
        void visit_call_pre( CallNode* node, T expr )
        {
        }
    
        void visit_call( CallNode* node, std::vector< T >& args )
        {
        }
    
        void visit_call_post( CallNode* node )
        {
        }
    
        void visit_print( PrintNode* node, std::vector< T >& args )
        {
        }
    
        void visit_diedie( DiedieNode* node, T msg )
        {
        }
    
        void visit_impossible( AstNode* node )
        {
        }
    
        void visit_assert( UnaryNode* node, T expr )
        {
        }
    
        void visit_assure( UnaryNode* node, T expr )
        {
        }
    
        void visit_let( LetNode* node, T var )
        {
        }
    
        void visit_let_post( LetNode* node )
        {
        }
    
        void visit_push( PushNode* node, T expr, T atom )
        {
        }
    
        void visit_pop( PopNode* node )
        {
        }
    
        void visit_ifthenelse( IfThenElseNode* node, T cond )
        {
        }
    
        void visit_case_pre( CaseNode* node, T val )
        {
        }
        
        void visit_case( CaseNode* node, T val, const std::vector< T >& case_labels )
        {
        }
        
        T visit_expression( Expression* node, T lhs, T rhs )
        {
            return 0;
        }
    
        T visit_expression_single( Expression* node, T val )
        {
            return 0;
        }
    
        T visit_function_atom( FunctionAtom* node, T args[], uint16_t argc )
        { 
            return 0;
        }
    
        T visit_derived_function_atom( FunctionAtom* node, T expr )
        {
            return 0;
        }
    
        T visit_zero_atom( ZeroAtom* node )
        {
            return 0;
        }

        T visit_int_atom( IntegerAtom* node )
        {
            return 0;
        }

        virtual T visit_bit_atom( IntegerAtom* node ) = 0;
        
                T visit_floating_atom( FloatingAtom* node )
        {
            return 0;
        }
    
        T visit_rational_atom( RationalAtom* node )
        {
            return 0;
        }
    
        T visit_undef_atom( UndefAtom* node )
        {
            return 0;
        }
    
        T visit_self_atom( SelfAtom* node )
        {
            return 0;
        }
    
        T visit_rule_atom( RuleAtom* node )
        {
            return 0;
        }
    
        T visit_boolean_atom( BooleanAtom* node )
        {
            return 0;
        }
    
        T visit_string_atom( StringAtom* node )
        {
            return 0;
        }
    
        T visit_list_atom( ListAtom* node, std::vector< T >& args )
        { 
            return 0;
        }
    
        T visit_number_range_atom( NumberRangeAtom* node )
        { 
            return 0; 
        }
    
        T visit_builtin_atom( BuiltinAtom* node, T args[], uint16_t argc ) 
        {
            return 0;
        }
    };
}

#endif /* _LIB_CASMFE_ASTINTERFACE_H_ */


//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
