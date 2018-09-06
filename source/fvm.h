// Copyright Ivan Stanojevic 2015.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __FVM_H

#define __FVM_H



#include "cstddef.h"
#include "iterator.h"
#include "utility.h"
#include "cassert.h"
#include "algorithm.h"
#include "functional.h"
#include "numeric.h"

#include "streaming.h"
#include "funtr.h"



// *** FORWARD_DECLARATIONS ***


//

template < class T, size_t N >
class fixed_vector ;

template < class T, size_t N1, size_t N2 >
class fixed_matrix ;

template < class T, size_t N >
class fixed_lower_triangular_matrix ;

template < class T, size_t N >
class fixed_upper_triangular_matrix ;


//

template < class T, size_t N >
fixed_vector < T, N > operator + ( const fixed_vector < T, N > & a,
                                   const fixed_vector < T, N > & b ) ;

template < class T, size_t N >
fixed_vector < T, N > operator - ( const fixed_vector < T, N > & a,
                                   const fixed_vector < T, N > & b ) ;

template < class T, size_t N >
T operator * ( const fixed_vector < T, N > & a,
               const fixed_vector < T, N > & b ) ;

template < class T, size_t N >
fixed_vector < T, N > operator * ( const fixed_vector < T, N > & a,
                                   const T & b ) ;

template < class T, size_t N >
fixed_vector < T, N > operator * ( const T & a,
                                   const fixed_vector < T, N > & b ) ;

template < class T, size_t N >
fixed_vector < T, N > operator / ( const fixed_vector < T, N > & a,
                                   const T & b ) ;

template < class T, size_t N >
fixed_vector < T, N > operator % ( const fixed_vector < T, N > & a,
                                   const T & b ) ;

template < class T, size_t N >
bool operator == ( const fixed_vector < T, N > & a,
                   const fixed_vector < T, N > & b ) ;

template < class T, size_t N >
bool operator < ( const fixed_vector < T, N > & a,
                  const fixed_vector < T, N > & b ) ;

template < class T, size_t N >
void swap ( fixed_vector < T, N > & a, fixed_vector < T, N > & b ) ;

template < class T, size_t N, class UnaryOperation >
fixed_vector < T, N > componentwise ( const fixed_vector < T, N > & a,
                                      UnaryOperation unary_operation ) ;

template < class T, size_t N, class BinaryOperation >
fixed_vector < T, N > componentwise ( const fixed_vector < T, N > & a,
                                      const fixed_vector < T, N > & b,
                                      BinaryOperation binary_operation ) ;

template < class T, size_t N >
T inner_product ( const fixed_vector < T, N > & a,
                  const fixed_vector < T, N > & b ) ;

template < class T, size_t N >
inline T norm ( const fixed_vector < T, N > & a ) ;


//

template < class T, size_t N1, size_t N2 >
fixed_matrix < T, N1, N2 > operator + ( const fixed_matrix < T, N1, N2 > & a,
                                        const fixed_matrix < T, N1, N2 > & b ) ;

template < class T, size_t N1, size_t N2 >
fixed_matrix < T, N1, N2 > operator - ( const fixed_matrix < T, N1, N2 > & a,
                                        const fixed_matrix < T, N1, N2 > & b ) ;

template < class T, size_t N1, size_t N2 >
fixed_matrix < T, N1, N2 > operator * ( const fixed_matrix < T, N1, N2 > & a,
                                        const T & b ) ;

template < class T, size_t N1, size_t N2 >
fixed_matrix < T, N1, N2 > operator * ( const T & a,
                                        const fixed_matrix < T, N1, N2 > & b ) ;

template < class T, size_t N1, size_t N2 >
fixed_matrix < T, N1, N2 > operator / ( const fixed_matrix < T, N1, N2 > & a,
                                        const T & b ) ;

template < class T, size_t N1, size_t N2 >
fixed_matrix < T, N1, N2 > operator % ( const fixed_matrix < T, N1, N2 > & a,
                                        const T & b ) ;

template < class T, size_t N1, size_t N2 >
bool operator == ( const fixed_matrix < T, N1, N2 > & a,
                   const fixed_matrix < T, N1, N2 > & b ) ;

template < class T, size_t N1, size_t N2 >
bool operator < ( const fixed_matrix < T, N1, N2 > & a,
                  const fixed_matrix < T, N1, N2 > & b ) ;

template < class T, size_t N1, size_t N2 >
void swap ( fixed_matrix < T, N1, N2 > & a, fixed_matrix < T, N1, N2 > & b ) ;

template < class T, size_t N1, size_t N2, class UnaryOperation >
fixed_matrix < T, N1, N2 >
  componentwise ( const fixed_matrix < T, N1, N2 > & a,
                  UnaryOperation unary_operation ) ;

template < class T, size_t N1, size_t N2, class BinaryOperation >
fixed_matrix < T, N1, N2 >
  componentwise ( const fixed_matrix < T, N1, N2 > & a,
                  const fixed_matrix < T, N1, N2 > & b,
                  BinaryOperation binary_operation ) ;

template < class T, size_t N1, size_t N2 >
fixed_matrix < T, N1, N2 > outer_product ( const fixed_vector < T, N1 > & a,
                                           const fixed_vector < T, N2 > & b ) ;

template < class T, size_t N1, size_t N2 >
fixed_vector < T, N1 > operator * ( const fixed_matrix < T, N1, N2 > & m,
                                    const fixed_vector < T, N2 > & v ) ;

template < class T, size_t N1, size_t N2 >
fixed_vector < T, N2 > operator * ( const fixed_vector < T, N1 > & v,
                                    const fixed_matrix < T, N1, N2 > & m ) ;

template < class T, size_t N1, size_t N2, size_t N3 >
fixed_matrix < T, N1, N3 > operator * ( const fixed_matrix < T, N1, N2 > & a,
                                        const fixed_matrix < T, N2, N3 > & b ) ;


//

template < class T, size_t N >
fixed_lower_triangular_matrix < T, N >
  operator + ( const fixed_lower_triangular_matrix < T, N > & a,
               const fixed_lower_triangular_matrix < T, N > & b ) ;

template < class T, size_t N >
fixed_lower_triangular_matrix < T, N >
  operator - ( const fixed_lower_triangular_matrix < T, N > & a,
               const fixed_lower_triangular_matrix < T, N > & b ) ;

template < class T, size_t N >
fixed_lower_triangular_matrix < T, N >
  operator * ( const fixed_lower_triangular_matrix < T, N > & a, const T & b ) ;

template < class T, size_t N >
fixed_lower_triangular_matrix < T, N >
  operator * ( const T & a, const fixed_lower_triangular_matrix < T, N > & b ) ;

template < class T, size_t N >
fixed_lower_triangular_matrix < T, N >
  operator / ( const fixed_lower_triangular_matrix < T, N > & a, const T & b ) ;

template < class T, size_t N >
fixed_lower_triangular_matrix < T, N >
  operator % ( const fixed_lower_triangular_matrix < T, N > & a, const T & b ) ;

template < class T, size_t N >
bool operator == ( const fixed_lower_triangular_matrix < T, N > & a,
                   const fixed_lower_triangular_matrix < T, N > & b ) ;

template < class T, size_t N >
bool operator < ( const fixed_lower_triangular_matrix < T, N > & a,
                  const fixed_lower_triangular_matrix < T, N > & b ) ;

template < class T, size_t N >
void swap ( const fixed_lower_triangular_matrix < T, N > & a,
            const fixed_lower_triangular_matrix < T, N > & b ) ;

template < class T, size_t N, class UnaryOperation >
fixed_lower_triangular_matrix < T, N >
  componentwise ( const fixed_lower_triangular_matrix < T, N > & a,
                  UnaryOperation unary_operation ) ;

template < class T, size_t N, class BinaryOperation >
fixed_lower_triangular_matrix < T, N >
  componentwise ( const fixed_lower_triangular_matrix < T, N > & a,
                  const fixed_lower_triangular_matrix < T, N > & b,
                  BinaryOperation binary_operation ) ;

template < class T, size_t N >
fixed_vector < T, N >
  operator * ( const fixed_lower_triangular_matrix < T, N > & m,
               const fixed_vector < T, N > & v ) ;

template < class T, size_t N >
fixed_vector < T, N >
  operator * ( const fixed_vector < T, N > & v,
               const fixed_lower_triangular_matrix < T, N > & m ) ;

