#ifndef NODEPP_CONSOLE
#define NODEPP_CONSOLE

/*────────────────────────────────────────────────────────────────────────────*/

#include "iterator.h"
#include "conio.h"

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace console {

    template< class V, class... T >
    int scan( const V& argc, const T&... args ){ while(!Serial.available() ){}
        return string::parse( Serial.readString().c_str(), (char*)argc, args... );
    }

    template< class V, class... T >
    int pout( const V& argc, const T&... args ){
        return Serial.write( (char*) string::format( (char*)argc, args... ) );
    }

    template< class V, class... T >
    int perr( const V& argc, const T&... args ){
        return Serial.write( (char*) string::format( (char*)argc, args... ) );
    }

    /*─······································································─*/

    template< class... T >
    int log( const T&... args ){ 
        string::map([=]( string_t arg ){ 
            pout("%s ",(char*)arg); 
        },  args... ); 
            return pout("\n"); 
    }

    template< class... T >
    void start( const T&... args ){
        Serial.begin( args... );
    }

    int log(){ return pout("\n"); }

    void clear(){ conio::clear(); }
    
    /*─······································································─*/

    template< class... T >
    int warning( const T&... args ){ 
               conio::warn("WARNING: ");
        return log( args... ); 
    }

    template< class... T >
    int success( const T&... args ){ 
               conio::done("SUCCESS: ");
        return log( args... );  
    }

    template< class... T >
    int error( const T&... args ){ 
               conio::error("ERROR: "); 
        return log( args... ); 
    }

    template< class... T >
    int done( const T&... args ){ 
               conio::done("DONE: "); 
        return log( args... ); 
    }

    template< class... T >
    int info( const T&... args ){ 
               conio::info("INFO: "); 
        return log( args... ); 
    }

}}

/*────────────────────────────────────────────────────────────────────────────*/

#endif