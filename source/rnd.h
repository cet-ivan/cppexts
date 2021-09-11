// Copyright Ivan Stanojevic 2021.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __RND_H

#define __RND_H



#include "cmath.h"
#include "cstdlib.h"
#include "mutex.h"

#include "numbase.h"
#include "spinlock.h"
#include "typeconv.h"



// *** PLATFORM SPECIFIC ***


#if defined(__unix__)


#include "ios.h"
#include "fstream.h"


//

template < class Integer >
Integer platform_integer_seed ( )

{
ifstream random_device ( "/dev/urandom", ios_base :: binary ) ;

if ( ! random_device.good ( ) )
  return 0 ;

Integer result ( 0 ) ;

for ( sint b = 0 ; b < numeric_traits < Integer > :: byte_size ; ++ b )
  result = ( result << 8 ) + random_device.get ( ) ;

return result ;
}


//

template < class FloatingPoint >
FloatingPoint platform_floating_point_seed ( )

{
ifstream random_device ( "/dev/urandom", ios_base :: binary ) ;

if ( ! random_device.good ( ) )
  return 0 ;

FloatingPoint result ( 0 ) ;

for ( sint b = 0 ;
           b < numeric_traits < FloatingPoint > :: mantissa_bit_size ;
           b += 8 )
  result = ldexp ( result + random_device.get ( ), -8 ) ;

return result ;
}


#elif defined(_WIN32) || defined(_WIN64)


#include "windows.h"


//

template < class Integer >
Integer platform_integer_seed ( )

{
HCRYPTPROV csp ;

BOOL cac_status = CryptAcquireContext ( & csp,
                                        nullptr,
                                        nullptr,
                                        PROV_RSA_FULL,
                                        CRYPT_VERIFYCONTEXT ) ;

if ( cac_status )
  {
  constexpr size_t result_byte_size = numeric_traits < Integer > :: byte_size ;

  BYTE result_bytes [ result_byte_size ] ;
  BOOL cgr_status = CryptGenRandom ( csp, result_byte_size, result_bytes ) ;

  CryptReleaseContext ( csp, 0 ) ;

  if ( cgr_status )
    {
    Integer result ( 0 ) ;

    for ( BYTE b : result_bytes )
      result = ( result << 8 ) + b ;

    return result ;
    }
  }

return 0 ;
}


//

template < class FloatingPoint >
FloatingPoint platform_floating_point_seed ( )

{
HCRYPTPROV csp ;

BOOL cac_status = CryptAcquireContext ( & csp,
                                        nullptr,
                                        nullptr,
                                        PROV_RSA_FULL,
                                        CRYPT_VERIFYCONTEXT ) ;

if ( cac_status )
  {
  constexpr size_t
    result_byte_size =
      ( numeric_traits < FloatingPoint > :: mantissa_bit_size + 7 ) >> 3 ;

  BYTE result_bytes [ result_byte_size ] ;
  BOOL cgr_status = CryptGenRandom ( csp, result_byte_size, result_bytes ) ;

  CryptReleaseContext ( csp, 0 ) ;

  if ( cgr_status )
    {
    FloatingPoint result ( 0 ) ;

    for ( BYTE b : result_bytes )
      result = ldexp ( result + b, -8 ) ;

    return result ;
    }
  }

return 0 ;
}


#endif



// *** SYSTEM_RND_STATIC_GENERATOR ***


class system_rnd_static_generator

{
private:

  class initializer

  {
  public:

    initializer ( )
      { srand ( platform_integer_seed < unsigned int > ( ) ) ; }

  } ;

  static spinlock sl ;
  static initializer init ;

public:

  static int operate ( )
    { lock_guard < spinlock > lck ( sl ) ;
      return rand ( ) ; }

} ;



// *** FLOATING_POINT_RND_STATIC_GENERATOR ***


template < class FloatingPoint >
class floating_point_rnd_static_generator

{
private:

  static const size_t ld_buffer_size = 7 ;
  static const size_t buffer_size = size_t ( 1 ) << ld_buffer_size ;
  static const size_t buffer_size_mask = buffer_size - 1 ;

  class buffer

  {
  public:

    FloatingPoint data [ buffer_size ] ;

    buffer ( )
      { for ( FloatingPoint & d : data )
          d = generate ( ) ; }

  } ;

  static FloatingPoint a1, a2 ;
  static const FloatingPoint c ;
  static buffer b ;
  static spinlock sl ;

  static FloatingPoint generate ( )
    { FloatingPoint a = a1 + a2 + c ;
      a -= floor ( a ) ;
      a2 = a1 ;
      a1 = a ;
      return a ; }

public:

  static FloatingPoint operate ( ) ;

} ;


//

template < class FloatingPoint >
FloatingPoint
  floating_point_rnd_static_generator < FloatingPoint > ::
    a1 ( platform_floating_point_seed < FloatingPoint > ( ) ) ;


