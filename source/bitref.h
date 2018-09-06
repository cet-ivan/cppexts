// Copyright Ivan Stanojevic 2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __BITREF_H

#define __BITREF_H



#include "cstddef.h"
#include "atomic.h"
#include "iterator.h"
#include "utility.h"
#include "cstdint.h"

#include "numbase.h"



// *** FORWARD DECLARATIONS ***


//

template < class Word >
class bit_reference ;


//

template < class Word >
class const_bit_reference ;


//

template < class Word >
class bit_iterator ;

template < class Word >
bit_iterator < Word > operator + ( const bit_iterator < Word > & a,
                                   ptrdiff_t b ) noexcept ;

template < class Word >
bit_iterator < Word > operator + ( ptrdiff_t a,
                                   const bit_iterator < Word > & b ) noexcept ;

template < class Word >
bit_iterator < Word > operator - ( const bit_iterator < Word > & a,
                                   ptrdiff_t b ) noexcept ;

template < class Word >
ptrdiff_t operator - ( const bit_iterator < Word > & a,
                       const bit_iterator < Word > & b ) noexcept ;

template < class Word >
bool operator == ( const bit_iterator < Word > & a,
                   const bit_iterator < Word > & b ) noexcept ;

template < class Word >
bool operator < ( const bit_iterator < Word > & a,
                  const bit_iterator < Word > & b ) noexcept ;


//

template < class Word >
class const_bit_iterator ;

template < class Word >
const_bit_iterator < Word >
  operator + ( const const_bit_iterator < Word > & a,
               ptrdiff_t b ) noexcept ;

template < class Word >
const_bit_iterator < Word >
  operator + ( ptrdiff_t a,
               const const_bit_iterator < Word > & b ) noexcept ;

template < class Word >
const_bit_iterator < Word >
  operator - ( const const_bit_iterator < Word > & a,
               ptrdiff_t b ) noexcept ;

template < class Word >
ptrdiff_t operator - ( const const_bit_iterator < Word > & a,
                       const const_bit_iterator < Word > & b ) noexcept ;

template < class Word >
bool operator == ( const const_bit_iterator < Word > & a,
                   const const_bit_iterator < Word > & b ) noexcept ;

template < class Word >
bool operator < ( const const_bit_iterator < Word > & a,
                  const const_bit_iterator < Word > & b ) noexcept ;


//

template < class Word >
class reverse_bit_iterator ;

template < class Word >
reverse_bit_iterator < Word >
  operator + ( const reverse_bit_iterator < Word > & a,
               ptrdiff_t b ) noexcept ;

template < class Word >
reverse_bit_iterator < Word >
  operator + ( ptrdiff_t a,
               const reverse_bit_iterator < Word > & b ) noexcept ;

template < class Word >
reverse_bit_iterator < Word >
  operator - ( const reverse_bit_iterator < Word > & a,
               ptrdiff_t b ) noexcept ;

template < class Word >
ptrdiff_t operator - ( const reverse_bit_iterator < Word > & a,
                       const reverse_bit_iterator < Word > & b ) noexcept ;

template < class Word >
bool operator == ( const reverse_bit_iterator < Word > & a,
                   const reverse_bit_iterator < Word > & b ) noexcept ;

template < class Word >
bool operator < ( const reverse_bit_iterator < Word > & a,
                  const reverse_bit_iterator < Word > & b ) noexcept ;


//

template < class Word >
class const_reverse_bit_iterator ;

template < class Word >
const_reverse_bit_iterator < Word >
  operator + ( const const_reverse_bit_iterator < Word > & a,
               ptrdiff_t b ) noexcept ;

template < class Word >
const_reverse_bit_iterator < Word >
  operator + ( ptrdiff_t a,
               const const_reverse_bit_iterator < Word > & b ) noexcept ;

template < class Word >
const_reverse_bit_iterator < Word >
  operator - ( const const_reverse_bit_iterator < Word > & a,
               ptrdiff_t b ) noexcept ;

template < class Word >
ptrdiff_t
  operator - ( const const_reverse_bit_iterator < Word > & a,
               const const_reverse_bit_iterator < Word > & b ) noexcept ;

template < class Word >
bool operator == ( const const_reverse_bit_iterator < Word > & a,
                   const const_reverse_bit_iterator < Word > & b ) noexcept ;

template < class Word >
bool operator < ( const const_reverse_bit_iterator < Word > & a,
                  const const_reverse_bit_iterator < Word > & b ) noexcept ;


//

template < class BitIterator >
BitIterator find_bit_1 ( BitIterator iter, size_t n ) ;

template < class BitIterator >
BitIterator find_bit_0 ( BitIterator iter, size_t n ) ;

template < class ReverseBitIterator >
ReverseBitIterator reverse_find_bit_1 ( ReverseBitIterator iter, size_t n ) ;

template < class ReverseBitIterator >
ReverseBitIterator reverse_find_bit_0 ( ReverseBitIterator iter, size_t n ) ;

template < class BitIterator >
bool valid_bit_iterator_range ( BitIterator first, BitIterator last ) ;



// *** BIT_REFERENCE ***


template < class Word >
class bit_reference

{
private:

  template < class Word2, class Allocator >
  friend class basic_bit_vector ;

