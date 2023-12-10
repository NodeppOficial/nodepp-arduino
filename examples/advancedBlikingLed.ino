#include <node++/node++.h>
#include <node++/timer.h>

using namespace nodepp;

void _Ready() {

    console::start(9600);

    queue_t<int> q ({ 13, 12, 11, 10 });

    q.map([]( int pin ){ 
        IO::mode( pin, OUTPUT ); 
    });

    timer::interval([=](){
        static auto p = q; p.next();

        int mode[2] = {       p.get()->data, 
            IO::digital::read(p.get()->data)
        };

        IO::digital::write( mode[0], !mode[1] );
        
    }, 100 );

}