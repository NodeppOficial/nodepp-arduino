#define led LED_BUILTIN

#include <nodepp.h>
#include <nodepp/timer.h>

using namespace nodepp;

onMain([](){

    IO::mode( led, OUTPUT );

    timer::interval([](){
        static bool b = 0; b=!b;
        IO::digital::write( led, b );
    },1000);

})