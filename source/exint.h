// Copyright Ivan Stanojevic 2021.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __EXINT_H

#define __EXINT_H



#include "memory.h"
#include "vector.h"
#include "functional.h"
#include "utility.h"
#include "algorithm.h"
#include "new.h"
#include "cmath.h"
#include "ios.h"
#include "istream.h"
#include "ostream.h"
#include "cassert.h"

#include "numbase.h"
#include "rnd.h"
#include "typeconv.h"



// *** FORWARD DECLARATIONS ***


template
  < class T,
    class Allocator =
            allocator < typename numeric_traits < T > :: unsigned_type > >
class basic_exint ;

template < class T, class Allocator >
basic_exint < T, Allocator >
  operator + ( const basic_exint < T, Allocator > & a,
               const basic_exint < T, Allocator > & b ) ;

template < class T, class Allocator >
basic_exint < T, Allocator >
  operator - ( const basic_exint < T, Allocator > & a,
               const basic_exint < T, Allocator > & b ) ;

template < class T, class Allocator >
basic_exint < T, Allocator >
  operator * ( const basic_exint < T, Allocator > & a,
               const basic_exint < T, Allocator > & b ) ;

template < class T, class Allocator >
void divmod ( const basic_exint < T, Allocator > & a,
              const basic_exint < T, Allocator > & b,
              basic_exint < T, Allocator > & q,
              basic_exint < T, Allocator > & r ) ;

template < class T, class Allocator >
basic_exint < T, Allocator >
  operator / ( const basic_exint < T, Allocator > & a,
               const basic_exint < T, Allocator > & b ) ;

template < class T, class Allocator >
basic_exint < T, Allocator >
  operator % ( const basic_exint < T, Allocator > & a,
               const basic_exint < T, Allocator > & b ) ;

template < class T, class Allocator >
basic_exint < T, Allocator >
  operator & ( const basic_exint < T, Allocator > & a,
               const basic_exint < T, Allocator > & b ) ;

template < class T, class Allocator >
basic_exint < T, Allocator >
  operator | ( const basic_exint < T, Allocator > & a,
               const basic_exint < T, Allocator > & b ) ;

template < class T, class Allocator >
basic_exint < T, Allocator >
  operator ^ ( const basic_exint < T, Allocator > & a,
               const basic_exint < T, Allocator > & b ) ;

template < class T, class Allocator >
bool operator == ( const basic_exint < T, Allocator > & a,
                   const basic_exint < T, Allocator > & b ) ;

template < class T, class Allocator >
bool operator < ( const basic_exint < T, Allocator > & a,
                  const basic_exint < T, Allocator > & b ) ;

template < class T, class Allocator >
void swap ( basic_exint < T, Allocator > & a,
            basic_exint < T, Allocator > & b ) ;

template < class T, class Allocator >
bool is_negative ( const basic_exint < T, Allocator > & x ) ;

template < class T, class Allocator >
sint exponent ( const basic_exint < T, Allocator > & x ) ;

template < class T, class Allocator >
void normalize_gcd ( basic_exint < T, Allocator > & gcd ) ;

template < class T, class Allocator >
void normalize_gcd_ext ( basic_exint < T, Allocator > & c,
                         basic_exint < T, Allocator > & d,
                         basic_exint < T, Allocator > & gcd ) ;

template < class T, class Allocator >
void normalize_fraction ( basic_exint < T, Allocator > & a,
                          basic_exint < T, Allocator > & b ) ;



// *** BASIC_EXINT ***


template < class T, class Allocator >
class basic_exint

{
public:

  typedef typename numeric_traits < T > :: signed_type signed_digit_type ;
  typedef typename numeric_traits < T > :: unsigned_type unsigned_digit_type ;

  static const sint
    digit_bit_size = numeric_traits < unsigned_digit_type > :: bit_size ;

private:

  class local_function

  {
  public:

    typedef unsigned_digit_type first_argument_type ;
    typedef unsigned_digit_type second_argument_type ;
    typedef unsigned_digit_type result_type ;

  } ;


  class function_with_carry : public local_function

  {
  protected:

    unsigned_digit_type carry = 0 ;

  public:

    static const bool has_carry = true ;

  } ;


  class function_without_carry : public local_function

  {
  public:

    static const bool has_carry = false ;

  } ;


  class plus : public function_with_carry

  {
  private:

    using function_with_carry :: carry ;

  public:

    unsigned_digit_type operator ( ) ( unsigned_digit_type a,
                                       unsigned_digit_type b )
      { a += b ;
        bool c = a < b ;
        a += carry ;
        carry = ( c  ||  a < carry ) ;
        return a ; }

  } ;


  class minus : public function_with_carry

  {
  private:

    using function_with_carry :: carry ;

  public:

    unsigned_digit_type operator ( ) ( unsigned_digit_type a,
                                       unsigned_digit_type b )
      { unsigned_digit_type na ( a - b ) ;
        bool c = na > a ;
        a = na - carry ;
        carry = ( c  ||  na < carry ) ;
        return a ; }

  } ;


  class bitwise_and : public function_without_carry

  {
  public:

