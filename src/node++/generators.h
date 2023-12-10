#if !defined(GENERATOR_FILE) && defined(NODEPP_STREAM)
    #define  GENERATOR_FILE
namespace nodepp { namespace _file_ {

    _Generator( read ){ public: 

        ulong*   r; int c;
        string_t y;
        ulong dist;

    template< class T > _Emit( T* str, ulong size=CHUNK_SIZE ){
    _Start c=0; y = str->get_borrow(); str->del_borrow(); str->flush();

        if( !str->is_available() ){ str->close(); y.clear(); _End; } r = str->get_range();

        if( r[1] != 0 ){ auto pos = str->pos(); dist = r[1]-r[0];
             if( pos < r[0] ){ str->del_borrow(); str->pos( r[0] ); }
        else if( pos >=r[1] ){ str->close(); _End; }
        } else { dist = size; }

        do{ if( !y.empty() ){ break; } if( c==-2 ){ _Next; }
          auto act = clamp( size, dist, str->get_buffer_size() );
                 c = str->_read( str->get_buffer_data(), act );
        } while( c == -2 );

        if( c<=0 && y.empty() ){ str->close(); _End; } else if( c>0 ){
            y+= (string_t){ str->get_buffer_data(), (ulong) c };
        }   c = y.size();

    _Stop
    }};
    
    /*─······································································─*/

    _Generator( write ){ public:

        ulong    y; 
        int      c;
        ulong size;
        
    template< class T > _Emit( T* str, const string_t& msg ){
    _Start c=0; y=0; str->flush();

        if(!str->is_available() || msg.empty() )
          { str->close(); _End; }

        if( str->get_borrow().empty() ){ str->set_borrow(msg); }

        do{ while(( c=str->_write( str->get_borrow_data(), str->get_borrow_size() ))==-2 )
                 { _Next; } str->get_borrow().splice(0,c); y+=c;
        }   while( c>=0 && !str->get_borrow().empty() ); 

               if( c<=0 ){ str->close(); _End; }

    _Stop
    }};

    /*─······································································─*/

    _Generator( line ){ public: 
    
        _file_::read prs;
        string_t s,y;  
        ulong      c; 

    template< class T > _Emit( T* str ){
    _Start s.clear(); y.clear(); c=1;

        while( str->is_available() ){
        while( prs(str) == 1 ){ _Next; }
           if( prs.c<=0 ){ break; } c=1; s += prs.y; 
          for( auto x:s ){ if( x == '\n' ){ break; } c++; }
           if( c<=s.size() ){ break; }
        }      str->set_borrow(s);
        
        y = str->get_borrow().splice( 0, c );
    
    _Stop
    }};

}}
#endif

/*────────────────────────────────────────────────────────────────────────────*/

#if !defined(GENERATOR_ENCODE) && defined(NODEPP_ENCODE)
    #define  GENERATOR_ENCODE 
namespace nodepp { namespace _encode_ {

    _file_::write _write;
    _file_::read  _read;

    char *ibff, *obfp; 
    ulong ibfz, obfz; 
    ulong result;

    char     obff;
    string_t data;
    iconv_t  ctx;

