// Copyright Ivan Stanojevic 2022.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __SIMPLEX_H

#define __SIMPLEX_H



#include "cassert.h"
#include "cstddef.h"
#include "vector.h"
#include "algorithm.h"
#include "type_traits.h"
#include "utility.h"

#include "numbase.h"
#include "funtr.h"



// *** SIMPLEX_RESULT ***


enum simplex_result { simplex_result_ok,
                      simplex_result_no_solution,
                      simplex_result_unbounded } ;



// *** RAW_SIMPLEX ***


template < class Tableau,
           class ColumnToRow,
           class RowToColumn >
simplex_result raw_simplex ( Tableau & tableau,
                             ColumnToRow & column_to_row,
                             RowToColumn & row_to_column )

{
typedef typename
  indexing_traits
    < typename indexing_traits < Tableau > :: value_type > :: value_type
  element ;

size_t total_variables = sequence_size ( column_to_row ),
       total_constraints = sequence_size ( row_to_column ) ;

#ifndef NDEBUG

assert ( total_variables >= total_constraints ) ;

assert ( sequence_size ( tableau ) == total_constraints + 1 ) ;

for ( size_t i = 0 ; i < total_constraints + 1 ; ++ i )
  assert ( sequence_size ( tableau [ i ] ) == total_variables + 1 ) ;

{
vector < size_t > sorted_column_to_row ;
sorted_column_to_row.reserve ( total_variables ) ;

for ( size_t j = 0 ; j < total_variables ; ++ j )
  sorted_column_to_row.push_back ( column_to_row [ j ] ) ;

sort ( sorted_column_to_row.begin ( ), sorted_column_to_row.end ( ) ) ;

size_t total_degrees_of_freedom = total_variables - total_constraints ;

for ( size_t j = 0 ; j < total_variables ; ++ j )
  assert (    sorted_column_to_row [ j ]
           == (   j < total_degrees_of_freedom
                ? 0
                : j - total_degrees_of_freedom + 1 ) ) ;
}

for ( size_t i = 1 ; i < total_constraints + 1 ; ++ i )
  assert ( tableau [ i ] [ 0 ] >= 0 ) ;

for ( size_t j = 1 ; j < total_variables + 1 ; ++ j )
  {
  size_t r = column_to_row [ j - 1 ] ;

  if ( r != 0 )
    {
    assert ( row_to_column [ r - 1 ] == j ) ;

    for ( size_t i = 0 ; i < total_constraints + 1 ; ++ i )
      assert ( tableau [ i ] [ j ] == ( i == r ? 1 : 0 ) ) ;
    }
  }

#endif

for ( ; ; )
  {
  size_t pivot_i = 0,
         pivot_j = 0 ;

  element max_delta ;

  for ( size_t j = 1 ; j < total_variables + 1 ; ++ j )
    {
    element cj = tableau [ 0 ] [ j ] ;

    if ( cj < 0 )
      {
      size_t column_pivot_i = 0 ;
      element min_ratio ;
      size_t min_old_pivot_j ;

      for ( size_t i = 1 ; i < total_constraints + 1 ; ++ i )
        {
        element aij = tableau [ i ] [ j ] ;

        if ( aij > 0 )
          {
          element ratio = tableau [ i ] [ 0 ] / aij ;
          size_t old_pivot_j = row_to_column [ i - 1 ] ;

          if (     column_pivot_i == 0
               ||  min_ratio > ratio
               ||  (     min_ratio == ratio
                     &&  min_old_pivot_j > old_pivot_j ) )
            {
            column_pivot_i = i ;
            min_ratio = ratio ;
            min_old_pivot_j = old_pivot_j ;
            }
          }
        }

      if ( column_pivot_i == 0 )
        return simplex_result_unbounded ;

      element delta = - cj * min_ratio ;

      if ( pivot_i == 0  ||  max_delta < delta )
        {
        pivot_i = column_pivot_i ;
        pivot_j = j ;
        max_delta = delta ;
        }
      }
    }

  if ( pivot_i == 0 )
    return simplex_result_ok ;

  {
  element pivot = tableau [ pivot_i ] [ pivot_j ] ;

  for ( size_t j = 0 ; j < total_variables + 1 ; ++ j )
    if ( j == pivot_j )
      tableau [ pivot_i ] [ j ] = 1 ;
    else
      tableau [ pivot_i ] [ j ] /= pivot ;
  }

  for ( size_t i = 0 ; i < total_constraints + 1 ; ++ i )
    if ( i != pivot_i )
      {
      element coef = tableau [ i ] [ pivot_j ] ;

      for ( size_t j = 0 ; j < total_variables + 1 ; ++ j )
        if ( j == pivot_j )
          tableau [ i ] [ j ] = 0 ;
        else
          tableau [ i ] [ j ] -= coef * tableau [ pivot_i ] [ j ] ;
      }

  column_to_row [ row_to_column [ pivot_i - 1 ] - 1 ] = 0 ;
  column_to_row [ pivot_j - 1 ] = pivot_i ;
  row_to_column [ pivot_i - 1 ] = pivot_j ;
  }
}



