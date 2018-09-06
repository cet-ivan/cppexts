// Copyright Ivan Stanojevic 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __THREADPOOL_H

#define __THREADPOOL_H



#include "compspec.h"

#include "cstddef.h"
#include "functional.h"
#include "mutex.h"
#include "condition_variable.h"
#include "thread.h"
#include "vector.h"
#include "cassert.h"
#include "type_traits.h"
#include "future.h"



// *** THREAD_POOL ***


class thread_pool

{
public:

  class slot ;

private:

  class pool_data ;


  class worker

  {
  private:

    enum state_t { idle, running, terminating } ;

    mutex mtx ;
    condition_variable cond_var ;

    function < void ( ) > action ;
    state_t state ;

    pool_data * pd ;
    size_t index_ ;

    thread th ;

    void main ( ) ;

  public:

    worker ( pool_data * i_pd, size_t i_index ) :
      mtx ( ),
      cond_var ( ),
      action ( ),
      state ( idle ),
      pd ( i_pd ),
      index_ ( i_index ),
      th ( & worker :: main, this )
      { }

    ~worker ( )
      { {
        lock_guard < mutex > lck ( mtx ) ;
        state = terminating ;
        cond_var.notify_one ( ) ;
        }
        th.join ( ) ; }

    worker ( const worker & ) = delete ;
    worker ( worker && ) = default ;
    worker & operator = ( const worker & ) = delete ;
    worker & operator = ( worker && ) = default ;

    size_t index ( ) const
      { return index_ ; }

    template < class F >
    void run ( F && f )
      { lock_guard < mutex > lck ( mtx ) ;
        #ifdef __gnu_compiler__
        action = bind < void > ( move ( f ) ) ;
        #else
        action = move ( f ) ;
        #endif
        state = running ;
        cond_var.notify_one ( ) ; }

  } ;


  class pool_data

  {
  private:

    mutex mtx ;
    condition_variable cond_var ;

    vector < worker > workers ;
    vector < worker * > free ;
    size_t free_number ;

  public:

    explicit pool_data ( size_t size = 0 ) :
      mtx ( ),
      cond_var ( ),
      workers ( ),
      free ( ),
      free_number ( 0 )
      { workers.reserve ( size ) ;
        free.reserve ( size ) ;
        for ( ; free_number < size ; ++ free_number )
          {
          workers.emplace_back ( this, free_number ) ;
          free.push_back ( & workers.back ( ) ) ;
          } }

    size_t size ( ) const
      { return workers.size ( ) ; }

    void wait ( size_t n )
      { assert ( n <= size ( ) ) ;
        unique_lock < mutex > lck ( mtx ) ;
        while ( free_number < n )
          cond_var.wait ( lck ) ; }

    void get_free ( slot * dest, size_t n )
      { assert ( n <= size ( ) ) ;
        unique_lock < mutex > lck ( mtx ) ;
        while ( free_number < n )
          cond_var.wait ( lck ) ;
        size_t new_free_number = free_number - n ;
        for ( auto iter = free.cbegin ( ) + new_free_number ;
                   iter != free.cbegin ( ) + free_number ;
                   ++ iter )
          {
          dest -> wrk = * iter ;
          ++ dest ;
          }
        free_number = new_free_number ; }

    void put_free ( worker * wrk )
      { lock_guard < mutex > lck ( mtx ) ;
        free [ free_number ] = wrk ;
        ++ free_number ;
        cond_var.notify_all ( ) ; }

  } ;


  template < class Result >
  class monitored_task

  {
  public:

    handle < packaged_task < Result ( ) > > pth ;

    template < class F >
    monitored_task ( F && f ) :
      pth ( handle < packaged_task < Result ( ) > > :: make ( move ( f ) ) )
      { }

    void operator ( ) ( )
      { ( * pth ) ( ) ; }

  } ;


  handle < pool_data > pdh ;

public:

  class slot

  {
  private:

    friend class thread_pool ;

    handle < pool_data > pdh ;
    worker * wrk ;

    slot ( const handle < pool_data > & i_pdh ) :
      pdh ( i_pdh ),
      wrk ( nullptr )
      { }

  public:

    slot ( ) noexcept :
      pdh ( ),
      wrk ( nullptr )
      { }

    ~slot ( )
      { if ( ! pdh.empty ( )  &&  wrk != nullptr )
          pdh -> put_free ( wrk ) ; }

    slot ( const slot & ) = delete ;
    slot ( slot && ) = default ;
    slot & operator = ( const slot & ) = delete ;
    slot & operator = ( slot && ) = default ;

