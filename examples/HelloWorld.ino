#include <nodepp.h>
#include <nodepp/timer.h>

using namespace nodepp;

void onMain(){

    timer::interval([](){
        console::log("hello world");
    }, 100 );

}