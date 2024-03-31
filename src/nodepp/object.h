
/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.nodepp.xyz/license.html
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_OBJECT
#define NODEPP_OBJECT

/*────────────────────────────────────────────────────────────────────────────*/

#include "any.h"
#include "initializer.h"

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace { 

    template< class T > struct obj_type_id                   { static constexpr int value = 0x0000 |  0; };

    template<>          struct obj_type_id<int>              { static constexpr int value = 0x0000 |  1; };
    template<>          struct obj_type_id<uint>             { static constexpr int value = 0x0000 |  2; };
    template<>          struct obj_type_id<bool>             { static constexpr int value = 0x0000 |  3; };
    template<>          struct obj_type_id<char>             { static constexpr int value = 0x0000 |  4; };
    template<>          struct obj_type_id<long>             { static constexpr int value = 0x0000 |  5; };
    template<>          struct obj_type_id<short>            { static constexpr int value = 0x0000 |  6; };
    template<>          struct obj_type_id<uchar>            { static constexpr int value = 0x0000 |  7; };
    template<>          struct obj_type_id<llong>            { static constexpr int value = 0x0000 |  8; };
    template<>          struct obj_type_id<ulong>            { static constexpr int value = 0x0000 |  9; };
    template<>          struct obj_type_id<ushort>           { static constexpr int value = 0x0000 | 10; };
    template<>          struct obj_type_id<ullong>           { static constexpr int value = 0x0000 | 11; };

    template<>          struct obj_type_id<wchar_t>          { static constexpr int value = 0x0000 | 12; };
    template<>          struct obj_type_id<char16_t>         { static constexpr int value = 0x0000 | 13; };
    template<>          struct obj_type_id<char32_t>         { static constexpr int value = 0x0000 | 14; };

    template<>          struct obj_type_id<float>            { static constexpr int value = 0x0000 | 15; };
    template<>          struct obj_type_id<double>           { static constexpr int value = 0x0000 | 16; };
    template<>          struct obj_type_id<ldouble>          { static constexpr int value = 0x0000 | 17; };
    
    template<>          struct obj_type_id<string_t>         { static constexpr int value = 0x0000 | 18; };
    template< ulong N > struct obj_type_id<char[N]>          { static constexpr int value = 0x0000 | 18; };
    template<>          struct obj_type_id<char*>            { static constexpr int value = 0x0000 | 18; };

    template< class T >          struct obj_type_id<T*>      { static constexpr int value = 0xf000 | obj_type_id<T>::value; };
    template< class T, ulong N > struct obj_type_id<T[N]>    { static constexpr int value = 0xf100 | obj_type_id<T>::value; };

    template< class T > struct obj_type_id<ptr_t<T>>         { static constexpr int value = 0xf200 | obj_type_id<T>::value; };
    template< class T > struct obj_type_id<array_t<T>>       { static constexpr int value = 0xf300 | obj_type_id<T>::value; };
    template< class T > struct obj_type_id<initializer_t<T>> { static constexpr int value = 0xf400 | obj_type_id<T>::value; };

}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { class object_t {
private:

    using T     = type::pair<string_t,object_t>;
    using ARRAY = array_t<T>;

protected: 

    struct NODE {
        int   type;
        any_t  mem;
    };  ptr_t<NODE> obj;

public:

    template< ulong N > 
    object_t( const T (&arr) [N] ) noexcept : obj(new NODE()) { 
        ARRAY mem (N); for( ulong x=N; x--; ){ mem[x] = arr[x]; } 
        obj->mem = mem; obj->type = 20;
    }

    template< class U > 
    object_t( const U& any ) noexcept : obj(new NODE()) { 
        obj->mem = any; obj->type = obj_type_id<U>::value;
    }
    
    object_t() noexcept : obj( new NODE() ) {}

    /*─······································································─*/

    template< class U >
    explicit operator U() const noexcept { return obj->mem.get<U>(); }

    object_t& operator[]( const string_t& name ) const noexcept {
        auto mem = obj->mem.get<ARRAY>();

        for( ulong x=0; x<mem.size(); x++ ){
         if( mem[x].first == string::to_string(name) )
             return mem[x].second;
        }    T item ({ name, 0 }); mem.push( item ); 
        
        obj->mem = mem; obj->type = 20;
        return mem[mem.last()].second;
    }

    /*─······································································─*/

    array_t<string_t> keys() const noexcept { array_t<string_t> res;
        if( obj->type == 20 ){ auto mem = obj->mem.get<ARRAY>();
            mem.map([&]( T item ){ res.push( item.first ); });
        }   return res;
    }

    int get_type_id() const noexcept { return obj->type; }

    /*─······································································─*/

    void erase( const string_t& name ) const noexcept {
        auto mem = obj->mem.get<ARRAY>();

        for( ulong x=0; x<mem.size(); x++ ) {
         if( mem[x].first == string::to_string(name) )
             mem.erase( x );
        } 

    }

    void erase() noexcept { obj = new NODE() ; }
    
};}

/*────────────────────────────────────────────────────────────────────────────*/

#endif