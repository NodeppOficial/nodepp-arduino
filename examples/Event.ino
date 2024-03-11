#include <nodepp.h>
#include <nodepp/event.h>

using namespace nodepp;

event_t<> Evento;
array_t<int> INP ({ 14 });
array_t<int> OUT ({ 12 }); 

onMain([](){
    
    for( auto x : OUT ) IO::mode( x, OUTPUT );
    for( auto x : INP ) IO::mode( x, INPUT );

    Evento.on([=](){
        static bool b=0; b=!b;
        IO::digital::write( OUT[0], b );
    });

    process::add([](){
    coStart
        while( IO::digital::read(INP[0])==0 )
             { coNext; } Evento.emit();
        while( IO::digital::read(INP[0])==1 )
             { coNext; } coGoto(0);
    coStop
    });
    
})