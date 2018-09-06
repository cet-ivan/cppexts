// Copyright Ivan Stanojevic 2012.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __SPECFUN_H

#define __SPECFUN_H



#include "cassert.h"
#include "vector.h"
#include "utility.h"

#include "cfe.h"
#include "convtest.h"
#include "numbase.h"
#include "exint.h"
#include "fraction.h"



// !!! functions are not thread safe !!!



// *** STATIC_CACHED_ARRAY ***


// pre: n >= 0

template < class T, class U, U Function ( sint ) >
T static_cached_array ( sint n )

{
assert ( n >= 0 ) ;

static vector < T > data ;

while ( data.size ( ) <= n )
  data.push_back ( convert_to < T > ( Function ( data.size ( ) ) ) ) ;

return data [ n ] ;
}



// *** STIRLING_NUMBER_OF_1ST_KIND ***


// pre: n >= 0, 0 <= k <= n

exint stirling_number_of_1st_kind ( sint n, sint k ) ;


// pre: n >= 0, 0 <= k <= n

template < class T >
T stirling_number_of_1st_kind ( sint n, sint k )

{
assert ( n >= 0 ) ;
assert ( k >= 0 ) ;
assert ( k <= n ) ;

static vector < vector < T > > data ;

if ( data.size ( ) <= n )
  data.resize ( n + 1 ) ;

vector < T > & data_n = data [ n ] ;

while ( data_n.size ( ) <= k )
  data_n.push_back ( convert_to < T > ( stirling_number_of_1st_kind
                                          ( n, data_n.size ( ) ) ) ) ;

return data_n [ k ] ;
}



// *** BERNOULLI NUMBER ***


// pre: n >= 0

fraction < exint > bernoulli_number ( sint n ) ;


// pre: n >= 0

template < class T >
inline T bernoulli_number ( sint n )

{
return static_cached_array < T,
                             fraction < exint >,
                             bernoulli_number > ( n ) ;
}



// *** DAWSON_INTEGRAL ***


// pre: T is real floating point type

template < class T >
T dawson_integral ( const T & x )

{
continued_fraction_evaluator < T > cfe ;
convergence_tester < T > ct ( 3 ) ;

T b ( 2 * sqr ( x ) ) ;

cfe.step ( x, 1 + b ) ;

for ( sint k = 1 ; ; ++ k )
  {
  cfe.step ( - ( k << 1 ) * b, ( k << 1 ) + 1 + b ) ;
  if ( cfe.value_valid ( ) )
    {
    ct.insert ( cfe.value ( ) ) ;
    if ( ct.converged ( ) )
      return ct.value ( ) ;
    }
  }
}



// *** GAMMA_ASYMPTOTIC_SERIES_COEFFICIENT ***


// pre: n >= 0

fraction < exint > gamma_asymptotic_series_coefficient ( sint n ) ;


// pre: n >= 0

template < class T >
inline T gamma_asymptotic_series_coefficient ( sint n )

{
return static_cached_array < T,
                             fraction < exint >,
                             gamma_asymptotic_series_coefficient > ( n ) ;
}



// *** GAMMA_CONTINUED_FRACTION_COEFFICIENT ***


// pre: n >= 0

fraction < exint > gamma_continued_fraction_coefficient ( sint n ) ;


// pre: n >= 0

template < class T >
inline T gamma_continued_fraction_coefficient ( sint n )

{
return static_cached_array < T,
                             fraction < exint >,
                             gamma_continued_fraction_coefficient > ( n ) ;
}



// *** GAMMA_FAST_CONTINUED_FRACTION_COEFFICIENTS ***


// pre: n >= 0

inline void gamma_fast_continued_fraction_coefficients
              ( sint n, fraction < exint > & a, fraction < exint > & b )

{
assert ( n >= 0 ) ;

if ( n == 0 )
  {
  a = gamma_continued_fraction_coefficient ( 0 ) ;
  b = gamma_continued_fraction_coefficient ( 1 ) ;
  }
else
  {
  n <<= 1 ;
  a = - gamma_continued_fraction_coefficient ( n - 1 )
      * gamma_continued_fraction_coefficient ( n ) ;
  b =   gamma_continued_fraction_coefficient ( n )
      + gamma_continued_fraction_coefficient ( n + 1 ) ;
  }
}


// pre: n >= 0

