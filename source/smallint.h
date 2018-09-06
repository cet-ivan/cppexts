// Copyright Ivan Stanojevic 2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __SMALLINT_H

#define __SMALLINT_H



#include "compspec.h"

#include "istream.h"
#include "ostream.h"
#include "utility.h"
#include "type_traits.h"

#include "numbase.h"
#include "rnd.h"
#include "typeconv.h"



// *** FORWARD DECLARATIONS ***


//

template < class T, sint Bits >
class signed_small_int ;

template < class T, sint Bits >
class unsigned_small_int ;


//

template < class T, sint Bits >
signed_small_int < T, Bits >
  operator + ( const signed_small_int < T, Bits > & a,
               const signed_small_int < T, Bits > & b ) ;

template < class T, sint Bits >
signed_small_int < T, Bits >
  operator - ( const signed_small_int < T, Bits > & a,
               const signed_small_int < T, Bits > & b ) ;

template < class T, sint Bits >
signed_small_int < T, Bits >
  operator * ( const signed_small_int < T, Bits > & a,
               const signed_small_int < T, Bits > & b ) ;

template < class T, sint Bits >
void divmod ( signed_small_int < T, Bits > a,
              signed_small_int < T, Bits > b,
              signed_small_int < T, Bits > & q,
              signed_small_int < T, Bits > & r ) ;

template < class T, sint Bits >
signed_small_int < T, Bits >
  operator / ( const signed_small_int < T, Bits > & a,
               const signed_small_int < T, Bits > & b ) ;

template < class T, sint Bits >
signed_small_int < T, Bits >
  operator % ( const signed_small_int < T, Bits > & a,
               const signed_small_int < T, Bits > & b ) ;

template < class T, sint Bits >
signed_small_int < T, Bits >
  operator & ( const signed_small_int < T, Bits > & a,
               const signed_small_int < T, Bits > & b ) ;

template < class T, sint Bits >
signed_small_int < T, Bits >
  operator | ( const signed_small_int < T, Bits > & a,
               const signed_small_int < T, Bits > & b ) ;

template < class T, sint Bits >
signed_small_int < T, Bits >
  operator ^ ( const signed_small_int < T, Bits > & a,
               const signed_small_int < T, Bits > & b ) ;

template < class T, sint Bits >
bool operator == ( const signed_small_int < T, Bits > & a,
                   const signed_small_int < T, Bits > & b ) ;

template < class T, sint Bits >
bool operator < ( const signed_small_int < T, Bits > & a,
                  const signed_small_int < T, Bits > & b ) ;

template < class T, sint Bits >
bool is_negative ( const signed_small_int < T, Bits > & x ) ;

template < class T, sint Bits >
bool is_high_bit_set ( const signed_small_int < T, Bits > & x ) ;

template < class T, sint Bits >
sint hamming_weight ( const signed_small_int < T, Bits > & x ) ;

template < class T, sint Bits >
signed_small_int < T, Bits >
  signed_shift_right ( const signed_small_int < T, Bits > & x, sint n ) ;

template < class T, sint Bits >
signed_small_int < T, Bits >
  unsigned_shift_right ( const signed_small_int < T, Bits > & x, sint n ) ;

template < class T, sint Bits >
signed_small_int < T, Bits >
  low_half ( const signed_small_int < T, Bits > & x ) ;

template < class T, sint Bits >
signed_small_int < T, Bits >
  low_half_high ( const signed_small_int < T, Bits > & x ) ;

template < class T, sint Bits >
signed_small_int < T, Bits >
  high_half ( const signed_small_int < T, Bits > & x ) ;

template < class T, sint Bits >
sint exponent ( const signed_small_int < T, Bits > & x ) ;

template < class T, sint Bits >
void normalize_gcd ( signed_small_int < T, Bits > & gcd ) ;

template < class T, sint Bits >
void normalize_gcd_ext ( signed_small_int < T, Bits > & c,
                         signed_small_int < T, Bits > & d,
                         signed_small_int < T, Bits > & gcd ) ;

template < class T, sint Bits >
void normalize_fraction ( signed_small_int < T, Bits > & a,
                          signed_small_int < T, Bits > & b ) ;


//

template < class T, sint Bits >
unsigned_small_int < T, Bits >
  operator + ( const unsigned_small_int < T, Bits > & a,
               const unsigned_small_int < T, Bits > & b ) ;

template < class T, sint Bits >
unsigned_small_int < T, Bits >
  operator - ( const unsigned_small_int < T, Bits > & a,
               const unsigned_small_int < T, Bits > & b ) ;

