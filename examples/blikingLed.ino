#define led LED_BUILTIN

#include <node++.h>
#include <node++/timer.h>

using namespace nodepp;

void _Ready() {
    pinMode( led, OUTPUT );

    timer::interval([](){
        static bool b = 0; b=!b;
        digitalWrite( led, b );
    },1000);

}