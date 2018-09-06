// Copyright Ivan Stanojevic 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __DOUBLEINT_H

#define __DOUBLEINT_H



#include "cassert.h"
#include "ios.h"
#include "istream.h"
#include "ostream.h"
#include "vector.h"
#include "utility.h"

#include "numbase.h"
#include "rnd.h"
#include "typeconv.h"



// *** FORWARD DECLARATIONS ***


//

template < class T >
class signed_double_int ;

template < class T >
class unsigned_double_int ;


//

template < class T >
signed_double_int < T > operator + ( const signed_double_int < T > & a,
                                     const signed_double_int < T > & b ) ;

template < class T >
signed_double_int < T > operator - ( const signed_double_int < T > & a,
                                     const signed_double_int < T > & b ) ;

template < class T >
signed_double_int < T > operator * ( const signed_double_int < T > & a,
                                     const signed_double_int < T > & b ) ;

template < class T >
void divmod ( signed_double_int < T > a, signed_double_int < T > b,
              signed_double_int < T > & q, signed_double_int < T > & r ) ;

template < class T >
signed_double_int < T > operator / ( const signed_double_int < T > & a,
                                     const signed_double_int < T > & b ) ;

template < class T >
signed_double_int < T > operator % ( const signed_double_int < T > & a,
                                     const signed_double_int < T > & b ) ;

template < class T >
signed_double_int < T > operator & ( const signed_double_int < T > & a,
                                     const signed_double_int < T > & b ) ;

template < class T >
signed_double_int < T > operator | ( const signed_double_int < T > & a,
                                     const signed_double_int < T > & b ) ;

template < class T >
signed_double_int < T > operator ^ ( const signed_double_int < T > & a,
                                     const signed_double_int < T > & b ) ;

template < class T >
bool operator == ( const signed_double_int < T > & a,
                   const signed_double_int < T > & b ) ;

template < class T >
bool operator < ( const signed_double_int < T > & a,
                  const signed_double_int < T > & b ) ;

template < class T >
bool is_negative ( const signed_double_int < T > & x ) ;

template < class T >
bool is_high_bit_set ( const signed_double_int < T > & x ) ;

template < class T >
sint hamming_weight ( const signed_double_int < T > & x ) ;

template < class T >
signed_double_int < T >
  signed_shift_right ( const signed_double_int < T > & x, sint n ) ;

template < class T >
signed_double_int < T >
  unsigned_shift_right ( const signed_double_int < T > & x, sint n ) ;

template < class T >
sint exponent ( const signed_double_int < T > & x ) ;

template < class T >
void normalize_gcd ( signed_double_int < T > & gcd ) ;

template < class T >
void normalize_gcd_ext ( signed_double_int < T > & c,
                         signed_double_int < T > & d,
                         signed_double_int < T > & gcd ) ;

template < class T >
void normalize_fraction ( signed_double_int < T > & a,
                          signed_double_int < T > & b ) ;


//

template < class T >
unsigned_double_int < T > operator + ( const unsigned_double_int < T > & a,
                                       const unsigned_double_int < T > & b ) ;

template < class T >
unsigned_double_int < T > operator - ( const unsigned_double_int < T > & a,
                                       const unsigned_double_int < T > & b ) ;

template < class T >
unsigned_double_int < T > operator * ( const unsigned_double_int < T > & a,
                                       const unsigned_double_int < T > & b ) ;

template < class T >
void divmod ( unsigned_double_int < T > a, unsigned_double_int < T > b,
              unsigned_double_int < T > & q, unsigned_double_int < T > & r ) ;

template < class T >
unsigned_double_int < T > operator / ( const unsigned_double_int < T > & a,
                                       const unsigned_double_int < T > & b ) ;

template < class T >
unsigned_double_int < T > operator % ( const unsigned_double_int < T > & a,
                                       const unsigned_double_int < T > & b ) ;

template < class T >
unsigned_double_int < T > operator & ( const unsigned_double_int < T > & a,
                                       const unsigned_double_int < T > & b ) ;

template < class T >
unsigned_double_int < T > operator | ( const unsigned_double_int < T > & a,
                                       const unsigned_double_int < T > & b ) ;

template < class T >
unsigned_double_int < T > operator ^ ( const unsigned_double_int < T > & a,
                                       const unsigned_double_int < T > & b ) ;

template < class T >
bool operator == ( const unsigned_double_int < T > & a,
                   const unsigned_double_int < T > & b ) ;

template < class T >
bool operator < ( const unsigned_double_int < T > & a,
                  const unsigned_double_int < T > & b ) ;

template < class T >
bool is_negative ( const unsigned_double_int < T > & x ) ;

template < class T >
bool is_high_bit_set ( const unsigned_double_int < T > & x ) ;

template < class T >
sint hamming_weight ( const unsigned_double_int < T > & x ) ;

template < class T >
unsigned_double_int < T >
  signed_shift_right ( const unsigned_double_int < T > & x, sint n ) ;

template < class T >
unsigned_double_int < T >
  unsigned_shift_right ( const unsigned_double_int < T > & x, sint n ) ;

template < class T >
sint exponent ( const unsigned_double_int < T > & x ) ;



// *** DOUBLE_INT SHIFTS ***


//

template < class DoubleInt >
inline DoubleInt double_int_shift_left ( DoubleInt x, sint n )

{
assert ( n >= 0  &&  n < 2 * DoubleInt :: digit_bit_size ) ;

if ( n != 0 )
  {
  if ( n < DoubleInt :: digit_bit_size )
    {
    x.high =   ( x.high << n )
             | ( x.low >> ( DoubleInt :: digit_bit_size - n ) ) ;
    x.low <<= n ;
    }
  else
    {
    x.high = x.low << ( n - DoubleInt :: digit_bit_size ) ;
    x.low = 0 ;
    }
  }

return x ;
}


//

