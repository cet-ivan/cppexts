// Copyright Ivan Stanojevic 2021.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __FSVM_H

#define __FSVM_H



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


template < class T, size_t N >
class fs_vector ;

template < class T, size_t N1, size_t N2 >
class fs_matrix ;

template < class T, size_t N >
class fs_lower_triangular_matrix ;

template < class T, size_t N >
class fs_upper_triangular_matrix ;



// *** FS_VECTOR FORWARD_DECLARATIONS ***


template < class T, size_t N >
fs_vector < T, N > operator + ( const fs_vector < T, N > & a,
                                const fs_vector < T, N > & b ) ;

template < class T, size_t N >
fs_vector < T, N > operator - ( const fs_vector < T, N > & a,
                                const fs_vector < T, N > & b ) ;

template < class T, size_t N >
T operator * ( const fs_vector < T, N > & a,
               const fs_vector < T, N > & b ) ;

template < class T, size_t N >
fs_vector < T, N > operator * ( const fs_vector < T, N > & a,
                                const T & b ) ;

template < class T, size_t N >
fs_vector < T, N > operator * ( const T & a,
                                const fs_vector < T, N > & b ) ;

template < class T, size_t N >
fs_vector < T, N > operator / ( const fs_vector < T, N > & a,
                                const T & b ) ;

template < class T, size_t N >
fs_vector < T, N > operator % ( const fs_vector < T, N > & a,
                                const T & b ) ;

template < class T, size_t N >
bool operator == ( const fs_vector < T, N > & a,
                   const fs_vector < T, N > & b ) ;

template < class T, size_t N >
bool operator < ( const fs_vector < T, N > & a,
                  const fs_vector < T, N > & b ) ;

template < class T, size_t N >
void swap ( fs_vector < T, N > & a, fs_vector < T, N > & b ) ;

template < class T, size_t N, class UnaryOperation >
fs_vector < T, N > componentwise ( const fs_vector < T, N > & a,
                                   UnaryOperation unary_operation ) ;

template < class T, size_t N, class BinaryOperation >
fs_vector < T, N > componentwise ( const fs_vector < T, N > & a,
                                   const fs_vector < T, N > & b,
                                   BinaryOperation binary_operation ) ;

template < class T, size_t N >
T inner_product ( const fs_vector < T, N > & a,
                  const fs_vector < T, N > & b ) ;

template < class T, size_t N >
inline T norm ( const fs_vector < T, N > & a ) ;



// *** FS_MATRIX FORWARD_DECLARATIONS ***


template < class T, size_t N1, size_t N2 >
fs_matrix < T, N1, N2 > operator + ( const fs_matrix < T, N1, N2 > & a,
                                     const fs_matrix < T, N1, N2 > & b ) ;

template < class T, size_t N1, size_t N2 >
fs_matrix < T, N1, N2 > operator - ( const fs_matrix < T, N1, N2 > & a,
                                     const fs_matrix < T, N1, N2 > & b ) ;

template < class T, size_t N1, size_t N2 >
fs_matrix < T, N1, N2 > operator * ( const fs_matrix < T, N1, N2 > & a,
                                     const T & b ) ;

template < class T, size_t N1, size_t N2 >
fs_matrix < T, N1, N2 > operator * ( const T & a,
                                     const fs_matrix < T, N1, N2 > & b ) ;

template < class T, size_t N1, size_t N2 >
fs_matrix < T, N1, N2 > operator / ( const fs_matrix < T, N1, N2 > & a,
                                     const T & b ) ;

template < class T, size_t N1, size_t N2 >
fs_matrix < T, N1, N2 > operator % ( const fs_matrix < T, N1, N2 > & a,
                                     const T & b ) ;

template < class T, size_t N1, size_t N2 >
bool operator == ( const fs_matrix < T, N1, N2 > & a,
                   const fs_matrix < T, N1, N2 > & b ) ;

template < class T, size_t N1, size_t N2 >
bool operator < ( const fs_matrix < T, N1, N2 > & a,
                  const fs_matrix < T, N1, N2 > & b ) ;

template < class T, size_t N1, size_t N2 >
void swap ( fs_matrix < T, N1, N2 > & a, fs_matrix < T, N1, N2 > & b ) ;

template < class T, size_t N1, size_t N2, class UnaryOperation >
fs_matrix < T, N1, N2 >
  componentwise ( const fs_matrix < T, N1, N2 > & a,
                  UnaryOperation unary_operation ) ;

template < class T, size_t N1, size_t N2, class BinaryOperation >
fs_matrix < T, N1, N2 >
  componentwise ( const fs_matrix < T, N1, N2 > & a,
                  const fs_matrix < T, N1, N2 > & b,
                  BinaryOperation binary_operation ) ;

template < class T, size_t N1, size_t N2 >
fs_matrix < T, N1, N2 > outer_product ( const fs_vector < T, N1 > & a,
                                        const fs_vector < T, N2 > & b ) ;

template < class T, size_t N1, size_t N2 >
fs_vector < T, N1 > operator * ( const fs_matrix < T, N1, N2 > & m,
                                 const fs_vector < T, N2 > & v ) ;

template < class T, size_t N1, size_t N2 >
fs_vector < T, N2 > operator * ( const fs_vector < T, N1 > & v,
                                 const fs_matrix < T, N1, N2 > & m ) ;

template < class T, size_t N1, size_t N2, size_t N3 >
fs_matrix < T, N1, N3 > operator * ( const fs_matrix < T, N1, N2 > & a,
                                     const fs_matrix < T, N2, N3 > & b ) ;



