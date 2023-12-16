
/*────────────────────────────────────────────────────────────────────────────*/


/*────────────────────────────────────────────────────────────────────────────*/

#if !defined(GENERATOR_TIMER) && defined(NODEPP_TIMER)
    #define  GENERATOR_TIMER
namespace nodepp { namespace _timer_ {

    $Generator( timer ){ public:

        template< class V, class... T > 
        $Emit( const V& func, const ptr_t<ulong>& out, ulong time, const T&... args ){
        $Start
            if(*out == 0 )                    $End;
            if( process::millis() <= *out )  $Goto(0);
            if ( func(args...)<0 )            $End;
            *out = process::millis() + time; $Goto(0); 
        $Stop
        }

        template< class V, class... T > 
        $Emit( const V& func, const ptr_t<ulong>& out, ulong* time, const T&... args ){
        $Start
            do { if(*out == 0 ) {  $End; } $Next;
               } while( process::millis() <= *out ); 
            if ( func(args...)<0 ){ $End; }
            *out = process::millis() + *time; $Goto(0); 
        $Stop
        }

    };
    
    /*─······································································─*/

    $Generator( utimer ){ public:

        template< class V, class... T > 
        $Emit( const V& func, const ptr_t<ulong>& out, ulong time, const T&... args ){
        $Start
            do { if(*out == 0 ) {  $End; } $Next;
               } while( process::micros() <= *out ); 
            if ( func(args...)<0 ){ $End; }
            *out = process::micros() + time; $Goto(0); 
        $Stop
        }

        template< class V, class... T > 
        $Emit( const V& func, const ptr_t<ulong>& out, ulong* time, const T&... args ){
        $Start
            do { if(*out == 0 ) {  $End; } $Next;
               } while( process::micros() <= *out ); 
            if ( func(args...)<0 ){ $End; } 
            *out = process::micros() + *time; $Goto(0);
        $Stop
        }

    };

}}
#endif