template < class T, size_t N1, size_t N2 >
fixed_matrix < T, N1, N2 >
  operator * ( const fixed_lower_triangular_matrix < T, N1 > & a,
               const fixed_matrix < T, N1, N2 > & b ) ;

template < class T, size_t N1, size_t N2 >
fixed_matrix < T, N1, N2 >
  operator * ( const fixed_matrix < T, N1, N2 > & a,
               const fixed_lower_triangular_matrix < T, N2 > & b ) ;

template < class T, size_t N >
fixed_lower_triangular_matrix < T, N >
  operator * ( const fixed_lower_triangular_matrix < T, N > & a,
               const fixed_lower_triangular_matrix < T, N > & b ) ;

template < class T, size_t N >
fixed_matrix < T, N, N >
  make_symmetric ( const fixed_lower_triangular_matrix < T, N > & m ) ;

template < class T, size_t N >
fixed_matrix < T, N, N >
  make_complete ( const fixed_lower_triangular_matrix < T, N > & m ) ;


//

template < class T, size_t N >
fixed_upper_triangular_matrix < T, N >
  operator + ( const fixed_upper_triangular_matrix < T, N > & a,
               const fixed_upper_triangular_matrix < T, N > & b ) ;

template < class T, size_t N >
fixed_upper_triangular_matrix < T, N >
  operator - ( const fixed_upper_triangular_matrix < T, N > & a,
               const fixed_upper_triangular_matrix < T, N > & b ) ;

template < class T, size_t N >
fixed_upper_triangular_matrix < T, N >
  operator * ( const fixed_upper_triangular_matrix < T, N > & a, const T & b ) ;

template < class T, size_t N >
fixed_upper_triangular_matrix < T, N >
  operator * ( const T & a, const fixed_upper_triangular_matrix < T, N > & b ) ;

template < class T, size_t N >
fixed_upper_triangular_matrix < T, N >
  operator / ( const fixed_upper_triangular_matrix < T, N > & a, const T & b ) ;

template < class T, size_t N >
fixed_upper_triangular_matrix < T, N >
  operator % ( const fixed_upper_triangular_matrix < T, N > & a, const T & b ) ;

template < class T, size_t N >
bool operator == ( const fixed_upper_triangular_matrix < T, N > & a,
                   const fixed_upper_triangular_matrix < T, N > & b ) ;

template < class T, size_t N >
bool operator < ( const fixed_upper_triangular_matrix < T, N > & a,
                  const fixed_upper_triangular_matrix < T, N > & b ) ;

template < class T, size_t N >
void swap ( const fixed_upper_triangular_matrix < T, N > & a,
            const fixed_upper_triangular_matrix < T, N > & b ) ;

template < class T, size_t N, class UnaryOperation >
fixed_upper_triangular_matrix < T, N >
  componentwise ( const fixed_upper_triangular_matrix < T, N > & a,
                  UnaryOperation unary_operation ) ;

template < class T, size_t N, class BinaryOperation >
fixed_upper_triangular_matrix < T, N >
  componentwise ( const fixed_upper_triangular_matrix < T, N > & a,
                  const fixed_upper_triangular_matrix < T, N > & b,
                  BinaryOperation binary_operation ) ;

template < class T, size_t N >
fixed_vector < T, N >
  operator * ( const fixed_upper_triangular_matrix < T, N > & m,
               const fixed_vector < T, N > & v ) ;

template < class T, size_t N >
fixed_vector < T, N >
  operator * ( const fixed_vector < T, N > & v,
               const fixed_upper_triangular_matrix < T, N > & m ) ;

template < class T, size_t N1, size_t N2 >
fixed_matrix < T, N1, N2 >
  operator * ( const fixed_upper_triangular_matrix < T, N1 > & a,
               const fixed_matrix < T, N1, N2 > & b ) ;

template < class T, size_t N1, size_t N2 >
fixed_matrix < T, N1, N2 >
  operator * ( const fixed_matrix < T, N1, N2 > & a,
               const fixed_upper_triangular_matrix < T, N2 > & b ) ;

template < class T, size_t N >
fixed_upper_triangular_matrix < T, N >
  operator * ( const fixed_upper_triangular_matrix < T, N > & a,
               const fixed_upper_triangular_matrix < T, N > & b ) ;

template < class T, size_t N >
fixed_matrix < T, N, N >
  make_symmetric ( const fixed_upper_triangular_matrix < T, N > & m ) ;

template < class T, size_t N >
fixed_matrix < T, N, N >
  make_complete ( const fixed_upper_triangular_matrix < T, N > & m ) ;



// *** FIXED_VECTOR ***


template < class T, size_t N >
class fixed_vector

{
public:

  static_assert ( N > 0, "Size of fixed_vector == 0." ) ;

  typedef T value_type ;

  typedef size_t size_type ;
  typedef ptrdiff_t difference_type ;

  typedef value_type * pointer ;
  typedef const value_type * const_pointer ;

  typedef value_type & reference ;
  typedef const value_type & const_reference ;

  typedef pointer iterator ;
  typedef const_pointer const_iterator ;

  typedef :: reverse_iterator < iterator > reverse_iterator ;
  typedef :: reverse_iterator < const_iterator > const_reverse_iterator ;

  T elements [ N ] ;

  pointer data ( ) noexcept
    { return elements ; }

  const_pointer data ( ) const noexcept
    { return elements ; }

  iterator begin ( ) noexcept
    { return elements ; }

  const_iterator begin ( ) const noexcept
    { return elements ; }

  iterator end ( ) noexcept
    { return elements + N ; }

  const_iterator end ( ) const noexcept
    { return elements + N ; }

  reverse_iterator rbegin ( ) noexcept
    { return reverse_iterator ( end ( ) ) ; }

  const_reverse_iterator rbegin ( ) const noexcept
    { return const_reverse_iterator ( end ( ) ) ; }

  reverse_iterator rend ( ) noexcept
    { return reverse_iterator ( begin ( ) ) ; }

  const_reverse_iterator rend ( ) const noexcept
    { return const_reverse_iterator ( begin ( ) ) ; }

  const_iterator cbegin ( ) const noexcept
    { return begin ( ) ; }

  const_iterator cend ( ) const noexcept
    { return end ( ) ; }

  const_reverse_iterator crbegin ( ) const noexcept
    { return rbegin ( ) ; }

  const_reverse_iterator crend ( ) const noexcept
    { return rend ( ) ; }

  constexpr size_t size ( ) noexcept
    { return N ; }

  constexpr bool empty ( ) noexcept
    { return false ; }

  reference at ( size_t n ) noexcept
    { assert ( n < N ) ;
      return elements [ n ] ; }

  const_reference at ( size_t n ) const noexcept
    { assert ( n < N ) ;
      return elements [ n ] ; }

  reference operator [ ] ( size_t n ) noexcept
    { return at ( n ) ; }

  const_reference operator [ ] ( size_t n ) const noexcept
    { return at ( n ) ; }

  reference front ( ) noexcept
    { return at ( 0 ) ; }

  const_reference front ( ) const noexcept
    { return at ( 0 ) ; }

  reference back ( ) noexcept
    { return at ( N - 1 ) ; }

  const_reference back ( ) const noexcept
    { return at ( N - 1 ) ; }

  void fill ( const T & x )
    { :: fill ( begin ( ), end ( ), x ) ; }

  void swap ( fixed_vector & b )
    noexcept ( noexcept ( swap ( declval < T & > ( ), declval < T & > ( ) ) ) )
    { swap_ranges ( begin ( ), end ( ), b.begin ( ) ) ; }

  const fixed_vector & operator + ( ) const
    { return * this ; }

  fixed_vector operator - ( ) const
    { fixed_vector result ;
      transform ( begin ( ), end ( ),
                  result.begin ( ),
                  :: negate < T > ( ) ) ;
      return result ; }

  friend fixed_vector operator + ( const fixed_vector & a,
                                   const fixed_vector & b )
    { fixed_vector result ;
      transform ( a.begin ( ), a.end ( ),
                  b.begin ( ),
                  result.begin ( ),
                  plus < T > ( ) ) ;
      return result ; }

