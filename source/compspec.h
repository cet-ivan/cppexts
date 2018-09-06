// Copyright Ivan Stanojevic 2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __COMPSPEC_H

#define __COMPSPEC_H



// *** COMPILER IDENTIFICATION ***


#if defined(__clang__)
  #define __clang_compiler__
#elif defined(__MINGW32__)
  #define __mingw_compiler__
#elif defined(__GNUC__)
  #define __gnu_compiler__
#endif



// *** SINGLE WORD TYPE NAMES ***


typedef signed char signed_char ;
typedef unsigned char unsigned_char ;
typedef unsigned short unsigned_short ;
typedef unsigned long unsigned_long ;
typedef long long long_long ;
typedef unsigned long long unsigned_long_long ;
typedef long double long_double ;



// *** FOR_BUILTIN_SIGNED_INTEGRAL_TYPES ***


#define FOR_BUILTIN_SIGNED_INTEGRAL_TYPES(Macro) \
Macro(char)                                      \
Macro(signed_char)                               \
Macro(short)                                     \
Macro(int)                                       \
Macro(long)                                      \
Macro(long_long)



// *** FOR_BUILTIN_SIGNED_INTEGRAL_TYPES_1 ***


#define FOR_BUILTIN_SIGNED_INTEGRAL_TYPES_1(Macro,Arg) \
Macro(char,Arg)                                        \
Macro(signed_char,Arg)                                 \
Macro(short,Arg)                                       \
Macro(int,Arg)                                         \
Macro(long,Arg)                                        \
Macro(long_long,Arg)



// *** FOR_BUILTIN_UNSIGNED_INTEGRAL_TYPES ***


#define FOR_BUILTIN_UNSIGNED_INTEGRAL_TYPES(Macro) \
Macro(unsigned_char)                               \
Macro(unsigned_short)                              \
Macro(unsigned)                                    \
Macro(unsigned_long)                               \
Macro(unsigned_long_long)



// *** FOR_BUILTIN_UNSIGNED_INTEGRAL_TYPES_1 ***


#define FOR_BUILTIN_UNSIGNED_INTEGRAL_TYPES_1(Macro,Arg) \
Macro(unsigned_char,Arg)                                 \
Macro(unsigned_short,Arg)                                \
Macro(unsigned,Arg)                                      \
Macro(unsigned_long,Arg)                                 \
Macro(unsigned_long_long,Arg)



// *** FOR_BUILTIN_INTEGRAL_TYPES ***


#define FOR_BUILTIN_INTEGRAL_TYPES(Macro)  \
FOR_BUILTIN_SIGNED_INTEGRAL_TYPES(Macro)   \
FOR_BUILTIN_UNSIGNED_INTEGRAL_TYPES(Macro)



// *** FOR_BUILTIN_INTEGRAL_TYPES_1 ***


#define FOR_BUILTIN_INTEGRAL_TYPES_1(Macro,Arg)  \
FOR_BUILTIN_SIGNED_INTEGRAL_TYPES_1(Macro,Arg)   \
FOR_BUILTIN_UNSIGNED_INTEGRAL_TYPES_1(Macro,Arg)



// *** FOR_BUILTIN_FLOATING_POINT_TYPES ***


#define FOR_BUILTIN_FLOATING_POINT_TYPES(Macro) \
Macro(float)                                    \
Macro(double)                                   \
Macro(long_double)



// *** FOR_BUILTIN_FLOATING_POINT_TYPES_1 ***


#define FOR_BUILTIN_FLOATING_POINT_TYPES_1(Macro,Arg) \
Macro(float,Arg)                                      \
Macro(double,Arg)                                     \
Macro(long_double,Arg)



// *** FOR_BUILTIN_NUMBER_TYPES ***


#define FOR_BUILTIN_NUMBER_TYPES(Macro) \
FOR_BUILTIN_INTEGRAL_TYPES(Macro)       \
FOR_BUILTIN_FLOATING_POINT_TYPES(Macro)



// *** FOR_BUILTIN_NUMBER_TYPES_1 ***


#define FOR_BUILTIN_NUMBER_TYPES_1(Macro,Arg) \
FOR_BUILTIN_INTEGRAL_TYPES_1(Macro,Arg)       \
FOR_BUILTIN_FLOATING_POINT_TYPES_1(Macro,Arg)



// *** FOR_BUILTIN_SIGNED_AND_UNSIGNED_INTEGRAL_TYPES ***


#define FOR_BUILTIN_SIGNED_AND_UNSIGNED_INTEGRAL_TYPES(Macro) \
Macro(char,unsigned_char)                                     \
Macro(signed_char,unsigned_char)                              \
Macro(short,unsigned_short)                                   \
Macro(int,unsigned)                                           \
Macro(long,unsigned_long)                                     \
Macro(long_long,unsigned_long_long)



// *** FOR_BUILTIN_UNSIGNED_AND_SIGNED_INTEGRAL_TYPES ***


#define FOR_BUILTIN_UNSIGNED_AND_SIGNED_INTEGRAL_TYPES(Macro) \
Macro(unsigned_char,signed_char)                              \
Macro(unsigned_short,short)                                   \
Macro(unsigned,int)                                           \
Macro(unsigned_long,long)                                     \
Macro(unsigned_long_long,long_long)