    bool valid ( ) const
      { return ! pdh.empty ( ) ; }

    size_t index ( ) const
      { return valid ( ) ? wrk -> index ( ) : -1 ; }

    template < class F, class ... Args >
    void run ( F && f, Args && ... args )
      { assert ( valid ( ) ) ;
        wrk -> run ( bind < void > ( forward < F > ( f ),
                                     forward < Args > ( args ) ... ) ) ;
        pdh.clear ( ) ; }

    template < class F, class ... Args >
    void run_with_index ( F && f, Args && ... args )
      { assert ( valid ( ) ) ;
        wrk -> run ( bind < void > ( forward < F > ( f ),
                                     forward < Args > ( args ) ... ,
                                     wrk -> index ( ) ) ) ;
        pdh.clear ( ) ; }

    template < class F, class ... Args >
    future < typename result_of < typename decay < F > :: type
                                    ( typename decay < Args > :: type ... ) >
                      :: type >
      run_monitored ( F && f, Args && ... args )
      { assert ( valid ( ) ) ;
        typedef
          typename result_of < typename decay < F > :: type
                                 ( typename decay < Args > :: type ... ) >
                   :: type
          result_type ;
        monitored_task < result_type >
          mt ( bind ( forward < F > ( f ),
                      forward < Args > ( args ) ... ) ) ;
        future < result_type > ft ( mt.pth -> get_future ( ) ) ;
        wrk -> run ( mt ) ;
        pdh.clear ( ) ;
        return ft ; }

    template < class F, class ... Args >
    future < typename result_of < typename decay < F > :: type
                                    ( typename decay < Args > :: type ... ,
                                      size_t ) >
                      :: type >
      run_monitored_with_index ( F && f, Args && ... args )
      { assert ( valid ( ) ) ;
        typedef
          typename result_of < typename decay < F > :: type
                                 ( typename decay < Args > :: type ... ,
                                   size_t ) >
                   :: type
          result_type ;
        monitored_task < result_type >
          mt ( bind ( forward < F > ( f ),
                      forward < Args > ( args ) ... ,
                      wrk -> index ( ) ) ) ;
        future < result_type > ft ( mt.pth -> get_future ( ) ) ;
        wrk -> run ( mt ) ;
        pdh.clear ( ) ;
        return ft ; }

  } ;


  explicit thread_pool ( size_t size = 0 ) :
    pdh ( handle < pool_data > :: make ( size ) )
    { }

  thread_pool ( const thread_pool & ) = delete ;
  thread_pool ( thread_pool && ) = default ;
  thread_pool & operator = ( const thread_pool & ) = delete ;
  thread_pool & operator = ( thread_pool && ) = default ;

  size_t size ( ) const
    { return pdh -> size ( ) ; }

  void wait ( size_t n = 1 )
    { pdh -> wait ( n ) ; }

  void wait_all ( )
    { wait ( size ( ) ) ; }

  slot get_slot ( )
    { slot result ( pdh ) ;
      pdh -> get_free ( & result, 1 ) ;
      return result ; }

  vector < slot > get_slots ( size_t n )
    { vector < slot > result ;
      result.reserve ( n ) ;
      for ( size_t i = 0 ; i < n ; ++ i )
        result.push_back ( slot ( pdh ) ) ;
      pdh -> get_free ( result.data ( ), n ) ;
      return result ; }

  template < class F, class ... Args >
  void run ( F && f, Args && ... args )
    { get_slot ( ).run ( forward < F > ( f ),
                         forward < Args > ( args ) ... ) ; }

  template < class F, class ... Args >
  void run_with_index ( F && f, Args && ... args )
    { get_slot ( ).run_with_index ( forward < F > ( f ),
                                    forward < Args > ( args ) ... ) ; }

  template < class F, class ... Args >
  future < typename result_of < typename decay < F > :: type
                                  ( typename decay < Args > :: type ... ) >
                    :: type >
    run_monitored ( F && f, Args && ... args )
    { return get_slot ( ).run_monitored ( forward < F > ( f ),
                                          forward < Args > ( args ) ... ) ; }

  template < class F, class ... Args >
  future < typename result_of < typename decay < F > :: type
                                  ( typename decay < Args > :: type ... ,
                                    size_t ) >
                    :: type >
    run_monitored_with_index ( F && f, Args && ... args )
    { return get_slot ( ).run_monitored_with_index
                            ( forward < F > ( f ),
                              forward < Args > ( args ) ... ) ; }

} ;



#endif
