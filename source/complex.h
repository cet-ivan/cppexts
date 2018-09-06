// Copyright Ivan Stanojevic 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __COMPLEX_H

#define __COMPLEX_H



#include "cmath.h"
#include "utility.h"

#include "numbase.h"
#include "typeconv.h"
#include "streaming.h"



// *** FORWARD DECLARATIONS ***


template < class T >
class __complex_base ;

template < class T >
class complex ;

template < class T >
complex < T > operator + ( const __complex_base < T > & a,
                           const __complex_base < T > & b ) ;

template < class T >
complex < T > operator + ( const complex < T > & a, const T & b ) ;

template < class T >
complex < T > operator + ( const T & a, const complex < T > & b ) ;

template < class T >
complex < T > operator - ( const __complex_base < T > & a,
                           const __complex_base < T > & b ) ;

template < class T >
complex < T > operator - ( const complex < T > & a, const T & b ) ;

template < class T >
complex < T > operator - ( const T & a, const complex < T > & b ) ;

template < class T >
complex < T > operator * ( const __complex_base < T > & a,
                           const __complex_base < T > & b ) ;

template < class T >
complex < T > operator * ( const complex < T > & a, const T & b ) ;

template < class T >
complex < T > operator * ( const T & a, const complex < T > & b ) ;

template < class T >
complex < T > operator / ( const __complex_base < T > & a,
                           const __complex_base < T > & b ) ;

template < class T >
complex < T > operator / ( const complex < T > & a, const T & b ) ;

template < class T >
complex < T > operator / ( const T & a, const complex < T > & b ) ;

template < class T >
bool operator == ( const __complex_base < T > & a,
                   const __complex_base < T > & b ) ;

template < class T >
bool operator == ( const complex < T > & a, const T & b ) ;

template < class T >
bool operator == ( const T & a, const complex < T > & b ) ;

template < class T >
complex < T > pow ( const __complex_base < T > & z,
                    const __complex_base < T > & e ) ;

template < class T >
complex < T > pow ( const complex < T > & z, const T & e ) ;

template < class T >
complex < T > pow ( const T & x, const complex < T > & e ) ;



// *** __COMPLEX_BASE ***


template < class T >
class __complex_base

{
private:

  friend class complex < T > ;

  __complex_base ( ) = default ;
  ~__complex_base ( ) = default ;
  __complex_base ( const __complex_base & ) = default ;
  __complex_base ( __complex_base && ) = default ;
  __complex_base & operator = ( const __complex_base & ) = default ;
  __complex_base & operator = ( __complex_base && ) = default ;

} ;



// *** COMPLEX ***


template < class T >
class complex : public __complex_base < T >

{
public:

  typedef T value_type ;

  T real,
    imag ;

  complex ( ) :
    real ( 0 ),
    imag ( 0 )
    { }

  complex ( const T & i_real ) :
    real ( i_real ),
    imag ( 0 )
    { }

  complex ( const T & i_real, const T & i_imag ) :
    real ( i_real ),
    imag ( i_imag )
    { }

  template < class X >
  complex ( const complex < X > & z ) :
    real ( z.real ),
    imag ( z.imag )
    { }

  template < class S >
  complex ( const S & x,
            typename implicit_conversion_test < S, T > :: result =
              implicit_conversion_allowed ) :
    real ( x ),
    imag ( 0 )
    { }

  const complex & operator + ( ) const
    { return * this ; }

  complex operator - ( ) const
    { return complex ( - real, - imag ) ; }

  friend complex operator + ( const __complex_base < T > & a,
                              const __complex_base < T > & b )
    { const complex & ar = static_cast < const complex & > ( a ),
                    & br = static_cast < const complex & > ( b ) ;
      return complex ( ar.real + br.real, ar.imag + br.imag ) ; }

  friend complex operator + ( const complex & a, const T & b )
    { return complex ( a.real + b, a.imag ) ; }

  friend complex operator + ( const T & a, const complex & b )
    { return complex ( a + b.real, b.imag ) ; }

  friend complex operator - ( const __complex_base < T > & a,
                              const __complex_base < T > & b )
    { const complex & ar = static_cast < const complex & > ( a ),
                    & br = static_cast < const complex & > ( b ) ;
      return complex ( ar.real - br.real, ar.imag - br.imag ) ; }

  friend complex operator - ( const complex & a, const T & b )
    { return complex ( a.real - b, a.imag ) ; }

