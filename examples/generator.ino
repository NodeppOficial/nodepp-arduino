#include <node++.h>

using namespace nodepp;

using namespace nodepp;

_Generator( process_1 ) {
    int counter = 100;
    _Emit(){ _Start
        while( counter-->0 ){
            console::done(" :>",counter);
            _Next;
        }
    _Stop }
};

_Generator( process_2 ) {
    int counter = 100;
    _Emit(){ _Start
        while( counter-->0 ){
            console::done(" :>",counter);
            _Next;
        }
    _Stop }
};

void _Ready() {
    console::start(9600);
    process_1 A; process_2 B;
    process::loop::add(A);
    process::loop::add(B);
}
