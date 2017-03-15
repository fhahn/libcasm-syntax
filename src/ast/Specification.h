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

#ifndef _LIB_CASMFE_SPECIFICATION_H_
#define _LIB_CASMFE_SPECIFICATION_H_

#include "Node.h"

#include "Definition.h"

namespace libcasm_fe
{
    namespace Ast
    {
        class Specification : public Node
        {
          public:
            using Ptr = std::shared_ptr< Specification >;

            Specification( const IdentifierNode::Ptr& name,
                const Definitions::Ptr& definitions );

            IdentifierNode::Ptr name( void ) const;
            Definitions::Ptr definitions( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            IdentifierNode::Ptr m_name;
            Definitions::Ptr m_definitions;
        };
    }
}

#endif // _LIB_CASMFE_SPECIFICATION_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//