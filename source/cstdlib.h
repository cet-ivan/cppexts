// Copyright Ivan Stanojevic 2023.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __CSTDLIB_H

#define __CSTDLIB_H



#include <cstdlib>



using std :: size_t ;
using std :: div_t ;
using std :: ldiv_t ;
using std :: lldiv_t ;

using std :: abort ;
using std :: atexit ;

#ifndef __mingw_compiler__

using std :: at_quick_exit ;
using std :: quick_exit ;

#endif

using std :: exit ;
using std :: _Exit ;

using std :: getenv ;
using std :: system ;

using std :: aligned_alloc ;
using std :: calloc ;
using std :: free ;
using std :: malloc ;
using std :: realloc ;

using std :: atof ;
using std :: atoi ;
using std :: atol ;
using std :: atoll ;

using std :: strtod ;
using std :: strtof ;
using std :: strtold ;
using std :: strtol ;
using std :: strtoll ;
using std :: strtoul ;
using std :: strtoull ;

using std :: mblen ;
using std :: mbtowc ;
using std :: wctomb ;
using std :: mbstowcs ;
using std :: wcstombs ;

using std :: bsearch ;
using std :: qsort ;

using std :: rand ;
using std :: srand ;

// using std :: abs ;

using std :: div ;



#endif
