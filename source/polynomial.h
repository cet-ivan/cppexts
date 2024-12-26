// Copyright Ivan Stanojevic 2023.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __POLYNOMIAL_H

#define __POLYNOMIAL_H



#include "memory.h"
#include "vector.h"
#include "initializer_list.h"
#include "algorithm.h"
#include "cstddef.h"
#include "functional.h"
#include "utility.h"
#include "cassert.h"

#include "numbase.h"
#include "typeconv.h"



// *** FORWARD DECLARATIONS ***


template < class T, class Allocator = allocator < T > >
class polynomial ;

template < class T, class Allocator >
polynomial < T, Allocator >
  reduce ( const polynomial < T, Allocator > & p ) ;

template < class T, class Allocator >
polynomial < T, Allocator >
  remove_delay ( const polynomial < T, Allocator > & p ) ;

template < class T, class Allocator >
polynomial < T, Allocator >
  add_delay ( const polynomial < T, Allocator > & p, size_t d ) ;

template < class T, class Allocator >
polynomial < T, Allocator >
  operator + ( const polynomial < T, Allocator > & a,
               const polynomial < T, Allocator > & b ) ;

template < class T, class Allocator >
polynomial < T, Allocator >
  operator - ( const polynomial < T, Allocator > & a,
               const polynomial < T, Allocator > & b ) ;

template < class T, class Allocator >
polynomial < T, Allocator >
  operator * ( const polynomial < T, Allocator > & a,
               const polynomial < T, Allocator > & b ) ;

template < class T, class Allocator >
void divmod ( const polynomial < T, Allocator > & a,
              const polynomial < T, Allocator > & b,
              polynomial < T, Allocator > & q,
              polynomial < T, Allocator > & r ) ;

template < class T, class Allocator >
polynomial < T, Allocator >
  operator / ( const polynomial < T, Allocator > & a,
               const polynomial < T, Allocator > & b ) ;

template < class T, class Allocator >
polynomial < T, Allocator >
  operator % ( const polynomial < T, Allocator > & a,
               const polynomial < T, Allocator > & b ) ;

template < class T, class Allocator >
bool operator == ( const polynomial < T, Allocator > & a,
                   const polynomial < T, Allocator > & b ) ;

template < class T, class Allocator >
bool operator < ( const polynomial < T, Allocator > & a,
                  const polynomial < T, Allocator > & b ) ;

template < class T, class Allocator >
polynomial < T, Allocator >
  scale_to_monic ( const polynomial < T, Allocator > & p ) ;

template < class T, class Allocator >
polynomial < T, Allocator > reverse ( const polynomial < T, Allocator > & p ) ;

template < class T, class Allocator >
polynomial < T, Allocator >
  reverse ( const polynomial < T, Allocator > & p, size_t size ) ;

template < class T, class Allocator >
polynomial < T, Allocator >
  derivative ( const polynomial < T, Allocator > & p ) ;

template < class T, class Allocator >
void normalize_gcd ( polynomial < T, Allocator > & gcd ) ;

template < class T, class Allocator >
void normalize_gcd_ext ( polynomial < T, Allocator > & c,
                         polynomial < T, Allocator > & d,
                         polynomial < T, Allocator > & gcd ) ;

template < class T, class Allocator >
void normalize_fraction ( polynomial < T, Allocator > & a,
                          polynomial < T, Allocator > & b ) ;



// *** POLYNOMIAL ***


template < class T, class Allocator >
class polynomial : public vector < T, Allocator >

{
public:

  using typename vector < T, Allocator > :: const_iterator ;
  using typename vector < T, Allocator > :: iterator ;
  using vector < T, Allocator > :: begin ;
  using vector < T, Allocator > :: end ;
  using vector < T, Allocator > :: rbegin ;
  using vector < T, Allocator > :: rend ;
  using vector < T, Allocator > :: size ;
  using vector < T, Allocator > :: resize ;
  using vector < T, Allocator > :: empty ;
  using vector < T, Allocator > :: reserve ;
  using vector < T, Allocator > :: at ;
  using vector < T, Allocator > :: back ;
  using vector < T, Allocator > :: push_back ;
  using vector < T, Allocator > :: insert ;
  using vector < T, Allocator > :: erase ;

private:

  class nonzero

  {
  public:

    bool operator ( ) ( const T & c ) const
      { return c != T ( 0 ) ; }

  } ;