template < class T, sint Bits >
unsigned_small_int < T, Bits >
  operator * ( const unsigned_small_int < T, Bits > & a,
               const unsigned_small_int < T, Bits > & b ) ;

template < class T, sint Bits >
void divmod ( unsigned_small_int < T, Bits > a,
              unsigned_small_int < T, Bits > b,
              unsigned_small_int < T, Bits > & q,
              unsigned_small_int < T, Bits > & r ) ;

template < class T, sint Bits >
unsigned_small_int < T, Bits >
  operator / ( const unsigned_small_int < T, Bits > & a,
               const unsigned_small_int < T, Bits > & b ) ;

template < class T, sint Bits >
unsigned_small_int < T, Bits >
  operator % ( const unsigned_small_int < T, Bits > & a,
               const unsigned_small_int < T, Bits > & b ) ;

template < class T, sint Bits >
unsigned_small_int < T, Bits >
  operator & ( const unsigned_small_int < T, Bits > & a,
               const unsigned_small_int < T, Bits > & b ) ;

template < class T, sint Bits >
unsigned_small_int < T, Bits >
  operator | ( const unsigned_small_int < T, Bits > & a,
               const unsigned_small_int < T, Bits > & b ) ;

template < class T, sint Bits >
unsigned_small_int < T, Bits >
  operator ^ ( const unsigned_small_int < T, Bits > & a,
               const unsigned_small_int < T, Bits > & b ) ;

template < class T, sint Bits >
bool operator == ( const unsigned_small_int < T, Bits > & a,
                   const unsigned_small_int < T, Bits > & b ) ;

template < class T, sint Bits >
bool operator < ( const unsigned_small_int < T, Bits > & a,
                  const unsigned_small_int < T, Bits > & b ) ;

template < class T, sint Bits >
bool is_negative ( const unsigned_small_int < T, Bits > & x ) ;

template < class T, sint Bits >
bool is_high_bit_set ( const unsigned_small_int < T, Bits > & x ) ;

template < class T, sint Bits >
sint hamming_weight ( const unsigned_small_int < T, Bits > & x ) ;

template < class T, sint Bits >
unsigned_small_int < T, Bits >
  signed_shift_right ( const unsigned_small_int < T, Bits > & x, sint n ) ;

template < class T, sint Bits >
unsigned_small_int < T, Bits >
  unsigned_shift_right ( const unsigned_small_int < T, Bits > & x, sint n ) ;

template < class T, sint Bits >
unsigned_small_int < T, Bits >
  low_half ( const unsigned_small_int < T, Bits > & x ) ;

template < class T, sint Bits >
unsigned_small_int < T, Bits >
  low_half_high ( const unsigned_small_int < T, Bits > & x ) ;

template < class T, sint Bits >
unsigned_small_int < T, Bits >
  high_half ( const unsigned_small_int < T, Bits > & x ) ;

template < class T, sint Bits >
sint exponent ( const unsigned_small_int < T, Bits > & x ) ;



// *** SMALL_INT_RND_STATIC_GENERATOR ***


template < class SmallInt >
class small_int_rnd_static_generator

{
public:

  static SmallInt operate ( )
    { return
        SmallInt ( rnd < typename SmallInt :: unsigned_value_type > ( ) ) ; }

} ;



// *** SMALL_INT_BASE ***


//

template < class T, sint Bits >
class small_int_base

{
public:

  typedef typename numeric_traits < T > :: signed_type signed_value_type ;
  typedef typename numeric_traits < T > :: unsigned_type unsigned_value_type ;

  static const sint bit_size = Bits ;

private:

  static_assert
    (     bit_size > 0
      &&  bit_size <= numeric_traits < unsigned_value_type > :: bit_size,
      "Illegal bit size." ) ;

protected:

  static const unsigned_value_type high_bit_mask ;
  static const unsigned_value_type low_bits_mask ;
  static const unsigned_value_type mask ;

} ;


//

template < class T, sint Bits >
const typename small_int_base < T, Bits > :: unsigned_value_type
  small_int_base < T, Bits > :: high_bit_mask =
    unsigned_value_type ( 1 ) << ( bit_size - 1 ) ;


//

template < class T, sint Bits >
const typename small_int_base < T, Bits > :: unsigned_value_type
  small_int_base < T, Bits > :: low_bits_mask =
    high_bit_mask - unsigned_value_type ( 1 ) ;


//

template < class T, sint Bits >
const typename small_int_base < T, Bits > :: unsigned_value_type
  small_int_base < T, Bits > :: mask =
    high_bit_mask + low_bits_mask ;



