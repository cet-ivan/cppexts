// Copyright Ivan Stanojevic 2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __STREAMING_H

#define __STREAMING_H



#include "cstddef.h"
#include "ostream.h"
#include "istream.h"
#include "ios.h"
#include "utility_base.h"
#include "cstring.h"
#include "cwchar.h"
#include "streambuf.h"
#include "cassert.h"
#include "string.h"



// *** FORWARD DECLARATIONS ***


template < class CharT, class CharTraits, class T, size_t N >
basic_ostream < CharT, CharTraits > &
  output_array ( basic_ostream < CharT, CharTraits > & o,
                 const T ( & array ) [ N ] ) ;

template < class CharT, class CharTraits, class T, size_t N >
basic_istream < CharT, CharTraits > &
  input_array ( basic_istream < CharT, CharTraits > & i,
                T ( & array ) [ N ] ) ;



// *** STANDARD_OUTPUT_OPERATOR ***


class standard_output_operator

{
public:

  template < class CharT, class CharTraits, class T >
  basic_ostream < CharT, CharTraits > &
    operator ( ) ( basic_ostream < CharT, CharTraits > & o,
                   const T & x ) const
    { return o << x ; }

} ;



// *** ARRAY_OUTPUT_OPERATOR ***


class array_output_operator : public standard_output_operator

{
public:

  using standard_output_operator :: operator ( ) ;

  template < class CharT, class CharTraits, class T, size_t N >
  basic_ostream < CharT, CharTraits > &
    operator ( ) ( basic_ostream < CharT, CharTraits > & o,
                   const T ( & array ) [ N ] ) const
    { return output_array ( o, array ) ; }

} ;



// *** OUTPUT GLOBALS ***


//

template < class CharT, class CharTraits, class T1, class T2 >
inline basic_ostream < CharT, CharTraits > &
  output_pair ( basic_ostream < CharT, CharTraits > & o,
                const T1 & a, const T2 & b )

{
return o << CharT ( '(' ) << a << CharT ( ',' ) << b << CharT ( ')' ) ;
}


//

template < class CharT, class CharTraits,
           class InputIterator,
           class OutputOperator = standard_output_operator >
basic_ostream < CharT, CharTraits > &
  output_range ( basic_ostream < CharT, CharTraits > & o,
                 InputIterator first, InputIterator last,
                 OutputOperator oo = standard_output_operator ( ) )

{
o << CharT ( '[' ) ;

bool comma = false ;

while ( first != last )
  {
  if ( comma )
    o << CharT ( ',' ) ;

  oo ( o, * first ) ;
  ++ first ;

  comma = true ;
  }

o << CharT ( ']' ) ;

return o ;
}


//

template < class CharT, class CharTraits,
           class InputIterator, class Size,
           class OutputOperator = standard_output_operator >
basic_ostream < CharT, CharTraits > &
  output_range_n ( basic_ostream < CharT, CharTraits > & o,
                   InputIterator first, Size n,
                   OutputOperator oo = standard_output_operator ( ) )

{
o << CharT ( '[' ) ;

bool comma = false ;

while ( n > 0 )
  {
  if ( comma )
    o << CharT ( ',' ) ;

  oo ( o, * first ) ;
  ++ first ;
  -- n ;

  comma = true ;
  }

o << CharT ( ']' ) ;

return o ;
}


//

template < class CharT, class CharTraits,
           class Sequence, class OutputOperator = standard_output_operator >
inline basic_ostream < CharT, CharTraits > &
  output_sequence ( basic_ostream < CharT, CharTraits > & o,
                    const Sequence & s,
                    OutputOperator oo = standard_output_operator ( ) )

{
return output_range ( o, s.begin ( ), s.end ( ), oo ) ;
}


//

template < class CharT, class CharTraits >
inline basic_ostream < CharT, CharTraits > &
  output_empty_sequence ( basic_ostream < CharT, CharTraits > & o )

{
return o << CharT ( '[' ) << CharT ( ']' ) ;
}


//

