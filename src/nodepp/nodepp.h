/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_NODEPP
#define NODEPP_NODEPP

/*────────────────────────────────────────────────────────────────────────────*/

#include "import.h"

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace process {

    template< class... T >
    void error( const T&... msg ){ _ERROR( msg... ); }

    /*─······································································─*/

    void stop(){
        while( !process::empty() ){
                process::next();
        }
    }

}}

/*────────────────────────────────────────────────────────────────────────────*/

#endif