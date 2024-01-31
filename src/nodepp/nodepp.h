#ifndef NODEPP_NODEPP
#define NODEPP_NODEPP

/*────────────────────────────────────────────────────────────────────────────*/

#include "import.h"
#include "task.h"

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace process {

    array_t<string_t> args; int threads = 0;
    
    /*─······································································─*/

    template< class... T >
    void add( const T&... args ){ process::loop::add( args... ); }
    
    /*─······································································─*/

    ulong size(){ 
        return process::poll::size() + 
               process::task::size() + 
               process::loop::size() + 
               process::threads      ; 
    }
    
    /*─······································································─*/

    void clear(){ 
        process::task::clear();
        process::poll::clear(); 
        process::loop::clear(); 
        process::threads = 0; 
    }
    
    /*─······································································─*/

    bool empty(){ return ( 
        process::task::empty() && 
        process::poll::empty() && 
        process::loop::empty() && 
        process::threads < 1 
    ) ; }
    
    /*─······································································─*/

    void start( int argc, char** args ){
        int i=0; do {
            process::args.push(args[i]);
        }   while( i ++< argc - 1 );
    }

    /*─······································································─*/

    int next(){ 
        static uint x = 0;
    _Start

        while( x-->0 ){
            if( !process::task::empty() ){ process::task::next(); _Next; }
            if( !process::poll::empty() ){ process::poll::next(); _Next; }
            if( !process::loop::empty() ){ process::loop::next(); _Next; }
        }    x = process::size();

        #if _KERNEL != NODEPP_KERNEL_ARDUINO
            process::delay( TIMEOUT );
        #endif

    _Stop
    }
    
    /*─······································································─*/

    void pipe(){
        while( !process::empty() )
                process::next();
    }

}}

/*────────────────────────────────────────────────────────────────────────────*/

#endif
