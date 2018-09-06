// Copyright Ivan Stanojevic 2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __LIST_H

#define __LIST_H



#include <list>

#include "streaming.h"



using std :: list ;

using std :: operator == ;
using std :: operator != ;
using std :: operator < ;
using std :: operator > ;
using std :: operator <= ;
using std :: operator >= ;

using std :: swap ;



// *** STREAMING ***


namespace std

{

//

template < class CharT, class CharTraits, class T, class Allocator >
inline basic_ostream < CharT, CharTraits > &
  operator << ( basic_ostream < CharT, CharTraits > & o,
                const list < T, Allocator > & x )

{
return output_sequence ( o, x ) ;
}


//

template < class CharT, class CharTraits, class T, class Allocator >
inline basic_istream < CharT, CharTraits > &
  operator >> ( basic_istream < CharT, CharTraits > & i,
                list < T, Allocator > & x )

{
return input_sequence ( i, x ) ;
}

}


using std :: operator << ;
using std :: operator >> ;



#endif