template < class DoubleInt >
inline DoubleInt double_int_signed_shift_right ( DoubleInt x, sint n )

{
assert ( n >= 0  &&  n < 2 * DoubleInt :: digit_bit_size ) ;

if ( n != 0 )
  {
  typename DoubleInt :: unsigned_digit_type
    prefix ( x.is_high_bit_set ( ) ? -1 : 0 ) ;

  if ( n < DoubleInt :: digit_bit_size )
    {
    x.low  =   ( x.high << ( DoubleInt :: digit_bit_size - n ) )
             | ( x.low >> n ) ;
    x.high =   ( prefix << ( DoubleInt :: digit_bit_size - n ) )
             | ( x.high >> n ) ;
    }
  else
    {
    x.low  =   n == DoubleInt :: digit_bit_size
             ? x.high
             :   ( prefix << ( DoubleInt :: digit_bit_size * 2 - n ) )
               | ( x.high >> ( n - DoubleInt :: digit_bit_size ) ) ;
    x.high = prefix ;
    }
  }

return x ;
}


//

template < class DoubleInt >
inline DoubleInt double_int_unsigned_shift_right ( DoubleInt x, sint n )

{
assert ( n >= 0  &&  n < 2 * DoubleInt :: digit_bit_size ) ;

if ( n != 0 )
  {
  if ( n < DoubleInt :: digit_bit_size )
    {
    x.low =   ( x.high << ( DoubleInt :: digit_bit_size - n ) )
            | ( x.low >> n ) ;
    x.high >>= n ;
    }
  else
    {
    x.low = x.high >> ( n - DoubleInt :: digit_bit_size ) ;
    x.high = 0 ;
    }
  }

return x ;
}



// *** DOUBLE_INT_POSITIVE_DIVMOD ***


// pre: a >= 0
//      b > 0
//
// post: q = a / b
//       r = a % b

template < class DoubleInt >
inline void double_int_positive_divmod ( DoubleInt a, DoubleInt b,
                                         DoubleInt & q, DoubleInt & r )

{
assert ( b != 0 ) ;

typedef typename DoubleInt :: unsigned_digit_type unsigned_digit_type ;

sint bit_shift ;

if ( b.high == 0 )
  {
  sint bit_shift_comp = exponent ( b.low ) ;
  bit_shift = DoubleInt :: digit_bit_size - bit_shift_comp ;

  unsigned_digit_type ac ;

  if ( bit_shift == 0 )
    ac = 0 ;
  else
    {
    b.low <<= bit_shift ;

    ac = a.high >> bit_shift_comp ;
    a.high = ( a.high << bit_shift ) | ( a.low >> bit_shift_comp ) ;
    a.low <<= bit_shift ;
    }

  q.high = unsigned_double_divide ( ac, a.high, b.low ) ;

  a.high -= q.high * b.low ;

  q.low = unsigned_double_divide ( a.high, a.low, b.low ) ;

  a.high = 0 ;
  a.low -= q.low * b.low ;
  }
else
  {
  sint bit_shift_comp = exponent ( b.high ) ;
  bit_shift = DoubleInt :: digit_bit_size - bit_shift_comp ;

  unsigned_digit_type ac ;

  if ( bit_shift == 0 )
    ac = 0 ;
  else
    {
    b.high = ( b.high << bit_shift ) | ( b.low >> bit_shift_comp ) ;
    b.low <<= bit_shift ;

    ac = a.high >> bit_shift_comp ;
    a.high = ( a.high << bit_shift ) | ( a.low >> bit_shift_comp ) ;
    a.low <<= bit_shift ;
    }

  q.high = 0 ;
  q.low = unsigned_double_divide ( ac, a.high, b.high ) ;

  unsigned_digit_type mc, mh, ml ;

  unsigned_double_multiply ( q.low, b.low, mh, ml ) ;

  {
  unsigned_digit_type th ;
  unsigned_double_multiply ( q.low, b.high, mc, th ) ;

  mh += th ;
  if ( mh < th )
    ++ mc ;
  }

  while (     ac < mc
          ||  (     ac == mc
                &&  (     a.high < mh
                      ||  (     a.high == mh
                            &&  a.low < ml ) ) ) )
    {

    {
    unsigned_digit_type mln ( ml - b.low ) ;
    if ( mln > ml )
      {
      -- mh ;
      if ( mh == unsigned_digit_type ( -1 ) )
        -- mc ;
      }
    ml = mln ;
    }

    {
    unsigned_digit_type mhn ( mh - b.high ) ;
    if ( mhn > mh )
      -- mc ;
    mh = mhn ;
    }

    -- q.low ;
    }

  {
  unsigned_digit_type aln ( a.low - ml ) ;
  if ( aln > a.low )
    -- a.high ;
  a.low = aln ;
  }

  a.high -= mh ;
  }

r = double_int_unsigned_shift_right ( a, bit_shift ) ;
}



// *** DOUBLE_INT STREAMING ***


//

template < class CharT, class CharTraits, class DoubleInt >
basic_ostream < CharT, CharTraits > &
  output_double_int ( basic_ostream < CharT, CharTraits > & o, DoubleInt x )

{
bool negative = is_negative ( x ) ;

if ( negative )
  x = - x ;

vector < CharT > text ;

do
  {
  DoubleInt d ;
  double_int_positive_divmod ( x, DoubleInt ( 10 ), x, d ) ;
  text.push_back ( convert_to < CharT > ( d ) + CharT ( '0' ) ) ;
  }
while ( x != 0 ) ;

if ( negative )
  text.push_back ( CharT ( '-' ) ) ;

reverse ( text.begin ( ), text.end ( ) ) ;

return o.write ( text.data ( ), text.size ( ) ) ;
}


//

template < class CharT, class CharTraits, class DoubleInt >
basic_istream < CharT, CharTraits > &
  input_double_int ( basic_istream < CharT, CharTraits > & i, DoubleInt & x )