    unsigned_digit_type operator ( ) ( unsigned_digit_type a,
                                       unsigned_digit_type b )
      { return a & b ; }

  } ;


  class bitwise_or : public function_without_carry

  {
  public:

    unsigned_digit_type operator ( ) ( unsigned_digit_type a,
                                       unsigned_digit_type b )
      { return a | b ; }

  } ;


  class bitwise_xor : public function_without_carry

  {
  public:

    unsigned_digit_type operator ( ) ( unsigned_digit_type a,
                                       unsigned_digit_type b )
      { return a ^ b ; }

  } ;


  vector < unsigned_digit_type, Allocator > data_ ;

  basic_exint ( size_t n, unsigned_digit_type value,
                const Allocator & a = Allocator ( ) ) :
    data_ ( n, value, a )
    { }

  template < class InputIterator >
  basic_exint ( InputIterator first, InputIterator last,
                const Allocator & a = Allocator ( ) ) :
    data_ ( first, last, a )
    { }

  void signed_construct ( signed_digit_type x )
    { if ( x != 0 )
        data_.push_back ( unsigned_digit_type ( x ) ) ; }

  void unsigned_construct ( unsigned_digit_type x )
    { if ( x != 0 )
        {
        data_.push_back ( x ) ;
        if ( is_high_bit_set ( x ) )
          data_.push_back ( 0 ) ;
        } }

  template < class FloatingPoint >
  static basic_exint
    from_positive_floating_point
      ( const FloatingPoint & x, const Allocator & a ) ;

  void reduce ( ) ;

  void unsigned_reduce ( )
    { data_.erase ( find_if
                      ( data_.rbegin ( ), data_.rend ( ),
                        bind ( not_equal_to < unsigned_digit_type > ( ),
                               placeholders :: _1,
                               unsigned_digit_type ( 0 ) ) )
                      .base ( ),
                    data_.end ( ) ) ; }

  void unsigned_to_signed ( )
    { if ( is_negative ( ) )
        data_.push_back ( 0 ) ; }

  template < class Function >
  void operate ( const basic_exint & b, Function fun ) ;

  void shift_left ( sint n ) ;
  void shift_right ( sint n ) ;

  void unsigned_shift_left ( sint n ) ;
  void unsigned_shift_right ( sint n ) ;

  static basic_exint positive_multiply ( const basic_exint & a,
                                         const basic_exint & b ) ;

  static basic_exint multiply ( const basic_exint & a,
                                const basic_exint & b ) ;

  static void positive_divmod ( basic_exint a, basic_exint b,
                                basic_exint & q, basic_exint & r ) ;

  static void divmod_imp ( const basic_exint & a, const basic_exint & b,
                           basic_exint & q, basic_exint & r ) ;

  template < class CharT, class CharTraits >
  basic_ostream < CharT, CharTraits > &
    output_to ( basic_ostream < CharT, CharTraits > & o ) const ;

  template < class CharT, class CharTraits >
  basic_istream < CharT, CharTraits > &
    input_from ( basic_istream < CharT, CharTraits > & i ) ;

public:

  explicit basic_exint ( const Allocator & a = Allocator ( ) ) :
    data_ ( a )
    { }

  basic_exint ( signed_digit_type x,
                const Allocator & a = Allocator ( ) ) :
    data_ ( a )
    { signed_construct ( x ) ; }

  basic_exint ( unsigned_digit_type x,
                const Allocator & a = Allocator ( ) ) :
    data_ ( a )
    { unsigned_construct ( x ) ; }

  template < class S >
  basic_exint ( S x,
                const Allocator & a = Allocator ( ),
                typename implicit_conversion_test
                           < S, unsigned_digit_type > :: result =
                  implicit_conversion_allowed ) :
    data_ ( a )
    { if ( numeric_traits < S > :: is_signed )
        signed_construct ( convert_to < signed_digit_type > ( x ) ) ;
      else
        unsigned_construct ( unsigned_digit_type ( x ) ) ; }

  explicit basic_exint
             ( const vector < unsigned_digit_type, Allocator > & i_data ) :
    data_ ( i_data )
    { reduce ( ) ; }

  explicit basic_exint
             ( vector < unsigned_digit_type, Allocator > && i_data ) :
    data_ ( move ( i_data ) )
    { reduce ( ) ; }

  template < class InputIterator >
  static basic_exint
    from_signed_block ( InputIterator first, InputIterator last,
                        const Allocator & a = Allocator ( ) )
    { basic_exint result ( first, last, a ) ;
      result.reduce ( ) ;
      return result ; }

  template < class InputIterator >
  static basic_exint
    from_unsigned_block ( InputIterator first, InputIterator last,
                          const Allocator & a = Allocator ( ) )
    { basic_exint result ( first, last, a ) ;
      if ( ! result.data_.empty ( ) )
        {
        if ( is_high_bit_set ( result.data_.back ( ) ) )
          result.data_.push_back ( 0 ) ;
        else
          result.reduce ( ) ;
        }
      return result ; }

  static basic_exint from_rnd ( size_t max_data_size,
                                const Allocator & a = Allocator ( ) ) ;

