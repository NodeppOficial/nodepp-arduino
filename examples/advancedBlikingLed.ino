#include <node++/node++.h>
#include <node++/timer.h>

using namespace nodepp;

void _Ready() {
    console::start(9600);

    queue_t<int> q ({ 13, 12, 11, 10 });

    q.map([]( int pin ){ 
        pinMode( pin, OUTPUT ); 
    });

    timer::interval([=](){
        static auto p = q; p.next();

        int mode[2] = { p.get()->data, 
            digitalRead(p.get()->data)
        };

        digitalWrite( mode[0], !mode[1] );
        
    }, 100 );

}