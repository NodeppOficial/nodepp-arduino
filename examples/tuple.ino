#include <node++.h>
#include <tuple.h>

using namespace nodepp;

void _Ready() { 
    console::start(9600);

    tuple_t< int, float, string_t > tp ( 10, 10.50, "hello world!" );

    console::log( tuple::get<0>(tp) );
    console::log( tuple::get<1>(tp) );
    console::log( tuple::get<2>(tp) );    

}
