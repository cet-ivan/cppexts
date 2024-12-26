// Copyright Ivan Stanojevic 2023.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __NUMBASE_H

#define __NUMBASE_H



#include "compspec.h"

#include "limits.h"
#include "cmath.h"
#include "cassert.h"
#include "functional.h"

#include "typeconv.h"



// *** SINT ***


typedef long sint ;



// *** UINT ***


typedef unsigned long uint ;



// *** __BUILTIN_SIGNED_TYPE ***


//

template < class T >
class __builtin_signed_type ;


//

#define __DEFINE_BUILTIN_SIGNED_TYPE(SignedType) \
                                                 \
template < >                                     \
class __builtin_signed_type < SignedType >       \
                                                 \
{                                                \
public:                                          \
                                                 \
  typedef SignedType type ;                      \
                                                 \
} ;

FOR_BUILTIN_SIGNED_INTEGRAL_TYPES(__DEFINE_BUILTIN_SIGNED_TYPE)

#undef __DEFINE_BUILTIN_SIGNED_TYPE


#define __DEFINE_BUILTIN_SIGNED_TYPE(UnsignedType,SignedType) \
                                                              \
template < >                                                  \
class __builtin_signed_type < UnsignedType >                  \
                                                              \
{                                                             \
public:                                                       \
                                                              \
  typedef SignedType type ;                                   \
                                                              \
} ;

FOR_BUILTIN_UNSIGNED_AND_SIGNED_INTEGRAL_TYPES(__DEFINE_BUILTIN_SIGNED_TYPE)

#undef __DEFINE_BUILTIN_SIGNED_TYPE



// *** __BUILTIN_UNSIGNED_TYPE ***


//

template < class T >
class __builtin_unsigned_type ;


//

#define __DEFINE_BUILTIN_UNSIGNED_TYPE(UnsignedType) \
                                                     \
template < >                                         \
class __builtin_unsigned_type < UnsignedType >       \
                                                     \
{                                                    \
public:                                              \
                                                     \
  typedef UnsignedType type ;                        \
                                                     \
} ;

FOR_BUILTIN_UNSIGNED_INTEGRAL_TYPES(__DEFINE_BUILTIN_UNSIGNED_TYPE)

#undef __DEFINE_BUILTIN_UNSIGNED_TYPE


#define __DEFINE_BUILTIN_UNSIGNED_TYPE(SignedType,UnsignedType) \
                                                                \
template < >                                                    \
class __builtin_unsigned_type < SignedType >                    \
                                                                \
{                                                               \
public:                                                         \
                                                                \
  typedef UnsignedType type ;                                   \
                                                                \
} ;

FOR_BUILTIN_SIGNED_AND_UNSIGNED_INTEGRAL_TYPES(__DEFINE_BUILTIN_UNSIGNED_TYPE)

#undef __DEFINE_BUILTIN_UNSIGNED_TYPE



// *** __BUILTIN_DOUBLE_SIZE_TYPE ***


//

template < class T >
class __builtin_double_size_type

{
public:

  static constexpr bool exists = false ;
  typedef void type ;

} ;


//

#define __DEFINE_BUILTIN_DOUBLE_SIZE_TYPE(Type,DoubleSizeType) \
                                                               \
template < >                                                   \
class __builtin_double_size_type < Type >                      \
                                                               \
{                                                              \
public:                                                        \
                                                               \
  static constexpr bool exists = true ;                        \
  typedef DoubleSizeType type ;                                \
                                                               \
} ;

FOR_BUILTIN_INTEGRAL_TYPES_AND_DOUBLE_SIZE_TYPES(__DEFINE_BUILTIN_DOUBLE_SIZE_TYPE)

#undef __DEFINE_BUILTIN_DOUBLE_SIZE_TYPE



// *** NUMERIC_TRAITS ***


//

template < class T >
class numeric_traits ;


//

#define __DEFINE_NUMERIC_TRAITS(Type)                                      \
                                                                           \
