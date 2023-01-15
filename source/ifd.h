// Copyright Ivan Stanojevic 2022.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __IFD_H

#define __IFD_H



#include "cstddef.h"
#include "algorithm.h"

#include "funtr.h"
#include "numbase.h"



// *** INVARIANT_FACTOR_DECOMPOSITION ***


// post: g'' = diag ( invariant factors of g' )

template < class G >
void invariant_factor_decomposition ( G && g )

{
typedef
  typename    indexing_traits
                < typename    indexing_traits < remove_reference_t < G > >
                           :: value_type >
           :: value_type
  element ;

size_t m = sequence_size ( g ) ;

if ( m == 0 )
  return ;

size_t n = sequence_size ( g [ 0 ] ) ;

if ( n == 0 )
  return ;

#ifndef NDEBUG

for ( size_t i = 1 ; i < m ; ++ i )
  assert ( sequence_size ( g [ i ] ) == n ) ;

#endif

size_t d = min ( m, n ) ;

for ( size_t k = 0 ; k < d ; ++ k )
  {
  if ( g [ k ] [ k ] == 0 )
    {
    for ( size_t i = k ; i < m ; ++ i )
      for ( size_t j = k ; j < n ; ++ j )
        if ( g [ i ] [ j ] != 0 )
          {
          if ( i != k )
            for ( size_t l = k ; l < n ; ++ l )
              swap ( g [ k ] [ l ], g [ i ] [ l ] ) ;

          if ( j != k )
            for ( size_t l = k ; l < m ; ++ l )
              swap ( g [ l ] [ k ], g [ l ] [ j ] ) ;

          goto nonzero_placed ;
          }

    return ;
    }

  nonzero_placed:

  for ( size_t j = k + 1 ; ; ++ j )
    {
    check_start:

    for ( size_t i = k + 1 ; i < m ; ++ i )
      {
      element alpha = g [ k ] [ k ],
              beta  = g [ i ] [ k ] ;

      if ( beta % alpha != 0 )
        {
        element x, y, delta ;

        gcd_ext ( alpha, beta, x, y, delta ) ;

        element u = beta  / delta,
                v = alpha / delta ;

        for ( size_t l = k ; l < n ; ++ l )
          {
          auto t1 = g [ k ] [ l ],
               t2 = g [ i ] [ l ] ;

          g [ k ] [ l ] =   x * t1 + y * t2 ;
          g [ i ] [ l ] = - u * t1 + v * t2 ;
          }
        }
      }

    if ( j >= n )
      break ;

    {
    element alpha = g [ k ] [ k ],
            beta  = g [ k ] [ j ] ;

    if ( beta % alpha != 0 )
      {
      element x, y, delta ;

      gcd_ext ( alpha, beta, x, y, delta ) ;

      element u = beta  / delta,
              v = alpha / delta ;

      for ( size_t l = k ; l < m ; ++ l )
        {
        auto t1 = g [ l ] [ k ],
             t2 = g [ l ] [ j ] ;

        g [ l ] [ k ] =   x * t1 + y * t2 ;
        g [ l ] [ j ] = - u * t1 + v * t2 ;
        }

      goto check_start ;
      }
    }

    for ( size_t i = k + 1 ; i < m ; ++ i )
      if ( g [ i ] [ j ] % g [ k ] [ k ] != 0 )
        {
        if ( g [ k ] [ j ] != 0 )
          {
          auto r = g [ k ] [ j ] / g [ k ] [ k ] ;

          for ( size_t l = k ; l < m ; ++ l )
            g [ l ] [ j ] -= r * g [ l ] [ k ] ;
          }

        for ( size_t l = k ; l < m ; ++ l )
          g [ l ] [ k ] += g [ l ] [ j ] ;

        goto check_start ;
        }
    }

  for ( size_t i = k + 1 ; i < m ; ++ i )
    if ( g [ i ] [ k ] != 0 )
      {
      auto r = g [ i ] [ k ] / g [ k ] [ k ] ;

      for ( size_t l = k ; l < n ; ++ l )
        g [ i ] [ l ] -= r * g [ k ] [ l ] ;
      }

  for ( size_t j = k + 1 ; j < n ; ++ j )
    if ( g [ k ] [ j ] != 0 )
      {
      auto r = g [ k ] [ j ] / g [ k ] [ k ] ;

      for ( size_t l = k ; l < m ; ++ l )
        g [ l ] [ j ] -= r * g [ l ] [ k ] ;
      }
  }
}


