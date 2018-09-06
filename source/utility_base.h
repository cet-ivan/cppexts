// Copyright Ivan Stanojevic 2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __UTILITY_BASE_H

#define __UTILITY_BASE_H



#include <utility>



using std :: swap ;

using std :: forward ;
using std :: move ;
using std :: move_if_noexcept ;

using std :: declval ;

using std :: pair ;

using std :: operator == ;
using std :: operator != ;
using std :: operator < ;
using std :: operator > ;
using std :: operator <= ;
using std :: operator >= ;

using std :: make_pair ;

using std :: tuple_size ;
using std :: tuple_element ;
using std :: get ;

using std :: piecewise_construct_t ;
using std :: piecewise_construct ;

using std :: tuple ;



// *** PAIR COMPONENT SELECTORS ***


//

template < class T1, class T2 >
class select_first

{
public:

  const T1 & operator ( ) ( const pair < T1, T2 > & p ) const
    { return p.first ; }

  T1 & operator ( ) ( pair < T1, T2 > & p ) const
    { return p.first ; }

} ;


//

template < class T1, class T2 >
class select_second

{
public:

  const T2 & operator ( ) ( const pair < T1, T2 > & p ) const
    { return p.second ; }

  T2 & operator ( ) ( pair < T1, T2 > & p ) const
    { return p.second ; }

} ;



// *** RELOPS ***


//

template < class T1, class T2 >
inline bool operator != ( const T1 & a, const T2 & b )

{
return ! ( a == b ) ;
}


//

template < class T1, class T2 >
inline bool operator > ( const T1 & a, const T2 & b )

{
return b < a ;
}


//

template < class T1, class T2 >
inline bool operator <= ( const T1 & a, const T2 & b )

{
return ! ( b < a ) ;
}


//

template < class T1, class T2 >
inline bool operator >= ( const T1 & a, const T2 & b )

{
return ! ( a < b ) ;
}



#endif
