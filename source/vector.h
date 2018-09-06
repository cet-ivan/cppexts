// Copyright Ivan Stanojevic 2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __VECTOR_H

#define __VECTOR_H



#include "compspec.h"

#include <vector>

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


//

template < class T, class Allocator >
class indexing_traits < vector < T, Allocator > >

{
public:

  typedef typename vector < T, Allocator > :: size_type index_type ;
  typedef T value_type ;

  static size_t size ( const vector < T, Allocator > & x )
    { return x.size ( ) ; }

} ;


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