    _Generator(pipe) { public:
        
        template< class T, class V, class U >
        _Emit( string_t from, string_t to, const T& inp, const V& out, ulong mult=1 ){
        _Start  ctx = iconv_open( to.data(), from.data() ); 

            if( ctx == (iconv_t)-1 ){
                _onError(inp.onError,"can't open a encode context");
                _onError(out.onError,"can't open a encode context"); _End;
            }

            while( inp.is_available() && out.is_available() ){
            while( _read(&inp)==1 ){ _Next; }
               if( _read.c <= 0 )  { break; }

                obff = ptr_t<char>( _read.y.size() * mult );
                ibff = data.data(); ibfz = _read.y.size();
                obfz = obff.size(); obfp = &obff;
                
                result = iconv( ctx, (char**)&ibff, &ibfz, &obfp, &obfz );

                if( result == (ulong)-1 ){

                    if( errno == EINVAL ) {
                        string_t message = "Input conversion stopped due to an incomplete character or shift sequence at the end of the input buffer.";
                        _onError(inp.onError,message);
                        _onError(out.onError,message); break;
                    }

                    else if( errno == EILSEQ ) {
                        string_t message = "Input conversion stopped due to an input byte that does not belong to the input codeset.";
                        _onError(inp.onError,message);
                        _onError(out.onError,message); break;
                    }

                    else if( errno == E2BIG ) {
                        string_t message = "Input conversion stopped due to lack of space in the output buffer.";
                        _onError(inp.onError,message);
                        _onError(out.onError,message); break;
                    }

                    else if( errno == EBADF ) {
                        string_t message = "The cd argument is not a valid open conversion descriptor";
                        _onError(inp.onError,message);
                        _onError(out.onError,message); break;
                    }

                    else {
                        string_t message = "can't encode correctly";
                        _onError(inp.onError,message);
                        _onError(out.onError,message); break;
                    }

                } else {
                    string_t info = (string_t){ &obff, obff.size() }; 
                    out.write( info ); inp.onData.emit( info ); 
                }

            }   iconv_close(ctx); out.close(); inp.close();

        _Stop
        }
        
        template< class T, class V, class U >
        _Emit( string_t from, string_t to, const T& inp, ulong mult=1 ){
        _Start  ctx = iconv_open( to.data(), from.data() ); 

            if( ctx == (iconv_t)-1 ){
                _onError(inp.onError,"can't open a encode context"); _End;
            }

            while( inp.is_available() ){
            while( _read(&inp)==1 ){ _Next; }
               if( _read.c <= 0 )  { break; }

                obff = ptr_t<char>( _read.y.size() * mult );
                ibff = data.data(); ibfz = _read.y.size();
                obfz = obff.size(); obfp = &obff;
                
                result = iconv( ctx, (char**)&ibff, &ibfz, &obfp, &obfz );

                if( result == (ulong)-1 ){

                    if( errno == EINVAL ) {
                        string_t message = "Input conversion stopped due to an incomplete character or shift sequence at the end of the input buffer.";
                        _onError(inp.onError,message); break;
                    }

                    else if( errno == EILSEQ ) {
                        string_t message = "Input conversion stopped due to an input byte that does not belong to the input codeset.";
                        _onError(inp.onError,message); break;
                    }

                    else if( errno == E2BIG ) {
                        string_t message = "Input conversion stopped due to lack of space in the output buffer.";
                        _onError(inp.onError,message); break;
                    }

                    else if( errno == EBADF ) {
                        string_t message = "The cd argument is not a valid open conversion descriptor";
                        _onError(inp.onError,message); break;
                    }

                    else {
                        string_t message = "can't encode correctly";
                        _onError(inp.onError,message); break;
                    }

                } else {
                    string_t info = (string_t){ &obff, obff.size() }; 
                    inp.onData.emit( info ); 
                }

            }   iconv_close(ctx); inp.close();

        _Stop
        }

    };

}}
#endif

/*────────────────────────────────────────────────────────────────────────────*/

#if !defined(GENERATOR_ZLIB) && defined(NODEPP_ZLIB)
    #define  GENERATOR_ZLIB 
namespace nodepp { namespace _zlib_ {