template < >                                                               \
class numeric_traits < Type >                                              \
                                                                           \
{                                                                          \
public:                                                                    \
                                                                           \
  static constexpr bool is_floating_point = false ;                        \
                                                                           \
  static constexpr bool is_signed = true ;                                 \
                                                                           \
  typedef Type signed_type ;                                               \
  typedef __builtin_unsigned_type < Type > :: type unsigned_type ;         \
                                                                           \
  static constexpr bool                                                    \
    has_double_size_type = __builtin_double_size_type < Type > :: exists ; \
                                                                           \
  typedef __builtin_double_size_type < Type > :: type double_size_type ;   \
                                                                           \
  static constexpr sint byte_size = sizeof ( Type ) ;                      \
  static constexpr sint bit_size = byte_size * 8 ;                         \
                                                                           \
  static constexpr Type min ( )                                            \
    { return Type ( Type ( 1 ) << ( bit_size - 1 ) ) ; }                   \
                                                                           \
  static constexpr Type max ( )                                            \
    { return Type (   ( Type ( 1 ) << ( bit_size - 2 ) ) - Type ( 1 )      \
                    + ( Type ( 1 ) << ( bit_size - 2 ) ) ) ; }             \
                                                                           \
} ;

FOR_BUILTIN_SIGNED_INTEGRAL_TYPES(__DEFINE_NUMERIC_TRAITS)

#undef __DEFINE_NUMERIC_TRAITS


//

#define __DEFINE_NUMERIC_TRAITS(Type)                                      \
                                                                           \
template < >                                                               \
class numeric_traits < Type >                                              \
                                                                           \
{                                                                          \
public:                                                                    \
                                                                           \
  static constexpr bool is_floating_point = false ;                        \
                                                                           \
  static constexpr bool is_signed = false ;                                \
                                                                           \
  typedef __builtin_signed_type < Type > :: type signed_type ;             \
  typedef Type unsigned_type ;                                             \
                                                                           \
  static constexpr bool                                                    \
    has_double_size_type = __builtin_double_size_type < Type > :: exists ; \
                                                                           \
  typedef __builtin_double_size_type < Type > :: type double_size_type ;   \
                                                                           \
  static constexpr sint byte_size = sizeof ( Type ) ;                      \
  static constexpr sint bit_size = byte_size * 8 ;                         \
                                                                           \
  static constexpr Type min ( )                                            \
    { return Type ( 0 ) ; }                                                \
                                                                           \
  static constexpr Type max ( )                                            \
    { return Type (   ( Type ( 1 ) << ( bit_size - 1 ) ) - Type ( 1 )      \
                    + ( Type ( 1 ) << ( bit_size - 1 ) ) ) ; }             \
                                                                           \
} ;

FOR_BUILTIN_UNSIGNED_INTEGRAL_TYPES(__DEFINE_NUMERIC_TRAITS)

#undef __DEFINE_NUMERIC_TRAITS


//

#define __DEFINE_NUMERIC_TRAITS(Type)                        \
                                                             \
template < >                                                 \
class numeric_traits < Type >                                \
                                                             \
{                                                            \
public:                                                      \
                                                             \
  static constexpr bool is_floating_point = true ;           \
                                                             \
  static constexpr sint                                      \
    mantissa_bit_size = numeric_limits < Type > :: digits ;  \
                                                             \
  typedef sint exponent_type ;                               \
                                                             \
  static constexpr Type min ( )                              \
    { return numeric_limits < Type > :: min ( ) ; }          \
                                                             \
  static constexpr Type max ( )                              \
    { return numeric_limits < Type > :: max ( ) ; }          \
                                                             \
  static constexpr Type epsilon ( )                          \
    { return numeric_limits < Type > :: epsilon ( ) ; }      \
                                                             \
  static constexpr sint                                      \
    min_exponent = numeric_limits < Type > :: min_exponent ; \
                                                             \
  static constexpr sint                                      \
    max_exponent = numeric_limits < Type > :: max_exponent ; \
                                                             \
} ;

FOR_BUILTIN_FLOATING_POINT_TYPES(__DEFINE_NUMERIC_TRAITS)

#undef __DEFINE_NUMERIC_TRAITS



// *** NUMERIC_CONSTANTS ***


//

template < class T >
class numeric_constants ;


//

template < >
class numeric_constants < float >

{
public:

  static constexpr float pi ( )
    { return 3.14159265358979323846f ; }

  static constexpr float sqrt_pi ( ) // sqrt ( pi )
    { return 1.77245385090551602730f ; }

