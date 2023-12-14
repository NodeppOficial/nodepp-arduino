
/*────────────────────────────────────────────────────────────────────────────*/


/*────────────────────────────────────────────────────────────────────────────*/

#if !defined(GENERATOR_TIMER) && defined(NODEPP_TIMER)
    #define  GENERATOR_TIMER
namespace nodepp { namespace _timer_ {

    $Generator( timer ){ public:

        ulong stamp = 0;

        template< class V, class... T > 
        $Emit( const V& func, const ptr_t<int>& out, ulong time, const T&... args ){
        $Start stamp = process::millis() + time; $Next;
            do { if(*out <= 0 )                   {  $End; }
                 if( process::millis() >= stamp ) { break; } $Next;
            } while( true ); if( func(args...)<0 ){  $End; } $Goto(0); 
        $Stop
        }

        template< class V, class... T > 
        $Emit( const V& func, const ptr_t<int>& out, ulong* time, const T&... args ){
        $Start stamp = process::millis() +*time; $Next;
            do { if(*out <= 0 )                   {  $End; }
                 if( process::millis() >= stamp ) { break; } $Next;
            } while( true ); if( func(args...)<0 ){  $End; } $Goto(0); 
        $Stop
        }

    };
    
    /*─······································································─*/

    $Generator( utimer ){ public:

        ulong stamp = 0;

        template< class V, class... T > 
        $Emit( const V& func, const ptr_t<int>& out, ulong time, const T&... args ){
        $Start stamp = process::micros() + time; $Next;
            do { if(*out <= 0 )                   {  $End; }
                 if( process::micros() >= stamp ) { break; } $Next;
            } while( true ); if( func(args...)<0 ){  $End; } $Goto(0); 
        $Stop
        }

        template< class V, class... T > 
        $Emit( const V& func, const ptr_t<int>& out, ulong* time, const T&... args ){
        $Start stamp = process::micros() +*time; $Next;
            do { if(*out <= 0 )                   {  $End; }
                 if( process::micros() >= stamp ) { break; } $Next;
            } while( true ); if( func(args...)<0 ){  $End; } $Goto(0); 
        $Stop
        }

    };

}}
#endif
