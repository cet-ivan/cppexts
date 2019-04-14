// Copyright Ivan Stanojevic 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __BITVECTOR_H

#define __BITVECTOR_H



#include "memory.h"
#include "cstddef.h"
#include "vector.h"
#include "iterator.h"
#include "initializer_list.h"
#include "cassert.h"
#include "utility.h"
#include "algorithm.h"

#include "numbase.h"
#include "bitref.h"



// *** FORWARD DECLARATIONS ***


template < class Word, class Allocator = allocator < Word > >
class basic_bit_vector ;

template < class Word, class Allocator >
size_t hamming_weight
         ( const basic_bit_vector < Word, Allocator > & x ) ;

template < class Word, class Allocator >
size_t hamming_distance
         ( const basic_bit_vector < Word, Allocator > & a,
           const basic_bit_vector < Word, Allocator > & b ) ;

template < class Word, class Allocator >
basic_bit_vector < Word, Allocator >
  operator & ( const basic_bit_vector < Word, Allocator > & a,
               const basic_bit_vector < Word, Allocator > & b ) ;

template < class Word, class Allocator >
basic_bit_vector < Word, Allocator >
  operator | ( const basic_bit_vector < Word, Allocator > & a,
               const basic_bit_vector < Word, Allocator > & b ) ;

template < class Word, class Allocator >
basic_bit_vector < Word, Allocator >
  operator ^ ( const basic_bit_vector < Word, Allocator > & a,
               const basic_bit_vector < Word, Allocator > & b ) ;

template < class Word, class Allocator >
basic_bit_vector < Word, Allocator >
  operator + ( const basic_bit_vector < Word, Allocator > & a,
               const basic_bit_vector < Word, Allocator > & b ) ;

template < class Word, class Allocator >
basic_bit_vector < Word, Allocator >
  operator - ( const basic_bit_vector < Word, Allocator > & a,
               const basic_bit_vector < Word, Allocator > & b ) ;

template < class Word, class Allocator >
bool operator * ( const basic_bit_vector < Word, Allocator > & a,
                  const basic_bit_vector < Word, Allocator > & b ) ;

template < class Word, class Allocator >
bool operator == ( const basic_bit_vector < Word, Allocator > & a,
                   const basic_bit_vector < Word, Allocator > & b ) ;

template < class Word, class Allocator >
bool operator < ( const basic_bit_vector < Word, Allocator > & a,
                  const basic_bit_vector < Word, Allocator > & b ) ;



// *** BASIC_BIT_VECTOR ***


template < class Word, class Allocator >
class basic_bit_vector

{
public:

  typedef Word word_type ;
  typedef Allocator allocator_type ;
  typedef size_t size_type ;
  typedef ptrdiff_t difference_type ;

  static const size_t word_bit_size = numeric_traits < Word > :: bit_size ;

  static const size_t log2_word_bit_size =
                        const_exponent ( word_bit_size ) - 1 ;

  static_assert ( word_bit_size == size_t ( 1 ) << log2_word_bit_size,
                  "Illegal word bit size." ) ;

private:

  static const size_t word_bit_size_1 = word_bit_size - 1 ;

  vector < Word > data_ ;
  size_t size_ ;

  void reset_trail ( )
    { size_t back_size_mod = size_ & word_bit_size_1 ;
      if ( back_size_mod > 0 )
        data_.back ( ) &= ( Word ( 1 ) << back_size_mod ) - 1 ; }

  void set_trail ( )
    { size_t back_size_mod = size_ & word_bit_size_1 ;
      if ( back_size_mod > 0 )
        data_.back ( ) |= Word ( -1 ) << back_size_mod ; }

  template < class InputIterator >
  void fill_from_range ( InputIterator first,
                         InputIterator last,
                         input_iterator_tag )
    { for ( ; first != last ; ++ first )
        push_back ( * first ) ; }

