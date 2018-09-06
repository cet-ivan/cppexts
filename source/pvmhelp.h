// Copyright Ivan Stanojevic 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __PVMHELP_H

#define __PVMHELP_H



#include <pvm3.h>
#include <time.h>

#include "cstddef.h"
#include "iterator.h"
#include "utility.h"
#include "vector.h"
#include "deque.h"
#include "list.h"
#include "set.h"
#include "map.h"
#include "exint.h"
#include "chrono.h"

#include "numbase.h"



// *** CONFIGURATION ***


// #define PVM_SIGNAL_HANDLING



// *** ERRORS ***


#ifdef PVM_SIGNAL_HANDLING

class signal_setup_error { } ;

#endif

class pvm_error { } ;



// *** PVM_HELPER ***


class pvm_helper

{
private:

#ifdef PVM_SIGNAL_HANDLING

  static volatile bool signal_received_ ;
  static void signal_handler ( int ) ;

#endif

  static int my_task_id_ ;


  class initializer

  {
  public:

    initializer ( ) ;
    ~initializer ( ) ;

  } ;

  static initializer init ;

public:

#ifdef PVM_SIGNAL_HANDLING

  static bool signal_received ( )
    { return signal_received_ ; }

#else

  static bool signal_received ( )
    { return false ; }

#endif

  static int my_task_id ( )
    { return my_task_id_ ; }

} ;



// *** PACKING AND UNPACKING ***


//

#define __DEFINE_PVM_FUNCTIONS(Type,NameSuffix)              \
                                                             \
inline void pvm_pack ( Type x )                              \
                                                             \
{                                                            \
int info = pvm_pk##NameSuffix ( & x, 1, 1 ) ;                \
if ( info < 0 )                                              \
  throw pvm_error ( ) ;                                      \
}                                                            \
                                                             \
inline void pvm_unpack ( Type & x )                          \
                                                             \
{                                                            \
int info = pvm_upk##NameSuffix ( & x, 1, 1 ) ;               \
if ( info < 0 )                                              \
  throw pvm_error ( ) ;                                      \
}                                                            \
                                                             \
inline void pvm_pack_array ( const Type * x, size_t n )      \
                                                             \
{                                                            \
assert ( n <= numeric_limits < int > :: max ( ) ) ;          \
int info = pvm_pk##NameSuffix ( const_cast < Type * > ( x ), \
                                static_cast < int > ( n ),   \
                                1 ) ;                        \
if ( info < 0 )                                              \
  throw pvm_error ( ) ;                                      \
}                                                            \
                                                             \
inline void pvm_unpack_array ( Type * x, size_t n )          \
                                                             \
{                                                            \
assert ( n <= numeric_limits < int > :: max ( ) ) ;          \
int info = pvm_upk##NameSuffix ( x,                          \
                                 static_cast < int > ( n ),  \
                                 1 ) ;                       \
if ( info < 0 )                                              \
  throw pvm_error ( ) ;                                      \
}

__DEFINE_PVM_FUNCTIONS(char,byte)
__DEFINE_PVM_FUNCTIONS(short,short)
__DEFINE_PVM_FUNCTIONS(unsigned short,ushort)
__DEFINE_PVM_FUNCTIONS(int,int)
__DEFINE_PVM_FUNCTIONS(unsigned int,uint)
__DEFINE_PVM_FUNCTIONS(long,long)
__DEFINE_PVM_FUNCTIONS(unsigned long,ulong)
__DEFINE_PVM_FUNCTIONS(float,float)
__DEFINE_PVM_FUNCTIONS(double,double)

#undef __DEFINE_PVM_FUNCTIONS


//

inline void pvm_pack ( signed char x )

{
pvm_pack ( static_cast < char > ( x ) ) ;
}


//

inline void pvm_unpack ( signed char & x )

{
pvm_unpack ( reinterpret_cast < char & > ( x ) ) ;
}


//

inline void pvm_pack_array ( const signed char * x, size_t n )

{
pvm_pack_array ( reinterpret_cast < const char * > ( x ), n ) ;
}


//

inline void pvm_unpack_array ( signed char * x, size_t n )

{
pvm_unpack_array ( reinterpret_cast < char * > ( x ), n ) ;
}


//

inline void pvm_pack ( unsigned char x )

{
pvm_pack ( static_cast < char > ( x ) ) ;
}


//

inline void pvm_unpack ( unsigned char & x )

{
pvm_unpack ( reinterpret_cast < char & > ( x ) ) ;
}