  friend complex operator - ( const T & a, const complex & b )
    { return complex ( a - b.real, - b.imag ) ; }

  friend complex operator * ( const __complex_base < T > & a,
                              const __complex_base < T > & b )
    { const complex & ar = static_cast < const complex & > ( a ),
                    & br = static_cast < const complex & > ( b ) ;
      return complex ( ar.real * br.real - ar.imag * br.imag,
                       ar.imag * br.real + ar.real * br.imag ) ; }

  friend complex operator * ( const complex & a, const T & b )
    { return complex ( a.real * b, a.imag * b ) ; }

  friend complex operator * ( const T & a, const complex & b )
    { return complex ( a * b.real, a * b.imag ) ; }

  friend complex operator / ( const __complex_base < T > & a,
                              const __complex_base < T > & b )
    { const complex & ar = static_cast < const complex & > ( a ),
                    & br = static_cast < const complex & > ( b ) ;
      T n ( norm ( br ) ) ;
      return complex ( ( ar.real * br.real + ar.imag * br.imag ) / n,
                       ( ar.imag * br.real - ar.real * br.imag ) / n ) ; }

  friend complex operator / ( const complex & a, const T & b )
    { return complex ( a.real / b, a.imag / b ) ; }

  friend complex operator / ( const T & a, const complex & b )
    { T n ( norm ( b ) ) ;
      return complex ( a * b.real / n, - a * b.imag / n ) ; }

  complex & operator = ( const T & x )
    { real = x ;
      imag = 0 ;
      return * this ; }

  complex & operator += ( const T & x )
    { real += x ;
      return * this ; }

  complex & operator -= ( const T & x )
    { real -= x ;
      return * this ; }

  complex & operator *= ( const T & x )
    { real *= x ;
      imag *= x ;
      return * this ; }

  complex & operator /= ( const T & x )
    { real /= x ;
      imag /= x ;
      return * this ; }

  template < class X >
  complex & operator = ( const complex < X > & z )
    { real = z.real ;
      imag = z.imag ;
      return * this ; }

  template < class X >
  complex & operator += ( const complex < X > & z )
    { real += z.real ;
      imag += z.imag ;
      return * this ; }

  template < class X >
  complex & operator -= ( const complex < X > & z )
    { real -= z.real ;
      imag -= z.imag ;
      return * this ; }

  template < class X >
  complex & operator *= ( const complex < X > & z )
    { T new_imag = imag * z.real + real * z.imag ;
      real = real * z.real - imag * z.imag ;
      imag = new_imag ;
      return * this ; }

  template < class X >
  complex & operator /= ( const complex < X > & z )
    { T n = norm ( z ),
        new_imag = ( imag * z.real - real * z.imag ) / n ;
      real = ( real * z.real + imag * z.imag ) / n ;
      imag = new_imag ;
      return * this ; }

  friend bool operator == ( const __complex_base < T > & a,
                            const __complex_base < T > & b )
    { const complex & ar = static_cast < const complex & > ( a ),
                    & br = static_cast < const complex & > ( b ) ;
      return ar.real == br.real  &&  ar.imag == br.imag ; }

  friend bool operator == ( const complex & a, const T & b )
    { return a.real == b  &&  a.imag == T ( 0 ) ; }

  friend bool operator == ( const T & a, const complex & b )
    { return a == b.real  &&  T ( 0 ) == b.imag ; }

  friend complex pow ( const __complex_base < T > & z,
                       const __complex_base < T > & e )
    { const complex & zr = static_cast < const complex & > ( z ),
                    & er = static_cast < const complex & > ( e ) ;
      if ( er == complex ( ) )
        return complex ( T ( 1 ) ) ;
      if ( zr == complex ( ) )
        return complex ( ) ;
      return exp ( er * log ( zr ) ) ; }

  friend complex pow ( const complex & z, const T & e )
    { if ( e == T ( 0 ) )
        return complex ( T ( 1 ) ) ;
      if ( z == complex ( ) )
        return complex ( ) ;
      return exp ( e * log ( z ) ) ; }

  friend complex pow ( const T & x, const complex & e )
    { return pow ( complex ( x ), e ) ; }

  template < class CharT, class CharTraits >
  friend basic_ostream < CharT, CharTraits > &
    operator << ( basic_ostream < CharT, CharTraits > & o,
                  const complex & z )
    { return output_pair ( o, z.real, z.imag ) ; }