  friend class const_bit_reference < Word > ;

  friend class bit_iterator < Word > ;
  friend class reverse_bit_iterator < Word > ;

  Word & word ;
  Word mask ;

  bit_reference ( Word & i_word, size_t bit_position ) noexcept :
    word ( i_word ),
    mask ( Word ( 1 ) << bit_position )
    { }

public:

  bit_reference ( const bit_reference & b ) = default ;

  operator bool ( ) const noexcept
    { return ( word & mask ) != 0 ; }

  void reset ( ) noexcept
    { atomic_fetch_and ( word, ~ mask ) ; }

  void non_atomic_reset ( ) noexcept
    { word &= ~ mask ; }

  void set ( ) noexcept
    { atomic_fetch_or ( word, mask ) ; }

  void non_atomic_set ( ) noexcept
    { word |= mask ; }

  void flip ( ) noexcept
    { atomic_fetch_xor ( word, mask ) ; }

  void non_atomic_flip ( ) noexcept
    { word ^= mask ; }

  void assign ( bool b ) noexcept
    { if ( b )
        set ( ) ;
      else
        reset ( ) ; }

  void non_atomic_assign ( bool b ) noexcept
    { if ( b )
        non_atomic_set ( ) ;
      else
        non_atomic_reset ( ) ; }

  bit_reference & operator = ( bool b ) noexcept
    { assign ( b ) ;
      return * this ; }

  bit_reference & operator = ( const bit_reference & b ) noexcept
    { return operator = ( static_cast < bool > ( b ) ) ; }

  bool operator ~ ( ) const noexcept
    { return ! static_cast < bool > ( * this ) ; }

  bit_reference & operator &= ( bool b ) noexcept
    { if ( ! b )
        reset ( ) ;
      return * this ; }

  bit_reference & operator |= ( bool b ) noexcept
    { if ( b )
        set ( ) ;
      return * this ; }

  bit_reference & operator ^= ( bool b ) noexcept
    { if ( b )
        flip ( ) ;
      return * this ; }

} ;


//

template < class Word1, class Word2 >
inline void swap ( bit_reference < Word1 > a,
                   bit_reference < Word2 > b ) noexcept

{
bool t = a ;
a = b ;
b = t ;
}


//

template < class Word >
inline void swap ( bit_reference < Word > a, bool & b ) noexcept

{
bool t = a ;
a = b ;
b = t ;
}


//

template < class Word >
inline void swap ( bool & a, bit_reference < Word > b ) noexcept

{
bool t = a ;
a = b ;
b = t ;
}



// *** CONST_BIT_REFERENCE ***


template < class Word >
class const_bit_reference

{
private:

  template < class Word2, class Allocator >
  friend class basic_bit_vector ;

  friend class const_bit_iterator < Word > ;
  friend class const_reverse_bit_iterator < Word > ;

  const Word & word ;
  Word mask ;

  const_bit_reference ( const Word & i_word, size_t bit_position ) noexcept :
    word ( i_word ),
    mask ( Word ( 1 ) << bit_position )
    { }

public:

  const_bit_reference ( const bit_reference < Word > & x ) noexcept :
    word ( x.word ),
    mask ( x.mask )
    { }

  operator bool ( ) const noexcept
    { return ( word & mask ) != 0 ; }

  bool operator ~ ( ) const noexcept
    { return ! static_cast < bool > ( * this ) ; }

} ;



// *** BIT_ITERATOR ***


template < class Word >
class bit_iterator

{
private:

  template < class Word2, class Allocator >
  friend class basic_bit_vector ;

  friend class const_bit_iterator < Word > ;
  friend class reverse_bit_iterator < Word > ;
  friend class const_reverse_bit_iterator < Word > ;

  friend bit_iterator find_bit_1 < > ( bit_iterator iter,
                                       size_t n ) ;

  friend bit_iterator find_bit_0 < > ( bit_iterator iter,
                                       size_t n ) ;

  friend bool valid_bit_iterator_range < > ( bit_iterator first,
                                             bit_iterator last ) ;

  typedef Word word_type ;

  static const size_t word_bit_size = numeric_traits < Word > :: bit_size ;
  static const size_t word_bit_size_1 = word_bit_size - 1 ;

  static const size_t log2_word_bit_size =
                        const_exponent ( word_bit_size ) - 1 ;

  static_assert ( word_bit_size == size_t ( 1 ) << log2_word_bit_size,
                  "Illegal word bit size." ) ;


  Word * word_position ;
  size_t bit_position ;

public:

  typedef ptrdiff_t difference_type ;
  typedef bool value_type ;
  typedef bit_iterator pointer ;
  typedef bit_reference < Word > reference ;
  typedef random_access_iterator_tag iterator_category ;

  explicit bit_iterator ( Word * i_word_position = nullptr ) noexcept :
    word_position ( i_word_position ),
    bit_position ( 0 )
    { }

  bit_iterator ( Word * i_word_position,
                 ptrdiff_t bit_offset ) noexcept :
    word_position ( i_word_position + ( bit_offset >> log2_word_bit_size ) ),
    bit_position ( bit_offset & word_bit_size_1 )
    { }

