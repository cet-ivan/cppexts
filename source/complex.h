// Copyright Ivan Stanojevic 2021.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __COMPLEX_H

#define __COMPLEX_H



#include "cmath.h"
#include "utility.h"
#include "algorithm.h"

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

  T re, im ;

  complex ( ) :
    re ( 0 ),
    im ( 0 )
    { }

  complex ( const T & i_re ) :
    re ( i_re ),
    im ( 0 )
    { }

  complex ( const T & i_re, const T & i_im ) :
    re ( i_re ),
    im ( i_im )
    { }

  template < class S >
  complex ( const S & x,
            typename implicit_conversion_test < S, T > :: result =
              implicit_conversion_allowed ) :
    re ( x ),
    im ( 0 )
    { }

  template < class S >
  complex ( const complex < S > & z,
            typename implicit_conversion_test < S, T > :: result =
              implicit_conversion_allowed ) :
    re ( z.re ),
    im ( z.im )
    { }

  T real ( ) const
    { return re ; }

  void real ( const T & x )
    { re = x ; }

  T imag ( ) const
    { return im ; }

  void imag ( const T & x )
    { im = x ; }

  const complex & operator + ( ) const
    { return * this ; }

  complex operator - ( ) const
    { return complex ( - re, - im ) ; }

  friend complex operator + ( const __complex_base < T > & a,
                              const __complex_base < T > & b )
    { const complex & ar = static_cast < const complex & > ( a ),
                    & br = static_cast < const complex & > ( b ) ;
      return complex ( ar.re + br.re, ar.im + br.im ) ; }

  friend complex operator + ( const complex & a, const T & b )
    { return complex ( a.re + b, a.im ) ; }

  friend complex operator + ( const T & a, const complex & b )
    { return complex ( a + b.re, b.im ) ; }

  friend complex operator - ( const __complex_base < T > & a,
                              const __complex_base < T > & b )
    { const complex & ar = static_cast < const complex & > ( a ),
                    & br = static_cast < const complex & > ( b ) ;
      return complex ( ar.re - br.re, ar.im - br.im ) ; }

  friend complex operator - ( const complex & a, const T & b )
    { return complex ( a.re - b, a.im ) ; }

  friend complex operator - ( const T & a, const complex & b )
    { return complex ( a - b.re, - b.im ) ; }

  friend complex operator * ( const __complex_base < T > & a,
                              const __complex_base < T > & b )
    { const complex & ar = static_cast < const complex & > ( a ),
                    & br = static_cast < const complex & > ( b ) ;
      return complex ( ar.re * br.re - ar.im * br.im,
                       ar.im * br.re + ar.re * br.im ) ; }

  friend complex operator * ( const complex & a, const T & b )
    { return complex ( a.re * b, a.im * b ) ; }

  friend complex operator * ( const T & a, const complex & b )
    { return complex ( a * b.re, a * b.im ) ; }

  friend complex operator / ( const __complex_base < T > & a,
                              const __complex_base < T > & b )
    { const complex & ar = static_cast < const complex & > ( a ),
                    & br = static_cast < const complex & > ( b ) ;
      T n ( norm ( br ) ) ;
      return complex ( ( ar.re * br.re + ar.im * br.im ) / n,
                       ( ar.im * br.re - ar.re * br.im ) / n ) ; }

  friend complex operator / ( const complex & a, const T & b )
    { return complex ( a.re / b, a.im / b ) ; }

  friend complex operator / ( const T & a, const complex & b )
    { T n ( norm ( b ) ) ;
      return complex ( a * b.re / n, - a * b.im / n ) ; }

  complex & operator = ( const T & x )
    { re = x ;
      im = 0 ;
      return * this ; }

  complex & operator += ( const T & x )
    { re += x ;
      return * this ; }

  complex & operator -= ( const T & x )
    { re -= x ;
      return * this ; }

  complex & operator *= ( const T & x )
    { re *= x ;
      im *= x ;
      return * this ; }

  complex & operator /= ( const T & x )
    { re /= x ;
      im /= x ;
      return * this ; }

  template < class X >
  complex & operator = ( const complex < X > & z )
    { re = z.re ;
      im = z.im ;
      return * this ; }

  template < class X >
  complex & operator += ( const complex < X > & z )
    { re += z.re ;
      im += z.im ;
      return * this ; }

  template < class X >
  complex & operator -= ( const complex < X > & z )
    { re -= z.re ;
      im -= z.im ;
      return * this ; }

  template < class X >
  complex & operator *= ( const complex < X > & z )
    { T new_im = im * z.re + re * z.im ;
      re = re * z.re - im * z.im ;
      im = new_im ;
      return * this ; }

  template < class X >
  complex & operator /= ( const complex < X > & z )
    { T n = norm ( z ),
        new_im = ( im * z.re - re * z.im ) / n ;
      re = ( re * z.re + im * z.im ) / n ;
      im = new_im ;
      return * this ; }

  friend bool operator == ( const __complex_base < T > & a,
                            const __complex_base < T > & b )
    { const complex & ar = static_cast < const complex & > ( a ),
                    & br = static_cast < const complex & > ( b ) ;
      return ar.re == br.re  &&  ar.im == br.im ; }

  friend bool operator == ( const complex & a, const T & b )
    { return a.re == b  &&  a.im == T ( 0 ) ; }

  friend bool operator == ( const T & a, const complex & b )
    { return a == b.re  &&  T ( 0 ) == b.im ; }

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
    { return output_pair ( o, z.re, z.im ) ; }

  template < class CharT, class CharTraits >
  friend basic_istream < CharT, CharTraits > &
    operator >> ( basic_istream < CharT, CharTraits > & i,
                  complex & z )
    { return input_pair ( i, z.re, z.im ) ; }

} ;