{
ios_base :: fmtflags start_flags = i.flags ( ) ;
i.setf ( ios_base :: skipws ) ;

DoubleInt y ( 0 ) ;

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

if ( c < CharT ( '0' )  ||  c > CharT ( '9' ) )
  {
  i.putback ( c ) ;
  i.setstate ( ios_base :: failbit ) ;
  goto error_end ;
  }

do
  {
  y = y * 10 + ( c - CharT ( '0' ) ) ;

  i >> c ;
  if ( i.eof ( ) )
    goto ok_end ;
  if ( ! i.good ( ) )
    goto error_end ;
  }
while ( c >= CharT ( '0' )  &&  c <= CharT ( '9' ) ) ;
i.putback ( c ) ;

ok_end:

if ( negative )
  x = - y ;
else
  x = y ;

error_end:

i.flags ( start_flags ) ;
return i ;
}



// *** DOUBLE_INT_UNSIGNED_DOUBLE_MULTIPLIER ***


template < class DoubleInt >
class double_int_unsigned_double_multiplier

{
public:

  static void operate ( DoubleInt a, DoubleInt b,
                        DoubleInt & h, DoubleInt & l ) ;

} ;


//

template < class DoubleInt >
inline void double_int_unsigned_double_multiplier < DoubleInt > ::
              operate ( DoubleInt a, DoubleInt b,
                        DoubleInt & h, DoubleInt & l )

{
typedef typename DoubleInt :: unsigned_digit_type unsigned_digit_type ;

unsigned_digit_type hh, hl, lh, ll ;

unsigned_double_multiply ( a.high, b.high, hh, hl ) ;
unsigned_double_multiply ( a.low, b.low, lh, ll ) ;

unsigned_digit_type mc ( 0 ), mh, ml ;

{
unsigned_digit_type as ( a.high + a.low ),
                    bs ( b.high + b.low ) ;

bool ac ( as < a.high ),
     bc ( bs < b.high ) ;

unsigned_double_multiply ( as, bs, mh, ml ) ;

if ( ac )
  {
  mh += bs ;
  if ( mh < bs )
    ++ mc ;
  }

if ( bc )
  {
  mh += as ;
  if ( mh < as )
    ++ mc ;
  }

if ( ac  &&  bc )
  ++ mc ;
}

{
unsigned_digit_type mln ( ml - hl ) ;
if ( mln > ml )
  {
  -- mh ;
  if ( mh == unsigned_digit_type ( -1 ) )
    -- mc ;
  }
ml = mln ;
}

{
unsigned_digit_type mhn ( mh - hh ) ;
if ( mhn > mh )
  -- mc ;
mh = mhn ;
}

{
unsigned_digit_type mln ( ml - ll ) ;
if ( mln > ml )
  {
  -- mh ;
  if ( mh == unsigned_digit_type ( -1 ) )
    -- mc ;
  }
ml = mln ;
}

{
unsigned_digit_type mhn ( mh - lh ) ;
if ( mhn > mh )
  -- mc ;
mh = mhn ;
}

{
lh += ml ;
if ( lh < ml )
  {
  ++ hl ;
  if ( hl == 0 )
    ++ hh ;
  }
}

{
hl += mh ;
if ( hl < mh )
  ++ hh ;
}

hh += mc ;

h.high = hh ;
h.low = hl ;
l.high = lh ;
l.low = ll ;
}



// *** DOUBLE_INT_UNSIGNED_DOUBLE_DIVIDER ***


template < class DoubleInt >
class double_int_unsigned_double_divider

{
public:

  static DoubleInt operate ( DoubleInt h, DoubleInt l, DoubleInt b ) ;

} ;


//

template < class DoubleInt >
inline DoubleInt double_int_unsigned_double_divider < DoubleInt > ::
                   operate ( DoubleInt h, DoubleInt l, DoubleInt b )

{
typedef typename DoubleInt :: unsigned_digit_type unsigned_digit_type ;

DoubleInt result ;

result.high =   h.high == b.high
              ? unsigned_digit_type ( -1 )
              : unsigned_double_divide ( h.high, h.low, b.high ) ;

{
unsigned_digit_type mc, mh, ml ;
unsigned_double_multiply ( result.high, b.low, mh, ml ) ;

{
unsigned_digit_type th ;
unsigned_double_multiply ( result.high, b.high, mc, th ) ;

mh += th ;
if ( mh < th )
  ++ mc ;
}

while (     h.high < mc
        ||  (     h.high == mc
              &&  (     h.low < mh
                    ||  (     h.low == mh
                          &&  l.high < ml ) ) ) )
  {

  {
  unsigned_digit_type mln ( ml - b.low ) ;
  if ( mln > ml )
    {
    -- mh ;
    if ( mh == unsigned_digit_type ( -1 ) )
      -- mc ;
    }
  ml = mln ;
  }

  {
  unsigned_digit_type mhn ( mh - b.high ) ;
  if ( mhn > mh )
    -- mc ;
  mh = mhn ;
  }

  -- result.high ;
  }

{
unsigned_digit_type lhn ( l.high - ml ) ;
if ( lhn > l.high )
  -- h.low ;
l.high = lhn ;
}

h.low -= mh ;
}

result.low =   h.low == b.high
             ? unsigned_digit_type ( -1 )
             : unsigned_double_divide ( h.low, l.high, b.high ) ;

{
unsigned_digit_type mc, mh, ml ;
unsigned_double_multiply ( result.low, b.low, mh, ml ) ;

{
unsigned_digit_type th ;
unsigned_double_multiply ( result.low, b.high, mc, th ) ;

mh += th ;
if ( mh < th )
  ++ mc ;
}

while (     h.low < mc
        ||  (     h.low == mc
              &&  (     l.high < mh
                    ||  (     l.high == mh
                          &&  l.low < ml ) ) ) )
  {

  {
  unsigned_digit_type mln ( ml - b.low ) ;
  if ( mln > ml )
    {
    -- mh ;
    if ( mh == unsigned_digit_type ( -1 ) )
      -- mc ;
    }
  ml = mln ;
  }

  {
  unsigned_digit_type mhn ( mh - b.high ) ;
  if ( mhn > mh )
    -- mc ;
  mh = mhn ;
  }

  -- result.low ;
  }
}

return result ;
}



