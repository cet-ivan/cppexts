// Copyright Ivan Stanojevic 2025.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __SPECFUN_H

#define __SPECFUN_H



#include "cmath.h"
#include "cassert.h"
#include "vector.h"
#include "mutex.h"
#include "utility.h"

#include "cfe.h"
#include "convtest.h"
#include "numbase.h"
#include "exint.h"
#include "fraction.h"



// *** LOG OPERATIONS ***


// pre: T is real floating point type
// returns: log ( exp ( a ) + exp ( b ) )

template < class T >
inline T log_add ( const T & a, const T & b )

{
return a > b ? a + log ( 1 + exp ( b - a ) ) : b + log ( 1 + exp ( a - b ) ) ;
}


// pre: T is real floating point type
//      a > b
// returns: log ( exp ( a ) - exp ( b ) )

template < class T >
inline T log_sub ( const T & a, const T & b )

{
assert ( a > b ) ;
return a + log ( 1 - exp ( b - a ) ) ;
}



// *** STATIC_CACHED_ARRAY ***


// pre: n >= 0

template < class T, class U, U Function ( sint ) >
T static_cached_array ( sint n )

{
assert ( n >= 0 ) ;

#ifdef __STDCPP_THREADS__

static mutex mtx ;
lock_guard < mutex > lck ( mtx ) ;

#endif

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
assert ( k >= 0  &&  k <= n ) ;

#ifdef __STDCPP_THREADS__

static mutex mtx ;
lock_guard < mutex > lck ( mtx ) ;

#endif

static vector < vector < T > > data ;

if ( data.size ( ) <= n )
  data.resize ( n + 1 ) ;

vector < T > & data_n = data [ n ] ;

while ( data_n.size ( ) <= k )
  data_n.push_back ( convert_to < T > ( stirling_number_of_1st_kind
                                          ( n, data_n.size ( ) ) ) ) ;

return data_n [ k ] ;
}



// *** BERNOULLI_NUMBER ***


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

#ifdef __STDCPP_THREADS__

static mutex mtx ;
lock_guard < mutex > lck ( mtx ) ;

#endif

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
             * exp ( ( x - T ( 1 ) / 2 ) * log ( x ) - x )
             * ct.value ( ) / c ;
    }
  }
}


// pre: T is real floating point type

template < class T >
inline T gamma ( const T & x )

{
return   x >= T ( 1 ) / 2
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
      return   ( x - T ( 1 ) / 2 ) * log ( x ) - x
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
return   x >= T ( 1 ) / 2
       ? log_gamma_positive ( x )
       :   log (   numeric_constants < T > :: pi ( )
                 / sin ( numeric_constants < T > :: pi ( ) * x ) )
         - log_gamma_positive ( 1 - x ) ;
}



// *** INCOMPLETE_GAMMA_AUX ***


// pre: T is real floating point type
//      a > 0

template < class T >
T incomplete_gamma_head_series_aux ( const T & a, const T & x )

{
assert ( a > 0 ) ;

T y = 1 / a,
  s = y ;

for ( sint n = 1 ; ; ++ n )
  {
  y *= x / ( a + n ) ;

  T t = s ;
  s += y ;

  if ( s == t )
    return s ;
  }
}


// pre: T is real floating point type
//      a > 0

template < class T >
T incomplete_gamma_tail_continued_fraction_aux ( const T & a, const T & x )

{
assert ( a > 0 ) ;

continued_fraction_evaluator < T > cfe ;
cfe.step ( 1, x + 1 - a ) ;

convergence_tester < T > ct ( 3 ) ;
ct.insert ( cfe.value ( ) ) ;

for ( sint n = 1 ; ; ++ n )
  {
  cfe.step ( n * ( a - n ), x + ( ( n << 1 ) + 1 ) - a ) ;
  ct.insert ( cfe.value ( ) ) ;

  if ( ct.converged ( ) )
    return ct.value ( ) ;
  }
}



// *** INCOMPLETE_GAMMA ***


// pre: T is real floating point type
//      a > 0
//      x >= 0

template < class T >
inline T incomplete_gamma_head ( const T & a, const T & x )

{
assert ( a > 0 ) ;
assert ( x >= 0 ) ;

if ( x == 0 )
  return 0 ;

T c = exp ( a * log ( x ) - x ) ;

return
    x < a + 1
  ? c * incomplete_gamma_head_series_aux ( a, x )
  : gamma ( a ) - c * incomplete_gamma_tail_continued_fraction_aux ( a, x ) ;
}


// pre: T is real floating point type
//      a > 0
//      x >= 0

template < class T >
inline T incomplete_gamma_tail ( const T & a, const T & x )

{
assert ( a > 0 ) ;
assert ( x >= 0 ) ;

if ( x == 0 )
  return gamma ( a ) ;

T c = exp ( a * log ( x ) - x ) ;

return   x < a + 1
       ? gamma ( a ) - c * incomplete_gamma_head_series_aux ( a, x )
       : c * incomplete_gamma_tail_continued_fraction_aux ( a, x ) ;
}



