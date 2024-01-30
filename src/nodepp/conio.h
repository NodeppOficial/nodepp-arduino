#ifndef NODEPP_CONIO
#define NODEPP_CONIO

/*────────────────────────────────────────────────────────────────────────────*/

#define C_BLACK   0
#define C_WHITE   1
#define C_GREEN   2
#define C_RED     3
#define C_BLUE    4
#define C_CYAN    5
#define C_YELLOW  6
#define C_MAGENTA 7
#define C_BOLD    10

/*────────────────────────────────────────────────────────────────────────────*/

namespace nodepp { namespace conio {

    int background( int color ){ 
        if( color >= 10 && color <= 17 ){ Serial.write("\033[1m"); color -= 10; }
        switch( color ) {
            case C_BLACK:   return Serial.write("\033[40m"); break;
            case C_WHITE:   return Serial.write("\033[47m"); break;
            case C_GREEN:   return Serial.write("\033[42m"); break;
            case C_RED:     return Serial.write("\033[41m"); break;
            case C_BLUE:    return Serial.write("\033[44m"); break;
            case C_CYAN:    return Serial.write("\033[46m"); break;
            case C_YELLOW:  return Serial.write("\033[43m"); break;
            case C_MAGENTA: return Serial.write("\033[45m"); break;
        }   return -1;
    }

    int foreground( int color ){
        if( color >= 10 && color <= 17 ){ Serial.write("\033[1m"); color -= 10; }
        switch( color ) {
            case C_BLACK:   return Serial.write("\033[30m"); break;
            case C_WHITE:   return Serial.write("\033[37m"); break;
            case C_GREEN:   return Serial.write("\033[32m"); break;
            case C_RED:     return Serial.write("\033[31m"); break;
            case C_BLUE:    return Serial.write("\033[34m"); break;
            case C_CYAN:    return Serial.write("\033[36m"); break;
            case C_YELLOW:  return Serial.write("\033[33m"); break;
            case C_MAGENTA: return Serial.write("\033[35m"); break;
        }   return -1;
    }

    /*─······································································─*/

    template< class V, class... T >
    int print( const V& argc, const T&... args ){ 
        Serial.write( (char*) string::format( (char*)argc, args... ) ); 
        return Serial.write("\033[0m"); 
    }
    
    int gotoxy( int x, int y ){ return print("\033[%d;%dH",x,y); }

    int undescore(){ return printf("\033[4m"); }

    int inverse(){ return printf("\033[7m"); }

    int reset(){ return printf("\033[0m"); }
    
    int clear(){ return printf("\033c"); }
    
    /*─······································································─*/

    int error( const char* msg ){ foreground( C_RED + C_BOLD ); return print( "%s", msg ); }

    int info( const char* msg ){ foreground( C_CYAN + C_BOLD ); return print( "%s", msg ); }

    int done( const char* msg ){ foreground( C_GREEN + C_BOLD ); return print( "%s", msg ); }

    int warn( const char* msg ){ foreground( C_YELLOW + C_BOLD ); return print( "%s", msg ); }

}}

/*────────────────────────────────────────────────────────────────────────────*/

#endif