  static polynomial add ( const polynomial & a, const polynomial & b ) ;
  static polynomial subtract ( const polynomial & a, const polynomial & b ) ;
  static polynomial multiply ( const polynomial & a, const polynomial & b ) ;

  static void divmod_imp ( polynomial a, polynomial b,
                           polynomial & q, polynomial & r ) ;

public:

  explicit polynomial ( const Allocator & a = Allocator ( ) ) :
    vector < T, Allocator > ( a )
    { }

  polynomial ( const T & c, const Allocator & a = Allocator ( ) ) :
    vector < T, Allocator > ( c == T ( 0 ) ? 0 : 1, c, a )
    { }

  template < class S >
  polynomial ( const S & x,
               const Allocator & a = Allocator ( ),
               typename implicit_conversion_test < S, T > :: result =
                 implicit_conversion_allowed ) :
    vector < T, Allocator > ( x == S ( 0 ) ? 0 : 1, x, a )
    { }

  template < class S, class AllocatorS >
  polynomial ( const polynomial < S, AllocatorS > & x,
               const Allocator & a = Allocator ( ),
               typename implicit_conversion_test < S, T > :: result =
                 implicit_conversion_allowed )
    { auto x_first_ending_zero = x.first_ending_zero ( ) ;
      reserve ( x_first_ending_zero - x.begin ( ) ) ;
      copy ( x.begin ( ), x_first_ending_zero, back_inserter ( * this ) ) ; }

  polynomial ( size_t s, const T & c, const Allocator & a = Allocator ( ) ) :
    vector < T, Allocator > ( s, c, a )
    { }

  explicit polynomial ( const vector < T, Allocator > & v ) :
    vector < T, Allocator > ( v )
    { }

  template < class InputIterator >
  polynomial ( InputIterator first, InputIterator last,
               const Allocator & a = Allocator ( ) ) :
    vector < T, Allocator > ( first, last, a )
    { }

  polynomial ( initializer_list < T > l,
               const Allocator & a = Allocator ( ) ) :
    vector < T, Allocator > ( l, a )
    { }

  const_iterator first_nonzero ( ) const
    { return find_if ( begin ( ), end ( ), nonzero ( ) ) ; }

  iterator first_nonzero ( )
    { return find_if ( begin ( ), end ( ), nonzero ( ) ) ; }

  const_iterator first_ending_zero ( ) const
    { return find_if ( rbegin ( ), rend ( ), nonzero ( ) ).base ( ) ; }

  iterator first_ending_zero ( )
    { return find_if ( rbegin ( ), rend ( ), nonzero ( ) ).base ( ) ; }

  sint delay ( ) const
    { return first_nonzero ( ) - begin ( ) ; }

  size_t active_size ( ) const
    { return first_ending_zero ( ) - begin ( ) ; }

  sint degree ( ) const
    { return max < sint > ( active_size ( ) - 1, 0 ) ; }

  bool is_zero ( ) const
    { return first_nonzero ( ) == end ( ) ; }

  bool is_pure_delay ( ) const
    { const_iterator nonzero_position = first_nonzero ( ) ;
      return     nonzero_position != end ( )
             &&  * nonzero_position == T ( 1 )
             &&  nonzero_position + 1 == first_ending_zero ( ) ; }

  T coefficient ( size_t n ) const
    { return n < size ( ) ? at ( n ) : T ( 0 ) ; }

  T lead_coefficient ( ) const
    { const_iterator ending_zero_position = first_ending_zero ( ) ;
      if ( ending_zero_position != begin ( ) )
        return * -- ending_zero_position ;
      else
        return T ( 0 ) ; }

  void reduce ( )
    { erase ( first_ending_zero ( ), end ( ) ) ; }

  friend polynomial reduce ( const polynomial & p )
    { return polynomial ( p.begin ( ), p.first_ending_zero ( ) ) ; }

  void remove_delay ( )
    { erase ( begin ( ), first_nonzero ( ) ) ; }

  friend polynomial remove_delay ( const polynomial & p )
    { return polynomial ( p.first_nonzero ( ), p.end ( ) ) ; }

  void add_delay ( size_t d )
    { insert ( begin ( ), d, T ( 0 ) ) ; }

  template < class U >
  U operator ( ) ( const U & x ) const ;

  const polynomial & operator + ( ) const
    { return * this ; }

  polynomial operator - ( ) const ;