  static constexpr float sqrt_2pi ( ) // sqrt ( 2 * pi )
    { return 2.50662827463100050242f ; }

  static constexpr float _1_2_sqrt_pi ( ) // 1 / ( 2 * sqrt ( pi ) )
    { return 0.28209479177387814347f ; }

  static constexpr float log_2pi_2 ( ) // log ( 2 * pi ) / 2
    { return 0.91893853320467274178f ; }

  static constexpr float log2e ( )
    { return 1.44269504088896338700f ; }

  static constexpr float log10e ( )
    { return 0.43429448190325182765f ; }

  static constexpr float ln2 ( )
    { return 0.69314718055994530942f ; }

  static constexpr float ln10 ( )
    { return 2.30258509299404568402f ; }

  static constexpr float gamma_cf_shift_limit ( )
    { return 4 ; }

  static constexpr float log_gamma_cf_shift_limit ( )
    { return 6 ; }

} ;


//

template < >
class numeric_constants < double >

{
public:

  static constexpr double pi ( )
    { return 3.14159265358979323846 ; }

  static constexpr double sqrt_pi ( ) // sqrt ( pi )
    { return 1.77245385090551602730 ; }

  static constexpr double sqrt_2pi ( ) // sqrt ( 2 * pi )
    { return 2.50662827463100050242 ; }

  static constexpr double _1_2_sqrt_pi ( ) // 1 / ( 2 * sqrt ( pi ) )
    { return 0.28209479177387814347 ; }

  static constexpr double log_2pi_2 ( ) // log ( 2 * pi ) / 2
    { return 0.91893853320467274178 ; }

  static constexpr double log2e ( )
    { return 1.44269504088896338700 ; }

  static constexpr double log10e ( )
    { return 0.43429448190325182765 ; }

  static constexpr double ln2 ( )
    { return 0.69314718055994530942 ; }

  static constexpr double ln10 ( )
    { return 2.30258509299404568402 ; }

  static constexpr double gamma_cf_shift_limit ( )
    { return 8 ; }

  static constexpr double log_gamma_cf_shift_limit ( )
    { return 9 ; }

} ;


//

template < >
class numeric_constants < long double >

{
public:

  static constexpr long double pi ( )
    { return 3.1415926535897932384626433832795029L ; }

  static constexpr long double sqrt_pi ( ) // sqrt ( pi )
    { return 1.7724538509055160272981674833411452L ; }

  static constexpr long double sqrt_2pi ( ) // sqrt ( 2 * pi )
    { return 2.5066282746310005024157652848110456L ; }

  static constexpr long double _1_2_sqrt_pi ( ) // 1 / ( 2 * sqrt ( pi ) )
    { return 0.2820947917738781434740397257803863L ; }

  static constexpr long double log_2pi_2 ( ) // log ( 2 * pi ) / 2
    { return 0.9189385332046727417803297364056176L ; }

  static constexpr long double log2e ( )
    { return 1.4426950408889633870046509400708601L ; }

  static constexpr long double log10e ( )
    { return 0.4342944819032518276511289189166051L ; }

  static constexpr long double ln2 ( )
    { return 0.6931471805599453094172321214581766L ; }

  static constexpr long double ln10 ( )
    { return 2.3025850929940456840179914546843642L ; }

  static constexpr long double gamma_cf_shift_limit ( )
    { return 11 ; }

  static constexpr long double log_gamma_cf_shift_limit ( )
    { return 12 ; }

} ;



// *** IS_HIGH_BIT_SET ***


#define __DEFINE_IS_HIGH_BIT_SET(Type)                               \
                                                                     \
inline bool is_high_bit_set ( Type x )                               \
                                                                     \
{                                                                    \
return    ( x & (    Type ( 1 )                                      \
                  << ( numeric_traits < Type > :: bit_size - 1 ) ) ) \
       != Type ( 0 ) ;                                               \
}

FOR_BUILTIN_INTEGRAL_TYPES(__DEFINE_IS_HIGH_BIT_SET)

#undef __DEFINE_IS_HIGH_BIT_SET



// *** HAMMING_WEIGHT ***


//

extern const sint __char_hamming_weight [ ] ;


//

#define __DEFINE_HAMMING_WEIGHT(Type)                              \
                                                                   \
