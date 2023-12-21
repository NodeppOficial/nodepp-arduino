#define led LED_BUILTIN

#include <node++.h>
#include <timer.h>

using namespace nodepp;

void _Ready() {
    IO::mode( led, OUTPUT );

    timer::interval([](){
        static bool b = 0; b=!b;
        IO::digital::write( led, b );
    },1000);

}