template < class CharT, class CharTraits, class Size >
basic_ostream < CharT, CharTraits > &
  output_empty_sequence_n ( basic_ostream < CharT, CharTraits > & o, Size n )

{
o << CharT ( '[' ) ;

bool comma = false ;

while ( n > 0 )
  {
  if ( comma )
    o << CharT ( ',' ) ;

  o << CharT ( '[' ) << CharT ( ']' ) ;
  -- n ;

  comma = true ;
  }

o << CharT ( ']' ) ;

return o ;
}


//

template < class CharT, class CharTraits, class T, size_t N >
inline basic_ostream < CharT, CharTraits > &
  output_array ( basic_ostream < CharT, CharTraits > & o,
                 const T ( & array ) [ N ] )

{
return output_range ( o, array, array + N, array_output_operator ( ) ) ;
}



// *** STANDARD_INPUT_OPERATOR ***


class standard_input_operator

{
public:

  template < class CharT, class CharTraits, class T >
  basic_istream < CharT, CharTraits > &
    operator ( ) ( basic_istream < CharT, CharTraits > & i,
                   T & x ) const
    { return i >> x ; }

} ;



// *** ARRAY_INPUT_OPERATOR ***


class array_input_operator : public standard_input_operator

{
public:

  using standard_input_operator :: operator ( ) ;

  template < class CharT, class CharTraits, class T, size_t N >
  basic_istream < CharT, CharTraits > &
    operator ( ) ( basic_istream < CharT, CharTraits > & i,
                   T ( & array ) [ N ] ) const
    { return input_array ( i, array ) ; }

} ;



// *** INPUT GLOBALS ***


//

template < class CharT, class CharTraits, class T1, class T2 >
basic_istream < CharT, CharTraits > &
  input_pair ( basic_istream < CharT, CharTraits > & i,
               T1 & a, T2 & b )

{
T1 ta ;
T2 tb ;

CharT c ;

i >> c ;
if ( ! i.good ( )  ||  c != CharT ( '(' ) )
  goto error_end ;

i >> ta ;
if ( ! i.good ( ) )
  goto error_end ;

i >> c ;
if ( ! i.good ( )  ||  c != CharT ( ',' ) )
  goto error_end ;

i >> tb ;
if ( ! i.good ( ) )
  goto error_end ;

i >> c ;
if ( ! i.good ( )  ||  c != CharT ( ')' ) )
  goto error_end ;

a = move ( ta ) ;
b = move ( tb ) ;

goto end ;

error_end:

i.setstate ( ios_base :: failbit ) ;

end:

return i ;
}


//

template < class CharT, class CharTraits,
           class ForwardIterator,
           class InputOperator = standard_input_operator >
basic_istream < CharT, CharTraits > &
  input_range ( basic_istream < CharT, CharTraits > & i,
                ForwardIterator first, ForwardIterator last,
                InputOperator io = standard_input_operator ( ) )

{
CharT c ;

i >> c ;
if ( ! i.good ( )  ||  c != CharT ( '[' ) )
  goto error_end ;

if ( first == last )
  goto finish ;

for ( ; ; )
  {
  io ( i, * first ) ;
  if ( ! i.good ( ) )
    goto error_end ;

  ++ first ;
  if ( first == last )
    goto finish ;

  i >> c ;
  if ( ! i.good ( )  &&  c != CharT ( ',' ) )
    goto error_end ;
  }

finish:

i >> c ;
if ( i.good ( )  &&  c == CharT ( ']' ) )
  goto end ;

error_end:

i.setstate ( ios_base :: failbit ) ;

end:

return i ;
}


//

template < class CharT, class CharTraits,
           class ForwardIterator, class Size,
           class InputOperator = standard_input_operator >
basic_istream < CharT, CharTraits > &
  input_range_n ( basic_istream < CharT, CharTraits > & i,
                  ForwardIterator first, Size n,
                  InputOperator io = standard_input_operator ( ) )