  friend polynomial operator + ( const polynomial & a, const polynomial & b )
    { return add ( a, b ) ; }

  friend polynomial operator - ( const polynomial & a, const polynomial & b )
    { return subtract ( a, b ) ; }

  friend polynomial operator * ( const polynomial & a, const polynomial & b )
    { return multiply ( a, b ) ; }

  friend void divmod ( const polynomial & a, const polynomial & b,
                       polynomial & q, polynomial & r )
    { divmod_imp ( a, b, q, r ) ; }

  friend polynomial operator / ( const polynomial & a, const polynomial & b )
    { polynomial q, r ;
      divmod ( a, b, q, r ) ;
      return q ; }

  friend polynomial operator % ( const polynomial & a, const polynomial & b )
    { polynomial q, r ;
      divmod ( a, b, q, r ) ;
      return r ; }

  polynomial & operator += ( const polynomial & b )
    { return * this = * this + b ; }

  polynomial & operator -= ( const polynomial & b )
    { return * this = * this - b ; }

  polynomial & operator *= ( const polynomial & b )
    { return * this = * this * b ; }

  polynomial & operator /= ( const polynomial & b )
    { return * this = * this / b ; }

  polynomial & operator %= ( const polynomial & b )
    { return * this = * this % b ; }

  friend bool operator == ( const polynomial & a, const polynomial & b )
    { size_t as = a.active_size ( ),
             bs = b.active_size ( ) ;
      return     as == bs
             &&  equal ( a.begin ( ), a.begin ( ) + as,
                         b.begin ( ) ) ; }

  friend bool operator < ( const polynomial & a, const polynomial & b )
    { return
        lexicographical_compare ( a.begin ( ), a.first_ending_zero ( ),
                                  b.begin ( ), b.first_ending_zero ( ) ) ; }

  void scale_to_monic ( )
    { reduce ( ) ;
      if ( ! empty ( ) )
        {
        transform
          ( begin ( ), end ( ) - 1,
            begin ( ),
            bind ( divides < T > ( ), placeholders :: _1, back ( ) ) ) ;
        back ( ) = T ( 1 ) ;
        } }

  void reverse ( )
    { reduce ( ) ;
      :: reverse ( begin ( ), end ( ) ) ; }

  void reverse ( size_t size )
    { resize ( size, T ( 0 ) ) ;
      :: reverse ( begin ( ), end ( ) ) ; }

  static
    polynomial pure_delay ( size_t d, const Allocator & a = Allocator ( ) ) ;

} ;


//

template < class T, class Allocator >
polynomial < T, Allocator >
  polynomial < T, Allocator > ::
    add ( const polynomial < T, Allocator > & a,
          const polynomial < T, Allocator > & b )

{
size_t as = a.active_size ( ),
       bs = b.active_size ( ) ;

polynomial < T, Allocator > result ;

if ( as < bs )
  {
  result.reserve ( bs ) ;

  transform ( a.begin ( ), a.begin ( ) + as,
              b.begin ( ),
              back_inserter ( result ),
              plus < T > ( ) ) ;

  copy ( b.begin ( ) + as, b.begin ( ) + bs,
         back_inserter ( result ) ) ;
  }
else
  {
  result.reserve ( as ) ;

  transform ( a.begin ( ), a.begin ( ) + bs,
              b.begin ( ),
              back_inserter ( result ),
              plus < T > ( ) ) ;

  copy ( a.begin ( ) + bs, a.begin ( ) + as,
         back_inserter ( result ) ) ;
  }

result.reduce ( ) ;
return result ;
}


//

template < class T, class Allocator >
polynomial < T, Allocator >
  polynomial < T, Allocator > ::
    subtract ( const polynomial < T, Allocator > & a,
               const polynomial < T, Allocator > & b )

{
size_t as = a.active_size ( ),
       bs = b.active_size ( ) ;

polynomial < T, Allocator > result ;

if ( as < bs )
  {
  result.reserve ( bs ) ;

  transform ( a.begin ( ), a.begin ( ) + as,
              b.begin ( ),
              back_inserter ( result ),
              minus < T > ( ) ) ;

  transform ( b.begin ( ) + as, b.begin ( ) + bs,
              back_inserter ( result ),
              negate < T > ( ) ) ;
  }
else
  {
  result.reserve ( as ) ;

  transform ( a.begin ( ), a.begin ( ) + bs,
              b.begin ( ),
              back_inserter ( result ),
              minus < T > ( ) ) ;

  copy ( a.begin ( ) + bs, a.begin ( ) + as,
         back_inserter ( result ) ) ;
  }

result.reduce ( ) ;
return result ;
}


