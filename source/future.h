// Copyright Ivan Stanojevic 2023.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __FUTURE_H

#define __FUTURE_H



#include <future>



using std :: future_errc ;
using std :: launch ;
using std :: future_status ;

using std :: is_error_code_enum ;
using std :: make_error_code ;
using std :: make_error_condition ;

using std :: future_category ;
using std :: future_error ;

using std :: promise ;

using std :: future ;
using std :: shared_future ;

using std :: packaged_task ;

using std :: swap ;

using std :: uses_allocator ;

using std :: async ;



// *** EXTENSIONS ***


//

template < class T >
inline bool is_ready ( const future < T > & f )

{
return f.wait_for ( chrono :: seconds ( 0 ) ) == future_status :: ready ;
}



#endif
