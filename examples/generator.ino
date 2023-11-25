#include <node++.h>

using namespace nodepp;

_Generator( process_1 ) {
    int counter = 100;
    _Emit(int)

    while( counter-->0 ){
        console::done(" :>",counter);
        _Return( counter );
    }

    _Stop
};

_Generator( process_2 ) {
    int counter = 100;
    _Emit(int)

    while( counter-->0 ){
        console::error(":>",counter);
        _Return( counter );
    }

    _Stop
};

void _Ready() {
    console::start(9600);
    process_1 A; process_2 B;
    while( A()>0 && B()>0 ){}
}
