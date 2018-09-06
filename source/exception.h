// Copyright Ivan Stanojevic 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __EXCEPTION_H

#define __EXCEPTION_H



#include <exception>



using std :: exception ;
using std :: bad_exception ;
using std :: nested_exception ;

using std :: unexpected_handler ;
using std :: get_unexpected ;
using std :: set_unexpected ;
using std :: unexpected ;

using std :: terminate_handler ;
using std :: get_terminate ;
using std :: set_terminate ;
using std :: terminate ;

using std :: uncaught_exception ;

using std :: exception_ptr ;

using std :: current_exception ;
using std :: rethrow_exception ;
using std :: make_exception_ptr ;

using std :: throw_with_nested ;
using std :: rethrow_if_nested ;



#endif
