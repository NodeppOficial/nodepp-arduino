/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.nodepp.xyz/license.html
 */

/*────────────────────────────────────────────────────────────────────────────*/

#define NODEPP_GENERATOR

#if !defined(GENERATOR_TIMER) && defined(NODEPP_TIMER) && defined(NODEPP_GENERATOR)
    #define  GENERATOR_TIMER
namespace nodepp { namespace _timer_ {

    GENERATOR( timer ){ public:

        template< class V, class... T > 
        gnEmit( V func, const ptr_t<int>& out, ulong time, ptr_t<ulong> stm, const T&... args ){
        gnStart
            if(*out == 0 )                   coEnd;
            if( process::millis() <= *stm )  coGoto(0);
            if( func(args...)<0 )            coEnd;
            *stm = process::millis() + time; coGoto(0); 
        gnStop
        }

        template< class V, class... T > 
        gnEmit( V func, const ptr_t<int>& out, ulong* time, ptr_t<ulong> stm, const T&... args ){
        gnStart
            if(*out == 0 )                   coEnd;
            if( process::millis() <= *stm )  coGoto(0);
            if( func(args...)<0 )            coEnd;
            *stm = process::millis() +*time; coGoto(0); 
        gnStop
        }

    };
    
    /*─······································································─*/

    GENERATOR( utimer ){ public:

        template< class V, class... T > 
        gnEmit( V func, const ptr_t<int>& out, ulong time, ptr_t<ulong> stm, const T&... args ){
        gnStart
            if(*out == 0 )                   coEnd;
            if( process::micros() <= *stm )  coGoto(0);
            if( func(args...)<0 )            coEnd;
            *stm = process::micros() + time; coGoto(0);
        gnStop
        }

        template< class V, class... T > 
        gnEmit( V func, const ptr_t<int>& out, ulong* time, ptr_t<ulong> stm, const T&... args ){
        gnStart
            if(*out == 0 )                   coEnd;
            if( process::micros() <= *stm )  coGoto(0);
            if( func(args...)<0 )            coEnd;
            *stm = process::micros() +*time; coGoto(0);
        gnStop
        }

    };

}}  
#undef NODEPP_GENERATOR
#endif

/*────────────────────────────────────────────────────────────────────────────*/
