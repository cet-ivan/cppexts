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
#include "stdexcept.h"
#include "algorithm.h"
#include "functional.h"
#include "numeric.h"
#include "complex.h"

#include "streaming.h"
#include "funtr.h"
#include "numbase.h"



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

template < class T, size_t N, class UnaryOperation >
fs_vector < T, N > componentwise ( const fs_vector < T, N > & a,
                                   UnaryOperation unary_operation ) ;

template < class T, size_t N, class BinaryOperation >
fs_vector < T, N > componentwise ( const fs_vector < T, N > & a,
                                   const fs_vector < T, N > & b,
                                   BinaryOperation binary_operation ) ;



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

template < class T, size_t N1, size_t N2, class UnaryOperation >
fs_matrix < T, N1, N2 >
  componentwise ( const fs_matrix < T, N1, N2 > & a,
                  UnaryOperation unary_operation ) ;

template < class T, size_t N1, size_t N2, class BinaryOperation >
fs_matrix < T, N1, N2 >
  componentwise ( const fs_matrix < T, N1, N2 > & a,
                  const fs_matrix < T, N1, N2 > & b,
                  BinaryOperation binary_operation ) ;



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

template < class T, size_t N, class UnaryOperation >
fs_lower_triangular_matrix < T, N >
  componentwise ( const fs_lower_triangular_matrix < T, N > & a,
                  UnaryOperation unary_operation ) ;

template < class T, size_t N, class BinaryOperation >
fs_lower_triangular_matrix < T, N >
  componentwise ( const fs_lower_triangular_matrix < T, N > & a,
                  const fs_lower_triangular_matrix < T, N > & b,
                  BinaryOperation binary_operation ) ;



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

template < class T, size_t N, class UnaryOperation >
fs_upper_triangular_matrix < T, N >
  componentwise ( const fs_upper_triangular_matrix < T, N > & a,
                  UnaryOperation unary_operation ) ;

template < class T, size_t N, class BinaryOperation >
fs_upper_triangular_matrix < T, N >
  componentwise ( const fs_upper_triangular_matrix < T, N > & a,
                  const fs_upper_triangular_matrix < T, N > & b,
                  BinaryOperation binary_operation ) ;



// *** FIXED_SIZE_STRUCTURE_COMPONENTWISE ***


//

template < class FixedSizeStructure, class UnaryOperation >
inline FixedSizeStructure
         fixed_size_structure_componentwise
           ( const FixedSizeStructure & a,
             UnaryOperation unary_operation )

{
FixedSizeStructure result ;

transform ( a.begin ( ), a.end ( ),
            result.begin ( ),
            unary_operation ) ;

return result ;
}


//

template < class FixedSizeStructure, class BinaryOperation >
inline FixedSizeStructure
         fixed_size_structure_componentwise
           ( const FixedSizeStructure & a,
             const FixedSizeStructure & b,
             BinaryOperation binary_operation )

{
FixedSizeStructure result ;

transform ( a.begin ( ), a.end ( ),
            b.begin ( ),
            result.begin ( ),
            binary_operation ) ;

return result ;
}



// *** FS_VECTOR ***


template < class T, size_t N >
class fs_vector

{
public:

  static_assert ( N > 0, "Size of fs_vector == 0." ) ;

  typedef T value_type ;

  typedef size_t size_type ;
  typedef ptrdiff_t difference_type ;

  typedef T * pointer ;
  typedef const T * const_pointer ;

  typedef T & reference ;
  typedef const T & const_reference ;

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

  constexpr size_t size ( ) const noexcept
    { return N ; }

  constexpr bool empty ( ) const noexcept
    { return false ; }

  reference access ( size_t n ) noexcept
    { assert ( n < N ) ;
      return elements [ n ] ; }

  const_reference access ( size_t n ) const noexcept
    { assert ( n < N ) ;
      return elements [ n ] ; }

  reference at ( size_t n )
    { if ( n >= N )
        throw out_of_range ( "fs_vector :: at, index out of range" ) ;
      return elements [ n ] ; }

  const_reference at ( size_t n ) const
    { if ( n >= N )
        throw out_of_range ( "fs_vector :: at, index out of range" ) ;
      return elements [ n ] ; }

  reference operator [ ] ( size_t n ) noexcept
    { return access ( n ) ; }

  const_reference operator [ ] ( size_t n ) const noexcept
    { return access ( n ) ; }

  reference front ( ) noexcept
    { return elements [ 0 ] ; }

  const_reference front ( ) const noexcept
    { return elements [ 0 ] ; }

  reference back ( ) noexcept
    { return elements [ N - 1 ] ; }

  const_reference back ( ) const noexcept
    { return elements [ N - 1 ] ; }

  void fill ( const T & x )
    { :: fill ( begin ( ), end ( ), x ) ; }

  void swap ( fs_vector & b ) noexcept ( is_nothrow_swappable_v < T > )
    { swap_ranges ( begin ( ), end ( ),
                    b.begin ( ) ) ; }