//

#ifdef NDEBUG

#define __DEFINE_SMALL_INT_BASE(Type)                                     \
                                                                          \
template < sint Bits >                                                    \
class small_int_base < Type, Bits >                                       \
                                                                          \
{                                                                         \
public:                                                                   \
                                                                          \
  typedef numeric_traits < Type > :: signed_type signed_value_type ;      \
  typedef numeric_traits < Type > :: unsigned_type unsigned_value_type ;  \
                                                                          \
  static const sint bit_size = Bits ;                                     \
                                                                          \
private:                                                                  \
                                                                          \
  static_assert                                                           \
    (     bit_size > 0                                                    \
      &&  bit_size <= numeric_traits < unsigned_value_type > :: bit_size, \
      "Illegal bit size." )  ;                                            \
                                                                          \
protected:                                                                \
                                                                          \
  static const unsigned_value_type                                        \
    high_bit_mask = unsigned_value_type ( 1 ) << ( bit_size - 1 ) ;       \
                                                                          \
  static const unsigned_value_type                                        \
    low_bits_mask = high_bit_mask - unsigned_value_type ( 1 ) ;           \
                                                                          \
  static const unsigned_value_type                                        \
    mask = high_bit_mask + low_bits_mask ;                                \
                                                                          \
} ;

FOR_BUILTIN_INTEGRAL_TYPES(__DEFINE_SMALL_INT_BASE)

#undef __DEFINE_SMALL_INT_BASE

#endif



// *** SIGNED_SMALL_INT ***


template < class T, sint Bits >
class signed_small_int : private small_int_base < T, Bits >

{
public:

  using typename small_int_base < T, Bits > :: signed_value_type ;
  using typename small_int_base < T, Bits > :: unsigned_value_type ;
  using small_int_base < T, Bits > :: bit_size ;

private:

  using small_int_base < T, Bits > :: high_bit_mask ;
  using small_int_base < T, Bits > :: low_bits_mask ;
  using small_int_base < T, Bits > :: mask ;

  unsigned_value_type data ;

public:

  signed_small_int ( ) :
    data ( 0 )
    { }

  signed_small_int ( const signed_value_type & x ) :
    data ( x & mask )
    { }

  signed_small_int ( const unsigned_value_type & x ) :
    data ( x & mask )
    { }

  template < sint XBits >
  signed_small_int ( const signed_small_int < T, XBits > & x ) :
    data ( x.signed_data ( ) & mask )
    { }

  template < class S >
  signed_small_int ( S x,
                     typename implicit_conversion_test
                                < S, unsigned_value_type > :: result =
                       implicit_conversion_allowed ) :
    data ( unsigned_value_type ( x ) & mask )
    { }

  static signed_small_int min ( )
    { return signed_small_int ( high_bit_mask ) ; }

  static signed_small_int max ( )
    { return signed_small_int ( low_bits_mask ) ; }

  signed_value_type signed_data ( ) const
    { return convert_to < signed_value_type >
               ( data - ( ( data & high_bit_mask ) << 1 ) ) ; }

  unsigned_value_type unsigned_data ( ) const
    { return data ; }

  bool is_high_bit_set ( ) const
    { return ( data & high_bit_mask ) != unsigned_value_type ( 0 ) ; }

  sint hamming_weight ( ) const
    { return :: hamming_weight ( data ) ; }

  const signed_small_int & operator + ( ) const
    { return * this ; }

  signed_small_int operator - ( ) const
    { return signed_small_int ( - data ) ; }

  friend signed_small_int operator + ( const signed_small_int & a,
                                       const signed_small_int & b )
    { return signed_small_int ( a.data + b.data ) ; }

  friend signed_small_int operator - ( const signed_small_int & a,
                                       const signed_small_int & b )
    { return signed_small_int ( a.data - b.data ) ; }

  friend signed_small_int operator * ( const signed_small_int & a,
                                       const signed_small_int & b )
    { return signed_small_int ( a.data * b.data ) ; }

  friend void divmod ( signed_small_int a, signed_small_int b,
                       signed_small_int & q, signed_small_int & r )
    { q = a / b ;
      r = a % b ; }

  friend signed_small_int operator / ( const signed_small_int & a,
                                       const signed_small_int & b )
    { return signed_small_int ( a.signed_data ( ) / b.signed_data ( ) ) ; }

  friend signed_small_int operator % ( const signed_small_int & a,
                                       const signed_small_int & b )
    { return signed_small_int ( a.signed_data ( ) % b.signed_data ( ) ) ; }

