// Copyright Ivan Stanojevic 2023.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __ALGORITHM_H

#define __ALGORITHM_H



#include <algorithm>

#include "type_traits.h"
#include "cstddef.h"
#include "utility.h"
#include "functional.h"



using std :: all_of ;
using std :: any_of ;
using std :: none_of ;

using std :: for_each ;
using std :: for_each_n ;

using std :: find ;
using std :: find_if ;
using std :: find_if_not ;
using std :: find_end ;
using std :: find_first_of ;
using std :: adjacent_find ;

using std :: count ;
using std :: count_if ;

using std :: mismatch ;

using std :: equal ;

using std :: is_permutation ;

using std :: search ;
using std :: search_n ;

using std :: copy ;
using std :: copy_n ;
using std :: copy_if ;
using std :: copy_backward ;

using std :: move ;
using std :: move_backward ;

using std :: swap_ranges ;
using std :: iter_swap ;

using std :: transform ;

using std :: replace ;
using std :: replace_if ;
using std :: replace_copy ;
using std :: replace_copy_if ;

using std :: fill ;
using std :: fill_n ;

using std :: generate ;
using std :: generate_n ;

using std :: remove ;
using std :: remove_if ;
using std :: remove_copy ;
using std :: remove_copy_if ;

using std :: unique ;
using std :: unique_copy ;

using std :: reverse ;
using std :: reverse_copy ;

using std :: rotate ;
using std :: rotate_copy ;

using std :: sample ;

using std :: shuffle ;

using std :: is_partitioned ;
using std :: partition ;
using std :: stable_partition ;
using std :: partition_copy ;
using std :: partition_point ;

using std :: sort ;
using std :: stable_sort ;
using std :: partial_sort ;
using std :: partial_sort_copy ;
using std :: is_sorted ;
using std :: is_sorted_until ;

using std :: nth_element ;

using std :: lower_bound ;
using std :: upper_bound ;
using std :: equal_range ;
using std :: binary_search ;

using std :: merge ;
using std :: inplace_merge ;

using std :: includes ;
using std :: set_union ;
using std :: set_intersection ;
using std :: set_difference ;
using std :: set_symmetric_difference ;

using std :: push_heap ;
using std :: pop_heap ;
using std :: make_heap ;
using std :: sort_heap ;
using std :: is_heap ;
using std :: is_heap_until ;

using std :: min ;
using std :: max ;
using std :: minmax ;
using std :: min_element ;
using std :: max_element ;
using std :: minmax_element ;

using std :: clamp ;

using std :: lexicographical_compare ;

using std :: next_permutation ;
using std :: prev_permutation ;



// *** EXTENSIONS ***


//

template < class InputIterator1, class InputIterator2, class Function >
InputIterator2 for_pairs ( InputIterator1 first1, InputIterator1 last1,
                           InputIterator2 first2,
                           Function fun )

{
while ( first1 != last1 )
  {
  fun ( * first1, * first2 ) ;
  ++ first1 ;
  ++ first2 ;
  }

return first2 ;
}


//

template < class InputIterator1, class InputIterator2,
           class Function, class Predicate >
enable_if_t
  < is_invocable_v < Predicate,
                     decltype ( * declval < InputIterator1 > ( ) ),
                     decltype ( * declval < InputIterator2 > ( ) ) >,
    InputIterator2 >
  for_pairs_asymmetric_if ( InputIterator1 first1, InputIterator1 last1,
                            InputIterator2 first2,
                            Function fun,
                            Predicate pred )

{
while ( first1 != last1 )
  {
  if ( pred ( * first1, * first2 ) )
    {
    fun ( * first1, * first2 ) ;
    ++ first2 ;
    }

  ++ first1 ;
  }

return first2 ;
}


//

template < class InputIterator1, class InputIterator2,
           class Function, class Predicate >
enable_if_t
  <       is_invocable_v < Predicate,
                           decltype ( * declval < InputIterator1 > ( ) ) >
    &&  ! is_invocable_v < Predicate,
                           decltype ( * declval < InputIterator1 > ( ) ),
                           decltype ( * declval < InputIterator2 > ( ) ) >,
    InputIterator2 >
  for_pairs_asymmetric_if ( InputIterator1 first1, InputIterator1 last1,
                            InputIterator2 first2,
                            Function fun,
                            Predicate pred )

{
while ( first1 != last1 )
  {
  if ( pred ( * first1 ) )
    {
    fun ( * first1, * first2 ) ;
    ++ first2 ;
    }

  ++ first1 ;
  }

return first2 ;
}


//

template < class InputIterator1, class InputIterator2,
           class Function, class PositionPredicate >
InputIterator2
  for_pairs_if_position ( InputIterator1 first1, InputIterator1 last1,
                          InputIterator2 first2,
                          Function fun,
                          PositionPredicate pred )

