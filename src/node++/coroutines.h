#ifndef NODEPP_COROUTINE
#define NODEPP_COROUTINE

/*────────────────────────────────────────────────────────────────────────────*/

template< class T > T clamp( const T& _min, const T& _max ){ return max( _min, min( _max, val ) ); }

/*────────────────────────────────────────────────────────────────────────────*/

#define _Ready loop(){ process::next(); } void setup

#define _Main _Ready

/*────────────────────────────────────────────────────────────────────────────*/

#define _Return(VALUE) do { _state_ = _Line; _Enable; return VALUE; case _Line:; } while (0)
#define _Next          do { _state_ = _Line; _Enable; return 1;     case _Line:; } while (0)
#define _Again         do { _state_ = _Line; _Enable; return 0;     case _Line:; } while (0)
#define _Goto(VALUE)   do { _state_ = VALUE; _Enable; return 1;                  } while (0)
#define _Yield(VALUE)  do { _state_ = VALUE; _Enable; return 1;     case VALUE:; } while (0)

/*────────────────────────────────────────────────────────────────────────────*/

#define _Start static int _state_ = 0; _Available { switch(_state_) { case 0:;
#define _End   do { _state_ = 0; _Enable; return -1; } while (0)
#define _Stop     } _state_ = 0; _Enable; return -1; }
#define _Emit  int operator()

/*────────────────────────────────────────────────────────────────────────────*/

#define _Available static bool _available_ = 1; if( _available_ ) return 1; _Disable;
#define _Disable     _available_ = 0
#define _Enable      _available_ = 1
#define _Set(VALUE)  _state_ = VALUE
#define _Get         _state_

/*────────────────────────────────────────────────────────────────────────────*/

#define CHUNK_TB( VALUE ) ( 1024 * 1024 * 1024 * 1024 * VALUE )
#define CHUNK_GB( VALUE ) ( 1024 * 1024 * 1024 * VALUE )
#define CHUNK_MB( VALUE ) ( 1024 * 1024 * VALUE )
#define CHUNK_KB( VALUE ) ( 1024 * VALUE )
#define CHUNK_B( VALUE )  ( VALUE )

/*────────────────────────────────────────────────────────────────────────────*/

#define MAX_SOCKET 1024
#define CHUNK_SIZE 1024
#define UNBFF_SIZE 1024
#define TIMEOUT    1

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { class NODEPP_GENERATOR { public: NODEPP_GENERATOR() {} }; }
#define _Generator(NAME) struct NAME : public nodepp::NODEPP_GENERATOR

/*────────────────────────────────────────────────────────────────────────────*/

#define _onError( Ev, message ) if( Ev.empty() ) \
                                  { console::error(message); exit(1); } \
                                else Ev.emit( except_t( message ) );

/*────────────────────────────────────────────────────────────────────────────*/

   #define _Error( MESSAGE ) console::error ( MESSAGE );

/*────────────────────────────────────────────────────────────────────────────*/

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

#define _Func  __PRETTY_FUNCTION__
#define _Name  __FUNCTION__
#define _Date  __DATE__
#define _File  __FILE__
#define _Line  __LINE__
#define _Time  __TIME__
/*────────────────────────────────────────────────────────────────────────────*/

#endif