// *** FS_LOWER_TRIANGULAR_MATRIX FORWARD_DECLARATIONS ***


template < class T, size_t N >
fs_lower_triangular_matrix < T, N >
  operator + ( const fs_lower_triangular_matrix < T, N > & a,
               const fs_lower_triangular_matrix < T, N > & b ) ;

template < class T, size_t N >
fs_lower_triangular_matrix < T, N >
  operator - ( const fs_lower_triangular_matrix < T, N > & a,
               const fs_lower_triangular_matrix < T, N > & b ) ;

template < class T, size_t N >
fs_lower_triangular_matrix < T, N >
  operator * ( const fs_lower_triangular_matrix < T, N > & a, const T & b ) ;

template < class T, size_t N >
fs_lower_triangular_matrix < T, N >
  operator * ( const T & a, const fs_lower_triangular_matrix < T, N > & b ) ;

template < class T, size_t N >
fs_lower_triangular_matrix < T, N >
  operator / ( const fs_lower_triangular_matrix < T, N > & a, const T & b ) ;

template < class T, size_t N >
fs_lower_triangular_matrix < T, N >
  operator % ( const fs_lower_triangular_matrix < T, N > & a, const T & b ) ;

template < class T, size_t N >
bool operator == ( const fs_lower_triangular_matrix < T, N > & a,
                   const fs_lower_triangular_matrix < T, N > & b ) ;

template < class T, size_t N >
bool operator < ( const fs_lower_triangular_matrix < T, N > & a,
                  const fs_lower_triangular_matrix < T, N > & b ) ;

template < class T, size_t N >
void swap ( const fs_lower_triangular_matrix < T, N > & a,
            const fs_lower_triangular_matrix < T, N > & b ) ;

template < class T, size_t N, class UnaryOperation >
fs_lower_triangular_matrix < T, N >
  componentwise ( const fs_lower_triangular_matrix < T, N > & a,
                  UnaryOperation unary_operation ) ;

template < class T, size_t N, class BinaryOperation >
fs_lower_triangular_matrix < T, N >
  componentwise ( const fs_lower_triangular_matrix < T, N > & a,
                  const fs_lower_triangular_matrix < T, N > & b,
                  BinaryOperation binary_operation ) ;

template < class T, size_t N >
fs_vector < T, N >
  operator * ( const fs_lower_triangular_matrix < T, N > & m,
               const fs_vector < T, N > & v ) ;

template < class T, size_t N >
fs_vector < T, N >
  operator * ( const fs_vector < T, N > & v,
               const fs_lower_triangular_matrix < T, N > & m ) ;

template < class T, size_t N1, size_t N2 >
fs_matrix < T, N1, N2 >
  operator * ( const fs_lower_triangular_matrix < T, N1 > & a,
               const fs_matrix < T, N1, N2 > & b ) ;

template < class T, size_t N1, size_t N2 >
fs_matrix < T, N1, N2 >
  operator * ( const fs_matrix < T, N1, N2 > & a,
               const fs_lower_triangular_matrix < T, N2 > & b ) ;

template < class T, size_t N >
fs_lower_triangular_matrix < T, N >
  operator * ( const fs_lower_triangular_matrix < T, N > & a,
               const fs_lower_triangular_matrix < T, N > & b ) ;

template < class T, size_t N >
fs_matrix < T, N, N >
  make_symmetric ( const fs_lower_triangular_matrix < T, N > & m ) ;

template < class T, size_t N >
fs_matrix < T, N, N >
  make_complete ( const fs_lower_triangular_matrix < T, N > & m ) ;



// *** FS_UPPER_TRIANGULAR_MATRIX FORWARD_DECLARATIONS ***


template < class T, size_t N >
fs_upper_triangular_matrix < T, N >
  operator + ( const fs_upper_triangular_matrix < T, N > & a,
               const fs_upper_triangular_matrix < T, N > & b ) ;

template < class T, size_t N >
fs_upper_triangular_matrix < T, N >
  operator - ( const fs_upper_triangular_matrix < T, N > & a,
               const fs_upper_triangular_matrix < T, N > & b ) ;

template < class T, size_t N >
fs_upper_triangular_matrix < T, N >
  operator * ( const fs_upper_triangular_matrix < T, N > & a, const T & b ) ;

template < class T, size_t N >
fs_upper_triangular_matrix < T, N >
  operator * ( const T & a, const fs_upper_triangular_matrix < T, N > & b ) ;

template < class T, size_t N >
fs_upper_triangular_matrix < T, N >
  operator / ( const fs_upper_triangular_matrix < T, N > & a, const T & b ) ;

template < class T, size_t N >
fs_upper_triangular_matrix < T, N >
  operator % ( const fs_upper_triangular_matrix < T, N > & a, const T & b ) ;

template < class T, size_t N >
bool operator == ( const fs_upper_triangular_matrix < T, N > & a,
                   const fs_upper_triangular_matrix < T, N > & b ) ;

template < class T, size_t N >
bool operator < ( const fs_upper_triangular_matrix < T, N > & a,
                  const fs_upper_triangular_matrix < T, N > & b ) ;

template < class T, size_t N >
void swap ( const fs_upper_triangular_matrix < T, N > & a,
            const fs_upper_triangular_matrix < T, N > & b ) ;

template < class T, size_t N, class UnaryOperation >
fs_upper_triangular_matrix < T, N >
  componentwise ( const fs_upper_triangular_matrix < T, N > & a,
                  UnaryOperation unary_operation ) ;

