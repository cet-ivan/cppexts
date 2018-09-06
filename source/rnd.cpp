// Copyright Ivan Stanojevic 2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#include "rnd.h"



// *** SYSTEM_RND_STATIC_GENERATOR ***


//

spinlock system_rnd_static_generator :: sl ;


//

system_rnd_static_generator :: initializer system_rnd_static_generator :: init ;
