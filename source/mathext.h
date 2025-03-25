// Copyright Ivan Stanojevic 2025.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __MATHEXT_H

#define __MATHEXT_H



#include "type_traits.h"
#include "cstddef.h"
#include "cassert.h"
#include "utility.h"
#include "vector.h"

#include "funtr.h"
#include "numbase.h"



// *** SOLVE_LINEAR_SYSTEM ***


//

template < class Matrix,
           class FreeVector,
           class SolutionVector >
void solve_linear_system ( Matrix && a,
                           FreeVector && b,
                           SolutionVector & x,
                           bool * singular )

{
typedef indexing_vt < indexing_vt < remove_reference_t < Matrix > > >
        matrix_element ;

typedef indexing_vt < SolutionVector > solution_vector_element ;

size_t dimension = indexing_size ( a ) ;

assert ( indexing_size ( b ) == dimension ) ;
assert ( indexing_size ( x ) == dimension ) ;

#ifndef NDEBUG

for ( size_t i = 0 ; i < dimension ; ++ i )
  assert ( indexing_size ( a [ i ] ) == dimension ) ;

#endif

for ( size_t i = 0 ; i < dimension ; ++ i )
  {
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
      matrix_element c = a [ j ] [ i ] / a [ i ] [ i ] ;

      a [ j ] [ i ] = 0 ;

      for ( size_t k = i + 1 ; k < dimension ; ++ k )
        a [ j ] [ k ] -= c * a [ i ] [ k ] ;

      b [ j ] -= c * b [ i ] ;
      }
  }

for ( size_t i = dimension ; i != 0 ; )
  {
  -- i ;

  solution_vector_element c = b [ i ] ;

  for ( size_t j = i + 1 ; j < dimension ; ++ j )
    c -= a [ i ] [ j ] * x [ j ] ;

  x [ i ] = c / a [ i ] [ i ] ;
  }

if ( singular != nullptr )
  * singular = false ;
}


//

template < class Matrix,
           class FreeVector,
           class SolutionVector >
inline void solve_linear_system ( Matrix && a,
                                  FreeVector && b,
                                  SolutionVector & x )

{
solve_linear_system ( forward < Matrix > ( a ), forward < FreeVector > ( b ),
                      x, nullptr ) ;
}


//

template < class Matrix,
           class FreeVector,
           class SolutionVector >
inline void solve_linear_system ( Matrix && a,
                                  FreeVector && b,
                                  SolutionVector & x,
                                  bool & singular )

{
solve_linear_system ( forward < Matrix > ( a ), forward < FreeVector > ( b ),
                      x, & singular ) ;
}



// *** SOLVE_LINEAR_SYSTEM_WITH_PIVOTING ***


//

template < class Matrix,
           class FreeVector,
           class PivotingCompareOperator,
           class SolutionVector >
void solve_linear_system_with_pivoting
       ( Matrix && a,
         FreeVector && b,
         PivotingCompareOperator pivoting_compare_operator,
         SolutionVector & x,
         bool * singular )