  signed_small_int & operator += ( const signed_small_int & b )
    { data = ( data + b.data ) & mask ;
      return * this ; }

  signed_small_int & operator -= ( const signed_small_int & b )
    { data = ( data - b.data ) & mask ;
      return * this ; }

  signed_small_int & operator *= ( const signed_small_int & b )
    { data = ( data * b.data ) & mask ;
      return * this ; }

  signed_small_int & operator /= ( const signed_small_int & b )
    { data = ( signed_data ( ) / b.signed_data ( ) ) & mask ;
      return * this ; }

  signed_small_int & operator %= ( const signed_small_int & b )
    { data = ( signed_data ( ) % b.signed_data ( ) ) & mask ;
      return * this ; }

  signed_small_int & operator ++ ( )
    { ++ data ;
      data &= mask ;
      return * this ; }

  signed_small_int operator ++ ( int )
    { unsigned_value_type t ( data ) ;
      ++ * this ;
      return t ; }

  signed_small_int & operator -- ( )
    { -- data ;
      data &= mask ;
      return * this ; }

  signed_small_int operator -- ( int )
    { unsigned_value_type t ( data ) ;
      -- * this ;
      return t ; }

  signed_small_int operator ~ ( ) const
    { return signed_small_int ( ~ data ) ; }

  friend signed_small_int operator & ( const signed_small_int & a,
                                       const signed_small_int & b )
    { return signed_small_int ( a.data & b.data ) ; }

  friend signed_small_int operator | ( const signed_small_int & a,
                                       const signed_small_int & b )
    { return signed_small_int ( a.data | b.data ) ; }

  friend signed_small_int operator ^ ( const signed_small_int & a,
                                       const signed_small_int & b )
    { return signed_small_int ( a.data ^ b.data ) ; }

  signed_small_int & operator &= ( const signed_small_int & b )
    { data &= b.data ;
      return * this ; }

  signed_small_int & operator |= ( const signed_small_int & b )
    { data |= b.data ;
      return * this ; }

  signed_small_int & operator ^= ( const signed_small_int & b )
    { data ^= b.data ;
      return * this ; }

  signed_small_int signed_shift_right ( sint n ) const
    { assert ( n >= 0  &&  n < bit_size ) ;
      return signed_small_int ( signed_data ( ) >> n ) ; }

  signed_small_int unsigned_shift_right ( sint n ) const
    { assert ( n >= 0  &&  n < bit_size ) ;
      return signed_small_int ( data >> n ) ; }

  signed_small_int operator << ( sint n ) const
    { assert ( n >= 0  &&  n < bit_size ) ;
      return signed_small_int ( data << n ) ; }

  signed_small_int operator >> ( sint n ) const
    { assert ( n >= 0  &&  n < bit_size ) ;
      return signed_shift_right ( n ) ; }

  signed_small_int & operator <<= ( sint n )
    { assert ( n >= 0  &&  n < bit_size ) ;
      data = ( data << n ) & mask ;
      return * this ; }

  signed_small_int & operator >>= ( sint n )
    { assert ( n >= 0  &&  n < bit_size ) ;
      data = ( signed_data ( ) >> n ) & mask ;
      return * this ; }

  friend bool operator == ( const signed_small_int & a,
                            const signed_small_int & b )
    { return a.data == b.data ; }

  friend bool operator < ( const signed_small_int & a,
                           const signed_small_int & b )
    { return ( ( a.data - b.data ) & high_bit_mask ) != 0 ; }

  template < class CharT, class CharTraits >
  friend basic_ostream < CharT, CharTraits > &
    operator << ( basic_ostream < CharT, CharTraits > & o,
                  const signed_small_int & x )
    { return o << x.signed_data ( ) ; }

  template < class CharT, class CharTraits >
  friend basic_istream < CharT, CharTraits > &
    operator >> ( basic_istream < CharT, CharTraits > & i,
                  signed_small_int & x )
    { i >> x.data ;
      x.data &= mask ;
      return i ; }

} ;



// *** SIGNED_SMALL_INT NUMERIC_TRAITS ***


template < class T, sint Bits >
class numeric_traits < signed_small_int < T, Bits > >

{
public:

  static const bool is_floating_point = false ;

  static const bool is_signed = true ;

  typedef signed_small_int < T, Bits > signed_type ;
  typedef unsigned_small_int < T, Bits > unsigned_type ;

  static const sint bit_size = signed_small_int < T, Bits > :: bit_size ;

  static const bool has_double_size_type =
    bit_size * 2 <= numeric_traits < T > :: bit_size ;

