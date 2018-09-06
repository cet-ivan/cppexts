// Copyright Ivan Stanojevic 2015.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __FUNCTIONAL_H

#define __FUNCTIONAL_H



#include <functional>



// using std :: unary_function ;
// using std :: binary_function ;

using std :: reference_wrapper ;
using std :: ref ;
using std :: cref ;

using std :: plus ;
using std :: minus ;
using std :: multiplies ;
using std :: divides ;
using std :: modulus ;
using std :: negate ;

using std :: equal_to ;
using std :: not_equal_to ;
using std :: greater ;
using std :: less ;
using std :: greater_equal ;
using std :: less_equal ;

using std :: logical_and ;
using std :: logical_or ;
using std :: logical_not ;

using std :: bit_and ;
using std :: bit_or ;
using std :: bit_xor ;

using std :: unary_negate ;
using std :: not1 ;
using std :: binary_negate ;
using std :: not2 ;

using std :: is_bind_expression ;
using std :: is_placeholder ;
using std :: bind ;
namespace placeholders = std :: placeholders ;

// using std :: binder1st ;
// using std :: bind1st ;
// using std :: binder2nd ;
// using std :: bind2nd ;

// using std :: pointer_to_unary_function ;
// using std :: pointer_to_binary_function ;
// using std :: ptr_fun ;

// using std :: mem_fun_t ;
// using std :: mem_fun1_t ;
// using std :: const_mem_fun_t ;
// using std :: const_mem_fun1_t ;
// using std :: mem_fun ;

// using std :: mem_fun_ref_t ;
// using std :: mem_fun1_ref_t ;
// using std :: const_mem_fun_ref_t ;
// using std :: const_mem_fun1_ref_t ;
// using std :: mem_fun_ref ;

using std :: mem_fn ;

using std :: bad_function_call ;
using std :: function ;

using std :: hash ;



#endif