  static basic_exint
           from_rnd_nonnegative ( size_t max_data_size,
                                  const Allocator & a = Allocator ( ) )
    { basic_exint result ( from_rnd ( max_data_size, a ) ) ;
      result.unsigned_to_signed ( ) ;
      return result ; }

  void clear ( )
    { data_.clear ( ) ; }

  void swap ( basic_exint & b )
    { data_.swap ( b.data_ ) ; }

  const vector < unsigned_digit_type, Allocator > & data ( ) const
    { return data_ ; }

  bool is_zero ( ) const
    { return data_.empty ( ) ; }

  bool is_positive ( ) const
    { return ! data_.empty ( )  &&  ! is_high_bit_set ( data_.back ( ) ) ; }

  bool is_negative ( ) const
    { return ! data_.empty ( )  &&  is_high_bit_set ( data_.back ( ) ) ; }

  signed_digit_type signed_prefix ( ) const
    { return is_negative ( ) ? -1 : 0 ; }

  unsigned_digit_type unsigned_prefix ( ) const
    { return is_negative ( ) ? -1 : 0 ; }

  unsigned_digit_type low_digit ( ) const
    { return data_.empty ( ) ? unsigned_digit_type ( 0 ) : data_.front ( ) ; }

  unsigned_digit_type high_digit ( ) const
    { return data_.empty ( ) ? unsigned_digit_type ( 0 ) : data_.back ( ) ; }

  unsigned_digit_type digit ( size_t index ) const
    { return index < data_.size ( ) ? data_ [ index ] : unsigned_prefix ( ) ; }

  sint exponent ( ) const ;

  template < class FloatingPoint >
  FloatingPoint to_floating_point ( ) const ;

  template < class FloatingPoint >
  static basic_exint from_floating_point ( const FloatingPoint & x,
                                           const Allocator & a = Allocator ( ) )
    { return   :: is_negative ( x )
             ? - from_positive_floating_point ( - x, a )
             : from_positive_floating_point ( x, a ) ; }

  const basic_exint & operator + ( ) const
    { return * this ; }

  basic_exint operator - ( ) const
    { return basic_exint ( ) - * this ; }

  friend basic_exint operator + ( const basic_exint & a,
                                  const basic_exint & b )
    { return basic_exint ( a ) += b ; }

  friend basic_exint operator - ( const basic_exint & a,
                                  const basic_exint & b )
    { return basic_exint ( a ) -= b ; }

  friend basic_exint operator * ( const basic_exint & a,
                                  const basic_exint & b )
    { return multiply ( a, b ) ; }

  friend void divmod ( const basic_exint & a, const basic_exint & b,
                       basic_exint & q, basic_exint & r )
    { divmod_imp ( a, b, q, r ) ; }

  friend basic_exint operator / ( const basic_exint & a,
                                  const basic_exint & b )
    { basic_exint q, r ;
      divmod ( a, b, q, r ) ;
      return q ; }

  friend basic_exint operator % ( const basic_exint & a,
                                  const basic_exint & b )
    { basic_exint q, r ;
      divmod ( a, b, q, r ) ;
      return r ; }

  basic_exint & operator += ( const basic_exint & b )
    { operate ( b, plus ( ) ) ;
      return * this ; }

  basic_exint & operator -= ( const basic_exint & b )
    { operate ( b, minus ( ) ) ;
      return * this ; }

  basic_exint & operator *= ( const basic_exint & b )
    { return * this = * this * b ; }

  basic_exint & operator /= ( const basic_exint & b )
    { return * this = * this / b ; }

  basic_exint & operator %= ( const basic_exint & b )
    { return * this = * this % b ; }

  basic_exint & operator ++ ( )
    { return * this += 1 ; }

  basic_exint operator ++ ( int )
    { basic_exint t ( * this ) ;
      ++ * this ;
      return t ; }

  basic_exint & operator -- ( )
    { return * this -= 1 ; }

  basic_exint operator -- ( int )
    { basic_exint t ( * this ) ;
      -- * this ;
      return t ; }

  basic_exint operator ~ ( ) const
    { return -1 - * this ; }

  friend basic_exint operator & ( const basic_exint & a,
                                  const basic_exint & b )
    { return basic_exint ( a ) &= b ; }

  friend basic_exint operator | ( const basic_exint & a,
                                  const basic_exint & b )
    { return basic_exint ( a ) |= b ; }

  friend basic_exint operator ^ ( const basic_exint & a,
                                  const basic_exint & b )
    { return basic_exint ( a ) ^= b ; }

  basic_exint & operator &= ( const basic_exint & b )
    { operate ( b, bitwise_and ( ) ) ;
      return * this ; }

  basic_exint & operator |= ( const basic_exint & b )
    { operate ( b, bitwise_or ( ) ) ;
      return * this ; }

  basic_exint & operator ^= ( const basic_exint & b )
    { operate ( b, bitwise_xor ( ) ) ;
      return * this ; }

  basic_exint operator << ( sint n ) const
    { return basic_exint ( * this ) <<= n ; }

