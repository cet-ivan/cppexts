// Copyright Ivan Stanojevic 2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __CSTDLIB_H

#define __CSTDLIB_H



#include <cstdlib>



using std :: _Exit ;
using std :: abort ;
using std :: atexit ;
using std :: exit ;

#ifndef __mingw_compiler__
using std :: at_quick_exit ;
using std :: quick_exit ;
#endif

using std :: getenv ;
using std :: system ;

using std :: calloc ;
using std :: free ;
using std :: malloc ;
using std :: realloc ;

using std :: atof ;
using std :: atoi ;
using std :: atol ;
using std :: atoll ;
using std :: mblen ;
using std :: mbtowc ;
using std :: mbstowcs ;
using std :: strtod ;
using std :: strtof ;
using std :: strtol ;
using std :: strtold ;
using std :: strtoll ;
using std :: strtoul ;
using std :: strtoull ;
using std :: wctomb ;
using std :: wcstombs ;

using std :: size_t ;
using std :: bsearch ;
using std :: qsort ;

using std :: div_t ;
using std :: ldiv_t ;
using std :: lldiv_t ;
using std :: abs ;
using std :: labs ;
using std :: llabs ;
using std :: div ;
using std :: ldiv ;
using std :: lldiv ;
using std :: rand ;
using std :: srand ;



#endif
