#ifndef NODEPP_COROUTINE
#define NODEPP_COROUTINE

/*────────────────────────────────────────────────────────────────────────────*/

template< class T > T clamp( const T& val, const T& _min, const T& _max ){ return max( _min, min( _max, val ) ); }

/*────────────────────────────────────────────────────────────────────────────*/

#define _Return(VALUE) do { _state_ = _LINE; return VALUE; case _LINE:; } while (0)
#define _Next          do { _state_ = _LINE; return 1;     case _LINE:; } while (0)
#define _Again         do { _state_ = _LINE; return 0;     case _LINE:; } while (0)
#define _Goto(VALUE)   do { _state_ = VALUE; return 1;                  } while (0)
#define _Yield(VALUE)  do { _state_ = VALUE; return 1;     case VALUE:; } while (0)

/*────────────────────────────────────────────────────────────────────────────*/

#define _EError( Ev, message ) if ( Ev.empty() ){ console::error(message); exit(1); } \
                               else Ev.emit( except_t( message ) );

#define _Error( MESSAGE ) console::error ( MESSAGE );

/*────────────────────────────────────────────────────────────────────────────*/

#define _Start static int _state_ = 0; { switch(_state_) { case 0:;
#define _End   do { _state_ = 0; return -1; } while (0)
#define _Stop     } _state_ = 0; return -1; }
#define _Emit  int operator()

/*────────────────────────────────────────────────────────────────────────────*/

#define _GStart { switch(_state_){ case 0:;
#define _GStop  } _state_ = 0; return -1; }

/*────────────────────────────────────────────────────────────────────────────*/

#define _main_ _init_(); void setup(){ \
   console::start( 9600 ); _init_(); \
} void loop(){ process::next(); \
} void _init_

/*────────────────────────────────────────────────────────────────────────────*/

#define _Generator(NAME) struct NAME : public NODEPP_GENERATOR_BASE
#define _Set(VALUE)      _state_     = VALUE
#define _Get             _state_

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
#define TIMEOUT    3

/*────────────────────────────────────────────────────────────────────────────*/

#define typeof(DATA) (string_t){ typeid( DATA ).name() }

struct NODEPP_GENERATOR_BASE { protected:
   bool _available_ = 1;
   int  _state_     = 0;
};

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

#define forEver() for (;;)

#define elif else if

/*────────────────────────────────────────────────────────────────────────────*/

#define _FUNC  __PRETTY_FUNCTION__
#define _NAME  __FUNCTION__
#define _DATE  __DATE__
#define _FILE  __FILE__
#define _LINE  __LINE__
#define _TIME  __TIME__

/*────────────────────────────────────────────────────────────────────────────*/

#endif
