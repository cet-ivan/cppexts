// Copyright Ivan Stanojevic 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __CMATH_H

#define __CMATH_H



#include <cmath>

#include "type_traits.h"



using std :: double_t ;
using std :: float_t ;

using std :: abs ;
using std :: acos ;
using std :: acosh ;
using std :: asin ;
using std :: asinh ;
using std :: atan ;
using std :: atan2 ;
using std :: atanh ;
using std :: cbrt ;
using std :: ceil ;
using std :: copysign ;
using std :: cos ;
using std :: cosh ;
using std :: erf ;
using std :: erfc ;
using std :: exp2 ;
using std :: exp ;
using std :: expm1 ;
using std :: fabs ;
using std :: fdim ;
using std :: floor ;
using std :: fma ;
using std :: fmax ;
using std :: fmin ;
using std :: fmod ;
using std :: frexp ;
using std :: hypot ;
using std :: ilogb ;
using std :: ldexp ;
using std :: lgamma ;
using std :: llrint ;
using std :: llround ;
using std :: log ;
using std :: log10 ;
using std :: log1p ;
using std :: log2 ;
using std :: logb ;
using std :: lrint ;
using std :: lround ;
using std :: modf ;
using std :: nan ;
using std :: nanf ;
using std :: nanl ;
using std :: nearbyint ;
using std :: nextafter ;
using std :: nexttoward ;
using std :: pow ;
using std :: remainder ;
using std :: remquo ;
using std :: rint ;
using std :: round ;
using std :: scalbln ;
using std :: scalbn ;
using std :: sin ;
using std :: sinh ;
using std :: sqrt ;
using std :: tan ;
using std :: tanh ;
using std :: tgamma ;
using std :: trunc ;

using std :: fpclassify ;
using std :: isfinite ;
using std :: isgreater ;
using std :: isgreaterequal ;
using std :: isinf ;
using std :: isless ;
using std :: islessequal ;
using std :: islessgreater ;
using std :: isnan ;
using std :: isnormal ;
using std :: isunordered ;
using std :: signbit ;



// *** EXTENSIONS ***


//

template < class T1, class T2 >
inline typename enable_if <     is_floating_point < T1 > :: value
                            &&  is_integral < T2 > :: value,
                            T1 > :: type
  ldexp ( T1 x, T2 n )

{
return std :: ldexp ( x, static_cast < int > ( n ) ) ;
}



#endif