  explicit bit_iterator ( const reverse_bit_iterator < Word > & x ) noexcept :
    word_position ( x.word_position ),
    bit_position ( x.bit_position )
    { ++ * this ; }

  reference operator * ( ) const noexcept
    { return reference ( * word_position, bit_position ) ; }

  Word word ( size_t bit_size = word_bit_size ) const noexcept
    { assert ( bit_size <= word_bit_size ) ;
      Word w = unsigned_shift_right ( * word_position, bit_position ) ;
      if ( bit_position + bit_size > word_bit_size )
        w |= * ( word_position + 1 ) << ( word_bit_size - bit_position ) ;
      if ( bit_size < word_bit_size )
        w &= ( Word ( 1 ) << bit_size ) - 1 ;
      return w ; }

  bit_iterator & operator ++ ( ) noexcept
    { if ( bit_position == word_bit_size_1 )
        {
        ++ word_position ;
        bit_position = 0 ;
        }
      else
        ++ bit_position ;
      return * this ; }

  bit_iterator operator ++ ( int ) noexcept
    { bit_iterator t ( * this ) ;
      ++ * this ;
      return t ; }

  bit_iterator & operator -- ( ) noexcept
    { if ( bit_position == 0 )
        {
        -- word_position ;
        bit_position = word_bit_size_1 ;
        }
      else
        -- bit_position ;
      return * this ; }

  bit_iterator operator -- ( int ) noexcept
    { bit_iterator t ( * this ) ;
      -- * this ;
      return t ; }

  bit_iterator & operator += ( ptrdiff_t n ) noexcept
    { n += bit_position ;
      word_position += n >> log2_word_bit_size ;
      bit_position = n & word_bit_size_1 ;
      return * this ; }

  bit_iterator & operator -= ( ptrdiff_t n ) noexcept
    { return * this += - n ; }

  friend bit_iterator operator + ( const bit_iterator & a,
                                   ptrdiff_t b ) noexcept
    { return bit_iterator ( a ) += b ; }

  friend bit_iterator operator + ( ptrdiff_t a,
                                   const bit_iterator & b ) noexcept
    { return bit_iterator ( b ) += a ; }

  friend bit_iterator operator - ( const bit_iterator & a,
                                   ptrdiff_t b ) noexcept
    { return bit_iterator ( a ) -= b ; }

  friend ptrdiff_t operator - ( const bit_iterator & a,
                                const bit_iterator & b ) noexcept
    { return   ( ( a.word_position - b.word_position ) << log2_word_bit_size )
             + ( a.bit_position - b.bit_position ) ; }

  reference operator [ ] ( ptrdiff_t n ) const noexcept
    { return * ( * this + n ) ; }

  friend bool operator == ( const bit_iterator & a,
                            const bit_iterator & b ) noexcept
    { return     a.word_position == b.word_position
             &&  a.bit_position == b.bit_position ; }

  friend bool operator < ( const bit_iterator & a,
                           const bit_iterator & b ) noexcept
    { return     a.word_position < b.word_position
             ||  (     a.word_position == b.word_position
                   &&  a.bit_position < b.bit_position ) ; }

} ;



// *** CONST_BIT_ITERATOR ***


template < class Word >
class const_bit_iterator

{
private:

  template < class Word2, class Allocator >
  friend class basic_bit_vector ;

  friend class const_reverse_bit_iterator < Word > ;

  friend const_bit_iterator find_bit_1 < > ( const_bit_iterator iter,
                                             size_t n ) ;

  friend const_bit_iterator find_bit_0 < > ( const_bit_iterator iter,
                                             size_t n ) ;

  friend bool valid_bit_iterator_range < > ( const_bit_iterator first,
                                             const_bit_iterator last ) ;


  typedef Word word_type ;

  static const size_t word_bit_size = numeric_traits < Word > :: bit_size ;
  static const size_t word_bit_size_1 = word_bit_size - 1 ;

  static const size_t log2_word_bit_size =
                        const_exponent ( word_bit_size ) - 1 ;

  static_assert ( word_bit_size == size_t ( 1 ) << log2_word_bit_size,
                  "Illegal word bit size." ) ;


  const Word * word_position ;
  size_t bit_position ;

public:

  typedef ptrdiff_t difference_type ;
  typedef bool value_type ;
  typedef const_bit_iterator pointer ;
  typedef const_bit_reference < Word > reference ;
  typedef random_access_iterator_tag iterator_category ;

  explicit const_bit_iterator
             ( const Word * i_word_position = nullptr ) noexcept :
    word_position ( i_word_position ),
    bit_position ( 0 )
    { }

  const_bit_iterator ( const Word * i_word_position,
                       ptrdiff_t bit_offset ) noexcept :
    word_position ( i_word_position + ( bit_offset >> log2_word_bit_size ) ),
    bit_position ( bit_offset & word_bit_size_1 )
    { }

  const_bit_iterator ( const bit_iterator < Word > & x ) noexcept :
    word_position ( x.word_position ),
    bit_position ( x.bit_position )
    { }

  explicit const_bit_iterator
             ( const reverse_bit_iterator < Word > & x ) noexcept :
    word_position ( x.word_position ),
    bit_position ( x.bit_position )
    { ++ * this ; }

