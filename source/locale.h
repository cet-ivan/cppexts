// Copyright Ivan Stanojevic 2023.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __LOCALE_H

#define __LOCALE_H



#include <locale>



using std :: locale ;

using std :: use_facet ;
using std :: has_facet ;

using std :: isspace ;
using std :: isprint ;
using std :: iscntrl ;
using std :: isupper ;
using std :: islower ;
using std :: isalpha ;
using std :: isdigit ;
using std :: ispunct ;
using std :: isxdigit;
using std :: isalnum ;
using std :: isgraph ;

using std :: toupper ;
using std :: tolower ;

using std :: ctype_base ;
using std :: ctype ;
using std :: ctype_byname ;

using std :: codecvt_base ;
using std :: codecvt ;
using std :: codecvt_byname ;

using std :: num_get ;
using std :: num_put ;
using std :: numpunct ;
using std :: numpunct_byname ;

using std :: collate ;
using std :: collate_byname ;

using std :: time_base ;
using std :: time_get ;
using std :: time_get_byname ;
using std :: time_put ;
using std :: time_put_byname ;

using std :: money_base ;
using std :: money_get ;
using std :: money_put ;
using std :: moneypunct ;
using std :: moneypunct_byname ;

using std :: messages_base ;
using std :: messages ;
using std :: messages_byname ;

// using std :: wstring_convert ;
// using std :: wbuffer_convert ;



#endif