template < class T, size_t N, class BinaryOperation >
fs_upper_triangular_matrix < T, N >
  componentwise ( const fs_upper_triangular_matrix < T, N > & a,
                  const fs_upper_triangular_matrix < T, N > & b,
                  BinaryOperation binary_operation ) ;

template < class T, size_t N >
fs_vector < T, N >
  operator * ( const fs_upper_triangular_matrix < T, N > & m,
               const fs_vector < T, N > & v ) ;

template < class T, size_t N >
fs_vector < T, N >
  operator * ( const fs_vector < T, N > & v,
               const fs_upper_triangular_matrix < T, N > & m ) ;

template < class T, size_t N1, size_t N2 >
fs_matrix < T, N1, N2 >
  operator * ( const fs_upper_triangular_matrix < T, N1 > & a,
               const fs_matrix < T, N1, N2 > & b ) ;

template < class T, size_t N1, size_t N2 >
fs_matrix < T, N1, N2 >
  operator * ( const fs_matrix < T, N1, N2 > & a,
               const fs_upper_triangular_matrix < T, N2 > & b ) ;

template < class T, size_t N >
fs_upper_triangular_matrix < T, N >
  operator * ( const fs_upper_triangular_matrix < T, N > & a,
               const fs_upper_triangular_matrix < T, N > & b ) ;

template < class T, size_t N >
fs_matrix < T, N, N >
  make_symmetric ( const fs_upper_triangular_matrix < T, N > & m ) ;

template < class T, size_t N >
fs_matrix < T, N, N >
  make_complete ( const fs_upper_triangular_matrix < T, N > & m ) ;



// *** FS_VECTOR ***


template < class T, size_t N >
class fs_vector

{
public:

  static_assert ( N > 0, "Size of fs_vector == 0." ) ;

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

  void swap ( fs_vector & b )
    noexcept ( noexcept ( swap ( declval < T & > ( ), declval < T & > ( ) ) ) )
    { swap_ranges ( begin ( ), end ( ), b.begin ( ) ) ; }

  const fs_vector & operator + ( ) const
    { return * this ; }

  fs_vector operator - ( ) const
    { fs_vector result ;
      transform ( begin ( ), end ( ),
                  result.begin ( ),
                  :: negate < T > ( ) ) ;
      return result ; }

  friend fs_vector operator + ( const fs_vector & a,
                                   const fs_vector & b )
    { fs_vector result ;
      transform ( a.begin ( ), a.end ( ),
                  b.begin ( ),
                  result.begin ( ),
                  plus < T > ( ) ) ;
      return result ; }

  friend fs_vector operator - ( const fs_vector & a,
                                   const fs_vector & b )
    { fs_vector result ;
      transform ( a.begin ( ), a.end ( ),
                  b.begin ( ),
                  result.begin ( ),
                  minus < T > ( ) ) ;
      return result ; }

  friend T operator * ( const fs_vector & a, const fs_vector & b )
    { return inner_product ( a.begin ( ), a.end ( ),
                             b.begin ( ),
                             T ( 0 ) ) ; }

  friend fs_vector operator * ( const fs_vector & a, const T & b )
    { fs_vector result ;
      transform ( a.begin ( ), a.end ( ),
                  result.begin ( ),
                  [ & ] ( const T & x ) { return x * b ; } ) ;
      return result ; }

  friend fs_vector operator * ( const T & a, const fs_vector & b )
    { fs_vector result ;
      transform ( b.begin ( ), b.end ( ),
                  result.begin ( ),
                  [ & ] ( const T & x ) { return a * x ; } ) ;
      return result ; }

  friend fs_vector operator / ( const fs_vector & a, const T & b )
    { fs_vector result ;
      transform ( a.begin ( ), a.end ( ),
                  result.begin ( ),
                  [ & ] ( const T & x ) { return x / b ; } ) ;
      return result ; }

  friend fs_vector operator % ( const fs_vector & a, const T & b )
    { fs_vector result ;
      transform ( a.begin ( ), a.end ( ),
                  result.begin ( ),
                  [ & ] ( const T & x ) { return x % b ; } ) ;
      return result ; }

  fs_vector & negate ( )
    { for ( T & x : elements )
        x = - x ;
      return * this ; }

  fs_vector & operator += ( const fs_vector & b )
    { for_each_pair ( begin ( ), end ( ),
                      b.begin ( ),
                      [ ] ( T & x, const T & y ) { x += y ; } ) ;
      return * this ; }

  fs_vector & operator -= ( const fs_vector & b )
    { for_each_pair ( begin ( ), end ( ),
                      b.begin ( ),
                      [ ] ( T & x, const T & y ) { x -= y ; } ) ;
      return * this ; }

  fs_vector & operator *= ( const T & b )
    { for ( T & x : elements )
        x *= b ;
      return * this ; }

  fs_vector & operator /= ( const T & b )
    { for ( T & x : elements )
        x /= b ;
      return * this ; }

  fs_vector & operator %= ( const T & b )
    { for ( T & x : elements )
        x %= b ;
      return * this ; }

  friend bool operator == ( const fs_vector & a, const fs_vector & b )
    { return equal ( a.begin ( ), a.end ( ), b.begin ( ) ) ; }

  friend bool operator < ( const fs_vector & a, const fs_vector & b )
    { return lexicographical_compare ( a.begin ( ), a.end ( ),
                                       b.begin ( ), b.end ( ) ) ; }

  friend void swap ( fs_vector & a, fs_vector & b )
    { a.swap ( b ) ; }