// *** EXACT_SIMPLEX ***


// pre:  all input value types are the same
//       arithmetic is exact
// post: result_vector = optimizing variable values
//       result_value = optimum objective function value

template < class ObjectiveFunctionVector,
           class EqConstraintMatrix,
           class EqConstraintFreeVector,
           class ResultVector,
           class ResultValue >
simplex_result
  exact_simplex ( const ObjectiveFunctionVector & objective_function_vector,
                  const EqConstraintMatrix & eq_constraint_matrix,
                  const EqConstraintFreeVector & eq_constraint_free_vector,
                  ResultVector & result_vector,
                  ResultValue & result_value,
                  bool maximize = false )

{
typedef typename indexing_traits < ObjectiveFunctionVector > :: value_type
  element ;

static_assert
  (    is_same < element,
                    typename indexing_traits
                      <    typename indexing_traits < EqConstraintMatrix >
                        :: value_type >
                 :: value_type >
    :: value,
    "" ) ;

static_assert
  (    is_same < element,
                    typename indexing_traits < EqConstraintFreeVector >
                 :: value_type >
    :: value,
    "" ) ;

size_t total_variables = sequence_size ( objective_function_vector ),
       total_constraints = sequence_size ( eq_constraint_matrix ) ;

#ifndef NDEBUG

for ( size_t i = 0 ; i < total_constraints ; ++ i )
  assert ( sequence_size ( eq_constraint_matrix [ i ] ) == total_variables ) ;

assert ( sequence_size ( eq_constraint_free_vector ) == total_constraints ) ;

assert ( sequence_size ( result_vector ) == total_variables ) ;

#endif

vector < vector < element > >
  tableau
    ( total_constraints + 1,
      vector < element > ( total_variables + total_constraints + 1, 0 ) ) ;

vector < size_t > column_to_row ( total_variables + total_constraints, 0 ),
                  row_to_column ( total_constraints, 0 ) ;

vector < element > & row_0 = tableau.front ( ) ;

for ( size_t i = 1 ; i < total_constraints + 1 ; ++ i )
  {
  vector < element > & row_i = tableau [ i ] ;

  element bi = eq_constraint_free_vector [ i - 1 ] ;
  bool negative = bi < 0 ;

  if ( negative )
    bi = - bi ;

  row_0 [ 0 ] -= bi ;
  row_i [ 0 ] = bi ;

  for ( size_t j = 1 ; j < total_variables + 1 ; ++ j )
    {
    element aij = eq_constraint_matrix [ i - 1 ] [ j - 1 ] ;

    if ( negative )
      aij = - aij ;

    row_0 [ j ] -= aij ;
    row_i [ j ] = aij ;
    }

  size_t j = total_variables + i ;

  row_i [ j ] = 1 ;

  column_to_row [ j - 1 ] = i ;
  row_to_column [ i - 1 ] = j ;
  }

raw_simplex ( tableau, column_to_row, row_to_column ) ;

if ( tableau [ 0 ] [ 0 ] != 0 )
  return simplex_result_no_solution ;

{
const size_t *
  artificial_column_to_row = column_to_row.data ( ) + total_variables ;

for ( vector < element > & row : tableau )
  row.erase ( remove_if_position
                ( row.begin ( ) + ( total_variables + 1 ), row.end ( ),
                  [ = ] ( size_t n )
                    { return artificial_column_to_row [ n ] == 0 ; } ),
              row.end ( ) ) ;
}

column_to_row.erase ( remove ( column_to_row.begin ( ) + total_variables,
                               column_to_row.end ( ),
                               0 ),
                      column_to_row.end ( ) ) ;

assert ( all_of ( row_0.begin ( ) + ( total_variables + 1 ),
                  row_0.end ( ),
                  [ ] ( const element & c ) { return c == 0 ; } ) ) ;

for ( size_t j = 1 ; j < total_variables + 1 ; ++ j )
  {
  element c = objective_function_vector [ j - 1 ] ;
  row_0 [ j ] = maximize ? - c : c ;
  }

for ( size_t j = 1 ; j < total_variables + 1 ; ++ j )
  {
  size_t i = column_to_row [ j - 1 ] ;

  if ( i != 0 )
    {
    const vector < element > & row_i = tableau [ i ] ;

    assert ( row_i [ j ] == 1 ) ;

    element cj = row_0 [ j ] ;

    for ( size_t k = 0 ; k < total_variables + 1 ; ++ k )
      if ( k == j )
        row_0 [ k ] = 0 ;
      else
        row_0 [ k ] -= cj * row_i [ k ] ;
    }
  }

while ( column_to_row.size ( ) > total_variables )
  {
  size_t pivot_i = column_to_row.back ( ) ;
  assert ( pivot_i != 0 ) ;

  vector < element > & pivot_row = tableau [ pivot_i ] ;
  assert ( pivot_row [ 0 ] == 0 ) ;
  assert ( pivot_row [ column_to_row.size ( ) ] == 1 ) ;

  size_t pivot_j = 0 ;

  {
  element max_abs_aij = 0 ;

  for ( size_t j = 1 ; j < column_to_row.size ( ) ; ++ j )
    {
    element abs_aij = abs ( pivot_row [ j ] ) ;

    if ( max_abs_aij < abs_aij )
      {
      pivot_j = j ;
      max_abs_aij = abs_aij ;
      }
    }
  }

  if ( pivot_j == 0 )
    {
    if ( pivot_i != tableau.size ( ) - 1 )
      pivot_row = move ( tableau.back ( ) ) ;

    tableau.pop_back ( ) ;

    size_t j = row_to_column.back ( ) ;

    column_to_row [ j - 1 ] = pivot_i ;
    row_to_column [ pivot_i - 1 ] = j ;

    row_to_column.pop_back ( ) ;
    }
  else
    {

    {
    element pivot = pivot_row [ pivot_j ] ;

    for ( size_t j = 1 ; j < column_to_row.size ( ) + 1 ; ++ j )
      if ( j == pivot_j )
        pivot_row [ j ] = 1 ;
      else
        pivot_row [ j ] /= pivot ;
    }

    for ( size_t i = 0 ; i < tableau.size ( ) ; ++ i )
      if ( i != pivot_i )
        {
        vector < element > & row_i = tableau [ i ] ;

        element coef = row_i [ pivot_j ] ;

        for ( size_t j = 1 ; j < column_to_row.size ( ) + 1 ; ++ j )
          if ( j == pivot_j )
            row_i [ j ] = 0 ;
          else
            row_i [ j ] -= coef * pivot_row [ j ] ;
        }

    column_to_row [ pivot_j - 1 ] = pivot_i ;
    row_to_column [ pivot_i - 1 ] = pivot_j ;
    }

  for ( vector < element > & row : tableau )
    row.pop_back ( ) ;

  column_to_row.pop_back ( ) ;
  }

simplex_result
  status = raw_simplex ( tableau, column_to_row, row_to_column ) ;

if ( status == simplex_result_unbounded )
  return simplex_result_unbounded ;

for ( size_t j = 1 ; j < total_variables + 1 ; ++ j )
  {
  size_t i = column_to_row [ j - 1 ] ;
  result_vector [ j - 1 ] = i != 0 ? tableau [ i ] [ 0 ] : 0 ;
  }

element t = tableau [ 0 ] [ 0 ] ;
result_value = maximize ? t : - t ;

return simplex_result_ok ;
}


