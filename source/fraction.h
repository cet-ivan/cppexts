// Copyright Ivan Stanojevic 2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __FRACTION_H

#define __FRACTION_H



#include "compspec.h"

#include "cassert.h"
#include "utility.h"

#include "numbase.h"
#include "streaming.h"
#include "typeconv.h"
#include "exint.h"



// *** GLOBALS ***


//

template < class T >
inline void normalize_fraction ( T & /* a */, T & /* b */ )

{
}


//

#define __DEFINE_NORMALIZE_FRACTION(Type)             \
                                                      \
inline void normalize_fraction ( Type & a, Type & b ) \
                                                      \
{                                                     \
if ( b < 0 )                                          \
  {                                                   \
  a = - a ;                                           \
  b = - b ;                                           \
  }                                                   \
}

FOR_BUILTIN_SIGNED_INTEGRAL_TYPES(__DEFINE_NORMALIZE_FRACTION)

#undef __DEFINE_NORMALIZE_FRACTION


//

template < class T >
inline void reduce_fraction ( T & a, T & b )

{
assert ( b != T ( 0 ) ) ;

T g ( raw_gcd ( a, b ) ) ;

a /= g ;
b /= g ;

normalize_fraction ( a, b ) ;
}



// *** FORWARD DECLARATIONS ***


template < class T >
class __fraction_base ;

template < class T >
class fraction ;

template < class T >
fraction < T > operator + ( const __fraction_base < T > & a,
                            const __fraction_base < T > & b ) ;

template < class T >
fraction < T > operator + ( const fraction < T > & a, const T & b ) ;

template < class T >
fraction < T > operator + ( const T & a, const fraction < T > & b ) ;

template < class T >
fraction < T > operator - ( const __fraction_base < T > & a,
                            const __fraction_base < T > & b ) ;

template < class T >
fraction < T > operator - ( const fraction < T > & a, const T & b ) ;

template < class T >
fraction < T > operator - ( const T & a, const fraction < T > & b ) ;

template < class T >
fraction < T > operator * ( const __fraction_base < T > & a,
                            const __fraction_base < T > & b ) ;

template < class T >
fraction < T > operator * ( const fraction < T > & a, const T & b ) ;

template < class T >
fraction < T > operator * ( const T & a, const fraction < T > & b ) ;

template < class T >
fraction < T > operator / ( const __fraction_base < T > & a,
                            const __fraction_base < T > & b ) ;

template < class T >
fraction < T > operator / ( const fraction < T > & a, const T & b ) ;

template < class T >
fraction < T > operator / ( const T & a, const fraction < T > & b ) ;

template < class T >
bool operator == ( const fraction < T > & a, const fraction < T > & b ) ;

template < class T >
bool operator < ( const fraction < T > & a, const fraction < T > & b ) ;



// *** __FRACTION_BASE ***


template < class T >
class __fraction_base

{
private:

  friend class fraction < T > ;

  __fraction_base ( ) = default ;
  ~__fraction_base ( ) = default ;
  __fraction_base ( const __fraction_base & ) = default ;
  __fraction_base ( __fraction_base && ) = default ;
  __fraction_base & operator = ( const __fraction_base & ) = default ;
  __fraction_base & operator = ( __fraction_base && ) = default ;

} ;



// *** FRACTION ***


template < class T >
class fraction : public __fraction_base < T >

{
private:

  class no_reduction_tag { } ;

  T numerator_,
    denominator_ ;

  void normalize ( )
    { normalize_fraction ( numerator_, denominator_ ) ; }

  void reduce ( )
    { reduce_fraction ( numerator_, denominator_ ) ; }

  fraction ( const T & i_numerator, const T & i_denominator,
             no_reduction_tag ) :
    numerator_ ( i_numerator ),
    denominator_ ( i_denominator )
    { }

public:

  fraction ( const T & i_numerator = T ( 0 ),
             const T & i_denominator = T ( 1 ) ) :
    numerator_ ( i_numerator ),
    denominator_ ( i_denominator )
    { assert ( i_denominator != T ( 0 ) ) ;
      reduce ( ) ; }

  template < class S >
  fraction ( const S & x,
             typename implicit_conversion_test < S, T > :: result =
               implicit_conversion_allowed ) :
    numerator_ ( x ),
    denominator_ ( 1 )
    { reduce ( ) ; }

  const T & numerator ( ) const
    { return numerator_ ; }

  const T & denominator ( ) const
    { return denominator_ ; }

  void negate ( )
    { numerator_ = - numerator_ ; }

  void invert ( )
    { assert ( numerator_ != T ( 0 ) ) ;
      swap ( numerator_, denominator_ ) ;
      normalize ( ) ; }