//

template < class FloatingPoint >
FloatingPoint
  floating_point_rnd_static_generator < FloatingPoint > ::
    a2 ( platform_floating_point_seed < FloatingPoint > ( ) ) ;


template < class FloatingPoint >
const FloatingPoint
  floating_point_rnd_static_generator < FloatingPoint > ::
    c ( ldexp ( FloatingPoint ( 2 ) / 3,
                - numeric_traits < FloatingPoint > :: mantissa_bit_size ) ) ;


//

template < class FloatingPoint >
typename floating_point_rnd_static_generator < FloatingPoint > :: buffer
  floating_point_rnd_static_generator < FloatingPoint > :: b ;


//

template < class FloatingPoint >
spinlock floating_point_rnd_static_generator < FloatingPoint > :: sl ;


//

template < class FloatingPoint >
FloatingPoint
  floating_point_rnd_static_generator < FloatingPoint > :: operate ( )

{
FloatingPoint &
  v = b.data [ system_rnd_static_generator :: operate ( ) & buffer_size_mask ] ;

lock_guard < spinlock > lck ( sl ) ;

v += generate ( ) ;
v -= floor ( v ) ;

return v ;
}



// *** UNSIGNED_INT_RND_STATIC_GENERATOR ***


template < class UnsignedInt, class FloatingPoint >
class unsigned_int_rnd_static_generator

{
public:

  static UnsignedInt operate ( )
    { UnsignedInt result ( 0 ) ;
      sint b = numeric_traits < UnsignedInt > :: bit_size ;
      do
        {
        result +=
          convert_to < UnsignedInt >
            ( ldexp ( floating_point_rnd_static_generator < FloatingPoint > ::
                        operate ( ),
                      b ) ) ;
        b -= numeric_traits < FloatingPoint > :: mantissa_bit_size ;
        }
      while ( b > 0 ) ;
      return result ; }

} ;



// *** SIGNED_INT_RND_STATIC_GENERATOR ***


template < class SignedInt, class FloatingPoint >
class signed_int_rnd_static_generator

{
public:

  static SignedInt operate ( )
    { return convert_to < SignedInt >
               ( unsigned_int_rnd_static_generator
                   < typename numeric_traits < SignedInt > :: unsigned_type,
                     FloatingPoint > ::
                   operate ( ) ) ; }

} ;



// *** RND_STATIC_GENERATOR ***


//

template < class T >
class rnd_static_generator ;


//

#define __DEFINE_RND_STATIC_GENERATOR(Type)           \
                                                      \
template < >                                          \
class rnd_static_generator < Type > :                 \
  public floating_point_rnd_static_generator < Type > \
                                                      \
{                                                     \
} ;

FOR_BUILTIN_FLOATING_POINT_TYPES(__DEFINE_RND_STATIC_GENERATOR)

#undef __DEFINE_RND_STATIC_GENERATOR


//

#define __DEFINE_RND_STATIC_GENERATOR(Type)                 \
                                                            \
template < >                                                \
class rnd_static_generator < Type > :                       \
  public unsigned_int_rnd_static_generator < Type, double > \
                                                            \
{                                                           \
} ;

FOR_BUILTIN_UNSIGNED_INTEGRAL_TYPES(__DEFINE_RND_STATIC_GENERATOR)

#undef __DEFINE_RND_STATIC_GENERATOR


//

#define __DEFINE_RND_STATIC_GENERATOR(Type)               \
                                                          \
template < >                                              \
class rnd_static_generator < Type > :                     \
  public signed_int_rnd_static_generator < Type, double > \
                                                          \
{                                                         \
} ;

FOR_BUILTIN_SIGNED_INTEGRAL_TYPES(__DEFINE_RND_STATIC_GENERATOR)

#undef __DEFINE_RND_STATIC_GENERATOR



// *** RND ***


//

template < class T >
inline T rnd ( )

{
return rnd_static_generator < T > :: operate ( ) ;
}



// *** RND_GENERATOR ***


template < class T >
class rnd_generator

{
public:

  T operator ( ) ( ) const
    { return rnd < T > ( ) ; }

} ;



// *** FLOATING_POINT_RANGE_RND_STATIC_GENERATOR ***


template < class FloatingPoint >
class floating_point_range_rnd_static_generator

{
public:

  static FloatingPoint
           operate ( const FloatingPoint & a, const FloatingPoint & b )
    { return   a < b
             ? a + rnd < FloatingPoint > ( ) * ( b - a )
             : a ; }

} ;



// *** UNSIGNED_INT_RANGE_RND_STATIC_GENERATOR ***


//

template < class UnsignedInt >
class unsigned_int_range_rnd_static_generator

{
public:

  static UnsignedInt operate ( const UnsignedInt & a, const UnsignedInt & b )
    { return   a < b
             ? a + rnd < UnsignedInt > ( ) % ( b - a )
             : a ; }

} ;



