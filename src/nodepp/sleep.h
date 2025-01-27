/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_SLEEP
#define NODEPP_SLEEP

/*────────────────────────────────────────────────────────────────────────────*/


namespace nodepp { namespace process {

    ulong seconds(){ return ::millis() / 1000; }

    ulong micros(){ return ::micros(); }

    ulong millis(){ return ::millis(); }

}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace process {

    ulong now(){ return millis(); }

    void delay( ulong time ){ 
        if( time == 0 ){ return; }
        ::delay( time ); 
    }

    void  yield(){ delay(TIMEOUT); }

}}

/*────────────────────────────────────────────────────────────────────────────*/

#endif
