#include <node++.h>
#include <node++/timer.h>

using namespace nodepp;

void _Ready() {
    console::start(9600);

    auto t = timer::interval([=](){ 
        static int i=0; i++; i%=1000;
        console::done(" interval every: 1 second - ",i," seconds");
    },1000);

    timer::timeout([=](){
        console::error("timeout after: 10 seconds ");
        timer::clear(t);
    },10000);

}