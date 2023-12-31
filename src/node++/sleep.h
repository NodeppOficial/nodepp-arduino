#ifndef NODEPP_SLEEP
#define NODEPP_SLEEP

/*────────────────────────────────────────────────────────────────────────────*/


namespace nodepp { namespace process {

    ulong seconds(){ return ::millis() / 1000; }

    ulong micros(){ return ::micros(); }

    ulong millis(){ return ::millis(); }

}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace process {

    void  delay( ulong time ){ ::delay( time ); }

    ulong now(){ return millis(); }

    void  yield(){ ::delay(0); }

}}

/*────────────────────────────────────────────────────────────────────────────*/

#endif
