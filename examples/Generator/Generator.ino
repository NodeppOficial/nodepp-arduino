#include <nodepp.h>

using namespace nodepp;

_Generator( process_1 ) {
    int counter = 100;
    _Emit(){ 
    _GStart
        while( counter-->0 ){
            console::done(" :>",counter);
            _Next;
        }
    _GStop }
};

_Generator( process_2 ) {
    int counter = 100;
    _Emit(){ 
    _GStart
        while( counter-->0 ){
            console::done(" :>",counter);
            _Next;
        }
    _GStop }
};

void _main_() {
    process_1 A; process_2 B;
    process::loop::add(A);
    process::loop::add(B);
}