{
CharT c ;

i >> c ;
if ( ! i.good ( )  ||  c != CharT ( '[' ) )
  goto error_end ;

if ( n <= 0 )
  goto finish ;

for ( ; ; )
  {
  io ( i, * first ) ;
  if ( ! i.good ( ) )
    goto error_end ;

  ++ first ;
  -- n ;
  if ( n <= 0 )
    goto finish ;

  i >> c ;
  if ( ! i.good ( )  &&  c != CharT ( ',' ) )
    goto error_end ;
  }

finish:

i >> c ;
if ( i.good ( )  &&  c == CharT ( ']' ) )
  goto end ;

error_end:

i.setstate ( ios_base :: failbit ) ;

end:

return i ;
}


//

template < class CharT, class CharTraits,
           class Sequence, class InputOperator = standard_input_operator >
basic_istream < CharT, CharTraits > &
  input_sequence ( basic_istream < CharT, CharTraits > & i,
                   Sequence & s,
                   InputOperator io = standard_input_operator ( ) )

{
Sequence ts ;

CharT c ;

i >> c ;
if ( ! i.good ( )  ||  c != CharT ( '[' ) )
  goto error_end ;

i >> c ;
if ( ! i.good ( ) )
  goto error_end ;

if ( c == CharT ( ']' ) )
  {
  s.clear ( ) ;
  goto end ;
  }

i.putback ( c ) ;

for ( ; ; )
  {
  typename Sequence :: value_type t ;

  io ( i, t ) ;
  if ( ! i.good ( ) )
    goto error_end ;

  ts.insert ( ts.end ( ), t ) ;

  i >> c ;
  if ( ! i.good ( ) )
    goto error_end ;

  if ( c == CharT ( ',' ) )
    continue ;

  if ( c == CharT ( ']' ) )
    break ;

  goto error_end ;
  }

s = move ( ts ) ;

goto end ;

error_end:

i.setstate ( ios_base :: failbit ) ;

end:

return i ;
}


//

template < class CharT, class CharTraits >
basic_istream < CharT, CharTraits > &
  input_empty_sequence ( basic_istream < CharT, CharTraits > & i )

{
CharT c ;

i >> c ;
if ( ! i.good ( )  ||  c != CharT ( '[' ) )
  goto error_end ;

i >> c ;
if ( i.good ( )  &&  c == CharT ( ']' ) )
  goto end ;

error_end:

i.setstate ( ios_base :: failbit ) ;

end:

return i ;
}


//

template < class CharT, class CharTraits, class Size >
basic_istream < CharT, CharTraits > &
  input_empty_sequence_n ( basic_istream < CharT, CharTraits > & i, Size n )

{
CharT c ;

i >> c ;
if ( ! i.good ( )  ||  c != CharT ( '[' ) )
  goto error_end ;

if ( n <= 0 )
  goto finish ;

for ( ; ; )
  {
  i >> c ;
  if ( ! i.good ( )  ||  c != CharT ( '[' ) )
    goto error_end ;

  i >> c ;
  if ( ! i.good ( )  ||  c != CharT ( ']' ) )
    goto error_end ;

  -- n ;
  if ( n <= 0 )
    goto finish ;

  i >> c ;
  if ( ! i.good ( )  &&  c != CharT ( ',' ) )
    goto error_end ;
  }

finish:

i >> c ;
if ( i.good ( )  &&  c == CharT ( ']' ) )
  goto end ;

error_end:

i.setstate ( ios_base :: failbit ) ;

end:

return i ;
}


//

template < class CharT, class CharTraits, class T, size_t N >
inline basic_istream < CharT, CharTraits > &
  input_array ( basic_istream < CharT, CharTraits > & i,
                T ( & array ) [ N ] )

{
return input_range ( i, array, array + N, array_input_operator ( ) ) ;
}



// *** CONST_CSTRING_INPUT_STREAMBUF ***


template < class CharT, class CharTraits = char_traits < CharT > >
class const_cstring_input_streambuf :
  public basic_streambuf < CharT, CharTraits >