  template < class ForwardIterator >
  void fill_from_range ( ForwardIterator first,
                         ForwardIterator last,
                         forward_iterator_tag )
    { data_.reserve (    ( distance ( first, last ) + word_bit_size_1 )
                      >> log2_word_bit_size ) ;
      fill_from_range ( first, last, input_iterator_tag ( ) ) ; }

  template < class InputIterator >
  void fill_from_range ( InputIterator first, InputIterator last )
    { fill_from_range ( first,
                        last,
                        typename iterator_traits < InputIterator > ::
                                   iterator_category ( ) ) ; }

  void fill_from_list ( initializer_list < bool > l )
    { fill_from_range ( l.begin ( ), l.end ( ) ) ; }

  template < class CharT, class CharTraits >
  basic_ostream < CharT, CharTraits > &
    output_to ( basic_ostream < CharT, CharTraits > & o ) const ;

  template < class CharT, class CharTraits >
  basic_istream < CharT, CharTraits > &
    input_from ( basic_istream < CharT, CharTraits > & i ) ;

public:

  typedef bool value_type ;

  typedef bit_iterator < Word > iterator ;
  typedef const_bit_iterator < Word > const_iterator ;

  typedef reverse_bit_iterator < Word > reverse_iterator ;
  typedef const_reverse_bit_iterator < Word > const_reverse_iterator ;

  typedef bit_reference < Word > reference ;
  typedef const_bit_reference < Word > const_reference ;


  explicit basic_bit_vector ( const Allocator & a = Allocator ( ) ) :
    data_ ( a ),
    size_ ( 0 )
    { }

  explicit basic_bit_vector ( size_t n,
                              bool b = false,
                              const Allocator & a = Allocator ( ) ) :
    data_ ( ( n + word_bit_size_1 ) >> log2_word_bit_size,
            Word ( b ? -1 : 0 ),
            a ),
    size_ ( n )
    { reset_trail ( ) ; }

  template < class InputIterator >
  basic_bit_vector ( InputIterator first,
                     InputIterator last,
                     const Allocator & a = Allocator ( ) ) :
    data_ ( a ),
    size_ ( 0 )
    { fill_from_range ( first, last ) ; }

  basic_bit_vector ( const_iterator first,
                     const_iterator last,
                     const Allocator & a = Allocator ( ) ) :
    data_ ( a ),
    size_ ( 0 )
    { resize ( last - first ) ;
      copy ( first, last, begin ( ) ) ; }

  basic_bit_vector ( iterator first,
                     iterator last,
                     const Allocator & a = Allocator ( ) ) :
    data_ ( a ),
    size_ ( 0 )
    { resize ( last - first ) ;
      copy ( first, last, begin ( ) ) ; }

  basic_bit_vector ( initializer_list < bool > l,
                     const Allocator & a = Allocator ( ) ) :
    data_ ( a ),
    size_ ( 0 )
    { fill_from_list ( l ) ; }

  void assign ( size_t n, bool b )
    { data_.assign ( ( n + word_bit_size_1 ) >> log2_word_bit_size,
                     Word ( b ? -1 : 0 ) ) ;
      size_ = n ;
      reset_trail ( ) ; }

  template < class InputIterator >
  void assign ( InputIterator first, InputIterator last )
    { clear ( ) ;
      fill_from_range ( first, last ) ; }

  void assign ( initializer_list < bool > l )
    { clear ( ) ;
      fill_from_list ( l ) ; }

  Allocator get_allocator ( ) const
    { return data_.get_allocator ( ) ; }

  iterator begin ( ) noexcept
    { return iterator ( data_.data ( ), 0 ) ; }

  const_iterator begin ( ) const noexcept
    { return const_iterator ( data_.data ( ), 0 ) ; }

  iterator end ( ) noexcept
    { return iterator ( data_.data ( ), size_ ) ; }

  const_iterator end ( ) const noexcept
    { return const_iterator ( data_.data ( ), size_ ) ; }

