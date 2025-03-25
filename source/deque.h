// Copyright Ivan Stanojevic 2025.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __DEQUE_H

#define __DEQUE_H



#include "compspec.h"

#include <deque>

#include "funtr.h"
#include "streaming.h"



using std :: deque ;

using std :: operator == ;
using std :: operator != ;
using std :: operator < ;
using std :: operator > ;
using std :: operator <= ;
using std :: operator >= ;

using std :: swap ;



// *** INDEXING_TRAITS ***


template < class T, class Allocator >
class indexing_traits < deque < T, Allocator > >

{
public:

  typedef typename deque < T, Allocator > :: size_type index_type ;
  typedef T value_type ;

} ;


//

template < class T, class Allocator >
inline size_t indexing_size ( const deque < T, Allocator > & x )

{
return x.size ( ) ;
}



#ifdef __gnu_compiler__


//

template < class T >
class indexing_traits < std :: _Deque_iterator < T, T &, T * > >

{
public:

  typedef
    typename std :: _Deque_iterator < T, T &, T * > :: size_type
    index_type ;

  typedef T value_type ;

} ;


//

template < class T >
class indexing_traits < std :: _Deque_iterator < T, const T &, const T * > >

{
public:

  typedef
    typename std :: _Deque_iterator < T, const T &, const T * > :: size_type
    index_type ;

  typedef T value_type ;

} ;


//

template < class T >
class indexing_traits
        < std :: reverse_iterator
            < std :: _Deque_iterator < T, T &, T * > > >

{
public:

  typedef
    typename std :: _Deque_iterator < T, T &, T * > :: size_type
    index_type ;

  typedef T value_type ;

} ;


//

template < class T >
class indexing_traits
        < std :: reverse_iterator
            < std :: _Deque_iterator < T, const T &, const T * > > >

{
public:

  typedef
    typename std :: _Deque_iterator < T, const T &, const T * > :: size_type
    index_type ;

  typedef T value_type ;

} ;


#endif



// *** CONCATENATION ***


template < class T, class Allocator >
class deque_concatenator

{
public:

  deque < T, Allocator > d ;

  deque_concatenator ( const deque < T, Allocator > & i_d ) :
    d ( i_d )
    { }

  deque_concatenator ( deque < T, Allocator > && i_d ) :
    d ( move ( i_d ) )
    { }

  template < class Sequence >
  deque_concatenator & operator + ( const Sequence & s )
    { d.insert ( d.end ( ), begin ( s ), end ( s ) ) ;
      return * this ; }

  template < class Sequence >
  deque_concatenator & operator + ( Sequence && s )
    { d.insert ( d.end ( ), make_move_iterator ( begin ( s ) ),
                            make_move_iterator ( end   ( s ) ) ) ;
      return * this ; }

} ;


//

template < class T, class Allocator, class ... Sequences >
inline deque < T, Allocator >
  concatenate ( const deque < T, Allocator > & d, Sequences && ... s )

{
return  (         deque_concatenator < T, Allocator > ( d )
          + ... + forward < Sequences > ( s ) )
       .d ;
}


//

template < class T, class Allocator, class ... Sequences >
inline deque < T, Allocator >
  concatenate ( deque < T, Allocator > && d, Sequences && ... s )

{
return  (         deque_concatenator < T, Allocator > ( move ( d ) )
          + ... + forward < Sequences > ( s ) )
       .d ;
}



// *** STREAMING ***


namespace std

{

//

template < class CharT, class CharTraits, class T, class Allocator >
inline basic_ostream < CharT, CharTraits > &
  operator << ( basic_ostream < CharT, CharTraits > & o,
                const deque < T, Allocator > & x )

{
return output_sequence ( o, x ) ;
}


//

template < class CharT, class CharTraits, class T, class Allocator >
inline basic_istream < CharT, CharTraits > &
  operator >> ( basic_istream < CharT, CharTraits > & i,
                deque < T, Allocator > & x )

{
return input_sequence ( i, x ) ;
}

}


using std :: operator << ;
using std :: operator >> ;



#endif