  explicit const_bit_iterator
             ( const const_reverse_bit_iterator < Word > & x ) noexcept :
    word_position ( x.word_position ),
    bit_position ( x.bit_position )
    { ++ * this ; }

  reference operator * ( ) const noexcept
    { return reference ( * word_position, bit_position ) ; }

  Word word ( size_t bit_size = word_bit_size ) const noexcept
    { assert ( bit_size <= word_bit_size ) ;
      Word w = unsigned_shift_right ( * word_position, bit_position ) ;
      if ( bit_position + bit_size > word_bit_size )
        w |= * ( word_position + 1 ) << ( word_bit_size - bit_position ) ;
      if ( bit_size < word_bit_size )
        w &= ( Word ( 1 ) << bit_size ) - 1 ;
      return w ; }

  const_bit_iterator & operator ++ ( ) noexcept
    { if ( bit_position == word_bit_size_1 )
        {
        ++ word_position ;
        bit_position = 0 ;
        }
      else
        ++ bit_position ;
      return * this ; }

  const_bit_iterator operator ++ ( int ) noexcept
    { const_bit_iterator t ( * this ) ;
      ++ * this ;
      return t ; }

  const_bit_iterator & operator -- ( ) noexcept
    { if ( bit_position == 0 )
        {
        -- word_position ;
        bit_position = word_bit_size_1 ;
        }
      else
        -- bit_position ;
      return * this ; }

  const_bit_iterator operator -- ( int ) noexcept
    { const_bit_iterator t ( * this ) ;
      -- * this ;
      return t ; }

  const_bit_iterator & operator += ( ptrdiff_t n ) noexcept
    { n += bit_position ;
      word_position += n >> log2_word_bit_size ;
      bit_position = n & word_bit_size_1 ;
      return * this ; }

  const_bit_iterator & operator -= ( ptrdiff_t n ) noexcept
    { return * this += - n ; }

  friend const_bit_iterator operator + ( const const_bit_iterator & a,
                                         ptrdiff_t b ) noexcept
    { return const_bit_iterator ( a ) += b ; }

  friend const_bit_iterator operator + ( ptrdiff_t a,
                                         const const_bit_iterator & b ) noexcept
    { return const_bit_iterator ( b ) += a ; }

  friend const_bit_iterator operator - ( const const_bit_iterator & a,
                                         ptrdiff_t b ) noexcept
    { return const_bit_iterator ( a ) -= b ; }

  friend ptrdiff_t operator - ( const const_bit_iterator & a,
                                const const_bit_iterator & b ) noexcept
    { return   ( ( a.word_position - b.word_position ) << log2_word_bit_size )
             + ( a.bit_position - b.bit_position ) ; }

  reference operator [ ] ( ptrdiff_t n ) const noexcept
    { return * ( * this + n ) ; }

  friend bool operator == ( const const_bit_iterator & a,
                            const const_bit_iterator & b ) noexcept
    { return     a.word_position == b.word_position
             &&  a.bit_position == b.bit_position ; }

  friend bool operator < ( const const_bit_iterator & a,
                           const const_bit_iterator & b ) noexcept
    { return     a.word_position < b.word_position
             ||  (     a.word_position == b.word_position
                   &&  a.bit_position < b.bit_position ) ; }

} ;



// *** REVERSE_BIT_ITERATOR ***


template < class Word >
class reverse_bit_iterator

{
private:

  template < class Word2, class Allocator >
  friend class basic_bit_vector ;

  friend class bit_iterator < Word > ;
  friend class const_bit_iterator < Word > ;
  friend class const_reverse_bit_iterator < Word > ;

  friend reverse_bit_iterator
           reverse_find_bit_1 < > ( reverse_bit_iterator iter,
                                    size_t n ) ;

  friend reverse_bit_iterator
           reverse_find_bit_0 < > ( reverse_bit_iterator iter,
                                    size_t n ) ;

  friend bool valid_bit_iterator_range < > ( reverse_bit_iterator first,
                                             reverse_bit_iterator last ) ;

  typedef Word word_type ;

  static const size_t word_bit_size = numeric_traits < Word > :: bit_size ;
  static const size_t word_bit_size_1 = word_bit_size - 1 ;

  static const size_t log2_word_bit_size =
                        const_exponent ( word_bit_size ) - 1 ;

  static_assert ( word_bit_size == size_t ( 1 ) << log2_word_bit_size,
                  "Illegal word bit size." ) ;


  Word * word_position ;
  size_t bit_position ;

public:

  typedef ptrdiff_t difference_type ;
  typedef bool value_type ;
  typedef reverse_bit_iterator pointer ;
  typedef bit_reference < Word > reference ;
  typedef random_access_iterator_tag iterator_category ;

  explicit reverse_bit_iterator ( Word * i_word_position = nullptr ) noexcept :
    word_position ( i_word_position - 1 ),
    bit_position ( word_bit_size_1 )
    { }

  reverse_bit_iterator ( Word * i_word_position,
                         ptrdiff_t bit_offset ) noexcept :
    word_position (   i_word_position
                    + ( ( bit_offset - 1 ) >> log2_word_bit_size ) ),
    bit_position ( ( bit_offset - 1 ) & word_bit_size_1 )
    { }

