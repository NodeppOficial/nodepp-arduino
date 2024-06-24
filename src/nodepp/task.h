/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_TASK
#define NODEPP_TASK

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace process { 
    
    queue_t<function_t<int>> queue;

    void clear(){ queue.clear(); }

    ulong size(){ return queue.size(); }

    bool empty(){ return queue.empty(); }

    void clear( void* address ){ *((bool*)( address )) = 0; }

    template< class T, class... V >
    void* add( T cb, const V&... arg ){ 
        ptr_t<T>    clb = new T( cb );
        ptr_t<bool> blk = new bool(0);
        ptr_t<bool> out = new bool(1);
        queue.push([=](){ 
            if( *out==0 ){ return -1; }
            if( *blk==1 ){ return  1; } *blk = 1;
            int rs = (*clb) (arg...);   *blk = 0; 
            return *out==0 ? -1 : rs; 
        }); return (void*) &out;
    } 

    void next(){
        if( queue.empty() ){ process::delay( TIMEOUT ); return; } 
          auto x = queue.get(); int y = x->data();
          if ( y == 1 ){ queue.next( ); }
        elif ( y <  0 ){ queue.erase( x ); }
    }

    template< class T, class... V > 
    void await( T cb, const V&... args ){
        while( cb( args... ) >= 0 )
             { next(); }
    }
    
}}

/*────────────────────────────────────────────────────────────────────────────*/

#endif