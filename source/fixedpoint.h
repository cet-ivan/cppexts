// Copyright Ivan Stanojevic 2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __FIXEDPOINT_H

#define __FIXEDPOINT_H



#include "istream.h"
#include "ostream.h"
#include "vector.h"
#include "algorithm.h"
#include "cassert.h"
#include "functional.h"
#include "cmath.h"
#include "utility.h"

#include "numbase.h"
#include "rnd.h"
#include "typeconv.h"



// *** FORWARD DECLARATIONS ***


//

template < class T, sint FractionalBits >
class signed_fixed_point ;

template < class T, sint FractionalBits >
class unsigned_fixed_point ;


//

template < class T, sint FractionalBits >
signed_fixed_point < T, FractionalBits >
  operator + ( const signed_fixed_point < T, FractionalBits > & a,
               const signed_fixed_point < T, FractionalBits > & b ) ;

template < class T, sint FractionalBits >
signed_fixed_point < T, FractionalBits >
  operator - ( const signed_fixed_point < T, FractionalBits > & a,
               const signed_fixed_point < T, FractionalBits > & b ) ;

template < class T, sint FractionalBits >
signed_fixed_point < T, FractionalBits >
  operator * ( const signed_fixed_point < T, FractionalBits > & a,
               const signed_fixed_point < T, FractionalBits > & b ) ;

template < class T, sint FractionalBits >
signed_fixed_point < T, FractionalBits >
  operator / ( const signed_fixed_point < T, FractionalBits > & a,
               const signed_fixed_point < T, FractionalBits > & b ) ;

template < class T, sint FractionalBits >
signed_fixed_point < T, FractionalBits >
  operator & ( const signed_fixed_point < T, FractionalBits > & a,
               const signed_fixed_point < T, FractionalBits > & b ) ;

template < class T, sint FractionalBits >
signed_fixed_point < T, FractionalBits >
  operator | ( const signed_fixed_point < T, FractionalBits > & a,
               const signed_fixed_point < T, FractionalBits > & b ) ;

template < class T, sint FractionalBits >
signed_fixed_point < T, FractionalBits >
  operator ^ ( const signed_fixed_point < T, FractionalBits > & a,
               const signed_fixed_point < T, FractionalBits > & b ) ;

template < class T, sint FractionalBits >
bool operator == ( const signed_fixed_point < T, FractionalBits > & a,
                   const signed_fixed_point < T, FractionalBits > & b ) ;

template < class T, sint FractionalBits >
bool operator < ( const signed_fixed_point < T, FractionalBits > & a,
                  const signed_fixed_point < T, FractionalBits > & b ) ;

template < class T, sint FractionalBits >
signed_fixed_point < T, FractionalBits >
  floor ( const signed_fixed_point < T, FractionalBits > & x ) ;

template < class T, sint FractionalBits >
signed_fixed_point < T, FractionalBits >
  ceil ( const signed_fixed_point < T, FractionalBits > & x ) ;

template < class T, sint FractionalBits >
signed_fixed_point < T, FractionalBits >
  trunc ( const signed_fixed_point < T, FractionalBits > & x ) ;

template < class T, sint FractionalBits >
signed_fixed_point < T, FractionalBits >
  round ( const signed_fixed_point < T, FractionalBits > & x ) ;

template < class T, sint FractionalBits >
bool is_negative ( const signed_fixed_point < T, FractionalBits > & x ) ;

template < class T, sint FractionalBits >
bool is_high_bit_set ( const signed_fixed_point < T, FractionalBits > & x ) ;

template < class T, sint FractionalBits >
sint hamming_weight ( const signed_fixed_point < T, FractionalBits > & x ) ;

template < class T, sint FractionalBits >
signed_fixed_point < T, FractionalBits >
  signed_shift_right ( const signed_fixed_point < T, FractionalBits > & x,
                       sint n ) ;

template < class T, sint FractionalBits >
signed_fixed_point < T, FractionalBits >
  unsigned_shift_right ( const signed_fixed_point < T, FractionalBits > & x,
                         sint n ) ;

template < class T, sint FractionalBits >
sint exponent ( const signed_fixed_point < T, FractionalBits > & x ) ;


//

template < class T, sint FractionalBits >
unsigned_fixed_point < T, FractionalBits >
  operator + ( const unsigned_fixed_point < T, FractionalBits > & a,
               const unsigned_fixed_point < T, FractionalBits > & b ) ;

template < class T, sint FractionalBits >
unsigned_fixed_point < T, FractionalBits >
  operator - ( const unsigned_fixed_point < T, FractionalBits > & a,
               const unsigned_fixed_point < T, FractionalBits > & b ) ;

template < class T, sint FractionalBits >
unsigned_fixed_point < T, FractionalBits >
  operator * ( const unsigned_fixed_point < T, FractionalBits > & a,
               const unsigned_fixed_point < T, FractionalBits > & b ) ;

template < class T, sint FractionalBits >
unsigned_fixed_point < T, FractionalBits >
  operator / ( const unsigned_fixed_point < T, FractionalBits > & a,
               const unsigned_fixed_point < T, FractionalBits > & b ) ;

template < class T, sint FractionalBits >
unsigned_fixed_point < T, FractionalBits >
  operator & ( const unsigned_fixed_point < T, FractionalBits > & a,
               const unsigned_fixed_point < T, FractionalBits > & b ) ;

template < class T, sint FractionalBits >
unsigned_fixed_point < T, FractionalBits >
  operator | ( const unsigned_fixed_point < T, FractionalBits > & a,
               const unsigned_fixed_point < T, FractionalBits > & b ) ;

template < class T, sint FractionalBits >
unsigned_fixed_point < T, FractionalBits >
  operator ^ ( const unsigned_fixed_point < T, FractionalBits > & a,
               const unsigned_fixed_point < T, FractionalBits > & b ) ;

template < class T, sint FractionalBits >
bool operator == ( const unsigned_fixed_point < T, FractionalBits > & a,
                   const unsigned_fixed_point < T, FractionalBits > & b ) ;

template < class T, sint FractionalBits >
bool operator < ( const unsigned_fixed_point < T, FractionalBits > & a,
                  const unsigned_fixed_point < T, FractionalBits > & b ) ;

template < class T, sint FractionalBits >
unsigned_fixed_point < T, FractionalBits >
  floor ( const unsigned_fixed_point < T, FractionalBits > & x ) ;

template < class T, sint FractionalBits >
unsigned_fixed_point < T, FractionalBits >
  ceil ( const unsigned_fixed_point < T, FractionalBits > & x ) ;

template < class T, sint FractionalBits >
unsigned_fixed_point < T, FractionalBits >
  trunc ( const unsigned_fixed_point < T, FractionalBits > & x ) ;

template < class T, sint FractionalBits >
unsigned_fixed_point < T, FractionalBits >
  round ( const unsigned_fixed_point < T, FractionalBits > & x ) ;

template < class T, sint FractionalBits >
bool is_negative ( const unsigned_fixed_point < T, FractionalBits > & x ) ;

template < class T, sint FractionalBits >
bool is_high_bit_set ( const unsigned_fixed_point < T, FractionalBits > & x ) ;

template < class T, sint FractionalBits >
sint hamming_weight ( const unsigned_fixed_point < T, FractionalBits > & x ) ;

template < class T, sint FractionalBits >
unsigned_fixed_point < T, FractionalBits >
  signed_shift_right ( const unsigned_fixed_point < T, FractionalBits > & x,
                       sint n ) ;