// *** FOR_BUILTIN_INTEGRAL_TYPES_AND_DOUBLE_SIZE_TYPES ***


#ifdef __LP64__

#define FOR_BUILTIN_INTEGRAL_TYPES_AND_DOUBLE_SIZE_TYPES(Macro) \
Macro(char,short)                                               \
Macro(signed_char,short)                                        \
Macro(unsigned_char,unsigned_short)                             \
Macro(short,int)                                                \
Macro(unsigned_short,unsigned)                                  \
Macro(int,long)                                                 \
Macro(unsigned,unsigned_long)

#else

#define FOR_BUILTIN_INTEGRAL_TYPES_AND_DOUBLE_SIZE_TYPES(Macro) \
Macro(char,short)                                               \
Macro(signed_char,short)                                        \
Macro(unsigned_char,unsigned_short)                             \
Macro(short,int)                                                \
Macro(unsigned_short,unsigned)                                  \
Macro(int,long_long)                                            \
Macro(unsigned,unsigned_long_long)                              \
Macro(long,long_long)                                           \
Macro(unsigned_long,unsigned_long_long)

#endif



// *** FOR_BUILTIN_NUMBER_TYPES_T1_LESS_T2 ***


#define FOR_BUILTIN_NUMBER_TYPES_T1_LESS_T2(Macro) \
                                                   \
Macro(signed_char,char)                            \
Macro(signed_char,unsigned_char)                   \
Macro(signed_char,short)                           \
Macro(signed_char,unsigned_short)                  \
Macro(signed_char,int)                             \
Macro(signed_char,unsigned)                        \
Macro(signed_char,long)                            \
Macro(signed_char,unsigned_long)                   \
Macro(signed_char,long_long)                       \
Macro(signed_char,unsigned_long_long)              \
Macro(signed_char,float)                           \
Macro(signed_char,double)                          \
Macro(signed_char,long_double)                     \
                                                   \
Macro(char,unsigned_char)                          \
Macro(char,short)                                  \
Macro(char,unsigned_short)                         \
Macro(char,int)                                    \
Macro(char,unsigned)                               \
Macro(char,long)                                   \
Macro(char,unsigned_long)                          \
Macro(char,long_long)                              \
Macro(char,unsigned_long_long)                     \
Macro(char,float)                                  \
Macro(char,double)                                 \
Macro(char,long_double)                            \
                                                   \
Macro(unsigned_char,short)                         \
Macro(unsigned_char,unsigned_short)                \
Macro(unsigned_char,int)                           \
Macro(unsigned_char,unsigned)                      \
Macro(unsigned_char,long)                          \
Macro(unsigned_char,unsigned_long)                 \
Macro(unsigned_char,long_long)                     \
Macro(unsigned_char,unsigned_long_long)            \
Macro(unsigned_char,float)                         \
Macro(unsigned_char,double)                        \
Macro(unsigned_char,long_double)                   \
                                                   \
Macro(short,unsigned_short)                        \
Macro(short,int)                                   \
Macro(short,unsigned)                              \
Macro(short,long)                                  \
Macro(short,unsigned_long)                         \
Macro(short,long_long)                             \
Macro(short,unsigned_long_long)                    \
Macro(short,float)                                 \
Macro(short,double)                                \
Macro(short,long_double)                           \
                                                   \
Macro(unsigned_short,int)                          \
Macro(unsigned_short,unsigned)                     \
Macro(unsigned_short,long)                         \
Macro(unsigned_short,unsigned_long)                \
Macro(unsigned_short,long_long)                    \
Macro(unsigned_short,unsigned_long_long)           \
Macro(unsigned_short,float)                        \
Macro(unsigned_short,double)                       \
Macro(unsigned_short,long_double)                  \
                                                   \
Macro(int,unsigned)                                \
Macro(int,long)                                    \
Macro(int,unsigned_long)                           \
Macro(int,long_long)                               \
Macro(int,unsigned_long_long)                      \
Macro(int,float)                                   \
Macro(int,double)                                  \
Macro(int,long_double)                             \
                                                   \
Macro(unsigned,long)                               \
Macro(unsigned,unsigned_long)                      \
Macro(unsigned,long_long)                          \
Macro(unsigned,unsigned_long_long)                 \
Macro(unsigned,float)                              \
Macro(unsigned,double)                             \
Macro(unsigned,long_double)                        \
                                                   \
Macro(long,unsigned_long)                          \
Macro(long,long_long)                              \
Macro(long,unsigned_long_long)                     \
Macro(long,float)                                  \
Macro(long,double)                                 \
Macro(long,long_double)                            \
                                                   \
Macro(unsigned_long,long_long)                     \
Macro(unsigned_long,unsigned_long_long)            \
Macro(unsigned_long,float)                         \
Macro(unsigned_long,double)                        \
Macro(unsigned_long,long_double)                   \
                                                   \
Macro(long_long,unsigned_long_long)                \
Macro(long_long,float)                             \
Macro(long_long,double)                            \
Macro(long_long,long_double)                       \
                                                   \
Macro(unsigned_long_long,float)                    \
Macro(unsigned_long_long,double)                   \
Macro(unsigned_long_long,long_double)              \
                                                   \
Macro(float,double)                                \
Macro(float,long_double)                           \
                                                   \
Macro(double,long_double)



#endif
