// Copyright Ivan Stanojevic 2023.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __REGEX_H

#define __REGEX_H



#include <regex>



namespace regex_constants = std :: regex_constants ;

using std :: regex_error ;

using std :: regex_traits ;

using std :: basic_regex ;
using std :: regex ;
using std :: wregex ;

using std :: sub_match ;
using std :: csub_match ;
using std :: wcsub_match ;
using std :: ssub_match ;
using std :: wssub_match ;

using std :: match_results ;
using std :: cmatch ;
using std :: wcmatch ;
using std :: smatch ;
using std :: wsmatch ;

using std :: regex_match ;
using std :: regex_search ;
using std :: regex_replace ;

using std :: regex_iterator ;
using std :: cregex_iterator ;
using std :: wcregex_iterator ;
using std :: sregex_iterator ;
using std :: wsregex_iterator ;

using std :: regex_token_iterator ;
using std :: cregex_token_iterator ;
using std :: wcregex_token_iterator ;
using std :: sregex_token_iterator ;
using std :: wsregex_token_iterator ;

using std :: operator == ;
using std :: operator != ;
using std :: operator < ;
using std :: operator > ;
using std :: operator <= ;
using std :: operator >= ;

using std :: operator << ;

using std :: swap ;




#endif