template < class T, sint FractionalBits >
unsigned_fixed_point < T, FractionalBits >
  unsigned_shift_right ( const unsigned_fixed_point < T, FractionalBits > & x,
                         sint n ) ;

template < class T, sint FractionalBits >
sint exponent ( const unsigned_fixed_point < T, FractionalBits > & x ) ;



// *** FIXED_POINT STREAMING ***


//

template < class CharT, class CharTraits, class FixedPoint >
basic_ostream < CharT, CharTraits > &
  output_fixed_point ( basic_ostream < CharT, CharTraits > & o, FixedPoint x )

{
typedef typename FixedPoint :: unsigned_value_type unsigned_value_type ;

bool negative = is_negative ( x ) ;

if ( negative )
  x = - x ;

vector < CharT > text ;

if ( FixedPoint :: fractional_bits < FixedPoint :: bit_size )
  {
  unsigned_value_type y ( x.data >> FixedPoint :: fractional_bits ) ;

  do
    {
    unsigned_value_type d ;
    divmod ( y, 10, y, d ) ;
    text.push_back ( convert_to < CharT > ( d ) + CharT ( '0' ) ) ;
    }
  while ( y != 0 ) ;

  reverse ( text.begin ( ), text.end ( ) ) ;
  }
else
  text.push_back ( CharT ( '0' ) ) ;

sint dot_position = text.size ( ) ;

{
unsigned_value_type y ( x.data << FixedPoint :: integer_bits ) ;

for ( sint i = 0 ; i < o.precision ( )  &&  y != 0 ; ++ i )
  {
  unsigned_value_type d ;
  unsigned_double_multiply ( y, unsigned_value_type ( 10 ), d, y ) ;
  text.push_back ( convert_to < CharT > ( d ) + CharT ( '0' ) ) ;
  }

if ( is_high_bit_set ( y ) )
  {
  auto iter = text.end ( ) ;

  for ( ; ; )
    {
    if ( iter == text.begin ( ) )
      {
      text.insert ( text.begin ( ), CharT ( '1' ) ) ;
      ++ dot_position ;
      break ;
      }

    -- iter ;

    if ( * iter != CharT ( '9' ) )
      {
      ++ * iter ;
      break ;
      }

    * iter = CharT ( '0' ) ;
    }
  }
}

text.erase ( find_if ( text.rbegin ( ), text.rend ( ) - dot_position,
                       [ ] ( const CharT & c ) { return c != CharT ( '0' ) ; } )
             .base ( ),
             text.end ( ) ) ;

if ( dot_position != text.size ( ) )
  text.insert ( text.begin ( ) + dot_position, CharT ( '.' ) ) ;

if ( negative )
  text.insert ( text.begin ( ), CharT ( '-' ) ) ;

return o.write ( text.data ( ), text.size ( ) ) ;
}


//

template < class CharT, class CharTraits, class FixedPoint >
basic_istream < CharT, CharTraits > &
  input_fixed_point ( basic_istream < CharT, CharTraits > & i, FixedPoint & x )

{
typedef typename FixedPoint :: unsigned_value_type unsigned_value_type ;

ios_base :: fmtflags start_flags = i.flags ( ) ;
i.setf ( ios_base :: skipws ) ;

unsigned_value_type integer_part ( 0 ),
                    fractional_part_high ( 0 ),
                    fractional_part_low ( 0 ) ;

bool negative ;
CharT c ;

i >> c ;
if ( ! i.good ( ) )
  goto error_end ;

i.unsetf ( ios_base :: skipws ) ;

if ( c == CharT ( '-' ) )
  {
  negative = true ;
  i >> c ;
  if ( ! i.good ( ) )
    goto error_end ;
  }
else
  negative = false ;

if ( c == CharT ( '.' ) )
  goto decimals ;

if ( c < CharT ( '0' )  ||  c > CharT ( '9' ) )
  {
  i.putback ( c ) ;
  i.setstate ( ios_base :: failbit ) ;
  goto error_end ;
  }

do
  {
  integer_part = integer_part * 10 + ( c - CharT ( '0' ) ) ;

  i >> c ;
  if ( i.eof ( ) )
    goto ok_end ;
  if ( ! i.good ( ) )
    goto error_end ;
  }
while ( c >= CharT ( '0' )  &&  c <= CharT ( '9' ) ) ;

if ( c != CharT ( '.' ) )
  {
  i.putback ( c ) ;
  goto ok_end ;
  }

decimals:

{
unsigned_value_type
  pc ( unsigned_value_type ( 1 ) << ( FixedPoint :: bit_size - 4 ) ),
  ph ( 0 ),
  pl ( 0 ) ;

unsigned_value_type
  b ( unsigned_value_type ( 10 ) << ( FixedPoint :: bit_size - 4 ) ) ;

bool ignore_digits = false ;

for ( ; ; )
  {
  unsigned_value_type qh ( unsigned_double_divide ( pc, ph, b ) ),
                      ql ( unsigned_double_divide ( ph - qh * b, pl, b ) ) ;

  if ( qh == 0  &&  ql == 0 )
    ignore_digits = true ;

  do
    {
    i >> c ;
    if ( i.eof ( ) )
      goto ok_end ;
    if ( ! i.good ( ) )
      goto error_end ;

    if ( c < CharT ( '0' )  ||  c > CharT ( '9' ) )
      {
      i.putback ( c ) ;
      goto ok_end ;
      }
    }
  while ( ignore_digits ) ;

  unsigned_value_type cv ( c - CharT ( '0' ) ) ;

  unsigned_value_type sh, sl ;
  unsigned_double_multiply ( cv, ql, sh, sl ) ;
  sh += cv * qh ;

  fractional_part_low += sl ;
  if ( fractional_part_low < sl )
    ++ fractional_part_high ;
  fractional_part_high += sh ;

  pc = qh >> 4 ;
  ph = ( qh << ( FixedPoint :: bit_size - 4 ) ) | ( ql >> 4 ) ;
  pl = ql << ( FixedPoint :: bit_size - 4 ) ;
  }
}

ok_end:

x.data =   FixedPoint :: fractional_bits < FixedPoint :: bit_size
         ?   ( integer_part << FixedPoint :: fractional_bits )
           | ( fractional_part_high >> FixedPoint :: integer_bits )
         : fractional_part_high ;

if ( negative )
  x.data = - x.data ;

error_end:

i.flags ( start_flags ) ;
return i ;
}



// *** FIXED_POINT_RND_STATIC_GENERATOR ***


template < class FixedPoint >
class fixed_point_rnd_static_generator

{
public:

  static FixedPoint operate ( )
    { return FixedPoint
               ( rnd < typename FixedPoint :: unsigned_value_type > ( ),
                 typename FixedPoint :: no_shift_tag ( ) ) ; }

} ;



// *** FIXED_POINT_BASE ***


//

template < class T, sint FractionalBits >
class fixed_point_base

{
public:

  typedef typename numeric_traits < T > :: signed_type signed_value_type ;
  typedef typename numeric_traits < T > :: unsigned_type unsigned_value_type ;

  static const sint bit_size = numeric_traits < T > :: bit_size ;
  static const sint fractional_bits = FractionalBits ;
  static const sint integer_bits = bit_size - fractional_bits ;

private:

  static_assert ( fractional_bits > 0  &&  fractional_bits <= bit_size,
                  "Illegal number of fractional bits." ) ;

protected:

  static const unsigned_value_type fractional_part_high_bit_mask ;
  static const unsigned_value_type fractional_part_low_bits_mask ;
  static const unsigned_value_type fractional_part_mask ;
  static const unsigned_value_type integer_part_low_bit_mask ;
  static const unsigned_value_type integer_part_mask ;

} ;


