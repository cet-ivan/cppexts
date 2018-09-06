// Copyright Ivan Stanojevic 2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __CONDITION_VARIABLE_H

#define __CONDITION_VARIABLE_H



#include "compspec.h"

#include <condition_variable>

#include "indir.h"
#include "mutex.h"



typedef std :: condition_variable     unmovable_condition_variable ;
typedef std :: condition_variable_any unmovable_condition_variable_any ;

using std :: notify_all_at_thread_exit ;

using std :: cv_status ;



// *** CONDITION_VARIABLE ***


class condition_variable

{
private:

  class local_lock : public unique_lock < unmovable_mutex >

  {
  public:

    local_lock ( unique_lock < :: mutex > & lock ) :
      unique_lock < unmovable_mutex > ( * lock.mutex ( ) -> mh, adopt_lock )
      { }

    ~local_lock ( )
      { release ( ) ; }

    local_lock ( const local_lock & ) = delete ;
    local_lock ( local_lock && ) = delete ;
    local_lock & operator = ( const local_lock & ) = delete ;
    local_lock & operator = ( local_lock && ) = delete ;

  } ;


  unique_handle < unmovable_condition_variable > cvh ;

public:

  condition_variable ( ) :
    cvh ( unique_handle < unmovable_condition_variable > :: make ( ) )
    { }

  void notify_one ( ) noexcept
    { cvh -> notify_one ( ) ; }

  void notify_all ( ) noexcept
    { cvh -> notify_all ( ) ; }

  void wait ( unique_lock < mutex > & lock )
    { local_lock ll ( lock ) ;
      cvh -> wait ( ll ) ; }

  template < class Predicate >
  void wait ( unique_lock < mutex > & lock, Predicate pred )
    { local_lock ll ( lock ) ;
      cvh -> wait ( ll, pred ) ; }

  template < class Clock, class Duration >
  cv_status wait_until
              ( unique_lock < mutex > & lock,
                const chrono :: time_point < Clock, Duration > & abs_time )
    { local_lock ll ( lock ) ;
      return wait_until ( ll, abs_time ) ; }

  template < class Clock, class Duration, class Predicate >
  bool wait_until ( unique_lock < mutex > & lock,
                    const chrono :: time_point < Clock, Duration > & abs_time,
                    Predicate pred )
    { local_lock ll ( lock ) ;
      return wait_until ( ll, abs_time, pred ) ; }

  template < class Rep, class Period >
  cv_status wait_for ( unique_lock < mutex > & lock,
                       const chrono :: duration < Rep, Period > & rel_time )
     { local_lock ll ( lock ) ;
       return wait_for ( ll, rel_time ) ; }

  template < class Rep, class Period, class Predicate >
  bool wait_for ( unique_lock < mutex > & lock,
                  const chrono :: duration < Rep, Period > & rel_time,
                  Predicate pred )
     { local_lock ll ( lock ) ;
       return wait_for ( ll, rel_time, pred ) ; }

  typedef unmovable_condition_variable :: native_handle_type
          native_handle_type ;

  native_handle_type native_handle ( )
    { return cvh -> native_handle ( ) ; }

} ;



// *** CONDITION_VARIABLE_ANY ***


class condition_variable_any

{
private:

  unique_handle < unmovable_condition_variable_any > cvh ;

public:

  condition_variable_any ( ) :
    cvh ( unique_handle < unmovable_condition_variable_any > :: make ( ) )
    { }

  void notify_one ( ) noexcept
    { cvh -> notify_one ( ) ; }

  void notify_all ( ) noexcept
    { cvh -> notify_all ( ) ; }

  template < class Lock >
  void wait ( Lock & lock )
    { cvh -> wait ( lock ) ; }

  template < class Lock, class Predicate >
  void wait ( Lock & lock, Predicate pred )
    { cvh -> wait ( lock, pred ) ; }

  template < class Lock, class Clock, class Duration >
  cv_status wait_until
              ( Lock & lock,
                const chrono :: time_point < Clock, Duration > & abs_time )
    { return cvh -> wait_until ( lock, abs_time ) ; }

  template < class Lock, class Clock, class Duration, class Predicate >
  bool wait_until ( Lock & lock,
                    const chrono :: time_point < Clock, Duration > & abs_time,
                    Predicate pred )
    { return cvh -> wait_until ( lock, abs_time, pred ) ; }

  template < class Lock, class Rep, class Period >
  cv_status wait_for ( Lock & lock,
                       const chrono :: duration < Rep, Period > & rel_time )
    { return cvh -> wait_for ( lock, rel_time ) ; }

  template < class Lock, class Rep, class Period, class Predicate >
  bool wait_for ( Lock & lock,
                  const chrono :: duration < Rep, Period > & rel_time,
                  Predicate pred )
    { return cvh -> wait_for ( lock, rel_time, pred ) ; }

} ;



#endif
