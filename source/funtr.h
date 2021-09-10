// Copyright Ivan Stanojevic 2021.
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



// *** EMPTY_INDEXING ***


//

template < class T, size_t Dimension >
class empty_indexing_imp

{
public:

  empty_indexing_imp < T, Dimension - 1 > operator [ ] ( size_t ) const
    { return empty_indexing_imp < T, Dimension - 1 > ( ) ; }

} ;


//

template < class T >
class empty_indexing_imp < T, 1 >

{
public:

  T operator [ ] ( size_t ) const
    { return T ( ) ; }

} ;


//

template < class T >
class empty_indexing_imp < T, 0 > ;


//

template < class T, size_t Dimension >
class empty_indexing_traits

{
public:

  typedef empty_indexing_imp < T, Dimension > type ;

} ;


//

template < class T >
class empty_indexing_traits < T, 0 >

{
public:

  typedef typename remove_const < T > :: type type ;

} ;


//

template < class T, size_t Dimension >
using empty_indexing = typename empty_indexing_traits < T, Dimension > :: type ;


//

template < class T, size_t Dimension >
class indexing_traits < empty_indexing_imp < T, Dimension > >

{
public:

  typedef size_t index_type ;
  typedef empty_indexing < T, Dimension - 1 > value_type ;

  static constexpr size_t size ( empty_indexing < T, Dimension > )
    { return 0 ; }

} ;


//

template < class T >
class indexing_traits < empty_indexing_imp < T, 0 > > ;



#endif