//

template < class T, sint FractionalBits >
const typename fixed_point_base < T, FractionalBits > :: unsigned_value_type
  fixed_point_base < T, FractionalBits > :: fractional_part_high_bit_mask =
    unsigned_value_type ( 1 ) << ( fractional_bits - 1 ) ;


//

template < class T, sint FractionalBits >
const typename fixed_point_base < T, FractionalBits > :: unsigned_value_type
  fixed_point_base < T, FractionalBits > :: fractional_part_low_bits_mask =
    fractional_part_high_bit_mask - unsigned_value_type ( 1 ) ;


//

template < class T, sint FractionalBits >
const typename fixed_point_base < T, FractionalBits > :: unsigned_value_type
  fixed_point_base < T, FractionalBits > :: fractional_part_mask =
    fractional_part_high_bit_mask + fractional_part_low_bits_mask ;


//

template < class T, sint FractionalBits >
const typename fixed_point_base < T, FractionalBits > :: unsigned_value_type
  fixed_point_base < T, FractionalBits > :: integer_part_low_bit_mask =
      fractional_bits < bit_size
    ? unsigned_value_type ( 1 ) << fractional_bits
    : 0 ;


//

template < class T, sint FractionalBits >
const typename fixed_point_base < T, FractionalBits > :: unsigned_value_type
  fixed_point_base < T, FractionalBits > :: integer_part_mask =
    ~ fractional_part_mask  ;



//

#ifdef NDEBUG

#define __DEFINE_FIXED_POINT_BASE(Type)                                    \
                                                                           \
template < sint FractionalBits >                                           \
class fixed_point_base < Type, FractionalBits >                            \
                                                                           \
{                                                                          \
public:                                                                    \
                                                                           \
  typedef numeric_traits < Type > :: signed_type signed_value_type ;       \
  typedef numeric_traits < Type > :: unsigned_type unsigned_value_type ;   \
                                                                           \
  static const sint bit_size = numeric_traits < Type > :: bit_size ;       \
  static const sint fractional_bits = FractionalBits ;                     \
  static const sint integer_bits = bit_size - fractional_bits ;            \
                                                                           \
private:                                                                   \
                                                                           \
  static_assert ( fractional_bits > 0  &&  fractional_bits <= bit_size,    \
                  "Illegal number of fractional bits." ) ;                 \
                                                                           \
protected:                                                                 \
                                                                           \
  static const unsigned_value_type                                         \
    fractional_part_high_bit_mask =                                        \
      unsigned_value_type ( 1 ) << ( fractional_bits - 1 ) ;               \
                                                                           \
  static const unsigned_value_type                                         \
    fractional_part_low_bits_mask =                                        \
      fractional_part_high_bit_mask - unsigned_value_type ( 1 ) ;          \
                                                                           \
  static const unsigned_value_type                                         \
    fractional_part_mask =                                                 \
      fractional_part_high_bit_mask + fractional_part_low_bits_mask ;      \
                                                                           \
  static const unsigned_value_type                                         \
    integer_part_low_bit_mask =                                            \
        fractional_bits < bit_size                                         \
      ? unsigned_value_type ( 1 ) << fractional_bits                       \
      : 0 ;                                                                \
                                                                           \
  static const unsigned_value_type                                         \
    integer_part_mask = ~ fractional_part_mask ;                           \
                                                                           \
} ;

FOR_BUILTIN_INTEGRAL_TYPES(__DEFINE_FIXED_POINT_BASE)

#undef __DEFINE_FIXED_POINT_BASE

#endif



// *** SIGNED_FIXED_POINT ***


template < class T, sint FractionalBits >
class signed_fixed_point : private fixed_point_base < T, FractionalBits >

{
public:

  friend class fixed_point_rnd_static_generator
                 < signed_fixed_point < T, FractionalBits > > ;

  friend class range_rnd_static_generator
                 < signed_fixed_point < T, FractionalBits > > ;

  friend class type_converter < unsigned_fixed_point < T, FractionalBits >,
                                signed_fixed_point < T, FractionalBits > > ;

  template < class CharT, class CharTraits, class FixedPoint >
  friend basic_ostream < CharT, CharTraits > &
    output_fixed_point ( basic_ostream < CharT, CharTraits > & o,
                         FixedPoint x ) ;

  template < class CharT, class CharTraits, class FixedPoint >
  friend basic_istream < CharT, CharTraits > &
    input_fixed_point ( basic_istream < CharT, CharTraits > & i,
                        FixedPoint & x ) ;

  using typename fixed_point_base < T, FractionalBits > :: signed_value_type ;
  using typename fixed_point_base < T, FractionalBits > :: unsigned_value_type ;
  using fixed_point_base < T, FractionalBits > :: bit_size ;
  using fixed_point_base < T, FractionalBits > :: fractional_bits ;
  using fixed_point_base < T, FractionalBits > :: integer_bits ;

private:

  using
    fixed_point_base < T, FractionalBits > :: fractional_part_high_bit_mask ;

  using
    fixed_point_base < T, FractionalBits > :: fractional_part_low_bits_mask ;

  using
    fixed_point_base < T, FractionalBits > :: fractional_part_mask ;

  using
    fixed_point_base < T, FractionalBits > :: integer_part_low_bit_mask ;

  using
    fixed_point_base < T, FractionalBits > :: integer_part_mask ;

  class no_shift_tag { } ;

  unsigned_value_type data ;

  signed_fixed_point ( const signed_value_type & i_data, no_shift_tag ) :
    data ( i_data )
    { }

  signed_fixed_point ( const unsigned_value_type & i_data, no_shift_tag ) :
    data ( i_data )
    { }

  static signed_fixed_point overflow_value ( bool negative )
    { return negative ? min ( ) : max ( ) ; }

  static signed_fixed_point multiply ( const signed_fixed_point & a,
                                       const signed_fixed_point & b ) ;

  static signed_fixed_point divide ( const signed_fixed_point & a,
                                     const signed_fixed_point & b ) ;

public:

  signed_fixed_point ( )
    { }

  signed_fixed_point ( const signed_value_type & x ) :
    data (   fractional_bits < bit_size
           ? x << fractional_bits
           : 0 )
    { }

  signed_fixed_point ( const unsigned_value_type & x ) :
    data (   fractional_bits < bit_size
           ? x << fractional_bits
           : 0 )
    { }

  template < class S >
  signed_fixed_point ( const S & x,
                       typename implicit_conversion_test
                                  < S, unsigned_value_type > :: result =
                         implicit_conversion_allowed ) :
    data (   fractional_bits < bit_size
           ? unsigned_value_type ( x ) << fractional_bits
           : 0 )
    { }

  static signed_fixed_point min ( )
    { return signed_fixed_point
               ( numeric_traits < signed_value_type > :: min ( ),
                 no_shift_tag ( ) ) ; }

  static signed_fixed_point max ( )
    { return signed_fixed_point
               ( numeric_traits < signed_value_type > :: max ( ),
                 no_shift_tag ( ) ) ; }

  static signed_fixed_point epsilon ( )
    { return signed_fixed_point
               ( unsigned_value_type ( 1 ),
                 no_shift_tag ( ) ) ; }

  signed_value_type signed_data ( ) const
    { return convert_to < signed_value_type > ( data ) ; }

  unsigned_value_type unsigned_data ( ) const
    { return data ; }

  bool is_high_bit_set ( ) const
    { return :: is_high_bit_set ( data ) ; }

  sint hamming_weight ( ) const
    { return :: hamming_weight ( data ) ; }