  basic_exint operator >> ( sint n ) const
    { return basic_exint ( * this ) >>= n ; }

  basic_exint & operator <<= ( sint n )
    { if ( n > 0 )
        shift_left ( n ) ;
      else
        if ( n < 0 )
          shift_right ( - n ) ;
      return * this ; }

  basic_exint & operator >>= ( sint n )
    { if ( n > 0 )
        shift_right ( n ) ;
      else
        if ( n < 0 )
          shift_left ( - n ) ;
      return * this ; }

  friend bool operator == ( const basic_exint & a, const basic_exint & b )
    { return a.data_ == b.data_ ; }

  friend bool operator < ( const basic_exint & a, const basic_exint & b )
    { return
          a.is_negative ( )
        ? (     ! b.is_negative ( )
            ||  (     a.data_.size ( ) > b.data_.size ( )
                  ||  (     a.data_.size ( ) == b.data_.size ( )
                        &&  lexicographical_compare
                              ( a.data_.rbegin ( ), a.data_.rend ( ),
                                b.data_.rbegin ( ), b.data_.rend ( ) ) ) ) )
        : (     ! b.is_negative ( )
            &&  (     a.data_.size ( ) < b.data_.size ( )
                  ||  (     a.data_.size ( ) == b.data_.size ( )
                        &&  lexicographical_compare
                              ( a.data_.rbegin ( ), a.data_.rend ( ),
                                b.data_.rbegin ( ), b.data_.rend ( ) ) ) ) ) ; }

  template < class CharT, class CharTraits >
  friend basic_ostream < CharT, CharTraits > &
    operator << ( basic_ostream < CharT, CharTraits > & o,
                  const basic_exint & x )
    { return x.output_to ( o ) ; }

  template < class CharT, class CharTraits >
  friend basic_istream < CharT, CharTraits > &
    operator >> ( basic_istream < CharT, CharTraits > & i,
                  basic_exint & x )
    { return x.input_from ( i ) ; }

} ;


// pre: x >= 0

template < class T, class Allocator >
template < class FloatingPoint >
basic_exint < T, Allocator >
  basic_exint < T, Allocator > :: from_positive_floating_point
    ( const FloatingPoint & x, const Allocator & a )

{
assert ( ! :: is_negative ( x ) ) ;

FloatingPoint y = trunc ( x ) ;

typename numeric_traits < FloatingPoint > :: exponent_type
  zde (   (   :: exponent ( y )
            - numeric_traits < FloatingPoint > :: mantissa_bit_size )
        / digit_bit_size ) ;

size_t zds ;

if ( :: is_negative ( zde ) )
  zds = 0 ;
else
  if ( zde <= numeric_traits < size_t > :: max ( ) )
    {
    zds = convert_to < size_t > ( zde ) ;
    y = ldexp ( y, - digit_bit_size * zde ) ;
    }
  else
    throw bad_alloc ( ) ;

basic_exint result ( zds, 0, a ) ;

while ( y != 0 )
  {
  FloatingPoint ys ( trunc ( ldexp ( y, - digit_bit_size ) ) ) ;
  result.data_.push_back ( convert_to < unsigned_digit_type >
                             ( y - ldexp ( ys, digit_bit_size ) ) ) ;
  y = ys ;
  }

return result ;
}


//

template < class T, class Allocator >
inline void basic_exint < T, Allocator > :: reduce ( )

{
auto prefix_begin =
       find_if ( data_.rbegin ( ), data_.rend ( ),
                 bind ( not_equal_to < unsigned_digit_type > ( ),
                        placeholders :: _1,
                        unsigned_prefix ( ) ) )
       .base ( ) ;

if ( prefix_begin == data_.end ( ) )
  return ;

if ( is_negative ( ) )
  {
  if (     prefix_begin == data_.begin ( )
       ||  ! is_high_bit_set ( * ( prefix_begin - 1 ) ) )
    ++ prefix_begin ;
  }
else
  {
  if (     prefix_begin != data_.begin ( )
       &&  is_high_bit_set ( * ( prefix_begin - 1 ) ) )
    ++ prefix_begin ;
  }

data_.erase ( prefix_begin, data_.end ( ) ) ;
}


//

template < class T, class Allocator >
template < class Function >
void basic_exint < T, Allocator > ::
       operate ( const basic_exint < T, Allocator > & b, Function fun )

{
reference_wrapper < Function > fun_ref ( fun ) ;

unsigned_digit_type p ( unsigned_prefix ( ) ) ;

if ( data_.size ( ) < b.data_.size ( ) )
  {
  data_.reserve (   Function :: has_carry
                  ? b.data_.size ( ) + 1
                  : b.data_.size ( ) ) ;

  transform ( data_.begin ( ), data_.end ( ),
              b.data_.begin ( ),
              data_.begin ( ),
              fun_ref ) ;

  transform ( b.data_.begin ( ) + data_.size ( ), b.data_.end ( ),
              back_inserter ( data_ ),
              bind ( fun_ref, p, placeholders :: _1 ) ) ;
  }
else
  {
  transform ( data_.begin ( ), data_.begin ( ) + b.data_.size ( ),
              b.data_.begin ( ),
              data_.begin ( ),
              fun_ref ) ;

  transform ( data_.begin ( ) + b.data_.size ( ), data_.end ( ),
              data_.begin ( ) + b.data_.size ( ),
              bind ( fun_ref, placeholders :: _1, b.unsigned_prefix ( ) ) ) ;
  }

if ( Function :: has_carry )
  data_.push_back ( fun ( p, b.unsigned_prefix ( ) ) ) ;

reduce ( ) ;
}


