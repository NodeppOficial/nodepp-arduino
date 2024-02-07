#include <nodepp.h>

using namespace nodepp;

GENERATOR( process_1 ) {
    int counter = 100;
    gnEmit(){ 
    gnStart
        while( counter-->0 ){
            console::done(" :>",counter);
            coNext;
        }
    gnStop }
};

_Generator( process_2 ) {
    int counter = 100;
    gnEmit(){ 
    gnStart
        while( counter-->0 ){
            console::done(" :>",counter);
            coNext;
        }
    gnStop }
};

void _main_() {
    process_1 A; process_2 B;
    process::loop::add(A);
    process::loop::add(B);
}