// *** DOUBLE_INT_RND_STATIC_GENERATOR ***


template < class DoubleInt >
class double_int_rnd_static_generator

{
private:

  typedef typename DoubleInt :: unsigned_digit_type unsigned_digit_type ;

public:

  static DoubleInt operate ( )
    { return DoubleInt ( rnd < unsigned_digit_type > ( ),
                         rnd < unsigned_digit_type > ( ) ) ; }

} ;



// *** SIGNED_DOUBLE_INT ***


template < class T >
class signed_double_int

{
public:

  typedef typename numeric_traits < T > :: signed_type signed_digit_type ;
  typedef typename numeric_traits < T > :: unsigned_type unsigned_digit_type ;

  static const sint
    digit_bit_size = numeric_traits < unsigned_digit_type > :: bit_size ;

private:

  sint positive_exponent ( ) const
    { sint e = :: exponent ( high ) ;
      return e != 0 ? e + digit_bit_size : :: exponent ( low ) ; }

  template < class FloatingPoint >
  FloatingPoint positive_to_floating_point ( ) const
    { FloatingPoint result ( ldexp ( convert_to < FloatingPoint > ( high ),
                                     digit_bit_size ) ) ;
      if (   :: exponent ( result )
           < (   numeric_traits < FloatingPoint > :: mantissa_bit_size
               + digit_bit_size ) )
        result += convert_to < FloatingPoint > ( low ) ;
      return result ; }

  template < class FloatingPoint >
  static signed_double_int
    from_positive_floating_point ( const FloatingPoint & x )
    { FloatingPoint xs ( trunc ( ldexp ( x, - digit_bit_size ) ) ) ;
      return signed_double_int
               ( convert_to < unsigned_digit_type >
                   ( xs - ldexp ( trunc ( ldexp ( xs, - digit_bit_size ) ),
                                  digit_bit_size ) ),
                 convert_to < unsigned_digit_type >
                   ( x - ldexp ( xs, digit_bit_size ) ) ) ; }

public:

  unsigned_digit_type high, low ;

  signed_double_int ( )
    { }

  signed_double_int ( const unsigned_digit_type & i_high,
                      const unsigned_digit_type & i_low ) :
    high ( i_high ),
    low ( i_low )
    { }

  signed_double_int ( const signed_digit_type & x ) :
    high ( x >= 0 ? 0 : -1 ),
    low ( x )
    { }

  signed_double_int ( const unsigned_digit_type & x ) :
    high ( 0 ),
    low ( x )
    { }

  template < class S >
  signed_double_int ( const S & x,
                      typename implicit_conversion_test
                                 < S, unsigned_digit_type > :: result =
                        implicit_conversion_allowed ) :
    high (   numeric_traits < S > :: is_signed
           ? ( is_negative ( x ) ? -1 : 0 )
           : 0 ),
    low ( x )
    { }

  static signed_double_int min ( )
    { return signed_double_int
               ( numeric_traits < signed_digit_type > :: min ( ), 0 ) ; }

  static signed_double_int max ( )
    { return signed_double_int
               ( numeric_traits < signed_digit_type > :: max ( ), -1 ) ; }

  bool is_high_bit_set ( ) const
    { return :: is_high_bit_set ( high ) ; }

  sint exponent ( ) const
    { return   is_high_bit_set ( )
             ? ( - * this ).positive_exponent ( )
             : positive_exponent ( ) ; }

  template < class FloatingPoint >
  FloatingPoint to_floating_point ( ) const
    { return   is_high_bit_set ( )
             ? -  ( - * this )
                 .template positive_to_floating_point < FloatingPoint > ( )
             : positive_to_floating_point < FloatingPoint > ( ) ; }

  template < class FloatingPoint >
  static signed_double_int from_floating_point ( const FloatingPoint & x )
    { return   is_negative ( x )
             ? - from_positive_floating_point ( - x )
             : from_positive_floating_point ( x ) ; }

  const signed_double_int & operator + ( ) const
    { return * this ; }

  signed_double_int operator - ( ) const
    { return signed_double_int ( low == 0 ? - high : - high - 1, - low ) ; }

  friend signed_double_int operator + ( const signed_double_int & a,
                                        const signed_double_int & b )
    { signed_double_int result ( a.high + b.high, a.low + b.low ) ;
      if ( result.low < a.low )
        ++ result.high ;
      return result ; }

  friend signed_double_int operator - ( const signed_double_int & a,
                                        const signed_double_int & b )
    { signed_double_int result ( a.high - b.high, a.low - b.low ) ;
      if ( result.low > a.low )
        -- result.high ;
      return result ; }

  friend signed_double_int operator * ( const signed_double_int & a,
                                        const signed_double_int & b )
    { signed_double_int result ;
      unsigned_double_multiply ( a.low, b.low, result.high, result.low ) ;
      result.high += a.high * b.low + a.low * b.high ;
      return result ; }

  friend void divmod ( signed_double_int a, signed_double_int b,
                       signed_double_int & q, signed_double_int & r )
    { if ( is_negative ( a ) )
        if ( is_negative ( b ) )
          {
          double_int_positive_divmod ( - a, - b, q, r ) ;
          r = - r ;
          }
        else
          {
          double_int_positive_divmod ( - a, b, q, r ) ;
          q = - q ;
          r = - r ;
          }
      else
        if ( is_negative ( b ) )
          {
          double_int_positive_divmod ( a, - b, q, r ) ;
          q = - q ;
          }
        else
          double_int_positive_divmod ( a, b, q, r ) ; }