inline sint hamming_weight ( Type x )                              \
                                                                   \
{                                                                  \
sint result = __char_hamming_weight [ x & 0xff ] ;                 \
                                                                   \
for ( sint i = 1 ; i < sizeof ( Type ) ; ++ i )                    \
  result += __char_hamming_weight [ ( x >> ( i << 3 ) ) & 0xff ] ; \
                                                                   \
return result ;                                                    \
}

FOR_BUILTIN_INTEGRAL_TYPES(__DEFINE_HAMMING_WEIGHT)

#undef __DEFINE_HAMMING_WEIGHT



// *** DIVMOD ***


#define __DEFINE_DIVMOD(Type)                             \
                                                          \
inline void divmod ( Type a, Type b, Type & q, Type & r ) \
                                                          \
{                                                         \
q = a / b ;                                               \
r = a % b ;                                               \
}

FOR_BUILTIN_INTEGRAL_TYPES(__DEFINE_DIVMOD)

#undef __DEFINE_DIVMOD



// *** SHIFT_RIGHT ***


//

#define __DEFINE_SHIFT_RIGHT(Type)                                            \
                                                                              \
inline Type signed_shift_right ( Type x, sint n )                             \
                                                                              \
{                                                                             \
assert ( n >= 0  &&  n < numeric_traits < Type > :: bit_size ) ;              \
return x >> n ;                                                               \
}                                                                             \
                                                                              \
inline Type unsigned_shift_right ( Type x, sint n )                           \
                                                                              \
{                                                                             \
assert ( n >= 0  &&  n < numeric_traits < Type > :: bit_size ) ;              \
return                                                                        \
  static_cast < Type >                                                        \
    ( static_cast < numeric_traits < Type > :: unsigned_type > ( x ) >> n ) ; \
}

FOR_BUILTIN_SIGNED_INTEGRAL_TYPES(__DEFINE_SHIFT_RIGHT)

#undef __DEFINE_SHIFT_RIGHT


//

#define __DEFINE_SHIFT_RIGHT(Type)                                          \
                                                                            \
inline Type signed_shift_right ( Type x, sint n )                           \
                                                                            \
{                                                                           \
assert ( n >= 0  &&  n < numeric_traits < Type > :: bit_size ) ;            \
return                                                                      \
  static_cast < Type >                                                      \
    ( static_cast < numeric_traits < Type > :: signed_type > ( x ) >> n ) ; \
}                                                                           \
                                                                            \
inline Type unsigned_shift_right ( Type x, sint n )                         \
                                                                            \
{                                                                           \
assert ( n >= 0  &&  n < numeric_traits < Type > :: bit_size ) ;            \
return x >> n ;                                                             \
}

FOR_BUILTIN_UNSIGNED_INTEGRAL_TYPES(__DEFINE_SHIFT_RIGHT)

#undef __DEFINE_SHIFT_RIGHT



// *** ROTATIONS ***


//

template < class T >
inline T rotate_left ( T x, sint n )

{
assert ( n >= 0  &&  n < numeric_traits < T > :: bit_size ) ;

return   n == 0
       ? x
       :   ( x << n )
         | unsigned_shift_right ( x, numeric_traits < T > :: bit_size - n ) ;
}


//

template < class T >
inline T rotate_right ( T x, sint n )

{
assert ( n >= 0  &&  n < numeric_traits < T > :: bit_size ) ;

return   n == 0
       ? x
       :   unsigned_shift_right ( x, n )
         | ( x << ( numeric_traits < T > :: bit_size - n ) ) ;
}



// *** HALFS ***


//

template < class T >
inline T generic_low_half ( T x )

{
static_assert ( ( numeric_traits < T > :: bit_size & 1 ) == 0,
                "Odd bit size." ) ;

return
  x & ( ( T ( 1 ) << ( numeric_traits < T > :: bit_size >> 1 ) ) - T ( 1 ) ) ;
}


//

template < class T >
inline T generic_low_half_high ( T x )

{
static_assert ( ( numeric_traits < T > :: bit_size & 1 ) == 0,
                "Odd bit size." ) ;

return T ( x << ( numeric_traits < T > :: bit_size >> 1 ) ) ;
}


//

template < class T >
inline T generic_high_half ( T x )