//

template < class T >
inline const T & real ( const complex < T > & z )

{
return z.re ;
}


//

template < class T >
inline const T & imag ( const complex < T > & z )

{
return z.im ;
}


//

template < class T >
inline T norm ( const complex < T > & z )

{
return sqr ( z.re ) + sqr ( z.im ) ;
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
return atan2 ( z.im, z.re ) ;
}


//

template < class T >
inline complex < T > conj ( const complex < T > & z )

{
return complex < T > ( z.re, - z.im ) ;
}


//

template < class T >
inline complex < T > polar ( const T & rho, const T & theta )

{
return complex < T > ( rho * cos ( theta ), rho * sin ( theta ) ) ;
}


//

template < class T >
inline complex < T > unit_polar ( const T & theta )

{
return complex < T > ( cos ( theta ), sin ( theta ) ) ;
}


//

template < class T >
inline complex < T > sqrt ( const complex < T > & z )

{
T m ( abs ( z ) ) ;

complex < T > result ( sqrt ( ( m + z.re ) / 2 ),
                       sqrt ( ( m - z.re ) / 2 ) ) ;

if ( z.im < T ( 0 ) )
  result.im = - result.im ;

return result ;
}


//

template < class T >
inline complex < T > exp ( const complex < T > & z )

{
return polar ( exp ( z.re ), z.im ) ;
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
complex < T > t ( sinh ( complex < T > ( - z.im, z.re ) ) ) ;
return complex < T > ( t.im, - t.re ) ;
}


//

template < class T >
inline complex < T > cos ( const complex < T > & z )

{
return cosh ( complex < T > ( - z.im, z.re ) ) ;
}


//

template < class T >
inline complex < T > tan ( const complex < T > & z )

{
complex < T > t ( tanh ( complex < T > ( - z.im, z.re ) ) ) ;
return complex < T > ( t.im, - t.re ) ;
}


//

template < class T >
inline complex < T > inner_product_multiply ( const complex < T > & a,
                                              const complex < T > & b )

{
return conj ( a ) * b ;
}


//

template < class T >
inline T l1_norm ( const complex < T > & z )

{
return abs ( z.re ) + abs ( z.im ) ;
}


//

template < class T >
inline T sqr_l2_norm ( const complex < T > & z )

{
return norm ( z ) ;
}


//

template < class T >
inline T linf_norm ( const complex < T > & z )

{
return max ( abs ( z.re ), abs ( z.im ) ) ;
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

template < class S, class T >
class implicit_conversion_test < S, complex < T > > :
  public implicit_conversion_test < S, T >

{
} ;


//

template < class S, class T >
class implicit_conversion_test < complex < S >, complex < T > > :
  public implicit_conversion_test < S, T >

{
} ;



#endif