  typedef typename conditional < has_double_size_type,
                                 signed_small_int < T, bit_size * 2 >,
                                 void > :: type
    double_size_type ;

  static signed_small_int < T, Bits > min ( )
    { return signed_small_int < T, Bits > :: min ( ) ; }

  static signed_small_int < T, Bits > max ( )
    { return signed_small_int < T, Bits > :: max ( ) ; }

} ;



// *** SIGNED_SMALL_INT RND_STATIC_GENERATOR ***


template < class T, sint Bits >
class rnd_static_generator < signed_small_int < T, Bits > > :
  public small_int_rnd_static_generator < signed_small_int < T, Bits > >

{
} ;



// *** SIGNED_SMALL_INT RANGE_RND_STATIC_GENERATOR ***


template < class T, sint Bits >
class range_rnd_static_generator < signed_small_int < T, Bits > > :
  public signed_int_range_rnd_static_generator
           < signed_small_int < T, Bits > >

{
} ;



// *** SIGNED_SMALL_INT GLOBAL INTERFACES ***


//

template < class T, sint Bits >
inline bool is_negative ( const signed_small_int < T, Bits > & x )

{
return x.is_high_bit_set ( ) ;
}


//

template < class T, sint Bits >
inline bool is_high_bit_set ( const signed_small_int < T, Bits > & x )

{
return x.is_high_bit_set ( ) ;
}


//

template < class T, sint Bits >
inline sint hamming_weight ( const signed_small_int < T, Bits > & x )

{
return x.hamming_weight ( ) ;
}


//

template < class T, sint Bits >
inline
  signed_small_int < T, Bits >
    signed_shift_right ( const signed_small_int < T, Bits > & x, sint n )

{
return x.signed_shift_right ( n ) ;
}


//

template < class T, sint Bits >
inline
  signed_small_int < T, Bits >
    unsigned_shift_right ( const signed_small_int < T, Bits > & x, sint n )

{
return x.unsigned_shift_right ( n ) ;
}


//

template < class T, sint Bits >
inline signed_small_int < T, Bits >
         low_half ( const signed_small_int < T, Bits > & x )

{
return generic_low_half ( x ) ;
}


//

template < class T, sint Bits >
inline signed_small_int < T, Bits >
         low_half_high ( const signed_small_int < T, Bits > & x )

{
return generic_low_half_high ( x ) ;
}


//

template < class T, sint Bits >
inline signed_small_int < T, Bits >
         high_half ( const signed_small_int < T, Bits > & x )

{
return generic_high_half ( x ) ;
}


//

template < class T, sint Bits >
inline sint exponent ( const signed_small_int < T, Bits > & x )

{
return exponent ( x.signed_data ( ) ) ;
}


//

template < class T, sint Bits >
inline void normalize_gcd ( signed_small_int < T, Bits > & gcd )

{
if ( is_negative ( gcd ) )
  gcd = - gcd ;
}


//

template < class T, sint Bits >
inline void normalize_gcd_ext ( signed_small_int < T, Bits > & c,
                                signed_small_int < T, Bits > & d,
                                signed_small_int < T, Bits > & gcd )

{
if ( is_negative ( gcd ) )
  {
  c = - c ;
  d = - d ;
  gcd = - gcd ;
  }
}


//

template < class T, sint Bits >
inline void normalize_fraction ( signed_small_int < T, Bits > & a,
                                 signed_small_int < T, Bits > & b )

{
if ( is_negative ( b ) )
  {
  a = - a ;
  b = - b ;
  }
}



// *** SIGNED_SMALL_INT IMPLICIT CONVERSION ***


//

template < class T, sint Bits >
class implicit_conversion_test
        < typename signed_small_int < T, Bits > :: signed_value_type,
          signed_small_int < T, Bits > > :
  public implicit_conversion_test_ok

{
} ;


//

template < class T, sint Bits >
class implicit_conversion_test
        < typename signed_small_int < T, Bits > :: unsigned_value_type,
          signed_small_int < T, Bits > > :
  public implicit_conversion_test_ok

{
} ;


//

template < class T, sint XBits, sint Bits >
class implicit_conversion_test < signed_small_int < T, XBits >,
                                 signed_small_int < T, Bits > > :
  public implicit_conversion_test_ok

{
} ;


//

template < class S, class T, sint Bits >
class implicit_conversion_test < S, signed_small_int < T, Bits > > :
  public implicit_conversion_test
           < S, typename signed_small_int < T, Bits > :: unsigned_value_type >

{
} ;



