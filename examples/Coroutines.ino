#include <nodepp.h>

using namespace nodepp;

onMain([](){

    process::loop::add([=](){ static int itr = 10;
    coStart
        while( itr --> 0 ){
            console::done(" Coroutine 1:",itr); 
            coNext;
        }
    coStop
    });

    process::loop::add([=](){ static int itr = 10;
    coStart
        while( itr --> 0 ){
            console::error("Coroutine 2:",itr);
            coNext;
        }
    coStop
    });

})