  reverse_iterator rbegin ( ) noexcept
    { return reverse_iterator ( data_.data ( ), size_ - 1 ) ; }

  const_reverse_iterator rbegin ( ) const noexcept
    { return const_reverse_iterator ( data_.data ( ), size_ - 1 ) ; }

  reverse_iterator rend ( ) noexcept
    { return reverse_iterator ( data_.data ( ), -1 ) ; }

  const_reverse_iterator rend ( ) const noexcept
    { return const_reverse_iterator ( data_.data ( ), -1 ) ; }

  const_iterator cbegin ( ) const noexcept
    { return begin ( ) ; }

  const_iterator cend ( ) const noexcept
    { return end ( ) ; }

  const_reverse_iterator crbegin ( ) const noexcept
    { return rbegin ( ) ; }

  const_reverse_iterator crend ( ) const noexcept
    { return rend ( ) ; }

  size_t size ( ) const noexcept
    { return size_ ; }

  size_t max_size ( ) const noexcept
    { size_t dm = data_.max_size ( ) ;
      return   dm <= size_t ( -1 ) >> log2_word_bit_size
             ? dm << log2_word_bit_size
             : size_t ( -1 ) ; }

  void resize ( size_t n, bool b = false )
    { if ( b  &&  n > size_ )
        set_trail ( ) ;
      data_.resize ( ( n + word_bit_size_1 ) >> log2_word_bit_size,
                     Word ( b ? -1 : 0 ) ) ;
      size_ = n ;
      reset_trail ( ) ; }

  size_t capacity ( ) const noexcept
    { size_t dc = data_.capacity ( ) ;
      return   dc <= size_t ( -1 ) >> log2_word_bit_size
             ? dc << log2_word_bit_size
             : size_t ( -1 ) ; }

  bool empty ( ) const noexcept
    { return size_ == 0 ; }

  void reserve ( size_t n )
    { data_.reserve ( ( n + word_bit_size_1 ) >> log2_word_bit_size ) ; }

  void shrink_to_fit ( )
    { data_.shrink_to_fit ( ) ; }

  reference at ( size_t n ) noexcept
    { assert ( n < size_ ) ;
      return reference ( data_ [ n >> log2_word_bit_size ],
                         n & word_bit_size_1 ) ; }

  const_reference at ( size_t n ) const noexcept
    { assert ( n < size_ ) ;
      return const_reference ( data_ [ n >> log2_word_bit_size ],
                               n & word_bit_size_1 ) ; }

  reference operator [ ] ( size_t n ) noexcept
    { return at ( n ) ; }

  const_reference operator [ ] ( size_t n ) const noexcept
    { return at ( n ) ; }

  reference front ( ) noexcept
    { return at ( 0 ) ; }

  const_reference front ( ) const noexcept
    { return at ( 0 ) ; }

  reference back ( ) noexcept
    { return at ( size_ - 1 ) ; }

  const_reference back ( ) const noexcept
    { return at ( size_ - 1 ) ; }

  Word * data ( ) noexcept
    { return data_.data ( ) ; }

  const Word * data ( ) const noexcept
    { return data_.data ( ) ; }

  void push_back ( bool b )
    { data_.resize ( ( size_ >> log2_word_bit_size ) + 1, Word ( 0 ) ) ;
      if ( b )
        data_.back ( ) |= Word ( 1 ) << ( size_ & word_bit_size_1 ) ;
      ++ size_ ; }

  void emplace_back ( bool b )
    { push_back ( b ) ; }

  void append ( Word word, size_t bit_size ) ;

  void append ( const basic_bit_vector & b )
    { size_t old_size = size_ ;
      resize ( size_ + b.size_ ) ;
      copy ( b.begin ( ), b.end ( ), begin ( ) + old_size ) ; }

  void pop_back ( )
    { assert ( size_ > 0 ) ;
      -- size_ ;
      data_.resize ( ( size_ + word_bit_size_1 ) >> log2_word_bit_size,
                     Word ( 0 ) ) ;
      reset_trail ( ) ; }

