// Copyright Ivan Stanojevic 2022.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __VECTOR_H

#define __VECTOR_H



#include "compspec.h"

#include <vector>

#include "utility.h"
#include "iterator.h"

#include "funtr.h"
#include "streaming.h"



using std :: vector ;

using std :: operator == ;
using std :: operator != ;
using std :: operator < ;
using std :: operator > ;
using std :: operator <= ;
using std :: operator >= ;

using std :: swap ;



// *** INDEXING_TRAITS ***


template < class T, class Allocator >
class indexing_traits < vector < T, Allocator > >

{
public:

  typedef typename vector < T, Allocator > :: size_type index_type ;
  typedef T value_type ;

} ;



// *** SEQUENCE_SIZE ***


template < class T, class Allocator >
inline size_t sequence_size ( const vector < T, Allocator > & x )

{
return x.size ( ) ;
}



#ifdef __gnu_compiler__


//

template < class T, class Allocator >
class indexing_traits
        < __gnu_cxx :: __normal_iterator
            < typename vector < T, Allocator > :: pointer,
              vector < T, Allocator > > >

{
public:

  typedef typename vector < T, Allocator > :: size_type index_type ;
  typedef T value_type ;

} ;


//

template < class T, class Allocator >
class indexing_traits
        < __gnu_cxx :: __normal_iterator
            < typename vector < T, Allocator > :: const_pointer,
              vector < T, Allocator > > >

{
public:

  typedef typename vector < T, Allocator > :: size_type index_type ;
  typedef T value_type ;

} ;


//

template < class T, class Allocator >
class indexing_traits
        < std :: reverse_iterator
            < __gnu_cxx :: __normal_iterator
                < typename vector < T, Allocator > :: pointer,
                  vector < T, Allocator > > > >

{
public:

  typedef typename vector < T, Allocator > :: size_type index_type ;
  typedef T value_type ;

} ;


//

template < class T, class Allocator >
class indexing_traits
        < std :: reverse_iterator
            < __gnu_cxx :: __normal_iterator
                < typename vector < T, Allocator > :: const_pointer,
                  vector < T, Allocator > > > >

{
public:

  typedef typename vector < T, Allocator > :: size_type index_type ;
  typedef T value_type ;

} ;


#endif



// *** CONCATENATION ***


template < class T, class Allocator >
class vector_concatenator

{
public:

  vector < T, Allocator > v ;

  vector_concatenator ( const vector < T, Allocator > & i_v, size_t new_size ) :
    v ( i_v )
    { v.reserve ( new_size ) ; }

  vector_concatenator ( vector < T, Allocator > && i_v, size_t new_size ) :
    v ( move ( i_v ) )
    { v.reserve ( new_size ) ; }

  template < class Sequence >
  vector_concatenator & operator + ( const Sequence & s )
    { v.insert ( v.end ( ), begin ( s ), end ( s ) ) ;
      return * this ; }

  template < class Sequence >
  vector_concatenator & operator + ( Sequence & s )
    { v.insert ( v.end ( ), cbegin ( s ), cend ( s ) ) ;
      return * this ; }

  template < class Sequence >
  vector_concatenator & operator + ( Sequence && s )
    { v.insert ( v.end ( ), make_move_iterator ( begin ( s ) ),
                            make_move_iterator ( end   ( s ) ) ) ;
      return * this ; }

} ;


//

template < class T, class Allocator, class ... Sequences >
inline vector < T, Allocator >
  concatenate ( const vector < T, Allocator > & v, Sequences && ... s )

{
return move ( (         vector_concatenator < T, Allocator >
                          ( v,
                            ( v.size ( ) + ... + sequence_size ( s ) ) )
                + ... + forward < Sequences > ( s ) ).v ) ;
}


//

template < class T, class Allocator, class ... Sequences >
inline vector < T, Allocator >
  concatenate ( vector < T, Allocator > && v, Sequences && ... s )

{
return move ( (         vector_concatenator < T, Allocator >
                          ( move ( v ),
                            ( v.size ( ) + ... + sequence_size ( s ) ) )
                + ... + forward < Sequences > ( s ) ).v ) ;
}



// *** STREAMING ***


namespace std

{

//

template < class CharT, class CharTraits, class T, class Allocator >
inline basic_ostream < CharT, CharTraits > &
  operator << ( basic_ostream < CharT, CharTraits > & o,
                const vector < T, Allocator > & x )

{
return output_sequence ( o, x ) ;
}


//

template < class CharT, class CharTraits, class T, class Allocator >
inline basic_istream < CharT, CharTraits > &
  operator >> ( basic_istream < CharT, CharTraits > & i,
                vector < T, Allocator > & x )

{
return input_sequence ( i, x ) ;
}

}


using std :: operator << ;
using std :: operator >> ;



#endif
