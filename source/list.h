// Copyright Ivan Stanojevic 2025.
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



// *** CONCATENATION ***


template < class T, class Allocator >
class list_concatenator

{
public:

  list < T, Allocator > l ;

  list_concatenator ( const list < T, Allocator > & i_l ) :
    l ( i_l )
    { }

  list_concatenator ( list < T, Allocator > && i_l ) :
    l ( move ( i_l ) )
    { }

  template < class Sequence >
  list_concatenator & operator + ( const Sequence & s )
    { l.insert ( l.end ( ), begin ( s ), end ( s ) ) ;
      return * this ; }

  template < class Sequence >
  list_concatenator & operator + ( Sequence && s )
    { l.insert ( l.end ( ), make_move_iterator ( begin ( s ) ),
                            make_move_iterator ( end   ( s ) ) ) ;
      return * this ; }

  list_concatenator & operator + ( list < T, Allocator > && s )
    { l.splice ( l.end ( ), s ) ;
      return * this ; }

} ;


//

template < class T, class Allocator, class ... Sequences >
inline list < T, Allocator >
  concatenate ( const list < T, Allocator > & l, Sequences && ... s )

{
return  (         list_concatenator < T, Allocator > ( l )
          + ... + forward < Sequences > ( s ) )
       .l ;
}


//

template < class T, class Allocator, class ... Sequences >
inline list < T, Allocator >
  concatenate ( list < T, Allocator > && l, Sequences && ... s )

{
return  (         list_concatenator < T, Allocator > ( move ( l ) )
          + ... + forward < Sequences > ( s ) )
       .l ;
}



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
