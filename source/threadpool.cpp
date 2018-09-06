// Copyright Ivan Stanojevic 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#include "threadpool.h"

#ifdef __linux__
#include <unistd.h>
#endif



// *** THREAD_POOL ***


//

void thread_pool :: worker :: main ( )

{
#ifdef __linux__

nice ( 10 ) ;

#endif

unique_lock < mutex > lck ( mtx ) ;

for ( ; ; )
  switch ( state )
    {
    case idle:

      cond_var.wait ( lck ) ;
      break ;

    case running:

      action ( ) ;
      action = function < void ( ) > ( ) ;
      state = idle ;
      pd -> put_free ( this ) ;
      break ;

    case terminating:

      return ;

    }
}
