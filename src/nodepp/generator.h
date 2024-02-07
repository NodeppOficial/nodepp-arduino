#define NODEPP_GENERATOR

#if !defined(GENERATOR_TIMER) && defined(NODEPP_TIMER)
    #define  GENERATOR_TIMER
namespace nodepp { namespace _timer_ {

    GENERATOR( timer ){ public:

        template< class V, class... T > 
        gnEmit( V func, const ptr_t<ulong>& out, ulong time, const T&... args ){
        gnStart
            if(*out == 0 )                   coEnd;
            if( process::millis() <= *out )  coGoto(0);
            if ( func(args...)<0 )           coEnd;
            *out = process::millis() + time; coGoto(0); 
        gnStop
        }

        template< class V, class... T > 
        gnEmit( V func, const ptr_t<ulong>& out, ulong* time, const T&... args ){
        gnStart
            do { if(*out == 0 ) {  coEnd; }   coNext;
               } while( process::millis() <= *out ); 
            if ( func(args...)<0 ){ coEnd; }
            *out = process::millis() + *time; coGoto(0); 
        gnStop
        }

    };
    
    /*─······································································─*/

    GENERATOR( utimer ){ public:

        template< class V, class... T > 
        gnEmit( V func, const ptr_t<ulong>& out, ulong time, const T&... args ){
        gnStart
            do { if(*out == 0 ) {  coEnd; }   coNext;
               } while( process::micros() <= *out ); 
            if ( func(args...)<0 ){ coEnd; }
            *out = process::micros() + time;  coGoto(0); 
        gnStop
        }

        template< class V, class... T > 
        gnEmit( V func, const ptr_t<ulong>& out, ulong* time, const T&... args ){
        gnStart
            do { if(*out == 0 ) {  coEnd; }   coNext;
               } while( process::micros() <= *out ); 
            if ( func(args...)<0 ){ coEnd; } 
            *out = process::micros() + *time; coGoto(0);
        gnStop
        }

    };

}}
#undef NODEPP_GENERATOR
#endif

/*────────────────────────────────────────────────────────────────────────────*/
