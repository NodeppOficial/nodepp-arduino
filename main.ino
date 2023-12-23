#include "node++/node++.h"
#include "node++/timer.h"

using namespace nodepp;

int OUT[] = { 12, 13 };

void _Ready() {

    for( auto x : OUT )
      IO::mode( x, OUTPUT );

    timer::interval([](){
      static bool b=0; b=!b;
      IO::digital::write( OUT[0], b );
    },100);

    timer::interval([](){
      static bool b=0; b=!b;
      IO::digital::write( OUT[1], b );
    },500);

}
