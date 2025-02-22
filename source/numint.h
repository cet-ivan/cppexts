// Copyright Ivan Stanojevic 2025.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __NUMINT_H

#define __NUMINT_H



#include "utility.h"
#include "vector.h"

#include "numbase.h"



// *** CLOSED_ROMBERG_INTEGRAL ***


template < class F, class T >
decltype ( declval < F > ( ) ( declval < T > ( ) ) * declval < T > ( ) )
  closed_romberg_integral ( F f, const T & a, const T & b )

{
typedef decltype ( declval < F > ( ) ( declval < T > ( ) ) * declval < T > ( ) )
        result_type ;

T h = b - a ;
vector < result_type > current ( 1, ( f ( a ) + f ( b ) ) * h / 2 ) ;

for ( sint total_intervals = 1 ; ; total_intervals *= 2 )
  {
  vector < result_type > next ;
  next.reserve ( current.size ( ) + 1 ) ;

  {
  result_type s = 0 ;
  T step_2 = h / ( 2 * total_intervals ) ;

  for ( sint k = 0 ; k < total_intervals ; ++ k )
    s += f ( a + ( 2 * k + 1 ) * step_2 ) ;

  next.push_back ( current.front ( ) / 2 + s * step_2 ) ;
  }

  {
  T correction_factor = 4 ;

  for ( const result_type & c : current )
    {
    next.push_back (   next.back ( )
                     + ( next.back ( ) - c ) / ( correction_factor - 1 ) ) ;

    correction_factor *= 4 ;
    }
  }

  if ( next.back ( ) == * ( next.end ( ) - 2 ) )
    return next.back ( ) ;

  current = move ( next ) ;
  }
}



// *** OPEN_ROMBERG_INTEGRAL ***


template < class F, class T >
decltype ( declval < F > ( ) ( declval < T > ( ) ) * declval < T > ( ) )
  open_romberg_integral ( F f, const T & a, const T & b )

{
typedef decltype ( declval < F > ( ) ( declval < T > ( ) ) * declval < T > ( ) )
        result_type ;

T h = b - a ;
vector < result_type > current ( 1, f ( ( a + b ) / 2 ) * h ) ;

for ( sint total_intervals = 1 ; ; total_intervals *= 3 )
  {
  vector < result_type > next ;
  next.reserve ( current.size ( ) + 1 ) ;

  {
  result_type s = 0 ;

  T step_3 = h / ( 3 * total_intervals ),
    step_6 = step_3 / 2 ;

  for ( sint k = 0 ; k < total_intervals ; ++ k )
    s +=   f ( a + ( 6 * k + 1 ) * step_6 )
         + f ( a + ( 6 * k + 5 ) * step_6 ) ;

  next.push_back ( current.front ( ) / 3 + s * step_3 ) ;
  }

  {
  T correction_factor = 9 ;

  for ( const result_type & c : current )
    {
    next.push_back (   next.back ( )
                     + ( next.back ( ) - c ) / ( correction_factor - 1 ) ) ;

    correction_factor *= 9 ;
    }
  }

  if ( next.back ( ) == * ( next.end ( ) - 2 ) )
    return next.back ( ) ;

  current = move ( next ) ;
  }
}



#endif