{
static_assert ( ( numeric_traits < T > :: bit_size & 1 ) == 0,
                "Odd bit size." ) ;

return unsigned_shift_right ( x, numeric_traits < T > :: bit_size >> 1 ) ;
}


//

#define __DEFINE_HALFS(Type)         \
                                     \
inline Type low_half ( Type x )      \
                                     \
{                                    \
return generic_low_half ( x ) ;      \
}                                    \
                                     \
inline Type low_half_high ( Type x ) \
                                     \
{                                    \
return generic_low_half_high ( x ) ; \
}                                    \
                                     \
inline Type high_half ( Type x )     \
                                     \
{                                    \
return generic_high_half ( x ) ;     \
}

FOR_BUILTIN_INTEGRAL_TYPES(__DEFINE_HALFS)

#undef __DEFINE_HALFS



// *** REVERSE ***


//

extern const unsigned char __char_reversed [ ] ;


//

#define __DEFINE_REVERSE(Type)          \
                                        \
inline Type reverse ( Type x )          \
                                        \
{                                       \
return __char_reversed [ uint ( x ) ] ; \
}

FOR_BUILTIN_CHAR_TYPES(__DEFINE_REVERSE)

#undef __DEFINE_REVERSE


//

#define __DEFINE_REVERSE(Type)                  \
                                                \
inline Type reverse ( Type x )                  \
                                                \
{                                               \
Type result = __char_reversed [ x & 0xff ] ;    \
                                                \
for ( sint i = 1 ; i < sizeof ( Type ) ; ++ i ) \
  {                                             \
  x >>= 8 ;                                     \
  result <<= 8 ;                                \
  result |= __char_reversed [ x & 0xff ] ;      \
  }                                             \
                                                \
return result ;                                 \
}

FOR_BUILTIN_NONCHAR_INTEGRAL_TYPES(__DEFINE_REVERSE)

#undef __DEFINE_REVERSE



// *** UNSIGNED_DOUBLE_MULTIPLIER ***


//

template < class T, bool HasDoubleSizeType >
class unsigned_double_multiplier ;


//

template < class T >
class unsigned_double_multiplier < T, true >

{
public:

  typedef typename numeric_traits < T > :: unsigned_type unsigned_type ;

  static void operate ( unsigned_type a, unsigned_type b, T & h, T & l ) ;

} ;


//

template < class T >
inline void unsigned_double_multiplier < T, true > ::
              operate ( unsigned_type a, unsigned_type b, T & h, T & l )

{
typedef typename numeric_traits < unsigned_type > :: double_size_type
  double_size_type ;

double_size_type r ( double_size_type ( a ) * double_size_type ( b ) ) ;

h = convert_to < T > ( high_half ( r ) ) ;
l = convert_to < T > ( r ) ;
}


//

template < class T >
class unsigned_double_multiplier < T, false >

{
public:

  typedef typename numeric_traits < T > :: unsigned_type unsigned_type ;

  static void operate ( unsigned_type a, unsigned_type b, T & h, T & l ) ;

} ;


//

template < class T >
inline void unsigned_double_multiplier < T, false > ::
              operate ( unsigned_type a, unsigned_type b, T & h, T & l )

{
unsigned_type ah ( high_half ( a ) ),
              al ( low_half ( a ) ),
              bh ( high_half ( b ) ),
              bl ( low_half ( b ) ) ;

unsigned_type rh ( ah * bh ),
              rl ( al * bl ) ;

{
unsigned_type x ( ah * bl ) ;

{
unsigned_type rln ( rl + low_half_high ( x ) ) ;
if ( rln < rl )
  ++ rh ;
rl = rln ;
}

rh += high_half ( x ) ;
}

{
unsigned_type x ( al * bh ) ;

{
unsigned_type rln ( rl + low_half_high ( x ) ) ;
if ( rln < rl )
  ++ rh ;
rl = rln ;
}

rh += high_half ( x ) ;
}

h = convert_to < T > ( rh ) ;
l = convert_to < T > ( rl ) ;
}



// *** UNSIGNED_DOUBLE_MULTIPLY ***


// pre: a > 0, b > 0
// post: (hl) = a * b

template < class T >
inline void unsigned_double_multiply ( T a, T b, T & h, T & l )

{
unsigned_double_multiplier
  < T, numeric_traits < T > :: has_double_size_type > ::
    operate ( a, b, h, l ) ;
}



