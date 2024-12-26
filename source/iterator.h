// Copyright Ivan Stanojevic 2024.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __ITERATOR_H

#define __ITERATOR_H



#include <iterator>

#include "cstddef.h"
#include "type_traits.h"



// using std :: iterator_traits ;

using std :: input_iterator_tag ;
using std :: output_iterator_tag ;
using std :: forward_iterator_tag ;
using std :: bidirectional_iterator_tag ;
using std :: random_access_iterator_tag ;

using std :: advance ;
using std :: distance ;
using std :: next ;
using std :: prev ;

using std :: reverse_iterator ;
using std :: make_reverse_iterator ;

using std :: back_insert_iterator ;
using std :: back_inserter ;
using std :: front_insert_iterator ;
using std :: front_inserter ;
using std :: insert_iterator ;
using std :: inserter ;

using std :: move_iterator ;
using std :: make_move_iterator ;

using std :: istream_iterator ;
using std :: ostream_iterator ;
using std :: istreambuf_iterator ;
using std :: ostreambuf_iterator ;

using std :: operator == ;
using std :: operator != ;
using std :: operator < ;
using std :: operator > ;
using std :: operator <= ;
using std :: operator >= ;

using std :: operator + ;
using std :: operator - ;

using std :: begin ;
using std :: end ;
using std :: cbegin ;
using std :: cend ;
using std :: rbegin ;
using std :: rend ;
using std :: crbegin ;
using std :: crend ;

using std :: size ;
using std :: empty ;
using std :: data ;

// using std :: iterator ;



// *** HAS_ITERATOR_CATEGORY_MEMBER_TYPE ***


template < class T >
class has_iterator_category_member_type

{
private:

  typedef const char ( & s1 ) [ 1 ] ;
  typedef const char ( & s2 ) [ 2 ] ;

  template < class U >
  static s1 test ( const typename U :: iterator_category * ) ;

  template < class >
  static s2 test ( ... ) ;

public:

   static constexpr bool value = sizeof ( test < T > ( nullptr ) ) == 1 ;

} ;


//

template < class T >
inline constexpr bool has_iterator_category_member_type_v =
                        has_iterator_category_member_type < T > :: value ;



// *** __ITERATOR_TRAITS_BASE ***


//

template < class T, bool IteratorCategoryExists >
class __iterator_traits_base ;


//

template < class T >
class __iterator_traits_base < T, true >

{
public:

  typedef typename T :: iterator_category iterator_category ;
  typedef typename T :: value_type value_type ;
  typedef typename T :: difference_type difference_type ;
  typedef typename T :: pointer pointer ;
  typedef typename T :: reference reference ;
  typedef typename T :: value_type assignment_type ;

} ;


//

template < class T >
class __iterator_traits_base < T, false >

{
} ;



// *** ITERATOR_TRAITS ***


//

template < class Iterator >
class iterator_traits :
  public __iterator_traits_base
           < Iterator,
             has_iterator_category_member_type_v < Iterator > >

{
} ;


//

template < class T >
class iterator_traits < T * >

{
public:

  typedef random_access_iterator_tag iterator_category ;
  typedef T value_type ;
  typedef ptrdiff_t difference_type ;
  typedef T * pointer ;
  typedef T & reference ;
  typedef T assignment_type ;

} ;


//

template < class T >
class iterator_traits < const T * >

{
public:

  typedef random_access_iterator_tag iterator_category ;
  typedef T value_type ;
  typedef ptrdiff_t difference_type ;
  typedef const T * pointer ;
  typedef const T & reference ;
  typedef T assignment_type ;

} ;


//

template < class Container >
class iterator_traits < back_insert_iterator < Container > >

{
public:

  typedef output_iterator_tag iterator_category ;
  typedef void value_type ;
  typedef void difference_type ;
  typedef void pointer ;
  typedef void reference ;
  typedef typename Container :: value_type assignment_type ;

} ;


//

template < class Container >
class iterator_traits < front_insert_iterator < Container > >

{
public:

  typedef output_iterator_tag iterator_category ;
  typedef void value_type ;
  typedef void difference_type ;
  typedef void pointer ;
  typedef void reference ;
  typedef typename Container :: value_type assignment_type ;

} ;


//

template < class Container >
class iterator_traits < insert_iterator < Container > >

{
public:

  typedef output_iterator_tag iterator_category ;
  typedef void value_type ;
  typedef void difference_type ;
  typedef void pointer ;
  typedef void reference ;
  typedef typename Container :: value_type assignment_type ;

} ;


//

template < class T, class CharT, class CharTraits >
class iterator_traits < ostream_iterator < T, CharT, CharTraits > >

{
public:

  typedef output_iterator_tag iterator_category ;
  typedef void value_type ;
  typedef void difference_type ;
  typedef void pointer ;
  typedef void reference ;
  typedef T assignment_type ;

} ;


//

template < class CharT, class CharTraits >
class iterator_traits < ostreambuf_iterator < CharT, CharTraits > >

{
public:

  typedef output_iterator_tag iterator_category ;
  typedef void value_type ;
  typedef void difference_type ;
  typedef void pointer ;
  typedef void reference ;
  typedef CharT assignment_type ;

} ;



// *** __IS_INPUT_ITERATOR_BASE ***


//

template < class T, bool IteratorCategoryExists >
class __is_input_iterator_base ;


//

template < class T >
class __is_input_iterator_base < T, true > :
  public integral_constant
           < bool,
             is_convertible_v
               < typename iterator_traits < T > :: iterator_category,
                 input_iterator_tag > >

{
} ;


//

template < class T >
class __is_input_iterator_base < T, false > : public false_type

{
} ;



// *** IS_INPUT_ITERATOR ***


template < class T >
class is_input_iterator :
  public __is_input_iterator_base
           < T,
             has_iterator_category_member_type_v < iterator_traits < T > > >

{
} ;


//

template < class  T >
inline constexpr bool is_input_iterator_v = is_input_iterator < T > :: value ;



#endif
