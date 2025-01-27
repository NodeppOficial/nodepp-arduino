/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_ENCODER
#define NODEPP_ENCODER
#define BASE8  "0123456789abcdef"
#define BASE64 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

/*────────────────────────────────────────────────────────────────────────────*/

#include "string.h"
#include "utf.h"

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace encoder { namespace key {

    string_t generate( const string_t& alph, int x=32 ) { 
        string_t data ( (ulong)x, '\0' ); while( x --> 0 ){
            data[x] = alph[ rand() % ( alph.size() - 1 ) ];
        }   return data;
    }

    string_t generate( int x=32 ) { 
        string_t data ( (ulong)x, '\0' ); while( x --> 0 ){
            data[x] = (char)( rand() % 0xFF );
        }   return data;
    }

}}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace encoder {
    
    ulong hash( const string_t& key, int tableSize ) {
        ulong hash = 5381; forEach( x, key ) {
              hash = ((hash << 5) + hash) + x;
        }     return hash % tableSize;
    }
    
    /*─······································································─*/

    ulong hash() { int x= sizeof(ulong) * 8; 
            ulong  data = 0; while( x --> 0 ){
            data = data <<1 | ( data | rand() % 2 );
        }   return data;
    }
    
    /*─······································································─*/

    ulong hash( int key, int tableSize ) { return key % tableSize; }
    
}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace encoder { namespace XOR {

    string_t get( string_t data, const string_t& key ){
        auto  tmp = data.copy();
        ulong pos = 0; forEach( x, tmp ) {
            x = x ^ key[pos]; pos++;
            pos %= key.size();
        }   return tmp;
    }

    string_t set( string_t data, const string_t& key ){
        auto  tmp = data.copy();
        ulong pos = 0; forEach( x, tmp ) {
            x = x ^ key[pos]; pos++;
            pos %= key.size();
        }   return tmp;
    }

}}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace encoder { namespace bytes {

    template< class T >
    ptr_t<uchar> get( T num ){
        ptr_t<uchar> out ( sizeof(num), 0 );
        for( ulong y=0; y<out.size(); y++ ){
             out[y] = num >> ( 8*(out.size()-y-1) );
        }    return out;
    }

    template< class T >
    T set( const ptr_t<uchar>& num ){ T out;
      for( ulong y=0; y<num.size(); y++ ){
           out = out << 8 | num[y];
      }    return out;
    }

}}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace encoder { namespace bin {

    template< class T >
    ptr_t<bool> get( T num ){
        ptr_t<bool> out ( sizeof(num) * 8, 0 );
        for ( auto x=sizeof(num)*8; x--; ){
              out[x] = num & 1 ; num >>= 1;
        }     return out;
    }

    template< class T >
    T set( const ptr_t<bool>& num ){ T out = 0;
        if  ( num.empty() ){ return out; }
        for ( auto& x : num ){
              out = out << 1 | ( x & 1 );
        }     return out;
    }

}}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace encoder { namespace hex {

    template< class T, class = typename type::enable_if<type::is_integral<T>::value,T>::type >
    string_t get( T num ){ string_t out; do {
             out.unshift( BASE8[num&(T)(0xf)] ); num >>= 4;
        } while( num != 0 ); if( out.size()%2!=0 ){
             out.unshift( '0' );
        } return out;
    }

    template< class T, class = typename type::enable_if<type::is_integral<T>::value,T>::type >
    T set( string_t num ){ if ( num.empty() ){ return 0; } 
        T out = 0; for ( auto c: num ){    out  = out<<4;
              if ( c >= '0' && c <= '9' ){ out |= c - '0'     ; } 
            elif ( c >= 'a' && c <= 'f' ){ out |= c - 'a' + 10; } 
            elif ( c >= 'A' && c <= 'F' ){ out |= c - 'A' + 10; } 
            else { return 0; }
        }   return out;
    }
    
    string_t get( const ptr_t<uchar>& inp ){
        if ( inp.empty() ){ return nullptr; }
        queue_t<char> out; for( auto x : inp ){
            for( auto y: get(x) ){ out.push( y ); }
        }   out.push('\0'); return string_t( out.data() );
    }

    ptr_t<uchar> set( string_t x ){
        if ( x.empty() ){ return nullptr; }
        ulong size = x.size()/2 + ( x.size()%2 != 0?1:0 ); 
        ptr_t<uchar> out(size,'\0'); for( auto &y : out ){
            y = set<uchar>( x.splice(0,2) );
        }   return out;
    }

}}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace encoder { namespace buffer {

    string_t hex2buff( const string_t& inp ){
        if( inp.empty() ){ return nullptr; }
        ptr_t<uchar> buff = hex::set(inp);
        string_t raw ( buff.size() + 1 );
        memcpy( raw.get(), &buff, buff.size() );
        return raw;
    }

    string_t buff2hex( const string_t& inp ){
        if( inp.empty() ){ return nullptr; } 
        auto raw = ptr_t<uchar>( inp.size() );
        memcpy( &raw, inp.get(), inp.size() );
        return hex::get( raw );
    }

}}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace encoder { namespace base64 {

    string_t get( const string_t &in ) {

        queue_t<char> out; int pos1 = 0, pos2 = -6;

        for ( uchar c: in ) {
            pos1= ( pos1 << 8 ) + c; pos2 += 8;
            while ( pos2 >= 0 ) {
                out.push(BASE64[(pos1>>pos2)&0x3F]);
                pos2 -= 6;
            }
        }

        if (pos2>-6) out.push(BASE64[((pos1<<8)>>(pos2+8))&0x3F]);
        while (out.size()%4){ out.push('='); } 
        
        out.push('\0'); return string_t( out.data() );
    }

    string_t set( const string_t &in ) {

        queue_t<char> out; int pos1=0, pos2=-8;
        array_t<int> T( 256, -1 );

        for ( int i=0; i<64; i++ ) T[BASE64[i]] = i;
        for ( uchar c: in ) { if ( T[c]==-1 ) break;
            pos1 = ( pos1 << 6 ) + T[c]; pos2 += 6;
            if (pos2 >= 0) {
                out.push(char((pos1>>pos2)&0xFF));
                pos2 -= 8;
            }
        }

        out.push('\0'); return string_t( out.data() );
    }

}}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace encoder { namespace utf8 {
    ptr_t<uint16> to_utf16( ptr_t<uint8> inp ){ return utf::utf8_to_utf16( inp ); }
    ptr_t<uint32> to_utf32( ptr_t<uint8> inp ){ return utf::utf8_to_utf32( inp ); }
}}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace encoder { namespace utf16 {
    ptr_t<uint8>  to_utf8 ( ptr_t<uint16> inp ){ return utf::utf16_to_utf8 ( inp ); }
    ptr_t<uint32> to_utf32( ptr_t<uint16> inp ){ return utf::utf16_to_utf32( inp ); }
}}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace encoder { namespace utf32 {
    ptr_t<uint8>  to_utf8 ( ptr_t<uint32> inp ){ return utf::utf32_to_utf8 ( inp ); }
    ptr_t<uint16> to_utf16( ptr_t<uint32> inp ){ return utf::utf32_to_utf16( inp ); }
}}}

/*────────────────────────────────────────────────────────────────────────────*/

#undef BASE64
#undef BASE8
#endif