  const fs_vector & operator + ( ) const
    { return * this ; }

  fs_vector operator - ( ) const
    { return componentwise ( * this, :: negate < T > ( ) ) ; }

  friend fs_vector operator + ( const fs_vector & a, const fs_vector & b )
    { return componentwise ( a, b, plus < T > ( ) ) ; }

  friend fs_vector operator - ( const fs_vector & a, const fs_vector & b )
    { return componentwise ( a, b, minus < T > ( ) ) ; }

  friend T operator * ( const fs_vector & a, const fs_vector & b )
    { return inner_product ( a.begin ( ), a.end ( ),
                             b.begin ( ),
                             T ( 0 ) ) ; }

  friend fs_vector operator * ( const fs_vector & a, const T & b )
    { return componentwise ( a, [ & ] ( const T & x ) { return x * b ; } ) ; }

  friend fs_vector operator * ( const T & a, const fs_vector & b )
    { return componentwise ( b, [ & ] ( const T & x ) { return a * x ; } ) ; }

  friend fs_vector operator / ( const fs_vector & a, const T & b )
    { return componentwise ( a, [ & ] ( const T & x ) { return x / b ; } ) ; }

  friend fs_vector operator % ( const fs_vector & a, const T & b )
    { return componentwise ( a, [ & ] ( const T & x ) { return x % b ; } ) ; }

  fs_vector & negate ( )
    { for ( T & x : elements )
        x = - x ;
      return * this ; }

  fs_vector & operator += ( const fs_vector & b )
    { for_pairs ( begin ( ), end ( ),
                  b.begin ( ),
                  [ ] ( T & x, const T & y ) { x += y ; } ) ;
      return * this ; }

