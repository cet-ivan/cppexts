// Copyright Ivan Stanojevic 2022.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __MAP_H

#define __MAP_H



#include <map>

#include "utility.h"

#include "funtr.h"
#include "streaming.h"



using std :: map ;
using std :: multimap ;

using std :: operator == ;
using std :: operator != ;
using std :: operator < ;
using std :: operator > ;
using std :: operator <= ;
using std :: operator >= ;

using std :: swap ;



// *** INDEXING_TRAITS ***


template < class Key, class T, class Compare, class Allocator >
class indexing_traits < map < Key, T, Compare, Allocator > >

{
public:

  typedef Key index_type ;
  typedef T value_type ;

} ;



// *** SEQUENCE_SIZE ***


//

template < class Key, class T, class Compare, class Allocator >
inline
  size_t sequence_size ( const map < Key, T, Compare, Allocator > & x )

{
return x.size ( ) ;
}


//

template < class Key, class T, class Compare, class Allocator >
inline
  size_t sequence_size ( const multimap < Key, T, Compare, Allocator > & x )

{
return x.size ( ) ;
}



// *** STREAMING ***


//

class map_type_pair_input_operator

{
public:

  template < class CharT, class CharTraits, class Key, class T >
  basic_istream < CharT, CharTraits > &
    operator ( ) ( basic_istream < CharT, CharTraits > & i,
                   pair < const Key, T > & p ) const
    { return input_pair ( i, const_cast < Key & > ( p.first ), p.second ) ; }

} ;


namespace std

{

//

template < class CharT, class CharTraits,
           class Key, class T, class Compare, class Allocator >
inline basic_ostream < CharT, CharTraits > &
  operator << ( basic_ostream < CharT, CharTraits > & o,
                const map < Key, T, Compare, Allocator > & x )

{
return output_sequence ( o, x ) ;
}


//

template < class CharT, class CharTraits,
           class Key, class T, class Compare, class Allocator >
inline basic_istream < CharT, CharTraits > &
  operator >> ( basic_istream < CharT, CharTraits > & i,
                map < Key, T, Compare, Allocator > & x )

{
return input_sequence ( i, x, map_type_pair_input_operator ( ) ) ;
}


//

template < class CharT, class CharTraits,
           class Key, class T, class Compare, class Allocator >
inline basic_ostream < CharT, CharTraits > &
  operator << ( basic_ostream < CharT, CharTraits > & o,
                const multimap < Key, T, Compare, Allocator > & x )

{
return output_sequence ( o, x ) ;
}


//

template < class CharT, class CharTraits,
           class Key, class T, class Compare, class Allocator >
inline basic_istream < CharT, CharTraits > &
  operator >> ( basic_istream < CharT, CharTraits > & i,
                multimap < Key, T, Compare, Allocator > & x )

{
return input_sequence ( i, x, map_type_pair_input_operator ( ) ) ;
}

}


using std :: operator << ;
using std :: operator >> ;



#endif
