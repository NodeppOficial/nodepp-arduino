#ifndef NODEPP_IO
#define NODEPP_IO

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace IO {

    template< class... T > void mode( const T&... args ){ return pinMode(args...); }
    
    /*─······································································─*/

    namespace tone {
        template< class... T > void on( const T&... args ){ ::tone(args...); }
        template< class... T > void off( const T&... args ){ ::noTone(args...); }
    }
    
    /*─······································································─*/

    namespace shift {
        template< class... T > void out( const T&... args ){ shiftOut(args...); }
        template< class... T > byte in( const T&... args ){ return shiftIn(args...); }
    }
    
    /*─······································································─*/

    namespace interrupt {
        template< class... T > void on(){ interrupts(); }
        template< class... T > void off(){ noInterrupts(); }
        template< class... T > void attach( const T&... args ){ attachInterrupt(args...); }
        template< class... T > void detach( const T&... args ){ detachInterrupt(args...); }
    }
    
    /*─······································································─*/

    namespace digital {
        template< class... T > int read( const T&... args ){ return digitalRead(args...); }
        template< class... T > void write( const T&... args ){ return digitalWrite(args...); }
    }
    
    /*─······································································─*/

    namespace duration {
        template< class... T > ulong in( const T&... args ){ return pulseIn(args...); }
        template< class... T > ulong inlong( const T&... args ){ return pulseInLong(args...); }
    }
    
    /*─······································································─*/

    namespace analog {
        template< class... T > int read( const T&... args ){ return analogRead(args...); }
        template< class... T > void write( const T&... args ){ return analogWrite(args...); }
        template< class... T > void reference( const T&... args ){ return analogReference(args...); }
        template< class... T > void set_read_resolution( const T&... args ){ return analogReadResolution(args...); }
        template< class... T > void set_write_resolution( const T&... args ){ return analogWriteResolution(args...); }
    }

}}

/*────────────────────────────────────────────────────────────────────────────*/

#endif