  const fraction & operator + ( ) const
    { return * this ; }

  fraction operator - ( ) const
    { return fraction ( - numerator_, denominator_, no_reduction_tag ( ) ) ; }

  friend fraction operator + ( const __fraction_base < T > & a,
                               const __fraction_base < T > & b )
    { const fraction & ar = static_cast < const fraction & > ( a ),
                     & br = static_cast < const fraction & > ( b ) ;
      return fraction (   ar.numerator_ * br.denominator_
                        + ar.denominator_ * br.numerator_,
                        ar.denominator_ * br.denominator_ ) ; }

  friend fraction operator + ( const fraction & a, const T & b )
    { return fraction ( a.numerator_ + a.denominator_ * b,
                        a.denominator_ ) ; }

  friend fraction operator + ( const T & a, const fraction & b )
    { return fraction ( a * b.denominator_ + b.numerator_,
                        b.denominator_ ) ; }

  friend fraction operator - ( const __fraction_base < T > & a,
                               const __fraction_base < T > & b )
    { const fraction & ar = static_cast < const fraction & > ( a ),
                     & br = static_cast < const fraction & > ( b ) ;
      return fraction (   ar.numerator_ * br.denominator_
                        - ar.denominator_ * br.numerator_,
                        ar.denominator_ * br.denominator_ ) ; }

  friend fraction operator - ( const fraction & a, const T & b )
    { return fraction ( a.numerator_ - a.denominator_ * b,
                        a.denominator_ ) ; }

  friend fraction operator - ( const T & a, const fraction & b )
    { return fraction ( a * b.denominator_ - b.numerator_,
                        b.denominator_ ) ; }

  friend fraction operator * ( const __fraction_base < T > & a,
                               const __fraction_base < T > & b )
    { const fraction & ar = static_cast < const fraction & > ( a ),
                     & br = static_cast < const fraction & > ( b ) ;
      return fraction ( ar.numerator_ * br.numerator_,
                        ar.denominator_ * br.denominator_ ) ; }

  friend fraction operator * ( const fraction & a, const T & b )
    { return fraction ( a.numerator_ * b, a.denominator_ ) ; }

  friend fraction operator * ( const T & a, const fraction & b )
    { return fraction ( a * b.numerator_, b.denominator_ ) ; }

  friend fraction operator / ( const __fraction_base < T > & a,
                               const __fraction_base < T > & b )
    { const fraction & ar = static_cast < const fraction & > ( a ),
                     & br = static_cast < const fraction & > ( b ) ;
      return fraction ( ar.numerator_ * br.denominator_,
                        ar.denominator_ * br.numerator_ ) ; }

  friend fraction operator / ( const fraction & a, const T & b )
    { return fraction ( a.numerator_, a.denominator_ * b ) ; }

  friend fraction operator / ( const T & a, const fraction & b )
    { return fraction ( a * b.denominator_, b.numerator_ ) ; }

  fraction & operator += ( const __fraction_base < T > & b )
    { return * this = * this + static_cast < const fraction & > ( b ) ; }

  fraction & operator += ( const T & b )
    { numerator_ += denominator_ * b ;
      reduce ( ) ;
      return * this ; }

  fraction & operator -= ( const __fraction_base < T > & b )
    { return * this = * this - static_cast < const fraction & > ( b ) ; }

  fraction & operator -= ( const T & b )
    { numerator_ -= denominator_ * b ;
      reduce ( ) ;
      return * this ; }

  fraction & operator *= ( const __fraction_base < T > & b )
    { const fraction & br = static_cast < const fraction & > ( b ) ;
      numerator_ *= br.numerator_ ;
      denominator_ *= br.denominator_ ;
      reduce ( ) ;
      return * this ; }

  fraction & operator *= ( const T & b )
    { numerator_ *= b ;
      reduce ( ) ;
      return * this ; }

  fraction & operator /= ( const __fraction_base < T > & b )
    { const fraction & br = static_cast < const fraction & > ( b ) ;
      assert ( br.numerator_ != T ( 0 ) ) ;
      numerator_ *= br.denominator_ ;
      denominator_ *= br.numerator_ ;
      reduce ( ) ;
      return * this ; }

  fraction & operator /= ( const T & b )
    { assert ( b != T ( 0 ) ) ;
      denominator_ *= b ;
      reduce ( ) ;
      return * this ; }

  friend bool operator == ( const fraction & a, const fraction & b )
    { return     a.numerator_ == b.numerator_
             &&  a.denominator_ == b.denominator_ ; }

  friend bool operator < ( const fraction & a, const fraction & b )
    { return a.numerator_ * b.denominator_ < a.denominator_ * b.numerator_ ; }