{
size_t n = 0 ;

while ( first1 != last1 )
  {
  if ( pred ( n ) )
    fun ( * first1, * first2 ) ;

  ++ first1 ;
  ++ first2 ;
  ++ n ;
  }

return first2 ;
}


//

template < class InputIterator1, class InputIterator2,
           class Function, class PositionPredicate >
InputIterator2
  for_pairs_asymmetric_if_position
    ( InputIterator1 first1, InputIterator1 last1,
      InputIterator2 first2,
      Function fun,
      PositionPredicate pred )

{
size_t n = 0 ;

while ( first1 != last1 )
  {
  if ( pred ( n ) )
    {
    fun ( * first1, * first2 ) ;
    ++ first2 ;
    }

  ++ first1 ;
  ++ n ;
  }

return first2 ;
}


//

template < class InputIterator, class OutputIterator, class PositionPredicate >
OutputIterator
  copy_if_position ( InputIterator first, InputIterator last,
                     OutputIterator result,
                     PositionPredicate pred )

{
size_t n = 0 ;

while ( first != last )
  {
  if ( pred ( n ) )
    {
    * result = * first ;
    ++ result ;
    }

  ++ first ;
  ++ n ;
  }

return result;
}


//

template < class ForwardIterator, class PositionPredicate >
ForwardIterator
  remove_if_position ( ForwardIterator first, ForwardIterator last,
                       PositionPredicate pred )

{
size_t n = 0 ;
ForwardIterator result = first ;

while ( first != last )
  {
  if ( ! pred ( n ) )
    {
    if ( result != first )
      * result = move ( * first ) ;

    ++ result ;
    }

  ++ first ;
  ++ n ;
  }

return result ;
}


//

template < class InputIterator, class OutputIterator,
           class UnaryOperation, class UnaryPredicate >
OutputIterator transform_if ( InputIterator first, InputIterator last,
                              OutputIterator result,
                              UnaryOperation op,
                              UnaryPredicate pred )

{
while ( first != last )
  {
  if ( pred ( * first ) )
    {
    * result = op ( * first ) ;
    ++ result ;
    }

  ++ first ;
  }

return result ;
}


//

template < class InputIterator1, class InputIterator2, class OutputIterator,
           class BinaryOperation, class BinaryPredicate >
OutputIterator transform_if ( InputIterator1 first1, InputIterator1 last1,
                              InputIterator2 first2,
                              OutputIterator result,
                              BinaryOperation op,
                              BinaryPredicate pred )

{
while ( first1 != last1 )
  {
  if ( pred ( * first1, * first2 ) )
    {
    * result = op ( * first1, * first2 ) ;
    ++ result ;
    }

  ++ first1 ;
  ++ first2 ;
  }

return result ;
}


//

template < class InputIterator, class OutputIterator,
           class UnaryOperation, class PositionPredicate >
OutputIterator
  transform_if_position ( InputIterator first, InputIterator last,
                          OutputIterator result,
                          UnaryOperation op,
                          PositionPredicate pred )

{
size_t n = 0 ;

while ( first != last )
  {
  if ( pred ( n ) )
    {
    * result = op ( * first ) ;
    ++ result ;
    }

  ++ first ;
  ++ n ;
  }

return result ;
}


//

template < class InputIterator1, class InputIterator2, class OutputIterator,
           class BinaryOperation, class PositionPredicate >
OutputIterator
  transform_if_position ( InputIterator1 first1, InputIterator1 last1,
                          InputIterator2 first2,
                          OutputIterator result,
                          BinaryOperation op,
                          PositionPredicate pred )

{
size_t n = 0 ;

while ( first1 != last1 )
  {
  if ( pred ( n ) )
    {
    * result = op ( * first1, * first2 ) ;
    ++ result ;
    }

  ++ first1 ;
  ++ first2 ;
  ++ n ;
  }

return result ;
}


//

template < class T, class Min, class Compare >
inline void limit_min ( T & x, const Min & min, Compare comp )

{
if ( comp ( x, min ) )
  x = min ;
}


//

template < class T, class Min >
inline void limit_min ( T & x, const Min & min )

{
limit_min ( x, min, less < T > ( ) ) ;
}


//

template < class T, class Max, class Compare >
inline void limit_max ( T & x, const Max & max, Compare comp )

{
if ( comp ( max, x ) )
  x = max ;
}


//

template < class T, class Max >
inline void limit_max ( T & x, const Max & max )

{
limit_max ( x, max, less < T > ( ) ) ;
}


//

template < class T, class Min, class Max, class Compare >
inline
  void limit_minmax ( T & x, const Min & min, const Max & max, Compare comp )

{
limit_min ( x, min, comp ) ;
limit_max ( x, max, comp ) ;
}


//

template < class T, class Min, class Max >
inline void limit_minmax ( T & x, const Min & min, const Max & max )

{
limit_minmax ( x, min, max, less < T > ( ) ) ;
}



#endif
