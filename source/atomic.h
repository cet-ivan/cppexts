// Copyright Ivan Stanojevic 2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __ATOMIC_H

#define __ATOMIC_H



#include "compspec.h"

#include <atomic>



using std :: memory_order ;
using std :: kill_dependency ;
using std :: atomic ;

using std :: atomic_is_lock_free ;
using std :: atomic_init ;
using std :: atomic_store ;
using std :: atomic_store_explicit ;
using std :: atomic_load ;
using std :: atomic_load_explicit ;
using std :: atomic_exchange ;
using std :: atomic_exchange_explicit ;
using std :: atomic_compare_exchange_weak ;
using std :: atomic_compare_exchange_strong ;
using std :: atomic_compare_exchange_weak_explicit ;
using std :: atomic_compare_exchange_strong_explicit ;

using std :: atomic_fetch_add ;
using std :: atomic_fetch_add_explicit ;
using std :: atomic_fetch_sub ;
using std :: atomic_fetch_sub_explicit ;
using std :: atomic_fetch_and ;
using std :: atomic_fetch_and_explicit ;
using std :: atomic_fetch_or ;
using std :: atomic_fetch_or_explicit ;
using std :: atomic_fetch_xor ;
using std :: atomic_fetch_xor_explicit ;

using std :: atomic_flag ;
using std :: atomic_flag_test_and_set ;
using std :: atomic_flag_test_and_set_explicit ;
using std :: atomic_flag_clear ;
using std :: atomic_flag_clear_explicit ;

using std :: atomic_thread_fence ;
using std :: atomic_signal_fence ;



// *** EXTENSIONS ***


#if     defined(__gnu_compiler__) \
    ||  defined(__clang_compiler__) \
    ||  defined(__mingw_compiler__)


//

#define __DEFINE_ATOMIC_EXCHANGE(Type)           \
                                                 \
inline Type atomic_exchange ( Type & x, Type y ) \
                                                 \
{                                                \
return __sync_lock_test_and_set ( & x, y ) ;     \
}

FOR_BUILTIN_INTEGRAL_TYPES(__DEFINE_ATOMIC_EXCHANGE)

#undef __DEFINE_ATOMIC_EXCHANGE


//

#define __DEFINE_ATOMIC_FETCH_ADD(Type)           \
                                                  \
inline Type atomic_fetch_add ( Type & x, Type y ) \
                                                  \
{                                                 \
return __sync_fetch_and_add ( & x, y ) ;          \
}

FOR_BUILTIN_INTEGRAL_TYPES(__DEFINE_ATOMIC_FETCH_ADD)

#undef __DEFINE_ATOMIC_FETCH_ADD


//

#define __DEFINE_ATOMIC_FETCH_SUB(Type)           \
                                                  \
inline Type atomic_fetch_sub ( Type & x, Type y ) \
                                                  \
{                                                 \
return __sync_fetch_and_sub ( & x, y ) ;          \
}

FOR_BUILTIN_INTEGRAL_TYPES(__DEFINE_ATOMIC_FETCH_SUB)

#undef __DEFINE_ATOMIC_FETCH_SUB


//

#define __DEFINE_ATOMIC_FETCH_AND(Type)           \
                                                  \
inline Type atomic_fetch_and ( Type & x, Type y ) \
                                                  \
{                                                 \
return __sync_fetch_and_and ( & x, y ) ;          \
}

FOR_BUILTIN_INTEGRAL_TYPES(__DEFINE_ATOMIC_FETCH_AND)

#undef __DEFINE_ATOMIC_FETCH_AND


//

#define __DEFINE_ATOMIC_FETCH_OR(Type)           \
                                                 \
inline Type atomic_fetch_or ( Type & x, Type y ) \
                                                 \
{                                                \
return __sync_fetch_and_or ( & x, y ) ;          \
}

FOR_BUILTIN_INTEGRAL_TYPES(__DEFINE_ATOMIC_FETCH_OR)

#undef __DEFINE_ATOMIC_FETCH_OR


//

#define __DEFINE_ATOMIC_FETCH_XOR(Type)           \
                                                  \
inline Type atomic_fetch_xor ( Type & x, Type y ) \
                                                  \
{                                                 \
return __sync_fetch_and_xor ( & x, y ) ;          \
}

FOR_BUILTIN_INTEGRAL_TYPES(__DEFINE_ATOMIC_FETCH_XOR)

#undef __DEFINE_ATOMIC_FETCH_XOR


#endif



#endif