    _Generator( inflate ){ public:
    
        ptr_t<z_stream> str = new z_stream;
        int x=0; ulong size; string_t dout;
        _file_::write _write;
        _file_::read  _read;
        

        template< class T, class V, class U >
        _Emit( const T& inp, const V& out, U cb ){
        _Start inp.onPipe.emit();

            str->zfree    = Z_NULL;
            str->zalloc   = Z_NULL;
            str->opaque   = Z_NULL;
            str->next_in  = Z_NULL;
            str->avail_in = Z_NULL;

            if( cb( &str ) != Z_OK ){ 
                string_t message = "Failed to initialize zlib for compression.";
                _onError( inp.onError, message );
                _onError( inp.onError, message ); _End;
            }

            while( inp.is_available() && out.is_available() ){
            while( _read(&inp)==1 ){ _Next; }
               if( _read.c <= 0 )  { break; }

                str->avail_in = _read.y.size();
                str->avail_out= inp.get_buffer_size();
                str->next_in  = (Bytef*)_read.y.data();
                str->next_out = (Bytef*)inp.get_buffer_data(); 
                            x = ::inflate( &str, Z_FINISH );

                if(( size=inp.get_buffer_size()-str->avail_out )>0){
                    dout = (string_t){ inp.get_buffer_data(), size };
                    inp.onData.emit(dout);
                    while( _write(&out,dout)==1 ){ _Next; } continue;
                }
                
                if( x==Z_STREAM_END ) { break; } else if( x < 0 ){ 
                    string_t message = string::format("ZLIB: %s",str->msg);
                    _onError( inp.onError, message );
                    _onError( out.onError, message ); break;
                }
            
            }   inflateEnd( &str ); out.close(); inp.close(); _Stop

        }

        template< class T, class U >
        _Emit( const T& inp, U cb ){
        _Start inp.onPipe.emit();

            str->zfree    = Z_NULL;
            str->zalloc   = Z_NULL;
            str->opaque   = Z_NULL;
            str->next_in  = Z_NULL;
            str->avail_in = Z_NULL;

            if( cb( &str ) != Z_OK ){ 
                string_t message = "Failed to initialize zlib for compression.";
                _onError( inp.onError, message ); _End;
            }

            while( inp.is_available() ){
            while( _read(&inp)==1 ){ _Next; }
               if( _read.c <= 0 )  { break; }

                str->avail_in = _read.y.size();
                str->avail_out= inp.get_buffer_size();
                str->next_in  = (Bytef*)_read.y.data();
                str->next_out = (Bytef*)inp.get_buffer_data(); 
                            x = ::inflate( &str, Z_PARTIAL_FLUSH );

                if(( size=inp.get_buffer_size()-str->avail_out )>0){
                    dout = (string_t){ inp.get_buffer_data(), size };
                    inp.onData.emit(dout); continue;
                }

                if( x==Z_STREAM_END ) { break; } else if( x < 0 ){ 
                    string_t message = string::format("ZLIB: %s",str->msg);
                    _onError( inp.onError, message ); inp.close(); break;
                } 

            }   inflateEnd( &str ); inp.close(); _Stop

        }

    };
    
    /*─······································································─*/

    _Generator( deflate ){ public:
    
        ptr_t<z_stream> str = new z_stream;
        int x=0; ulong size; string_t dout;
        _file_::write _write;
        _file_::read  _read;
        

        template< class T, class V, class U >
        _Emit( const T& inp, const V& out, U cb ){
        _Start inp.onPipe.emit();

            str->zfree    = Z_NULL;
            str->zalloc   = Z_NULL;
            str->opaque   = Z_NULL;
            str->next_in  = Z_NULL;
            str->avail_in = Z_NULL;

            if( cb( &str ) != Z_OK ){ 
                string_t message = "Failed to initialize zlib for compression.";
                _onError( inp.onError, message );
                _onError( inp.onError, message ); _End;
            }

            while( inp.is_available() && out.is_available() ){
            while( _read(&inp)==1 ){ _Next; }
               if( _read.c <= 0 )  { break; }

                str->avail_in = _read.y.size();
                str->avail_out= inp.get_buffer_size();
                str->next_in  = (Bytef*)_read.y.data();
                str->next_out = (Bytef*)inp.get_buffer_data(); 
                            x = ::deflate( &str, Z_PARTIAL_FLUSH );

                if(( size=inp.get_buffer_size()-str->avail_out )>0){
                    dout = (string_t){ inp.get_buffer_data(), size };
                    inp.onData.emit(dout);
                    while( _write(&out,dout)==1 ){ _Next; } continue;
                }

                if( x==Z_STREAM_END ) { break; } else if( x < 0 ){ 
                    string_t message = string::format("ZLIB: %s",str->msg);
                    _onError( inp.onError, message );
                    _onError( out.onError, message ); break;
                }
            
            }   deflateEnd( &str ); out.close(); inp.close(); _Stop

        }

        template< class T, class U >
        _Emit( const T& inp, U cb ){
        _Start inp.onPipe.emit();

            str->zfree    = Z_NULL;
            str->zalloc   = Z_NULL;
            str->opaque   = Z_NULL;
            str->next_in  = Z_NULL;
            str->avail_in = Z_NULL;

            if( cb( &str ) != Z_OK ){ 
                string_t message = "Failed to initialize zlib for compression.";
                _onError( inp.onError, message ); _End;
            }

            while( inp.is_available() ){
            while( _read(&inp)==1 ){ _Next; }
               if( _read.c <= 0 )  { break; }

                str->avail_in = _read.y.size();
                str->avail_out= inp.get_buffer_size();
                str->next_in  = (Bytef*)_read.y.data();
                str->next_out = (Bytef*)inp.get_buffer_data(); 
                            x = ::deflate( &str, Z_PARTIAL_FLUSH );

                if(( size=inp.get_buffer_size()-str->avail_out )>0){
                    dout = (string_t){ inp.get_buffer_data(), size };
                    inp.onData.emit(dout); continue;
                }
                
                if( x==Z_STREAM_END ) { break; } else if( x < 0 ){ 
                    string_t message = string::format("ZLIB: %s",str->msg);
                    _onError( inp.onError, message ); inp.close(); break;
                } 

            }   deflateEnd( &str ); inp.close(); _Stop

        }

    };

}}
#endif

