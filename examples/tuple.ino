#include <node++.h>
#include <node++/tuple.h>

using namespace nodepp;

void _Ready() { 
    console::start(9600);

    tuple_t< int, float, string_t > tp ( 10, 10.50, "hello world!" );

    console::log( type::get<0>(tp) );
    console::log( type::get<1>(tp) );
    console::log( type::get<2>(tp) );    

}