  template < class CharT, class CharTraits >
  friend basic_ostream < CharT, CharTraits > &
    operator << ( basic_ostream < CharT, CharTraits > & o,
                  const fs_vector & x )
    { return output_array ( o, x.elements ) ; }

  template < class CharT, class CharTraits >
  friend basic_istream < CharT, CharTraits > &
    operator >> ( basic_istream < CharT, CharTraits > & i,
                  fs_vector & x )
    { fs_vector tx ;
      input_array ( i, tx.elements ) ;
      if ( i.good ( ) )
        x = move ( tx ) ;
      return i ; }

} ;


//

template < class T, size_t N, class UnaryOperation >
inline fs_vector < T, N >
         componentwise ( const fs_vector < T, N > & a,
                         UnaryOperation unary_operation )

{
fs_vector < T, N > result ;

transform ( a.begin ( ), a.end ( ),
            result.begin ( ),
            unary_operation ) ;

return result ;
}


//

template < class T, size_t N, class BinaryOperation >
inline fs_vector < T, N >
         componentwise ( const fs_vector < T, N > & a,
                         const fs_vector < T, N > & b,
                         BinaryOperation binary_operation )

{
fs_vector < T, N > result ;

transform ( a.begin ( ), a.end ( ),
            b.begin ( ),
            result.begin ( ),
            binary_operation ) ;

return result ;
}


//

template < class T, size_t N >
inline T inner_product ( const fs_vector < T, N > & a,
                         const fs_vector < T, N > & b )

{
return a * b ;
}


//

template < class T, size_t N >
inline T norm ( const fs_vector < T, N > & a )

{
return a * a ;
}



// *** FS_VECTOR INDEXING_TRAITS ***


template < class T, size_t N >
class indexing_traits < fs_vector < T, N > >

{
public:

  typedef size_t index_type ;
  typedef T value_type ;

  static constexpr size_t size ( const fs_vector < T, N > & x )
    { return N ; }

} ;



// *** FS_MATRIX ***


template < class T, size_t N1, size_t N2 >
class fs_matrix

{
public:

  static_assert ( N1 > 0, "Size1 of fs_matrix == 0." ) ;
  static_assert ( N2 > 0, "Size2 of fs_matrix == 0." ) ;

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

  void swap ( fs_matrix & b )
    noexcept ( noexcept ( swap ( declval < T & > ( ), declval < T & > ( ) ) ) )
    { swap_ranges ( element_begin ( ), element_end ( ),
                    b.element_begin ( ) ) ; }

  const fs_matrix & operator + ( ) const
    { return * this ; }

  fs_matrix operator - ( ) const
    { fs_matrix result ;
      transform ( element_begin ( ), element_end ( ),
                  result.element_begin ( ),
                  :: negate < T > ( ) ) ;
      return result ; }

  friend fs_matrix operator + ( const fs_matrix & a,
                                const fs_matrix & b )
    { fs_matrix result ;
      transform ( a.element_begin ( ), a.element_end ( ),
                  b.element_begin ( ),
                  result.element_begin ( ),
                  plus < T > ( ) ) ;
      return result ; }

  friend fs_matrix operator - ( const fs_matrix & a,
                                const fs_matrix & b )
    { fs_matrix result ;
      transform ( a.element_begin ( ), a.element_end ( ),
                  b.element_begin ( ),
                  result.element_begin ( ),
                  minus < T > ( ) ) ;
      return result ; }

  friend fs_matrix operator * ( const fs_matrix & a, const T & b )
    { fs_matrix result ;
      transform ( a.element_begin ( ), a.element_end ( ),
                  result.element_begin ( ),
                  [ & ] ( const T & x ) { return x * b ; } ) ;
      return result ; }

  friend fs_matrix operator * ( const T & a, const fs_matrix & b )
    { fs_matrix result ;
      transform ( b.element_begin ( ), b.element_end ( ),
                  result.element_begin ( ),
                  [ & ] ( const T & x ) { return a * x ; } ) ;
      return result ; }

  friend fs_matrix operator / ( const fs_matrix & a, const T & b )
    { fs_matrix result ;
      transform ( a.element_begin ( ), a.element_end ( ),
                  result.element_begin ( ),
                  [ & ] ( const T & x ) { return x / b ; } ) ;
      return result ; }

  friend fs_matrix operator % ( const fs_matrix & a, const T & b )
    { fs_matrix result ;
      transform ( a.element_begin ( ), a.element_end ( ),
                  result.element_begin ( ),
                  [ & ] ( const T & x ) { return x % b ; } ) ;
      return result ; }

  fs_matrix < T, N2, N1 > transposed ( ) const
    { fs_matrix < T, N2, N1 > result ;
      for ( size_t n1 = 0 ; n1 < N1 ; ++ n1 )
        for ( size_t n2 = 0 ; n2 < N2 ; ++ n2 )
          result.at ( n2, n1 ) = at ( n1, n2 ) ;
      return result ; }

  fs_matrix & negate ( )
    { for_each ( element_begin ( ), element_end ( ),
                 [ ] ( T & x ) { x = - x ; } ) ;
      return * this ; }

  fs_matrix & operator += ( const fs_matrix & b )
    { for_each_pair ( element_begin ( ), element_end ( ),
                      b.element_begin ( ),
                      [ ] ( T & x, const T & y ) { x += y ; } ) ;
      return * this ; }

  fs_matrix & operator -= ( const fs_matrix & b )
    { for_each_pair ( element_begin ( ), element_end ( ),
                      b.element_begin ( ),
                      [ ] ( T & x, const T & y ) { x -= y ; } ) ;
      return * this ; }

