#ifndef NODEPP_NODEPP
#define NODEPP_NODEPP

/*────────────────────────────────────────────────────────────────────────────*/

#include "import.h"
#include "task.h"

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace process {

    array_t<string_t> args; int threads = 0;

    /*─······································································─*/

    ulong size(){ 
        return process::poll::size() + 
               process::task::size() + 
               process::loop::size() + 
               process::threads      ; 
    }
    
    /*─······································································─*/

    void start( int argc, char** args ){
        int i=0; do {
            process::args.push(args[i]);
        }   while( i ++< argc - 1 );
    }

    /*─······································································─*/

    int next(){
        static int x = 0;   
    coStart

        x = process::task::size(); while( x-->0 ){ process::task::next(); coNext; }
        x = process::loop::size(); while( x-->0 ){ process::loop::next(); coNext; }
        x = process::poll::size(); while( x-->0 ){ process::poll::next(); coNext; }

    coStop
    }
    
    /*─······································································─*/

    template< class... T >
    void add( const T&... args ){ process::loop::add( args... ); }

    /*─······································································─*/

    template< class T >
    void error( T& ev, const string_t& msg ){ _EERROR( ev, msg ); }

    void error( const string_t& msg ){ _ERROR( msg ); }

    /*─······································································─*/

    template< class T, class... V > 
    void await( T cb, const V&... args ){
        while( cb( args... ) >= 0 )
             { next(); }
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

    void pipe(){
        while( !process::empty() )
                process::next();
    }

}}

/*────────────────────────────────────────────────────────────────────────────*/

#endif