{
private:

  using typename basic_streambuf < CharT, CharTraits > :: int_type ;
  using typename basic_streambuf < CharT, CharTraits > :: pos_type ;
  using typename basic_streambuf < CharT, CharTraits > :: off_type ;

  const CharT * begin ;
  const CharT * current ;
  const CharT * end ;

  pos_type seekoff ( off_type off,
                     ios_base :: seekdir way,
                     ios_base :: openmode which ) ;

  pos_type seekpos ( pos_type sp,
                     ios_base :: openmode which ) ;

  streamsize showmanyc ( ) ;
  int_type underflow ( ) ;
  int_type uflow ( ) ;
  int_type pbackfail ( int_type c ) ;

public:

  explicit const_cstring_input_streambuf ( const CharT * s ) :
    begin ( s ),
    current ( s ),
    end ( s + CharTraits :: length ( s ) )
    { assert ( s != 0 ) ; }

} ;


//

template < class CharT, class CharTraits >
typename const_cstring_input_streambuf < CharT, CharTraits > :: pos_type
  const_cstring_input_streambuf < CharT, CharTraits > ::
    seekoff ( typename const_cstring_input_streambuf < CharT, CharTraits > ::
                         off_type off,
              ios_base :: seekdir way,
              ios_base :: openmode which )

{
if ( ( which & ios_base :: in ) == 0 )
  return off_type ( -1 ) ;

off_type min_off,
         max_off ;

const CharT * new_current ;

switch ( way )
  {
  case ios_base :: beg:

    min_off = 0 ;
    max_off = end - begin ;
    new_current = begin + off ;
    break ;

  case ios_base :: cur:

    min_off = begin - current ;
    max_off = end - current ;
    new_current = current + off ;
    break ;

  case ios_base :: end:

    min_off = begin - end ;
    max_off = 0 ;
    new_current = end + off ;
    break ;

  default:

    return off_type ( -1 ) ;

  }

if ( off < min_off  ||  off > max_off )
  return off_type ( -1 ) ;

current = new_current ;
return current - begin ;
}


//

template < class CharT, class CharTraits >
typename const_cstring_input_streambuf < CharT, CharTraits > :: pos_type
  const_cstring_input_streambuf < CharT, CharTraits > ::
    seekpos ( typename const_cstring_input_streambuf < CharT, CharTraits > ::
                         pos_type sp,
              ios_base :: openmode which )

{
if ( ( which & ios_base :: in ) == 0  ||  sp < 0  ||  sp > end - begin )
  return off_type ( -1 ) ;

current = begin + sp ;
return sp ;
}


//

template < class CharT, class CharTraits >
streamsize const_cstring_input_streambuf < CharT, CharTraits > :: showmanyc ( )

{
return end - current ;
}


//

template < class CharT, class CharTraits >
typename const_cstring_input_streambuf < CharT, CharTraits > :: int_type
  const_cstring_input_streambuf < CharT, CharTraits > :: underflow ( )

{
return   current == end
       ? CharTraits :: eof ( )
       : CharTraits :: to_int_type ( * current ) ;
}


//

template < class CharT, class CharTraits >
typename const_cstring_input_streambuf < CharT, CharTraits > :: int_type
  const_cstring_input_streambuf < CharT, CharTraits > :: uflow ( )

{
return   current == end
       ? CharTraits :: eof ( )
       : CharTraits :: to_int_type ( * current ++ ) ;
}


//

template < class CharT, class CharTraits >
typename const_cstring_input_streambuf < CharT, CharTraits > :: int_type
  const_cstring_input_streambuf < CharT, CharTraits > ::
    pbackfail ( typename const_cstring_input_streambuf
                           < CharT, CharTraits > :: int_type c )

{
return       current == begin
         ||  ( c != CharTraits :: eof ( )  &&  c != * ( current - 1 ) )
       ? CharTraits :: eof ( )
       : CharTraits :: to_int_type ( * -- current ) ;
}



// *** CSTRING_CTR ***


template < class T, class CharT >
T cstring_ctr ( const CharT * s )

{
const_cstring_input_streambuf < CharT > sb ( s ) ;
basic_istream < CharT > i ( & sb ) ;
T result ;
i >> result ;
return result ;
}



#endif