// pre: n >= 0

template < class T, class Allocator >
void basic_exint < T, Allocator > :: shift_left ( sint n )

{
assert ( n >= 0 ) ;

if ( is_zero ( ) )
  return ;

sint digits, bits ;
divmod ( n, digit_bit_size, digits, bits ) ;

if ( bits > 0 )
  {
  unsigned_digit_type
    l (   ( unsigned_prefix ( ) << bits )
        | ( data_.back ( ) >> ( digit_bit_size - bits ) ) ),
    p ( is_high_bit_set ( data_.back ( ) << bits ) ? -1 : 0 ) ;

  {
  sint new_size = data_.size ( ) + digits ;
  if ( l != p )
    ++ new_size ;
  data_.reserve ( new_size ) ;
  }

  for ( auto iter = data_.end ( ) - 1 ;
             iter != data_.begin ( ) ;
             -- iter )
    * iter =   ( * iter << bits )
             | ( * ( iter - 1 ) >> ( digit_bit_size - bits ) ) ;

  data_.front ( ) <<= bits ;

  if ( l != p )
    data_.push_back ( l ) ;
  }

data_.insert ( data_.begin ( ), digits, 0 ) ;
}


// pre: n >= 0

template < class T, class Allocator >
void basic_exint < T, Allocator > :: shift_right ( sint n )

{
assert ( n >= 0 ) ;

if ( is_zero ( ) )
  return ;

sint digits, bits ;
divmod ( n, digit_bit_size, digits, bits ) ;

if ( digits >= data_.size ( ) )
  {
  * this = signed_prefix ( ) ;
  return ;
  }

data_.erase ( data_.begin ( ), data_.begin ( ) + digits ) ;

if ( bits > 0 )
  {
  for ( auto iter = data_.begin ( ) ;
             iter != data_.end ( ) - 1 ;
             ++ iter )
    * iter =   ( * iter >> bits )
             | ( * ( iter + 1 ) << ( digit_bit_size - bits ) ) ;

  data_.back ( ) = signed_shift_right ( data_.back ( ), bits ) ;

  reduce ( ) ;
  }
}


// pre: n >= 0

template < class T, class Allocator >
void basic_exint < T, Allocator > :: unsigned_shift_left ( sint n )

{
assert ( n >= 0 ) ;

if ( is_zero ( ) )
  return ;

sint digits, bits ;
divmod ( n, digit_bit_size, digits, bits ) ;

if ( bits > 0 )
  {
  unsigned_digit_type l ( data_.back ( ) >> ( digit_bit_size - bits ) ) ;

  {
  sint new_size = data_.size ( ) + digits ;
  if ( l != 0 )
    ++ new_size ;
  data_.reserve ( new_size ) ;
  }

  for ( auto iter = data_.end ( ) - 1 ;
             iter != data_.begin ( ) ;
             -- iter )
    * iter =   ( * iter << bits )
             | ( * ( iter - 1 ) >> ( digit_bit_size - bits ) ) ;

  data_.front ( ) <<= bits ;

  if ( l != 0 )
    data_.push_back ( l ) ;
  }

data_.insert ( data_.begin ( ), digits, 0 ) ;

unsigned_reduce ( ) ;
}


// pre: n >= 0

template < class T, class Allocator >
void basic_exint < T, Allocator > :: unsigned_shift_right ( sint n )

{
assert ( n >= 0 ) ;

if ( is_zero ( ) )
  return ;

sint digits, bits ;
divmod ( n, digit_bit_size, digits, bits ) ;

if ( digits >= data_.size ( ) )
  {
  clear ( ) ;
  return ;
  }

data_.erase ( data_.begin ( ), data_.begin ( ) + digits ) ;

if ( bits > 0 )
  {
  for ( auto iter = data_.begin ( ) ;
             iter != data_.end ( ) - 1 ;
             ++ iter )
    * iter =   ( * iter >> bits )
             | ( * ( iter + 1 ) << ( digit_bit_size - bits ) ) ;

  data_.back ( ) >>= bits ;
  }

unsigned_reduce ( ) ;
}


// pre: a >= 0
//      b >= 0
//
// returns: a * b

template < class T, class Allocator >
basic_exint < T, Allocator >
  basic_exint < T, Allocator > ::
    positive_multiply ( const basic_exint < T, Allocator > & a,
                        const basic_exint < T, Allocator > & b )

