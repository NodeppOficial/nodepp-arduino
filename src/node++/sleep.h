#ifndef NODEPP_SLEEP
#define NODEPP_SLEEP

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef ARDUINO
#include <sys/time.h>
using TIMEVAL = struct timeval;
#endif

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace process {

    array_t<string_t> args; int threads = 0;
    
    void udelay( ulong time ){ ::delayMicroseconds( time ); }

    void  delay( ulong time ){ ::delay( time ); }

    void  yield(){ ::delay(0); }

    ulong seconds(){ return ::millis() / 1000; }

    ulong micros(){ return ::micros(); }

    ulong millis(){ return ::millis(); }

    ulong now(){ return millis(); }

}}

/*────────────────────────────────────────────────────────────────────────────*/

#endif