  friend fixed_vector operator - ( const fixed_vector & a,
                                   const fixed_vector & b )
    { fixed_vector result ;
      transform ( a.begin ( ), a.end ( ),
                  b.begin ( ),
                  result.begin ( ),
                  minus < T > ( ) ) ;
      return result ; }

  friend T operator * ( const fixed_vector & a, const fixed_vector & b )
    { return inner_product ( a.begin ( ), a.end ( ),
                             b.begin ( ),
                             T ( 0 ) ) ; }

  friend fixed_vector operator * ( const fixed_vector & a, const T & b )
    { fixed_vector result ;
      transform ( a.begin ( ), a.end ( ),
                  result.begin ( ),
                  [ & ] ( const T & x ) { return x * b ; } ) ;
      return result ; }

  friend fixed_vector operator * ( const T & a, const fixed_vector & b )
    { fixed_vector result ;
      transform ( b.begin ( ), b.end ( ),
                  result.begin ( ),
                  [ & ] ( const T & x ) { return a * x ; } ) ;
      return result ; }

  friend fixed_vector operator / ( const fixed_vector & a, const T & b )
    { fixed_vector result ;
      transform ( a.begin ( ), a.end ( ),
                  result.begin ( ),
                  [ & ] ( const T & x ) { return x / b ; } ) ;
      return result ; }

  friend fixed_vector operator % ( const fixed_vector & a, const T & b )
    { fixed_vector result ;
      transform ( a.begin ( ), a.end ( ),
                  result.begin ( ),
                  [ & ] ( const T & x ) { return x % b ; } ) ;
      return result ; }

  fixed_vector & negate ( )
    { for ( T & x : elements )
        x = - x ;
      return * this ; }

  fixed_vector & operator += ( const fixed_vector & b )
    { for_each_pair ( begin ( ), end ( ),
                      b.begin ( ),
                      [ ] ( T & x, const T & y ) { x += y ; } ) ;
      return * this ; }

  fixed_vector & operator -= ( const fixed_vector & b )
    { for_each_pair ( begin ( ), end ( ),
                      b.begin ( ),
                      [ ] ( T & x, const T & y ) { x -= y ; } ) ;
      return * this ; }

  fixed_vector & operator *= ( const T & b )
    { for ( T & x : elements )
        x *= b ;
      return * this ; }

  fixed_vector & operator /= ( const T & b )
    { for ( T & x : elements )
        x /= b ;
      return * this ; }

  fixed_vector & operator %= ( const T & b )
    { for ( T & x : elements )
        x %= b ;
      return * this ; }

  friend bool operator == ( const fixed_vector & a, const fixed_vector & b )
    { return equal ( a.begin ( ), a.end ( ), b.begin ( ) ) ; }

  friend bool operator < ( const fixed_vector & a, const fixed_vector & b )
    { return lexicographical_compare ( a.begin ( ), a.end ( ),
                                       b.begin ( ), b.end ( ) ) ; }

  friend void swap ( fixed_vector & a, fixed_vector & b )
    { a.swap ( b ) ; }

  template < class CharT, class CharTraits >
  friend basic_ostream < CharT, CharTraits > &
    operator << ( basic_ostream < CharT, CharTraits > & o,
                  const fixed_vector & x )
    { return output_array ( o, x.elements ) ; }

  template < class CharT, class CharTraits >
  friend basic_istream < CharT, CharTraits > &
    operator >> ( basic_istream < CharT, CharTraits > & i,
                  fixed_vector & x )
    { fixed_vector tx ;
      input_array ( i, tx.elements ) ;
      if ( i.good ( ) )
        x = move ( tx ) ;
      return i ; }

} ;


//

template < class T, size_t N, class UnaryOperation >
inline fixed_vector < T, N >
         componentwise ( const fixed_vector < T, N > & a,
                         UnaryOperation unary_operation )

{
fixed_vector < T, N > result ;

transform ( a.begin ( ), a.end ( ),
            result.begin ( ),
            unary_operation ) ;

return result ;
}


//

template < class T, size_t N, class BinaryOperation >
inline fixed_vector < T, N >
         componentwise ( const fixed_vector < T, N > & a,
                         const fixed_vector < T, N > & b,
                         BinaryOperation binary_operation )

{
fixed_vector < T, N > result ;

transform ( a.begin ( ), a.end ( ),
            b.begin ( ),
            result.begin ( ),
            binary_operation ) ;

return result ;
}


//

template < class T, size_t N >
inline T inner_product ( const fixed_vector < T, N > & a,
                         const fixed_vector < T, N > & b )

{
return a * b ;
}


//

template < class T, size_t N >
inline T norm ( const fixed_vector < T, N > & a )

{
return a * a ;
}



// *** FIXED_VECTOR INDEXING_TRAITS ***


template < class T, size_t N >
class indexing_traits < fixed_vector < T, N > >

{
public:

  typedef size_t index_type ;
  typedef T value_type ;

  static constexpr size_t size ( const fixed_vector < T, N > & x )
    { return N ; }

} ;



// *** FIXED_MATRIX ***


template < class T, size_t N1, size_t N2 >
class fixed_matrix

{
public:

  static_assert ( N1 > 0, "Size1 of fixed_matrix == 0." ) ;
  static_assert ( N2 > 0, "Size2 of fixed_matrix == 0." ) ;

  typedef T value_type [ N2 ] ;

  typedef size_t size_type ;
  typedef ptrdiff_t difference_type ;

  typedef value_type * pointer ;
  typedef const value_type * const_pointer ;

  typedef value_type & reference ;
  typedef const value_type & const_reference ;

  typedef pointer iterator ;
  typedef const_pointer const_iterator ;

  typedef :: reverse_iterator < iterator > reverse_iterator ;
  typedef :: reverse_iterator < const_iterator > const_reverse_iterator ;

  typedef T * element_pointer ;
  typedef const T * const_element_pointer ;

  typedef T & element_reference ;
  typedef const T & const_element_reference ;

  typedef element_pointer element_iterator ;
  typedef const_element_pointer const_element_iterator ;

  typedef :: reverse_iterator < element_iterator > reverse_element_iterator ;

  typedef :: reverse_iterator < const_element_iterator >
          const_reverse_element_iterator ;

  value_type elements [ N1 ] ;

  pointer data ( ) noexcept
    { return elements ; }

  const_pointer data ( ) const noexcept
    { return elements ; }

  iterator begin ( ) noexcept
    { return data ( ) ; }

  const_iterator begin ( ) const noexcept
    { return data ( ) ; }

  iterator end ( ) noexcept
    { return data ( ) + N1 ; }

  const_iterator end ( ) const noexcept
    { return data ( ) + N1 ; }

  reverse_iterator rbegin ( ) noexcept
    { return reverse_iterator ( end ( ) ) ; }

  const_reverse_iterator rbegin ( ) const noexcept
    { return const_reverse_iterator ( end ( ) ) ; }

  reverse_iterator rend ( ) noexcept
    { return reverse_iterator ( begin ( ) ) ; }

  const_reverse_iterator rend ( ) const noexcept
    { return const_reverse_iterator ( begin ( ) ) ; }

  const_iterator cbegin ( ) const noexcept
    { return begin ( ) ; }

  const_iterator cend ( ) const noexcept
    { return end ( ) ; }

  const_reverse_iterator crbegin ( ) const noexcept
    { return rbegin ( ) ; }

  const_reverse_iterator crend ( ) const noexcept
    { return rend ( ) ; }

  constexpr size_t size ( ) noexcept
    { return N1 ; }

  constexpr bool empty ( ) noexcept
    { return false ; }

  reference at ( size_t n1 ) noexcept
    { assert ( n1 < N1 ) ;
      return data ( ) [ n1 ] ; }

  const_reference at ( size_t n1 ) const noexcept
    { assert ( n1 < N1 ) ;
      return data ( ) [ n1 ] ; }

  reference operator [ ] ( size_t n1 ) noexcept
    { return at ( n1 ) ; }

  const_reference operator [ ] ( size_t n1 ) const noexcept
    { return at ( n1 ) ; }

  reference front ( ) noexcept
    { return at ( 0 ) ; }

  const_reference front ( ) const noexcept
    { return at ( 0 ) ; }

  reference back ( ) noexcept
    { return at ( N1 - 1 ) ; }

  const_reference back ( ) const noexcept
    { return at ( N1 - 1 ) ; }