  signed_value_type truncated_to_integer ( ) const
    { return   fractional_bits < bit_size
             ?    convert_to < signed_value_type >
                    (   :: is_high_bit_set ( data )
                      ? data + fractional_part_mask
                      : data )
               >> fractional_bits
             : 0 ; }

  signed_value_type rounded_to_integer ( ) const
    { return   fractional_bits < bit_size
             ?    convert_to < signed_value_type >
                    ( data + (   :: is_high_bit_set ( data )
                               ? fractional_part_low_bits_mask
                               : fractional_part_high_bit_mask ) )
               >> fractional_bits
             : 0 ; }

  template < class FloatingPoint >
  FloatingPoint to_floating_point ( ) const
    { return ldexp ( convert_to < FloatingPoint > ( signed_data ( ) ),
                     - fractional_bits ) ; }

  static signed_fixed_point from_raw_data ( const signed_value_type & x )
    { return signed_fixed_point ( x, no_shift_tag ( ) ) ; }

  static signed_fixed_point from_raw_data ( const unsigned_value_type & x )
    { return signed_fixed_point ( x, no_shift_tag ( ) ) ; }

  template < class S >
  static signed_fixed_point from_raw_data ( const S & x )
    { return signed_fixed_point ( unsigned_value_type ( x ),
                                  no_shift_tag ( ) ) ; }

  template < class FloatingPoint >
  static signed_fixed_point from_floating_point ( const FloatingPoint & x )
    { return signed_fixed_point
               ( convert_to < signed_value_type >
                   ( ldexp (   ldexp ( x, fractional_bits + 1 )
                             + ( is_negative ( x ) ? -1 : 1 ),
                             -1 ) ),
                 no_shift_tag ( ) ) ; }

  const signed_fixed_point & operator + ( ) const
    { return * this ; }

  signed_fixed_point operator - ( ) const
    { return signed_fixed_point ( - data, no_shift_tag ( ) ) ; }

  friend signed_fixed_point operator + ( const signed_fixed_point & a,
                                         const signed_fixed_point & b )
    { return signed_fixed_point ( a.data + b.data, no_shift_tag ( ) ) ; }

  friend signed_fixed_point operator - ( const signed_fixed_point & a,
                                         const signed_fixed_point & b )
    { return signed_fixed_point ( a.data - b.data, no_shift_tag ( ) ) ; }

  friend signed_fixed_point operator * ( const signed_fixed_point & a,
                                         const signed_fixed_point & b )
    { return multiply ( a, b ) ; }

  friend signed_fixed_point operator / ( const signed_fixed_point & a,
                                         const signed_fixed_point & b )
    { return divide ( a, b ) ; }

  signed_fixed_point & operator += ( const signed_fixed_point & b )
    { data += b.data ;
      return * this ; }

  signed_fixed_point & operator -= ( const signed_fixed_point & b )
    { data -= b.data ;
      return * this ; }

  signed_fixed_point & operator *= ( const signed_fixed_point & b )
    { return * this = * this * b ; }

  signed_fixed_point & operator /= ( const signed_fixed_point & b )
    { return * this = * this / b ; }

  signed_fixed_point & operator ++ ( )
    { if ( fractional_bits < bit_size )
        data += integer_part_low_bit_mask ;
      return * this ; }

  signed_fixed_point operator ++ ( int )
    { signed_fixed_point t ( * this ) ;
      ++ * this ;
      return t ; }

  signed_fixed_point & operator -- ( )
    { if ( fractional_bits < bit_size )
        data -= integer_part_low_bit_mask ;
      return * this ; }

  signed_fixed_point operator -- ( int )
    { signed_fixed_point t ( * this ) ;
      -- * this ;
      return t ; }

  signed_fixed_point operator ~ ( ) const
    { return signed_fixed_point ( ~ data, no_shift_tag ( ) ) ; }

  friend signed_fixed_point operator & ( const signed_fixed_point & a,
                                         const signed_fixed_point & b )
    { return signed_fixed_point ( a.data & b.data, no_shift_tag ( ) ) ; }

  friend signed_fixed_point operator | ( const signed_fixed_point & a,
                                         const signed_fixed_point & b )
    { return signed_fixed_point ( a.data | b.data, no_shift_tag ( ) ) ; }

  friend signed_fixed_point operator ^ ( const signed_fixed_point & a,
                                         const signed_fixed_point & b )
    { return signed_fixed_point ( a.data ^ b.data, no_shift_tag ( ) ) ; }

  signed_fixed_point & operator &= ( const signed_fixed_point & b )
    { data &= b.data ;
      return * this ; }

  signed_fixed_point & operator |= ( const signed_fixed_point & b )
    { data |= b.data ;
      return * this ; }

  signed_fixed_point & operator ^= ( const signed_fixed_point & b )
    { data ^= b.data ;
      return * this ; }

  signed_fixed_point signed_shift_right ( sint n ) const
    { assert ( n >= 0  &&  n < bit_size ) ;
      return signed_fixed_point ( :: signed_shift_right ( data, n ),
                                  no_shift_tag ( ) ) ; }

  signed_fixed_point unsigned_shift_right ( sint n ) const
    { assert ( n >= 0  &&  n < bit_size ) ;
      return signed_fixed_point ( data >> n, no_shift_tag ( ) ) ; }

  signed_fixed_point operator << ( sint n ) const
    { assert ( n >= 0  &&  n < bit_size ) ;
      return signed_fixed_point ( data << n, no_shift_tag ( ) ) ; }

  signed_fixed_point operator >> ( sint n ) const
    { assert ( n >= 0  &&  n < bit_size ) ;
      return signed_shift_right ( n ) ; }

  signed_fixed_point & operator <<= ( sint n )
    { assert ( n >= 0  &&  n < bit_size ) ;
      data <<= n ;
      return * this ; }

  signed_fixed_point & operator >>= ( sint n )
    { assert ( n >= 0  &&  n < bit_size ) ;
      data = signed_shift_right ( data, n ) ;
      return * this ; }

  friend bool operator == ( const signed_fixed_point & a,
                            const signed_fixed_point & b )
    { return a.data == b.data ; }

  friend bool operator < ( const signed_fixed_point & a,
                           const signed_fixed_point & b )
    { return   convert_to < signed_value_type > ( a.data )
             < convert_to < signed_value_type > ( b.data ) ; }

  friend signed_fixed_point floor ( const signed_fixed_point & x )
    { return signed_fixed_point
               ( x.data & integer_part_mask,
                 no_shift_tag ( ) ) ; }

  friend signed_fixed_point ceil ( const signed_fixed_point & x )
    { return signed_fixed_point
               ( ( x.data + fractional_part_mask ) & integer_part_mask,
                 no_shift_tag ( ) ) ; }

  friend signed_fixed_point trunc ( const signed_fixed_point & x )
    { return signed_fixed_point
               (   (   :: is_high_bit_set ( x.data )
                     ? x.data + fractional_part_mask
                     : x.data )
                 & integer_part_mask,
                 no_shift_tag ( ) ) ; }

  friend signed_fixed_point round ( const signed_fixed_point & x )
    { return signed_fixed_point
               (   ( x.data + (   :: is_high_bit_set ( x.data )
                                ? fractional_part_low_bits_mask
                                : fractional_part_high_bit_mask ) )
                 & integer_part_mask,
                 no_shift_tag ( ) ) ; }

  template < class CharT, class CharTraits >
  friend basic_ostream < CharT, CharTraits > &
    operator << ( basic_ostream < CharT, CharTraits > & o,
                  const signed_fixed_point & x )
    { return output_fixed_point ( o, x ) ; }