  friend signed_double_int operator / ( const signed_double_int & a,
                                        const signed_double_int & b )
    { signed_double_int q, r ;
      divmod ( a, b, q, r ) ;
      return q ; }

  friend signed_double_int operator % ( const signed_double_int & a,
                                        const signed_double_int & b )
    { signed_double_int q, r ;
      divmod ( a, b, q, r ) ;
      return r ; }

  signed_double_int & operator += ( const signed_double_int & b )
    { low += b.low ;
      if ( low < b.low )
        ++ high ;
      high += b.high ;
      return * this ; }

  signed_double_int & operator -= ( const signed_double_int & b )
    { unsigned_digit_type ln ( low - b.low ) ;
      if ( ln > low )
        -- high ;
      low = ln ;
      high -= b.high ;
      return * this ; }

  signed_double_int & operator *= ( const signed_double_int & b )
    { return * this = * this * b ; }

  signed_double_int & operator /= ( const signed_double_int & b )
    { return * this = * this / b ; }

  signed_double_int & operator %= ( const signed_double_int & b )
    { return * this = * this % b ; }

  signed_double_int & operator ++ ( )
    { ++ low ;
      if ( low == 0 )
        ++ high ;
      return * this ; }

  signed_double_int operator ++ ( int )
    { signed_double_int t ( * this ) ;
      ++ * this ;
      return t ; }

  signed_double_int & operator -- ( )
    { -- low ;
      if ( low == unsigned_digit_type ( -1 ) )
        -- high ;
      return * this ; }

  signed_double_int operator -- ( int )
    { signed_double_int t ( * this ) ;
      -- * this ;
      return t ; }

  signed_double_int operator ~ ( ) const
    { return signed_double_int ( ~ high, ~ low ) ; }

  friend signed_double_int operator & ( const signed_double_int & a,
                                        const signed_double_int & b )
    { return signed_double_int ( a.high & b.high, a.low & b.low ) ; }

  friend signed_double_int operator | ( const signed_double_int & a,
                                        const signed_double_int & b )
    { return signed_double_int ( a.high | b.high, a.low | b.low ) ; }

  friend signed_double_int operator ^ ( const signed_double_int & a,
                                        const signed_double_int & b )
    { return signed_double_int ( a.high ^ b.high, a.low ^ b.low ) ; }

  signed_double_int & operator &= ( const signed_double_int & b )
    { high &= b.high ;
      low &= b.low ;
      return * this ; }

  signed_double_int & operator |= ( const signed_double_int & b )
    { high |= b.high ;
      low |= b.low ;
      return * this ; }

  signed_double_int & operator ^= ( const signed_double_int & b )
    { high ^= b.high ;
      low ^= b.low ;
      return * this ; }

  signed_double_int operator << ( sint n ) const
    { return double_int_shift_left ( * this, n ) ; }

  signed_double_int operator >> ( sint n ) const
    { return double_int_signed_shift_right ( * this, n ) ; }

  signed_double_int & operator <<= ( sint n )
    { return * this = * this << n ; }

  signed_double_int & operator >>= ( sint n )
    { return * this = * this >> n ; }

  friend bool operator == ( const signed_double_int & a,
                            const signed_double_int & b )
    { return a.high == b.high  &&  a.low == b.low ; }

  friend bool operator < ( const signed_double_int & a,
                           const signed_double_int & b )
    { return       convert_to < signed_digit_type > ( a.high )
                 < convert_to < signed_digit_type > ( b.high )
             ||  ( a.high == b.high  &&  a.low < b.low ) ; }

  template < class CharT, class CharTraits >
  friend basic_ostream < CharT, CharTraits > &
    operator << ( basic_ostream < CharT, CharTraits > & o,
                  const signed_double_int & x )
    { return output_double_int ( o, x ) ; }

  template < class CharT, class CharTraits >
  friend basic_istream < CharT, CharTraits > &
    operator >> ( basic_istream < CharT, CharTraits > & i,
                  signed_double_int & x )
    { return input_double_int ( i, x ) ; }

} ;



// *** SIGNED_DOUBLE_INT NUMERIC_TRAITS ***


template < class T >
class numeric_traits < signed_double_int < T > >

{
public:

  static const bool is_floating_point = false ;

  static const bool is_signed = true ;

  typedef signed_double_int < T > signed_type ;
  typedef unsigned_double_int < T > unsigned_type ;

  static const sint bit_size = numeric_traits < T > :: bit_size * 2 ;

  static const bool has_double_size_type = false ;
  typedef void double_size_type ;

  static signed_double_int < T > min ( )
    { return signed_double_int < T > :: min ( ) ; }

  static signed_double_int < T > max ( )
    { return signed_double_int < T > :: max ( ) ; }

} ;



// *** SIGNED_DOUBLE_INT UNSIGNED_DOUBLE_MULTIPLIER ***


template < class T >
class unsigned_double_multiplier < signed_double_int < T >, false > :
  public double_int_unsigned_double_multiplier < signed_double_int < T > >

{
} ;



// *** SIGNED_DOUBLE_INT UNSIGNED_DOUBLE_DIVIDER ***


template < class T >
class unsigned_double_divider < signed_double_int < T >, false > :
  public double_int_unsigned_double_divider < signed_double_int < T > >

{
} ;



// *** SIGNED_DOUBLE_INT RND_STATIC_GENERATOR ***


template < class T >
class rnd_static_generator < signed_double_int < T > > :
  public double_int_rnd_static_generator < signed_double_int < T > >

{
} ;



// *** SIGNED_DOUBLE_INT RANGE_RND_STATIC_GENERATOR ***


template < class T >
class range_rnd_static_generator < signed_double_int < T > > :
  public signed_int_range_rnd_static_generator < signed_double_int < T > >

{
} ;



// *** SIGNED_DOUBLE_INT GLOBAL INTERFACES ***