  element_pointer element_data ( ) noexcept
    { return * elements ; }

  const_element_pointer element_data ( ) const noexcept
    { return * elements ; }

  element_iterator element_begin ( ) noexcept
    { return element_data ( ) ; }

  const_element_iterator element_begin ( ) const noexcept
    { return element_data ( ) ; }

  element_iterator element_end ( ) noexcept
    { return element_data ( ) + N1 * N2 ; }

  const_element_iterator element_end ( ) const noexcept
    { return element_data ( ) + N1 * N2 ; }

  reverse_element_iterator element_rbegin ( ) noexcept
    { return reverse_element_iterator ( element_end ( ) ) ; }

  const_reverse_element_iterator element_rbegin ( ) const noexcept
    { return const_reverse_element_iterator ( element_end ( ) ) ; }

  reverse_element_iterator element_rend ( ) noexcept
    { return reverse_element_iterator ( element_begin ( ) ) ; }

  const_reverse_element_iterator element_rend ( ) const noexcept
    { return const_reverse_element_iterator ( element_begin ( ) ) ; }

  const_element_iterator element_cbegin ( ) const noexcept
    { return element_begin ( ) ; }

  const_element_iterator element_cend ( ) const noexcept
    { return element_end ( ) ; }

  const_reverse_element_iterator element_crbegin ( ) const noexcept
    { return element_rbegin ( ) ; }

  const_reverse_element_iterator element_crend ( ) const noexcept
    { return element_rend ( ) ; }

  constexpr size_t element_size ( ) noexcept
    { return N1 * N2 ; }

  constexpr size_t size1 ( ) noexcept
    { return N1 ; }

  constexpr size_t size2 ( ) noexcept
    { return N2 ; }

  element_reference at ( size_t n1, size_t n2 ) noexcept
    { assert ( n1 < N1 ) ;
      assert ( n2 < N2 ) ;
      return data ( ) [ n1 ] [ n2 ] ; }

  const_element_reference at ( size_t n1, size_t n2 ) const noexcept
    { assert ( n1 < N1 ) ;
      assert ( n2 < N2 ) ;
      return data ( ) [ n1 ] [ n2 ] ; }

  element_reference operator ( ) ( size_t n1, size_t n2 ) noexcept
    { return at ( n1, n2 ) ; }

  const_element_reference
    operator ( ) ( size_t n1, size_t n2 ) const noexcept
    { return at ( n1, n2 ) ; }

  element_reference element_front ( ) noexcept
    { return at ( 0, 0 ) ; }

  const_element_reference element_front ( ) const noexcept
    { return at ( 0, 0 ) ; }

  element_reference element_back ( ) noexcept
    { return at ( N1 - 1, N2 - 1 ) ; }

  const_element_reference element_back ( ) const noexcept
    { return at ( N1 - 1, N2 - 1 ) ; }

  void fill ( const T & x )
    { :: fill ( element_begin ( ), element_end ( ), x ) ; }

  void swap ( fixed_matrix & b )
    noexcept ( noexcept ( swap ( declval < T & > ( ), declval < T & > ( ) ) ) )
    { swap_ranges ( element_begin ( ), element_end ( ),
                    b.element_begin ( ) ) ; }

  const fixed_matrix & operator + ( ) const
    { return * this ; }

  fixed_matrix operator - ( ) const
    { fixed_matrix result ;
      transform ( element_begin ( ), element_end ( ),
                  result.element_begin ( ),
                  :: negate < T > ( ) ) ;
      return result ; }

  friend fixed_matrix operator + ( const fixed_matrix & a,
                                   const fixed_matrix & b )
    { fixed_matrix result ;
      transform ( a.element_begin ( ), a.element_end ( ),
                  b.element_begin ( ),
                  result.element_begin ( ),
                  plus < T > ( ) ) ;
      return result ; }

  friend fixed_matrix operator - ( const fixed_matrix & a,
                                   const fixed_matrix & b )
    { fixed_matrix result ;
      transform ( a.element_begin ( ), a.element_end ( ),
                  b.element_begin ( ),
                  result.element_begin ( ),
                  minus < T > ( ) ) ;
      return result ; }

  friend fixed_matrix operator * ( const fixed_matrix & a, const T & b )
    { fixed_matrix result ;
      transform ( a.element_begin ( ), a.element_end ( ),
                  result.element_begin ( ),
                  [ & ] ( const T & x ) { return x * b ; } ) ;
      return result ; }

  friend fixed_matrix operator * ( const T & a, const fixed_matrix & b )
    { fixed_matrix result ;
      transform ( b.element_begin ( ), b.element_end ( ),
                  result.element_begin ( ),
                  [ & ] ( const T & x ) { return a * x ; } ) ;
      return result ; }

  friend fixed_matrix operator / ( const fixed_matrix & a, const T & b )
    { fixed_matrix result ;
      transform ( a.element_begin ( ), a.element_end ( ),
                  result.element_begin ( ),
                  [ & ] ( const T & x ) { return x / b ; } ) ;
      return result ; }

  friend fixed_matrix operator % ( const fixed_matrix & a, const T & b )
    { fixed_matrix result ;
      transform ( a.element_begin ( ), a.element_end ( ),
                  result.element_begin ( ),
                  [ & ] ( const T & x ) { return x % b ; } ) ;
      return result ; }

  fixed_matrix < T, N2, N1 > transposed ( ) const
    { fixed_matrix < T, N2, N1 > result ;
      for ( size_t n1 = 0 ; n1 < N1 ; ++ n1 )
        for ( size_t n2 = 0 ; n2 < N2 ; ++ n2 )
          result.at ( n2, n1 ) = at ( n1, n2 ) ;
      return result ; }

  fixed_matrix & negate ( )
    { for_each ( element_begin ( ), element_end ( ),
                 [ ] ( T & x ) { x = - x ; } ) ;
      return * this ; }

  fixed_matrix & operator += ( const fixed_matrix & b )
    { for_each_pair ( element_begin ( ), element_end ( ),
                      b.element_begin ( ),
                      [ ] ( T & x, const T & y ) { x += y ; } ) ;
      return * this ; }

  fixed_matrix & operator -= ( const fixed_matrix & b )
    { for_each_pair ( element_begin ( ), element_end ( ),
                      b.element_begin ( ),
                      [ ] ( T & x, const T & y ) { x -= y ; } ) ;
      return * this ; }

  fixed_matrix & operator *= ( const T & b )
    { for_each ( element_begin ( ), element_end ( ),
                 [ & ] ( T & x ) { x *= b ; } ) ;
      return * this ; }

  fixed_matrix & operator *= ( const fixed_matrix < T, N2, N2 > & b )
    { return * this = * this * b ; }

  fixed_matrix & operator *=
    ( const fixed_lower_triangular_matrix < T, N2 > & b )
    { return * this = * this * b ; }

  fixed_matrix & operator *=
    ( const fixed_upper_triangular_matrix < T, N2 > & b )
    { return * this = * this * b ; }

  fixed_matrix & operator /= ( const T & b )
    { for_each ( element_begin ( ), element_end ( ),
                 [ & ] ( T & x ) { x /= b ; } ) ;
      return * this ; }

  fixed_matrix & operator %= ( const T & b )
    { for_each ( element_begin ( ), element_end ( ),
                 [ & ] ( T & x ) { x %= b ; } ) ;
      return * this ; }

  friend bool operator == ( const fixed_matrix & a, const fixed_matrix & b )
    { return equal ( a.element_begin ( ), a.element_end ( ),
                     b.element_begin ( ) ) ; }

  friend bool operator < ( const fixed_matrix & a, const fixed_matrix & b )
    { return lexicographical_compare
               ( a.element_begin ( ), a.element_end ( ),
                 b.element_begin ( ), b.element_end ( ) ) ; }

  friend void swap ( fixed_matrix & a, fixed_matrix & b )
    { a.swap ( b ) ; }

  template < class CharT, class CharTraits >
  friend basic_ostream < CharT, CharTraits > &
    operator << ( basic_ostream < CharT, CharTraits > & o,
                  const fixed_matrix & x )
    { return output_array ( o, x.elements ) ; }