// *** UNSIGNED_DOUBLE_DIVIDER ***


//

template < class T, bool HasDoubleSizeType >
class unsigned_double_divider ;


//

template < class T >
class unsigned_double_divider < T, true >

{
public:

  typedef typename numeric_traits < T > :: unsigned_type unsigned_type ;

  static T operate ( unsigned_type h, unsigned_type l, unsigned_type b ) ;

} ;


//

template < class T >
inline T unsigned_double_divider < T, true > ::
           operate ( unsigned_type h, unsigned_type l, unsigned_type b )

{
typedef typename numeric_traits < unsigned_type > :: double_size_type
  double_size_type ;

return convert_to < T >
         (   (   (    double_size_type ( h )
                   << numeric_traits < unsigned_type > :: bit_size )
               + double_size_type ( l ) )
           / double_size_type ( b ) ) ;
}


//

template < class T >
class unsigned_double_divider < T, false >

{
public:

  typedef typename numeric_traits < T > :: unsigned_type unsigned_type ;

  static T operate ( unsigned_type h, unsigned_type l, unsigned_type b ) ;

} ;


//

template < class T >
inline T unsigned_double_divider < T, false > ::
           operate ( unsigned_type h, unsigned_type l, unsigned_type b )

{
unsigned_type bh ( high_half ( b ) ),
              bl ( low_half ( b ) ),
              blh ( low_half_high ( b ) ) ;

unsigned_type rh ( h / bh ) ;

{
unsigned_type x ( rh * bl ) ;

unsigned_type mh ( rh * bh + high_half ( x ) ),
              ml ( low_half_high ( x ) ) ;

while ( mh > h  ||  ( mh == h  &&  ml > l ) )
  {

  {
  unsigned_type mln ( ml - blh ) ;
  if ( mln > ml )
    -- mh ;
  ml = mln ;
  }

  mh -= bh ;

  -- rh ;
  }

{
unsigned_type ln ( l - ml ) ;
if ( ln > l )
  -- h ;
l = ln ;
}

h -= mh ;
}

unsigned_type rl ( ( low_half_high ( h ) + high_half ( l ) ) / bh ) ;

{
unsigned_type x ( rl * bh ) ;

unsigned_type mh ( high_half ( x ) ),
              ml ( rl * bl ) ;

{
unsigned_type mln ( ml + low_half_high ( x ) ) ;
if ( mln < ml )
  ++ mh ;
ml = mln ;
}

while ( mh > h  ||  ( mh == h  &&  ml > l ) )
  {

  {
  unsigned_type mln ( ml - b ) ;
  if ( mln > ml )
    -- mh ;
  ml = mln ;
  }

  -- rl ;
  }
}

return convert_to < T > ( low_half_high ( rh ) + rl ) ;
}



// *** UNSIGNED_DOUBLE_DIVIDE ***


// pre: b >= 1 << ( bit_size ( T ) - 1 )
//      h < b
//
// returns: (hl) / b

template < class T >
inline T unsigned_double_divide ( T h, T l, T b )

{
#ifndef NDEBUG

typedef typename numeric_traits < T > :: unsigned_type unsigned_type ;

assert (    unsigned_type ( b )
         >=    unsigned_type ( 1 )
            << ( numeric_traits < unsigned_type > :: bit_size - 1 ) ) ;

assert ( unsigned_type ( h ) < unsigned_type ( b ) ) ;

#endif

return unsigned_double_divider
         < T, numeric_traits < T > :: has_double_size_type > ::
           operate ( h, l, b ) ;
}



// *** EXPONENT ***


//

#define __DEFINE_EXPONENT(Type)                                       \
                                                                      \
constexpr sint const_exponent ( Type x )                              \
                                                                      \
{                                                                     \
return x == Type ( 0 ) ? 0 : const_exponent ( Type ( x >> 1 ) ) + 1 ; \
}                                                                     \
                                                                      \
inline sint exponent ( Type x )                                       \
                                                                      \
{                                                                     \
sint result ( 0 ) ;                                                   \
                                                                      \
while ( x != Type ( 0 ) )                                             \
  {                                                                   \
  x >>= 1 ;                                                           \
  ++ result ;                                                         \
  }                                                                   \
                                                                      \
return result ;                                                       \
}