{
assert ( ! a.is_negative ( ) ) ;
assert ( ! b.is_negative ( ) ) ;

if ( a.is_zero ( )  ||  b.is_zero ( ) )
  return basic_exint < T, Allocator > ( ) ;

const vector < unsigned_digit_type, Allocator > * av,
                                                * bv ;

if ( a.data_.size ( ) < b.data_.size ( ) )
  {
  av = & a.data_ ;
  bv = & b.data_ ;
  }
else
  {
  av = & b.data_ ;
  bv = & a.data_ ;
  }

basic_exint < T, Allocator >
  r ( av -> size ( ) + bv -> size ( ), unsigned_digit_type ( 0 ) ) ;

for ( sint i = 0 ; i < av -> size ( ) ; ++ i )
  {
  unsigned_digit_type ad ( ( * av ) [ i ] ),
                      carry ( 0 ) ;

  sint j ;

  for ( j = 0 ; j < bv -> size ( ) ; ++ j )
    {
    unsigned_digit_type h, l ;
    unsigned_double_multiply ( ad, ( * bv ) [ j ], h, l ) ;

    l += carry ;

    if ( l < carry )
      ++ h ;

    unsigned_digit_type & rd = r.data_ [ i + j ] ;

    rd += l ;

    if ( rd < l )
      ++ h ;

    carry = h ;
    }

  for ( ; ; ++ j )
    {
    unsigned_digit_type & rd = r.data_ [ i + j ] ;

    rd += carry ;

    if ( rd >= carry )
      break ;

    carry = 1 ;
    }
  }

r.reduce ( ) ;
return r ;
}


// returns: a * b

template < class T, class Allocator >
basic_exint < T, Allocator >
  basic_exint < T, Allocator > ::
    multiply ( const basic_exint < T, Allocator > & a,
               const basic_exint < T, Allocator > & b )

{
if ( a.is_negative ( ) )
  if ( b.is_negative ( ) )
    return positive_multiply ( - a, - b ) ;
  else
    return - positive_multiply ( - a, b ) ;
else
  if ( b.is_negative ( ) )
    return - positive_multiply ( a, - b ) ;
  else
    return positive_multiply ( a, b ) ;
}


// pre: a >= 0
//      b > 0
//
// post: q = a / b
//       r = a % b

template < class T, class Allocator >
void basic_exint < T, Allocator > ::
       positive_divmod ( basic_exint < T, Allocator > a,
                         basic_exint < T, Allocator > b,
                         basic_exint < T, Allocator > & q,
                         basic_exint < T, Allocator > & r )

{
assert ( ! a.is_negative ( ) ) ;
assert ( b.is_positive ( ) ) ;

if ( a < b )
  {
  q.clear ( ) ;
  r = move ( a ) ;
  return ;
  }

a.unsigned_reduce ( ) ;
b.unsigned_reduce ( ) ;

sint bit_shift = digit_bit_size - :: exponent ( b.data_.back ( ) ) ;

a.unsigned_shift_left ( bit_shift ) ;
b.unsigned_shift_left ( bit_shift ) ;

if ( a.data_.back ( ) >= b.data_.back ( ) )
  a.data_.push_back ( 0 ) ;

vector < unsigned_digit_type, Allocator >
  qv ( a.data_.size ( ) - b.data_.size ( ), 0 ) ;

vector < unsigned_digit_type, Allocator > bs ( b.data_.size ( ) + 1, 0 ) ;

do
  {
  unsigned_digit_type
    qd (   a.data_.back ( ) == b.data_.back ( )
         ? unsigned_digit_type ( -1 )
         : unsigned_double_divide
             ( a.data_.back ( ), a.data_ [ a.data_.size ( ) - 2 ],
               b.data_.back ( ) ) ) ;

  {
  unsigned_digit_type carry ( 0 ) ;

  for ( sint i = 0 ; i < b.data_.size ( ) ; ++ i )
    {
    unsigned_digit_type h, l ;
    unsigned_double_multiply ( qd, b.data_ [ i ], h, l ) ;

    l += carry ;

    if ( l < carry )
      ++ h ;

    bs [ i ] = l ;

    carry = h ;
    }

  bs.back ( ) = carry ;
  }

  while ( lexicographical_compare ( a.data_.rbegin ( ), a.data_.rend ( ),
                                    bs.rbegin ( ), bs.rend ( ) ) )
    {
    minus fun ;

    transform ( bs.begin ( ), bs.end ( ) - 1,
                b.data_.begin ( ),
                bs.begin ( ),
                ref ( fun ) ) ;

    bs.back ( ) = fun ( bs.back ( ), 0 ) ;

    -- qd ;
    }

  qv [ a.data_.size ( ) - bs.size ( ) ] = qd ;

  transform ( a.data_.end ( ) - bs.size ( ), a.data_.end ( ) - 1,
              bs.begin ( ),
              a.data_.end ( ) - bs.size ( ),
              minus ( ) ) ;

  a.data_.pop_back ( ) ;
  }
while ( a.data_.size ( ) > b.data_.size ( ) ) ;

a.unsigned_shift_right ( bit_shift ) ;

q.data_ = move ( qv ) ;
q.unsigned_to_signed ( ) ;

r = move ( a ) ;
r.unsigned_to_signed ( ) ;
}


// post: q = a / b
//       r = a % b