//

template < class T, class Allocator >
polynomial < T, Allocator >
  polynomial < T, Allocator > ::
    multiply ( const polynomial < T, Allocator > & a,
               const polynomial < T, Allocator > & b )

{
size_t as = a.active_size ( ),
       bs = b.active_size ( ) ;

if ( as == 0  ||  bs == 0 )
  return polynomial < T, Allocator > ( ) ;

polynomial < T, Allocator > result ( as + bs - 1, T ( 0 ) ) ;

if ( as < bs )
  for ( size_t i = 0 ; i < as ; ++ i )
    for ( size_t j = 0 ; j < bs ; ++ j )
      result [ i + j ] += a [ i ] * b [ j ] ;
else
  for ( size_t j = 0 ; j < bs ; ++ j )
    for ( size_t i = 0 ; i < as ; ++ i )
      result [ i + j ] += a [ i ] * b [ j ] ;

result.reduce ( ) ;
return result ;
}


//

template < class T, class Allocator >
void polynomial < T, Allocator > ::
       divmod_imp ( polynomial < T, Allocator > a,
                    polynomial < T, Allocator > b,
                    polynomial < T, Allocator > & q,
                    polynomial < T, Allocator > & r )

{
assert ( ! b.is_zero ( ) ) ;

a.reduce ( ) ;
b.reduce ( ) ;

if ( a.size ( ) < b.size ( ) )
  {
  q.clear ( ) ;
  r = a ;
  return ;
  }

q.assign ( a.size ( ) - b.size ( ) + 1, T ( 0 ) ) ;

do
  {
  size_t tqd = a.size ( ) - b.size ( ) ;

  T tq = a.back ( ) / b.back ( ) ;

  q [ tqd ] = tq ;

  for ( size_t i = 0 ; i < b.size ( ) - 1 ; ++ i )
    a [ tqd + i ] -= tq * b [ i ] ;

  a.pop_back ( ) ;
  a.reduce ( ) ;
  }
while ( a.size ( ) >= b.size ( ) ) ;

r = a ;
}


//

template < class T, class Allocator >
polynomial < T, Allocator >
  add_delay ( const polynomial < T, Allocator > & p, size_t d )

{
polynomial < T, Allocator > result ;
result.reserve ( d + p.size ( ) ) ;
result.assign ( d, T ( 0 ) ) ;
result.insert ( result.end ( ), p.begin ( ), p.end ( ) ) ;
return result ;
}


//

template < class T, class Allocator >
template < class U >
U polynomial < T, Allocator > :: operator ( ) ( const U & x ) const

{
const_iterator index = first_ending_zero ( ) ;

if ( index == begin ( ) )
  return U ( 0 ) ;

U result ( * -- index ) ;

while ( index != begin ( ) )
  result = result * x + * -- index ;

return result ;
}


//

template < class T, class Allocator >
polynomial < T, Allocator > polynomial < T, Allocator > :: operator - ( ) const

{
size_t as = active_size ( ) ;

polynomial result ;
result.reserve ( as ) ;

transform ( begin ( ), begin ( ) + as,
            back_inserter ( result ),
            negate < T > ( ) ) ;

result.reduce ( ) ;
return result ;
}


//

template < class T, class Allocator >
polynomial < T, Allocator >
  polynomial < T, Allocator > :: pure_delay ( size_t d, const Allocator & a )

{
polynomial result ;
result.reserve ( d + 1 ) ;
result.insert ( result.end ( ), d, T ( 0 ) ) ;
result.push_back ( T ( 1 ) ) ;
return result ;
}



// *** GLOBALS ***


//

template < class T, class Allocator >
polynomial < T, Allocator >
  scale_to_monic ( const polynomial < T, Allocator > & p )

{
polynomial < T, Allocator > result ;

size_t as = p.active_size ( ) ;

if ( as != 0 )
  {
  result.reserve ( as ) ;

  transform ( p.begin ( ), p.begin ( ) + ( as - 1 ),
              back_inserter ( result ),
              bind ( divides < T > ( ), placeholders :: _1, p [ as - 1 ] ) ) ;

  result.push_back ( T ( 1 ) ) ;
  }

return result ;
}


