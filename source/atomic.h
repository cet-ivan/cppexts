// Copyright Ivan Stanojevic 2023.
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

using std :: atomic_bool ;
using std :: atomic_char ;
using std :: atomic_schar ;
using std :: atomic_uchar ;
using std :: atomic_short ;
using std :: atomic_ushort ;
using std :: atomic_int ;
using std :: atomic_uint ;
using std :: atomic_long ;
using std :: atomic_ulong ;
using std :: atomic_llong ;
using std :: atomic_ullong ;
using std :: atomic_char16_t ;
using std :: atomic_char32_t ;
using std :: atomic_wchar_t ;

using std :: atomic_int8_t ;
using std :: atomic_uint8_t ;
using std :: atomic_int16_t ;
using std :: atomic_uint16_t ;
using std :: atomic_int32_t ;
using std :: atomic_uint32_t ;
using std :: atomic_int64_t ;
using std :: atomic_uint64_t ;

using std :: atomic_int_least8_t ;
using std :: atomic_uint_least8_t ;
using std :: atomic_int_least16_t ;
using std :: atomic_uint_least16_t ;
using std :: atomic_int_least32_t ;
using std :: atomic_uint_least32_t ;
using std :: atomic_int_least64_t ;
using std :: atomic_uint_least64_t ;

using std :: atomic_int_fast8_t ;
using std :: atomic_uint_fast8_t ;
using std :: atomic_int_fast16_t ;
using std :: atomic_uint_fast16_t ;
using std :: atomic_int_fast32_t ;
using std :: atomic_uint_fast32_t ;
using std :: atomic_int_fast64_t ;
using std :: atomic_uint_fast64_t ;

using std :: atomic_intptr_t ;
using std :: atomic_uintptr_t ;
using std :: atomic_size_t ;
using std :: atomic_ptrdiff_t ;
using std :: atomic_intmax_t ;
using std :: atomic_uintmax_t ;

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
