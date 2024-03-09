/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.nodepp.xyz/license.html
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_COROUTINE
#define NODEPP_COROUTINE

/*────────────────────────────────────────────────────────────────────────────*/

template< class T > T clamp( const T& val, const T& _min, const T& _max ){ return max( _min, min( _max, val ) ); }

/*────────────────────────────────────────────────────────────────────────────*/

#define _EERROR( Ev, message ) if ( Ev.empty() ){ console::error(message); } \
                               else Ev.emit( except_t( message ) );

#define _ERROR( MESSAGE ) console::error ( MESSAGE );

/*────────────────────────────────────────────────────────────────────────────*/

#define coReturn(VALUE) do { _state_ = _LINE_; return VALUE; case _LINE_:; } while (0)
#define coNext          do { _state_ = _LINE_; return 1;     case _LINE_:; } while (0)
#define coAgain         do { _state_ = _LINE_; return 0;     case _LINE_:; } while (0)
#define coGoto(VALUE)   do { _state_ = VALUE ; return 1;                   } while (0)
#define coYield(VALUE)  do { _state_ = VALUE ; return 1;     case VALUE:;  } while (0)

/*────────────────────────────────────────────────────────────────────────────*/

#define coStart static int _state_ = 0; { switch(_state_) { case 0:;
#define coEnd     do { _state_ = 0; return -1; } while (0)
#define coStop       } _state_ = 0; return -1; }
#define coSet(VALUE)   _state_ = VALUE
#define coGet          _state_

/*────────────────────────────────────────────────────────────────────────────*/

#define GENERATOR(NAME) struct NAME : public NODEPP_GENERATOR_BASE
#define gnStart    { switch(_state_) { case 0:;
#define gnStop     } _state_ = 0;  return -1; }
#define gnEmit       int operator()

/*────────────────────────────────────────────────────────────────────────────*/

#define onMain( ... ) void setup(){   \
   Serial.begin( 9600 );              \
   function_t<void>( __VA_ARGS__ )(); \
}  void loop(){ process::next(); }

/*────────────────────────────────────────────────────────────────────────────*/

#define CHUNK_TB( VALUE ) ( 1024 * 1024 * 1024 * 1024 * VALUE )
#define CHUNK_GB( VALUE ) ( 1024 * 1024 * 1024 * VALUE )
#define CHUNK_MB( VALUE ) ( 1024 * 1024 * VALUE )
#define CHUNK_KB( VALUE ) ( 1024 * VALUE )
#define CHUNK_B( VALUE )  ( VALUE )

/*────────────────────────────────────────────────────────────────────────────*/

#define CHUNK_SIZE 512
#define UNBFF_SIZE 256
#define MAX_SOCKET 10
#define TIMEOUT    1

/*────────────────────────────────────────────────────────────────────────────*/

struct NODEPP_GENERATOR_BASE { protected: int _state_ = 0; };

#define typeof(DATA) (string_t){ typeid( DATA ).name() }

#define ullong  unsigned long long int
#define ulong   unsigned long int
#define llong   long long int
#define ldouble long double

#define ushort  unsigned short
#define uchar   unsigned char
#define uint    unsigned int
#define wchar   wchar_t

/*────────────────────────────────────────────────────────────────────────────*/

#define forEach( ITEM, CB ) for( auto& x : ITEM ){ CB( x ); }
#define function( ... ) [=]( __VA_ARGS__ )
#define forEver() for (;;)
#define elif else if

/*────────────────────────────────────────────────────────────────────────────*/

#define _FUNC_  __PRETTY_FUNCTION__
#define _NAME_  __FUNCTION__
#define _DATE_  __DATE__
#define _FILE_  __FILE__
#define _LINE_  __LINE__
#define _TIME_  __TIME__

/*────────────────────────────────────────────────────────────────────────────*/

#endif
