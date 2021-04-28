// Copyright Ivan Stanojevic 2021.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __MATHEXT_H

#define __MATHEXT_H



#include "cstddef.h"
#include "cassert.h"
#include "utility.h"
#include "vector.h"

#include "funtr.h"
#include "numbase.h"



// *** LINEAR ALGEBRA GLOBALS ***


//

template < class Matrix,
           class FreeVector,
           class SolutionVector >
void solve_linear_system ( Matrix & a,
                           FreeVector & b,
                           SolutionVector & x,
                           bool * singular )

{
typedef typename
  indexing_traits
    < typename indexing_traits < Matrix > :: value_type > :: value_type
  matrix_element ;

typedef typename indexing_traits < SolutionVector > :: value_type
  solution_vector_element ;

size_t dimension = indexing_size ( a ) ;

assert ( indexing_size ( b ) == dimension ) ;
assert ( indexing_size ( x ) == dimension ) ;

for ( size_t i = 0 ; i < dimension ; ++ i )
  {
  assert ( indexing_size ( a [ i ] ) == dimension ) ;

  if ( a [ i ] [ i ] == 0 )
    {
    for ( size_t j = i + 1 ; j < dimension ; ++ j )
      if ( a [ j ] [ i ] != 0 )
        {
        for ( size_t k = i ; k < dimension ; ++ k )
          swap ( a [ i ] [ k ], a [ j ] [ k ] ) ;

        swap ( b [ i ], b [ j ] ) ;

        goto pivot_set ;
        }

    if ( singular != nullptr )
      * singular = true ;

    return ;
    }

  pivot_set:

  for ( size_t j = i + 1 ; j < dimension ; ++ j )
    if ( a [ j ] [ i ] != 0 )
      {
      matrix_element c ( a [ j ] [ i ] / a [ i ] [ i ] ) ;

      a [ j ] [ i ] = 0 ;

      for ( size_t k = i + 1 ; k < dimension ; ++ k )
        a [ j ] [ k ] -= c * a [ i ] [ k ] ;

      b [ j ] -= c * b [ i ] ;
      }
  }

for ( size_t i = dimension ; i != 0 ; )
  {
  -- i ;

  solution_vector_element c ( b [ i ] ) ;

  for ( size_t k = i + 1 ; k < dimension ; ++ k )
    c -= a [ i ] [ k ] * x [ k ] ;

  x [ i ] = c / a [ i ] [ i ] ;
  }

if ( singular != nullptr )
  * singular = false ;
}


//

template < class Matrix,
           class FreeVector,
           class SolutionVector >
inline void solve_linear_system ( Matrix & a,
                                  FreeVector & b,
                                  SolutionVector & x )

{
solve_linear_system ( a, b, x, nullptr ) ;
}


//

template < class Matrix,
           class FreeVector,
           class SolutionVector >
inline void solve_linear_system ( Matrix & a,
                                  FreeVector & b,
                                  SolutionVector & x,
                                  bool & singular )

{
solve_linear_system ( a, b, x, & singular ) ;
}


//

template < class Matrix >
typename indexing_traits
           < typename indexing_traits < Matrix > :: value_type > :: value_type
  determinant ( Matrix & a )

{
typedef typename
  indexing_traits
    < typename indexing_traits < Matrix > :: value_type > :: value_type
  matrix_element ;

size_t dimension = indexing_size ( a ) ;

bool negate = false ;

for ( size_t i = 0 ; i < dimension ; ++ i )
  {
  assert ( indexing_size ( a [ i ] ) == dimension ) ;

  if ( a [ i ] [ i ] == 0 )
    {
    for ( size_t j = i + 1 ; j < dimension ; ++ j )
      if ( a [ j ] [ i ] != 0 )
        {
        for ( size_t k = i ; k < dimension ; ++ k )
          swap ( a [ i ] [ k ], a [ j ] [ k ] ) ;

        negate = ! negate ;

        goto pivot_set ;
        }

    return matrix_element ( 0 ) ;
    }

  pivot_set:

  for ( size_t j = i + 1 ; j < dimension ; ++ j )
    if ( a [ j ] [ i ] != 0 )
      {
      matrix_element c ( a [ j ] [ i ] / a [ i ] [ i ] ) ;

      a [ j ] [ i ] = 0 ;

      for ( size_t k = i + 1 ; k < dimension ; ++ k )
        a [ j ] [ k ] -= c * a [ i ] [ k ] ;
      }
  }

matrix_element r ( negate ? -1 : 1 ) ;

for ( size_t i = 0 ; i < dimension ; ++ i )
  r *= a [ i ] [ i ] ;

return r ;
}


