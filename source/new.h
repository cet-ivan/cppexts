// Copyright Ivan Stanojevic 2023.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __NEW_H

#define __NEW_H



#include "compspec.h"

#include <new>



using std :: bad_alloc ;
using std :: bad_array_new_length ;

using std :: align_val_t ;

using std :: nothrow_t ;
using std :: nothrow ;

using std :: new_handler ;
using std :: get_new_handler ;
using std :: set_new_handler ;


using std :: launder ;

#if defined(__gnu_compiler__)

using std :: hardware_destructive_interference_size ;
using std :: hardware_constructive_interference_size ;

#endif



#endif