//

template < class T >
inline bool is_negative ( const signed_double_int < T > & x )

{
return x.is_high_bit_set ( ) ;
}


//

template < class T >
inline bool is_high_bit_set ( const signed_double_int < T > & x )

{
return x.is_high_bit_set ( ) ;
}


//

template < class T >
inline sint hamming_weight ( const signed_double_int < T > & x )

{
return hamming_weight ( x.high ) + hamming_weight ( x.low ) ;
}


//

template < class T >
inline signed_double_int < T >
         signed_shift_right ( const signed_double_int < T > & x, sint n )

{
return double_int_signed_shift_right ( x, n ) ;
}


//

template < class T >
inline signed_double_int < T >
         unsigned_shift_right ( const signed_double_int < T > & x, sint n )

{
return double_int_unsigned_shift_right ( x, n ) ;
}


//

template < class T >
inline sint exponent ( const signed_double_int < T > & x )

{
return x.exponent ( ) ;
}


//

template < class T >
inline void normalize_gcd ( signed_double_int < T > & gcd )

{
if ( is_negative ( gcd ) )
  gcd = - gcd ;
}


//

template < class T >
inline void normalize_gcd_ext ( signed_double_int < T > & c,
                                signed_double_int < T > & d,
                                signed_double_int < T > & gcd )

{
if ( is_negative ( gcd ) )
  {
  c = - c ;
  d = - d ;
  gcd = - gcd ;
  }
}


//

template < class T >
inline void normalize_fraction ( signed_double_int < T > & a,
                                 signed_double_int < T > & b )

{
if ( is_negative ( b ) )
  {
  a = - a ;
  b = - b ;
  }
}



// *** SIGNED_DOUBLE_INT IMPLICIT CONVERSION ***


//

template < class T >
class implicit_conversion_test
        < typename signed_double_int < T > :: signed_digit_type,
          signed_double_int < T > > :
  public implicit_conversion_test_ok

{
} ;


//

template < class T >
class implicit_conversion_test
        < typename signed_double_int < T > :: unsigned_digit_type,
          signed_double_int < T > > :
  public implicit_conversion_test_ok

{
} ;


//

template < class S, class T >
class implicit_conversion_test < S, signed_double_int < T > > :
  public implicit_conversion_test
           < S, typename signed_double_int < T > :: unsigned_digit_type >

{
} ;



// *** UNSIGNED_DOUBLE_INT ***


template < class T >
class unsigned_double_int

{
public:

  typedef typename numeric_traits < T > :: signed_type signed_digit_type ;
  typedef typename numeric_traits < T > :: unsigned_type unsigned_digit_type ;

  static const sint
    digit_bit_size = numeric_traits < unsigned_digit_type > :: bit_size ;

private:

  template < class FloatingPoint >
  static unsigned_double_int
    from_positive_floating_point ( const FloatingPoint & x )
    { FloatingPoint xs ( trunc ( ldexp ( x, - digit_bit_size ) ) ) ;
      return unsigned_double_int
               ( convert_to < unsigned_digit_type >
                   ( xs - ldexp ( trunc ( ldexp ( xs, - digit_bit_size ) ),
                                  digit_bit_size ) ),
                 convert_to < unsigned_digit_type >
                   ( x - ldexp ( xs, digit_bit_size ) ) ) ; }

public:

  unsigned_digit_type high, low ;

  unsigned_double_int ( )
    { }

  unsigned_double_int ( const unsigned_digit_type & i_high,
                        const unsigned_digit_type & i_low ) :
    high ( i_high ),
    low ( i_low )
    { }

  unsigned_double_int ( const signed_digit_type & x ) :
    high ( x >= 0 ? 0 : -1 ),
    low ( x )
    { }

  unsigned_double_int ( const unsigned_digit_type & x ) :
    high ( 0 ),
    low ( x )
    { }

  unsigned_double_int ( const signed_double_int < T > & x ) :
    high ( x.high ),
    low ( x.low )
    { }

  template < class S >
  unsigned_double_int ( const S & x,
                        typename implicit_conversion_test
                                   < S, unsigned_digit_type > :: result =
                          implicit_conversion_allowed ) :
    high (   numeric_traits < S > :: is_signed
           ? ( is_negative ( x ) ? -1 : 0 )
           : 0 ),
    low ( x )
    { }

  static unsigned_double_int min ( )
    { return 0 ; }

  static unsigned_double_int max ( )
    { return unsigned_double_int ( -1, -1 ) ; }

  bool is_high_bit_set ( ) const
    { return :: is_high_bit_set ( high ) ; }

  sint exponent ( ) const
    { sint e = :: exponent ( high ) ;
      return e != 0 ? e + digit_bit_size : :: exponent ( low ) ; }

  template < class FloatingPoint >
  FloatingPoint to_floating_point ( ) const
    { FloatingPoint result ( ldexp ( convert_to < FloatingPoint > ( high ),
                                     digit_bit_size ) ) ;
      if (   :: exponent ( result )
           < (   numeric_traits < FloatingPoint > :: mantissa_bit_size
               + digit_bit_size ) )
        result += convert_to < FloatingPoint > ( low ) ;
      return result ; }

  template < class FloatingPoint >
  static unsigned_double_int from_floating_point ( const FloatingPoint & x )
    { return   is_negative ( x )
             ? - from_positive_floating_point ( - x )
             : from_positive_floating_point ( x ) ; }

  const unsigned_double_int & operator + ( ) const
    { return * this ; }

  unsigned_double_int operator - ( ) const
    { return unsigned_double_int ( low == 0 ? - high : - high - 1, - low ) ; }

  friend unsigned_double_int operator + ( const unsigned_double_int & a,
                                          const unsigned_double_int & b )
    { unsigned_double_int result ( a.high + b.high, a.low + b.low ) ;
      if ( result.low < a.low )
        ++ result.high ;
      return result ; }

