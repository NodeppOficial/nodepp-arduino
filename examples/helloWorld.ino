#include <node++.h>
#include <timer.h>

using namespace nodepp;

void _Ready() {
    console::start(9600);

    timer::interval([](){
        console::log("hello world");
    }, 100 );

}