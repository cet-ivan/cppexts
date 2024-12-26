// Copyright Ivan Stanojevic 2023.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __QUEUE_H

#define __QUEUE_H



#include <queue>

#include "vector.h"
#include "functional.h"
#include "type_traits.h"
#include "algorithm.h"
#include "memory.h"
#include "utility.h"



using std :: queue ;

using std :: operator == ;
using std :: operator != ;
using std :: operator < ;
using std :: operator > ;
using std :: operator <= ;
using std :: operator >= ;

using std :: swap ;



// *** PRIORITY_QUEUE ***


template < class T,
           class Container = vector < T >,
           class Compare = less < typename Container :: value_type > >
class priority_queue

{
public:

  typedef typename Container :: value_type value_type ;
  typedef typename Container :: reference reference ;
  typedef typename Container :: const_reference const_reference ;
  typedef typename Container :: size_type size_type ;
  typedef Container container_type ;
  typedef Compare value_compare ;

  static_assert ( ( is_same_v < T, value_type > ), "" ) ;

protected:

  container_type c ;
  value_compare comp ;

public:

  priority_queue ( )
    { }

  explicit priority_queue ( const value_compare & i_comp ) :
    c ( ),
    comp ( i_comp )
    { }

  priority_queue ( const value_compare & i_comp,
                   const container_type & i_c ) :
    c ( i_c ),
    comp ( i_comp )
    { make_heap ( c.begin ( ), c.end ( ), comp ) ; }

  priority_queue ( const value_compare & i_comp,
                   container_type && i_c ) :
    c ( move ( i_c ) ),
    comp ( i_comp )
    { make_heap ( c.begin ( ), c.end ( ), comp ) ; }

  template < class InputIterator >
  priority_queue ( InputIterator first, InputIterator last ) :
    c ( first, last ),
    comp ( )
    { make_heap ( c.begin ( ), c.end ( ), comp ) ; }

  template < class InputIterator >
  priority_queue ( InputIterator first, InputIterator last,
                   const value_compare & i_comp ) :
    c ( first, last ),
    comp ( i_comp )
    { make_heap ( c.begin ( ), c.end ( ), comp ) ; }

  template < class InputIterator >
  priority_queue ( InputIterator first, InputIterator last,
                   const value_compare & i_comp,
                   const container_type & i_c ) :
    c ( i_c ),
    comp ( i_comp )
    { c.insert ( c.end ( ), first, last ) ;
      make_heap ( c.begin ( ), c.end ( ), comp ) ; }

  template < class InputIterator >
  priority_queue ( InputIterator first, InputIterator last,
                   const value_compare & i_comp,
                   container_type && i_c ) :
    c ( move ( i_c ) ),
    comp ( i_comp )
    { c.insert ( c.end ( ), first, last ) ;
      make_heap ( c.begin ( ), c.end ( ), comp ) ; }

  template < class Alloc,
             class = enable_if_t < uses_allocator_v < container_type,
                                                      Alloc > > >
  explicit priority_queue ( const Alloc & a ) :
    c ( a ),
    comp ( )
    { }

  template < class Alloc,
             class = enable_if_t < uses_allocator_v < container_type,
                                                      Alloc > > >
  priority_queue ( const value_compare & i_comp,
                   const Alloc & a ) :
    c ( a ),
    comp ( i_comp )
    { }

  template < class Alloc,
             class = enable_if_t < uses_allocator_v < container_type,
                                                      Alloc > > >
  priority_queue ( const value_compare & i_comp,
                   const container_type & i_c,
                   const Alloc & a ) :
    c ( i_c, a ),
    comp ( i_comp )
    { make_heap ( c.begin ( ), c.end ( ), comp ) ; }

  template < class Alloc,
             class = enable_if_t < uses_allocator_v < container_type,
                                                      Alloc > > >
  priority_queue ( const value_compare & i_comp,
                   container_type && i_c,
                   const Alloc & a ) :
    c ( move ( i_c ), a ),
    comp ( i_comp )
    { make_heap ( c.begin ( ), c.end ( ), comp ) ; }

  template < class Alloc,
             class = enable_if_t < uses_allocator_v < container_type,
                                                      Alloc > > >
  priority_queue ( const priority_queue & q,
                   const Alloc & a ) :
    c ( q.c, a ),
    comp ( q.comp )
    { }

  template < class Alloc,
             class = enable_if_t < uses_allocator_v < container_type,
                                                      Alloc > > >
  priority_queue ( priority_queue && q,
                   const Alloc & a ) :
    c ( move ( q.c ), a ),
    comp ( move ( q.comp ) )
    { }

  const container_type & container ( ) const
    { return c ; }

  bool empty ( ) const
    { return c.empty ( ) ; }

  size_type size ( ) const
    { return c.size ( ) ; }

  const_reference top ( ) const
    { return c.front ( ) ; }

  void push ( const value_type & x )
    { c.push_back ( x ) ;
      push_heap ( c.begin ( ), c.end ( ), comp ) ; }

  void push ( value_type && x )
    { c.push_back ( move ( x ) ) ;
      push_heap ( c.begin ( ), c.end ( ), comp ) ; }

  template < class ... Args >
  void emplace ( Args && ... args )
    { c.emplace_back ( forward < Args > ( args ) ... ) ;
      push_heap ( c.begin ( ), c.end ( ), comp ) ; }

  void pop ( )
    { pop_heap ( c.begin ( ), c.end ( ), comp ) ;
      c.pop_back ( ) ; }

  value_type pull ( )
    { pop_heap ( c.begin ( ), c.end ( ), comp ) ;
      value_type t ( move ( c.back ( ) ) ) ;
      c.pop_back ( ) ;
      return t ; }

  void swap ( priority_queue & q )
    noexcept (     noexcept ( :: swap ( c, q.c ) )
               &&  noexcept ( :: swap ( comp, q.comp ) ) )
    { :: swap ( c, q.c ) ;
      :: swap ( comp, q.comp ) ; }

} ;


//

template < class T, class Container, class Compare >
inline void swap ( priority_queue < T, Container, Compare > & x,
                   priority_queue < T, Container, Compare > & y )
  noexcept ( noexcept ( x.swap ( y ) ) )

{
x.swap ( y ) ;
}


//

template < class T, class Container, class Compare, class Alloc >
class uses_allocator < priority_queue < T, Container, Compare >, Alloc > :
        uses_allocator < Container, Alloc > :: type

{
} ;



#endif