FOR_BUILTIN_UNSIGNED_INTEGRAL_TYPES(__DEFINE_EXPONENT)

#undef __DEFINE_EXPONENT


//

#define __DEFINE_EXPONENT(Type)                                               \
                                                                              \
constexpr sint const_exponent ( Type x )                                      \
                                                                              \
{                                                                             \
return                                                                        \
    x < Type ( 0 )                                                            \
  ? const_exponent                                                            \
      ( static_cast < numeric_traits < Type > :: unsigned_type > ( - x ) )    \
  : const_exponent                                                            \
      ( static_cast < numeric_traits < Type > :: unsigned_type > ( x ) ) ;    \
}                                                                             \
                                                                              \
inline sint exponent ( Type x )                                               \
                                                                              \
{                                                                             \
if ( x < Type ( 0 ) )                                                         \
  x = - x ;                                                                   \
                                                                              \
return exponent                                                               \
         ( static_cast < numeric_traits < Type > :: unsigned_type > ( x ) ) ; \
}



FOR_BUILTIN_SIGNED_INTEGRAL_TYPES(__DEFINE_EXPONENT)

#undef __DEFINE_EXPONENT


//

#define __DEFINE_EXPONENT(Type)     \
                                    \
inline sint exponent ( Type x )     \
                                    \
{                                   \
int e ;                             \
frexp ( x, & e ) ;                  \
return static_cast < sint > ( e ) ; \
}

FOR_BUILTIN_FLOATING_POINT_TYPES(__DEFINE_EXPONENT)

#undef __DEFINE_EXPONENT



// *** IS_NEGATIVE ***


template < class T >
inline bool is_negative ( const T & x )

{
return x < T ( 0 ) ;
}



// *** ABS ***


template < class T >
inline T abs ( const T & x )

{
return is_negative ( x ) ? - x : x ;
}



// *** SQR ***


//

template < class T >
inline T sqr ( const T & x )

{
return x * x ;
}


//

template < class T, class Operation >
inline T sqr ( const T & x, Operation operation )

{
return operation ( x, x ) ;
}



// *** POWER ***


// pre: exponent > 0
//
// returns: base^exponent (using operation)

template < class Base, class Exponent, class Operation >
Base positive_power ( Base base, Exponent exponent, Operation operation )

{
assert ( exponent > Exponent ( 0 ) ) ;

while ( ( convert_to < int > ( exponent ) & 1 ) == 0 )
  {
  exponent >>= 1 ;
  base = operation ( base, base ) ;
  }

Base result ( base ) ;

for ( ; ; )
  {
  exponent >>= 1 ;

  if ( exponent == Exponent ( 0 ) )
    return result ;

  base = operation ( base, base ) ;

  if ( ( convert_to < int > ( exponent ) & 1 ) != 0 )
    result = operation ( result, base ) ;
  }
}


// pre: exponent > 0
//
// returns: base^exponent

template < class Base, class Exponent >
inline Base positive_power ( const Base & base, const Exponent & exponent )

{
return positive_power ( base, exponent, multiplies < Base > ( ) ) ;
}


// pre: exponent >= 0
//
// returns: base^exponent (using operation)

template < class Base, class Exponent, class Operation >
inline Base
  power ( const Base & base, const Exponent & exponent, Operation operation )

{
return   exponent == Exponent ( 0 )
       ? Base ( 1 )
       : positive_power ( base, exponent, operation ) ;
}


// returns: base^exponent

template < class Base, class Exponent >
inline Base power ( const Base & base, const Exponent & exponent )

{
return   is_negative ( exponent )
       ? Base ( 1 ) / positive_power ( base, - exponent )
       : power ( base, exponent, multiplies < Base > ( ) ) ;
}



// *** INNER_PRODUCT_MULTIPLY ***


template < class T >
inline T inner_product_multiply ( const T & a, const T & b )

{
return a * b ;
}



// *** NORMS & DISTANCES ***


//

template < class T >
inline auto l1_norm ( const T & x )

{
return abs ( x ) ;
}


//

template < class T >
inline auto l1_distance ( const T & a, const T & b )

{
return l1_norm ( b - a ) ;
}


//

template < class T >
inline auto sqr_l2_norm ( const T & x )

{
return sqr ( x ) ;
}