  friend unsigned_double_int operator - ( const unsigned_double_int & a,
                                          const unsigned_double_int & b )
    { unsigned_double_int result ( a.high - b.high, a.low - b.low ) ;
      if ( result.low > a.low )
        -- result.high ;
      return result ; }

  friend unsigned_double_int operator * ( const unsigned_double_int & a,
                                          const unsigned_double_int & b )
    { unsigned_double_int result ;
      unsigned_double_multiply ( a.low, b.low, result.high, result.low ) ;
      result.high += a.high * b.low + a.low * b.high ;
      return result ; }

  friend void divmod ( unsigned_double_int a, unsigned_double_int b,
                       unsigned_double_int & q, unsigned_double_int & r )
    { double_int_positive_divmod ( a, b, q, r ) ; }

  friend unsigned_double_int operator / ( const unsigned_double_int & a,
                                          const unsigned_double_int & b )
    { unsigned_double_int q, r ;
      divmod ( a, b, q, r ) ;
      return q ; }

  friend unsigned_double_int operator % ( const unsigned_double_int & a,
                                          const unsigned_double_int & b )
    { unsigned_double_int q, r ;
      divmod ( a, b, q, r ) ;
      return r ; }

  unsigned_double_int & operator += ( const unsigned_double_int & b )
    { low += b.low ;
      if ( low < b.low )
        ++ high ;
      high += b.high ;
      return * this ; }

  unsigned_double_int & operator -= ( const unsigned_double_int & b )
    { unsigned_digit_type ln ( low - b.low ) ;
      if ( ln > low )
        -- high ;
      low = ln ;
      high -= b.high ;
      return * this ; }

  unsigned_double_int & operator *= ( const unsigned_double_int & b )
    { return * this = * this * b ; }

  unsigned_double_int & operator /= ( const unsigned_double_int & b )
    { return * this = * this / b ; }

  unsigned_double_int & operator %= ( const unsigned_double_int & b )
    { return * this = * this % b ; }

  unsigned_double_int & operator ++ ( )
    { ++ low ;
      if ( low == 0 )
        ++ high ;
      return * this ; }

  unsigned_double_int operator ++ ( int )
    { unsigned_double_int t ( * this ) ;
      ++ * this ;
      return t ; }

  unsigned_double_int & operator -- ( )
    { -- low ;
      if ( low == unsigned_digit_type ( -1 ) )
        -- high ;
      return * this ; }

  unsigned_double_int operator -- ( int )
    { unsigned_double_int t ( * this ) ;
      -- * this ;
      return t ; }

  unsigned_double_int operator ~ ( ) const
    { return unsigned_double_int ( ~ high, ~ low ) ; }

  friend unsigned_double_int operator & ( const unsigned_double_int & a,
                                          const unsigned_double_int & b )
    { return unsigned_double_int ( a.high & b.high, a.low & b.low ) ; }

  friend unsigned_double_int operator | ( const unsigned_double_int & a,
                                          const unsigned_double_int & b )
    { return unsigned_double_int ( a.high | b.high, a.low | b.low ) ; }

  friend unsigned_double_int operator ^ ( const unsigned_double_int & a,
                                          const unsigned_double_int & b )
    { return unsigned_double_int ( a.high ^ b.high, a.low ^ b.low ) ; }

  unsigned_double_int & operator &= ( const unsigned_double_int & b )
    { high &= b.high ;
      low &= b.low ;
      return * this ; }

  unsigned_double_int & operator |= ( const unsigned_double_int & b )
    { high |= b.high ;
      low |= b.low ;
      return * this ; }

  unsigned_double_int & operator ^= ( const unsigned_double_int & b )
    { high ^= b.high ;
      low ^= b.low ;
      return * this ; }

  unsigned_double_int operator << ( sint n ) const
    { return double_int_shift_left ( * this, n ) ; }

  unsigned_double_int operator >> ( sint n ) const
    { return double_int_unsigned_shift_right ( * this, n ) ; }

  unsigned_double_int & operator <<= ( sint n )
    { return * this = * this << n ; }

  unsigned_double_int & operator >>= ( sint n )
    { return * this = * this >> n ; }

  friend bool operator == ( const unsigned_double_int & a,
                            const unsigned_double_int & b )
    { return a.high == b.high  &&  a.low == b.low ; }

  friend bool operator < ( const unsigned_double_int & a,
                           const unsigned_double_int & b )
    { return a.high < b.high  ||  ( a.high == b.high  &&  a.low < b.low ) ; }

  template < class CharT, class CharTraits >
  friend basic_ostream < CharT, CharTraits > &
    operator << ( basic_ostream < CharT, CharTraits > & o,
                  const unsigned_double_int & x )
    { return output_double_int ( o, x ) ; }

  template < class CharT, class CharTraits >
  friend basic_istream < CharT, CharTraits > &
    operator >> ( basic_istream < CharT, CharTraits > & i,
                  unsigned_double_int & x )
    { return input_double_int ( i, x ) ; }

} ;



// *** UNSIGNED_DOUBLE_INT NUMERIC_TRAITS ***


template < class T >
class numeric_traits < unsigned_double_int < T > >

{
public:

  static const bool is_floating_point = false ;

  static const bool is_signed = false ;

  typedef signed_double_int < T > signed_type ;
  typedef unsigned_double_int < T > unsigned_type ;

  static const sint bit_size = numeric_traits < T > :: bit_size * 2 ;

  static const bool has_double_size_type = false ;
  typedef void double_size_type ;

  static unsigned_double_int < T > min ( )
    { return unsigned_double_int < T > :: min ( ) ; }

  static unsigned_double_int < T > max ( )
    { return unsigned_double_int < T > :: max ( ) ; }

} ;



// *** UNSIGNED_DOUBLE_INT UNSIGNED_DOUBLE_MULTIPLIER ***


