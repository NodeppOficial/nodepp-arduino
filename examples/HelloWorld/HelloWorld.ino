#include <nodepp.h>
#include <nodepp/timer.h>

using namespace nodepp;

void _main_() {

    timer::interval([](){
        console::log("hello world");
    }, 100 );

}