// pre:  a : m * m
//       g : m * n
//       b : n * n

// post: g' = a * g'' * b
//       g'' = diag ( invariant factors of g' )
//       a, b are invertible

template < class A, class G, class B >
void invariant_factor_decomposition ( A && a, G && g, B && b )

{
typedef
  typename    indexing_traits
                < typename    indexing_traits < remove_reference_t < G > >
                           :: value_type >
           :: value_type
  element ;

size_t m = sequence_size ( g ) ;

if ( m == 0 )
  return ;

size_t n = sequence_size ( g [ 0 ] ) ;

if ( n == 0 )
  return ;

#ifndef NDEBUG

for ( size_t i = 1 ; i < m ; ++ i )
  assert ( sequence_size ( g [ i ] ) == n ) ;

#endif

assert ( sequence_size ( a ) == m ) ;

for ( size_t i = 0 ; i < m ; ++ i )
  {
  assert ( sequence_size ( a [ i ] ) == m ) ;

  for ( size_t j = 0 ; j < m ; ++ j )
    a [ i ] [ j ] = 0 ;

  a [ i ] [ i ] = 1 ;
  }

assert ( sequence_size ( b ) == n ) ;

for ( size_t i = 0 ; i < n ; ++ i )
  {
  assert ( sequence_size ( b [ i ] ) == n ) ;

  for ( size_t j = 0 ; j < n ; ++ j )
    b [ i ] [ j ] = 0 ;

  b [ i ] [ i ] = 1 ;
  }

size_t d = min ( m, n ) ;

for ( size_t k = 0 ; k < d ; ++ k )
  {
  if ( g [ k ] [ k ] == 0 )
    {
    for ( size_t i = k ; i < m ; ++ i )
      for ( size_t j = k ; j < n ; ++ j )
        if ( g [ i ] [ j ] != 0 )
          {
          if ( i != k )
            {
            for ( size_t l = k ; l < n ; ++ l )
              swap ( g [ k ] [ l ], g [ i ] [ l ] ) ;

            for ( size_t l = 0 ; l < m ; ++ l )
              swap ( a [ l ] [ k ], a [ l ] [ i ] ) ;
            }

          if ( j != k )
            {
            for ( size_t l = k ; l < m ; ++ l )
              swap ( g [ l ] [ k ], g [ l ] [ j ] ) ;

            for ( size_t l = 0 ; l < n ; ++ l )
              swap ( b [ k ] [ l ], b [ j ] [ l ] ) ;
            }

          goto nonzero_placed ;
          }

    return ;
    }

  nonzero_placed:

  for ( size_t j = k + 1 ; ; ++ j )
    {
    check_start:

    for ( size_t i = k + 1 ; i < m ; ++ i )
      {
      element alpha = g [ k ] [ k ],
              beta  = g [ i ] [ k ] ;

      if ( beta % alpha != 0 )
        {
        element x, y, delta ;

        gcd_ext ( alpha, beta, x, y, delta ) ;

        element u = beta  / delta,
                v = alpha / delta ;

        for ( size_t l = k ; l < n ; ++ l )
          {
          auto t1 = g [ k ] [ l ],
               t2 = g [ i ] [ l ] ;

          g [ k ] [ l ] =   x * t1 + y * t2 ;
          g [ i ] [ l ] = - u * t1 + v * t2 ;
          }

        for ( size_t l = 0 ; l < m ; ++ l )
          {
          auto t1 = a [ l ] [ k ],
               t2 = a [ l ] [ i ] ;

          a [ l ] [ k ] =   v * t1 + u * t2 ;
          a [ l ] [ i ] = - y * t1 + x * t2 ;
          }
        }
      }

    if ( j >= n )
      break ;

    {
    element alpha = g [ k ] [ k ],
            beta  = g [ k ] [ j ] ;

    if ( beta % alpha != 0 )
      {
      element x, y, delta ;

      gcd_ext ( alpha, beta, x, y, delta ) ;

      element u = beta  / delta,
              v = alpha / delta ;

      for ( size_t l = k ; l < m ; ++ l )
        {
        auto t1 = g [ l ] [ k ],
             t2 = g [ l ] [ j ] ;

        g [ l ] [ k ] =   x * t1 + y * t2 ;
        g [ l ] [ j ] = - u * t1 + v * t2 ;
        }

      for ( size_t l = 0 ; l < n ; ++ l )
        {
        auto t1 = b [ k ] [ l ],
             t2 = b [ j ] [ l ] ;

        b [ k ] [ l ] =   v * t1 + u * t2 ;
        b [ j ] [ l ] = - y * t1 + x * t2 ;
        }

      goto check_start ;
      }
    }

    for ( size_t i = k + 1 ; i < m ; ++ i )
      if ( g [ i ] [ j ] % g [ k ] [ k ] != 0 )
        {
        if ( g [ k ] [ j ] != 0 )
          {
          auto r = g [ k ] [ j ] / g [ k ] [ k ] ;

          for ( size_t l = k ; l < m ; ++ l )
            g [ l ] [ j ] -= r * g [ l ] [ k ] ;

          for ( size_t l = 0 ; l < n ; ++ l )
            b [ k ] [ l ] += r * b [ j ] [ l ] ;
          }

        for ( size_t l = k ; l < m ; ++ l )
          g [ l ] [ k ] += g [ l ] [ j ] ;

        for ( size_t l = 0 ; l < n ; ++ l )
          b [ j ] [ l ] -= b [ k ] [ l ] ;

        goto check_start ;
        }
    }

  for ( size_t i = k + 1 ; i < m ; ++ i )
    if ( g [ i ] [ k ] != 0 )
      {
      auto r = g [ i ] [ k ] / g [ k ] [ k ] ;

      for ( size_t l = k ; l < n ; ++ l )
        g [ i ] [ l ] -= r * g [ k ] [ l ] ;

      for ( size_t l = 0 ; l < m ; ++ l )
        a [ l ] [ k ] += r * a [ l ] [ i ] ;
      }

  for ( size_t j = k + 1 ; j < n ; ++ j )
    if ( g [ k ] [ j ] != 0 )
      {
      auto r = g [ k ] [ j ] / g [ k ] [ k ] ;

      for ( size_t l = k ; l < m ; ++ l )
        g [ l ] [ j ] -= r * g [ l ] [ k ] ;

      for ( size_t l = 0 ; l < n ; ++ l )
        b [ k ] [ l ] += r * b [ j ] [ l ] ;
      }
  }
}


