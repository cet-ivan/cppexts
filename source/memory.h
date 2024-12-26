// Copyright Ivan Stanojevic 2023.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __MEMORY_H

#define __MEMORY_H



#include "compspec.h"

#include <memory>



using std :: pointer_traits ;

#if defined(__gnu_compiler__)  &&  __GNUC >= 6

using std :: pointer_safety ;
using std :: declare_reachable ;
using std :: undeclare_reachable ;
using std :: declare_no_pointers ;
using std :: undeclare_no_pointers ;
using std :: get_pointer_safety ;

#endif

using std :: align ;

using std :: allocator_arg_t ;
using std :: allocator_arg ;

using std :: uses_allocator ;
using std :: uses_allocator_v ;

using std :: allocator_traits ;

using std :: allocator ;

using std :: addressof ;

using std :: uninitialized_default_construct ;
using std :: uninitialized_default_construct_n ;
using std :: uninitialized_value_construct ;
using std :: uninitialized_value_construct_n ;
using std :: uninitialized_copy ;
using std :: uninitialized_copy_n ;
using std :: uninitialized_move ;
using std :: uninitialized_move_n ;
using std :: uninitialized_fill ;
using std :: uninitialized_fill_n ;
using std :: destroy_at ;
using std :: destroy ;
using std :: destroy_n ;

using std :: default_delete ;
using std :: unique_ptr ;

using std :: swap ;

using std :: bad_weak_ptr ;

using std :: shared_ptr ;
using std :: make_shared ;
using std :: allocate_shared ;

using std :: static_pointer_cast ;
using std :: dynamic_pointer_cast ;
using std :: const_pointer_cast ;
using std :: reinterpret_pointer_cast ;

using std :: get_deleter ;

using std :: weak_ptr ;

using std :: owner_less ;

using std :: enable_shared_from_this ;

using std :: atomic_is_lock_free ;
using std :: atomic_load ;
using std :: atomic_load_explicit ;
using std :: atomic_store ;
using std :: atomic_store_explicit ;
using std :: atomic_exchange ;
using std :: atomic_exchange_explicit ;
using std :: atomic_compare_exchange_weak ;
using std :: atomic_compare_exchange_strong ;
using std :: atomic_compare_exchange_weak_explicit ;
using std :: atomic_compare_exchange_strong_explicit ;

using std :: hash ;

using std :: operator == ;
using std :: operator != ;
using std :: operator < ;
using std :: operator > ;
using std :: operator <= ;
using std :: operator >= ;

using std :: operator << ;


// using std :: raw_storage_iterator ;

// using std :: get_temporary_buffer ;
// using std :: return_temporary_buffer ;

// using std :: auto_ptr ;



#endif