  basic_bit_vector & reset ( )
    { fill ( data_.begin ( ), data_.end ( ), Word ( 0 ) ) ;
      return * this ; }

  basic_bit_vector & set ( )
    { fill ( data_.begin ( ), data_.end ( ), Word ( -1 ) ) ;
      reset_trail ( ) ;
      return * this ; }

  basic_bit_vector & flip ( )
    { for ( Word & w : data_ )
        w = ~ w ;
      reset_trail ( ) ;
      return * this ; }

  void clear ( ) noexcept
    { data_.clear ( ) ;
      size_ = 0 ; }

  void swap ( basic_bit_vector & x ) noexcept
    { data_.swap ( x.data_ ) ;
      :: swap ( size_, x.size_ ) ; }

  bool all ( ) const
    { size_t back_size_mod = size_ & word_bit_size_1 ;
      return   back_size_mod == 0
             ? all_of ( data_.begin ( ),
                        data_.end ( ),
                        [ ] ( Word x ) { return x == Word ( -1 ) ; } )
             :     all_of ( data_.begin ( ),
                            data_.end ( ) - 1,
                            [ ] ( Word x ) { return x == Word ( -1 ) ; } )
               &&  data_.back ( ) == ( Word ( 1 ) << back_size_mod ) - 1 ; }

  bool any ( ) const
    { return any_of ( data_.begin ( ), data_.end ( ),
                      [ ] ( Word x ) { return x != Word ( 0 ) ; } ) ; }

  bool none ( ) const
    { return ! any ( ) ; }

  friend size_t hamming_weight < > ( const basic_bit_vector & x ) ;

  friend size_t hamming_distance < > ( const basic_bit_vector & a,
                                       const basic_bit_vector & b ) ;

  basic_bit_vector operator ~ ( ) const
    { return basic_bit_vector ( * this ).flip ( ) ; }

  basic_bit_vector & operator &= ( const basic_bit_vector & b ) ;
  basic_bit_vector & operator |= ( const basic_bit_vector & b ) ;
  basic_bit_vector & operator ^= ( const basic_bit_vector & b ) ;

  friend basic_bit_vector operator & ( const basic_bit_vector & a,
                                       const basic_bit_vector & b )
    { return basic_bit_vector ( a ) &= b ; }

  friend basic_bit_vector operator | ( const basic_bit_vector & a,
                                       const basic_bit_vector & b )
    { return basic_bit_vector ( a ) |= b ; }

  friend basic_bit_vector operator ^ ( const basic_bit_vector & a,
                                       const basic_bit_vector & b )
    { return basic_bit_vector ( a ) ^= b ; }

  friend basic_bit_vector operator + ( const basic_bit_vector & a,
                                       const basic_bit_vector & b )
    { return a ^ b ; }

  friend basic_bit_vector operator - ( const basic_bit_vector & a,
                                       const basic_bit_vector & b )
    { return a ^ b ; }

  friend bool operator * < > ( const basic_bit_vector & a,
                               const basic_bit_vector & b ) ;

  friend bool operator == ( const basic_bit_vector & a,
                            const basic_bit_vector & b )
    { return a.data_ == b.data_  &&  a.size_ == b.size_ ; }

  friend bool operator < < > ( const basic_bit_vector & a,
                               const basic_bit_vector & b ) ;

  template < class CharT, class CharTraits >
  friend basic_ostream < CharT, CharTraits > &
    operator << ( basic_ostream < CharT, CharTraits > & o,
                  const basic_bit_vector & x )
    { return x.output_to ( o ) ; }

  template < class CharT, class CharTraits >
  friend basic_istream < CharT, CharTraits > &
    operator >> ( basic_istream < CharT, CharTraits > & i,
                  basic_bit_vector & x )
    { return x.input_from ( i ) ; }

} ;