//

template < class T >
inline auto sqr_l2_distance ( const T & a, const T & b )

{
return sqr_l2_norm ( b - a ) ;
}


//

template < class T >
inline auto l2_norm ( const T & x )

{
return abs ( x ) ;
}


//

template < class T >
inline auto l2_distance ( const T & a, const T & b )

{
return l2_norm ( b - a ) ;
}


//

template < class T >
inline auto linf_norm ( const T & x )

{
return abs ( x ) ;
}


//

template < class T >
inline auto linf_distance ( const T & a, const T & b )

{
return linf_norm ( b - a ) ;
}



// *** GCD ***


//

template < class T >
inline void normalize_gcd ( T & /* gcd */ )

{
}


//

#define __DEFINE_NORMALIZE_GCD(Type)     \
                                         \
inline void normalize_gcd ( Type & gcd ) \
                                         \
{                                        \
if ( gcd < Type ( 0 ) )                  \
  gcd = - gcd ;                          \
}

FOR_BUILTIN_SIGNED_INTEGRAL_TYPES(__DEFINE_NORMALIZE_GCD)

#undef __DEFINE_NORMALIZE_GCD


// returns: gcd ( a, b ) (unnormalized)

template < class T >
T raw_gcd ( T a, T b )

{
if ( b == T ( 0 ) )
  return a ;

T q, r ;

for ( ; ; )
  {
  divmod ( a, b, q, r ) ;

  if ( r == T ( 0 ) )
    return b ;

  a = b ;
  b = r ;
  }
}


//

template < class T >
inline T gcd ( const T & a, const T & b )

{
T g ( raw_gcd ( a, b ) ) ;
normalize_gcd ( g ) ;
return g ;
}



// *** GCD_EXT ***


//

template < class T >
inline void normalize_gcd_ext ( T & /* c */, T & /* d */, T & /* gcd */ )

{
}


//

#define __DEFINE_NORMALIZE_GCD_EXT(Type)                         \
                                                                 \
inline void normalize_gcd_ext ( Type & c, Type & d, Type & gcd ) \
                                                                 \
{                                                                \
if ( gcd < Type ( 0 ) )                                          \
  {                                                              \
  c = - c ;                                                      \
  d = - d ;                                                      \
  gcd = - gcd ;                                                  \
  }                                                              \
}

FOR_BUILTIN_SIGNED_INTEGRAL_TYPES(__DEFINE_NORMALIZE_GCD_EXT)

#undef __DEFINE_NORMALIZE_GCD_EXT


// post: a * c + b * d == gcd == gcd ( a, b ) (unnormalized)

template < class T >
void raw_gcd_ext ( T a, T b, T & c, T & d, T & gcd )

{
if ( b == T ( 0 ) )
  {
  c = T ( 1 ) ;
  d = T ( 0 ) ;
  gcd = a ;
  return ;
  }

c = T ( 0 ) ;
d = T ( 1 ) ;

T cl ( 1 ),
  dl ( 0 ) ;

for ( ; ; )
  {
  T q, r ;

  divmod ( a, b, q, r ) ;

  if ( r == T ( 0 ) )
    {
    gcd = b ;
    return ;
    }

  a = b ;
  b = r ;

  T ca ( c ),
    da ( d ) ;

  c = cl - q * c ;
  d = dl - q * d ;

  cl = ca ;
  dl = da ;
  }
}


//

template < class T >
inline void gcd_ext ( const T & a, const T & b, T & c, T & d, T & gcd )

{
raw_gcd_ext ( a, b, c, d, gcd ) ;
normalize_gcd_ext ( c, d, gcd ) ;
}



// *** PIVOTING_COMPARE ***


//

template < class T >
class pivoting_compare ;


//

#define __DEFINE_PIVOTING_COMPARE(Type)                      \
template < >                                                 \
class pivoting_compare < Type >                              \
                                                             \
{                                                            \
public:                                                      \
                                                             \
  bool operator ( ) ( const Type & a, const Type & b ) const \
    { return abs ( a ) < abs ( b ) ; }                       \
                                                             \
} ;

FOR_BUILTIN_FLOATING_POINT_TYPES(__DEFINE_PIVOTING_COMPARE)

#undef __DEFINE_PIVOTING_COMPARE



#endif
