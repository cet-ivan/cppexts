// Copyright Ivan Stanojevic 2024.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __PZEROS_H

#define __PZEROS_H



#include "complex.h"

#include "polynomial.h"
#include "algorithm.h"
#include "convtest.h"



// *** ZEROS ***


template < class T, class Allocator >
vector < typename complex_traits < T > :: complex_type,
         typename Allocator ::
           template rebind < typename complex_traits < T > :: complex_type > ::
             other >
  zeros ( polynomial < T, Allocator > p )

{
typedef typename complex_traits < T > :: real_type real_type ;
typedef typename complex_traits < T > :: complex_type complex_type ;

typedef
  vector < complex_type,
           typename Allocator :: template rebind < complex_type > :: other >
  complex_vector ;

if ( p.is_zero ( ) )
  return complex_vector ( ) ;

p.scale_to_monic ( ) ;

sint delay = p.delay ( ) ;
p.remove_delay ( ) ;

complex_vector result ;
real_type result_norm ( numeric_traits < real_type > :: max ( ) ) ;

complex_vector current ;
current.reserve ( p.degree ( ) ) ;

{
real_type m ( 0 ) ;

for ( const T & c : p )
  limit_min ( m, abs ( c ) ) ;

m *= 2 ;

for ( sint i = 0 ; i < p.degree ( ) ; ++ i )
  current.push_back
            ( polar ( m,
                        i * 2 * numeric_constants < real_type > :: pi ( )
                      / p.degree ( ) ) ) ;
}

convergence_tester < real_type > ct ( max < sint > ( p.size ( ) << 2, 2 ) ) ;

do
  {
  real_type current_norm ( 0 ) ;

  for ( auto change_iter = current.begin ( ) ;
             change_iter != current.end ( ) ;
             ++ change_iter )
    {
    complex_type z ( 1 ) ;

    for ( auto mult_iter = current.cbegin ( ) ;
               mult_iter != current.cend ( ) ;
               ++ mult_iter )
      if ( mult_iter != change_iter )
        z *= * change_iter - * mult_iter ;

    complex_type delta_z ( p ( * change_iter ) / z ) ;
    * change_iter -= delta_z ;
    current_norm += norm ( delta_z ) ;
    }

  if ( result_norm > current_norm )
    {
    result = current ;
    result_norm = current_norm ;
    }

  ct.insert ( current_norm ) ;
  }
while ( ! ct.converged ( ) ) ;

result.insert ( result.end ( ), delay, complex_type ( ) ) ;

return result ;
}



#endif