  explicit reverse_bit_iterator ( const bit_iterator < Word > & x ) noexcept :
    word_position ( x.word_position ),
    bit_position ( x.bit_position )
    { ++ * this ; }

  reference operator * ( ) const noexcept
    { return reference ( * word_position, bit_position ) ; }

  Word word ( size_t bit_size = word_bit_size ) const noexcept
    { assert ( bit_size <= word_bit_size ) ;
      Word w = * word_position << ( word_bit_size_1 - bit_position ) ;
      if ( bit_position + 1 < bit_size )
        w |= unsigned_shift_right
               ( * ( word_position - 1 ), bit_position + 1 ) ;
      w = reverse ( w ) ;
      if ( bit_size < word_bit_size )
        w &= ( Word ( 1 ) << bit_size ) - 1 ;
      return w ; }

  reverse_bit_iterator & operator ++ ( ) noexcept
    { if ( bit_position == 0 )
        {
        -- word_position ;
        bit_position = word_bit_size_1 ;
        }
      else
        -- bit_position ;
      return * this ; }

  reverse_bit_iterator operator ++ ( int ) noexcept
    { reverse_bit_iterator t ( * this ) ;
      ++ * this ;
      return t ; }

  reverse_bit_iterator & operator -- ( ) noexcept
    { if ( bit_position == word_bit_size_1 )
        {
        ++ word_position ;
        bit_position = 0 ;
        }
      else
        ++ bit_position ;
      return * this ; }

  reverse_bit_iterator operator -- ( int ) noexcept
    { reverse_bit_iterator t ( * this ) ;
      -- * this ;
      return t ; }

  reverse_bit_iterator & operator -= ( ptrdiff_t n ) noexcept
    { n += bit_position ;
      word_position += n >> log2_word_bit_size ;
      bit_position = n & word_bit_size_1 ;
      return * this ; }

  reverse_bit_iterator & operator += ( ptrdiff_t n ) noexcept
    { return * this -= - n ; }

  friend reverse_bit_iterator
           operator + ( const reverse_bit_iterator & a,
                        ptrdiff_t b ) noexcept
    { return reverse_bit_iterator ( a ) += b ; }

  friend reverse_bit_iterator
           operator + ( ptrdiff_t a,
                        const reverse_bit_iterator & b ) noexcept
    { return reverse_bit_iterator ( b ) += a ; }

  friend reverse_bit_iterator
           operator - ( const reverse_bit_iterator & a,
                        ptrdiff_t b ) noexcept
    { return reverse_bit_iterator ( a ) -= b ; }

  friend ptrdiff_t operator - ( const reverse_bit_iterator & a,
                                const reverse_bit_iterator & b ) noexcept
    { return   ( ( b.word_position - a.word_position ) << log2_word_bit_size )
             + ( b.bit_position - a.bit_position ) ; }

  reference operator [ ] ( ptrdiff_t n ) const noexcept
    { return * ( * this + n ) ; }

  friend bool operator == ( const reverse_bit_iterator & a,
                            const reverse_bit_iterator & b ) noexcept
    { return     a.word_position == b.word_position
             &&  a.bit_position == b.bit_position ; }

  friend bool operator < ( const reverse_bit_iterator & a,
                           const reverse_bit_iterator & b ) noexcept
    { return     a.word_position > b.word_position
             ||  (     a.word_position == b.word_position
                   &&  a.bit_position > b.bit_position ) ; }

} ;



// *** CONST_REVERSE_BIT_ITERATOR ***


template < class Word >
class const_reverse_bit_iterator

{
private:

  template < class Word2, class Allocator >
  friend class basic_bit_vector ;

  friend class const_bit_iterator < Word > ;

  friend const_reverse_bit_iterator
           reverse_find_bit_1 < > ( const_reverse_bit_iterator iter,
                                    size_t n ) ;

  friend const_reverse_bit_iterator
           reverse_find_bit_0 < > ( const_reverse_bit_iterator iter,
                                    size_t n ) ;

  friend bool valid_bit_iterator_range < > ( const_reverse_bit_iterator first,
                                             const_reverse_bit_iterator last ) ;

  typedef Word word_type ;

  static const size_t word_bit_size = numeric_traits < Word > :: bit_size ;
  static const size_t word_bit_size_1 = word_bit_size - 1 ;

  static const size_t log2_word_bit_size =
                        const_exponent ( word_bit_size ) - 1 ;

  static_assert ( word_bit_size == size_t ( 1 ) << log2_word_bit_size,
                  "Illegal word bit size." ) ;


  const Word * word_position ;
  size_t bit_position ;

public:

  typedef ptrdiff_t difference_type ;
  typedef bool value_type ;
  typedef const_reverse_bit_iterator pointer ;
  typedef const_bit_reference < Word > reference ;
  typedef random_access_iterator_tag iterator_category ;

  explicit const_reverse_bit_iterator
             ( const Word * i_word_position = nullptr ) noexcept :
    word_position ( i_word_position - 1 ),
    bit_position ( word_bit_size_1 )
    { }

  const_reverse_bit_iterator ( const Word * i_word_position,
                               ptrdiff_t bit_offset ) noexcept :
    word_position (   i_word_position
                    + ( ( bit_offset - 1 ) >> log2_word_bit_size ) ),
    bit_position ( ( bit_offset - 1 ) & word_bit_size_1 )
    { }

