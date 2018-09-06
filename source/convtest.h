// Copyright Ivan Stanojevic 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __CONVTEST_H

#define __CONVTEST_H



#include "cstddef.h"
#include "list.h"
#include "set.h"
#include "iterator.h"



// *** CONVERGENCE_TESTER ***


template < class T >
class convergence_tester

{
private:

  size_t size ;

  list < T > window ;
  multiset < T > sorted_window ;

  bool converged_ ;
  T value_ ;

  void raw_insert ( const T & x )
    { window.push_back ( x ) ;
      sorted_window.insert ( x ) ; }

  void raw_remove_first ( )
    { sorted_window.erase ( sorted_window.find ( window.front ( ) ) ) ;
      window.pop_front ( ) ; }

public:

  convergence_tester ( size_t i_size = 0 ) :
    size ( i_size ),
    window ( ),
    sorted_window ( ),
    converged_ ( i_size == 0 ),
    value_ ( )
    { }

  void insert ( const T & x ) ;

  bool converged ( ) const
    { return converged_ ; }

  T value ( ) const
    { return value_ ; }

} ;


//

template < class T >
void convergence_tester < T > :: insert ( const T & x )

{
if ( converged_ )
  return ;

if ( window.size ( ) < size )
  {
  raw_insert ( x ) ;
  return ;
  }

T last_var = * ( -- sorted_window.end ( ) ) - * sorted_window.begin ( ) ;

raw_insert ( x ) ;
raw_remove_first ( ) ;

if ( * ( -- sorted_window.end ( ) ) - * sorted_window.begin ( ) >= last_var )
  {
  converged_ = true ;
  value_ = * next ( sorted_window.begin ( ), size >> 1 ) ;
  }
}



#endif