  template < class CharT, class CharTraits >
  friend basic_istream < CharT, CharTraits > &
    operator >> ( basic_istream < CharT, CharTraits > & i,
                  signed_fixed_point & x )
    { return input_fixed_point ( i, x ) ; }

} ;


//

template < class T, sint FractionalBits >
inline signed_fixed_point < T, FractionalBits >
  signed_fixed_point < T, FractionalBits > ::
    multiply ( const signed_fixed_point < T, FractionalBits > & a,
               const signed_fixed_point < T, FractionalBits > & b )

{
unsigned_value_type av, bv ;

bool negative ;

if ( is_negative ( a ) )
  {
  av = - a.data ;
  negative = true ;
  }
else
  {
  av = a.data ;
  negative = false ;
  }

if ( is_negative ( b ) )
  {
  bv = - b.data ;
  negative = ! negative ;
  }
else
  bv = b.data ;

unsigned_value_type h, l ;
unsigned_double_multiply ( av, bv, h, l ) ;

l += fractional_part_high_bit_mask ;
if ( l < fractional_part_high_bit_mask )
  ++ h ;

unsigned_value_type
  r (   fractional_bits < bit_size
      ? ( h << ( bit_size - fractional_bits ) ) | ( l >> fractional_bits )
      : h ) ;

return signed_fixed_point ( negative ? - r : r, no_shift_tag ( ) ) ;
}


//

template < class T, sint FractionalBits >
inline signed_fixed_point < T, FractionalBits >
  signed_fixed_point < T, FractionalBits > ::
    divide ( const signed_fixed_point < T, FractionalBits > & a,
             const signed_fixed_point < T, FractionalBits > & b )

{
assert ( b.data != 0 ) ;

unsigned_value_type av, bv ;

bool negative ;

if ( is_negative ( a ) )
  {
  av = - a.data ;
  negative = true ;
  }
else
  {
  av = a.data ;
  negative = false ;
  }

if ( is_negative ( b ) )
  {
  bv = - b.data ;
  negative = ! negative ;
  }
else
  bv = b.data ;

sint bit_shift = bit_size - exponent ( bv ) ;

bv <<= bit_shift ;

bit_shift += fractional_bits + 1 ;

if ( bit_shift > bit_size  &&  av >> ( bit_size * 2 - bit_shift ) != 0 )
  return overflow_value ( negative ) ;

if ( bit_shift == bit_size * 2 )
  return signed_fixed_point ( unsigned_value_type ( 0 ), no_shift_tag ( ) ) ;

unsigned_value_type h, l ;

if ( bit_shift < bit_size )
  {
  h = av >> ( bit_size - bit_shift ) ;
  l = av << bit_shift ;
  }
else
  {
  h = av << ( bit_shift - bit_size ) ;
  l = 0 ;
  }

if ( h >= bv )
  return overflow_value ( negative ) ;

unsigned_value_type r ( ( unsigned_double_divide ( h, l, bv ) + 1 ) >> 1 ) ;

return signed_fixed_point ( negative ? - r : r, no_shift_tag ( ) ) ;
}



// *** SIGNED_FIXED_POINT NUMERIC_TRAITS ***


template < class T, sint FractionalBits >
class numeric_traits < signed_fixed_point < T, FractionalBits > >

{
public:

  static const bool is_floating_point = false ;

  static const bool is_signed = true ;

  typedef signed_fixed_point < T, FractionalBits > signed_type ;
  typedef unsigned_fixed_point < T, FractionalBits > unsigned_type ;

  static const sint
    bit_size = signed_fixed_point < T, FractionalBits > :: bit_size ;

  static const bool has_double_size_type = false ;
  typedef void double_size_type ;

  static signed_fixed_point < T, FractionalBits > min ( )
    { return signed_fixed_point < T, FractionalBits > :: min ( ) ; }

  static signed_fixed_point < T, FractionalBits > max ( )
    { return signed_fixed_point < T, FractionalBits > :: max ( ) ; }

  static signed_fixed_point < T, FractionalBits > epsilon ( )
    { return signed_fixed_point < T, FractionalBits > :: epsilon ( ) ; }

} ;



// *** SIGNED_FIXED_POINT RND_STATIC_GENERATOR ***


template < class T, sint FractionalBits >
class rnd_static_generator < signed_fixed_point < T, FractionalBits > > :
  public fixed_point_rnd_static_generator
           < signed_fixed_point < T, FractionalBits > >

{
} ;



// *** SIGNED_FIXED_POINT RANGE_RND_STATIC_GENERATOR ***


template < class T, sint FractionalBits >
class range_rnd_static_generator < signed_fixed_point < T, FractionalBits > >

{
public:

  static signed_fixed_point < T, FractionalBits >
           operate ( const signed_fixed_point < T, FractionalBits > & a,
                     const signed_fixed_point < T, FractionalBits > & b )
    { return signed_fixed_point < T, FractionalBits >
               ( range_rnd ( a.signed_data ( ), b.signed_data ( ) ),
                 typename signed_fixed_point < T, FractionalBits > ::
                   no_shift_tag ( ) ) ; }

} ;



// *** SIGNED_FIXED_POINT GLOBAL INTERFACES ***


//

template < class T, sint FractionalBits >
inline bool is_negative
              ( const signed_fixed_point < T, FractionalBits > & x )

{
return x.is_high_bit_set ( ) ;
}


//

template < class T, sint FractionalBits >
inline bool is_high_bit_set
              ( const signed_fixed_point < T, FractionalBits > & x )

{
return x.is_high_bit_set ( ) ;
}


//

template < class T, sint FractionalBits >
inline sint hamming_weight
              ( const signed_fixed_point < T, FractionalBits > & x )

{
return x.hamming_weight ( ) ;
}


//

template < class T, sint FractionalBits >
inline
  signed_fixed_point < T, FractionalBits >
    signed_shift_right ( const signed_fixed_point < T, FractionalBits > & x,
                         sint n )

{
return x.signed_shift_right ( n ) ;
}


//

template < class T, sint FractionalBits >
inline
  signed_fixed_point < T, FractionalBits >
    unsigned_shift_right ( const signed_fixed_point < T, FractionalBits > & x,
                           sint n )

{
return x.unsigned_shift_right ( n ) ;
}


//

template < class T, sint FractionalBits >
inline sint exponent ( const signed_fixed_point < T, FractionalBits > & x )

{
return exponent ( x.signed_data ( ) ) - FractionalBits ;
}



// *** SIGNED_FIXED_POINT IMPLICIT CONVERSION ***


//

template < class T, sint FractionalBits >
class implicit_conversion_test
        < typename signed_fixed_point < T, FractionalBits > ::
                     signed_value_type,
          signed_fixed_point < T, FractionalBits > > :
  public implicit_conversion_test_ok

{
} ;


//

template < class T, sint FractionalBits >
class implicit_conversion_test
        < typename signed_fixed_point < T, FractionalBits > ::
                     unsigned_value_type,
          signed_fixed_point < T, FractionalBits > > :
  public implicit_conversion_test_ok

{
} ;


//

template < class S, class T, sint FractionalBits >
class implicit_conversion_test < S,
                                 signed_fixed_point < T, FractionalBits > > :
  public implicit_conversion_test
           < S,
             typename signed_fixed_point < T, FractionalBits > ::
                        unsigned_value_type >

{
} ;



// *** UNSIGNED_FIXED_POINT ***


template < class T, sint FractionalBits >
class unsigned_fixed_point : private fixed_point_base < T, FractionalBits >

{
public:

  friend class fixed_point_rnd_static_generator
                 < unsigned_fixed_point < T, FractionalBits > > ;

