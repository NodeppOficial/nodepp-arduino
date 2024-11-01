/*
 * Copyright 2023 The Nodepp Project Authors. All Rights Reserved.
 *
 * Licensed under the MIT (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://github.com/NodeppOficial/nodepp/blob/main/LICENSE
 */

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef NODEPP_COROUTINE
#define NODEPP_COROUTINE

/*────────────────────────────────────────────────────────────────────────────*/

template< class T > T clamp( const T& val, const T& _min, const T& _max ){ return max( _min, min( _max, val ) ); }

/*────────────────────────────────────────────────────────────────────────────*/

#define coDelay(VALUE)  do { static auto tm = process::millis()+VALUE; while( process::millis() < tm ){ coNext; } tm = process::millis()+VALUE; break; } while (0)
#define coUDelay(VALUE) do { static auto tm = process::micros()+VALUE; while( process::micros() < tm ){ coNext; } tm = process::micros()+VALUE; break; } while (0)
#define coWait(VALUE)   do { while( !VALUE ){ coNext; } } while(0)

/*────────────────────────────────────────────────────────────────────────────*/

#define coReturn(VALUE) do { _state_ = _LINE_; return VALUE; case _LINE_:; } while (0)
#define coNext          do { _state_ = _LINE_; return 1;     case _LINE_:; } while (0)
#define coAgain         do { _state_ = _LINE_; return 0;     case _LINE_:; } while (0)
#define coGoto(VALUE)   do { _state_ = VALUE ; return 1;                   } while (0)
#define coYield(VALUE)  do { _state_ = VALUE ; return 1;     case VALUE:;  } while (0)

/*────────────────────────────────────────────────────────────────────────────*/

#define _EERROR( Ev, ... ) if  ( Ev.empty() ){ console::error(__VA_ARGS__); } \
                           else{ Ev.emit( except_t(__VA_ARGS__) ); }
#define _ERROR( ... )      { console::error(__VA_ARGS__); exit(1); }

/*────────────────────────────────────────────────────────────────────────────*/

#define coStart static int _state_ = 0; { switch(_state_) { case 0:;
#define coEnd         do { _state_ = 0; return -1; } while (0)
#define coStop           } _state_ = 0; return -1; }
#define coSet(VALUE)       _state_ = VALUE
#define coGet              _state_

/*────────────────────────────────────────────────────────────────────────────*/

#define CHUNK_TB( VALUE ) ( 1024 * 1024 * 1024 * 1024 * VALUE )
#define CHUNK_GB( VALUE ) ( 1024 * 1024 * 1024 * VALUE )
#define CHUNK_MB( VALUE ) ( 1024 * 1024 * VALUE )
#define CHUNK_KB( VALUE ) ( 1024 * VALUE )
#define CHUNK_B( VALUE )  ( VALUE )

/*────────────────────────────────────────────────────────────────────────────*/

#define GENERATOR(NAME) struct NAME : public generator_t
#define gnStart { switch(_state_) { case 0:;
#define coEmit  int operator()
#define gnStop  coStop
#define gnEmit  coEmit

/*────────────────────────────────────────────────────────────────────────────*/

#define onMain loop(){ process::next(); } void setup

/*────────────────────────────────────────────────────────────────────────────*/

#define forEach( X, ITEM ) for( auto& X : ITEM )
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

#ifndef MAX_WORKERS
#define MAX_WORKERS 64
#endif

#ifndef MAX_EVENTS
#define MAX_EVENTS  64
#endif

#ifndef MAX_FILENO
#define MAX_FILENO  64
#endif

#ifndef MAX_TASKS
#define MAX_TASKS   64
#endif

/*────────────────────────────────────────────────────────────────────────────*/

#define CHUNK_SIZE 256
#define UNBFF_SIZE 128

/*────────────────────────────────────────────────────────────────────────────*/

#ifndef TIMEOUT
#define TIMEOUT 1
#endif

/*────────────────────────────────────────────────────────────────────────────*/

#define typeof(DATA) (string_t){ typeid( DATA ).name() }
struct generator_t { protected: int _state_ = 0; };

#define ullong  unsigned long long int
#define ulong   unsigned long int
#define llong   long long int
#define ldouble long double

#define ushort  unsigned short
#define uchar   unsigned char
#define uint    unsigned int
#define wchar   wchar_t

/*────────────────────────────────────────────────────────────────────────────*/

#endif
