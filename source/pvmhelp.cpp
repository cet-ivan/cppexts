// Copyright Ivan Stanojevic 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)



#include "pvmhelp.h"

#include <signal.h>

#include "cstring.h"



// *** PVM_HELPER ***


#ifdef PVM_SIGNAL_HANDLING

//

volatile bool pvm_helper :: signal_received_ = false ;


//

void pvm_helper :: signal_handler ( int )

{
signal_received_ = true ;
}

#endif


//

int pvm_helper :: my_task_id_ = 0 ;


//

pvm_helper :: initializer pvm_helper :: init ;


//

pvm_helper :: initializer :: initializer ( )

{
#ifdef PVM_SIGNAL_HANDLING

struct sigaction sa ;
memset ( & sa, 0, sizeof ( struct sigaction ) ) ;
sa.sa_handler = signal_handler ;
sigemptyset ( & sa.sa_mask ) ;
sa.sa_flags = SA_RESTART ;

if ( sigaction ( SIGTERM, & sa, nullptr ) != 0 )
  throw signal_setup_error ( ) ;

#endif

my_task_id_ = pvm_mytid ( ) ;

if ( my_task_id_ < 0 )
  throw pvm_error ( ) ;
}


//

pvm_helper :: initializer :: ~initializer ( )

{
pvm_exit ( ) ;
}
