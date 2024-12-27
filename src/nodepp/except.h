/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_EXCEPT
#define NODEPP_EXCEPT

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { class except_t { 
protected: 

    struct NODE { 
        string_t msg;
        void *ev = nullptr;
    };  ptr_t<NODE> obj;

public:

    virtual ~except_t() noexcept { }
    
    except_t() noexcept : obj( new NODE() ) {}

    /*─······································································─*/

    template< class T, class = typename type::enable_if<type::is_class<T>::value,T>::type >
    except_t( const T& except_type ) noexcept : obj(new NODE()) {
        obj->msg = except_type.what();
    }

    /*─······································································─*/

    template< class... T >
    except_t( const T&... msg ) noexcept : obj(new NODE()) {
        obj->msg = string::join( " ", msg... );
    }

    /*─······································································─*/

    except_t( const string_t& msg ) noexcept : obj(new NODE()) {
        obj->msg = msg;
    }


    /*─······································································─*/

    const char* what() const noexcept { return obj->msg.c_str(); }
    operator char*() const noexcept { return (char*)what(); }
    void print() const noexcept { console::error(obj->msg); } 

};}

/*────────────────────────────────────────────────────────────────────────────*/

#endif