  template < class CharT, class CharTraits >
  friend basic_istream < CharT, CharTraits > &
    operator >> ( basic_istream < CharT, CharTraits > & i,
                  complex & z )
    { return input_pair ( i, z.real, z.imag ) ; }

} ;


//

template < class T >
inline const T & real ( const complex < T > & z )

{
return z.real ;
}


//

template < class T >
inline const T & imag ( const complex < T > & z )

{
return z.imag ;
}


//

template < class T >
inline T norm ( const complex < T > & z )

{
return sqr ( z.real ) + sqr ( z.imag ) ;
}


//

template < class T >
inline T abs ( const complex < T > & z )

{
return sqrt ( norm ( z ) ) ;
}


//

template < class T >
inline T arg ( const complex < T > & z )

{
return atan2 ( z.imag, z.real ) ;
}


//

template < class T >
inline complex < T > conj ( const complex < T > & z )

{
return complex < T > ( z.real, - z.imag ) ;
}


//

template < class T >
inline complex < T > polar ( const T & rho, const T & theta )

{
return complex < T > ( rho * cos ( theta ), rho * sin ( theta ) ) ;
}


//

template < class T >
inline complex < T > sqrt ( const complex < T > & z )

{
T m ( abs ( z ) ) ;

complex < T > result ( sqrt ( ( m + z.real ) / 2 ),
                       sqrt ( ( m - z.real ) / 2 ) ) ;

if ( ( z.imag ) < T ( 0 ) )
  result.imag = - result.imag ;

return result ;
}


//

template < class T >
inline complex < T > exp ( const complex < T > & z )

{
return polar ( exp ( z.real ), z.imag ) ;
}


//

template < class T >
inline complex < T > log ( const complex < T > & z )

{
return complex < T > ( log ( norm ( z ) ) / 2, arg ( z ) ) ;
}


//

template < class T >
inline complex < T > log2 ( const complex < T > & z )

{
return log ( z ) * numeric_constants < T > :: log2e ( ) ;
}


//

template < class T >
inline complex < T > log10 ( const complex < T > & z )

{
return log ( z ) * numeric_constants < T > :: log10e ( ) ;
}


//

template < class T >
inline complex < T > sinh ( const complex < T > & z )

{
complex < T > u ( exp ( z ) ),
              v ( T ( 1 ) / u ) ;

return ( u - v ) / T ( 2 ) ;
}


//

template < class T >
inline complex < T > cosh ( const complex < T > & z )

{
complex < T > u ( exp ( z ) ),
              v ( T ( 1 ) / u ) ;

return ( u + v ) / T ( 2 ) ;
}


//

template < class T >
inline complex < T > tanh ( const complex < T > & z )

{
complex < T > u ( exp ( z ) ),
              v ( T ( 1 ) / u ) ;

return ( u - v ) / ( u + v ) ;
}


//

template < class T >
inline complex < T > sin ( const complex < T > & z )

{
complex < T > t ( sinh ( complex < T > ( - z.imag, z.real ) ) ) ;
return complex < T > ( t.imag, - t.real ) ;
}


//

template < class T >
inline complex < T > cos ( const complex < T > & z )

{
return cosh ( complex < T > ( - z.imag, z.real ) ) ;
}


//

template < class T >
inline complex < T > tan ( const complex < T > & z )

{
complex < T > t ( tanh ( complex < T > ( - z.imag, z.real ) ) ) ;
return complex < T > ( t.imag, - t.real ) ;
}



// *** COMPLEX_TRAITS ***


//

template < class T >
class complex_traits

{
public:

  typedef T real_type ;
  typedef complex < T > complex_type ;

} ;


//

template < class T >
class complex_traits < complex < T > >

{
public:

  typedef T real_type ;
  typedef complex < T > complex_type ;

} ;



// *** PIVOTING_COMPARE ***


template < class T >
class pivoting_compare < complex < T > >

{
public:

  bool operator ( ) ( const complex < T > & a, const complex < T > & b )
    { return norm ( a ) < norm ( b ) ; }

} ;



// *** IMPLICIT CONVERSION ***


//

template < class T >
class implicit_conversion_test < T, complex < T > > :
  public implicit_conversion_test_ok

{
} ;


//

template < class X, class T >
class implicit_conversion_test < complex < X >, complex < T > > :
  public implicit_conversion_test_ok

{
} ;


//

template < class S, class T >
class implicit_conversion_test < S, complex < T > > :
  public implicit_conversion_test < S, T >

{
} ;



#endif