//

template < class T, class Allocator >
polynomial < T, Allocator > reverse ( const polynomial < T, Allocator > & p )

{
polynomial < T, Allocator > result ;
result.reserve ( p.size ( ) ) ;
copy ( p.rbegin ( ), p.rend ( ), back_inserter ( result ) ) ;
return result ;
}


//

template < class T, class Allocator >
polynomial < T, Allocator >
  reverse ( const polynomial < T, Allocator > & p, size_t size )

{
polynomial < T, Allocator > result ;
result.reserve ( size ) ;

if ( size <= p.size ( ) )
  copy ( p.rend ( ) - size, p.rend ( ), back_inserter ( result ) ) ;
else
  {
  result.insert ( result.end ( ), size - p.size ( ), T ( 0 ) ) ;
  copy ( p.rbegin ( ), p.rend ( ), back_inserter ( result ) ) ;
  }

return result ;
}


//

template < class T, class Allocator >
polynomial < T, Allocator >
  derivative ( const polynomial < T, Allocator > & p )

{
size_t as = p.active_size ( ) ;

polynomial < T, Allocator > result ;

if ( as <= 1 )
  return result ;

result.reserve ( as - 1 ) ;

for ( size_t i = 1 ; i < as ; ++ i )
  result.push_back ( T ( i ) * p [ i ] ) ;

result.reduce ( ) ;
return result ;
}



// *** INDEXING_TRAITS ***


template < class T, class Allocator >
class indexing_traits < polynomial < T, Allocator > >

{
public:

  typedef typename polynomial < T, Allocator > :: size_type index_type ;
  typedef T value_type ;

} ;



// *** GLOBAL INTERFACES ***


//

template < class T, class Allocator >
inline void normalize_gcd ( polynomial < T, Allocator > & gcd )

{
gcd.scale_to_monic ( ) ;
}


//

template < class T, class Allocator >
inline void normalize_gcd_ext ( polynomial < T, Allocator > & c,
                                polynomial < T, Allocator > & d,
                                polynomial < T, Allocator > & gcd )

{
c.reduce ( ) ;
d.reduce ( ) ;
gcd.reduce ( ) ;

if ( ! gcd.is_zero ( ) )
  {
  c /= gcd.back ( ) ;
  d /= gcd.back ( ) ;
  gcd.scale_to_monic ( ) ;
  }
}


//

template < class T, class Allocator >
inline void normalize_fraction ( polynomial < T, Allocator > & a,
                                 polynomial < T, Allocator > & b )

{
a.reduce ( ) ;
b.reduce ( ) ;

if ( ! b.is_zero ( ) )
  {
  a /= b.back ( ) ;
  b.scale_to_monic ( ) ;
  }
}



// *** IMPLICIT CONVERSION ***


//

template < class T, class Allocator >
class implicit_conversion_test < T, polynomial < T, Allocator > > :
  public implicit_conversion_test_ok

{
} ;


//

template < class S, class T, class Allocator >
class implicit_conversion_test < S, polynomial < T, Allocator > > :
  public implicit_conversion_test < S, T >

{
} ;


//

template < class S, class AllocatorS, class T, class Allocator >
class implicit_conversion_test < polynomial < S, AllocatorS >,
                                 polynomial < T, Allocator > > :
  public implicit_conversion_test < S, T >

{
} ;



// *** TYPE CONVERSION ***


//

template < class T1, class Allocator1, class T2, class Allocator2 >
class type_converter < polynomial < T1, Allocator1 >,
                       polynomial < T2, Allocator2 > >

{
public:

  static polynomial < T2, Allocator2 >
    operate ( const polynomial < T1, Allocator1 > & x ) ;

} ;


//

template < class T1, class Allocator1, class T2, class Allocator2 >
polynomial < T2, Allocator2 >
  type_converter < polynomial < T1, Allocator1 >,
                   polynomial < T2, Allocator2 > > ::
    operate ( const polynomial < T1, Allocator1 > & x )

{
auto x_first_ending_zero = x.first_ending_zero ( ) ;

polynomial < T2, Allocator2 > result ;
result.reserve ( x_first_ending_zero - x.begin ( ) ) ;

transform ( x.begin ( ), x_first_ending_zero,
            back_inserter ( result ),
            [ ] ( const T1 & s ) { return convert_to < T2 > ( s ) ; } ) ;

return result ;
}



#endif
