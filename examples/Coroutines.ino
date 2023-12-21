#include <node++/node++.h>

using namespace nodepp;

void _Ready() { console::start(9600);

    process::loop::add([=](){ static int itr = 10;
    _Start
        while( itr --> 0 ){
            console::done(" Coroutine 1:",itr); 
            _Next;
        }
    _Stop
    });

    process::loop::add([=](){ static int itr = 10;
    _Start
        while( itr --> 0 ){
            console::error("Coroutine 2:",itr);
            _Next;
        }
    _Stop
    });

}