// pre:  all input value types are the same
//       arithmetic is exact
// post: result_vector = optimizing variable values
//       result_value = optimum objective function value

template < class ObjectiveFunctionVector,
           class EqConstraintMatrix,
           class EqConstraintFreeVector,
           class LeqConstraintMatrix,
           class LeqConstraintFreeVector,
           class GeqConstraintMatrix,
           class GeqConstraintFreeVector,
           class ResultVector,
           class ResultValue >
simplex_result
  exact_simplex ( const ObjectiveFunctionVector & objective_function_vector,
                  const EqConstraintMatrix & eq_constraint_matrix,
                  const EqConstraintFreeVector & eq_constraint_free_vector,
                  const LeqConstraintMatrix & leq_constraint_matrix,
                  const LeqConstraintFreeVector & leq_constraint_free_vector,
                  const GeqConstraintMatrix & geq_constraint_matrix,
                  const GeqConstraintFreeVector & geq_constraint_free_vector,
                  ResultVector & result_vector,
                  ResultValue & result_value,
                  bool maximize = false )

{
typedef typename indexing_traits < ObjectiveFunctionVector > :: value_type
  element ;

static_assert
  (    is_same < element,
                    typename indexing_traits
                      <    typename indexing_traits < EqConstraintMatrix >
                        :: value_type >
                 :: value_type >
    :: value,
    "" ) ;

static_assert
  (    is_same < element,
                    typename indexing_traits < EqConstraintFreeVector >
                 :: value_type >
    :: value,
    "" ) ;

static_assert
  (    is_same < element,
                    typename indexing_traits
                      <    typename indexing_traits < LeqConstraintMatrix >
                        :: value_type >
                 :: value_type >
    :: value,
    "" ) ;

static_assert
  (    is_same < element,
                    typename indexing_traits < LeqConstraintFreeVector >
                 :: value_type >
    :: value,
    "" ) ;

static_assert
  (    is_same < element,
                    typename indexing_traits
                      <    typename indexing_traits < GeqConstraintMatrix >
                        :: value_type >
                 :: value_type >
    :: value,
    "" ) ;

static_assert
  (    is_same < element,
                    typename indexing_traits < GeqConstraintFreeVector >
                 :: value_type >
    :: value,
    "" ) ;

size_t total_base_variables = sequence_size ( objective_function_vector ),
       total_eq_constraints = sequence_size ( eq_constraint_matrix ),
       total_leq_constraints = sequence_size ( leq_constraint_matrix ),
       total_geq_constraints = sequence_size ( geq_constraint_matrix ) ;

#ifndef NDEBUG

for ( size_t i = 0 ; i < total_eq_constraints ; ++ i )
  assert (    sequence_size ( eq_constraint_matrix [ i ] )
           == total_base_variables ) ;

assert (    sequence_size ( eq_constraint_free_vector )
         == total_eq_constraints ) ;

for ( size_t i = 0 ; i < total_leq_constraints ; ++ i )
  assert (    sequence_size ( leq_constraint_matrix [ i ] )
           == total_base_variables ) ;

assert (    sequence_size ( leq_constraint_free_vector )
         == total_leq_constraints ) ;

for ( size_t i = 0 ; i < total_geq_constraints ; ++ i )
  assert (    sequence_size ( geq_constraint_matrix [ i ] )
           == total_base_variables ) ;

assert (    sequence_size ( geq_constraint_free_vector )
         == total_geq_constraints ) ;

assert ( sequence_size ( result_vector ) == total_base_variables ) ;

#endif

size_t total_neq_constraints = total_leq_constraints + total_geq_constraints,
       total_variables = total_base_variables + total_neq_constraints,
       total_constraints = total_eq_constraints + total_neq_constraints ;

vector < element > extended_objective_function_vector ( total_variables, 0 ) ;

for ( size_t j = 0 ; j < total_base_variables ; ++ j )
  extended_objective_function_vector [ j ] = objective_function_vector [ j ] ;

vector < vector < element > >
  constraint_matrix ( total_constraints,
                      vector < element > ( total_variables, 0 ) ) ;

vector < element > constraint_free_vector ( total_constraints, 0 ) ;

for ( size_t i = 0 ; i < total_eq_constraints ; ++ i )
  {
  for ( size_t j = 0 ; j < total_base_variables ; ++ j )
    constraint_matrix [ i ] [ j ] = eq_constraint_matrix [ i ] [ j ] ;

  constraint_free_vector [ i ] = eq_constraint_free_vector [ i ] ;
  }

{
size_t i0 = total_eq_constraints,
       j0 = total_base_variables ;

for ( size_t i = 0 ; i < total_leq_constraints ; ++ i )
  {
  for ( size_t j = 0 ; j < total_base_variables ; ++ j )
    constraint_matrix [ i0 + i ] [ j ] = leq_constraint_matrix [ i ] [ j ] ;

  constraint_matrix [ i0 + i ] [ j0 + i ] = 1 ;

  constraint_free_vector [ i0 + i ] = leq_constraint_free_vector [ i ] ;
  }
}

{
size_t i0 = total_eq_constraints + total_leq_constraints,
       j0 = total_base_variables + total_leq_constraints ;

for ( size_t i = 0 ; i < total_geq_constraints ; ++ i )
  {
  for ( size_t j = 0 ; j < total_base_variables ; ++ j )
    constraint_matrix [ i0 + i ] [ j ] = geq_constraint_matrix [ i ] [ j ] ;

  constraint_matrix [ i0 + i ] [ j0 + i ] = -1 ;

  constraint_free_vector [ i0 + i ] = geq_constraint_free_vector [ i ] ;
  }
}

vector < element > extended_result_vector ( total_variables, 0 ) ;

simplex_result
  status = exact_simplex ( extended_objective_function_vector,
                           constraint_matrix,
                           constraint_free_vector,
                           extended_result_vector,
                           result_value,
                           maximize ) ;

if ( status == simplex_result_ok )
  for ( size_t j = 0 ; j < total_base_variables ; ++ j )
    result_vector [ j ] = extended_result_vector [ j ] ;

return status ;
}



#endif