// *** SIGNED_INT_RANGE_RND_STATIC_GENERATOR ***


//

template < class SignedInt >
class signed_int_range_rnd_static_generator

{
private:

  typedef typename numeric_traits < SignedInt > :: unsigned_type unsigned_type ;

public:

  static SignedInt operate ( const SignedInt & a, const SignedInt & b )
    { return   a < b
             ? a + convert_to < SignedInt >
                     ( rnd < unsigned_type > ( ) % unsigned_type ( b - a ) )
             : a ; }

} ;



// *** RANGE_RND_STATIC_GENERATOR ***


//

template < class T >
class range_rnd_static_generator ;


//

#define __DEFINE_RANGE_RND_STATIC_GENERATOR(Type)           \
                                                            \
template < >                                                \
class range_rnd_static_generator < Type > :                 \
  public floating_point_range_rnd_static_generator < Type > \
                                                            \
{                                                           \
} ;

FOR_BUILTIN_FLOATING_POINT_TYPES(__DEFINE_RANGE_RND_STATIC_GENERATOR)

#undef __DEFINE_RANGE_RND_STATIC_GENERATOR


//

#define __DEFINE_RANGE_RND_STATIC_GENERATOR(Type)         \
                                                          \
template < >                                              \
class range_rnd_static_generator < Type > :               \
  public unsigned_int_range_rnd_static_generator < Type > \
                                                          \
{                                                         \
} ;

FOR_BUILTIN_UNSIGNED_INTEGRAL_TYPES(__DEFINE_RANGE_RND_STATIC_GENERATOR)

#undef __DEFINE_RANGE_RND_STATIC_GENERATOR


//

#define __DEFINE_RANGE_RND_STATIC_GENERATOR(Type)       \
                                                        \
template < >                                            \
class range_rnd_static_generator < Type > :             \
  public signed_int_range_rnd_static_generator < Type > \
                                                        \
{                                                       \
} ;

FOR_BUILTIN_SIGNED_INTEGRAL_TYPES(__DEFINE_RANGE_RND_STATIC_GENERATOR)

#undef __DEFINE_RANGE_RND_STATIC_GENERATOR



// *** RANGE_RND ***


//

template < class T >
inline T range_rnd ( const T & a, const T & b )

{
return range_rnd_static_generator < T > :: operate ( a, b ) ;
}



// *** RANGE_RND_GENERATOR ***


template < class T >
class range_rnd_generator

{
private:

  T a, b ;

public:

  range_rnd_generator ( const T & i_a, const T & i_b ) :
    a ( i_a ),
    b ( i_b )
    { }

  T operator ( ) ( ) const
    { return range_rnd < T > ( a, b ) ; }

} ;



// *** GAUSS_RND_STATIC_GENERATOR ***


template < class FloatingPoint >
class gauss_rnd_static_generator

{
private:

  static bool s_ready ;
  static FloatingPoint s ;
  static spinlock sl ;

public:

  static FloatingPoint operate ( ) ;

} ;


//

template < class FloatingPoint >
bool gauss_rnd_static_generator < FloatingPoint > :: s_ready = false ;


//

template < class FloatingPoint >
FloatingPoint gauss_rnd_static_generator < FloatingPoint > :: s ;


//

template < class FloatingPoint >
spinlock gauss_rnd_static_generator < FloatingPoint > :: sl ;


//

template < class FloatingPoint >
FloatingPoint gauss_rnd_static_generator < FloatingPoint > :: operate ( )

{
lock_guard < spinlock > lck ( sl ) ;

if ( s_ready )
  {
  s_ready = false ;
  return s ;
  }

FloatingPoint r = sqrt ( -2 * log ( rnd < FloatingPoint > ( ) ) ),
              t =   ( 2 * numeric_constants < FloatingPoint > :: pi ( ) )
                  * rnd < FloatingPoint > ( ) ;

s = r * sin ( t ) ;
s_ready = true ;

return r * cos ( t ) ;
}



// *** GAUSS_RND ***


//

template < class FloatingPoint >
inline FloatingPoint gauss_rnd ( )

{
return gauss_rnd_static_generator < FloatingPoint > :: operate ( ) ;
}



// *** GAUSS_RND_GENERATOR ***


template < class FloatingPoint >
class gauss_rnd_generator

{
private:

  FloatingPoint m, sigma ;

public:

  typedef FloatingPoint result_type ;

  gauss_rnd_generator ( ) :
    m ( 0 ),
    sigma ( 1 )
    { }

  gauss_rnd_generator ( const FloatingPoint & i_m,
                        const FloatingPoint & i_sigma ) :
    m ( i_m ),
    sigma ( i_sigma )
    { }

  FloatingPoint operator ( ) ( ) const
    { return sigma * gauss_rnd < FloatingPoint > ( ) + m ; }

} ;



#endif
