// Copyright Ivan Stanojevic 2023.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __INDIR_H

#define __INDIR_H



#include "utility.h"
#include "type_traits.h"
#include "cstddef.h"
#include "atomic.h"
#include "cassert.h"



// *** CLONER_BY_CLONE ***


template < class T >
class cloner_by_clone

{
public:

  static T * operate ( const T & x )
    { return x.clone ( ) ; }

} ;



// *** CLONER_BY_CONSTRUCTOR ***


template < class T >
class cloner_by_constructor

{
public:

  static T * operate ( const T & x )
    { return new T ( x ) ; }

} ;



// *** SELECT_CLONER ***


template < class T >
class select_cloner

{
private:

  typedef const char ( & s1 ) [ 1 ] ;
  typedef const char ( & s2 ) [ 2 ] ;

  template < class C, C >
  class type_value ;

  template < class U >
  static s1 test ( const type_value < U * ( U :: * ) ( ) const &,
                                      & U :: clone > * ) ;

  template < class >
  static s2 test ( ... ) ;

public:

  typedef conditional_t < sizeof ( test < T > ( nullptr ) ) == 1,
                          cloner_by_clone < T >,
                          cloner_by_constructor < T > >
    type ;

} ;



// *** CLONER ***


template < class T >
class cloner : public select_cloner < T > :: type

{
} ;



// *** MOVE_CLONER_BY_CLONE ***


template < class T >
class move_cloner_by_clone

{
public:

  static T * operate ( T && x )
    { return move ( x ).clone ( ) ; }

} ;



// *** MOVE_CLONER_BY_CONSTRUCTOR ***


template < class T >
class move_cloner_by_constructor

{
public:

  static T * operate ( T && x )
    { return new T ( move ( x ) ) ; }

} ;



// *** SELECT_MOVE_CLONER ***


template < class T >
class select_move_cloner

{
private:

  typedef const char ( & s1 ) [ 1 ] ;
  typedef const char ( & s2 ) [ 2 ] ;

  template < class C, C >
  class type_value ;

  template < class U >
  static s1 test ( const type_value < U * ( U :: * ) ( ) &&,
                                      & U :: clone > * ) ;

  template < class >
  static s2 test ( ... ) ;

public:

  typedef conditional_t < sizeof ( test < T > ( nullptr ) ) == 1,
                          move_cloner_by_clone < T >,
                          move_cloner_by_constructor < T > >
    type ;

} ;



// *** MOVE_CLONER ***


template < class T >
class move_cloner : public select_move_cloner < T > :: type

{
} ;



// *** HANDLE FORWARD DECLARATIONS ***


template < class T >
class handle ;

template < class T >
bool operator == ( const handle < T > & a, const handle < T > & b ) ;

template < class T >
bool operator < ( const handle < T > & a, const handle < T > & b ) ;

template < class T >
void swap ( handle < T > & a, handle < T > & b ) ;



// *** HANDLE ***


template < class T >
class handle

{
private:

  class object_reference

  {
  public:

    T * object ;
    atomic < size_t > count ;

  } ;


  object_reference * obj_ref ;

  handle ( object_reference * i_obj_ref ) :
    obj_ref ( i_obj_ref )
    { }

  void destroy ( )
    { if ( obj_ref != nullptr  &&  -- obj_ref -> count == 0 )
        {
        delete obj_ref -> object ;
        delete obj_ref ;
        } }

  T * cmp_ptr ( ) const
    { return   obj_ref != nullptr
             ? obj_ref -> object
             : static_cast < T * > ( nullptr ) ; }

public:

  handle ( ) noexcept :
    obj_ref ( nullptr )
    { }

  ~handle ( )
    { destroy ( ) ; }

  handle ( const handle & h ) noexcept :
    obj_ref ( h.obj_ref )
    { if ( obj_ref != nullptr )
        ++ obj_ref -> count ; }

  handle ( handle && h ) noexcept :
    obj_ref ( h.obj_ref )
    { h.obj_ref = nullptr ; }

  handle & operator = ( const handle & h ) noexcept
    { handle ( h ).swap ( * this ) ;
      return * this ; }

  handle & operator = ( handle && h ) noexcept
    { h.swap ( * this ) ;
      h.clear ( ) ;
      return * this ; }

  explicit handle ( const T & x ) :
    obj_ref ( new object_reference )
    { try
        {
        obj_ref -> object = cloner < T > :: operate ( x ) ;
        obj_ref -> count = 1 ;
        }
      catch ( ... )
        {
        delete obj_ref ;
        throw ;
        } }

  explicit handle ( T && x ) :
    obj_ref ( new object_reference )
    { try
        {
        obj_ref -> object = move_cloner < T > :: operate ( move ( x ) ) ;
        obj_ref -> count = 1 ;
        }
      catch ( ... )
        {
        delete obj_ref ;
        throw ;
        } }

  template < class O, class ... Args >
  static handle make ( Args && ... args )
    { object_reference * obj_ref = new object_reference ;
      try
        {
        obj_ref -> object = new O ( forward < Args > ( args ) ... ) ;
        obj_ref -> count = 1 ;
        }
      catch ( ... )
        {
        delete obj_ref ;
        throw ;
        }
      return handle ( obj_ref ) ; }

