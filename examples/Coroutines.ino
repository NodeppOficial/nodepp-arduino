#include <node++.h>

using namespace nodepp;

void _Ready() { console::start(9600);

    process::loop::add([=](){ static int itr = 10;
        _Start

        while( itr --> 0 ){
            console::done(" Process 1:",itr); _Yield(1);
        }

        _End
    });

    process::loop::add([=](){ static int itr = 10;
        _Start

        while( itr --> 0 ){
            console::error("Process 2:",itr); _Yield(1);
        }

        _End
    });

}