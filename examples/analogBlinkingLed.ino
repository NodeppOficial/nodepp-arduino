#include <node++/node++.h>
#include <node++/timer.h>

using namespace nodepp;

ulong frq = 1000;
array_t<int> INP ({ 14 });
array_t<int> OUT ({ 13, 12 }); 

void _Ready() {
    
    for( auto x : OUT ) IO::mode( x, OUTPUT );
    for( auto x : INP ) IO::mode( x, INPUT );

    timer::interval([](){
        frq = IO::digital::read( INP[0] );
    },1);

    timer::interval([](){
        static bool b = 0; b=!b;
        IO::digital::write( OUT[0], b );
    }, &frq );

    timer::interval([](){
        static bool b = 0; b=!b;
        IO::digital::write( OUT[1], b );
    },500);

}