  friend class range_rnd_static_generator
                 < unsigned_fixed_point < T, FractionalBits > > ;

  friend class type_converter < unsigned_fixed_point < T, FractionalBits >,
                                signed_fixed_point < T, FractionalBits > > ;

  template < class CharT, class CharTraits, class FixedPoint >
  friend basic_ostream < CharT, CharTraits > &
    output_fixed_point ( basic_ostream < CharT, CharTraits > & o,
                         FixedPoint x ) ;

  template < class CharT, class CharTraits, class FixedPoint >
  friend basic_istream < CharT, CharTraits > &
    input_fixed_point ( basic_istream < CharT, CharTraits > & i,
                        FixedPoint & x ) ;

  using typename fixed_point_base < T, FractionalBits > :: signed_value_type ;
  using typename fixed_point_base < T, FractionalBits > :: unsigned_value_type ;
  using fixed_point_base < T, FractionalBits > :: bit_size ;
  using fixed_point_base < T, FractionalBits > :: fractional_bits ;
  using fixed_point_base < T, FractionalBits > :: integer_bits ;

private:

  using
    fixed_point_base < T, FractionalBits > :: fractional_part_high_bit_mask ;

  using
    fixed_point_base < T, FractionalBits > :: fractional_part_low_bits_mask ;

  using
    fixed_point_base < T, FractionalBits > :: fractional_part_mask ;

  using
    fixed_point_base < T, FractionalBits > :: integer_part_low_bit_mask ;

  using
    fixed_point_base < T, FractionalBits > :: integer_part_mask ;

  class no_shift_tag { } ;

  unsigned_value_type data ;

  unsigned_fixed_point ( const signed_value_type & i_data, no_shift_tag ) :
    data ( i_data )
    { }

  unsigned_fixed_point ( const unsigned_value_type & i_data, no_shift_tag ) :
    data ( i_data )
    { }

  static unsigned_fixed_point overflow_value ( )
    { return max ( ) ; }

  static unsigned_fixed_point multiply ( const unsigned_fixed_point & a,
                                         const unsigned_fixed_point & b ) ;

  static unsigned_fixed_point divide ( const unsigned_fixed_point & a,
                                       const unsigned_fixed_point & b ) ;

public:

  unsigned_fixed_point ( )
    { }

  unsigned_fixed_point ( const signed_value_type & x ) :
    data (   fractional_bits < bit_size
           ? x << fractional_bits
           : 0 )
    { }

  unsigned_fixed_point ( const unsigned_value_type & x ) :
    data (   fractional_bits < bit_size
           ? x << fractional_bits
           : 0 )
    { }

  unsigned_fixed_point ( const signed_fixed_point < T, FractionalBits > & x ) :
    data ( x.unsigned_data ( ) )
    { }

  template < class S >
  unsigned_fixed_point ( const S & x,
                         typename implicit_conversion_test
                                    < S, unsigned_value_type > :: result =
                           implicit_conversion_allowed ) :
    data (   fractional_bits < bit_size
           ? unsigned_value_type ( x ) << fractional_bits
           : 0 )
    { }

  static unsigned_fixed_point min ( )
    { return unsigned_fixed_point
               ( numeric_traits < unsigned_value_type > :: min ( ),
                 no_shift_tag ( ) ) ; }

  static unsigned_fixed_point max ( )
    { return unsigned_fixed_point
               ( numeric_traits < unsigned_value_type > :: max ( ),
                 no_shift_tag ( ) ) ; }

  static unsigned_fixed_point epsilon ( )
    { return unsigned_fixed_point
               ( unsigned_value_type ( 1 ),
                 no_shift_tag ( ) ) ; }

  signed_value_type signed_data ( ) const
    { return convert_to < signed_value_type > ( data ) ; }

  unsigned_value_type unsigned_data ( ) const
    { return data ; }

  bool is_high_bit_set ( ) const
    { return :: is_high_bit_set ( data ) ; }

  sint hamming_weight ( ) const
    { return :: hamming_weight ( data ) ; }

  unsigned_value_type truncated_to_integer ( ) const
    { return   fractional_bits < bit_size
             ? data >> fractional_bits
             : 0 ; }

  unsigned_value_type rounded_to_integer ( ) const
    { return   fractional_bits < bit_size
             ? ( data + fractional_part_high_bit_mask ) >> fractional_bits
             : 0 ; }

  template < class FloatingPoint >
  FloatingPoint to_floating_point ( ) const
    { return ldexp ( convert_to < FloatingPoint > ( data ),
                     - fractional_bits ) ; }

  static unsigned_fixed_point from_raw_data ( const signed_value_type & x )
    { return unsigned_fixed_point ( x, no_shift_tag ( ) ) ; }

  static unsigned_fixed_point from_raw_data ( const unsigned_value_type & x )
    { return unsigned_fixed_point ( x, no_shift_tag ( ) ) ; }

  template < class S >
  static unsigned_fixed_point from_raw_data ( const S & x )
    { return unsigned_fixed_point ( unsigned_value_type ( x ),
                                    no_shift_tag ( ) ) ; }

  template < class FloatingPoint >
  static unsigned_fixed_point from_floating_point ( const FloatingPoint & x )
    { return unsigned_fixed_point
               ( convert_to < unsigned_value_type >
                   ( ldexp ( ldexp ( x, fractional_bits + 1 ) + 1, -1 ) ),
                 no_shift_tag ( ) ) ; }

  const unsigned_fixed_point & operator + ( ) const
    { return * this ; }

  unsigned_fixed_point operator - ( ) const
    { return unsigned_fixed_point ( - data, no_shift_tag ( ) ) ; }

  friend unsigned_fixed_point operator + ( const unsigned_fixed_point & a,
                                           const unsigned_fixed_point & b )
    { return unsigned_fixed_point ( a.data + b.data, no_shift_tag ( ) ) ; }

  friend unsigned_fixed_point operator - ( const unsigned_fixed_point & a,
                                           const unsigned_fixed_point & b )
    { return unsigned_fixed_point ( a.data - b.data, no_shift_tag ( ) ) ; }

  friend unsigned_fixed_point operator * ( const unsigned_fixed_point & a,
                                           const unsigned_fixed_point & b )
    { return multiply ( a, b ) ; }

  friend unsigned_fixed_point operator / ( const unsigned_fixed_point & a,
                                           const unsigned_fixed_point & b )
    { return divide ( a, b ) ; }

  unsigned_fixed_point & operator += ( const unsigned_fixed_point & b )
    { data += b.data ;
      return * this ; }

  unsigned_fixed_point & operator -= ( const unsigned_fixed_point & b )
    { data -= b.data ;
      return * this ; }

  unsigned_fixed_point & operator *= ( const unsigned_fixed_point & b )
    { return * this = * this * b ; }

  unsigned_fixed_point & operator /= ( const unsigned_fixed_point & b )
    { return * this = * this / b ; }

  unsigned_fixed_point & operator ++ ( )
    { if ( fractional_bits < bit_size )
        data += integer_part_low_bit_mask ;
      return * this ; }

  unsigned_fixed_point operator ++ ( int )
    { unsigned_fixed_point t ( * this ) ;
      ++ * this ;
      return t ; }

  unsigned_fixed_point & operator -- ( )
    { if ( fractional_bits < bit_size )
        data -= integer_part_low_bit_mask ;
      return * this ; }

  unsigned_fixed_point operator -- ( int )
    { unsigned_fixed_point t ( * this ) ;
      -- * this ;
      return t ; }