  fs_vector & operator -= ( const fs_vector & b )
    { for_pairs ( begin ( ), end ( ),
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
    { return equal ( a.begin ( ), a.end ( ),
                     b.begin ( ) ) ; }

  friend bool operator < ( const fs_vector & a, const fs_vector & b )
    { return lexicographical_compare ( a.begin ( ), a.end ( ),
                                       b.begin ( ), b.end ( ) ) ; }

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

template < class T, size_t N >
void swap ( fs_vector < T, N > & a, fs_vector < T, N > & b )

{
a.swap ( b ) ;
}


//

template < class T, size_t N, class UnaryOperation >
inline fs_vector < T, N >
         componentwise ( const fs_vector < T, N > & a,
                         UnaryOperation unary_operation )

{
return fixed_size_structure_componentwise ( a, unary_operation ) ;
}


//

template < class T, size_t N, class BinaryOperation >
inline fs_vector < T, N >
         componentwise ( const fs_vector < T, N > & a,
                         const fs_vector < T, N > & b,
                         BinaryOperation binary_operation )

{
return fixed_size_structure_componentwise ( a, b, binary_operation ) ;
}


//

template < class T, size_t N >
inline fs_vector < complex < T >, N >
         conj ( const fs_vector < complex < T >, N > & a )

{
return componentwise ( a, conj < T > ) ;
}


//

template < class T, size_t N >
inline T inner_product ( const fs_vector < T, N > & a,
                         const fs_vector < T, N > & b )

{
return inner_product ( a.begin ( ), a.end ( ),
                       b.begin ( ),
                       T ( 0 ),
                       plus < T > ( ),
                       [ ] ( const T & x, const T & y )
                         { return inner_product_multiply ( x, y ) ; } ) ;
}


//

template < class T, size_t N >
inline auto l1_norm ( const fs_vector < T, N > & a )

{
typedef decltype ( l1_norm ( declval < T > ( ) ) ) result_type ;

return accumulate ( a.begin ( ), a.end ( ),
                    result_type ( 0 ),
                    [ ] ( const result_type & x, const T & y )
                      { return x + l1_norm ( y ) ; } ) ;
}


//

template < class T, size_t N >
inline auto l1_distance ( const fs_vector < T, N > & a,
                          const fs_vector < T, N > & b )

{
typedef decltype ( l1_distance ( declval < T > ( ), declval < T > ( ) ) )
        result_type ;

return inner_product ( a.begin ( ), a.end ( ),
                       b.begin ( ),
                       result_type ( 0 ),
                       plus < result_type > ( ),
                       [ ] ( const T & x, const T & y )
                         { return l1_distance ( x, y ) ; } ) ;
}


//

template < class T, size_t N >
inline auto sqr_l2_norm ( const fs_vector < T, N > & a )

{
typedef decltype ( sqr_l2_norm ( declval < T > ( ) ) ) result_type ;

return accumulate ( a.begin ( ), a.end ( ),
                    result_type ( 0 ),
                    [ ] ( const result_type & x, const T & y )
                      { return x + sqr_l2_norm ( y ) ; } ) ;
}


//

template < class T, size_t N >
inline auto sqr_l2_distance ( const fs_vector < T, N > & a,
                              const fs_vector < T, N > & b )

{
typedef decltype ( sqr_l2_distance ( declval < T > ( ), declval < T > ( ) ) )
        result_type ;

return inner_product ( a.begin ( ), a.end ( ),
                       b.begin ( ),
                       result_type ( 0 ),
                       plus < result_type > ( ),
                       [ ] ( const T & x, const T & y )
                         { return sqr_l2_distance ( x, y ) ; } ) ;
}


//

template < class T, size_t N >
inline auto l2_norm ( const fs_vector < T, N > & a )

{
return sqrt ( sqr_l2_norm ( a ) ) ;
}


//

template < class T, size_t N >
inline auto l2_distance ( const fs_vector < T, N > & a,
                          const fs_vector < T, N > & b )

{
return sqrt ( sqr_l2_distance ( a, b ) ) ;
}


//

template < class T, size_t N >
inline auto linf_norm ( const fs_vector < T, N > & a )

{
typedef decltype ( linf_norm ( declval < T > ( ) ) ) result_type ;

return accumulate ( a.begin ( ), a.end ( ),
                    result_type ( 0 ),
                    [ ] ( const result_type & x, const T & y )
                      { return max ( x, linf_norm ( y ) ) ; } ) ;
}


//

template < class T, size_t N >
inline auto linf_distance ( const fs_vector < T, N > & a,
                            const fs_vector < T, N > & b )

{
typedef decltype ( linf_distance ( declval < T > ( ), declval < T > ( ) ) )
        result_type ;

return inner_product ( a.begin ( ), a.end ( ),
                       b.begin ( ),
                       result_type ( 0 ),
                       [ ] ( const result_type & x, const result_type & y )
                         { return max ( x, y ) ; },
                       [ ] ( const T & x, const T & y )
                         { return linf_distance ( x, y ) ; } ) ;
}


//

template < class T, size_t N >
inline auto norm ( const fs_vector < T, N > & a )

{
return sqr_l2_norm ( a ) ;
}


//

template < class T, size_t N >
inline auto length ( const fs_vector < T, N > & a )

{
return sqrt ( norm ( a ) ) ;
}


//

template < class T >
inline fs_vector < T, 3 > cross_product ( const fs_vector < T, 3 > & a,
                                          const fs_vector < T, 3 > & b )

{
return fs_vector < T, 3 > { a [ 1 ] * b [ 2 ] - a [ 2 ] * b [ 1 ],
                            a [ 2 ] * b [ 0 ] - a [ 0 ] * b [ 2 ],
                            a [ 0 ] * b [ 1 ] - a [ 1 ] * b [ 0 ] } ;
}


//

template < class T >
inline T cross_product_z ( const fs_vector < T, 2 > & a,
                           const fs_vector < T, 2 > & b )

{
return a [ 0 ] * b [ 1 ] - a [ 1 ] * b [ 0 ] ;
}



// *** FS_VECTOR INDEXING_TRAITS ***


template < class T, size_t N >
class indexing_traits < fs_vector < T, N > >

{
public:

  typedef size_t index_type ;
  typedef T value_type ;

  static constexpr size_t size ( const fs_vector < T, N > & )
    { return N ; }

} ;



// *** FS_MATRIX ***


template < class T, size_t N1, size_t N2 >
class fs_matrix

{
public:

  static_assert ( N1 > 0, "Size1 of fs_matrix == 0." ) ;
  static_assert ( N2 > 0, "Size2 of fs_matrix == 0." ) ;

  typedef T value_type ;

  typedef size_t size_type ;
  typedef ptrdiff_t difference_type ;

  typedef T * pointer ;
  typedef const T * const_pointer ;

  typedef T & reference ;
  typedef const T & const_reference ;

  typedef pointer iterator ;
  typedef const_pointer const_iterator ;

  typedef :: reverse_iterator < iterator > reverse_iterator ;
  typedef :: reverse_iterator < const_iterator > const_reverse_iterator ;

  typedef T ( & row_reference ) [ N2 ] ;
  typedef const T ( & const_row_reference ) [ N2 ] ;

  T elements [ N1 ] [ N2 ] ;

  pointer data ( ) noexcept
    { return * elements ; }

  const_pointer data ( ) const noexcept
    { return * elements ; }

  iterator begin ( ) noexcept
    { return * elements ; }

  const_iterator begin ( ) const noexcept
    { return * elements ; }

  iterator end ( ) noexcept
    { return * ( elements + N1 ) ; }

  const_iterator end ( ) const noexcept
    { return * ( elements + N1 ) ; }

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

  constexpr size_t size ( ) const noexcept
    { return N1 * N2 ; }

  constexpr size_t size1 ( ) const noexcept
    { return N1 ; }

  constexpr size_t size2 ( ) const noexcept
    { return N2 ; }

  constexpr bool empty ( ) const noexcept
    { return false ; }

  reference access ( size_t n1, size_t n2 ) noexcept
    { assert ( n1 < N1 ) ;
      assert ( n2 < N2 ) ;
      return elements [ n1 ] [ n2 ] ; }

  const_reference access ( size_t n1, size_t n2 ) const noexcept
    { assert ( n1 < N1 ) ;
      assert ( n2 < N2 ) ;
      return elements [ n1 ] [ n2 ] ; }

  reference at ( size_t n1, size_t n2 )
    { if ( n1 >= N1 )
        throw out_of_range ( "fs_matrix :: at, index1 out of range" ) ;
      if ( n2 >= N2 )
        throw out_of_range ( "fs_matrix :: at, index2 out of range" ) ;
      return elements [ n1 ] [ n2 ] ; }

  const_reference at ( size_t n1, size_t n2 ) const
    { if ( n1 >= N1 )
        throw out_of_range ( "fs_matrix :: at, index1 out of range" ) ;
      if ( n2 >= N2 )
        throw out_of_range ( "fs_matrix :: at, index2 out of range" ) ;
      return elements [ n1 ] [ n2 ] ; }

  row_reference operator [ ] ( size_t n1 ) noexcept
    { assert ( n1 < N1 ) ;
      return elements [ n1 ] ; }

  const_row_reference operator [ ] ( size_t n1 ) const noexcept
    { assert ( n1 < N1 ) ;
      return elements [ n1 ] ; }

  reference operator ( ) ( size_t n1, size_t n2 ) noexcept
    { return access ( n1, n2 ) ; }

  const_reference operator ( ) ( size_t n1, size_t n2 ) const noexcept
    { return access ( n1, n2 ) ; }

  void fill ( const T & x )
    { :: fill ( begin ( ), end ( ), x ) ; }

  void swap ( fs_matrix & b ) noexcept ( is_nothrow_swappable_v < T > )
    { swap_ranges ( begin ( ), end ( ),
                    b.begin ( ) ) ; }

  const fs_matrix & operator + ( ) const
    { return * this ; }

  fs_matrix operator - ( ) const
    { return componentwise ( * this, :: negate < T > ( ) ) ; }

  friend fs_matrix operator + ( const fs_matrix & a, const fs_matrix & b )
    { return componentwise ( a, b, plus < T > ( ) ) ; }

  friend fs_matrix operator - ( const fs_matrix & a, const fs_matrix & b )
    { return componentwise ( a, b, minus < T > ( ) ) ; }

  friend fs_matrix operator * ( const fs_matrix & a, const T & b )
    { return componentwise ( a, [ & ] ( const T & x ) { return x * b ; } ) ; }

  friend fs_matrix operator * ( const T & a, const fs_matrix & b )
    { return componentwise ( b, [ & ] ( const T & x ) { return a * x ; } ) ; }

  friend fs_matrix operator / ( const fs_matrix & a, const T & b )
    { return componentwise ( a, [ & ] ( const T & x ) { return x / b ; } ) ; }

  friend fs_matrix operator % ( const fs_matrix & a, const T & b )
    { return componentwise ( a, [ & ] ( const T & x ) { return x % b ; } ) ; }

  fs_matrix < T, N2, N1 > transposed ( ) const
    { fs_matrix < T, N2, N1 > result ;
      for ( size_t n1 = 0 ; n1 < N1 ; ++ n1 )
        for ( size_t n2 = 0 ; n2 < N2 ; ++ n2 )
          result ( n2, n1 ) = access ( n1, n2 ) ;
      return result ; }

  fs_matrix & negate ( )
    { for_each ( begin ( ), end ( ),
                 [ ] ( T & x ) { x = - x ; } ) ;
      return * this ; }

  fs_matrix & operator += ( const fs_matrix & b )
    { for_pairs ( begin ( ), end ( ),
                  b.begin ( ),
                  [ ] ( T & x, const T & y ) { x += y ; } ) ;
      return * this ; }

  fs_matrix & operator -= ( const fs_matrix & b )
    { for_pairs ( begin ( ), end ( ),
                  b.begin ( ),
                  [ ] ( T & x, const T & y ) { x -= y ; } ) ;
      return * this ; }

  fs_matrix & operator *= ( const T & b )
    { for_each ( begin ( ), end ( ),
                 [ & ] ( T & x ) { x *= b ; } ) ;
      return * this ; }

  fs_matrix & operator *= ( const fs_matrix < T, N2, N2 > & b )
    { return * this = * this * b ; }

  fs_matrix & operator *= ( const fs_lower_triangular_matrix < T, N2 > & b )
    { return * this = * this * b ; }

  fs_matrix & operator *= ( const fs_upper_triangular_matrix < T, N2 > & b )
    { return * this = * this * b ; }

  fs_matrix & operator /= ( const T & b )
    { for_each ( begin ( ), end ( ),
                 [ & ] ( T & x ) { x /= b ; } ) ;
      return * this ; }

  fs_matrix & operator %= ( const T & b )
    { for_each ( begin ( ), end ( ),
                 [ & ] ( T & x ) { x %= b ; } ) ;
      return * this ; }

  friend bool operator == ( const fs_matrix & a, const fs_matrix & b )
    { return equal ( a.begin ( ), a.end ( ),
                     b.begin ( ) ) ; }

  friend bool operator < ( const fs_matrix & a, const fs_matrix & b )
    { return lexicographical_compare ( a.begin ( ), a.end ( ),
                                       b.begin ( ), b.end ( ) ) ; }

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

template < class T, size_t N1, size_t N2 >
void swap ( fs_matrix < T, N1, N2 > & a, fs_matrix < T, N1, N2 > & b )

{
a.swap ( b ) ;
}


//

template < class T, size_t N1, size_t N2, class UnaryOperation >
inline fs_matrix < T, N1, N2 >
         componentwise ( const fs_matrix < T, N1, N2 > & a,
                         UnaryOperation unary_operation )

{
return fixed_size_structure_componentwise ( a, unary_operation ) ;
}


//

template < class T, size_t N1, size_t N2, class BinaryOperation >
inline fs_matrix < T, N1, N2 >
         componentwise ( const fs_matrix < T, N1, N2 > & a,
                         const fs_matrix < T, N1, N2 > & b,
                         BinaryOperation binary_operation )

{
return fixed_size_structure_componentwise ( a, b, binary_operation ) ;
}


//

template < class T, size_t N1, size_t N2 >
inline fs_matrix < complex < T >, N1, N2 >
         conj ( const fs_matrix < complex < T >, N1, N2 > & a )

{
return componentwise ( a, conj < T > ) ;
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

  static constexpr size_t size ( const fs_matrix < T, N1, N2 > & )
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

  typedef T * pointer ;
  typedef const T * const_pointer ;

  typedef T & reference ;
  typedef const T & const_reference ;

  typedef pointer iterator ;
  typedef const_pointer const_iterator ;

  typedef :: reverse_iterator < iterator > reverse_iterator ;
  typedef :: reverse_iterator < const_iterator > const_reverse_iterator ;

private:

  static const size_t size_ = ( N * ( N + 1 ) ) >> 1 ;

  static constexpr size_t high_index_offset ( size_t n )
    { return ( n * ( n + 1 ) ) >> 1 ; }

public:

  T elements [ size_ ] ;

  pointer data ( ) noexcept
    { return elements ; }

  const_pointer data ( ) const noexcept
    { return elements ; }

  iterator begin ( ) noexcept
    { return elements ; }

  const_iterator begin ( ) const noexcept
    { return elements ; }

  iterator end ( ) noexcept
    { return elements + size_ ; }

  const_iterator end ( ) const noexcept
    { return elements + size_ ; }

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

  constexpr size_t size ( ) const noexcept
    { return size_ ; }

  constexpr size_t size1 ( ) const noexcept
    { return N ; }

  constexpr size_t size2 ( ) const noexcept
    { return N ; }

  constexpr bool empty ( ) const noexcept
    { return false ; }

  reference access ( size_t n1, size_t n2 ) noexcept
    { assert ( n1 < N ) ;
      assert ( n2 <= n1 ) ;
      return elements [ high_index_offset ( n1 ) + n2 ] ; }

  const_reference access ( size_t n1, size_t n2 ) const noexcept
    { assert ( n1 < N ) ;
      assert ( n2 <= n1 ) ;
      return elements [ high_index_offset ( n1 ) + n2 ] ; }

  reference at ( size_t n1, size_t n2 )
    { if ( n1 >= N )
        throw out_of_range
                ( "fs_lower_triangular_matrix :: at, index1 out of range" ) ;
      if ( n2 > n1 )
        throw out_of_range
                ( "fs_lower_triangular_matrix :: at, index2 out of range" ) ;
      return elements [ high_index_offset ( n1 ) + n2 ] ; }

  const_reference at ( size_t n1, size_t n2 ) const
    { if ( n1 >= N )
        throw out_of_range
                ( "fs_lower_triangular_matrix :: at, index1 out of range" ) ;
      if ( n2 > n1 )
        throw out_of_range
                ( "fs_lower_triangular_matrix :: at, index2 out of range" ) ;
      return elements [ high_index_offset ( n1 ) + n2 ] ; }

  pointer operator [ ] ( size_t n1 ) noexcept
    { assert ( n1 < N ) ;
      return elements + high_index_offset ( n1 ) ; }

  const_pointer operator [ ] ( size_t n1 ) const noexcept
    { assert ( n1 < N ) ;
      return elements + high_index_offset ( n1 ) ; }

  reference operator ( ) ( size_t n1, size_t n2 ) noexcept
    { return access ( n1, n2 ) ; }

  const_reference operator ( ) ( size_t n1, size_t n2 ) const noexcept
    { return access ( n1, n2 ) ; }

  T access_symmetric ( size_t n1, size_t n2 ) const
    { assert ( n1 < N ) ;
      assert ( n2 < N ) ;
      return n2 <= n1 ? access ( n1, n2 ) : access ( n2, n1 ) ; }

  T access_full ( size_t n1, size_t n2 ) const
    { assert ( n1 < N ) ;
      assert ( n2 < N ) ;
      return n2 <= n1 ? access ( n1, n2 ) : T ( 0 ) ; }

  void fill ( const T & x )
    { :: fill ( begin ( ), end ( ), x ) ; }

  void swap ( fs_lower_triangular_matrix & b )
    noexcept ( is_nothrow_swappable_v < T > )
    { swap_ranges ( begin ( ), end ( ),
                    b.begin ( ) ) ; }

  const fs_lower_triangular_matrix & operator + ( ) const
    { return * this ; }

  fs_lower_triangular_matrix operator - ( ) const
    { return componentwise ( * this, :: negate < T > ( ) ) ; }

  friend fs_lower_triangular_matrix
           operator + ( const fs_lower_triangular_matrix & a,
                        const fs_lower_triangular_matrix & b )
    { return componentwise ( a, b, plus < T > ( ) ) ; }

  friend fs_lower_triangular_matrix
           operator - ( const fs_lower_triangular_matrix & a,
                        const fs_lower_triangular_matrix & b )
    { return componentwise ( a, b, minus < T > ( ) ) ; }

  friend fs_lower_triangular_matrix
           operator * ( const fs_lower_triangular_matrix & a, const T & b )
    { return componentwise ( a, [ & ] ( const T & x ) { return x * b ; } ) ; }

  friend fs_lower_triangular_matrix
           operator * ( const T & a, const fs_lower_triangular_matrix & b )
    { return componentwise ( b, [ & ] ( const T & x ) { return a * x ; } ) ; }

  friend fs_lower_triangular_matrix
           operator / ( const fs_lower_triangular_matrix & a, const T & b )
    { return componentwise ( a, [ & ] ( const T & x ) { return x / b ; } ) ; }

  friend fs_lower_triangular_matrix
           operator % ( const fs_lower_triangular_matrix & a, const T & b )
    { return componentwise ( a, [ & ] ( const T & x ) { return x % b ; } ) ; }

  fs_upper_triangular_matrix < T, N > transposed ( ) const
    { fs_upper_triangular_matrix < T, N > result ;
      for ( size_t n1 = 0 ; n1 < N ; ++ n1 )
        for ( size_t n2 = 0 ; n2 <= n1 ; ++ n2 )
          result ( n2, n1 ) = access ( n1, n2 ) ;
      return result ; }

  fs_lower_triangular_matrix & negate ( )
    { for ( T & x : elements )
        x = - x ;
      return * this ; }

  fs_lower_triangular_matrix &
    operator += ( const fs_lower_triangular_matrix & b )
    { for_pairs ( begin ( ), end ( ),
                  b.begin ( ),
                  [ ] ( T & x, const T & y ) { x += y ; } ) ;
      return * this ; }

  fs_lower_triangular_matrix &
    operator -= ( const fs_lower_triangular_matrix & b )
    { for_pairs ( begin ( ), end ( ),
                  b.begin ( ),
                  [ ] ( T & x, const T & y ) { x -= y ; } ) ;
      return * this ; }

  fs_lower_triangular_matrix & operator *= ( const T & b )
    { for ( T & x : elements )
        x *= b ;
      return * this ; }

  fs_lower_triangular_matrix &
    operator *= ( const fs_lower_triangular_matrix & b )
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
    { return equal ( a.begin ( ), a.end ( ),
                     b.begin ( ) ) ; }

  friend bool operator < ( const fs_lower_triangular_matrix & a,
                           const fs_lower_triangular_matrix & b )
    { return lexicographical_compare ( a.begin ( ), a.end ( ),
                                       b.begin ( ), b.end ( ) ) ; }

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

template < class T, size_t N >
void swap ( fs_lower_triangular_matrix < T, N > & a,
            fs_lower_triangular_matrix < T, N > & b )

{
a.swap ( b ) ;
}


//

template < class T, size_t N, class UnaryOperation >
inline fs_lower_triangular_matrix < T, N >
         componentwise ( const fs_lower_triangular_matrix < T, N > & a,
                         UnaryOperation unary_operation )

{
return fixed_size_structure_componentwise ( a, unary_operation ) ;
}


//

template < class T, size_t N, class BinaryOperation >
inline fs_lower_triangular_matrix < T, N >
         componentwise ( const fs_lower_triangular_matrix < T, N > & a,
                         const fs_lower_triangular_matrix < T, N > & b,
                         BinaryOperation binary_operation )

{
return fixed_size_structure_componentwise ( a, b, binary_operation ) ;
}


//

template < class T, size_t N >
inline fs_lower_triangular_matrix < complex < T >, N >
         conj ( const fs_lower_triangular_matrix < complex < T >, N > & a )

{
return componentwise ( a, conj < T > ) ;
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
    result ( n1, n2 ) = m.access_symmetric ( n1, n2 ) ;

return result ;
}


//

template < class T, size_t N >
inline fs_matrix < T, N, N >
         make_full ( const fs_lower_triangular_matrix < T, N > & m )

{
fs_matrix < T, N, N > result ;

for ( size_t n1 = 0 ; n1 < N ; ++ n1 )
  for ( size_t n2 = 0 ; n2 < N ; ++ n2 )
    result ( n1, n2 ) = m.access_full ( n1, n2 ) ;

return result ;
}



// *** FS_LOWER_TRIANGULAR_MATRIX INDEXING_TRAITS ***


template < class T, size_t N >
class indexing_traits < fs_lower_triangular_matrix < T, N > >

{
public:

  typedef size_t index_type ;
  typedef T * value_type ;

  static constexpr size_t size ( const fs_lower_triangular_matrix < T, N > & )
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

  typedef T * pointer ;
  typedef const T * const_pointer ;

  typedef T & reference ;
  typedef const T & const_reference ;

  typedef pointer iterator ;
  typedef const_pointer const_iterator ;

  typedef :: reverse_iterator < iterator > reverse_iterator ;
  typedef :: reverse_iterator < const_iterator > const_reverse_iterator ;

private:

  static const size_t size_ = ( N * ( N + 1 ) ) >> 1 ;

  static constexpr size_t high_index_offset ( size_t n )
    { return ( n * ( ( N << 1 ) - 1 - n ) ) >> 1 ; }

public:

  T elements [ size_ ] ;

  pointer data ( ) noexcept
    { return elements ; }

  const_pointer data ( ) const noexcept
    { return elements ; }

  iterator begin ( ) noexcept
    { return elements ; }

  const_iterator begin ( ) const noexcept
    { return elements ; }

  iterator end ( ) noexcept
    { return elements + size_ ; }

  const_iterator end ( ) const noexcept
    { return elements + size_ ; }

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

  constexpr size_t size ( ) const noexcept
    { return size_ ; }

  constexpr size_t size1 ( ) const noexcept
    { return N ; }

  constexpr size_t size2 ( ) const noexcept
    { return N ; }

  constexpr bool empty ( ) const noexcept
    { return false ; }

  reference access ( size_t n1, size_t n2 ) noexcept
    { assert ( n1 < N ) ;
      assert ( n2 >= n1  &&  n2 < N ) ;
      return elements [ high_index_offset ( n1 ) + n2 ] ; }

  const_reference access ( size_t n1, size_t n2 ) const noexcept
    { assert ( n1 < N ) ;
      assert ( n2 >= n1  &&  n2 < N ) ;
      return elements [ high_index_offset ( n1 ) + n2 ] ; }

  reference at ( size_t n1, size_t n2 )
    { if ( n1 >= N )
        throw out_of_range
                ( "fs_upper_triangular_matrix :: at, index1 out of range" ) ;
      if ( n2 < n1  &&  n2 >= N )
        throw out_of_range
                ( "fs_upper_triangular_matrix :: at, index2 out of range" ) ;
      return elements [ high_index_offset ( n1 ) + n2 ] ; }

  const_reference at ( size_t n1, size_t n2 ) const
    { if ( n1 >= N )
        throw out_of_range
                ( "fs_upper_triangular_matrix :: at, index1 out of range" ) ;
      if ( n2 < n1  &&  n2 >= N )
        throw out_of_range
                ( "fs_upper_triangular_matrix :: at, index2 out of range" ) ;
      return elements [ high_index_offset ( n1 ) + n2 ] ; }

  pointer operator [ ] ( size_t n1 ) noexcept
    { assert ( n1 < N ) ;
      return elements + high_index_offset ( n1 ) ; }

  const_pointer operator [ ] ( size_t n1 ) const noexcept
    { assert ( n1 < N ) ;
      return elements + high_index_offset ( n1 ) ; }

  reference operator ( ) ( size_t n1, size_t n2 ) noexcept
    { return access ( n1, n2 ) ; }

  const_reference operator ( ) ( size_t n1, size_t n2 ) const noexcept
    { return access ( n1, n2 ) ; }

  T access_symmetric ( size_t n1, size_t n2 ) const
    { assert ( n1 < N ) ;
      assert ( n2 < N ) ;
      return n2 >= n1 ? access ( n1, n2 ) : access ( n2, n1 ) ; }

  T access_full ( size_t n1, size_t n2 ) const
    { assert ( n1 < N ) ;
      assert ( n2 < N ) ;
      return n2 >= n1 ? access ( n1, n2 ) : T ( 0 ) ; }

  void fill ( const T & x )
    { :: fill ( begin ( ), end ( ), x ) ; }

  void swap ( fs_upper_triangular_matrix & b )
    noexcept ( is_nothrow_swappable_v < T > )
    { swap_ranges ( begin ( ), end ( ),
                    b.begin ( ) ) ; }

  const fs_upper_triangular_matrix & operator + ( ) const
    { return * this ; }

  fs_upper_triangular_matrix operator - ( ) const
    { return componentwise ( * this, :: negate < T > ( ) ) ; }

  friend fs_upper_triangular_matrix
           operator + ( const fs_upper_triangular_matrix & a,
                        const fs_upper_triangular_matrix & b )
    { return componentwise ( a, b, plus < T > ( ) ) ; }

  friend fs_upper_triangular_matrix
           operator - ( const fs_upper_triangular_matrix & a,
                        const fs_upper_triangular_matrix & b )
    { return componentwise ( a, b, minus < T > ( ) ) ; }

  friend fs_upper_triangular_matrix
           operator * ( const fs_upper_triangular_matrix & a, const T & b )
    { return componentwise ( a, [ & ] ( const T & x ) { return x * b ; } ) ; }

  friend fs_upper_triangular_matrix
           operator * ( const T & a, const fs_upper_triangular_matrix & b )
    { return componentwise ( b, [ & ] ( const T & x ) { return a * x ; } ) ; }

  friend fs_upper_triangular_matrix
           operator / ( const fs_upper_triangular_matrix & a, const T & b )
    { return componentwise ( a, [ & ] ( const T & x ) { return x / b ; } ) ; }

  friend fs_upper_triangular_matrix
           operator % ( const fs_upper_triangular_matrix & a, const T & b )
    { return componentwise ( a, [ & ] ( const T & x ) { return x % b ; } ) ; }

  fs_lower_triangular_matrix < T, N > transposed ( ) const
    { fs_lower_triangular_matrix < T, N > result ;
      for ( size_t n1 = 0 ; n1 < N ; ++ n1 )
        for ( size_t n2 = n1 ; n2 < N ; ++ n2 )
          result ( n2, n1 ) = access ( n1, n2 ) ;
      return result ; }

  fs_upper_triangular_matrix & negate ( )
    { for ( T & x : elements )
        x = - x ;
      return * this ; }

  fs_upper_triangular_matrix &
    operator += ( const fs_upper_triangular_matrix & b )
    { for_pairs ( begin ( ), end ( ),
                  b.begin ( ),
                  [ ] ( T & x, const T & y ) { x += y ; } ) ;
      return * this ; }

  fs_upper_triangular_matrix &
    operator -= ( const fs_upper_triangular_matrix & b )
    { for_pairs ( begin ( ), end ( ),
                  b.begin ( ),
                  [ ] ( T & x, const T & y ) { x -= y ; } ) ;
      return * this ; }

  fs_upper_triangular_matrix & operator *= ( const T & b )
    { for ( T & x : elements )
        x *= b ;
      return * this ; }

  fs_upper_triangular_matrix &
    operator *= ( const fs_upper_triangular_matrix & b )
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
    { return equal ( a.begin ( ), a.end ( ),
                     b.begin ( ) ) ; }

  friend bool operator < ( const fs_upper_triangular_matrix & a,
                           const fs_upper_triangular_matrix & b )
    { return lexicographical_compare ( a.begin ( ), a.end ( ),
                                       b.begin ( ), b.end ( ) ) ; }

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

template < class T, size_t N >
void swap ( fs_upper_triangular_matrix < T, N > & a,
            fs_upper_triangular_matrix < T, N > & b )

{
a.swap ( b ) ;
}


//

template < class T, size_t N, class UnaryOperation >
inline fs_upper_triangular_matrix < T, N >
         componentwise ( const fs_upper_triangular_matrix < T, N > & a,
                         UnaryOperation unary_operation )

{
return fixed_size_structure_componentwise ( a, unary_operation ) ;
}


//

template < class T, size_t N, class BinaryOperation >
inline fs_upper_triangular_matrix < T, N >
         componentwise ( const fs_upper_triangular_matrix < T, N > & a,
                         const fs_upper_triangular_matrix < T, N > & b,
                         BinaryOperation binary_operation )

{
return fixed_size_structure_componentwise ( a, b, binary_operation ) ;
}


//

template < class T, size_t N >
inline fs_upper_triangular_matrix < complex < T >, N >
         conj ( const fs_upper_triangular_matrix < complex < T >, N > & a )

{
return componentwise ( a, conj < T > ) ;
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
  for ( size_t n2 = n1 ; n2 < N ; ++ n2 )
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
    result ( n1, n2 ) = m.access_symmetric ( n1, n2 ) ;

return result ;
}


//

template < class T, size_t N >
inline fs_matrix < T, N, N >
         make_full ( const fs_upper_triangular_matrix < T, N > & m )

{
fs_matrix < T, N, N > result ;

for ( size_t n1 = 0 ; n1 < N ; ++ n1 )
  for ( size_t n2 = 0 ; n2 < N ; ++ n2 )
    result ( n1, n2 ) = m.access_full ( n1, n2 ) ;

return result ;
}



// *** FS_UPPER_TRIANGULAR_MATRIX INDEXING_TRAITS ***


template < class T, size_t N >
class indexing_traits < fs_upper_triangular_matrix < T, N > >

{
public:

  typedef size_t index_type ;
  typedef T * value_type ;

  static constexpr size_t size ( const fs_upper_triangular_matrix < T, N > & )
    { return N ; }

} ;



#endif
