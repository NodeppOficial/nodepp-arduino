/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.nodepp.xyz/license.html
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_NODEPP
#define NODEPP_NODEPP

/*────────────────────────────────────────────────────────────────────────────*/

#include "import.h"
#include "task.h"

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace process { int threads = 0;

    /*─······································································─*/

    ulong size(){ 
        return process::task::size() +
               process::threads      ; 
    }

    /*─······································································─*/

    int next(){
        static int x = 0;   
    coStart
        if( process::size() <= 0 ){ process::delay( TIMEOUT ); coGoto(0); }
        x = process::task::size(); while( x-->0 ){ process::task::next(); coNext; }
    coStop
    }
    
    /*─······································································─*/

    template< class... T >
    void* add( const T&... args ){ return process::task::add( args... ); }

    /*─······································································─*/

    template< class T >
    void error( const T&... msg ){ _ERROR( msg... ); }

    /*─······································································─*/

    template< class T, class... V > 
    void await( T cb, const V&... args ){
        while( cb( args... ) >= 0 )
             { next(); }
    }
    
    /*─······································································─*/

    void clear(){ 
        process::task::clear(); 
        process::threads = 0; 
    }

    void clear( void* address ){
         *((bool*)address) = 0;
    }
    
    /*─······································································─*/

    bool empty(){ return ( 
        process::task::empty() && 
        process::threads < 1 
    );}
    
    /*─······································································─*/

    void run(){
        while( !process::empty() )
                process::next();
    }

}}

/*────────────────────────────────────────────────────────────────────────────*/

#endif