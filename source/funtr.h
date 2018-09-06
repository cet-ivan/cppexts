// Copyright Ivan Stanojevic 2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __FUNTR_H

#define __FUNTR_H



#include "cstddef.h"

#include "type_traits.h"



// *** INDEXING_TRAITS ***


//

template < class T >
class indexing_traits ;


//

template < class T >
inline size_t indexing_size ( const T & x )

{
return indexing_traits < T > :: size ( x ) ;
}


//

template < class T >
class indexing_traits < T [ ] >

{
public:

  typedef size_t index_type ;
  typedef typename remove_const < T > :: type value_type ;

} ;


//

template < class T, size_t Size >
class indexing_traits < T [ Size ] >

{
public:

  typedef size_t index_type ;
  typedef typename remove_const < T > :: type value_type ;

  static constexpr size_t size ( const T /* x */ [ ] )
    { return Size ; }

} ;


//

template < class T >
class indexing_traits < T * >

{
public:

  typedef size_t index_type ;
  typedef typename remove_const < T > :: type value_type ;

} ;



#endif