template < class T >
void gamma_fast_continued_fraction_coefficients ( sint n, T & a, T & b )

{
assert ( n >= 0 ) ;

static vector < pair < T, T > > data ;

while ( data.size ( ) <= n )
  {
  fraction < exint > c, d ;
  gamma_fast_continued_fraction_coefficients ( n, c, d ) ;
  data.push_back ( pair < T, T > ( convert_to < T > ( c ),
                                   convert_to < T > ( d ) ) ) ;
  }

a = data [ n ].first ;
b = data [ n ].second ;
}



// *** GAMMA ***


// pre: T is real floating point type
//      x > 0

template < class T >
T gamma_positive ( T x )

{
assert ( x > 0 ) ;

T c ( 1 ) ;

while ( x < numeric_constants < T > :: gamma_cf_shift_limit ( ) )
  {
  c *= x ;
  x += 1 ;
  }

continued_fraction_evaluator < T > cfe ( 1 ) ;
convergence_tester < T > ct ( 3 ) ;

for ( sint k = 0 ; ; ++ k )
  {
  T a, b ;
  gamma_fast_continued_fraction_coefficients < T > ( k, a, b ) ;
  cfe.step ( a, x + b ) ;
  if ( cfe.value_valid ( ) )
    {
    ct.insert ( cfe.value ( ) ) ;
    if ( ct.converged ( ) )
      return   numeric_constants < T > :: sqrt_2pi ( )
             * exp ( ( x - 0.5 ) * log ( x ) - x )
             * ct.value ( ) / c ;
    }
  }
}


// pre: T is real floating point type

template < class T >
inline T gamma ( const T & x )

{
return   x >= 0.5
       ? gamma_positive ( x )
       :   numeric_constants < T > :: pi ( )
         / (   sin ( numeric_constants < T > :: pi ( ) * x )
             * gamma_positive ( 1 - x ) ) ;
}



// *** LOG_GAMMA_ASYMPTOTIC_SERIES_COEFFICIENT ***


// pre: n >= 0

inline fraction < exint > log_gamma_asymptotic_series_coefficient ( sint n )

{
assert ( n >= 0 ) ;
sint q = ( n << 1 ) + 2 ;
return bernoulli_number ( q ) / ( exint ( q - 1 ) * exint ( q ) ) ;
}


// pre: n >= 0

template < class T >
inline T log_gamma_asymptotic_series_coefficient ( sint n )

{
return static_cached_array < T,
                             fraction < exint >,
                             log_gamma_asymptotic_series_coefficient > ( n ) ;
}



// *** LOG_GAMMA_CONTINUED_FRACTION_COEFFICIENT ***


// pre: n >= 0

fraction < exint > log_gamma_continued_fraction_coefficient ( sint n ) ;


// pre: n >= 0

template < class T >
inline T log_gamma_continued_fraction_coefficient ( sint n )

{
return static_cached_array < T,
                             fraction < exint >,
                             log_gamma_continued_fraction_coefficient > ( n ) ;
}



// *** LOG_GAMMA ***


// pre: T is real floating point type
//      x > 0

template < class T >
T log_gamma_positive ( T x )

{
assert ( x > 0 ) ;

T c ( 1 ) ;

while ( x < numeric_constants < T > :: log_gamma_cf_shift_limit ( ) )
  {
  c *= x ;
  x += 1 ;
  }

continued_fraction_evaluator < T > cfe ;
convergence_tester < T > ct ( 3 ) ;

for ( sint k = 0 ; ; ++ k )
  {
  cfe.step ( log_gamma_continued_fraction_coefficient < T > ( k ), x ) ;
  if ( cfe.value_valid ( ) )
    {
    ct.insert ( cfe.value ( ) ) ;
    if ( ct.converged ( ) )
      return   ( x - 0.5 ) * log ( x ) - x
             + numeric_constants < T > :: log_2pi_2 ( )
             + ct.value ( ) - log ( c ) ;
    }
  }
}


// pre: T is real floating point type
//      gamma ( x ) > 0

template < class T >
inline T log_gamma ( const T & x )

{
return   x >= 0.5
       ? log_gamma_positive ( x )
       :   log (   numeric_constants < T > :: pi ( )
                 / sin ( numeric_constants < T > :: pi ( ) * x ) )
         - log_gamma_positive ( 1 - x ) ;
}



#endif