  const_reverse_bit_iterator
    ( const reverse_bit_iterator < Word > & x ) noexcept :
    word_position ( x.word_position ),
    bit_position ( x.bit_position )
    { }

  explicit const_reverse_bit_iterator
             ( const bit_iterator < Word > & x ) noexcept :
    word_position ( x.word_position ),
    bit_position ( x.bit_position )
    { ++ * this ; }

  explicit const_reverse_bit_iterator
             ( const const_bit_iterator < Word > & x ) noexcept :
    word_position ( x.word_position ),
    bit_position ( x.bit_position )
    { ++ * this ; }

  reference operator * ( ) const noexcept
    { return reference ( * word_position, bit_position ) ; }

  Word word ( size_t bit_size = word_bit_size ) const noexcept
    { assert ( bit_size <= word_bit_size ) ;
      Word w = * word_position << ( word_bit_size_1 - bit_position ) ;
      if ( bit_position + 1 < bit_size )
        w |= unsigned_shift_right
               ( * ( word_position - 1 ), bit_position + 1 ) ;
      w = reverse ( w ) ;
      if ( bit_size < word_bit_size )
        w &= ( Word ( 1 ) << bit_size ) - 1 ;
      return w ; }

  const_reverse_bit_iterator & operator ++ ( ) noexcept
    { if ( bit_position == 0 )
        {
        -- word_position ;
        bit_position = word_bit_size_1 ;
        }
      else
        -- bit_position ;
      return * this ; }

  const_reverse_bit_iterator operator ++ ( int ) noexcept
    { const_reverse_bit_iterator t ( * this ) ;
      ++ * this ;
      return t ; }

  const_reverse_bit_iterator & operator -- ( ) noexcept
    { if ( bit_position == word_bit_size_1 )
        {
        ++ word_position ;
        bit_position = 0 ;
        }
      else
        ++ bit_position ;
      return * this ; }

  const_reverse_bit_iterator operator -- ( int ) noexcept
    { const_reverse_bit_iterator t ( * this ) ;
      -- * this ;
      return t ; }

  const_reverse_bit_iterator & operator -= ( ptrdiff_t n ) noexcept
    { n += bit_position ;
      word_position += n >> log2_word_bit_size ;
      bit_position = n & word_bit_size_1 ;
      return * this ; }

  const_reverse_bit_iterator & operator += ( ptrdiff_t n ) noexcept
    { return * this -= - n ; }

  friend const_reverse_bit_iterator
           operator + ( const const_reverse_bit_iterator & a,
                        ptrdiff_t b ) noexcept
    { return const_reverse_bit_iterator ( a ) += b ; }

  friend const_reverse_bit_iterator
           operator + ( ptrdiff_t a,
                        const const_reverse_bit_iterator & b ) noexcept
    { return const_reverse_bit_iterator ( b ) += a ; }

  friend const_reverse_bit_iterator
           operator - ( const const_reverse_bit_iterator & a,
                        ptrdiff_t b ) noexcept
    { return const_reverse_bit_iterator ( a ) -= b ; }

  friend ptrdiff_t operator - ( const const_reverse_bit_iterator & a,
                                const const_reverse_bit_iterator & b ) noexcept
    { return   ( ( b.word_position - a.word_position ) << log2_word_bit_size )
             + ( b.bit_position - a.bit_position ) ; }

  reference operator [ ] ( ptrdiff_t n ) const noexcept
    { return * ( * this + n ) ; }

  friend bool operator == ( const const_reverse_bit_iterator & a,
                            const const_reverse_bit_iterator & b ) noexcept
    { return     a.word_position == b.word_position
             &&  a.bit_position == b.bit_position ; }

  friend bool operator < ( const const_reverse_bit_iterator & a,
                           const const_reverse_bit_iterator & b ) noexcept
    { return     a.word_position > b.word_position
             ||  (     a.word_position == b.word_position
                   &&  a.bit_position > b.bit_position ) ; }

} ;



// *** REVERSE ITERATOR HELPERS ***


//

template < class Word >
inline reverse_bit_iterator < Word >
         make_reverse_iterator ( const bit_iterator < Word > & x )

{
return reverse_bit_iterator < Word > ( x ) ;
}


//

template < class Word >
inline bit_iterator < Word >
         make_reverse_iterator ( const reverse_bit_iterator < Word > & x )

{
return bit_iterator < Word > ( x ) ;
}


//

template < class Word >
inline const_reverse_bit_iterator < Word >
         make_reverse_iterator ( const const_bit_iterator < Word > & x )

{
return const_reverse_bit_iterator < Word > ( x ) ;
}


//

template < class Word >
inline const_bit_iterator < Word >
         make_reverse_iterator ( const const_reverse_bit_iterator < Word > & x )

{
return const_bit_iterator < Word > ( x ) ;
}



// *** GLOBALS ***


// pre: w != 0

template < class Word >
inline size_t raw_find_bit_1 ( Word w )

{
for ( size_t i = 0 ; ; ++ i )
  if ( ( w >> i ) & 1 )
    return i ;
}


//

template < class Word >
inline size_t find_bit_1 ( Word w )

