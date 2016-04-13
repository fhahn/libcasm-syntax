//  
//  Copyright (c) 2014-2016, Florian Hahn, Philipp Paulweber
//  All rights reserved.
//  
//  Developed by: Florian Hahn
//                Philipp Paulweber
//                https://github.com/ppaulweber/libcasm-fe
//  
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program. If not, see <http://www.gnu.org/licenses/>.
//  

#ifndef CASM_FRONTEND_H
#define CASM_FRONTEND_H

#include <utility>
#include <string>

#include "libsyntax/ast.h"

void casm_frontend_init();

void casm_frontend_destroy();

AstNode* casm_frontend_pass_1_parse(const std::string& filename);

bool casm_frontend_pass_2_typecheck(AstNode *root);

std::string casm_dump_ast(AstNode *root);
#endif
