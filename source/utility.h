// Copyright Ivan Stanojevic 2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __UTILITY_H

#define __UTILITY_H



#include "utility_base.h"
#include "streaming.h"


// *** STREAMING ***


namespace std

{

//

template < class CharT, class CharTraits, class T1, class T2 >
inline basic_ostream < CharT, CharTraits > &
  operator << ( basic_ostream < CharT, CharTraits > & o,
                const pair < T1, T2 > & p )

{
return output_pair ( o, p.first, p.second ) ;
}


//

template < class CharT, class CharTraits, class T1, class T2 >
inline basic_istream < CharT, CharTraits > &
  operator >> ( basic_istream < CharT, CharTraits > & i,
                pair < T1, T2 > & p )

{
return input_pair ( i, p.first, p.second ) ;
}

}


using std :: operator << ;
using std :: operator >> ;



#endif