{
return w == 0 ? numeric_traits < Word > :: bit_size
              : raw_find_bit_1 ( w ) ;
}


// pre w != -1

template < class Word >
inline size_t raw_find_bit_0 ( Word w )

{
for ( size_t i = 0 ; ; ++ i )
  if ( ! ( ( w >> i ) & 1 ) )
    return i ;
}


//

template < class Word >
inline size_t find_bit_0 ( Word w )

{
return w == -1 ? numeric_traits < Word > :: bit_size
               : raw_find_bit_0 ( w ) ;
}


// pre w != 0

template < class Word >
inline size_t raw_find_last_bit_1 ( Word w )

{
for ( size_t i = numeric_traits < Word > :: bit_size - 1 ; ; -- i )
  if ( ( w >> i ) & 1 )
    return i ;
}


//

template < class Word >
inline size_t find_last_bit_1 ( Word w )

{
return w == -1 ? -1
               : raw_find_last_bit_1 ( w ) ;
}


// pre w != 0

template < class Word >
inline size_t raw_reverse_find_bit_1 ( Word w )

{
return numeric_traits < Word > :: bit_size - 1 - raw_find_last_bit_1 ( w ) ;
}


//

template < class Word >
inline size_t reverse_find_bit_1 ( Word w )

{
return w == 0 ? numeric_traits < Word > :: bit_size
              : raw_reverse_find_bit_1 ( w ) ;
}


// pre w != -1

template < class Word >
inline size_t raw_find_last_bit_0 ( Word w )

{
for ( size_t i = numeric_traits < Word > :: bit_size - 1 ; ; -- i )
  if ( ! ( ( w >> i ) & 1 ) )
    return i ;
}


//

template < class Word >
inline size_t find_last_bit_0 ( Word w )

{
return w == -1 ? -1
               : raw_find_last_bit_0 ( w ) ;
}


// pre w != -1

template < class Word >
inline size_t raw_reverse_find_bit_0 ( Word w )

{
return numeric_traits < Word > :: bit_size - 1 - raw_find_last_bit_0 ( w ) ;
}


//

template < class Word >
inline size_t reverse_find_bit_0 ( Word w )

{
return w == -1 ? numeric_traits < Word > :: bit_size
               : raw_reverse_find_bit_0 ( w ) ;
}


//

template < class BitIterator >
BitIterator find_bit_1 ( BitIterator iter, size_t n )

{
typedef typename BitIterator :: word_type word_type ;

if ( n == 0 )
  return iter ;

if ( iter.bit_position > 0 )
  {
  size_t relevant_bits =
           min ( BitIterator :: word_bit_size - iter.bit_position, n ) ;

  word_type w =   ( * iter.word_position >> iter.bit_position )
                & ( ( word_type ( 1 ) << relevant_bits ) - 1 ) ;

  if ( w )
    return iter + raw_find_bit_1 ( w ) ;

  if ( n == relevant_bits )
    return iter + n ;

  n -= relevant_bits ;

  ++ iter.word_position ;
  }

while ( n >= BitIterator :: word_bit_size )
  {
  if ( * iter.word_position )
    return BitIterator ( iter.word_position,
                         raw_find_bit_1 ( * iter.word_position ) ) ;

  n -= BitIterator :: word_bit_size ;

  ++ iter.word_position ;
  }

if ( n > 0 )
  {
  word_type w = * iter.word_position & ( ( word_type ( 1 ) << n ) - 1 ) ;

  if ( w )
    return BitIterator ( iter.word_position, raw_find_bit_1 ( w ) ) ;
  }

return BitIterator ( iter.word_position, n ) ;
}


//

template < class BitIterator >
BitIterator find_bit_0 ( BitIterator iter, size_t n )

{
typedef typename BitIterator :: word_type word_type ;

if ( n == 0 )
  return iter ;

if ( iter.bit_position > 0 )
  {
  size_t relevant_bits =
           min ( BitIterator :: word_bit_size - iter.bit_position, n ) ;

  word_type w =   ( * iter.word_position >> iter.bit_position )
                | ( word_type ( -1 ) << relevant_bits ) ;

  if ( w != -1 )
    return iter + raw_find_bit_0 ( w ) ;

  if ( n == relevant_bits )
    return iter + n ;

  n -= relevant_bits ;

  ++ iter.word_position ;
  }

while ( n >= BitIterator :: word_bit_size )
  {
  if ( * iter.word_position != -1 )
    return BitIterator ( iter.word_position,
                         raw_find_bit_0 ( * iter.word_position ) ) ;

  n -= BitIterator :: word_bit_size ;

  ++ iter.word_position ;
  }

if ( n > 0 )
  {
  word_type w = * iter.word_position | ( word_type ( -1 ) << n ) ;

  if ( w != -1 )
    return BitIterator ( iter.word_position, raw_find_bit_0 ( w ) ) ;
  }

return BitIterator ( iter.word_position, n ) ;
}


//

template < class ReverseBitIterator >
ReverseBitIterator reverse_find_bit_1 ( ReverseBitIterator iter, size_t n )

