
/*────────────────────────────────────────────────────────────────────────────*/


/*────────────────────────────────────────────────────────────────────────────*/

#if !defined(GENERATOR_TIMER) && defined(NODEPP_TIMER)
    #define  GENERATOR_TIMER
namespace nodepp { namespace _timer_ {

    _Generator( timer ){ public:

        ulong stamp = 0;

        template< class V, class... T > 
        _Emit( V func, ptr_t<int> out, ulong time, T... args ){
        _Start stamp = process::millis() + time; _Next;
            do { if(*out <= 0 )                   {  _End; }
                 if( process::millis() >= stamp ) { break; } _Next;
            } while( true ); if( func(args...)<0 ){  _End; } _Goto(0); 
        _Stop
        }

        template< class V, class... T > 
        _Emit( V func, ptr_t<int> out, ulong* time, T... args ){
        _Start stamp = process::millis() +*time; _Next;
            do { if(*out <= 0 )                   {  _End; }
                 if( process::millis() >= stamp ) { break; } _Next;
            } while( true ); if( func(args...)<0 ){  _End; } _Goto(0); 
        _Stop
        }

    };
    
    /*─······································································─*/

    _Generator( utimer ){ public:

        ulong stamp = 0;

        template< class V, class... T > 
        _Emit( V func, ptr_t<int> out, ulong time, T... args ){
        _Start stamp = process::micros() + time; _Next;
            do { if(*out <= 0 )                   {  _End; }
                 if( process::micros() >= stamp ) { break; } _Next;
            } while( true ); if( func(args...)<0 ){  _End; } _Goto(0); 
        _Stop
        }

        template< class V, class... T > 
        _Emit( V func, ptr_t<int> out, ulong* time, T... args ){
        _Start stamp = process::micros() +*time; _Next;
            do { if(*out <= 0 )                   {  _End; }
                 if( process::micros() >= stamp ) { break; } _Next;
            } while( true ); if( func(args...)<0 ){  _End; } _Goto(0); 
        _Stop
        }

    };

}}
#endif