//

template < class Word, class Allocator >
template < class CharT, class CharTraits >
basic_ostream < CharT, CharTraits > &
  basic_bit_vector < Word, Allocator > ::
    output_to ( basic_ostream < CharT, CharTraits > & o ) const

{
for ( size_t i = 0 ; i < size_ ; ++ i )
  o << (   (   ( data_ [ i >> log2_word_bit_size ] >> ( i & word_bit_size_1 ) )
             & 1 )
         ? CharT ( '1' )
         : CharT ( '0' ) ) ;

return o ;
}


//

template < class Word, class Allocator >
template < class CharT, class CharTraits >
basic_istream < CharT, CharTraits > &
  basic_bit_vector < Word, Allocator > ::
    input_from ( basic_istream < CharT, CharTraits > & i )

{
clear ( ) ;

ios_base :: fmtflags start_flags = i.flags ( ) ;
i.setf ( ios_base :: skipws ) ;

for ( ; ; )
  {
  CharT c ;

  i >> c ;
  if ( ! i.good ( ) )
    break ;

  if ( c == CharT ( '0' ) )
    {
    push_back ( false ) ;
    goto next_bit ;
    }

  if ( c == CharT ( '1' ) )
    {
    push_back ( true ) ;
    goto next_bit ;
    }

  i.putback ( c ) ;
  break ;

  next_bit:

  i.unsetf ( ios_base :: skipws ) ;
  }

i.flags ( start_flags ) ;
return i ;
}


//

template < class Word, class Allocator >
inline void basic_bit_vector < Word, Allocator > ::
              append ( Word word, size_t bit_size )

{
assert ( bit_size <= word_bit_size ) ;

if ( bit_size == 0 )
  return ;

size_t back_size_mod = size_ & word_bit_size_1 ;

if ( back_size_mod == 0 )
  data_.push_back ( word ) ;
else
  {
  data_.back ( ) |= word << back_size_mod ;

  size_t back_size_mod_c = word_bit_size - back_size_mod ;

  if ( bit_size > back_size_mod_c )
    data_.push_back ( unsigned_shift_right ( word, back_size_mod_c ) ) ;
  }

size_ += bit_size ;
reset_trail ( ) ;
}


//

template < class Word, class Allocator >
size_t hamming_weight ( const basic_bit_vector < Word, Allocator > & x )

{
size_t result = 0 ;

for ( Word w : x.data_ )
  result += :: hamming_weight ( w ) ;

return result ;
}


//

template < class Word, class Allocator >
size_t hamming_distance ( const basic_bit_vector < Word, Allocator > & a,
                          const basic_bit_vector < Word, Allocator > & b )

{
const basic_bit_vector < Word, Allocator > * ap ;
const basic_bit_vector < Word, Allocator > * bp ;

if ( a.data_.size ( ) < b.data_.size ( ) )
  {
  ap = & a ;
  bp = & b ;
  }
else
  {
  ap = & b ;
  bp = & a ;
  }

size_t result = 0 ;

for_each_pair
  ( ap -> data_.begin ( ), ap -> data_.end ( ),
    bp -> data_.begin ( ),
    [ & ] ( Word x, Word y ) { result += hamming_weight ( x ^ y ) ; } ) ;

for_each ( bp -> data_.begin ( ) + ap -> data_.size ( ), bp -> data_.end ( ),
           [ & ] ( Word x ) { result += hamming_weight ( x ) ; } ) ;

return result ;
}


//

template < class Word, class Allocator >
basic_bit_vector < Word, Allocator > &
  basic_bit_vector < Word, Allocator > ::
    operator &= ( const basic_bit_vector < Word, Allocator > & b )