// *** UNSIGNED_SMALL_INT ***


template < class T, sint Bits >
class unsigned_small_int : private small_int_base < T, Bits >

{
public:

  using typename small_int_base < T, Bits > :: signed_value_type ;
  using typename small_int_base < T, Bits > :: unsigned_value_type ;
  using small_int_base < T, Bits > :: bit_size ;

private:

  using small_int_base < T, Bits > :: high_bit_mask ;
  using small_int_base < T, Bits > :: low_bits_mask ;
  using small_int_base < T, Bits > :: mask ;

  unsigned_value_type data ;

public:

  unsigned_small_int ( ) :
    data ( 0 )
    { }

  unsigned_small_int ( const signed_value_type & x ) :
    data ( x & mask )
    { }

  unsigned_small_int ( const unsigned_value_type & x ) :
    data ( x & mask )
    { }

  template < sint XBits >
  unsigned_small_int ( const signed_small_int < T, XBits > & x ) :
    data ( x.signed_data ( ) & mask )
    { }

  template < sint XBits >
  unsigned_small_int ( const unsigned_small_int < T, XBits > & x ) :
    data ( x.unsigned_data ( ) & mask )
    { }

  template < class S >
  unsigned_small_int ( S x,
                       typename implicit_conversion_test
                                  < S, unsigned_value_type > :: result =
                         implicit_conversion_allowed ) :
    data ( unsigned_value_type ( x ) & mask )
    { }

  static unsigned_small_int min ( )
    { return unsigned_small_int ( 0 ) ; }

  static unsigned_small_int max ( )
    { return unsigned_small_int ( mask ) ; }

  signed_value_type signed_data ( ) const
    { return convert_to < signed_value_type >
               ( data - ( ( data & high_bit_mask ) << 1 ) ) ; }

  unsigned_value_type unsigned_data ( ) const
    { return data ; }

  bool is_high_bit_set ( ) const
    { return ( data & high_bit_mask ) != unsigned_value_type ( 0 ) ; }

  sint hamming_weight ( ) const
    { return :: hamming_weight ( data ) ; }

  const unsigned_small_int & operator + ( ) const
    { return * this ; }

  unsigned_small_int operator - ( ) const
    { return unsigned_small_int ( - data ) ; }

  friend unsigned_small_int operator + ( const unsigned_small_int & a,
                                         const unsigned_small_int & b )
    { return unsigned_small_int ( a.data + b.data ) ; }

  friend unsigned_small_int operator - ( const unsigned_small_int & a,
                                         const unsigned_small_int & b )
    { return unsigned_small_int ( a.data - b.data ) ; }

  friend unsigned_small_int operator * ( const unsigned_small_int & a,
                                         const unsigned_small_int & b )
    { return unsigned_small_int ( a.data * b.data ) ; }

  friend void divmod ( unsigned_small_int a, unsigned_small_int b,
                       unsigned_small_int & q, unsigned_small_int & r )
    { q = a / b ;
      r = a % b ; }

  friend unsigned_small_int operator / ( const unsigned_small_int & a,
                                         const unsigned_small_int & b )
    { return unsigned_small_int ( a.data / b.data ) ; }

  friend unsigned_small_int operator % ( const unsigned_small_int & a,
                                         const unsigned_small_int & b )
    { return unsigned_small_int ( a.data % b.data ) ; }

  unsigned_small_int & operator += ( const unsigned_small_int & b )
    { data = ( data + b.data ) & mask ;
      return * this ; }

  unsigned_small_int & operator -= ( const unsigned_small_int & b )
    { data = ( data - b.data ) & mask ;
      return * this ; }

  unsigned_small_int & operator *= ( const unsigned_small_int & b )
    { data = ( data * b.data ) & mask ;
      return * this ; }

  unsigned_small_int & operator /= ( const unsigned_small_int & b )
    { data /= b.data ;
      return * this ; }

  unsigned_small_int & operator %= ( const unsigned_small_int & b )
    { data %= b.data ;
      return * this ; }

  unsigned_small_int & operator ++ ( )
    { ++ data ;
      data &= mask ;
      return * this ; }

  unsigned_small_int operator ++ ( int )
    { unsigned_value_type t ( data ) ;
      ++ * this ;
      return t ; }

  unsigned_small_int & operator -- ( )
    { -- data ;
      data &= mask ;
      return * this ; }

  unsigned_small_int operator -- ( int )
    { unsigned_value_type t ( data ) ;
      -- * this ;
      return t ; }

  unsigned_small_int operator ~ ( ) const
    { return unsigned_small_int ( ~ data ) ; }