  template < class CharT, class CharTraits >
  friend basic_istream < CharT, CharTraits > &
    operator >> ( basic_istream < CharT, CharTraits > & i,
                  fixed_matrix & x )
    { fixed_matrix tx ;
      input_array ( i, tx.elements ) ;
      if ( i.good ( ) )
        x = move ( tx ) ;
      return i ; }

} ;


//

template < class T, size_t N1, size_t N2, class UnaryOperation >
inline fixed_matrix < T, N1, N2 >
         componentwise ( const fixed_matrix < T, N1, N2 > & a,
                         UnaryOperation unary_operation )

{
fixed_matrix < T, N1, N2 > result ;

transform ( a.element_begin ( ), a.element_end ( ),
            result.element_begin ( ),
            unary_operation ) ;

return result ;
}


//

template < class T, size_t N1, size_t N2, class BinaryOperation >
inline fixed_matrix < T, N1, N2 >
         componentwise ( const fixed_matrix < T, N1, N2 > & a,
                         const fixed_matrix < T, N1, N2 > & b,
                         BinaryOperation binary_operation )

{
fixed_matrix < T, N1, N2 > result ;

transform ( a.element_begin ( ), a.element_end ( ),
            b.element_begin ( ),
            result.element_begin ( ),
            binary_operation ) ;

return result ;
}


//

template < class T, size_t N1, size_t N2 >
inline fixed_matrix < T, N1, N2 >
         outer_product ( const fixed_vector < T, N1 > & a,
                         const fixed_vector < T, N2 > & b )

{
fixed_matrix < T, N1, N2 > result ;

for ( size_t n1 = 0 ; n1 < N1 ; ++ n1 )
  for ( size_t n2 = 0 ; n2 < N2 ; ++ n2 )
    result ( n1, n2 ) = a [ n1 ] * b [ n2 ] ;

return result ;
}


//

template < class T, size_t N1, size_t N2 >
inline fixed_vector < T, N1 >
         operator * ( const fixed_matrix < T, N1, N2 > & m,
                      const fixed_vector < T, N2 > & v )

{
fixed_vector < T, N1 > result ;

for ( size_t n1 = 0 ; n1 < N1 ; ++ n1 )
  {
  T s ( 0 ) ;

  for ( size_t n2 = 0 ; n2 < N2 ; ++ n2 )
    s += m ( n1, n2 ) * v [ n2 ] ;

  result [ n1 ] = s ;
  }

return result ;
}


//

template < class T, size_t N1, size_t N2 >
inline fixed_vector < T, N2 >
         operator * ( const fixed_vector < T, N1 > & v,
                      const fixed_matrix < T, N1, N2 > & m )

{
fixed_vector < T, N2 > result ;

for ( size_t n2 = 0 ; n2 < N2 ; ++ n2 )
  {
  T s ( 0 ) ;

  for ( size_t n1 = 0 ; n1 < N1 ; ++ n1 )
    s += v [ n1 ] * m ( n1, n2 ) ;

  result [ n2 ] = s ;
  }

return result ;
}


//

template < class T, size_t N1, size_t L, size_t N2 >
inline fixed_matrix < T, N1, N2 >
         operator * ( const fixed_matrix < T, N1, L > & a,
                      const fixed_matrix < T, L, N2 > & b )

{
fixed_matrix < T, N1, N2 > result ;

for ( size_t n1 = 0 ; n1 < N1 ; ++ n1 )
  for ( size_t n2 = 0 ; n2 < N2 ; ++ n2 )
    {
    T s ( 0 ) ;

    for ( size_t l = 0 ; l < L ; ++ l )
      s += a ( n1, l ) * b ( l, n2 ) ;

    result ( n1, n2 ) = s ;
    }

return result ;
}



// *** FIXED_MATRIX INDEXING_TRAITS ***


template < class T, size_t N1, size_t N2 >
class indexing_traits < fixed_matrix < T, N1, N2 > >

{
public:

  typedef size_t index_type ;
  typedef T value_type [ N2 ] ;

  static constexpr size_t size ( const fixed_matrix < T, N1, N2 > & x )
    { return N1 ; }

} ;



// *** FIXED_LOWER_TRIANGULAR_MATRIX ***


template < class T, size_t N >
class fixed_lower_triangular_matrix

{
public:

  static_assert ( N > 0, "Size of fixed_lower_triangular_matrix == 0." ) ;

  typedef T value_type ;

  typedef size_t size_type ;
  typedef ptrdiff_t difference_type ;

  typedef value_type * pointer ;
  typedef const value_type * const_pointer ;

  typedef value_type & reference ;
  typedef const value_type & const_reference ;

  typedef pointer iterator ;
  typedef const_pointer const_iterator ;

  typedef :: reverse_iterator < iterator > reverse_iterator ;
  typedef :: reverse_iterator < const_iterator > const_reverse_iterator ;

  T elements [ ( N * ( N + 1 ) ) >> 1 ] ;

  constexpr size_t size ( ) noexcept
    { return ( N * ( N + 1 ) ) >> 1 ; }

  constexpr bool empty ( ) noexcept
    { return false ; }

  pointer data ( ) noexcept
    { return elements ; }

  const_pointer data ( ) const noexcept
    { return elements ; }

  iterator begin ( ) noexcept
    { return data ( ) ; }

  const_iterator begin ( ) const noexcept
    { return data ( ) ; }

  iterator end ( ) noexcept
    { return data ( ) + size ( ) ; }

  const_iterator end ( ) const noexcept
    { return data ( ) + size ( ) ; }

  reverse_iterator rbegin ( ) noexcept
    { return reverse_iterator ( end ( ) ) ; }

  const_reverse_iterator rbegin ( ) const noexcept
    { return const_reverse_iterator ( end ( ) ) ; }

  reverse_iterator rend ( ) noexcept
    { return reverse_iterator ( begin ( ) ) ; }

  const_reverse_iterator rend ( ) const noexcept
    { return const_reverse_iterator ( begin ( ) ) ; }

  const_iterator cbegin ( ) const noexcept
    { return begin ( ) ; }

  const_iterator cend ( ) const noexcept
    { return end ( ) ; }

  const_reverse_iterator crbegin ( ) const noexcept
    { return rbegin ( ) ; }

  const_reverse_iterator crend ( ) const noexcept
    { return rend ( ) ; }

  pointer operator [ ] ( size_t n1 ) noexcept
    { assert ( n1 < N ) ;
      return elements + ( ( n1 * ( n1 + 1 ) ) >> 1 ) ; }

  const_pointer operator [ ] ( size_t n1 ) const noexcept
    { assert ( n1 < N ) ;
      return elements + ( ( n1 * ( n1 + 1 ) ) >> 1 ) ; }

  reference at ( size_t n1, size_t n2 ) noexcept
    { assert ( n2 <= n1 ) ;
      return ( * this ) [ n1 ] [ n2 ] ; }

  const_reference at ( size_t n1, size_t n2 ) const noexcept
    { assert ( n2 <= n1 ) ;
      return ( * this ) [ n1 ] [ n2 ] ; }

  reference operator ( ) ( size_t n1, size_t n2 ) noexcept
    { return at ( n1, n2 ) ; }

  const_reference operator ( ) ( size_t n1, size_t n2 ) const noexcept
    { return at ( n1, n2 ) ; }

  T symmetric_at ( size_t n1, size_t n2 ) const
    { return n2 <= n1 ? at ( n1, n2 ) : at ( n2, n1 ) ; }

  T complete_at ( size_t n1, size_t n2 ) const
    { return n2 <= n1 ? at ( n1, n2 ) : T ( 0 ) ; }

  reference front ( ) noexcept
    { return elements [ 0 ] ; }

  const_reference front ( ) const noexcept
    { return elements [ 0 ] ; }

  reference back ( ) noexcept
    { return elements [ size ( ) - 1 ] ; }

  const_reference back ( ) const noexcept
    { return elements [ size ( ) - 1 ] ; }

  void fill ( const T & x )
    { :: fill ( begin ( ), end ( ), x ) ; }

  void swap ( fixed_lower_triangular_matrix & b )
    noexcept ( noexcept ( swap ( declval < T & > ( ), declval < T & > ( ) ) ) )
    { swap_ranges ( begin ( ), end ( ), b.begin ( ) ) ; }

  const fixed_lower_triangular_matrix & operator + ( ) const
    { return * this ; }