  template < class ... Args >
  static handle make ( Args && ... args )
    { return make < T > ( forward < Args > ( args ) ... ) ; }

  template < class O, class ... Args >
  void emplace ( Args && ... args )
    { * this = make < O > ( forward < Args > ( args ) ... ) ; }

  template < class ... Args >
  void emplace ( Args && ... args )
    { * this = make ( forward < Args > ( args ) ... ) ; }

  bool empty ( ) const
    { return obj_ref == nullptr ; }

  size_t reference_count ( ) const
    { return obj_ref == nullptr ? 0 : obj_ref -> count ; }

  const T * cptr ( ) const
    { assert ( obj_ref != nullptr ) ;
      return obj_ref -> object ; }

  T * ptr ( ) const
    { assert ( obj_ref != nullptr ) ;
      return obj_ref -> object ; }

  const T & cref ( ) const
    { return * cptr ( ) ; }

  T & ref ( ) const
    { return * ptr ( ) ; }

  T * operator -> ( ) const
    { return ptr ( ) ; }

  T & operator * ( ) const
    { return ref ( ) ; }

  void clear ( )
    { destroy ( ) ;
      obj_ref = nullptr ; }

  void swap ( handle & h )
    { :: swap ( obj_ref, h.obj_ref ) ; }

  void detach ( )
    { if ( obj_ref != nullptr  &&  obj_ref -> count > 1 )
        handle ( cref ( ) ).swap ( * this ) ; }

  friend bool operator == ( const handle & a, const handle & b )
    { return a.cmp_ptr ( ) == b.cmp_ptr ( ) ; }

  friend bool operator < ( const handle & a, const handle & b )
    { return a.cmp_ptr ( ) < b.cmp_ptr ( ) ; }

} ;


//

template < class T >
inline void swap ( handle < T > & a, handle < T > & b )

{
a.swap ( b ) ;
}



// *** UNIQUE_HANDLE FORWARD DECLARATIONS ***


template < class T >
class unique_handle ;

template < class T >
bool operator == ( const unique_handle < T > & a,
                   const unique_handle < T > & b ) ;

template < class T >
bool operator < ( const unique_handle < T > & a,
                  const unique_handle < T > & b ) ;

template < class T >
void swap ( unique_handle < T > & a, unique_handle < T > & b ) ;



// *** UNIQUE_HANDLE ***


template < class T >
class unique_handle

{
private:

  T * object ;

  unique_handle ( T * i_object ) :
    object ( i_object )
    { }

  void destroy ( )
    { if ( object != nullptr )
        delete object ; }

public:

  unique_handle ( ) noexcept :
    object ( nullptr )
    { }

  ~unique_handle ( )
    { destroy ( ) ; }

  unique_handle ( const unique_handle & ) = delete ;

  unique_handle ( unique_handle && h ) noexcept :
    object ( h.object )
    { h.object = nullptr ; }

  unique_handle & operator = ( const unique_handle & ) = delete ;

  unique_handle & operator = ( unique_handle && h ) noexcept
    { if ( & h != this )
        {
        destroy ( ) ;
        object = h.object ;
        h.object = nullptr ;
        }
      return * this ; }

  unique_handle ( const T & x ) :
    object ( cloner < T > :: operate ( x ) )
    { }

  unique_handle ( T && x ) :
    object ( move_cloner < T > :: operate ( move ( x ) ) )
    { }

  template < class O, class ... Args >
  static unique_handle make ( Args && ... args )
    { return unique_handle ( new O ( forward < Args > ( args ) ... ) ) ; }

  template < class ... Args >
  static unique_handle make ( Args && ... args )
    { return make < T > ( forward < Args > ( args ) ... ) ; }

  template < class O, class ... Args >
  void emplace ( Args && ... args )
    { * this = make < O > ( forward < Args > ( args ) ... ) ; }

  template < class ... Args >
  void emplace ( Args && ... args )
    { * this = make ( forward < Args > ( args ) ... ) ; }

  bool empty ( ) const
    { return object == nullptr ; }

  const T * cptr ( ) const
    { assert ( object != nullptr ) ;
      return object ; }

  T * ptr ( ) const
    { assert ( object != nullptr ) ;
      return object ; }

  const T & cref ( ) const
    { return * cptr ( ) ; }

  T & ref ( ) const
    { return * ptr ( ) ; }

  T * operator -> ( ) const
    { return ptr ( ) ; }

  T & operator * ( ) const
    { return ref ( ) ; }

  void clear ( )
    { destroy ( ) ;
      object = nullptr ; }

  void swap ( unique_handle & h )
    { :: swap ( object, h.object ) ; }

  friend bool operator == ( const unique_handle & a, const unique_handle & b )
    { return a.object == b.object ; }

  friend bool operator < ( const unique_handle & a, const unique_handle & b )
    { return a.object < b.object ; }

} ;


//

template < class T >
inline void swap ( unique_handle < T > & a, unique_handle < T > & b )

{
a.swap ( b ) ;
}



#endif