  friend unsigned_small_int operator & ( const unsigned_small_int & a,
                                         const unsigned_small_int & b )
    { return unsigned_small_int ( a.data & b.data ) ; }

  friend unsigned_small_int operator | ( const unsigned_small_int & a,
                                         const unsigned_small_int & b )
    { return unsigned_small_int ( a.data | b.data ) ; }

  friend unsigned_small_int operator ^ ( const unsigned_small_int & a,
                                         const unsigned_small_int & b )
    { return unsigned_small_int ( a.data ^ b.data ) ; }

  unsigned_small_int & operator &= ( const unsigned_small_int & b )
    { data &= b.data ;
      return * this ; }

  unsigned_small_int & operator |= ( const unsigned_small_int & b )
    { data |= b.data ;
      return * this ; }

  unsigned_small_int & operator ^= ( const unsigned_small_int & b )
    { data ^= b.data ;
      return * this ; }

  unsigned_small_int signed_shift_right ( sint n ) const
    { assert ( n >= 0  &&  n < bit_size ) ;
      return unsigned_small_int ( signed_data ( ) >> n ) ; }

  unsigned_small_int unsigned_shift_right ( sint n ) const
    { assert ( n >= 0  &&  n < bit_size ) ;
      return unsigned_small_int ( data >> n ) ; }

  unsigned_small_int operator << ( sint n ) const
    { assert ( n >= 0  &&  n < bit_size ) ;
      return unsigned_small_int ( data << n ) ; }

  unsigned_small_int operator >> ( sint n ) const
    { assert ( n >= 0  &&  n < bit_size ) ;
      return unsigned_shift_right ( n ) ; }

  unsigned_small_int & operator <<= ( sint n )
    { assert ( n >= 0  &&  n < bit_size ) ;
      data = ( data << n ) & mask ;
      return * this ; }

  unsigned_small_int & operator >>= ( sint n )
    { assert ( n >= 0  &&  n < bit_size ) ;
      data >>= n ;
      return * this ; }

  friend bool operator == ( const unsigned_small_int & a,
                            const unsigned_small_int & b )
    { return a.data == b.data ; }

  friend bool operator < ( const unsigned_small_int & a,
                           const unsigned_small_int & b )
    { return a.data < b.data ; }

  template < class CharT, class CharTraits >
  friend basic_ostream < CharT, CharTraits > &
    operator << ( basic_ostream < CharT, CharTraits > & o,
                  const unsigned_small_int & x )
    { return o << x.data ; }

  template < class CharT, class CharTraits >
  friend basic_istream < CharT, CharTraits > &
    operator >> ( basic_istream < CharT, CharTraits > & i,
                  unsigned_small_int & x )
    { i >> x.data ;
      x.data &= mask ;
      return i ; }

} ;



// *** UNSIGNED_SMALL_INT NUMERIC_TRAITS ***


template < class T, sint Bits >
class numeric_traits < unsigned_small_int < T, Bits > >

{
public:

  static const bool is_floating_point = false ;

  static const bool is_signed = false ;

  typedef signed_small_int < T, Bits > signed_type ;
  typedef unsigned_small_int < T, Bits > unsigned_type ;

  static const sint bit_size = unsigned_small_int < T, Bits > :: bit_size ;

  static const bool has_double_size_type =
    bit_size * 2 <= numeric_traits < T > :: bit_size ;

  typedef typename conditional < has_double_size_type,
                                 unsigned_small_int < T, bit_size * 2 >,
                                 void > :: type
    double_size_type ;

  static unsigned_small_int < T, Bits > min ( )
    { return unsigned_small_int < T, Bits > :: min ( ) ; }

  static unsigned_small_int < T, Bits > max ( )
    { return unsigned_small_int < T, Bits > :: max ( ) ; }

} ;



// *** UNSIGNED_SMALL_INT RND_STATIC_GENERATOR ***


template < class T, sint Bits >
class rnd_static_generator < unsigned_small_int < T, Bits > > :
  public small_int_rnd_static_generator < unsigned_small_int < T, Bits > >

{
} ;



// *** UNSIGNED_SMALL_INT RANGE_RND_STATIC_GENERATOR ***


template < class T, sint Bits >
class range_rnd_static_generator < unsigned_small_int < T, Bits > > :
  public unsigned_int_range_rnd_static_generator
           < unsigned_small_int < T, Bits > >

{
} ;



// *** UNSIGNED_SMALL_INT GLOBAL INTERFACES ***


//

template < class T, sint Bits >
inline bool is_negative ( const unsigned_small_int < T, Bits > & x )