  fs_matrix & operator *= ( const T & b )
    { for_each ( element_begin ( ), element_end ( ),
                 [ & ] ( T & x ) { x *= b ; } ) ;
      return * this ; }

  fs_matrix & operator *= ( const fs_matrix < T, N2, N2 > & b )
    { return * this = * this * b ; }

  fs_matrix & operator *=
    ( const fs_lower_triangular_matrix < T, N2 > & b )
    { return * this = * this * b ; }

  fs_matrix & operator *=
    ( const fs_upper_triangular_matrix < T, N2 > & b )
    { return * this = * this * b ; }

  fs_matrix & operator /= ( const T & b )
    { for_each ( element_begin ( ), element_end ( ),
                 [ & ] ( T & x ) { x /= b ; } ) ;
      return * this ; }

  fs_matrix & operator %= ( const T & b )
    { for_each ( element_begin ( ), element_end ( ),
                 [ & ] ( T & x ) { x %= b ; } ) ;
      return * this ; }

  friend bool operator == ( const fs_matrix & a, const fs_matrix & b )
    { return equal ( a.element_begin ( ), a.element_end ( ),
                     b.element_begin ( ) ) ; }

  friend bool operator < ( const fs_matrix & a, const fs_matrix & b )
    { return lexicographical_compare
               ( a.element_begin ( ), a.element_end ( ),
                 b.element_begin ( ), b.element_end ( ) ) ; }

  friend void swap ( fs_matrix & a, fs_matrix & b )
    { a.swap ( b ) ; }

  template < class CharT, class CharTraits >
  friend basic_ostream < CharT, CharTraits > &
    operator << ( basic_ostream < CharT, CharTraits > & o,
                  const fs_matrix & x )
    { return output_array ( o, x.elements ) ; }

  template < class CharT, class CharTraits >
  friend basic_istream < CharT, CharTraits > &
    operator >> ( basic_istream < CharT, CharTraits > & i,
                  fs_matrix & x )
    { fs_matrix tx ;
      input_array ( i, tx.elements ) ;
      if ( i.good ( ) )
        x = move ( tx ) ;
      return i ; }

} ;


//

template < class T, size_t N1, size_t N2, class UnaryOperation >
inline fs_matrix < T, N1, N2 >
         componentwise ( const fs_matrix < T, N1, N2 > & a,
                         UnaryOperation unary_operation )

{
fs_matrix < T, N1, N2 > result ;

transform ( a.element_begin ( ), a.element_end ( ),
            result.element_begin ( ),
            unary_operation ) ;

return result ;
}


//

template < class T, size_t N1, size_t N2, class BinaryOperation >
inline fs_matrix < T, N1, N2 >
         componentwise ( const fs_matrix < T, N1, N2 > & a,
                         const fs_matrix < T, N1, N2 > & b,
                         BinaryOperation binary_operation )

{
fs_matrix < T, N1, N2 > result ;

transform ( a.element_begin ( ), a.element_end ( ),
            b.element_begin ( ),
            result.element_begin ( ),
            binary_operation ) ;

return result ;
}


//

template < class T, size_t N1, size_t N2 >
inline fs_matrix < T, N1, N2 >
         outer_product ( const fs_vector < T, N1 > & a,
                         const fs_vector < T, N2 > & b )

{
fs_matrix < T, N1, N2 > result ;

for ( size_t n1 = 0 ; n1 < N1 ; ++ n1 )
  for ( size_t n2 = 0 ; n2 < N2 ; ++ n2 )
    result ( n1, n2 ) = a [ n1 ] * b [ n2 ] ;

return result ;
}


//

template < class T, size_t N1, size_t N2 >
inline fs_vector < T, N1 >
         operator * ( const fs_matrix < T, N1, N2 > & m,
                      const fs_vector < T, N2 > & v )

