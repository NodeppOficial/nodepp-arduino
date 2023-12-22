
/*────────────────────────────────────────────────────────────────────────────*/


/*────────────────────────────────────────────────────────────────────────────*/

#if !defined(GENERATOR_TIMER) && defined(NODEPP_TIMER)
    #define  GENERATOR_TIMER
namespace nodepp { namespace _timer_ {

    _Generator( timer ){ public:

        template< class V, class... T > 
        _Emit( V func, const ptr_t<ulong>& out, ulong time, const T&... args ){
        _Start
            if(*out == 0 )                   _End;
            if( process::millis() <= *out )  _Goto(0);
            if ( func(args...)<0 )           _End;
            *out = process::millis() + time; _Goto(0); 
        _Stop
        }

        template< class V, class... T > 
        _Emit( V func, const ptr_t<ulong>& out, ulong* time, const T&... args ){
        _Start
            do { if(*out == 0 ) {  _End; }    _Next;
               } while( process::millis() <= *out ); 
            if ( func(args...)<0 ){ _End; }
            *out = process::millis() + *time; _Goto(0); 
        _Stop
        }

    };
    
    /*─······································································─*/

    _Generator( utimer ){ public:

        template< class V, class... T > 
        _Emit( V func, const ptr_t<ulong>& out, ulong time, const T&... args ){
        _Start
            do { if(*out == 0 ) {  _End; }   _Next;
               } while( process::micros() <= *out ); 
            if ( func(args...)<0 ){ _End; }
            *out = process::micros() + time; _Goto(0); 
        _Stop
        }

        template< class V, class... T > 
        _Emit( V func, const ptr_t<ulong>& out, ulong* time, const T&... args ){
        _Start
            do { if(*out == 0 ) {  _End; }   _Next;
               } while( process::micros() <= *out ); 
            if ( func(args...)<0 ){ _End; } 
            *out = process::micros() + *time; _Goto(0);
        _Stop
        }

    };

}}
#endif
