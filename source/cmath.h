// Copyright Ivan Stanojevic 2023.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __CMATH_H

#define __CMATH_H



#include <cmath>

#include "type_traits.h"



using std :: double_t ;
using std :: float_t ;

using std :: acos ;
using std :: asin ;
using std :: atan ;
using std :: atan2 ;

using std :: cos ;
using std :: sin ;
using std :: tan ;

using std :: acosh ;
using std :: asinh ;
using std :: atanh ;

using std :: cosh ;
using std :: sinh ;
using std :: tanh ;

using std :: exp ;
using std :: exp2 ;
using std :: expm1 ;

using std :: frexp ;
using std :: ilogb ;
using std :: ldexp ;

using std :: log ;
using std :: log10 ;
using std :: log1p ;
using std :: log2 ;
using std :: logb ;

using std :: modf ;

using std :: scalbn ;
using std :: scalbln ;

using std :: cbrt ;

//using std :: abs ;
using std :: fabs ;

using std :: hypot ;

using std :: pow ;
using std :: sqrt ;

using std :: erf ;
using std :: erfc ;

using std :: lgamma ;
using std :: tgamma ;

using std :: ceil ;
using std :: floor ;

using std :: nearbyint ;
using std :: rint ;
using std :: lrint ;
using std :: llrint ;

using std :: round ;
using std :: lround ;
using std :: llround ;

using std :: trunc ;
using std :: fmod ;
using std :: remainder ;
using std :: remquo ;

using std :: copysign ;

using std :: nan ;
using std :: nanf ;
using std :: nanl ;

using std :: nextafter ;
using std :: nexttoward ;

using std :: fdim ;

using std :: fmax ;
using std :: fmin ;

using std :: fma ;

using std :: fpclassify ;
using std :: isfinite ;
using std :: isinf ;
using std :: isnan ;
using std :: isnormal ;
using std :: signbit ;
using std :: isgreater ;
using std :: isgreaterequal ;
using std :: isless ;
using std :: islessequal ;
using std :: islessgreater ;
using std :: isunordered ;

#if defined(__gnu_compiler__)

using std :: assoc_laguerre ;
using std :: assoc_legendre ;

// using std :: beta ;

using std :: comp_ellint_1 ;
using std :: comp_ellint_2 ;
using std :: comp_ellint_3 ;

using std :: cyl_bessel_i ;
using std :: cyl_bessel_j ;
using std :: cyl_bessel_k ;

using std :: cyl_neumann ;

using std :: ellint_1 ;
using std :: ellint_2 ;
using std :: ellint_3 ;

using std :: expint ;

using std :: hermite ;
using std :: laguerre ;
using std :: legendre ;

using std :: riemann_zeta ;

using std :: sph_bessel ;
using std :: sph_legendre ;
using std :: sph_neumann ;

#endif



// *** EXTENSIONS ***


//

template < class T1, class T2 >
inline enable_if_t < is_floating_point_v < T1 > &&  is_integral_v < T2 >, T1 >
  ldexp ( T1 x, T2 n )

{
return std :: ldexp ( x, static_cast < int > ( n ) ) ;
}



#endif