template < class T, class Allocator >
void basic_exint < T, Allocator > ::
       divmod_imp ( const basic_exint < T, Allocator > & a,
                    const basic_exint < T, Allocator > & b,
                    basic_exint < T, Allocator > & q,
                    basic_exint < T, Allocator > & r )

{
if ( a.is_negative ( ) )
  if ( b.is_negative ( ) )
    {
    positive_divmod ( - a, - b, q, r ) ;
    r = - r ;
    }
  else
    {
    positive_divmod ( - a, b, q, r ) ;
    q = - q ;
    r = - r ;
    }
else
  if ( b.is_negative ( ) )
    {
    positive_divmod ( a, - b, q, r ) ;
    q = - q ;
    }
  else
    positive_divmod ( a, b, q, r ) ;
}


//

template < class T, class Allocator >
template < class CharT, class CharTraits >
basic_ostream < CharT, CharTraits > &
  basic_exint < T, Allocator > ::
    output_to ( basic_ostream < CharT, CharTraits > & o ) const

{
basic_exint < T, Allocator > x ;

bool negative = is_negative ( ) ;

if ( negative )
  x = - * this ;
else
  x = * this ;

vector < CharT > text ;

do
  {
  basic_exint < T, Allocator > d ;
  divmod ( x, 10, x, d ) ;
  text.push_back ( convert_to < CharT > ( d ) + CharT ( '0' ) ) ;
  }
while ( ! x.is_zero ( ) ) ;

if ( negative )
  text.push_back ( CharT ( '-' ) ) ;

reverse ( text.begin ( ), text.end ( ) ) ;

return o.write ( text.data ( ), text.size ( ) ) ;
}


//

template < class T, class Allocator >
template < class CharT, class CharTraits >
basic_istream < CharT, CharTraits > &
  basic_exint < T, Allocator > ::
    input_from ( basic_istream < CharT, CharTraits > & i )

{
ios_base :: fmtflags start_flags = i.flags ( ) ;
i.setf ( ios_base :: skipws ) ;

basic_exint < T, Allocator > x ;

bool negative ;
CharT c ;

i >> c ;
if ( ! i.good ( ) )
  goto error_end ;

i.unsetf ( ios_base :: skipws ) ;

if ( c == CharT ( '-' ) )
  {
  negative = true ;
  i >> c ;
  if ( ! i.good ( ) )
    goto error_end ;
  }
else
  negative = false ;

if ( c < CharT ( '0' )  ||  c > CharT ( '9' ) )
  {
  i.putback ( c ) ;
  i.setstate ( ios_base :: failbit ) ;
  goto error_end ;
  }

do
  {
  try
    {
    x = x * 10 + ( c - CharT ( '0' ) ) ;
    }
  catch ( ... )
    {
    goto error_end ;
    }

  i >> c ;
  if ( i.eof ( ) )
    goto ok_end ;
  if ( ! i.good ( ) )
    goto error_end ;
  }
while ( c >= CharT ( '0' )  &&  c <= CharT ( '9' ) ) ;
i.putback ( c ) ;

ok_end:

if ( negative )
  * this = - x ;
else
  * this = move ( x ) ;

error_end:

i.flags ( start_flags ) ;
return i ;
}


//

template < class T, class Allocator >
basic_exint < T, Allocator >
  basic_exint < T, Allocator > :: from_rnd ( size_t max_data_size,
                                             const Allocator & a )

{
basic_exint < T, Allocator > result ( a ) ;
result.data_.reserve ( max_data_size + 1 ) ;

for ( size_t i = 0 ; i < max_data_size ; ++ i )
  result.data_.push_back ( rnd < unsigned_digit_type > ( ) ) ;

result.reduce ( ) ;

return result ;
}


//

template < class T, class Allocator >
inline sint basic_exint < T, Allocator > :: exponent ( ) const

{
if ( is_zero ( ) )
  return 0 ;

unsigned_digit_type l ;

if ( is_negative ( ) )
  {
  l = ~ data_.back ( ) ;

  if (    find_if ( data_.begin ( ), data_.end ( ) - 1,
                    bind ( not_equal_to < unsigned_digit_type > ( ),
                           placeholders :: _1,
                           unsigned_digit_type ( 0 ) ) )
       == data_.end ( ) - 1 )
    ++ l ;
  }
else
  l = data_.back ( ) ;

return   digit_bit_size * static_cast < sint > ( data_.size ( ) - 1 )
       + :: exponent ( l ) ;
}


//

template < class T, class Allocator >
template < class FloatingPoint >
inline
  FloatingPoint basic_exint < T, Allocator > :: to_floating_point ( ) const

{
if ( data_.empty ( ) )
  return 0 ;

auto iter = data_.end ( ) ;

FloatingPoint r = convert_to < FloatingPoint >
                    ( convert_to < signed_digit_type > ( * -- iter ) ) ;

sint digits =   (   numeric_traits < FloatingPoint > :: mantissa_bit_size
                  + digit_bit_size - 2 )
              / digit_bit_size ;

while ( iter != data_.begin ( )  &&  digits != 0 )
  {
  r =   ldexp ( r, digit_bit_size )
      + convert_to < FloatingPoint > ( * -- iter ) ;
  -- digits ;
  }

return ldexp ( r, ( iter - data_.begin ( ) ) * digit_bit_size ) ;
}