  template < class CharT, class CharTraits >
  friend basic_ostream < CharT, CharTraits > &
    operator << ( basic_ostream < CharT, CharTraits > & o, const fraction & x )
    { return output_pair ( o, x.numerator_, x.denominator_ ) ; }

  template < class CharT, class CharTraits >
  friend basic_istream < CharT, CharTraits > &
    operator >> ( basic_istream < CharT, CharTraits > & i, fraction & x )
    { input_pair ( i, x.numerator_, x.denominator_ ) ;
      x.reduce ( ) ;
      return i ; }

} ;


//

template < class FloatingPoint, class T, class Allocator >
inline FloatingPoint
  to_floating_point ( const fraction < basic_exint < T, Allocator > > & x )

{
sint es =   ( x.numerator ( ).exponent ( ) - x.denominator ( ).exponent ( ) )
          - ( numeric_traits < FloatingPoint > :: mantissa_bit_size + 1 ) ;

basic_exint < T, Allocator >
  r (   es > 0
      ? x.numerator ( ) / ( x.denominator ( ) << es )
      : ( x.numerator ( ) << - es ) / x.denominator ( ) ) ;

if (   r.exponent ( )
     > ( numeric_traits < FloatingPoint > :: mantissa_bit_size + 1 ) )
  {
  r >>= 1 ;
  ++ es ;
  }

return ldexp ( convert_to < FloatingPoint > ( ( r + 1 ) >> 1 ), es + 1 ) ;
}



// *** IMPLICIT CONVERSION ***


//

template < class T >
class implicit_conversion_test < T, fraction < T > > :
  public implicit_conversion_test_ok

{
} ;


//

template < class S, class T >
class implicit_conversion_test < S, fraction < T > > :
  public implicit_conversion_test < S, T >

{
} ;



// *** TYPE CONVERSION ***


//

template < class T >
class fraction_direct_converter

{
public:

  static T operate ( const fraction < T > & x )
    { return x.numerator ( ) / x.denominator ( ) ; }

} ;


//

template < class T >
class type_converter < fraction < T >, T > :
  public fraction_direct_converter < T >

{
} ;


//

#define __DEFINE_TYPE_CONVERTER_1(TS,TD)                    \
                                                            \
template < >                                                \
class type_converter < fraction < TS >, TD >                \
                                                            \
{                                                           \
public:                                                     \
                                                            \
  static TD operate ( const fraction < TS > & x )           \
    { return TD ( x.numerator ( ) / x.denominator ( ) ) ; } \
                                                            \
} ;

#define __DEFINE_TYPE_CONVERTER(TD)                        \
FOR_BUILTIN_INTEGRAL_TYPES_1(__DEFINE_TYPE_CONVERTER_1,TD)

FOR_BUILTIN_INTEGRAL_TYPES(__DEFINE_TYPE_CONVERTER)

#undef __DEFINE_TYPE_CONVERTER

#undef __DEFINE_TYPE_CONVERTER_1


//

#define __DEFINE_TYPE_CONVERTER_1(TS,TD)                    \
                                                            \
template < >                                                \
class type_converter < fraction < TS >, TD >                \
                                                            \
{                                                           \
public:                                                     \
                                                            \
  static TD operate ( const fraction < TS > & x )           \
    { return   static_cast < TD > ( x.numerator ( ) )       \
             / static_cast < TD > ( x.denominator ( ) ) ; } \
                                                            \
} ;

#define __DEFINE_TYPE_CONVERTER(TD)                        \
FOR_BUILTIN_INTEGRAL_TYPES_1(__DEFINE_TYPE_CONVERTER_1,TD)

FOR_BUILTIN_FLOATING_POINT_TYPES(__DEFINE_TYPE_CONVERTER)

#undef __DEFINE_TYPE_CONVERTER

#undef __DEFINE_TYPE_CONVERTER_1


//

#define __DEFINE_TYPE_CONVERTER(TD)                                         \
template < class T, class Allocator >                                       \
class type_converter < fraction < basic_exint < T, Allocator > >, TD >      \
                                                                            \
{                                                                           \
public:                                                                     \
                                                                            \
  static TD operate ( const fraction < basic_exint < T, Allocator > > & x ) \
    { return to_floating_point < TD > ( x ) ; }                             \
                                                                            \
} ;


FOR_BUILTIN_FLOATING_POINT_TYPES(__DEFINE_TYPE_CONVERTER)

#undef __DEFINE_TYPE_CONVERTER


//

template < class T, class Allocator >
class type_converter < fraction < basic_exint < T, Allocator > >,
                       basic_exint < T, Allocator > > :
  public fraction_direct_converter < basic_exint < T, Allocator > >

{
} ;



#endif
