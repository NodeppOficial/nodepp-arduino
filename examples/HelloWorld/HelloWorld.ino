#include <nodepp.h>
#include <nodepp/timer.h>

using namespace nodepp;

onMain([](){

    timer::interval([](){
        console::log("hello world");
    }, 100 );

})