//

template < class Matrix,
           class FreeVector,
           class PivotingCompareOperator,
           class SolutionVector >
void solve_linear_system_with_pivoting
       ( Matrix & a,
         FreeVector & b,
         PivotingCompareOperator pivoting_compare_operator,
         SolutionVector & x,
         bool * singular )

{
typedef typename indexing_traits
          < typename indexing_traits < Matrix > :: value_type > :: value_type
  matrix_element ;

typedef typename indexing_traits < SolutionVector > :: value_type
  solution_vector_element ;

size_t dimension = indexing_size ( a ) ;

assert ( indexing_size ( b ) == dimension ) ;
assert ( indexing_size ( x ) == dimension ) ;

vector < size_t > solution_index ;
solution_index.reserve ( dimension ) ;
for ( size_t i = 0 ; i < dimension ; ++ i )
  solution_index.push_back ( i ) ;

for ( size_t i = 0 ; i < dimension ; ++ i )
  {
  assert ( indexing_size ( a [ i ] ) == dimension ) ;

  {
  matrix_element c ( a [ i ] [ i ] ) ;
  size_t p = i,
         q = i ;

  for ( size_t k = i + 1 ; k < dimension ; ++ k )
    if ( pivoting_compare_operator ( c, a [ i ] [ k ] ) )
      {
      c = a [ i ] [ k ] ;
      q = k ;
      }

  for ( size_t j = i + 1 ; j < dimension ; ++ j )
    for ( size_t k = i ; k < dimension ; ++ k )
      if ( pivoting_compare_operator ( c, a [ j ] [ k ] ) )
        {
        c = a [ j ] [ k ] ;
        p = j ;
        q = k ;
        }

  if ( p != i )
    {
    for ( size_t k = i ; k < dimension ; ++ k )
      swap ( a [ i ] [ k ], a [ p ] [ k ] ) ;

    swap ( b [ i ], b [ p ] ) ;
    }

  if ( q != i )
    {
    for ( size_t j = 0 ; j < dimension ; ++ j )
      swap ( a [ j ] [ i ], a [ j ] [ q ] ) ;

    swap ( solution_index [ i ], solution_index [ q ] ) ;
    }
  }

  if ( a [ i ] [ i ] == 0 )
    {
    if ( singular != nullptr )
      * singular = true ;

    return ;
    }

  for ( size_t j = i + 1 ; j < dimension ; ++ j )
    if ( a [ j ] [ i ] != 0 )
      {
      matrix_element c ( a [ j ] [ i ] / a [ i ] [ i ] ) ;

      a [ j ] [ i ] = 0 ;

      for ( size_t k = i + 1 ; k < dimension ; ++ k )
        a [ j ] [ k ] -= c * a [ i ] [ k ] ;

      b [ j ] -= c * b [ i ] ;
      }
  }

for ( size_t i = dimension ; i != 0 ; )
  {
  -- i ;

  solution_vector_element c ( b [ i ] ) ;

  for ( size_t j = i + 1 ; j < dimension ; ++ j )
    c -= a [ i ] [ j ] * x [ solution_index [ j ] ] ;

  x [ solution_index [ i ] ] = c / a [ i ] [ i ] ;
  }

if ( singular != nullptr )
  * singular = false ;
}


//

template < class Matrix,
           class FreeVector,
           class PivotingCompareOperator,
           class SolutionVector >
inline void solve_linear_system_with_pivoting
              ( Matrix & a,
                FreeVector & b,
                PivotingCompareOperator pivoting_compare_operator,
                SolutionVector & x )

{
solve_linear_system_with_pivoting
  ( a, b, pivoting_compare_operator, x, nullptr ) ;
}


//