  unsigned_fixed_point operator ~ ( ) const
    { return unsigned_fixed_point ( ~ data, no_shift_tag ( ) ) ; }

  friend unsigned_fixed_point operator & ( const unsigned_fixed_point & a,
                                           const unsigned_fixed_point & b )
    { return unsigned_fixed_point ( a.data & b.data, no_shift_tag ( ) ) ; }

  friend unsigned_fixed_point operator | ( const unsigned_fixed_point & a,
                                           const unsigned_fixed_point & b )
    { return unsigned_fixed_point ( a.data | b.data, no_shift_tag ( ) ) ; }

  friend unsigned_fixed_point operator ^ ( const unsigned_fixed_point & a,
                                           const unsigned_fixed_point & b )
    { return unsigned_fixed_point ( a.data ^ b.data, no_shift_tag ( ) ) ; }

  unsigned_fixed_point & operator &= ( const unsigned_fixed_point & b )
    { data &= b.data ;
      return * this ; }

  unsigned_fixed_point & operator |= ( const unsigned_fixed_point & b )
    { data |= b.data ;
      return * this ; }

  unsigned_fixed_point & operator ^= ( const unsigned_fixed_point & b )
    { data ^= b.data ;
      return * this ; }

  unsigned_fixed_point signed_shift_right ( sint n ) const
    { assert ( n >= 0  &&  n < bit_size ) ;
      return unsigned_fixed_point ( :: signed_shift_right ( data, n ),
                                    no_shift_tag ( ) ) ; }

  unsigned_fixed_point unsigned_shift_right ( sint n ) const
    { assert ( n >= 0  &&  n < bit_size ) ;
      return unsigned_fixed_point ( data >> n, no_shift_tag ( ) ) ; }

  unsigned_fixed_point operator << ( sint n ) const
    { assert ( n >= 0  &&  n < bit_size ) ;
      return unsigned_fixed_point ( data << n, no_shift_tag ( ) ) ; }

  unsigned_fixed_point operator >> ( sint n ) const
    { assert ( n >= 0  &&  n < bit_size ) ;
      return unsigned_shift_right ( n ) ; }

  unsigned_fixed_point & operator <<= ( sint n )
    { assert ( n >= 0  &&  n < bit_size ) ;
      data <<= n ;
      return * this ; }

  unsigned_fixed_point & operator >>= ( sint n )
    { assert ( n >= 0  &&  n < bit_size ) ;
      data >>= n ;
      return * this ; }

  friend bool operator == ( const unsigned_fixed_point & a,
                            const unsigned_fixed_point & b )
    { return a.data == b.data ; }

  friend bool operator < ( const unsigned_fixed_point & a,
                           const unsigned_fixed_point & b )
    { return a.data < b.data ; }

  friend unsigned_fixed_point floor ( const unsigned_fixed_point & x )
    { return unsigned_fixed_point
               ( x.data & integer_part_mask,
                 no_shift_tag ( ) ) ; }

  friend unsigned_fixed_point ceil ( const unsigned_fixed_point & x )
    { return unsigned_fixed_point
               ( ( x.data + fractional_part_mask ) & integer_part_mask,
                 no_shift_tag ( ) ) ; }

  friend unsigned_fixed_point trunc ( const unsigned_fixed_point & x )
    { return floor ( x ) ; }

  friend unsigned_fixed_point round ( const unsigned_fixed_point & x )
    { return unsigned_fixed_point
               (   ( x.data + fractional_part_high_bit_mask )
                 & integer_part_mask,
                 no_shift_tag ( ) ) ; }

  template < class CharT, class CharTraits >
  friend basic_ostream < CharT, CharTraits > &
    operator << ( basic_ostream < CharT, CharTraits > & o,
                  const unsigned_fixed_point & x )
    { return output_fixed_point ( o, x ) ; }

  template < class CharT, class CharTraits >
  friend basic_istream < CharT, CharTraits > &
    operator >> ( basic_istream < CharT, CharTraits > & i,
                  unsigned_fixed_point & x )
    { return input_fixed_point ( i, x ) ; }

} ;


//

template < class T, sint FractionalBits >
inline unsigned_fixed_point < T, FractionalBits >
  unsigned_fixed_point < T, FractionalBits > ::
    multiply ( const unsigned_fixed_point < T, FractionalBits > & a,
               const unsigned_fixed_point < T, FractionalBits > & b )

{
unsigned_value_type h, l ;
unsigned_double_multiply ( a.data, b.data, h, l ) ;

l += fractional_part_high_bit_mask ;
if ( l < fractional_part_high_bit_mask )
  ++ h ;

return unsigned_fixed_point
         (   fractional_bits < bit_size
           ? ( h << ( bit_size - fractional_bits ) ) | ( l >> fractional_bits )
           : h,
           no_shift_tag ( ) ) ;
}


//

template < class T, sint FractionalBits >
inline unsigned_fixed_point < T, FractionalBits >
  unsigned_fixed_point < T, FractionalBits > ::
    divide ( const unsigned_fixed_point < T, FractionalBits > & a,
             const unsigned_fixed_point < T, FractionalBits > & b )

{
assert ( b.data != 0 ) ;

unsigned_value_type bv ( b.data ) ;

sint bit_shift = bit_size - exponent ( bv ) ;

bv <<= bit_shift ;

bit_shift += fractional_bits + 1 ;

unsigned_value_type h, l, rh ;

if ( bit_shift > bit_size )
  {
  unsigned_value_type c ( a.data >> ( bit_size * 2 - bit_shift ) ) ;

  if ( c > 1 )
    return overflow_value ( ) ;

  h = a.data << ( bit_shift - bit_size ) ;
  l = 0 ;

  if ( c == 1 )
    {
    unsigned_value_type hn ( h - bv ) ;

    if ( hn <= h )
      return overflow_value ( ) ;

    h = hn ;
    rh = 1 ;
    }
  else
    rh = 0 ;
  }
else
  {
  if ( bit_shift < bit_size )
    {
    h = a.data >> ( bit_size - bit_shift ) ;
    l = a.data << bit_shift ;
    }
  else
    {
    h = a.data ;
    l = 0 ;
    }

  rh = 0 ;
  }

if ( h >= bv )
  {
  if ( rh > 0 )
    return overflow_value ( ) ;

  h -= bv ;
  rh = 1 ;
  }

unsigned_value_type r ( unsigned_double_divide ( h, l, bv ) + 1 ) ;

if ( r == 0 )
  {
  if ( rh > 0 )
    return overflow_value ( ) ;

  rh = 1 ;
  }

return unsigned_fixed_point ( ( rh << ( bit_size - 1 ) ) | ( r >> 1 ),
                              no_shift_tag ( ) ) ;
}



// *** UNSIGNED_FIXED_POINT NUMERIC_TRAITS ***


template < class T, sint FractionalBits >
class numeric_traits < unsigned_fixed_point < T, FractionalBits > >

{
public:

  static const bool is_floating_point = false ;

  static const bool is_signed = false ;

  typedef signed_fixed_point < T, FractionalBits > signed_type ;
  typedef unsigned_fixed_point < T, FractionalBits > unsigned_type ;

  static const sint
    bit_size = unsigned_fixed_point < T, FractionalBits > :: bit_size ;

  static const bool has_double_size_type = false ;
  typedef void double_size_type ;

  static unsigned_fixed_point < T, FractionalBits > min ( )
    { return unsigned_fixed_point < T, FractionalBits > :: min ( ) ; }

  static unsigned_fixed_point < T, FractionalBits > max ( )
    { return unsigned_fixed_point < T, FractionalBits > :: max ( ) ; }

