#include <nodepp.h>
#include <nodepp/timer.h>

using namespace nodepp;

void onMain(){

    auto t = timer::interval([=](){ 
        static int i=0; i++; i%=1000;
        console::done(" interval every: 1 second - ",i," seconds");
    },1000);

    timer::timeout([=](){
        console::error("timeout after: 10 seconds ");
        timer::clear(t);
    },10000);

}