{
typedef typename ReverseBitIterator :: word_type word_type ;

if ( n == 0 )
  return iter ;

if ( iter.bit_position < ReverseBitIterator :: word_bit_size_1 )
  {
  size_t relevant_bits = min ( iter.bit_position + 1, n ) ;

  word_type
    w =   (    * iter.word_position
            << ( ReverseBitIterator :: word_bit_size_1 - iter.bit_position ) )
        & (    word_type ( -1 )
            << ( ReverseBitIterator :: word_bit_size - relevant_bits ) ) ;

  if ( w )
    return iter + raw_reverse_find_bit_1 ( w ) ;

  if ( n == relevant_bits )
    return iter + n ;

  n -= relevant_bits ;

  -- iter.word_position ;
  }

while ( n >= ReverseBitIterator :: word_bit_size )
  {
  if ( * iter.word_position )
    return ReverseBitIterator ( iter.word_position,
                                raw_find_last_bit_1 ( * iter.word_position ) ) ;

  n -= ReverseBitIterator :: word_bit_size ;

  -- iter.word_position ;
  }

if ( n > 0 )
  {
  word_type
    w =   * iter.word_position
        & ( word_type ( -1 ) << ( ReverseBitIterator :: word_bit_size - n ) ) ;

  if ( w )
    return ReverseBitIterator ( iter.word_position,
                                raw_find_last_bit_1 ( w ) ) ;
  }

return ReverseBitIterator ( iter.word_position, n ) ;
}


//

template < class ReverseBitIterator >
ReverseBitIterator reverse_find_bit_0 ( ReverseBitIterator iter, size_t n )

{
typedef typename ReverseBitIterator :: word_type word_type ;

if ( n == 0 )
  return iter ;

if ( iter.bit_position < ReverseBitIterator :: word_bit_size_1 )
  {
  size_t relevant_bits = min ( iter.bit_position + 1, n ) ;

  word_type
    w =   (    * iter.word_position
            << ( ReverseBitIterator :: word_bit_size_1 - iter.bit_position ) )
        | (   (    word_type ( 1 )
                << ( ReverseBitIterator :: word_bit_size - relevant_bits ) )
            - 1 ) ;

  if ( w != -1 )
    return iter + raw_reverse_find_bit_0 ( w ) ;

  if ( n == relevant_bits )
    return iter + n ;

  n -= relevant_bits ;

  -- iter.word_position ;
  }

while ( n >= ReverseBitIterator :: word_bit_size )
  {
  if ( * iter.word_position != -1 )
    return ReverseBitIterator ( iter.word_position,
                                raw_find_last_bit_1 ( * iter.word_position ) ) ;

  n -= ReverseBitIterator :: word_bit_size ;

  -- iter.word_position ;
  }

if ( n > 0 )
  {
  word_type w =   * iter.word_position
                | ( (    word_type ( 1 )
                      << ( ReverseBitIterator :: word_bit_size - n ) ) - 1 ) ;

  if ( w != -1 )
    return ReverseBitIterator ( iter.word_position,
                                raw_find_last_bit_0 ( w ) ) ;
  }

return ReverseBitIterator ( iter.word_position, n ) ;
}


//

template < class BitIterator >
inline bool valid_bit_iterator_range ( BitIterator first, BitIterator last )

{
return        (   reinterpret_cast < uintptr_t > ( first.word_position )
                & ( BitIterator :: word_bit_size_1 >> 3 ) )
           == (   reinterpret_cast < uintptr_t > ( last.word_position )
                & ( BitIterator :: word_bit_size_1 >> 3 ) )
       &&  first <= last ;
}


//

template < class BitIterator >
inline BitIterator find_bit ( const BitIterator & first,
                              const BitIterator & last,
                              bool b )

{
assert ( valid_bit_iterator_range ( first, last ) ) ;
ptrdiff_t n = last - first ;
return b ? find_bit_1 ( first, n ) : find_bit_0 ( first, n ) ;
}


//

template < class Word, class T >
inline bit_iterator < Word >
         find ( const bit_iterator < Word > & first,
                const bit_iterator < Word > & last,
                T b )

{
return find_bit ( first, last, b ) ;
}


//

template < class Word, class T >
inline const_bit_iterator < Word >
         find ( const const_bit_iterator < Word > & first,
                const const_bit_iterator < Word > & last,
                T b )

{
return find_bit ( first, last, b ) ;
}


//

template < class ReverseBitIterator >
inline ReverseBitIterator reverse_find_bit ( const ReverseBitIterator & first,
                                             const ReverseBitIterator & last,
                                             bool b )

{
assert ( valid_bit_iterator_range ( first, last ) ) ;
ptrdiff_t n = last - first ;
return b ? reverse_find_bit_1 ( first, n ) : reverse_find_bit_0 ( first, n ) ;
}


//

template < class Word, class T >
inline reverse_bit_iterator < Word >
         find ( const reverse_bit_iterator < Word > & first,
                const reverse_bit_iterator < Word > & last,
                T b )

{
return reverse_find_bit ( first, last, b ) ;
}


//

template < class Word, class T >
inline const_reverse_bit_iterator < Word >
         find ( const const_reverse_bit_iterator < Word > & first,
                const const_reverse_bit_iterator < Word > & last,
                T b )

{
return reverse_find_bit ( first, last, b ) ;
}



#endif