{
typedef indexing_vt < indexing_vt < remove_reference_t < Matrix > > >
        matrix_element ;

typedef indexing_vt < SolutionVector > solution_vector_element ;

size_t dimension = indexing_size ( a ) ;

assert ( indexing_size ( b ) == dimension ) ;
assert ( indexing_size ( x ) == dimension ) ;

#ifndef NDEBUG

for ( size_t i = 0 ; i < dimension ; ++ i )
  assert ( indexing_size ( a [ i ] ) == dimension ) ;

#endif

vector < size_t > solution_index ;
solution_index.reserve ( dimension ) ;
for ( size_t i = 0 ; i < dimension ; ++ i )
  solution_index.push_back ( i ) ;

for ( size_t i = 0 ; i < dimension ; ++ i )
  {

  {
  matrix_element c = a [ i ] [ i ] ;
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
      matrix_element c = a [ j ] [ i ] / a [ i ] [ i ] ;

      a [ j ] [ i ] = 0 ;

      for ( size_t k = i + 1 ; k < dimension ; ++ k )
        a [ j ] [ k ] -= c * a [ i ] [ k ] ;

      b [ j ] -= c * b [ i ] ;
      }
  }

for ( size_t i = dimension ; i != 0 ; )
  {
  -- i ;

  solution_vector_element c = b [ i ] ;

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
              ( Matrix && a,
                FreeVector && b,
                PivotingCompareOperator pivoting_compare_operator,
                SolutionVector & x )

{
solve_linear_system_with_pivoting
  ( forward < Matrix > ( a ), forward < FreeVector > ( b ),
    pivoting_compare_operator,
    x, nullptr ) ;
}


//

template < class Matrix,
           class FreeVector,
           class PivotingCompareOperator,
           class SolutionVector >
inline void solve_linear_system_with_pivoting
              ( Matrix && a,
                FreeVector && b,
                PivotingCompareOperator pivoting_compare_operator,
                SolutionVector & x,
                bool & singular )

{
solve_linear_system_with_pivoting
  ( forward < Matrix > ( a ), forward < FreeVector > ( b ),
    pivoting_compare_operator,
    x, & singular ) ;
}


//

template < class Matrix,
           class FreeVector,
           class SolutionVector >
inline void solve_linear_system_with_pivoting
              ( Matrix && a,
                FreeVector && b,
                SolutionVector & x )

{
typedef indexing_vt < indexing_vt < remove_reference_t < Matrix > > >
        matrix_element ;

solve_linear_system_with_pivoting
  ( forward < Matrix > ( a ), forward < FreeVector > ( b ),
    pivoting_compare < matrix_element > ( ),
    x ) ;
}


//

template < class Matrix,
           class FreeVector,
           class SolutionVector >
inline void solve_linear_system_with_pivoting
              ( Matrix && a,
                FreeVector && b,
                SolutionVector & x,
                bool & singular )

{
typedef indexing_vt < indexing_vt < remove_reference_t < Matrix > > >
        matrix_element ;

solve_linear_system_with_pivoting
  ( forward < Matrix > ( a ), forward < FreeVector > ( b ),
    pivoting_compare < matrix_element > ( ),
    x, singular ) ;
}



// *** SOLVE_MULTIPLE_LINEAR_SYSTEMS ***


//

template < class Matrix,
           class FreeMatrix,
           class SolutionMatrix >
void solve_multiple_linear_systems ( Matrix && a,
                                     FreeMatrix && b,
                                     SolutionMatrix & x,
                                     bool * singular )

{
typedef indexing_vt < indexing_vt < remove_reference_t < Matrix > > >
        matrix_element ;

typedef indexing_vt < indexing_vt < remove_reference_t < SolutionMatrix > > >
        solution_matrix_element ;

size_t dimension = indexing_size ( a ) ;

assert ( indexing_size ( b ) == dimension ) ;
assert ( indexing_size ( x ) == dimension ) ;

size_t total_systems = dimension > 0 ? indexing_size ( b [ 0 ] ) : 0 ;

#ifndef NDEBUG

for ( size_t i = 0 ; i < dimension ; ++ i )
  {
  assert ( indexing_size ( a [ i ] ) == dimension ) ;
  assert ( indexing_size ( b [ i ] ) == total_systems ) ;
  assert ( indexing_size ( x [ i ] ) == total_systems ) ;
  }

#endif

for ( size_t i = 0 ; i < dimension ; ++ i )
  {
  if ( a [ i ] [ i ] == 0 )
    {
    for ( size_t j = i + 1 ; j < dimension ; ++ j )
      if ( a [ j ] [ i ] != 0 )
        {
        for ( size_t k = i ; k < dimension ; ++ k )
          swap ( a [ i ] [ k ], a [ j ] [ k ] ) ;

        for ( size_t k = 0 ; k < total_systems ; ++ k )
          swap ( b [ i ] [ k ], b [ j ] [ k ] ) ;

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
      matrix_element c = a [ j ] [ i ] / a [ i ] [ i ] ;

      a [ j ] [ i ] = 0 ;

      for ( size_t k = i + 1 ; k < dimension ; ++ k )
        a [ j ] [ k ] -= c * a [ i ] [ k ] ;

      for ( size_t k = 0 ; k < total_systems ; ++ k )
        b [ j ] [ k ] -= c * b [ i ] [ k ] ;
      }
  }

for ( size_t i = dimension ; i != 0 ; )
  {
  -- i ;

  for ( size_t k = 0 ; k < total_systems ; ++ k )
    {
    solution_matrix_element c = b [ i ] [ k ] ;

    for ( size_t j = i + 1 ; j < dimension ; ++ j )
      c -= a [ i ] [ j ] * x [ j ] [ k ] ;

    x [ i ] [ k ] = c / a [ i ] [ i ] ;
    }
  }

if ( singular != nullptr )
  * singular = false ;
}


//

template < class Matrix,
           class FreeMatrix,
           class SolutionMatrix >
inline void solve_multiple_linear_systems ( Matrix && a,
                                            FreeMatrix && b,
                                            SolutionMatrix & x )

{
solve_multiple_linear_systems
  ( forward < Matrix > ( a ), forward < FreeMatrix > ( b ),
    x, nullptr ) ;
}


//

template < class Matrix,
           class FreeMatrix,
           class SolutionMatrix >
inline void solve_multiple_linear_systems ( Matrix && a,
                                            FreeMatrix && b,
                                            SolutionMatrix & x,
                                            bool & singular )

{
solve_multiple_linear_systems
  ( forward < Matrix > ( a ), forward < FreeMatrix > ( b ),
    x, & singular ) ;
}



// *** SOLVE_MULTIPLE_LINEAR_SYSTEMS_WITH_PIVOTING ***


//

template < class Matrix,
           class FreeMatrix,
           class PivotingCompareOperator,
           class SolutionMatrix >
void solve_multiple_linear_systems_with_pivoting
       ( Matrix && a,
         FreeMatrix && b,
         PivotingCompareOperator pivoting_compare_operator,
         SolutionMatrix & x,
         bool * singular )

{
typedef indexing_vt < indexing_vt < remove_reference_t < Matrix > > >
        matrix_element ;

typedef indexing_vt < indexing_vt < SolutionMatrix > >
        solution_matrix_element ;

size_t dimension = indexing_size ( a ) ;

assert ( indexing_size ( b ) == dimension ) ;
assert ( indexing_size ( x ) == dimension ) ;

size_t total_systems = dimension > 0 ? indexing_size ( b [ 0 ] ) : 0 ;

#ifndef NDEBUG

for ( size_t i = 0 ; i < dimension ; ++ i )
  {
  assert ( indexing_size ( a [ i ] ) == dimension ) ;
  assert ( indexing_size ( b [ i ] ) == total_systems ) ;
  assert ( indexing_size ( x [ i ] ) == total_systems ) ;
  }

#endif

vector < size_t > solution_index ;
solution_index.reserve ( dimension ) ;
for ( size_t i = 0 ; i < dimension ; ++ i )
  solution_index.push_back ( i ) ;

for ( size_t i = 0 ; i < dimension ; ++ i )
  {

  {
  matrix_element c = a [ i ] [ i ] ;
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

    for ( size_t k = 0 ; k < total_systems ; ++ k )
      swap ( b [ i ] [ k ], b [ p ] [ k ] ) ;
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
      matrix_element c = a [ j ] [ i ] / a [ i ] [ i ] ;

      a [ j ] [ i ] = 0 ;

      for ( size_t k = i + 1 ; k < dimension ; ++ k )
        a [ j ] [ k ] -= c * a [ i ] [ k ] ;

      for ( size_t k = 0 ; k < total_systems ; ++ k )
        b [ j ] [ k ] -= c * b [ i ] [ k ] ;
      }
  }

for ( size_t i = dimension ; i != 0 ; )
  {
  -- i ;

  for ( size_t k = 0 ; k < total_systems ; ++ k )
    {
    solution_matrix_element c = b [ i ] [ k ] ;

    for ( size_t j = i + 1 ; j < dimension ; ++ j )
      c -= a [ i ] [ j ] * x [ solution_index [ j ] ] [ k ] ;

    x [ solution_index [ i ] ] [ k ] = c / a [ i ] [ i ] ;
    }
  }

if ( singular != nullptr )
  * singular = false ;
}


//

template < class Matrix,
           class FreeMatrix,
           class PivotingCompareOperator,
           class SolutionMatrix >
inline void solve_multiple_linear_systems_with_pivoting
              ( Matrix && a,
                FreeMatrix && b,
                PivotingCompareOperator pivoting_compare_operator,
                SolutionMatrix & x )

{
solve_multiple_linear_systems_with_pivoting
  ( forward < Matrix > ( a ), forward < FreeMatrix > ( b ),
    pivoting_compare_operator,
    x, nullptr ) ;
}


//

template < class Matrix,
           class FreeMatrix,
           class PivotingCompareOperator,
           class SolutionMatrix >
inline void solve_multiple_linear_systems_with_pivoting
              ( Matrix && a,
                FreeMatrix && b,
                PivotingCompareOperator pivoting_compare_operator,
                SolutionMatrix & x,
                bool & singular )

{
solve_multiple_linear_systems_with_pivoting
  ( forward < Matrix > ( a ), forward < FreeMatrix > ( b ),
    pivoting_compare_operator,
    x, & singular ) ;
}


//

template < class Matrix,
           class FreeMatrix,
           class SolutionMatrix >
inline void solve_multiple_linear_systems_with_pivoting
              ( Matrix && a,
                FreeMatrix && b,
                SolutionMatrix & x )

{
typedef indexing_vt < indexing_vt < remove_reference_t < Matrix > > >
        matrix_element ;

solve_multiple_linear_systems_with_pivoting
  ( forward < Matrix > ( a ), forward < FreeMatrix > ( b ),
    pivoting_compare < matrix_element > ( ),
    x ) ;
}


//

template < class Matrix,
           class FreeMatrix,
           class SolutionMatrix >
inline void solve_multiple_linear_systems_with_pivoting
              ( Matrix && a,
                FreeMatrix && b,
                SolutionMatrix & x,
                bool & singular )

{
typedef indexing_vt < indexing_vt < remove_reference_t < Matrix > > >
        matrix_element ;

solve_multiple_linear_systems_with_pivoting
  ( forward < Matrix > ( a ), forward < FreeMatrix > ( b ),
    pivoting_compare < matrix_element > ( ),
    x, singular ) ;
}



// *** DETERMINANT ***


//

template < class Matrix >
indexing_vt < indexing_vt < remove_reference_t < Matrix > > >
  determinant ( Matrix && a )

{
typedef indexing_vt < indexing_vt < remove_reference_t < Matrix > > >
        matrix_element ;

size_t dimension = indexing_size ( a ) ;

#ifndef NDEBUG

for ( size_t i = 0 ; i < dimension ; ++ i )
  assert ( indexing_size ( a [ i ] ) == dimension ) ;

#endif

bool negated = false ;

for ( size_t i = 0 ; i < dimension ; ++ i )
  {
  if ( a [ i ] [ i ] == 0 )
    {
    for ( size_t j = i + 1 ; j < dimension ; ++ j )
      if ( a [ j ] [ i ] != 0 )
        {
        for ( size_t k = i ; k < dimension ; ++ k )
          swap ( a [ i ] [ k ], a [ j ] [ k ] ) ;

        negated = ! negated ;

        goto pivot_set ;
        }

    return matrix_element ( 0 ) ;
    }

  pivot_set:

  for ( size_t j = i + 1 ; j < dimension ; ++ j )
    if ( a [ j ] [ i ] != 0 )
      {
      matrix_element c = a [ j ] [ i ] / a [ i ] [ i ] ;

      a [ j ] [ i ] = 0 ;

      for ( size_t k = i + 1 ; k < dimension ; ++ k )
        a [ j ] [ k ] -= c * a [ i ] [ k ] ;
      }
  }

matrix_element r = negated ? -1 : 1 ;

for ( size_t i = 0 ; i < dimension ; ++ i )
  r *= a [ i ] [ i ] ;

return r ;
}



// *** DETERMINANT_WITH_PIVOTING ***


//

template < class Matrix, class PivotingCompareOperator >
indexing_vt < indexing_vt < remove_reference_t < Matrix > > >
  determinant_with_pivoting
    ( Matrix && a,
      PivotingCompareOperator pivoting_compare_operator )

{
typedef indexing_vt < indexing_vt < remove_reference_t < Matrix > > >
        matrix_element ;

size_t dimension = indexing_size ( a ) ;

#ifndef NDEBUG

for ( size_t i = 0 ; i < dimension ; ++ i )
  assert ( indexing_size ( a [ i ] ) == dimension ) ;

#endif

bool negated = false ;

for ( size_t i = 0 ; i < dimension ; ++ i )
  {

  {
  matrix_element c = a [ i ] [ i ] ;
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

    negated = ! negated ;
    }

  if ( q != i )
    {
    for ( size_t j = 0 ; j < dimension ; ++ j )
      swap ( a [ j ] [ i ], a [ j ] [ q ] ) ;

    negated = ! negated ;
    }
  }

  if ( a [ i ] [ i ] == 0 )
    return matrix_element ( 0 ) ;

  for ( size_t j = i + 1 ; j < dimension ; ++ j )
    if ( a [ j ] [ i ] != 0 )
      {
      matrix_element c = a [ j ] [ i ] / a [ i ] [ i ] ;

      a [ j ] [ i ] = 0 ;

      for ( size_t k = i + 1 ; k < dimension ; ++ k )
        a [ j ] [ k ] -= c * a [ i ] [ k ] ;
      }
  }

matrix_element r = negated ? -1 : 1 ;

for ( size_t i = 0 ; i < dimension ; ++ i )
  r *= a [ i ] [ i ] ;

return r ;
}


//

template < class Matrix >
inline indexing_vt < indexing_vt < remove_reference_t < Matrix > > >
  determinant_with_pivoting ( Matrix && a )

{
typedef indexing_vt < indexing_vt < remove_reference_t < Matrix > > >
  matrix_element ;

return determinant_with_pivoting
         ( forward < Matrix > ( a ), pivoting_compare < matrix_element > ( ) ) ;
}



// *** INVERT_MATRIX ***


//

template < class Matrix,
           class InverseMatrix >
void invert_matrix ( Matrix && a,
                     InverseMatrix & b,
                     bool * singular )

{
typedef indexing_vt < indexing_vt < remove_reference_t < Matrix > > >
        matrix_element ;

size_t dimension = indexing_size ( a ) ;

assert ( indexing_size ( b ) == dimension ) ;

#ifndef NDEBUG

for ( size_t i = 0 ; i < dimension ; ++ i )
  {
  assert ( indexing_size ( a [ i ] ) == dimension ) ;
  assert ( indexing_size ( b [ i ] ) == dimension ) ;
  }

#endif

for ( size_t i = 0 ; i < dimension ; ++ i )
  for ( size_t j = 0 ; j < dimension ; ++ j )
    b [ i ] [ j ] = i == j ? 1 : 0 ;

for ( size_t i = 0 ; i < dimension ; ++ i )
  {
  if ( a [ i ] [ i ] == 0 )
    {
    for ( size_t j = i + 1 ; j < dimension ; ++ j )
      if ( a [ j ] [ i ] != 0 )
        {
        for ( size_t k = i ; k < dimension ; ++ k )
          swap ( a [ i ] [ k ], a [ j ] [ k ] ) ;

        for ( size_t k = 0 ; k < dimension ; ++ k )
          swap ( b [ i ] [ k ], b [ j ] [ k ] ) ;

        goto pivot_set ;
        }

    if ( singular != nullptr )
      * singular = true ;

    return ;
    }

  pivot_set:

  {
  matrix_element c = a [ i ] [ i ] ;

  if ( c != 1 )
    {
    a [ i ] [ i ] = 1 ;

    for ( size_t j = i + 1 ; j < dimension ; ++ j )
      a [ i ] [ j ] /= c ;

    for ( size_t j = 0 ; j < dimension ; ++ j )
      b [ i ] [ j ] /= c ;
    }
  }

  for ( size_t j = 0 ; j < dimension ; ++ j )
    {
    if ( j == i )
      continue ;

    matrix_element c = a [ j ] [ i ] ;

    if ( c != 0 )
      {
      a [ j ] [ i ] = 0 ;

      for ( size_t k = i + 1 ; k < dimension ; ++ k )
        a [ j ] [ k ] -= c * a [ i ] [ k ] ;

      for ( size_t k = 0 ; k < dimension ; ++ k )
        b [ j ] [ k ] -= c * b [ i ] [ k ] ;
      }
    }
  }

if ( singular != nullptr )
  * singular = false ;
}


//

template < class Matrix,
           class InverseMatrix >
inline void invert_matrix ( Matrix && a,
                            InverseMatrix & b )

{
invert_matrix ( forward < Matrix > ( a ), b, nullptr ) ;
}


//

template < class Matrix,
           class InverseMatrix >
inline void invert_matrix ( Matrix && a,
                            InverseMatrix & b,
                            bool & singular )

{
invert_matrix ( forward < Matrix > ( a ), b, & singular ) ;
}



// *** INVERT_MATRIX_WITH_PIVOTING ***


//

template < class Matrix,
           class PivotingCompareOperator,
           class InverseMatrix >
void invert_matrix_with_pivoting
       ( Matrix && a,
         PivotingCompareOperator pivoting_compare_operator,
         InverseMatrix & b,
         bool * singular )

{
typedef indexing_vt < indexing_vt < remove_reference_t < Matrix > > >
        matrix_element ;

size_t dimension = indexing_size ( a ) ;

assert ( indexing_size ( b ) == dimension ) ;

#ifndef NDEBUG

for ( size_t i = 0 ; i < dimension ; ++ i )
  {
  assert ( indexing_size ( a [ i ] ) == dimension ) ;
  assert ( indexing_size ( b [ i ] ) == dimension ) ;
  }

#endif

vector < size_t > line_index ;
line_index.reserve ( dimension ) ;
for ( size_t i = 0 ; i < dimension ; ++ i )
  line_index.push_back ( i ) ;

for ( size_t i = 0 ; i < dimension ; ++ i )
  for ( size_t j = 0 ; j < dimension ; ++ j )
    b [ i ] [ j ] = i == j ? 1 : 0 ;

for ( size_t i = 0 ; i < dimension ; ++ i )
  {
  size_t li = line_index [ i ] ;

  {
  matrix_element c = a [ li ] [ li ] ;
  size_t p = i,
         q = i ;

  for ( size_t k = i + 1 ; k < dimension ; ++ k )
    {
    size_t lk = line_index [ k ] ;

    if ( pivoting_compare_operator ( c, a [ li ] [ lk ] ) )
      {
      c = a [ li ] [ lk ] ;
      q = k ;
      }
    }

  for ( size_t j = i + 1 ; j < dimension ; ++ j )
    {
    size_t lj = line_index [ j ] ;

    for ( size_t k = i ; k < dimension ; ++ k )
      {
      size_t lk = line_index [ k ] ;

      if ( pivoting_compare_operator ( c, a [ lj ] [ lk ] ) )
        {
        c = a [ lj ] [ lk ] ;
        p = j ;
        q = k ;
        }
      }
    }

  if ( p != i )
    {
    size_t lp = line_index [ p ] ;

    for ( size_t k = i ; k < dimension ; ++ k )
      {
      size_t lk = line_index [ k ] ;

      swap ( a [ li ] [ lk ], a [ lp ] [ lk ] ) ;
      }

    for ( size_t lk = 0 ; lk < dimension ; ++ lk )
      swap ( b [ li ] [ lk ], b [ lp ] [ lk ] ) ;
    }

  if ( q != i )
    {
    swap ( line_index [ i ], line_index [ q ] ) ;
    li = line_index [ i ] ;
    }
  }

  {
  matrix_element c = a [ li ] [ li ] ;

  if ( c == 0 )
    {
    if ( singular != nullptr )
      * singular = true ;

    return ;
    }

  if ( c != 1 )
    {
    a [ li ] [ li ] = 1 ;

    for ( size_t j = i + 1 ; j < dimension ; ++ j )
      {
      size_t lj = line_index [ j ] ;

      a [ li ] [ lj ] /= c ;
      }

    for ( size_t lj = 0 ; lj < dimension ; ++ lj )
      b [ li ] [ lj ] /= c ;
    }
  }

  for ( size_t lj = 0 ; lj < dimension ; ++ lj )
    {
    if ( lj == li )
      continue ;

    matrix_element c = a [ lj ] [ li ] ;

    if ( c != 0 )
      {
      a [ lj ] [ li ] = 0 ;

      for ( size_t k = i + 1 ; k < dimension ; ++ k )
        {
        size_t lk = line_index [ k ] ;

        a [ lj ] [ lk ] -= c * a [ li ] [ lk ] ;
        }

      for ( size_t lk = 0 ; lk < dimension ; ++ lk )
        b [ lj ] [ lk ] -= c * b [ li ] [ lk ] ;
      }
    }
  }

if ( singular != nullptr )
  * singular = false ;
}


//

template < class Matrix,
           class PivotingCompareOperator,
           class InverseMatrix >
inline void invert_matrix_with_pivoting
              ( Matrix && a,
                PivotingCompareOperator pivoting_compare_operator,
                InverseMatrix & b )

{
invert_matrix_with_pivoting
  ( forward < Matrix > ( a ), pivoting_compare_operator,
    b, nullptr ) ;
}


//

template < class Matrix,
           class PivotingCompareOperator,
           class InverseMatrix >
inline void invert_matrix_with_pivoting
              ( Matrix && a,
                PivotingCompareOperator pivoting_compare_operator,
                InverseMatrix & b,
                bool & singular )

{
invert_matrix_with_pivoting
  ( forward < Matrix > ( a ), pivoting_compare_operator,
    b, & singular ) ;
}


//

template < class Matrix,
           class InverseMatrix >
inline void invert_matrix_with_pivoting ( Matrix && a,
                                          InverseMatrix & b )

{
typedef indexing_vt < indexing_vt < remove_reference_t < Matrix > > >
        matrix_element ;

invert_matrix_with_pivoting
  ( forward < Matrix > ( a ), pivoting_compare < matrix_element > ( ),
    b ) ;
}


//

template < class Matrix,
           class InverseMatrix >
inline void invert_matrix_with_pivoting ( Matrix && a,
                                          InverseMatrix & b,
                                          bool & singular )

{
typedef indexing_vt < indexing_vt < remove_reference_t < Matrix > > >
        matrix_element ;

invert_matrix_with_pivoting
  ( forward < Matrix > ( a ), pivoting_compare < matrix_element > ( ),
    b, singular ) ;
}



#endif