{
if ( size_ < b.size_ )
  {
  transform ( data_.begin ( ), data_.end ( ),
              b.data_.begin ( ),
              data_.begin ( ),
              bit_and < Word > ( ) ) ;

  data_.insert ( data_.end ( ),
                 b.data_.size ( ) - data_.size ( ),
                 Word ( 0 ) ) ;

  size_ = b.size_ ;
  }
else
  {
  transform ( b.data_.begin ( ), b.data_.end ( ),
              data_.begin ( ),
              data_.begin ( ),
              bit_and < Word > ( ) ) ;

  fill ( data_.begin ( ) + b.data_.size ( ), data_.end ( ),
         Word ( 0 ) ) ;
  }

return * this ;
}


//

template < class Word, class Allocator >
basic_bit_vector < Word, Allocator > &
  basic_bit_vector < Word, Allocator > ::
    operator |= ( const basic_bit_vector < Word, Allocator > & b )

{
if ( size_ < b.size_ )
  {
  transform ( data_.begin ( ), data_.end ( ),
              b.data_.begin ( ),
              data_.begin ( ),
              bit_or < Word > ( ) ) ;

  data_.insert ( data_.end ( ),
                 b.data_.begin ( ) + data_.size ( ), b.data_.end ( ) ) ;

  size_ = b.size_ ;
  }
else
  transform ( b.data_.begin ( ), b.data_.end ( ),
              data_.begin ( ),
              data_.begin ( ),
              bit_or < Word > ( ) ) ;

return * this ;
}


//

template < class Word, class Allocator >
basic_bit_vector < Word, Allocator > &
  basic_bit_vector < Word, Allocator > ::
    operator ^= ( const basic_bit_vector < Word, Allocator > & b )

{
if ( size_ < b.size_ )
  {
  transform ( data_.begin ( ), data_.end ( ),
              b.data_.begin ( ),
              data_.begin ( ),
              bit_xor < Word > ( ) ) ;

  data_.insert ( data_.end ( ),
                 b.data_.begin ( ) + data_.size ( ), b.data_.end ( ) ) ;

  size_ = b.size_ ;
  }
else
  transform ( b.data_.begin ( ), b.data_.end ( ),
              data_.begin ( ),
              data_.begin ( ),
              bit_xor < Word > ( ) ) ;

return * this ;
}


//

template < class Word, class Allocator >
bool operator * ( const basic_bit_vector < Word, Allocator > & a,
                  const basic_bit_vector < Word, Allocator > & b )

{
const basic_bit_vector < Word, Allocator > * ap ;
const basic_bit_vector < Word, Allocator > * bp ;

if ( a.data_.size ( ) < b.data_.size ( ) )
  {
  ap = & a ;
  bp = & b ;
  }
else
  {
  ap = & b ;
  bp = & a ;
  }

size_t w = 0 ;

for_each_pair ( ap -> data_.begin ( ), ap -> data_.end ( ),
                bp -> data_.begin ( ),
                [ & ] ( Word x, Word y ) { w ^= hamming_weight ( x & y ) ; } ) ;

return ( w & 1 ) != 0 ;
}


//

template < class Word, class Allocator >
bool operator < ( const basic_bit_vector < Word, Allocator > & a,
                  const basic_bit_vector < Word, Allocator > & b )

{
auto iter_a = a.data_.begin ( ) ;

for ( auto iter_b = b.data_.begin ( ) ; iter_b != b.data_.end ( ) ; ++ iter_b )
  {
  if ( iter_a == a.data_.end ( ) )
    return true ;

  Word r_a = reverse ( * iter_a ),
       r_b = reverse ( * iter_b ) ;

  if ( r_a < r_b )
    return true ;

  if ( r_a > r_b )
    return false ;

  ++ iter_a ;
  }

return a.size_ < b.size_ ;
}


//

template < class Word, class Allocator >
inline void swap ( basic_bit_vector < Word, Allocator > & a,
                   basic_bit_vector < Word, Allocator > & b ) noexcept

{
a.swap ( b ) ;
}



// *** BIT_VECTOR ***


typedef basic_bit_vector < uint > bit_vector ;



#endif
