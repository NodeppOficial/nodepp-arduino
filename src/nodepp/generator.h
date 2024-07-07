/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#define NODEPP_GENERATOR

#if !defined(GENERATOR_TIMER) && defined(NODEPP_TIMER) && defined(NODEPP_GENERATOR)
    #define  GENERATOR_TIMER
namespace nodepp { namespace _timer_ {

    GENERATOR( timer ){ public:

        template< class V, class... T > 
        gnEmit( V func, ulong time, const T&... args ){
        gnStart
            coDelay( time ); if( func(args...)<0 )
            { coEnd; } coGoto(0); 
        gnStop
        }

        template< class V, class... T > 
        gnEmit( V func, ulong* time, const T&... args ){
        gnStart
            coDelay( *time ); if( func(args...)<0 )
            { coEnd; } coGoto(0); 
        gnStop
        }

    };
    
    /*─······································································─*/

    GENERATOR( utimer ){ public:

        template< class V, class... T > 
        gnEmit( V func, ulong time, const T&... args ){
        gnStart
            coUDelay( time ); if( func(args...)<0 )
            { coEnd; } coGoto(0);
        gnStop
        }

        template< class V, class... T > 
        gnEmit( V func, ulong* time, const T&... args ){
        gnStart
            coUDelay( *time ); if( func(args...)<0 )
            { coEnd; } coGoto(0);
        gnStop
        }

    };

}}  
#undef NODEPP_GENERATOR
#endif

/*────────────────────────────────────────────────────────────────────────────*/
