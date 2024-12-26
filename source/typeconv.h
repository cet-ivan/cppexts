// Copyright Ivan Stanojevic 2023.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __TYPECONV_H

#define __TYPECONV_H



#include "compspec.h"



// *** TYPE_CONVERTER ***


//

template < class Source, class Destination >
class type_converter

{
public:

  static Destination operate ( const Source & x )
    { return Destination ( x ) ; }

} ;


//

template < class T >
class type_converter < T, T >

{
public:

  static T operate ( T x )
    { return x ; }

} ;


//

#define __DEFINE_TYPE_CONVERTER_1(Source,Destination) \
                                                      \
template < >                                          \
class type_converter < Source, Destination >          \
                                                      \
{                                                     \
public:                                               \
                                                      \
  static Destination operate ( Source x )             \
    { return static_cast < Destination > ( x ) ; }    \
                                                      \
} ;

#define __DEFINE_TYPE_CONVERTER(Destination)                      \
FOR_BUILTIN_NUMBER_TYPES_1(__DEFINE_TYPE_CONVERTER_1,Destination)

FOR_BUILTIN_NUMBER_TYPES(__DEFINE_TYPE_CONVERTER)

#undef __DEFINE_TYPE_CONVERTER
#undef __DEFINE_TYPE_CONVERTER_1



// *** CONVERT_TO ***


//

template < class Destination, class Source >
inline Destination convert_to ( const Source & x )

{
return type_converter < Source, Destination > :: operate ( x ) ;
}


//

#define __DEFINE_CONVERT_TO(Source)                              \
                                                                 \
template < class Destination >                                   \
inline Destination convert_to ( Source x )                       \
                                                                 \
{                                                                \
return type_converter < Source, Destination > :: operate ( x ) ; \
}

FOR_BUILTIN_NUMBER_TYPES(__DEFINE_CONVERT_TO)

#undef __DEFINE_CONVERT_TO



// *** IMPLICIT_CONVERSION ***


//

class implicit_conversion_allowed_t

{
} ;


//

const implicit_conversion_allowed_t implicit_conversion_allowed = { } ;


//

class implicit_conversion_test_ok

{
public:

  typedef implicit_conversion_allowed_t result ;
  static constexpr bool allowed = true ;

} ;


//

template < class From, class To >
class implicit_conversion_test

{
public:

  static constexpr bool allowed = false ;

} ;


//

#define __DEFINE_IMPLICIT_CONVERSION_TEST(From,To)  \
                                                    \
template < >                                        \
class implicit_conversion_test < From, To > :       \
  public implicit_conversion_test_ok                \
                                                    \
{                                                   \
} ;

FOR_BUILTIN_NUMBER_TYPES_T1_LESS_T2(__DEFINE_IMPLICIT_CONVERSION_TEST)

#undef __DEFINE_IMPLICIT_CONVERSION_TEST



#endif