//

inline void pvm_pack_array ( const unsigned char * x, size_t n )

{
pvm_pack_array ( reinterpret_cast < const char * > ( x ), n ) ;
}


//

inline void pvm_unpack_array ( unsigned char * x, size_t n )

{
pvm_unpack_array ( reinterpret_cast < char * > ( x ), n ) ;
}


//

inline void pvm_pack ( const char * x )

{
int info = pvm_pkstr ( const_cast < char * > ( x ) ) ;
if ( info < 0 )
  throw pvm_error ( ) ;
}


//

inline void pvm_unpack ( char * x )

{
int info = pvm_upkstr ( x ) ;
if ( info < 0 )
  throw pvm_error ( ) ;
}


//

template < class T1, class T2 >
inline void pvm_pack ( const pair < T1, T2 > & x )

{
pvm_pack ( x.first ) ;
pvm_pack ( x.second ) ;
}


//

template < class T1, class T2 >
inline void pvm_unpack ( pair < T1, T2 > & x )

{
pvm_unpack ( x.first ) ;
pvm_unpack ( x.second ) ;
}


//

template < class T1, class T2 >
inline void pvm_unpack ( pair < const T1, T2 > & x )

{
pvm_unpack ( const_cast < T1 & > ( x.first ) ) ;
pvm_unpack ( x.second ) ;
}


//

template < class InputIterator >
void pvm_pack_range ( InputIterator first, InputIterator last )

{
while ( first != last )
  {
  pvm_pack ( * first ) ;
  ++ first ;
  }
}


//

template < class ForwardIterator >
void pvm_unpack_range ( ForwardIterator first, ForwardIterator last )

{
while ( first != last )
  {
  typename iterator_traits < ForwardIterator > :: assignment_type x ;
  pvm_unpack ( x ) ;
  * first = x ;
  ++ first ;
  }
}


//

template < class InputIterator, class Size >
void pvm_pack_n ( InputIterator first, Size n )

{
while ( n > 0 )
  {
  pvm_pack ( * first ) ;
  ++ first ;
  -- n ;
  }
}


//

template < class OutputIterator, class Size >
void pvm_unpack_n ( OutputIterator first, Size n )

{
while ( n > 0 )
  {
  typename iterator_traits < OutputIterator > :: assignment_type x ;
  pvm_unpack ( x ) ;
  * first = x ;
  ++ first ;
  -- n ;
  }
}


//

template < class Container >
inline void pvm_pack_container ( const Container & c )

{
pvm_pack ( static_cast < unsigned long > ( c.size ( ) ) ) ;
pvm_pack_range ( c.begin ( ), c.end ( ) ) ;
}


//

template < class Container >
inline void pvm_unpack_container ( Container & c )

{
unsigned long size ;
pvm_unpack ( size ) ;

Container t ;
pvm_unpack_n ( back_inserter ( t ), size ) ;

c = move ( t ) ;
}


//

template < class AssociativeContainer >
inline void pvm_unpack_associative_container ( AssociativeContainer & a )

{
unsigned long size ;
pvm_unpack ( size ) ;

AssociativeContainer t ;
pvm_unpack_n ( inserter ( t, t.end ( ) ), size ) ;

a = move ( t ) ;
}


//

template < class T, class Allocator >
inline void pvm_pack ( const vector < T, Allocator > & x )

{
pvm_pack_container ( x ) ;
}


//

template < class T, class Allocator >
inline void pvm_unpack ( vector < T, Allocator > & x )

{
unsigned long size ;
pvm_unpack ( size ) ;

vector < T, Allocator > t ;
t.reserve ( size ) ;
pvm_unpack_n ( back_inserter ( t ), size ) ;

x = move ( t ) ;
}


//

template < class T, class Allocator >
inline void pvm_pack ( const deque < T, Allocator > & x )

{
pvm_pack_container ( x ) ;
}


//

template < class T, class Allocator >
inline void pvm_unpack ( deque < T, Allocator > & x )

{
pvm_unpack_container ( x ) ;
}


//

template < class T, class Allocator >
inline void pvm_pack ( const list < T, Allocator > & x )

{
pvm_pack_container ( x ) ;
}


//

template < class T, class Allocator >
inline void pvm_unpack ( list < T, Allocator > & x )

{
pvm_unpack_container ( x ) ;
}


//

template < class Key, class Compare, class Allocator >
inline void pvm_pack ( const set < Key, Compare, Allocator > & x )

