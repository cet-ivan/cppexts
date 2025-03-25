// Copyright Ivan Stanojevic 2025.
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
class indexing_traits < T [ ] >

{
public:

  typedef size_t index_type ;
  typedef remove_const_t < T > value_type ;

} ;


//

template < class T, size_t N >
class indexing_traits < T [ N ] >

{
public:

  typedef size_t index_type ;
  typedef remove_const_t < T > value_type ;

} ;


//

template < class T >
class indexing_traits < T * >

{
public:

  typedef size_t index_type ;
  typedef remove_const_t < T > value_type ;

} ;


//

template< class T >
using indexing_it = typename indexing_traits < T > :: index_type ;


//

template< class T >
using indexing_vt = typename indexing_traits < T > :: value_type ;



// *** EMPTY_INDEXING ***


//

template < class T, size_t Dimension >
class empty_indexing

{
public:

  static_assert ( Dimension > 0 ) ;

  typedef empty_indexing < T, Dimension - 1 > value_type ;

  value_type operator [ ] ( size_t ) const
    { return value_type ( ) ; }

} ;


//

template < class T >
class empty_indexing < T, 1 >

{
public:

  typedef remove_const_t < T > value_type ;

  value_type operator [ ] ( size_t ) const
    { return value_type ( ) ; }

} ;


//

template < class T, size_t Dimension >
class indexing_traits < empty_indexing < T, Dimension > >

{
public:

  typedef size_t index_type ;
  typedef typename empty_indexing < T, Dimension > :: value_type value_type ;

} ;



// *** INDEXING_SIZE ***


//

template < class T, size_t N >
constexpr size_t indexing_size ( const T ( & ) [ N ] )

{
return N ;
}


//

template < class T, size_t Dimension >
constexpr size_t indexing_size ( const empty_indexing < T, Dimension > & )

{
return 0 ;
}



#endif