{
return false ;
}


//

template < class T, sint Bits >
inline bool is_high_bit_set ( const unsigned_small_int < T, Bits > & x )

{
return x.is_high_bit_set ( ) ;
}


//

template < class T, sint Bits >
inline sint hamming_weight ( const unsigned_small_int < T, Bits > & x )

{
return x.hamming_weight ( ) ;
}


//

template < class T, sint Bits >
inline
  unsigned_small_int < T, Bits >
    signed_shift_right ( const unsigned_small_int < T, Bits > & x, sint n )

{
return x.signed_shift_right ( n ) ;
}


//

template < class T, sint Bits >
inline
  unsigned_small_int < T, Bits >
    unsigned_shift_right ( const unsigned_small_int < T, Bits > & x, sint n )

{
return x.unsigned_shift_right ( n ) ;
}


//

template < class T, sint Bits >
inline unsigned_small_int < T, Bits >
         low_half ( const unsigned_small_int < T, Bits > & x )

{
return generic_low_half ( x ) ;
}


//

template < class T, sint Bits >
inline unsigned_small_int < T, Bits >
         low_half_high ( const unsigned_small_int < T, Bits > & x )

{
return generic_low_half_high ( x ) ;
}


//

template < class T, sint Bits >
inline unsigned_small_int < T, Bits >
         high_half ( const unsigned_small_int < T, Bits > & x )

{
return generic_high_half ( x ) ;
}


//

template < class T, sint Bits >
inline sint exponent ( const unsigned_small_int < T, Bits > & x )

{
return exponent ( x.unsigned_data ( ) ) ;
}



// *** UNSIGNED_SMALL_INT IMPLICIT CONVERSION ***


//

template < class T, sint Bits >
class implicit_conversion_test
        < typename unsigned_small_int < T, Bits > :: signed_value_type,
          unsigned_small_int < T, Bits > > :
  public implicit_conversion_test_ok

{
} ;


//

template < class T, sint Bits >
class implicit_conversion_test
        < typename unsigned_small_int < T, Bits > :: unsigned_value_type,
          unsigned_small_int < T, Bits > > :
  public implicit_conversion_test_ok

{
} ;


//

template < class T, sint XBits, sint Bits >
class implicit_conversion_test < signed_small_int < T, XBits >,
                                 unsigned_small_int < T, Bits > > :
  public implicit_conversion_test_ok

{
} ;


//

template < class T, sint XBits, sint Bits >
class implicit_conversion_test < unsigned_small_int < T, XBits >,
                                 unsigned_small_int < T, Bits > > :
  public implicit_conversion_test_ok

{
} ;


//

template < class S, class T, sint Bits >
class implicit_conversion_test < S, unsigned_small_int < T, Bits > > :
  public implicit_conversion_test
           < S, typename unsigned_small_int < T, Bits > :: unsigned_value_type >

{
} ;



// *** TYPE CONVERSION ***


//

template < class T, sint Bits >
class type_converter < unsigned_small_int < T, Bits >,
                       signed_small_int < T, Bits > >

{
public:

  static signed_small_int < T, Bits >
    operate ( const unsigned_small_int < T, Bits > & x )
    { return signed_small_int < T, Bits > ( x.unsigned_data ( ) ) ; }

} ;


//

template < class T, sint Bits >
class type_converter
        < signed_small_int < T, Bits >,
          typename signed_small_int < T, Bits > :: signed_value_type >

{
public:

  static typename signed_small_int < T, Bits > :: signed_value_type
    operate ( const signed_small_int < T, Bits > & x )
    { return x.signed_data ( ) ; }

} ;


//

template < class T, sint Bits, class U >
class type_converter < signed_small_int < T, Bits >, U >

{
public:

  static U operate ( const signed_small_int < T, Bits > & x )
    { return convert_to < U > ( x.signed_data ( ) ) ; }

} ;


//

template < class T, sint Bits >
class type_converter
        < unsigned_small_int < T, Bits >,
          typename unsigned_small_int < T, Bits > :: unsigned_value_type >

{
public:

  static typename unsigned_small_int < T, Bits > :: unsigned_value_type
    operate ( const unsigned_small_int < T, Bits > & x )
    { return x.unsigned_data ( ) ; }

} ;


//

template < class T, sint Bits, class U >
class type_converter < unsigned_small_int < T, Bits >, U >

{
public:

  static U operate ( const unsigned_small_int < T, Bits > & x )
    { return convert_to < U > ( x.unsigned_data ( ) ) ; }

} ;



#endif
