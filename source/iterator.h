// Copyright Ivan Stanojevic 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __ITERATOR_H

#define __ITERATOR_H



#include <iterator>

#include "cstddef.h"



// using std :: iterator_traits ;

using std :: iterator ;

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



// *** ITERATOR_TRAITS ***


//

template < class Iterator >
class iterator_traits

{
public:

  typedef typename Iterator :: iterator_category iterator_category ;
  typedef typename Iterator :: value_type value_type ;
  typedef typename Iterator :: difference_type difference_type ;
  typedef typename Iterator :: pointer pointer ;
  typedef typename Iterator :: reference reference ;
  typedef typename Iterator :: value_type assignment_type ;

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



#endif
