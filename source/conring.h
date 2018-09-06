// Copyright Ivan Stanojevic 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __CONRING_H

#define __CONRING_H



#include "compspec.h"

#include "cassert.h"
#include "istream.h"
#include "ostream.h"
#include "utility.h"

#include "typeconv.h"



// *** NORMALIZE_CONGRUENCE_RING_ELEMENT ***


//

template < class T >
inline void normalize_congruence_ring_element ( T & value, const T & modulus )

{
value %= modulus ;
}


//

#define __DEFINE_NORMALIZE_CONGRUENCE_RING_ELEMENT(Type)                     \
                                                                             \
inline void normalize_congruence_ring_element ( Type & value, Type modulus ) \
                                                                             \
{                                                                            \
value %= modulus ;                                                           \
if ( value < 0 )                                                             \
  value += modulus ;                                                         \
}

FOR_BUILTIN_SIGNED_INTEGRAL_TYPES(__DEFINE_NORMALIZE_CONGRUENCE_RING_ELEMENT)

#undef __DEFINE_NORMALIZE_CONGRUENCE_RING_ELEMENT



// *** FORWARD DECLARATIONS ***


template < class RingTraits >
class congruence_ring ;


template < class RingTraits >
congruence_ring < RingTraits >
  operator + ( const congruence_ring < RingTraits > & a,
               const congruence_ring < RingTraits > & b ) ;


template < class RingTraits >
congruence_ring < RingTraits >
  operator - ( const congruence_ring < RingTraits > & a,
               const congruence_ring < RingTraits > & b ) ;


template < class RingTraits >
congruence_ring < RingTraits >
  operator * ( const congruence_ring < RingTraits > & a,
               const congruence_ring < RingTraits > & b ) ;


template < class RingTraits >
congruence_ring < RingTraits >
  operator / ( const congruence_ring < RingTraits > & a,
               const congruence_ring < RingTraits > & b ) ;


template < class RingTraits >
bool operator == ( const congruence_ring < RingTraits > & a,
                   const congruence_ring < RingTraits > & b ) ;


template < class RingTraits >
bool operator < ( const congruence_ring < RingTraits > & a,
                  const congruence_ring < RingTraits > & b ) ;



// *** CONGRUENCE_RING ***


template < class RingTraits >
class congruence_ring

{
public:

  typedef typename RingTraits :: value_type value_type ;

private:

  value_type value ;

  void normalize ( )
    { normalize_congruence_ring_element ( value,
                                          RingTraits :: modulus ( ) ) ; }

public:

  congruence_ring ( ) :
    value ( 0 )
    { }

  congruence_ring ( const value_type & x ) :
    value ( x )
    { normalize ( ) ; }

  template < class S >
  congruence_ring
    ( const S & x,
      typename implicit_conversion_test < S, value_type > :: result =
        implicit_conversion_allowed ) :
    value ( x )
    { normalize ( ) ; }

  const value_type & base ( ) const
    { return value ; }

  const congruence_ring & operator + ( ) const
    { return * this ; }

  congruence_ring operator - ( ) const
    { return congruence_ring ( - value ) ; }

  friend congruence_ring operator + ( const congruence_ring & a,
                                      const congruence_ring & b )
    { return congruence_ring ( a.value + b.value ) ; }

  friend congruence_ring operator - ( const congruence_ring & a,
                                      const congruence_ring & b )
    { return congruence_ring ( a.value - b.value ) ; }

  friend congruence_ring operator * ( const congruence_ring & a,
                                      const congruence_ring & b )
    { return congruence_ring ( a.value * b.value ) ; }

  friend congruence_ring operator / ( const congruence_ring & a,
                                      const congruence_ring & b )
    { value_type x, y, gcd ;
      gcd_ext ( RingTraits :: modulus ( ), b.value, x, y, gcd ) ;
      assert ( gcd == value_type ( 1 ) ) ;
      return congruence_ring ( a.value * y ) ; }

  congruence_ring & operator ++ ( )
    { value += value_type ( 1 ) ;
      normalize ( ) ;
      return * this ; }

  congruence_ring operator ++ ( int )
    { congruence_ring t = * this ;
      ++ * this ;
      return t ; }

  congruence_ring & operator -- ( )
    { value -= value_type ( 1 ) ;
      normalize ( ) ;
      return * this ; }

  congruence_ring operator -- ( int )
    { congruence_ring t = * this ;
      -- * this ;
      return t ; }

  congruence_ring & operator += ( const congruence_ring & b )
    { value += b.value ;
      normalize ( ) ;
      return * this ; }

  congruence_ring & operator -= ( const congruence_ring & b )
    { value -= b.value ;
      normalize ( ) ;
      return * this ; }

  congruence_ring & operator *= ( const congruence_ring & b )
    { value *= b.value ;
      normalize ( ) ;
      return * this ; }

  congruence_ring & operator /= ( const congruence_ring & b )
    { return * this = * this / b ; }

  friend bool operator == ( const congruence_ring & a,
                            const congruence_ring & b )
    { return a.value == b.value ; }

  friend bool operator < ( const congruence_ring & a,
                           const congruence_ring & b )
    { return a.value < b.value ; }

  template < class CharT, class CharTraits >
  friend basic_ostream < CharT, CharTraits > &
    operator << ( basic_ostream < CharT, CharTraits > & o,
                  const congruence_ring & a )
    { return o << a.value ; }

  template < class CharT, class CharTraits >
  friend basic_istream < CharT, CharTraits > &
    operator >> ( basic_istream < CharT, CharTraits > & i,
                  congruence_ring & a )
    { i >> a.value ;
      a.normalize ( ) ;
      return i ; }

} ;



// *** Z_RING_TRAITS ***


template < sint Modulus >
class z_ring_traits

{
public:

  typedef sint value_type ;

  static value_type modulus ( )
    { return Modulus ; }

} ;



// *** IMPLICIT CONVERSION ***


//

template < class RingTraits >
class implicit_conversion_test < typename RingTraits :: value_type,
                                 congruence_ring < RingTraits > > :
  public implicit_conversion_test_ok

{
} ;


//

template < class S, class RingTraits >
class implicit_conversion_test < S, congruence_ring < RingTraits > > :
  public implicit_conversion_test < S, typename RingTraits :: value_type >

{
} ;



#endif