  static unsigned_fixed_point < T, FractionalBits > epsilon ( )
    { return unsigned_fixed_point < T, FractionalBits > :: epsilon ( ) ; }

} ;



// *** UNSIGNED_FIXED_POINT RND_STATIC_GENERATOR ***


template < class T, sint FractionalBits >
class rnd_static_generator < unsigned_fixed_point < T, FractionalBits > > :
  public fixed_point_rnd_static_generator
           < unsigned_fixed_point < T, FractionalBits > >

{
} ;



// *** UNSIGNED_FIXED_POINT RANGE_RND_STATIC_GENERATOR ***


template < class T, sint FractionalBits >
class range_rnd_static_generator < unsigned_fixed_point < T, FractionalBits > >

{
public:

  static unsigned_fixed_point < T, FractionalBits >
           operate ( const unsigned_fixed_point < T, FractionalBits > & a,
                     const unsigned_fixed_point < T, FractionalBits > & b )
    { return unsigned_fixed_point < T, FractionalBits >
               ( range_rnd ( a.unsigned_data ( ), b.unsigned_data ( ) ),
                 typename unsigned_fixed_point < T, FractionalBits > ::
                   no_shift_tag ( ) ) ; }

} ;



// *** UNSIGNED_FIXED_POINT GLOBAL INTERFACES ***


//

template < class T, sint FractionalBits >
inline bool is_negative
              ( const unsigned_fixed_point < T, FractionalBits > & x )

{
return false ;
}


//

template < class T, sint FractionalBits >
inline bool is_high_bit_set
              ( const unsigned_fixed_point < T, FractionalBits > & x )

{
return x.is_high_bit_set ( ) ;
}


//

template < class T, sint FractionalBits >
inline sint hamming_weight
              ( const unsigned_fixed_point < T, FractionalBits > & x )

{
return x.hamming_weight ( ) ;
}


//

template < class T, sint FractionalBits >
inline
  unsigned_fixed_point < T, FractionalBits >
    signed_shift_right ( const unsigned_fixed_point < T, FractionalBits > & x,
                         sint n )

{
return x.signed_shift_right ( n ) ;
}


//

template < class T, sint FractionalBits >
inline
  unsigned_fixed_point < T, FractionalBits >
    unsigned_shift_right ( const unsigned_fixed_point < T, FractionalBits > & x,
                           sint n )

{
return x.unsigned_shift_right ( n ) ;
}


//

template < class T, sint FractionalBits >
inline sint exponent ( const unsigned_fixed_point < T, FractionalBits > & x )

{
return exponent ( x.unsigned_data ( ) ) - FractionalBits ;
}



// *** UNSIGNED_FIXED_POINT IMPLICIT CONVERSION ***


//

template < class T, sint FractionalBits >
class implicit_conversion_test
        < typename unsigned_fixed_point < T, FractionalBits > ::
                     signed_value_type,
          unsigned_fixed_point < T, FractionalBits > > :
  public implicit_conversion_test_ok

{
} ;


//

template < class T, sint FractionalBits >
class implicit_conversion_test
        < typename unsigned_fixed_point < T, FractionalBits > ::
                     unsigned_value_type,
          unsigned_fixed_point < T, FractionalBits > > :
  public implicit_conversion_test_ok

{
} ;


//

template < class T, sint FractionalBits >
class implicit_conversion_test < signed_fixed_point < T, FractionalBits >,
                                 unsigned_fixed_point < T, FractionalBits > > :
  public implicit_conversion_test_ok

{
} ;


//

template < class S, class T, sint FractionalBits >
class implicit_conversion_test < S,
                                 unsigned_fixed_point < T, FractionalBits > > :
  public implicit_conversion_test
           < S,
             typename unsigned_fixed_point < T, FractionalBits > ::
               unsigned_value_type >

{
} ;



// *** TYPE CONVERSION ***


//

template < class T, sint FractionalBits >
class type_converter < unsigned_fixed_point < T, FractionalBits >,
                       signed_fixed_point < T, FractionalBits > >

{
public:

  static signed_fixed_point < T, FractionalBits >
    operate ( const unsigned_fixed_point < T, FractionalBits > & x )
    { return signed_fixed_point < T, FractionalBits >
               ( x.data,
                 typename signed_fixed_point < T, FractionalBits > ::
                            no_shift_tag ( ) ) ; }

} ;


//

template < class T, sint FractionalBits >
class type_converter
        < signed_fixed_point < T, FractionalBits >,
          typename signed_fixed_point < T, FractionalBits > ::
                     signed_value_type >

{
public:

  static typename signed_fixed_point < T, FractionalBits > ::
                    signed_value_type
    operate ( const signed_fixed_point < T, FractionalBits > & x )
    { return x.truncated_to_integer ( ) ; }

} ;


//

template < class T, sint FractionalBits >
class type_converter
        < unsigned_fixed_point < T, FractionalBits >,
          typename unsigned_fixed_point < T, FractionalBits > ::
                     unsigned_value_type >

{
public:

  static typename unsigned_fixed_point < T, FractionalBits > ::
                    unsigned_value_type
    operate ( const unsigned_fixed_point < T, FractionalBits > & x )
    { return x.truncated_to_integer ( ) ; }

} ;


//

template
  < class FixedPoint, class Destination, bool DestinationIsFloatingPoint >
class from_fixed_point_type_converter ;


//

template < class FixedPoint, class Destination >
class from_fixed_point_type_converter < FixedPoint, Destination, false >

{
public:

  static Destination operate ( const FixedPoint & x )
    { return convert_to < Destination > ( x.truncated_to_integer ( ) ) ; }

} ;


//

template < class FixedPoint, class Destination >
class from_fixed_point_type_converter < FixedPoint, Destination, true >

{
public:

  static Destination operate ( const FixedPoint & x )
    { return x.template to_floating_point < Destination > ( ) ; }

} ;


//

template < class T, sint FractionalBits, class U >
class type_converter < signed_fixed_point < T, FractionalBits >, U > :
  public from_fixed_point_type_converter
           < signed_fixed_point < T, FractionalBits >,
             U,
             numeric_traits < U > :: is_floating_point >

{
} ;


//

template < class T, sint FractionalBits, class U >
class type_converter < unsigned_fixed_point < T, FractionalBits >, U > :
  public from_fixed_point_type_converter
           < unsigned_fixed_point < T, FractionalBits >,
             U,
             numeric_traits < U > :: is_floating_point >

{
} ;


//

template < class Source, class FixedPoint, bool SourceIsFloatingPoint >
class to_fixed_point_type_converter ;


//

template < class Source, class FixedPoint >
class to_fixed_point_type_converter < Source, FixedPoint, false >

{
public:

  static FixedPoint operate ( const Source & x )
    { return FixedPoint ( x ) ; }

} ;


//

template < class Source, class FixedPoint >
class to_fixed_point_type_converter < Source, FixedPoint, true >

{
public:

  static FixedPoint operate ( const Source & x )
    { return FixedPoint :: from_floating_point ( x ) ; }

} ;


//

template < class S, class T, sint FractionalBits >
class type_converter < S, signed_fixed_point < T, FractionalBits > > :
  public to_fixed_point_type_converter
           < S,
             signed_fixed_point < T, FractionalBits >,
             numeric_traits < S > :: is_floating_point >

{
} ;


//

template < class S, class T, sint FractionalBits >
class type_converter < S, unsigned_fixed_point < T, FractionalBits > > :
  public to_fixed_point_type_converter
           < S,
             unsigned_fixed_point < T, FractionalBits >,
             numeric_traits < S > :: is_floating_point >

{
} ;



#endif