// *** LOG_INCOMPLETE_GAMMA ***


// pre: T is real floating point type
//      a > 0
//      x > 0

template < class T >
inline T log_incomplete_gamma_head ( const T & a, const T & x )

{
assert ( a > 0 ) ;
assert ( x > 0 ) ;

T c = a * log ( x ) - x ;

return
    x < a + 1
  ? c + log ( incomplete_gamma_head_series_aux ( a, x ) )
  : log_sub
      ( log_gamma ( a ),
        c + log ( incomplete_gamma_tail_continued_fraction_aux ( a, x ) ) ) ;
}


// pre: T is real floating point type
//      a > 0
//      x >= 0

template < class T >
inline T log_incomplete_gamma_tail ( const T & a, const T & x )

{
assert ( a > 0 ) ;
assert ( x >= 0 ) ;

if ( x == 0 )
  return log_gamma ( a ) ;

T c = a * log ( x ) - x ;

return   x < a + 1
       ? log_sub ( log_gamma ( a ),
                   c + log ( incomplete_gamma_head_series_aux ( a, x ) ) )
       : c + log ( incomplete_gamma_tail_continued_fraction_aux ( a, x ) ) ;
}



// *** GAUSS_CCDF ***


// pre: T is real floating point type

template < class T >
inline T gauss_ccdf ( const T & x )

{
T r =   numeric_constants < T > :: _1_2_sqrt_pi ( )
      * incomplete_gamma_tail ( T ( 1 ) / 2, sqr ( x ) / 2 ) ;

return x >= 0 ? r : 1 - r ;
}



// *** LOG_BETA ***


// pre: T is real floating point type
//      a > 0
//      b > 0

template < class T >
inline T log_beta ( const T & a, const T & b )

{
assert ( a > 0 ) ;
assert ( b > 0 ) ;

return log_gamma ( a ) + log_gamma ( b ) - log_gamma ( a + b ) ;
}



// *** BETA ***


// pre: T is real floating point type
//      a > 0
//      b > 0

template < class T >
inline T beta ( const T & a, const T & b )

{
assert ( a > 0 ) ;
assert ( b > 0 ) ;

return exp ( log_beta ( a, b ) ) ;
}



// *** INCOMPLETE_BETA_AUX ***


// pre: T is real floating point type
//      a > 0
//      b > 0
//      0 <= x <= 1

template < class T >
T incomplete_beta_continued_fraction_aux
    ( const T & a, const T & b, const T & x )

{
assert ( a > 0 ) ;
assert ( b > 0 ) ;
assert ( x >= 0  &&  x <= 1 ) ;

continued_fraction_evaluator < T > cfe ;
cfe.step ( 1, 1 ) ;

convergence_tester < T > ct ( 3 ) ;
ct.insert ( cfe.value ( ) ) ;

sint m = 0 ;

do
  {
  cfe.step ( - ( a + m ) * ( a + b + m ) * x
             / ( ( a + ( m << 1 ) ) * ( a + ( ( m << 1 ) + 1 ) ) ),
             1 ) ;

  ++ m ;

  cfe.step (   m * ( b - m ) * x
             / ( ( a + ( ( m << 1 ) - 1 ) ) * ( a + ( m << 1 ) ) ),
             1 ) ;

  ct.insert ( cfe.value ( ) ) ;
  }
while ( ! ct.converged ( ) ) ;

return ct.value ( ) ;
}



// *** INCOMPLETE_BETA ***


// pre: T is real floating point type
//      a > 0
//      b > 0
//      0 <= x <= 1

template < class T >
inline T incomplete_beta ( const T & a, const T & b, const T & x )

{
assert ( a > 0 ) ;
assert ( b > 0 ) ;
assert ( x >= 0  &&  x <= 1 ) ;

if ( x == 0 )
  return 0 ;

if ( x == 1 )
  return beta ( a, b ) ;

T c = exp ( a * log ( x ) + b * log ( 1 - x ) ) ;

return   x * ( a + b + 2 ) < a + 1
       ? c * incomplete_beta_continued_fraction_aux ( a, b, x ) / a
       :   beta ( a, b )
         - c * incomplete_beta_continued_fraction_aux ( b, a, 1 - x ) / b ;
}



// *** LOG_INCOMPLETE_BETA ***


// pre: T is real floating point type
//      a > 0
//      b > 0
//      0 < x <= 1

template < class T >
inline T log_incomplete_beta ( const T & a, const T & b, const T & x )

{
assert ( a > 0 ) ;
assert ( b > 0 ) ;
assert ( x > 0  &&  x <= 1 ) ;

if ( x == 1 )
  return log_beta ( a, b ) ;

T c = a * log ( x ) + b * log ( 1 - x ) ;

return   x * ( a + b + 2 ) < a + 1
       ? c + log ( incomplete_beta_continued_fraction_aux ( a, b, x ) / a )
       : log_sub
           ( log_beta ( a, b ),
             c + log (   incomplete_beta_continued_fraction_aux ( b, a, 1 - x )
                       / b ) ) ;
}



#endif