template < class T >
class unsigned_double_multiplier < unsigned_double_int < T >, false > :
  public double_int_unsigned_double_multiplier < unsigned_double_int < T > >

{
} ;



// *** UNSIGNED_DOUBLE_INT UNSIGNED_DOUBLE_DIVIDER ***


template < class T >
class unsigned_double_divider < unsigned_double_int < T >, false > :
  public double_int_unsigned_double_divider < unsigned_double_int < T > >

{
} ;



// *** UNSIGNED_DOUBLE_INT RND_STATIC_GENERATOR ***


template < class T >
class rnd_static_generator < unsigned_double_int < T > > :
  public double_int_rnd_static_generator < unsigned_double_int < T > >

{
} ;



// *** UNSIGNED_DOUBLE_INT RANGE_RND_STATIC_GENERATOR ***


template < class T >
class range_rnd_static_generator < unsigned_double_int < T > > :
  public unsigned_int_range_rnd_static_generator < unsigned_double_int < T > >

{
} ;



// *** UNSIGNED_DOUBLE_INT GLOBAL INTERFACES ***


//

template < class T >
inline bool is_negative ( const unsigned_double_int < T > & x )

{
return false ;
}


//

template < class T >
inline bool is_high_bit_set ( const unsigned_double_int < T > & x )

{
return x.is_high_bit_set ( ) ;
}


//

template < class T >
inline sint hamming_weight ( const unsigned_double_int < T > & x )

{
return hamming_weight ( x.high ) + hamming_weight ( x.low ) ;
}


//

template < class T >
inline unsigned_double_int < T >
         signed_shift_right ( const unsigned_double_int < T > & x, sint n )

{
return double_int_signed_shift_right ( x, n ) ;
}


//

template < class T >
inline unsigned_double_int < T >
         unsigned_shift_right ( const unsigned_double_int < T > & x, sint n )

{
return double_int_unsigned_shift_right ( x, n ) ;
}


//

template < class T >
inline sint exponent ( const unsigned_double_int < T > & x )

{
return x.exponent ( ) ;
}



// *** UNSIGNED_DOUBLE_INT IMPLICIT CONVERSION ***


//

template < class T >
class implicit_conversion_test
        < typename unsigned_double_int < T > :: signed_digit_type,
          unsigned_double_int < T > > :
  public implicit_conversion_test_ok

{
} ;


//

template < class T >
class implicit_conversion_test
        < typename unsigned_double_int < T > :: unsigned_digit_type,
          unsigned_double_int < T > > :
  public implicit_conversion_test_ok

{
} ;


//

template < class T >
class implicit_conversion_test
        < signed_double_int < T >, unsigned_double_int < T > > :
  public implicit_conversion_test_ok

{
} ;


//

template < class S, class T >
class implicit_conversion_test < S, unsigned_double_int < T > > :
  public implicit_conversion_test
           < S, typename unsigned_double_int < T > :: unsigned_digit_type >

{
} ;



// *** TYPE CONVERSION ***


//

template < class T >
class type_converter < unsigned_double_int < T >, signed_double_int < T > >

{
public:

  static signed_double_int < T >
    operate ( const unsigned_double_int < T > & x )
    { return signed_double_int < T > ( x.high, x.low ) ; }

} ;


//

template < class T >
class type_converter
        < signed_double_int < T >,
          typename signed_double_int < T > :: unsigned_digit_type >

{
public:

  static typename signed_double_int < T > :: unsigned_digit_type
    operate ( const signed_double_int < T > & x )
    { return x.low ; }

} ;


//

template < class T >
class type_converter
        < unsigned_double_int < T >,
          typename unsigned_double_int < T > :: unsigned_digit_type >

{
public:

  static typename unsigned_double_int < T > :: unsigned_digit_type
    operate ( const unsigned_double_int < T > & x )
    { return x.low ; }

} ;


//

template
  < class DoubleInt, class Destination, bool DestinationIsFloatingPoint >
class from_double_int_type_converter ;


//

template < class DoubleInt, class Destination >
class from_double_int_type_converter < DoubleInt, Destination, false >

{
public:

  static Destination operate ( const DoubleInt & x )
    { return convert_to < Destination > ( x.low ) ; }

} ;


//

template < class DoubleInt, class Destination >
class from_double_int_type_converter < DoubleInt, Destination, true >

{
public:

  static Destination operate ( const DoubleInt & x )
    { return x.template to_floating_point < Destination > ( ) ; }

} ;


//

template < class T, class U >
class type_converter < signed_double_int < T >, U > :
  public from_double_int_type_converter
           < signed_double_int < T >,
             U,
             numeric_traits < U > :: is_floating_point >

{
} ;


//

template < class T, class U >
class type_converter < unsigned_double_int < T >, U > :
  public from_double_int_type_converter
           < unsigned_double_int < T >,
             U,
             numeric_traits < U > :: is_floating_point >

{
} ;


//

template < class Source, class DoubleInt, bool SourceIsFloatingPoint >
class to_double_int_type_converter ;


//

template < class Source, class DoubleInt >
class to_double_int_type_converter < Source, DoubleInt, false >

{
public:

  static DoubleInt operate ( const Source & x )
    { return DoubleInt ( x ) ; }

} ;


//

template < class Source, class DoubleInt >
class to_double_int_type_converter < Source, DoubleInt, true >

{
public:

  static DoubleInt operate ( const Source & x )
    { return DoubleInt :: from_floating_point ( x ) ; }

} ;


//

template < class S, class T >
class type_converter < S, signed_double_int < T > > :
  public to_double_int_type_converter
           < S,
             signed_double_int < T >,
             numeric_traits < S > :: is_floating_point >

{
} ;


//

template < class S, class T >
class type_converter < S, unsigned_double_int < T > > :
  public to_double_int_type_converter
           < S,
             unsigned_double_int < T >,
             numeric_traits < S > :: is_floating_point >

{
} ;



#endif
