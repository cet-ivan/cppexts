// Copyright Ivan Stanojevic 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __TYPE_TRAITS_H

#define __TYPE_TRAITS_H



#include "compspec.h"

#include <type_traits>



using std :: integral_constant ;
using std :: true_type ;
using std :: false_type ;

using std :: is_void ;
using std :: is_integral ;
using std :: is_floating_point ;
using std :: is_array ;
using std :: is_pointer ;
using std :: is_lvalue_reference ;
using std :: is_rvalue_reference ;
using std :: is_member_object_pointer ;
using std :: is_member_function_pointer ;
using std :: is_enum ;
using std :: is_union ;
using std :: is_class ;
using std :: is_function ;

using std :: is_reference ;
using std :: is_arithmetic ;
using std :: is_fundamental ;
using std :: is_object ;
using std :: is_scalar ;
using std :: is_compound ;
using std :: is_member_pointer ;

using std :: is_const ;
using std :: is_volatile ;
using std :: is_trivial ;
using std :: is_trivially_copyable ;
using std :: is_standard_layout ;
using std :: is_pod ;
using std :: is_literal_type ;
using std :: is_empty ;
using std :: is_polymorphic ;
using std :: is_abstract ;

using std :: is_signed ;
using std :: is_unsigned ;

using std :: is_constructible ;
using std :: is_default_constructible ;
using std :: is_copy_constructible ;
using std :: is_move_constructible ;

using std :: is_assignable ;
using std :: is_copy_assignable ;
using std :: is_move_assignable ;

using std :: is_destructible ;

using std :: is_trivially_constructible ;
using std :: is_trivially_default_constructible ;
using std :: is_trivially_copy_constructible ;
using std :: is_trivially_move_constructible ;

using std :: is_trivially_assignable ;
using std :: is_trivially_copy_assignable ;
using std :: is_trivially_move_assignable ;

using std :: is_trivially_destructible ;

using std :: is_nothrow_constructible ;
using std :: is_nothrow_default_constructible ;
using std :: is_nothrow_copy_constructible ;
using std :: is_nothrow_move_constructible ;

using std :: is_nothrow_assignable ;
using std :: is_nothrow_copy_assignable ;
using std :: is_nothrow_move_assignable ;

using std :: is_nothrow_destructible ;
using std :: has_virtual_destructor ;

using std :: alignment_of ;
using std :: rank ;
using std :: extent ;

using std :: is_same ;
using std :: is_base_of ;
using std :: is_convertible ;

using std :: remove_const ;
using std :: remove_volatile ;
using std :: remove_cv ;
using std :: add_const ;
using std :: add_volatile ;
using std :: add_cv ;

using std :: remove_reference ;
using std :: add_lvalue_reference ;
using std :: add_rvalue_reference ;

using std :: make_signed ;
using std :: make_unsigned ;

using std :: remove_extent ;
using std :: remove_all_extents ;

using std :: remove_pointer ;
using std :: add_pointer ;

using std :: aligned_storage ;
using std :: decay ;
using std :: enable_if ;
using std :: conditional ;
using std :: common_type ;
using std :: underlying_type ;
using std :: result_of ;



#endif