  fixed_lower_triangular_matrix operator - ( ) const
    { fixed_lower_triangular_matrix result ;
      transform ( begin ( ), end ( ),
                  result.begin ( ),
                  :: negate < T > ( ) ) ;
      return result ; }

  friend fixed_lower_triangular_matrix
           operator + ( const fixed_lower_triangular_matrix & a,
                        const fixed_lower_triangular_matrix & b )
    { fixed_lower_triangular_matrix result ;
      transform ( a.begin ( ), a.end ( ),
                  b.begin ( ),
                  result.begin ( ),
                  plus < T > ( ) ) ;
      return result ; }

  friend fixed_lower_triangular_matrix
           operator - ( const fixed_lower_triangular_matrix & a,
                        const fixed_lower_triangular_matrix & b )
    { fixed_lower_triangular_matrix result ;
      transform ( a.begin ( ), a.end ( ),
                  b.begin ( ),
                  result.begin ( ),
                  minus < T > ( ) ) ;
      return result ; }

  friend fixed_lower_triangular_matrix
           operator * ( const fixed_lower_triangular_matrix & a, const T & b )
    { fixed_lower_triangular_matrix result ;
      transform ( a.begin ( ), a.end ( ),
                  result.begin ( ),
                  [ & ] ( const T & x ) { return x * b ; } ) ;
      return result ; }

  friend fixed_lower_triangular_matrix
           operator * ( const T & a, const fixed_lower_triangular_matrix & b )
    { fixed_lower_triangular_matrix result ;
      transform ( b.begin ( ), b.end ( ),
                  result.begin ( ),
                  [ & ] ( const T & x ) { return a * x ; } ) ;
      return result ; }

  friend fixed_lower_triangular_matrix
           operator / ( const fixed_lower_triangular_matrix & a, const T & b )
    { fixed_lower_triangular_matrix result ;
      transform ( a.begin ( ), a.end ( ),
                  result.begin ( ),
                  [ & ] ( const T & x ) { return x / b ; } ) ;
      return result ; }

  friend fixed_lower_triangular_matrix
           operator % ( const fixed_lower_triangular_matrix & a, const T & b )
    { fixed_lower_triangular_matrix result ;
      transform ( a.begin ( ), a.end ( ),
                  result.begin ( ),
                  [ & ] ( const T & x ) { return x % b ; } ) ;
      return result ; }

  fixed_lower_triangular_matrix & negate ( )
    { for ( T & x : elements )
        x = - x ;
      return * this ; }

  fixed_lower_triangular_matrix &
    operator += ( const fixed_lower_triangular_matrix & b )
    { for_each_pair ( begin ( ), end ( ),
                      b.begin ( ),
                      [ ] ( T & x, const T & y ) { x += y ; } ) ;
      return * this ; }

  fixed_lower_triangular_matrix &
    operator -= ( const fixed_lower_triangular_matrix & b )
    { for_each_pair ( begin ( ), end ( ),
                      b.begin ( ),
                      [ ] ( T & x, const T & y ) { x -= y ; } ) ;
      return * this ; }

  fixed_lower_triangular_matrix & operator *= ( const T & b )
    { for ( T & x : elements )
        x *= b ;
      return * this ; }

  fixed_lower_triangular_matrix & operator *=
    ( const fixed_lower_triangular_matrix & b )
    { return * this = * this * b ; }

  fixed_lower_triangular_matrix & operator /= ( const T & b )
    { for ( T & x : elements )
        x /= b ;
      return * this ; }

  fixed_lower_triangular_matrix & operator %= ( const T & b )
    { for ( T & x : elements )
        x %= b ;
      return * this ; }

  friend bool operator == ( const fixed_lower_triangular_matrix & a,
                            const fixed_lower_triangular_matrix & b )
    { return equal ( a.begin ( ), a.end ( ), b.begin ( ) ) ; }

  friend bool operator < ( const fixed_lower_triangular_matrix & a,
                           const fixed_lower_triangular_matrix & b )
    { return lexicographical_compare ( a.begin ( ), a.end ( ),
                                       b.begin ( ), b.end ( ) ) ; }

  friend void swap ( fixed_lower_triangular_matrix & a,
                     fixed_lower_triangular_matrix & b )
    { a.swap ( b ) ; }

  template < class CharT, class CharTraits >
  friend basic_ostream < CharT, CharTraits > &
    operator << ( basic_ostream < CharT, CharTraits > & o,
                  const fixed_lower_triangular_matrix & x )
    { return output_array ( o, x.elements ) ; }

  template < class CharT, class CharTraits >
  friend basic_istream < CharT, CharTraits > &
    operator >> ( basic_istream < CharT, CharTraits > & i,
                  fixed_lower_triangular_matrix & x )
    { fixed_lower_triangular_matrix tx ;
      input_array ( i, tx.elements ) ;
      if ( i.good ( ) )
        x = move ( tx ) ;
      return i ; }

} ;


//

template < class T, size_t N, class UnaryOperation >
inline fixed_lower_triangular_matrix < T, N >
         componentwise ( const fixed_lower_triangular_matrix < T, N > & a,
                         UnaryOperation unary_operation )

{
fixed_lower_triangular_matrix < T, N > result ;

transform ( a.begin ( ), a.end ( ),
            result.begin ( ),
            unary_operation ) ;

return result ;
}


//

template < class T, size_t N, class BinaryOperation >
inline fixed_lower_triangular_matrix < T, N >
         componentwise ( const fixed_lower_triangular_matrix < T, N > & a,
                         const fixed_lower_triangular_matrix < T, N > & b,
                         BinaryOperation binary_operation )

{
fixed_lower_triangular_matrix < T, N > result ;

transform ( a.begin ( ), a.end ( ),
            b.begin ( ),
            result.begin ( ),
            binary_operation ) ;

return result ;
}


//

template < class T, size_t N >
inline fixed_vector < T, N >
         operator * ( const fixed_lower_triangular_matrix < T, N > & m,
                      const fixed_vector < T, N > & v )

{
fixed_vector < T, N > result ;

for ( size_t n1 = 0 ; n1 < N ; ++ n1 )
  {
  T s ( 0 ) ;

  for ( size_t n2 = 0 ; n2 <= n1 ; ++ n2 )
    s += m ( n1, n2 ) * v [ n2 ] ;

  result [ n1 ] = s ;
  }

return result ;
}


//

template < class T, size_t N >
inline fixed_vector < T, N >
         operator * ( const fixed_vector < T, N > & v,
                      const fixed_lower_triangular_matrix < T, N > & m )

{
fixed_vector < T, N > result ;

for ( size_t n2 = 0 ; n2 < N ; ++ n2 )
  {
  T s ( 0 ) ;

  for ( size_t n1 = n2 ; n1 < N ; ++ n1 )
    s += v [ n1 ] * m ( n1, n2 ) ;

  result [ n2 ] = s ;
  }

return result ;
}


//

template < class T, size_t N1, size_t N2 >
inline fixed_matrix < T, N1, N2 >
         operator * ( const fixed_lower_triangular_matrix < T, N1 > & a,
                      const fixed_matrix < T, N1, N2 > & b )

{
fixed_matrix < T, N1, N2 > result ;

for ( size_t n1 = 0 ; n1 < N1 ; ++ n1 )
  for ( size_t n2 = 0 ; n2 < N2 ; ++ n2 )
    {
    T s ( 0 ) ;

    for ( size_t l = 0 ; l <= n1 ; ++ l )
      s += a ( n1, l ) * b ( l, n2 ) ;

    result ( n1, n2 ) = s ;
    }

return result ;
}


//

template < class T, size_t N1, size_t N2 >
inline fixed_matrix < T, N1, N2 >
         operator * ( const fixed_matrix < T, N1, N2 > & a,
                      const fixed_lower_triangular_matrix < T, N2 > & b )

{
fixed_matrix < T, N1, N2 > result ;

for ( size_t n1 = 0 ; n1 < N1 ; ++ n1 )
  for ( size_t n2 = 0 ; n2 < N2 ; ++ n2 )
    {
    T s ( 0 ) ;

    for ( size_t l = n2 ; l < N2 ; ++ l )
      s += a ( n1, l ) * b ( l, n2 ) ;

    result ( n1, n2 ) = s ;
    }

return result ;
}


//

template < class T, size_t N >
inline fixed_lower_triangular_matrix < T, N >
         operator * ( const fixed_lower_triangular_matrix < T, N > & a,
                      const fixed_lower_triangular_matrix < T, N > & b )