// *** RANGE_RND_STATIC_GENERATOR ***


template < class T, class Allocator >
class range_rnd_static_generator < basic_exint < T, Allocator > >

{
public:

  static basic_exint < T, Allocator >
           operate ( const basic_exint < T, Allocator > & a,
                     const basic_exint < T, Allocator > & b )
    { if ( a >= b )
        return a ;
      basic_exint < T, Allocator > range = b - a ;
      return
          a
        + basic_exint < T, Allocator > ::
            from_rnd_nonnegative ( range.data ( ).size ( ) + 1 ) % range ; }

} ;



// *** GLOBAL INTERFACES ***


//

template < class T, class Allocator >
inline void swap ( basic_exint < T, Allocator > & a,
                   basic_exint < T, Allocator > & b )

{
a.swap ( b ) ;
}


//

template < class T, class Allocator >
inline bool is_negative ( const basic_exint < T, Allocator > & x )

{
return x.is_negative ( ) ;
}


//

template < class T, class Allocator >
inline sint exponent ( const basic_exint < T, Allocator > & x )

{
return x.exponent ( ) ;
}


//

template < class T, class Allocator >
inline void normalize_gcd ( basic_exint < T, Allocator > & gcd )

{
if ( gcd.is_negative ( ) )
  gcd = - gcd ;
}


//

template < class T, class Allocator >
inline void normalize_gcd_ext ( basic_exint < T, Allocator > & c,
                                basic_exint < T, Allocator > & d,
                                basic_exint < T, Allocator > & gcd )

{
if ( gcd.is_negative ( ) )
  {
  c = - c ;
  d = - d ;
  gcd = - gcd ;
  }
}


//

template < class T, class Allocator >
inline void normalize_fraction ( basic_exint < T, Allocator > & a,
                                 basic_exint < T, Allocator > & b )

{
if ( b.is_negative ( ) )
  {
  a = - a ;
  b = - b ;
  }
}



// *** IMPLICIT CONVERSION ***


//

template < class T, class Allocator >
class implicit_conversion_test
        < typename basic_exint < T, Allocator > :: signed_digit_type,
          basic_exint < T, Allocator > > :
  public implicit_conversion_test_ok

{
} ;


//

template < class T, class Allocator >
class implicit_conversion_test
        < typename basic_exint < T, Allocator > :: unsigned_digit_type,
          basic_exint < T, Allocator > > :
  public implicit_conversion_test_ok

{
} ;


//

template < class S, class T, class Allocator >
class implicit_conversion_test < S, basic_exint < T, Allocator > > :
  public implicit_conversion_test
           < S, typename basic_exint < T, Allocator > :: unsigned_digit_type >

{
} ;



// *** TYPE CONVERSION ***


//

template < class T, class Allocator >
class type_converter
        < basic_exint < T, Allocator >,
          typename basic_exint < T, Allocator > :: unsigned_digit_type >

{
public:

  static typename basic_exint < T, Allocator > :: unsigned_digit_type
    operate ( const basic_exint < T, Allocator > & x )
    { return x.low_digit ( ) ; }

} ;


//

template
  < class BasicExint, class Destination, bool DestinationIsFloatingPoint >
class from_basic_exint_type_converter ;


//

template < class BasicExint, class Destination >
class from_basic_exint_type_converter < BasicExint, Destination, false >

{
public:

  static Destination operate ( const BasicExint & x )
    { return convert_to < Destination > ( x.low_digit ( ) ) ; }

} ;


//

template < class BasicExint, class Destination >
class from_basic_exint_type_converter < BasicExint, Destination, true >

{
public:

  static Destination operate ( const BasicExint & x )
    { return x.template to_floating_point < Destination > ( ) ; }

} ;


//

template < class T, class Allocator, class U >
class type_converter < basic_exint < T, Allocator >, U > :
  public from_basic_exint_type_converter
           < basic_exint < T, Allocator >,
             U,
             numeric_traits < U > :: is_floating_point >

{
} ;


//

template < class Source, class BasicExint, bool SourceIsFloatingPoint >
class to_basic_exint_type_converter ;


//

template < class Source, class BasicExint >
class to_basic_exint_type_converter < Source, BasicExint, false >

{
public:

  static BasicExint operate ( const Source & x )
    { return BasicExint ( x ) ; }

} ;


//

template < class Source, class BasicExint >
class to_basic_exint_type_converter < Source, BasicExint, true >

{
public:

  static BasicExint operate ( const Source & x )
    { return BasicExint :: from_floating_point ( x ) ; }

} ;


//

template < class S, class T, class Allocator >
class type_converter < S, basic_exint < T, Allocator > > :
  public to_basic_exint_type_converter
           < S,
             basic_exint < T, Allocator >,
             numeric_traits < S > :: is_floating_point >

{
} ;



// *** EXINT ***


typedef basic_exint < uint > exint ;



#endif