{
pvm_pack_container ( x ) ;
}


//

template < class Key, class Compare, class Allocator >
inline void pvm_unpack ( set < Key, Compare, Allocator > & x )

{
pvm_unpack_associative_container ( x ) ;
}


//

template < class Key, class Compare, class Allocator >
inline void pvm_pack ( const multiset < Key, Compare, Allocator > & x )

{
pvm_pack_container ( x ) ;
}


//

template < class Key, class Compare, class Allocator >
inline void pvm_unpack ( multiset < Key, Compare, Allocator > & x )

{
pvm_unpack_associative_container ( x ) ;
}


//

template < class Key, class T, class Compare, class Allocator >
inline void pvm_pack ( const map < Key, T, Compare, Allocator > & x )

{
pvm_pack_container ( x ) ;
}


//

template < class Key, class T, class Compare, class Allocator >
inline void pvm_unpack ( map < Key, T, Compare, Allocator > & x )

{
pvm_unpack_associative_container ( x ) ;
}


//

template < class Key, class T, class Compare, class Allocator >
inline void pvm_pack ( const multimap < Key, T, Compare, Allocator > & x )

{
pvm_pack_container ( x ) ;
}


//

template < class Key, class T, class Compare, class Allocator >
inline void pvm_unpack ( multimap < Key, T, Compare, Allocator > & x )

{
pvm_unpack_associative_container ( x ) ;
}


//

template < class T, class Allocator >
inline void pvm_pack ( const basic_exint < T, Allocator > & x )

{
pvm_pack ( x.data ( ) ) ;
}


//

template < class T, class Allocator >
inline void pvm_unpack ( basic_exint < T, Allocator > & x )

{
vector < T, Allocator > data ;
pvm_unpack ( data ) ;
x = basic_exint < T, Allocator > ( move ( data ) ) ;
}



// *** SENDING AND RECEIVING ***


//

inline void pvm_init_send_buffer ( )

{
int bufid = pvm_initsend ( PvmDataRaw ) ;
if ( bufid < 0 )
  throw pvm_error ( ) ;
}


//

inline void pvm_send_message ( int task_id, int message_tag )

{
int info = pvm_send ( task_id, message_tag ) ;
if ( info < 0 )
  throw pvm_error ( ) ;
}


//

inline void pvm_receive_message ( int task_id, int message_tag )

{
int bufid = pvm_recv ( task_id, message_tag ) ;
if ( bufid < 0 )
  throw pvm_error ( ) ;
}


//

inline bool pvm_nonblocking_receive_message ( int task_id, int message_tag )

{
int bufid = pvm_nrecv ( task_id, message_tag ) ;
if ( bufid < 0 )
  throw pvm_error ( ) ;

return bufid > 0 ;
}


//

template < class Rep, class Period >
inline bool pvm_timed_receive_message
              ( int task_id,
                int message_tag,
                const chrono :: duration < Rep, Period > & timeout )

{
struct timeval tv ;

chrono :: seconds
  s = chrono :: duration_cast < chrono :: seconds > ( timeout ) ;

tv.tv_sec  = static_cast < __time_t > ( s.count ( ) ) ;

tv.tv_usec =
  chrono :: duration_cast < chrono :: microseconds > ( timeout - s ).count ( ) ;

int bufid = pvm_trecv ( task_id, message_tag, & tv ) ;
if ( bufid < 0 )
  throw pvm_error ( ) ;

return bufid > 0 ;
}


//

inline void pvm_get_received_message_info ( int & task_id, int & message_tag )

{
int info = pvm_bufinfo ( pvm_getrbuf ( ), nullptr, & message_tag, & task_id ) ;
if ( info < 0 )
  throw pvm_error ( ) ;
}



// *** DYNAMIC GROUPS ***


//

inline void pvm_join_group ( const char * group )

{
int info = pvm_joingroup ( const_cast < char * > ( group ) ) ;
if ( info < 0 )
  throw pvm_error ( ) ;
}


//

inline void pvm_leave_group ( const char * group )

{
int info = pvm_lvgroup ( const_cast < char * > ( group ) ) ;
if ( info < 0 )
  throw pvm_error ( ) ;
}


//

inline void pvm_broadcast_message ( const char * group, int message_tag )

{
int info = pvm_bcast ( const_cast < char * > ( group ), message_tag ) ;
if ( info < 0  &&  info != PvmNoGroup )
  throw pvm_error ( ) ;
}



#endif
