// Copyright Ivan Stanojevic 2023.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __MUTEX_H

#define __MUTEX_H



#include <mutex>

#include "indir.h"
#include "chrono.h"



typedef std :: mutex                 unmovable_mutex ;
typedef std :: recursive_mutex       unmovable_recursive_mutex ;
typedef std :: timed_mutex           unmovable_timed_mutex ;
typedef std :: recursive_timed_mutex unmovable_recursive_timed_mutex ;

using std :: defer_lock_t ;
using std :: try_to_lock_t ;
using std :: adopt_lock_t ;

using std :: defer_lock ;
using std :: try_to_lock ;
using std :: adopt_lock ;

using std :: lock_guard ;
using std :: scoped_lock ;
using std :: unique_lock ;

using std :: swap ;

using std :: try_lock ;
using std :: lock ;

using std :: once_flag ;

using std :: call_once ;



// *** MUTEX ***


class mutex

{
private:

  friend class condition_variable ;

  unique_handle < unmovable_mutex > mh ;

public:

  mutex ( ) :
    mh ( unique_handle < unmovable_mutex > :: make ( ) )
    { }

  void lock ( )
    { mh -> lock ( ) ; }

  bool try_lock ( )
    { return mh -> try_lock ( ) ; }

  void unlock ( )
    { mh -> unlock ( ) ; }

  typedef unmovable_mutex :: native_handle_type native_handle_type ;

  native_handle_type native_handle ( ) const
    { return mh -> native_handle ( ) ; }

} ;



// *** RECURSIVE_MUTEX ***


class recursive_mutex

{
private:

  friend class condition_variable ;

  unique_handle < unmovable_recursive_mutex > mh ;

public:

  recursive_mutex ( ) :
    mh ( unique_handle < unmovable_recursive_mutex > :: make ( ) )
    { }

  void lock ( )
    { mh -> lock ( ) ; }

  bool try_lock ( )
    { return mh -> try_lock ( ) ; }

  void unlock ( )
    { mh -> unlock ( ) ; }

  typedef unmovable_recursive_mutex :: native_handle_type native_handle_type ;

  native_handle_type native_handle ( ) const
    { return mh -> native_handle ( ) ; }

} ;



// *** TIMED_MUTEX ***


class timed_mutex

{
private:

  friend class condition_variable ;

  unique_handle < unmovable_timed_mutex > mh ;

public:

  timed_mutex ( ) :
    mh ( unique_handle < unmovable_timed_mutex > :: make ( ) )
    { }

  void lock ( )
    { mh -> lock ( ) ; }

  bool try_lock ( )
    { return mh -> try_lock ( ) ; }

  template < class Rep, class Period >
  bool try_lock_for ( const chrono :: duration < Rep, Period > & rel_time )
    { return mh -> try_lock_for ( rel_time ) ; }

  template < class Clock, class Duration >
  bool try_lock_until
         ( const chrono :: time_point < Clock, Duration > & abs_time )
    { return try_lock_until ( abs_time ) ; }

  void unlock ( )
    { mh -> unlock ( ) ; }

  #ifndef __clang__

  typedef unmovable_timed_mutex :: native_handle_type native_handle_type ;

  native_handle_type native_handle ( ) const
    { return mh -> native_handle ( ) ; }

  #endif

} ;



// *** RECURSIVE_TIMED_MUTEX ***


class recursive_timed_mutex

{
private:

  friend class condition_variable ;

  unique_handle < unmovable_recursive_timed_mutex > mh ;

public:

  recursive_timed_mutex ( ) :
    mh ( unique_handle < unmovable_recursive_timed_mutex > :: make ( ) )
    { }

  void lock ( )
    { mh -> lock ( ) ; }

  bool try_lock ( )
    { return mh -> try_lock ( ) ; }

  template < class Rep, class Period >
  bool try_lock_for ( const chrono :: duration < Rep, Period > & rel_time )
    { return mh -> try_lock_for ( rel_time ) ; }

  template < class Clock, class Duration >
  bool try_lock_until
         ( const chrono :: time_point < Clock, Duration > & abs_time )
    { return try_lock_until ( abs_time ) ; }

  void unlock ( )
    { mh -> unlock ( ) ; }

  #ifndef __clang__

  typedef unmovable_recursive_timed_mutex :: native_handle_type
          native_handle_type ;

  native_handle_type native_handle ( ) const
    { return mh -> native_handle ( ) ; }

  #endif

} ;



#endif
