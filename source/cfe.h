// Copyright Ivan Stanojevic 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __CFE_H

#define __CFE_H



#include "algorithm.h"
#include "cmath.h"

#include "numbase.h"



// *** CONTINUED_FRACTION_EVAULATOR ***


template < class T >
class continued_fraction_evaluator

{
private:

  T k0, l0, k1, l1 ;

public:

  continued_fraction_evaluator ( const T & b0 = 0 ) :
    k0 ( b0 ),
    l0 ( 1 ),
    k1 ( 1 ),
    l1 ( 0 )
    { }

  void step ( const T & a, const T & b ) ;

  bool value_valid ( ) const
    { return l0 != 0 ; }

  T value ( ) const
    { return k0 / l0 ; }

} ;


//

template < class T >
void continued_fraction_evaluator < T > :: step ( const T & a, const T & b )

{
T k = k0 * b + k1 * a,
  l = l0 * b + l1 * a ;

k1 = k0 ;
k0 = k ;
l1 = l0 ;
l0 = l ;

sint exp_correction = - max ( max ( exponent ( k0 ), exponent ( l0 ) ),
                              max ( exponent ( k1 ), exponent ( l1 ) ) ) ;

k0 = ldexp ( k0, exp_correction ) ;
l0 = ldexp ( l0, exp_correction ) ;
k1 = ldexp ( k1, exp_correction ) ;
l1 = ldexp ( l1, exp_correction ) ;
}



#endif