/*────────────────────────────────────────────────────────────────────────────*/

#if !defined(GENERATOR_STREAM) && defined(NODEPP_STREAM)
    #define  GENERATOR_STREAM 
namespace nodepp { namespace _stream_ {

    _Generator( pipe ){ public:

        _file_::write _write;
        _file_::read  _read;

        template< class T > _Emit( const T& inp ){
        _Start inp.onPipe.emit();
            while( inp.is_available() ){
            while( _read(&inp)==1 ){ _Next; } 
               if( _read.c <= 0 )  { break; }
                inp.onData.emit( _read.y );
            }   inp.close();
        _Stop
        }

        template< class T, class V > _Emit( const T& inp, const V& out ){
        _Start inp.onPipe.emit();
            while( inp.is_available() && out.is_available() ){
            while( _read(&inp)==1 )         { _Next; } 
               if( _read.c <= 0 )           { break; }
                inp.onData.emit( _read.y );
            while( _write(&out,_read.y)==1 ){ _Next; }
            }   inp.close(); out.close();
        _Stop
        }

    };
    
    /*─······································································─*/

    _Generator( line ){ public:

        _file_::write _write;
        _file_::line  _read;

        template< class T > _Emit( const T& inp ){
        _Start inp.onPipe.emit();
            while( inp.is_available() ){
            while( _read(&inp)==1 ){ _Next; } 
               if( _read.c <= 0 )  { break; }
                inp.onData.emit( _read.y );
            }   inp.close();
        _Stop
        }

        template< class T, class V > _Emit( const T& inp, const V& out ){
        _Start inp.onPipe.emit();
            while( inp.is_available() && out.is_available() ){
            while( _read(&inp)==1 )         { _Next; } 
               if( _read.c <= 0 )           { break; }
                inp.onData.emit( _read.y );
            while( _write(&out,_read.y)==1 ){ _Next; }
            }   inp.close(); out.close();
        _Stop
        }

    };
    
}}
#endif

/*────────────────────────────────────────────────────────────────────────────*/

#if !defined(GENERATOR_TIMER) && defined(NODEPP_TIMER)
    #define  GENERATOR_TIMER
namespace nodepp { namespace _timer_ {

    _Generator( timer ){ public:

        ulong stamp = 0;

        template< class V, class... T > 
        _Emit( V func, ptr_t<int> out, ulong time, T... args ){
        _Start stamp = process::millis() + time; _Next;
            do { if(*out <= 0 )                   {  _End; }
                 if( process::millis() >= stamp ) { break; } _Next;
            } while( true ); if( func(args...)<0 ){  _End; } _Goto(0); 
        _Stop
        }

        template< class V, class... T > 
        _Emit( V func, ptr_t<int> out, ulong* time, T... args ){
        _Start stamp = process::millis() +*time; _Next;
            do { if(*out <= 0 )                   {  _End; }
                 if( process::millis() >= stamp ) { break; } _Next;
            } while( true ); if( func(args...)<0 ){  _End; } _Goto(0); 
        _Stop
        }

    };
    
    /*─······································································─*/

    _Generator( utimer ){ public:

        ulong stamp = 0;

        template< class V, class... T > 
        _Emit( V func, ptr_t<int> out, ulong time, T... args ){
        _Start stamp = process::micros() + time; _Next;
            do { if(*out <= 0 )                   {  _End; }
                 if( process::micros() >= stamp ) { break; } _Next;
            } while( true ); if( func(args...)<0 ){  _End; } _Goto(0); 
        _Stop
        }

        template< class V, class... T > 
        _Emit( V func, ptr_t<int> out, ulong* time, T... args ){
        _Start stamp = process::micros() +*time; _Next;
            do { if(*out <= 0 )                   {  _End; }
                 if( process::micros() >= stamp ) { break; } _Next;
            } while( true ); if( func(args...)<0 ){  _End; } _Goto(0); 
        _Stop
        }

    };

}}
#endif
