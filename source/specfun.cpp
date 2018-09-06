// Copyright Ivan Stanojevic 2010.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#include "specfun.h"

#include "qde.h"



// *** STIRLING_NUMBER_OF_1ST_KIND ***


// pre: n >= 0, 0 <= k <= n

exint stirling_number_of_1st_kind ( sint n, sint k )

{
assert ( n >= 0 ) ;
assert ( k >= 0 ) ;
assert ( k <= n ) ;

static vector < vector < exint > > data ( 1, vector < exint > ( 1, 1 ) ) ;

while ( data.size ( ) <= n )
  {
  data.push_back ( vector < exint > ( ) ) ;

  const vector < exint > & dn_1 = * ( data.end ( ) - 2 ) ;
  vector < exint > & dn = * ( data.end ( ) - 1 ) ;

  dn.reserve ( data.size ( ) ) ;

  dn.push_back ( exint ( ) ) ;

  sint s = data.size ( ) - 2 ;
  exint t ( s ) ;

  for ( sint i = 0 ; i < s ; ++ i )
    dn.push_back ( dn_1 [ i ] - t * dn_1 [ i + 1 ] ) ;

  dn.push_back ( exint ( 1 ) ) ;
  }

return data [ n ] [ k ] ;
}



// *** BERNOULLI NUMBER ***


// pre: n >= 0

fraction < exint > bernoulli_number ( sint n )

{
class local_data : public vector < fraction < exint > >

{
public:

  local_data ( )
    { push_back ( 1 ) ;
      push_back ( fraction < exint > ( -1, 2 ) ) ;
      push_back ( fraction < exint > ( 1, 6 ) ) ; }

} ;

assert ( n >= 0 ) ;

static local_data data ;

while ( data.size ( ) <= n )
  if ( ( data.size ( ) & 1 ) != 0 )
    data.push_back ( 0 ) ;
  else
    {
    fraction < exint > s ;
    exint f ( 1 ) ;

    for ( sint i = 0 ; i < data.size ( ) ; ++ i )
      {
      s += f * data [ i ] ;
      f *= data.size ( ) + 1 - i ;
      f /= i + 1 ;
      }

    data.push_back ( - s / ( data.size ( ) + 1 ) ) ;
    }

return data [ n ] ;
}



// *** GAMMA_ASYMPTOTIC_SERIES_COEFFICIENT ***


// pre: n >= 0

fraction < exint > gamma_asymptotic_series_coefficient ( sint n )

{
assert ( n >= 0 ) ;

static vector < fraction < exint > > data ( 2, 1 ) ;

while ( data.size ( ) <= ( n << 1 ) + 1 )
  {
  fraction < exint > t ( data.back ( ) ) ;

  for ( sint i = 2 ; i < data.size ( ) ; ++ i )
    t -= i * data [ i ] * data [ data.size ( ) + 1 - i ] ;

  data.push_back ( t / ( data.size ( ) + 1 ) ) ;
  }

static exint factor ( 1 ) ;
static vector < fraction < exint > > scaled_data ;

while ( scaled_data.size ( ) <= n )
  {
  sint i = ( scaled_data.size ( ) << 1 ) + 1 ;
  factor *= i ;
  scaled_data.push_back ( factor * data [ i ] ) ;
  }

return scaled_data [ n ] ;
}



// *** GAMMA_CONTINUED_FRACTION_COEFFICIENT ***


// pre: n >= 0

fraction < exint > gamma_continued_fraction_coefficient ( sint n )

{
assert ( n >= 0 ) ;

static quotient_difference_evaluator < fraction < exint > > qde ;

while ( qde.data ( ).size ( ) <= n )
  {
  fraction < exint >
    c ( gamma_asymptotic_series_coefficient ( qde.data ( ).size ( ) + 1 ) ) ;

  if ( ( qde.data ( ).size ( ) & 1 ) != 0 )
    c.negate ( ) ;

  qde.step ( c ) ;
  }

return qde.data ( ) [ n ] ;
}



// *** LOG_GAMMA_CONTINUED_FRACTION_COEFFICIENT ***


// pre: n >= 0

fraction < exint > log_gamma_continued_fraction_coefficient ( sint n )

{
assert ( n >= 0 ) ;

static quotient_difference_evaluator < fraction < exint > > qde ;

while ( qde.data ( ).size ( ) <= n )
  {
  fraction < exint >
    c ( log_gamma_asymptotic_series_coefficient ( qde.data ( ).size ( ) ) ) ;

  if ( ( qde.data ( ).size ( ) & 1 ) != 0 )
    c.negate ( ) ;

  qde.step ( c ) ;
  }

return qde.data ( ) [ n ] ;
}