template < class Matrix,
           class FreeVector,
           class PivotingCompareOperator,
           class SolutionVector >
inline void solve_linear_system_with_pivoting
              ( Matrix & a,
                FreeVector & b,
                PivotingCompareOperator pivoting_compare_operator,
                SolutionVector & x,
                bool & singular )

{
solve_linear_system_with_pivoting
  ( a, b, pivoting_compare_operator, x, & singular ) ;
}


//

template < class Matrix,
           class FreeVector,
           class SolutionVector >
inline void solve_linear_system_with_pivoting
              ( Matrix & a,
                FreeVector & b,
                SolutionVector & x )

{
typedef typename indexing_traits
          < typename indexing_traits < Matrix > :: value_type > :: value_type
  matrix_element ;

solve_linear_system_with_pivoting
  ( a, b, pivoting_compare < matrix_element > ( ), x ) ;
}


//

template < class Matrix,
           class FreeVector,
           class SolutionVector >
inline void solve_linear_system_with_pivoting
              ( Matrix & a,
                FreeVector & b,
                SolutionVector & x,
                bool & singular )

{
typedef typename indexing_traits
          < typename indexing_traits < Matrix > :: value_type > :: value_type
  matrix_element ;

solve_linear_system_with_pivoting
  ( a, b, pivoting_compare < matrix_element > ( ), x, singular ) ;
}


//

template < class Matrix, class PivotingCompareOperator >
typename indexing_traits
           < typename indexing_traits < Matrix > :: value_type > :: value_type
  determinant_with_pivoting
    ( Matrix & a,
      PivotingCompareOperator pivoting_compare_operator )

{
typedef typename indexing_traits
          < typename indexing_traits < Matrix > :: value_type > :: value_type
  matrix_element ;

size_t dimension = indexing_size ( a ) ;

bool negate = false ;

for ( size_t i = 0 ; i < dimension ; ++ i )
  {
  assert ( indexing_size ( a [ i ] ) == dimension ) ;

  {
  matrix_element c ( a [ i ] [ i ] ) ;
  size_t p = i,
         q = i ;

  for ( size_t k = i + 1 ; k < dimension ; ++ k )
    if ( pivoting_compare_operator ( c, a [ i ] [ k ] ) )
      {
      c = a [ i ] [ k ] ;
      q = k ;
      }

  for ( size_t j = i + 1 ; j < dimension ; ++ j )
    for ( size_t k = i ; k < dimension ; ++ k )
      if ( pivoting_compare_operator ( c, a [ j ] [ k ] ) )
        {
        c = a [ j ] [ k ] ;
        p = j ;
        q = k ;
        }

  if ( p != i )
    {
    for ( size_t k = i ; k < dimension ; ++ k )
      swap ( a [ i ] [ k ], a [ p ] [ k ] ) ;

    negate = ! negate ;
    }

  if ( q != i )
    {
    for ( size_t j = 0 ; j < dimension ; ++ j )
      swap ( a [ j ] [ i ], a [ j ] [ q ] ) ;

    negate = ! negate ;
    }
  }

  if ( a [ i ] [ i ] == 0 )
    return matrix_element ( 0 ) ;

  for ( size_t j = i + 1 ; j < dimension ; ++ j )
    if ( a [ j ] [ i ] != 0 )
      {
      matrix_element c ( a [ j ] [ i ] / a [ i ] [ i ] ) ;

      a [ j ] [ i ] = 0 ;

      for ( size_t k = i + 1 ; k < dimension ; ++ k )
        a [ j ] [ k ] -= c * a [ i ] [ k ] ;
      }
  }

matrix_element r ( negate ? -1 : 1 ) ;

for ( size_t i = 0 ; i < dimension ; ++ i )
  r *= a [ i ] [ i ] ;

return r ;
}


//

template < class Matrix >
inline
  typename indexing_traits
             < typename indexing_traits < Matrix > :: value_type > :: value_type
    determinant_with_pivoting ( Matrix & a )

{
typedef typename indexing_traits
          < typename indexing_traits < Matrix > :: value_type > :: value_type
  matrix_element ;

return
  determinant_with_pivoting ( a, pivoting_compare < matrix_element > ( ) ) ;
}



#endif
