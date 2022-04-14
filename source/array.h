// Copyright Ivan Stanojevic 2022.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __ARRAY_H

#define __ARRAY_H



#include <array>

#include "funtr.h"
#include "streaming.h"



using std :: array ;

using std :: operator == ;
using std :: operator != ;
using std :: operator < ;
using std :: operator > ;
using std :: operator <= ;
using std :: operator >= ;

using std :: swap ;

using std :: tuple_size ;
using std :: tuple_element ;

using std :: get ;



// *** INDEXING_TRAITS ***


template < class T, size_t N >
class indexing_traits < array < T, N > >

{
public:

  typedef size_t index_type ;
  typedef T value_type ;

} ;



// *** SEQUENCE_SIZE ***


template < class T, size_t N >
inline constexpr size_t sequence_size ( const array < T, N > & )

{
return N ;
}



// *** STREAMING ***


namespace std

{

//

template < class CharT, class CharTraits, class T, size_t N >
inline basic_ostream < CharT, CharTraits > &
  operator << ( basic_ostream < CharT, CharTraits > & o,
                const array < T, N > & x )

{
return output_sequence ( o, x ) ;
}

}


using std :: operator << ;
using std :: operator >> ;



#endif