// pre:  a     : m * m
//       a_inv : m * m
//       g     : m * n
//       b     : n * n
//       b_inv : n * n

// post: g' = a * g'' * b
//       g'' = diag ( invariant factors of g' )
//       a * a_inv = I
//       b * b_inv = I

template < class A, class AInv, class G, class B, class BInv >
void invariant_factor_decomposition
       ( A && a, AInv && a_inv, G && g, B && b, BInv && b_inv )

{
typedef
  typename    indexing_traits
                < typename    indexing_traits < remove_reference_t < G > >
                           :: value_type >
           :: value_type
  element ;

size_t m = sequence_size ( g ) ;

if ( m == 0 )
  return ;

size_t n = sequence_size ( g [ 0 ] ) ;

if ( n == 0 )
  return ;

#ifndef NDEBUG

for ( size_t i = 1 ; i < m ; ++ i )
  assert ( sequence_size ( g [ i ] ) == n ) ;

#endif

assert ( sequence_size ( a ) == m ) ;

for ( size_t i = 0 ; i < m ; ++ i )
  {
  assert ( sequence_size ( a [ i ] ) == m ) ;

  for ( size_t j = 0 ; j < m ; ++ j )
    a [ i ] [ j ] = 0 ;

  a [ i ] [ i ] = 1 ;
  }

assert ( sequence_size ( a_inv ) == m ) ;

for ( size_t i = 0 ; i < m ; ++ i )
  {
  assert ( sequence_size ( a_inv [ i ] ) == m ) ;

  for ( size_t j = 0 ; j < m ; ++ j )
    a_inv [ i ] [ j ] = 0 ;

  a_inv [ i ] [ i ] = 1 ;
  }

assert ( sequence_size ( b ) == n ) ;

for ( size_t i = 0 ; i < n ; ++ i )
  {
  assert ( sequence_size ( b [ i ] ) == n ) ;

  for ( size_t j = 0 ; j < n ; ++ j )
    b [ i ] [ j ] = 0 ;

  b [ i ] [ i ] = 1 ;
  }

assert ( sequence_size ( b_inv ) == n ) ;

for ( size_t i = 0 ; i < n ; ++ i )
  {
  assert ( sequence_size ( b_inv [ i ] ) == n ) ;

  for ( size_t j = 0 ; j < n ; ++ j )
    b_inv [ i ] [ j ] = 0 ;

  b_inv [ i ] [ i ] = 1 ;
  }

size_t d = min ( m, n ) ;

for ( size_t k = 0 ; k < d ; ++ k )
  {
  if ( g [ k ] [ k ] == 0 )
    {
    for ( size_t i = k ; i < m ; ++ i )
      for ( size_t j = k ; j < n ; ++ j )
        if ( g [ i ] [ j ] != 0 )
          {
          if ( i != k )
            {
            for ( size_t l = k ; l < n ; ++ l )
              swap ( g [ k ] [ l ], g [ i ] [ l ] ) ;

            for ( size_t l = 0 ; l < m ; ++ l )
              swap ( a [ l ] [ k ], a [ l ] [ i ] ) ;

            for ( size_t l = 0 ; l < m ; ++ l )
              swap ( a_inv [ k ] [ l ], a_inv [ i ] [ l ] ) ;
            }

          if ( j != k )
            {
            for ( size_t l = k ; l < m ; ++ l )
              swap ( g [ l ] [ k ], g [ l ] [ j ] ) ;

            for ( size_t l = 0 ; l < n ; ++ l )
              swap ( b [ k ] [ l ], b [ j ] [ l ] ) ;

            for ( size_t l = 0 ; l < n ; ++ l )
              swap ( b_inv [ l ] [ k ], b_inv [ l ] [ j ] ) ;
            }

          goto nonzero_placed ;
          }

    return ;
    }

  nonzero_placed:

  for ( size_t j = k + 1 ; ; ++ j )
    {
    check_start:

    for ( size_t i = k + 1 ; i < m ; ++ i )
      {
      element alpha = g [ k ] [ k ],
              beta  = g [ i ] [ k ] ;

      if ( beta % alpha != 0 )
        {
        element x, y, delta ;

        gcd_ext ( alpha, beta, x, y, delta ) ;

        element u = beta  / delta,
                v = alpha / delta ;

        for ( size_t l = k ; l < n ; ++ l )
          {
          auto t1 = g [ k ] [ l ],
               t2 = g [ i ] [ l ] ;

          g [ k ] [ l ] =   x * t1 + y * t2 ;
          g [ i ] [ l ] = - u * t1 + v * t2 ;
          }

        for ( size_t l = 0 ; l < m ; ++ l )
          {
          auto t1 = a [ l ] [ k ],
               t2 = a [ l ] [ i ] ;

          a [ l ] [ k ] =   v * t1 + u * t2 ;
          a [ l ] [ i ] = - y * t1 + x * t2 ;
          }

        for ( size_t l = 0 ; l < m ; ++ l )
          {
          auto t1 = a_inv [ k ] [ l ],
               t2 = a_inv [ i ] [ l ] ;

          a_inv [ k ] [ l ] =   x * t1 + y * t2 ;
          a_inv [ i ] [ l ] = - u * t1 + v * t2 ;
          }
        }
      }

    if ( j >= n )
      break ;

    {
    element alpha = g [ k ] [ k ],
            beta  = g [ k ] [ j ] ;

    if ( beta % alpha != 0 )
      {
      element x, y, delta ;

      gcd_ext ( alpha, beta, x, y, delta ) ;

      element u = beta  / delta,
              v = alpha / delta ;

      for ( size_t l = k ; l < m ; ++ l )
        {
        auto t1 = g [ l ] [ k ],
             t2 = g [ l ] [ j ] ;

        g [ l ] [ k ] =   x * t1 + y * t2 ;
        g [ l ] [ j ] = - u * t1 + v * t2 ;
        }

      for ( size_t l = 0 ; l < n ; ++ l )
        {
        auto t1 = b [ k ] [ l ],
             t2 = b [ j ] [ l ] ;

        b [ k ] [ l ] =   v * t1 + u * t2 ;
        b [ j ] [ l ] = - y * t1 + x * t2 ;
        }

      for ( size_t l = 0 ; l < n ; ++ l )
        {
        auto t1 = b_inv [ l ] [ k ],
             t2 = b_inv [ l ] [ j ] ;

        b_inv [ l ] [ k ] =   x * t1 + y * t2 ;
        b_inv [ l ] [ j ] = - u * t1 + v * t2 ;
        }

      goto check_start ;
      }
    }

    for ( size_t i = k + 1 ; i < m ; ++ i )
      if ( g [ i ] [ j ] % g [ k ] [ k ] != 0 )
        {
        if ( g [ k ] [ j ] != 0 )
          {
          auto r = g [ k ] [ j ] / g [ k ] [ k ] ;

          for ( size_t l = k ; l < m ; ++ l )
            g [ l ] [ j ] -= r * g [ l ] [ k ] ;

          for ( size_t l = 0 ; l < n ; ++ l )
            b [ k ] [ l ] += r * b [ j ] [ l ] ;

          for ( size_t l = 0 ; l < n ; ++ l )
            b_inv [ l ] [ j ] -= r * b_inv [ l ] [ k ] ;
          }

        for ( size_t l = k ; l < m ; ++ l )
          g [ l ] [ k ] += g [ l ] [ j ] ;

        for ( size_t l = 0 ; l < n ; ++ l )
          b [ j ] [ l ] -= b [ k ] [ l ] ;

        for ( size_t l = 0 ; l < n ; ++ l )
          b_inv [ l ] [ k ] += b_inv [ l ] [ j ] ;

        goto check_start ;
        }
    }

  for ( size_t i = k + 1 ; i < m ; ++ i )
    if ( g [ i ] [ k ] != 0 )
      {
      auto r = g [ i ] [ k ] / g [ k ] [ k ] ;

      for ( size_t l = k ; l < n ; ++ l )
        g [ i ] [ l ] -= r * g [ k ] [ l ] ;

      for ( size_t l = 0 ; l < m ; ++ l )
        a [ l ] [ k ] += r * a [ l ] [ i ] ;

      for ( size_t l = 0 ; l < m ; ++ l )
        a_inv [ i ] [ l ] -= r * a_inv [ k ] [ l ] ;
      }

  for ( size_t j = k + 1 ; j < n ; ++ j )
    if ( g [ k ] [ j ] != 0 )
      {
      auto r = g [ k ] [ j ] / g [ k ] [ k ] ;

      for ( size_t l = k ; l < m ; ++ l )
        g [ l ] [ j ] -= r * g [ l ] [ k ] ;

      for ( size_t l = 0 ; l < n ; ++ l )
        b [ k ] [ l ] += r * b [ j ] [ l ] ;

      for ( size_t l = 0 ; l < n ; ++ l )
        b_inv [ l ] [ j ] -= r * b_inv [ l ] [ k ] ;
      }
  }
}



#endif
