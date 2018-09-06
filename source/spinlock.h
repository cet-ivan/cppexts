// Copyright Ivan Stanojevic 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#ifndef __SPINLOCK_H

#define __SPINLOCK_H



#include "atomic.h"



// *** SPINLOCK ***


class spinlock

{
private:

  atomic_flag af ATOMIC_FLAG_INIT ;

public:

  void lock ( )
    { while ( af.test_and_set ( ) ) ; }

  bool try_lock ( )
    { return ! af.test_and_set ( ) ; }

  void unlock ( )
    { af.clear ( ) ; }

} ;



#endif
