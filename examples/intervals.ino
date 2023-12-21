#include <node++.h>
#include <timer.h>

using namespace nodepp;

void _Ready() { console::start( 9600 );
    
    timer::interval([=](){
        static int i = 0; i++; i%=1000;
        console::error("time interval 1 - ",i," seconds");
    },1000);
    
    timer::interval([=](){
        static int i = 0; i++; i%=1000;
        console::done(" time interval 2 - ",i," seconds");
    },500);

}