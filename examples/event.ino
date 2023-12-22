#include "node++/node++.h"
#include "node++/timer.h"
#include "node++/event.h"

using namespace nodepp;

event_t<> Evento;
array_t<int> INP ({ 14 });
array_t<int> OUT ({ 13, 12 }); 

void _Ready() {
    
    for( auto x : OUT ) IO::mode( x, OUTPUT );
    for( auto x : INP ) IO::mode( x, INPUT );

    Evento.on([=](){
        static bool b=0; b=!b;
        IO::digital::write( OUT[0], b );
    });

    process::add([](){
    _Start
        while( IO::digital::read(INP[0])==0 )
          { _Next; } Evento.emit();
        while( IO::digital::read(INP[0])==1 )
          { _Next; } _Goto(0);
    _Stop
    });

    timer::interval([](){
        static bool b = 0; b=!b;
        IO::digital::write( OUT[1], b );
    },500);
    
}