{
fixed_lower_triangular_matrix < T, N > result ;

for ( size_t n1 = 0 ; n1 < N ; ++ n1 )
  for ( size_t n2 = 0 ; n2 <= n1 ; ++ n2 )
    {
    T s ( 0 ) ;

    for ( size_t l = n2 ; l <= n1 ; ++ l )
      s += a ( n1, l ) * b ( l, n2 ) ;

    result ( n1, n2 ) = s ;
    }

return result ;
}


//

template < class T, size_t N >
inline fixed_matrix < T, N, N >
         make_symmetric ( const fixed_lower_triangular_matrix < T, N > & m )

{
fixed_matrix < T, N, N > result ;

for ( size_t n1 = 0 ; n1 < N ; ++ n1 )
  for ( size_t n2 = 0 ; n2 < N ; ++ n2 )
    result ( n1, n2 ) = m.symmetric_at ( n1, n2 ) ;

return result ;
}


//

template < class T, size_t N >
inline fixed_matrix < T, N, N >
         make_complete ( const fixed_lower_triangular_matrix < T, N > & m )

{
fixed_matrix < T, N, N > result ;

for ( size_t n1 = 0 ; n1 < N ; ++ n1 )
  for ( size_t n2 = 0 ; n2 < N ; ++ n2 )
    result ( n1, n2 ) = m.complete_at ( n1, n2 ) ;

return result ;
}



// *** FIXED_LOWER_TRIANGULAR_MATRIX INDEXING_TRAITS ***


template < class T, size_t N >
class indexing_traits < fixed_lower_triangular_matrix < T, N > >

{
public:

  typedef size_t index_type ;
  typedef T * value_type ;

  static constexpr
    size_t size ( const fixed_lower_triangular_matrix < T, N > & x )
    { return N ; }

} ;



// *** FIXED_UPPER_TRIANGULAR_MATRIX ***


template < class T, size_t N >
class fixed_upper_triangular_matrix

{
public:

  static_assert ( N > 0, "Size of fixed_upper_triangular_matrix == 0." ) ;

  typedef T value_type ;

  typedef size_t size_type ;
  typedef ptrdiff_t difference_type ;

  typedef value_type * pointer ;
  typedef const value_type * const_pointer ;

  typedef value_type & reference ;
  typedef const value_type & const_reference ;

  typedef pointer iterator ;
  typedef const_pointer const_iterator ;

  typedef :: reverse_iterator < iterator > reverse_iterator ;
  typedef :: reverse_iterator < const_iterator > const_reverse_iterator ;

  T elements [ ( N * ( N + 1 ) ) >> 1 ] ;

  constexpr size_t size ( ) noexcept
    { return ( N * ( N + 1 ) ) >> 1 ; }

  constexpr bool empty ( ) noexcept
    { return false ; }

  pointer data ( ) noexcept
    { return elements ; }

  const_pointer data ( ) const noexcept
    { return elements ; }

  iterator begin ( ) noexcept
    { return data ( ) ; }

  const_iterator begin ( ) const noexcept
    { return data ( ) ; }

  iterator end ( ) noexcept
    { return data ( ) + size ( ) ; }

  const_iterator end ( ) const noexcept
    { return data ( ) + size ( ) ; }

  reverse_iterator rbegin ( ) noexcept
    { return reverse_iterator ( end ( ) ) ; }

  const_reverse_iterator rbegin ( ) const noexcept
    { return const_reverse_iterator ( end ( ) ) ; }

  reverse_iterator rend ( ) noexcept
    { return reverse_iterator ( begin ( ) ) ; }

  const_reverse_iterator rend ( ) const noexcept
    { return const_reverse_iterator ( begin ( ) ) ; }

  const_iterator cbegin ( ) const noexcept
    { return begin ( ) ; }

  const_iterator cend ( ) const noexcept
    { return end ( ) ; }

  const_reverse_iterator crbegin ( ) const noexcept
    { return rbegin ( ) ; }

  const_reverse_iterator crend ( ) const noexcept
    { return rend ( ) ; }

  pointer operator [ ] ( size_t n1 ) noexcept
    { assert ( n1 < N ) ;
      return elements + ( ( n1 * ( ( N << 1 ) + 1 - n1 ) ) >> 1 ) ; }

  const_pointer operator [ ] ( size_t n1 ) const noexcept
    { assert ( n1 < N ) ;
      return elements + ( ( n1 * ( ( N << 1 ) + 1 - n1 ) ) >> 1 ) ; }

  reference at ( size_t n1, size_t n2 ) noexcept
    { assert ( n2 >= n1 ) ;
      assert ( n2 < N ) ;
      return ( * this ) [ n1 ] [ n2 - n1 ] ; }

  const_reference at ( size_t n1, size_t n2 ) const noexcept
    { assert ( n2 >= n1 ) ;
      assert ( n2 < N ) ;
      return ( * this ) [ n1 ] [ n2 - n1 ] ; }

  reference operator ( ) ( size_t n1, size_t n2 ) noexcept
    { return at ( n1, n2 ) ; }

  const_reference operator ( ) ( size_t n1, size_t n2 ) const noexcept
    { return at ( n1, n2 ) ; }

  T symmetric_at ( size_t n1, size_t n2 ) const
    { return n2 >= n1 ? at ( n1, n2 ) : at ( n2, n1 ) ; }

  T complete_at ( size_t n1, size_t n2 ) const
    { return n2 >= n1 ? at ( n1, n2 ) : T ( 0 ) ; }

  reference front ( ) noexcept
    { return elements [ 0 ] ; }

  const_reference front ( ) const noexcept
    { return elements [ 0 ] ; }

  reference back ( ) noexcept
    { return elements [ size ( ) - 1 ] ; }

  const_reference back ( ) const noexcept
    { return elements [ size ( ) - 1 ] ; }

  void fill ( const T & x )
    { :: fill ( begin ( ), end ( ), x ) ; }

  void swap ( fixed_upper_triangular_matrix & b )
    noexcept ( noexcept ( swap ( declval < T & > ( ), declval < T & > ( ) ) ) )
    { swap_ranges ( begin ( ), end ( ), b.begin ( ) ) ; }

  const fixed_upper_triangular_matrix & operator + ( ) const
    { return * this ; }

  fixed_upper_triangular_matrix operator - ( ) const
    { fixed_upper_triangular_matrix result ;
      transform ( begin ( ), end ( ),
                  result.begin ( ),
                  :: negate < T > ( ) ) ;
      return result ; }

  friend fixed_upper_triangular_matrix
           operator + ( const fixed_upper_triangular_matrix & a,
                        const fixed_upper_triangular_matrix & b )
    { fixed_upper_triangular_matrix result ;
      transform ( a.begin ( ), a.end ( ),
                  b.begin ( ),
                  result.begin ( ),
                  plus < T > ( ) ) ;
      return result ; }

  friend fixed_upper_triangular_matrix
           operator - ( const fixed_upper_triangular_matrix & a,
                        const fixed_upper_triangular_matrix & b )
    { fixed_upper_triangular_matrix result ;
      transform ( a.begin ( ), a.end ( ),
                  b.begin ( ),
                  result.begin ( ),
                  minus < T > ( ) ) ;
      return result ; }

  friend fixed_upper_triangular_matrix
           operator * ( const fixed_upper_triangular_matrix & a, const T & b )
    { fixed_upper_triangular_matrix result ;
      transform ( a.begin ( ), a.end ( ),
                  result.begin ( ),
                  [ & ] ( const T & x ) { return x * b ; } ) ;
      return result ; }

  friend fixed_upper_triangular_matrix
           operator * ( const T & a, const fixed_upper_triangular_matrix & b )
    { fixed_upper_triangular_matrix result ;
      transform ( b.begin ( ), b.end ( ),
                  result.begin ( ),
                  [ & ] ( const T & x ) { return a * x ; } ) ;
      return result ; }

  friend fixed_upper_triangular_matrix
           operator / ( const fixed_upper_triangular_matrix & a, const T & b )
    { fixed_upper_triangular_matrix result ;
      transform ( a.begin ( ), a.end ( ),
                  result.begin ( ),
                  [ & ] ( const T & x ) { return x / b ; } ) ;
      return result ; }