{
fs_vector < T, N1 > result ;

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
inline fs_vector < T, N2 >
         operator * ( const fs_vector < T, N1 > & v,
                      const fs_matrix < T, N1, N2 > & m )

{
fs_vector < T, N2 > result ;

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
inline fs_matrix < T, N1, N2 >
         operator * ( const fs_matrix < T, N1, L > & a,
                      const fs_matrix < T, L, N2 > & b )

{
fs_matrix < T, N1, N2 > result ;

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



// *** FS_MATRIX INDEXING_TRAITS ***


template < class T, size_t N1, size_t N2 >
class indexing_traits < fs_matrix < T, N1, N2 > >

{
public:

  typedef size_t index_type ;
  typedef T value_type [ N2 ] ;

  static constexpr size_t size ( const fs_matrix < T, N1, N2 > & x )
    { return N1 ; }

} ;



// *** FS_LOWER_TRIANGULAR_MATRIX ***


template < class T, size_t N >
class fs_lower_triangular_matrix

{
public:

  static_assert ( N > 0, "Size of fs_lower_triangular_matrix == 0." ) ;

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

  void swap ( fs_lower_triangular_matrix & b )
    noexcept ( noexcept ( swap ( declval < T & > ( ), declval < T & > ( ) ) ) )
    { swap_ranges ( begin ( ), end ( ), b.begin ( ) ) ; }

  const fs_lower_triangular_matrix & operator + ( ) const
    { return * this ; }

  fs_lower_triangular_matrix operator - ( ) const
    { fs_lower_triangular_matrix result ;
      transform ( begin ( ), end ( ),
                  result.begin ( ),
                  :: negate < T > ( ) ) ;
      return result ; }

  friend fs_lower_triangular_matrix
           operator + ( const fs_lower_triangular_matrix & a,
                        const fs_lower_triangular_matrix & b )
    { fs_lower_triangular_matrix result ;
      transform ( a.begin ( ), a.end ( ),
                  b.begin ( ),
                  result.begin ( ),
                  plus < T > ( ) ) ;
      return result ; }

  friend fs_lower_triangular_matrix
           operator - ( const fs_lower_triangular_matrix & a,
                        const fs_lower_triangular_matrix & b )
    { fs_lower_triangular_matrix result ;
      transform ( a.begin ( ), a.end ( ),
                  b.begin ( ),
                  result.begin ( ),
                  minus < T > ( ) ) ;
      return result ; }

  friend fs_lower_triangular_matrix
           operator * ( const fs_lower_triangular_matrix & a, const T & b )
    { fs_lower_triangular_matrix result ;
      transform ( a.begin ( ), a.end ( ),
                  result.begin ( ),
                  [ & ] ( const T & x ) { return x * b ; } ) ;
      return result ; }

  friend fs_lower_triangular_matrix
           operator * ( const T & a, const fs_lower_triangular_matrix & b )
    { fs_lower_triangular_matrix result ;
      transform ( b.begin ( ), b.end ( ),
                  result.begin ( ),
                  [ & ] ( const T & x ) { return a * x ; } ) ;
      return result ; }

  friend fs_lower_triangular_matrix
           operator / ( const fs_lower_triangular_matrix & a, const T & b )
    { fs_lower_triangular_matrix result ;
      transform ( a.begin ( ), a.end ( ),
                  result.begin ( ),
                  [ & ] ( const T & x ) { return x / b ; } ) ;
      return result ; }

  friend fs_lower_triangular_matrix
           operator % ( const fs_lower_triangular_matrix & a, const T & b )
    { fs_lower_triangular_matrix result ;
      transform ( a.begin ( ), a.end ( ),
                  result.begin ( ),
                  [ & ] ( const T & x ) { return x % b ; } ) ;
      return result ; }

  fs_lower_triangular_matrix & negate ( )
    { for ( T & x : elements )
        x = - x ;
      return * this ; }

  fs_lower_triangular_matrix &
    operator += ( const fs_lower_triangular_matrix & b )
    { for_each_pair ( begin ( ), end ( ),
                      b.begin ( ),
                      [ ] ( T & x, const T & y ) { x += y ; } ) ;
      return * this ; }

  fs_lower_triangular_matrix &
    operator -= ( const fs_lower_triangular_matrix & b )
    { for_each_pair ( begin ( ), end ( ),
                      b.begin ( ),
                      [ ] ( T & x, const T & y ) { x -= y ; } ) ;
      return * this ; }

  fs_lower_triangular_matrix & operator *= ( const T & b )
    { for ( T & x : elements )
        x *= b ;
      return * this ; }

  fs_lower_triangular_matrix & operator *=
    ( const fs_lower_triangular_matrix & b )
    { return * this = * this * b ; }

  fs_lower_triangular_matrix & operator /= ( const T & b )
    { for ( T & x : elements )
        x /= b ;
      return * this ; }

  fs_lower_triangular_matrix & operator %= ( const T & b )
    { for ( T & x : elements )
        x %= b ;
      return * this ; }

  friend bool operator == ( const fs_lower_triangular_matrix & a,
                            const fs_lower_triangular_matrix & b )
    { return equal ( a.begin ( ), a.end ( ), b.begin ( ) ) ; }

  friend bool operator < ( const fs_lower_triangular_matrix & a,
                           const fs_lower_triangular_matrix & b )
    { return lexicographical_compare ( a.begin ( ), a.end ( ),
                                       b.begin ( ), b.end ( ) ) ; }

  friend void swap ( fs_lower_triangular_matrix & a,
                     fs_lower_triangular_matrix & b )
    { a.swap ( b ) ; }

  template < class CharT, class CharTraits >
  friend basic_ostream < CharT, CharTraits > &
    operator << ( basic_ostream < CharT, CharTraits > & o,
                  const fs_lower_triangular_matrix & x )
    { return output_array ( o, x.elements ) ; }

  template < class CharT, class CharTraits >
  friend basic_istream < CharT, CharTraits > &
    operator >> ( basic_istream < CharT, CharTraits > & i,
                  fs_lower_triangular_matrix & x )
    { fs_lower_triangular_matrix tx ;
      input_array ( i, tx.elements ) ;
      if ( i.good ( ) )
        x = move ( tx ) ;
      return i ; }

} ;


//

template < class T, size_t N, class UnaryOperation >
inline fs_lower_triangular_matrix < T, N >
         componentwise ( const fs_lower_triangular_matrix < T, N > & a,
                         UnaryOperation unary_operation )

{
fs_lower_triangular_matrix < T, N > result ;

transform ( a.begin ( ), a.end ( ),
            result.begin ( ),
            unary_operation ) ;

return result ;
}


//

template < class T, size_t N, class BinaryOperation >
inline fs_lower_triangular_matrix < T, N >
         componentwise ( const fs_lower_triangular_matrix < T, N > & a,
                         const fs_lower_triangular_matrix < T, N > & b,
                         BinaryOperation binary_operation )

{
fs_lower_triangular_matrix < T, N > result ;

transform ( a.begin ( ), a.end ( ),
            b.begin ( ),
            result.begin ( ),
            binary_operation ) ;

return result ;
}


//

template < class T, size_t N >
inline fs_vector < T, N >
         operator * ( const fs_lower_triangular_matrix < T, N > & m,
                      const fs_vector < T, N > & v )

{
fs_vector < T, N > result ;

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
inline fs_vector < T, N >
         operator * ( const fs_vector < T, N > & v,
                      const fs_lower_triangular_matrix < T, N > & m )

{
fs_vector < T, N > result ;

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
inline fs_matrix < T, N1, N2 >
         operator * ( const fs_lower_triangular_matrix < T, N1 > & a,
                      const fs_matrix < T, N1, N2 > & b )

{
fs_matrix < T, N1, N2 > result ;

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
inline fs_matrix < T, N1, N2 >
         operator * ( const fs_matrix < T, N1, N2 > & a,
                      const fs_lower_triangular_matrix < T, N2 > & b )

{
fs_matrix < T, N1, N2 > result ;

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
inline fs_lower_triangular_matrix < T, N >
         operator * ( const fs_lower_triangular_matrix < T, N > & a,
                      const fs_lower_triangular_matrix < T, N > & b )

{
fs_lower_triangular_matrix < T, N > result ;

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
inline fs_matrix < T, N, N >
         make_symmetric ( const fs_lower_triangular_matrix < T, N > & m )

{
fs_matrix < T, N, N > result ;

for ( size_t n1 = 0 ; n1 < N ; ++ n1 )
  for ( size_t n2 = 0 ; n2 < N ; ++ n2 )
    result ( n1, n2 ) = m.symmetric_at ( n1, n2 ) ;

return result ;
}


//

template < class T, size_t N >
inline fs_matrix < T, N, N >
         make_complete ( const fs_lower_triangular_matrix < T, N > & m )

{
fs_matrix < T, N, N > result ;

for ( size_t n1 = 0 ; n1 < N ; ++ n1 )
  for ( size_t n2 = 0 ; n2 < N ; ++ n2 )
    result ( n1, n2 ) = m.complete_at ( n1, n2 ) ;

return result ;
}



// *** FS_LOWER_TRIANGULAR_MATRIX INDEXING_TRAITS ***


template < class T, size_t N >
class indexing_traits < fs_lower_triangular_matrix < T, N > >

{
public:

  typedef size_t index_type ;
  typedef T * value_type ;

  static constexpr
    size_t size ( const fs_lower_triangular_matrix < T, N > & x )
    { return N ; }

} ;



// *** FS_UPPER_TRIANGULAR_MATRIX ***


template < class T, size_t N >
class fs_upper_triangular_matrix

{
public:

  static_assert ( N > 0, "Size of fs_upper_triangular_matrix == 0." ) ;

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

  void swap ( fs_upper_triangular_matrix & b )
    noexcept ( noexcept ( swap ( declval < T & > ( ), declval < T & > ( ) ) ) )
    { swap_ranges ( begin ( ), end ( ), b.begin ( ) ) ; }

  const fs_upper_triangular_matrix & operator + ( ) const
    { return * this ; }

  fs_upper_triangular_matrix operator - ( ) const
    { fs_upper_triangular_matrix result ;
      transform ( begin ( ), end ( ),
                  result.begin ( ),
                  :: negate < T > ( ) ) ;
      return result ; }

  friend fs_upper_triangular_matrix
           operator + ( const fs_upper_triangular_matrix & a,
                        const fs_upper_triangular_matrix & b )
    { fs_upper_triangular_matrix result ;
      transform ( a.begin ( ), a.end ( ),
                  b.begin ( ),
                  result.begin ( ),
                  plus < T > ( ) ) ;
      return result ; }

  friend fs_upper_triangular_matrix
           operator - ( const fs_upper_triangular_matrix & a,
                        const fs_upper_triangular_matrix & b )
    { fs_upper_triangular_matrix result ;
      transform ( a.begin ( ), a.end ( ),
                  b.begin ( ),
                  result.begin ( ),
                  minus < T > ( ) ) ;
      return result ; }

  friend fs_upper_triangular_matrix
           operator * ( const fs_upper_triangular_matrix & a, const T & b )
    { fs_upper_triangular_matrix result ;
      transform ( a.begin ( ), a.end ( ),
                  result.begin ( ),
                  [ & ] ( const T & x ) { return x * b ; } ) ;
      return result ; }

  friend fs_upper_triangular_matrix
           operator * ( const T & a, const fs_upper_triangular_matrix & b )
    { fs_upper_triangular_matrix result ;
      transform ( b.begin ( ), b.end ( ),
                  result.begin ( ),
                  [ & ] ( const T & x ) { return a * x ; } ) ;
      return result ; }

  friend fs_upper_triangular_matrix
           operator / ( const fs_upper_triangular_matrix & a, const T & b )
    { fs_upper_triangular_matrix result ;
      transform ( a.begin ( ), a.end ( ),
                  result.begin ( ),
                  [ & ] ( const T & x ) { return x / b ; } ) ;
      return result ; }

  friend fs_upper_triangular_matrix
           operator % ( const fs_upper_triangular_matrix & a, const T & b )
    { fs_upper_triangular_matrix result ;
      transform ( a.begin ( ), a.end ( ),
                  result.begin ( ),
                  [ & ] ( const T & x ) { return x % b ; } ) ;
      return result ; }

  fs_upper_triangular_matrix & negate ( )
    { for ( T & x : elements )
        x = - x ;
      return * this ; }

  fs_upper_triangular_matrix &
    operator += ( const fs_upper_triangular_matrix & b )
    { for_each_pair ( begin ( ), end ( ),
                      b.begin ( ),
                      [ ] ( T & x, const T & y ) { x += y ; } ) ;
      return * this ; }

  fs_upper_triangular_matrix &
    operator -= ( const fs_upper_triangular_matrix & b )
    { for_each_pair ( begin ( ), end ( ),
                      b.begin ( ),
                      [ ] ( T & x, const T & y ) { x -= y ; } ) ;
      return * this ; }

  fs_upper_triangular_matrix & operator *= ( const T & b )
    { for ( T & x : elements )
        x *= b ;
      return * this ; }

  fs_upper_triangular_matrix & operator *=
    ( const fs_upper_triangular_matrix & b )
    { return * this = * this * b ; }

  fs_upper_triangular_matrix & operator /= ( const T & b )
    { for ( T & x : elements )
        x /= b ;
      return * this ; }

  fs_upper_triangular_matrix & operator %= ( const T & b )
    { for ( T & x : elements )
        x %= b ;
      return * this ; }

  friend bool operator == ( const fs_upper_triangular_matrix & a,
                            const fs_upper_triangular_matrix & b )
    { return equal ( a.begin ( ), a.end ( ), b.begin ( ) ) ; }

  friend bool operator < ( const fs_upper_triangular_matrix & a,
                           const fs_upper_triangular_matrix & b )
    { return lexicographical_compare ( a.begin ( ), a.end ( ),
                                       b.begin ( ), b.end ( ) ) ; }

  friend void swap ( fs_upper_triangular_matrix & a,
                     fs_upper_triangular_matrix & b )
    { a.swap ( b ) ; }

  template < class CharT, class CharTraits >
  friend basic_ostream < CharT, CharTraits > &
    operator << ( basic_ostream < CharT, CharTraits > & o,
                  const fs_upper_triangular_matrix & x )
    { return output_array ( o, x.elements ) ; }

  template < class CharT, class CharTraits >
  friend basic_istream < CharT, CharTraits > &
    operator >> ( basic_istream < CharT, CharTraits > & i,
                  fs_upper_triangular_matrix & x )
    { fs_upper_triangular_matrix tx ;
      input_array ( i, tx.elements ) ;
      if ( i.good ( ) )
        x = move ( tx ) ;
      return i ; }

} ;


//

template < class T, size_t N, class UnaryOperation >
inline fs_upper_triangular_matrix < T, N >
         componentwise ( const fs_upper_triangular_matrix < T, N > & a,
                         UnaryOperation unary_operation )

{
fs_upper_triangular_matrix < T, N > result ;

transform ( a.begin ( ), a.end ( ),
            result.begin ( ),
            unary_operation ) ;

return result ;
}


//

template < class T, size_t N, class BinaryOperation >
inline fs_upper_triangular_matrix < T, N >
         componentwise ( const fs_upper_triangular_matrix < T, N > & a,
                         const fs_upper_triangular_matrix < T, N > & b,
                         BinaryOperation binary_operation )

{
fs_upper_triangular_matrix < T, N > result ;

transform ( a.begin ( ), a.end ( ),
            b.begin ( ),
            result.begin ( ),
            binary_operation ) ;

return result ;
}


//

template < class T, size_t N >
inline fs_vector < T, N >
         operator * ( const fs_upper_triangular_matrix < T, N > & m,
                      const fs_vector < T, N > & v )

{
fs_vector < T, N > result ;

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
inline fs_vector < T, N >
         operator * ( const fs_vector < T, N > & v,
                      const fs_upper_triangular_matrix < T, N > & m )

{
fs_vector < T, N > result ;

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
inline fs_matrix < T, N1, N2 >
         operator * ( const fs_upper_triangular_matrix < T, N1 > & a,
                      const fs_matrix < T, N1, N2 > & b )

{
fs_matrix < T, N1, N2 > result ;

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
inline fs_matrix < T, N1, N2 >
         operator * ( const fs_matrix < T, N1, N2 > & a,
                      const fs_upper_triangular_matrix < T, N2 > & b )

{
fs_matrix < T, N1, N2 > result ;

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
inline fs_upper_triangular_matrix < T, N >
         operator * ( const fs_upper_triangular_matrix < T, N > & a,
                      const fs_upper_triangular_matrix < T, N > & b )

{
fs_upper_triangular_matrix < T, N > result ;

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
inline fs_matrix < T, N, N >
         make_symmetric ( const fs_upper_triangular_matrix < T, N > & m )

{
fs_matrix < T, N, N > result ;

for ( size_t n1 = 0 ; n1 < N ; ++ n1 )
  for ( size_t n2 = 0 ; n2 < N ; ++ n2 )
    result ( n1, n2 ) = m.symmetric_at ( n1, n2 ) ;

return result ;
}


//

template < class T, size_t N >
inline fs_matrix < T, N, N >
         make_complete ( const fs_upper_triangular_matrix < T, N > & m )

{
fs_matrix < T, N, N > result ;

for ( size_t n1 = 0 ; n1 < N ; ++ n1 )
  for ( size_t n2 = 0 ; n2 < N ; ++ n2 )
    result ( n1, n2 ) = m.complete_at ( n1, n2 ) ;

return result ;
}



// *** FS_UPPER_TRIANGULAR_MATRIX INDEXING_TRAITS ***


template < class T, size_t N >
class indexing_traits < fs_upper_triangular_matrix < T, N > >

{
public:

  typedef size_t index_type ;
  typedef T * value_type ;

  static constexpr
    size_t size ( const fs_upper_triangular_matrix < T, N > & x )
    { return N ; }

} ;



#endif
