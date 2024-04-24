#include <nodepp.h>
#include <nodepp/timer.h>

using namespace nodepp;

void onMain(){
    
    timer::interval([=](){
        static int i = 0; i++; i%=1000;
        console::error("time interval 1 - ",i," seconds");
    },1000);
    
    timer::interval([=](){
        static int i = 0; i++; i%=1000;
        console::done(" time interval 2 - ",i," seconds");
    },500);

}