  friend fixed_upper_triangular_matrix
           operator % ( const fixed_upper_triangular_matrix & a, const T & b )
    { fixed_upper_triangular_matrix result ;
      transform ( a.begin ( ), a.end ( ),
                  result.begin ( ),
                  [ & ] ( const T & x ) { return x % b ; } ) ;
      return result ; }

  fixed_upper_triangular_matrix & negate ( )
    { for ( T & x : elements )
        x = - x ;
      return * this ; }

  fixed_upper_triangular_matrix &
    operator += ( const fixed_upper_triangular_matrix & b )
    { for_each_pair ( begin ( ), end ( ),
                      b.begin ( ),
                      [ ] ( T & x, const T & y ) { x += y ; } ) ;
      return * this ; }

  fixed_upper_triangular_matrix &
    operator -= ( const fixed_upper_triangular_matrix & b )
    { for_each_pair ( begin ( ), end ( ),
                      b.begin ( ),
                      [ ] ( T & x, const T & y ) { x -= y ; } ) ;
      return * this ; }

  fixed_upper_triangular_matrix & operator *= ( const T & b )
    { for ( T & x : elements )
        x *= b ;
      return * this ; }

  fixed_upper_triangular_matrix & operator *=
    ( const fixed_upper_triangular_matrix & b )
    { return * this = * this * b ; }

  fixed_upper_triangular_matrix & operator /= ( const T & b )
    { for ( T & x : elements )
        x /= b ;
      return * this ; }

  fixed_upper_triangular_matrix & operator %= ( const T & b )
    { for ( T & x : elements )
        x %= b ;
      return * this ; }

  friend bool operator == ( const fixed_upper_triangular_matrix & a,
                            const fixed_upper_triangular_matrix & b )
    { return equal ( a.begin ( ), a.end ( ), b.begin ( ) ) ; }

  friend bool operator < ( const fixed_upper_triangular_matrix & a,
                           const fixed_upper_triangular_matrix & b )
    { return lexicographical_compare ( a.begin ( ), a.end ( ),
                                       b.begin ( ), b.end ( ) ) ; }

  friend void swap ( fixed_upper_triangular_matrix & a,
                     fixed_upper_triangular_matrix & b )
    { a.swap ( b ) ; }

  template < class CharT, class CharTraits >
  friend basic_ostream < CharT, CharTraits > &
    operator << ( basic_ostream < CharT, CharTraits > & o,
                  const fixed_upper_triangular_matrix & x )
    { return output_array ( o, x.elements ) ; }

  template < class CharT, class CharTraits >
  friend basic_istream < CharT, CharTraits > &
    operator >> ( basic_istream < CharT, CharTraits > & i,
                  fixed_upper_triangular_matrix & x )
    { fixed_upper_triangular_matrix tx ;
      input_array ( i, tx.elements ) ;
      if ( i.good ( ) )
        x = move ( tx ) ;
      return i ; }

} ;


//

template < class T, size_t N, class UnaryOperation >
inline fixed_upper_triangular_matrix < T, N >
         componentwise ( const fixed_upper_triangular_matrix < T, N > & a,
                         UnaryOperation unary_operation )

{
fixed_upper_triangular_matrix < T, N > result ;

transform ( a.begin ( ), a.end ( ),
            result.begin ( ),
            unary_operation ) ;

return result ;
}


//

template < class T, size_t N, class BinaryOperation >
inline fixed_upper_triangular_matrix < T, N >
         componentwise ( const fixed_upper_triangular_matrix < T, N > & a,
                         const fixed_upper_triangular_matrix < T, N > & b,
                         BinaryOperation binary_operation )

{
fixed_upper_triangular_matrix < T, N > result ;

transform ( a.begin ( ), a.end ( ),
            b.begin ( ),
            result.begin ( ),
            binary_operation ) ;

return result ;
}


//

template < class T, size_t N >
inline fixed_vector < T, N >
         operator * ( const fixed_upper_triangular_matrix < T, N > & m,
                      const fixed_vector < T, N > & v )

{
fixed_vector < T, N > result ;

for ( size_t n1 = 0 ; n1 < N ; ++ n1 )
  {
  T s ( 0 ) ;

  for ( size_t n2 = n1 ; n2 < N ; ++ n2 )
    s += m ( n1, n2 ) * v [ n2 ] ;

  result [ n1 ] = s ;
  }

return result ;
}


//

template < class T, size_t N >
inline fixed_vector < T, N >
         operator * ( const fixed_vector < T, N > & v,
                      const fixed_upper_triangular_matrix < T, N > & m )

{
fixed_vector < T, N > result ;

for ( size_t n2 = 0 ; n2 < N ; ++ n2 )
  {
  T s ( 0 ) ;

  for ( size_t n1 = 0 ; n1 <= n2 ; ++ n1 )
    s += v [ n1 ] * m ( n1, n2 ) ;

  result [ n2 ] = s ;
  }

return result ;
}


//

template < class T, size_t N1, size_t N2 >
inline fixed_matrix < T, N1, N2 >
         operator * ( const fixed_upper_triangular_matrix < T, N1 > & a,
                      const fixed_matrix < T, N1, N2 > & b )

{
fixed_matrix < T, N1, N2 > result ;

for ( size_t n1 = 0 ; n1 < N1 ; ++ n1 )
  for ( size_t n2 = 0 ; n2 < N2 ; ++ n2 )
    {
    T s ( 0 ) ;

    for ( size_t l = n1 ; l < N1 ; ++ l )
      s += a ( n1, l ) * b ( l, n2 ) ;

    result ( n1, n2 ) = s ;
    }

return result ;
}


//

template < class T, size_t N1, size_t N2 >
inline fixed_matrix < T, N1, N2 >
         operator * ( const fixed_matrix < T, N1, N2 > & a,
                      const fixed_upper_triangular_matrix < T, N2 > & b )

{
fixed_matrix < T, N1, N2 > result ;

for ( size_t n1 = 0 ; n1 < N1 ; ++ n1 )
  for ( size_t n2 = 0 ; n2 < N2 ; ++ n2 )
    {
    T s ( 0 ) ;

    for ( size_t l = 0 ; l <= n2 ; ++ l )
      s += a ( n1, l ) * b ( l, n2 ) ;

    result ( n1, n2 ) = s ;
    }

return result ;
}


//

template < class T, size_t N >
inline fixed_upper_triangular_matrix < T, N >
         operator * ( const fixed_upper_triangular_matrix < T, N > & a,
                      const fixed_upper_triangular_matrix < T, N > & b )

{
fixed_upper_triangular_matrix < T, N > result ;

for ( size_t n1 = 0 ; n1 < N ; ++ n1 )
  for ( size_t n2 = 0 ; n2 <= n1 ; ++ n2 )
    {
    T s ( 0 ) ;

    for ( size_t l = n1 ; l <= n2 ; ++ l )
      s += a ( n1, l ) * b ( l, n2 ) ;

    result ( n1, n2 ) = s ;
    }

return result ;
}


//

template < class T, size_t N >
inline fixed_matrix < T, N, N >
         make_symmetric ( const fixed_upper_triangular_matrix < T, N > & m )

{
fixed_matrix < T, N, N > result ;

for ( size_t n1 = 0 ; n1 < N ; ++ n1 )
  for ( size_t n2 = 0 ; n2 < N ; ++ n2 )
    result ( n1, n2 ) = m.symmetric_at ( n1, n2 ) ;

return result ;
}


//

template < class T, size_t N >
inline fixed_matrix < T, N, N >
         make_complete ( const fixed_upper_triangular_matrix < T, N > & m )

{
fixed_matrix < T, N, N > result ;

for ( size_t n1 = 0 ; n1 < N ; ++ n1 )
  for ( size_t n2 = 0 ; n2 < N ; ++ n2 )
    result ( n1, n2 ) = m.complete_at ( n1, n2 ) ;

return result ;
}



// *** FIXED_UPPER_TRIANGULAR_MATRIX INDEXING_TRAITS ***


template < class T, size_t N >
class indexing_traits < fixed_upper_triangular_matrix < T, N > >

{
public:

  typedef size_t index_type ;
  typedef T * value_type ;

  static constexpr
    size_t size ( const fixed_upper_triangular_matrix < T, N > & x )
    { return N ; }

} ;



#endif
