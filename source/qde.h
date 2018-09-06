// Copyright Ivan Stanojevic 2015.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __QDE_H

#define __QDE_H



#include "memory.h"
#include "vector.h"
#include "utility.h"



// *** QUOTIENT_DIFFERENCE_EVALUATOR ***


template < class T, class Allocator = allocator < T > >
class quotient_difference_evaluator

{
private:

  vector < T, Allocator > dm1, data_ ;

public:

  explicit
    quotient_difference_evaluator ( const Allocator & a = Allocator ( ) ) :
    dm1 ( a ),
    data_ ( a )
    { }

  void step ( const T & x ) ;

  const vector < T, Allocator > & data ( ) const
    { return data_ ; }

} ;


//

template < class T, class Allocator >
void quotient_difference_evaluator < T, Allocator > :: step ( const T & x )

{
vector < T > dm0 ;
dm0.reserve ( data_.size ( ) + 1 ) ;

dm0.push_back ( x ) ;

if ( data_.size ( ) >= 1 )
  {
  dm0.push_back ( dm0.back ( ) / dm1 [ 0 ] ) ;

  if ( data_.size ( ) >= 2 )
    {
    dm0.push_back ( dm0.back ( ) - dm1 [ 1 ] ) ;

    for ( sint i = 3 ; i <= data_.size ( ) ; ++ i )
      if ( ( i & 1 ) == 0 )
        dm0.push_back ( dm1 [ i - 2 ] + dm0.back ( ) - dm1 [ i - 1 ] ) ;
      else
        dm0.push_back ( dm1 [ i - 2 ] * dm0.back ( ) / dm1 [ i - 1 ] ) ;
    }
  }

data_.push_back ( dm0.back ( ) ) ;

dm1 = move ( dm0 ) ;
}



#endif
