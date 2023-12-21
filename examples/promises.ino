#include <node++.h>
#include <timer.h>
#include <promise.h>

using namespace nodepp;

void _Ready() { 
    console::start(9600);

    auto t = timer::add([](){
        static int i=0; i++;
        console::log("new interval",i);
        return ( i >= 20 ) ? -1 : 1 ;
    }, 1000 );

    promise::resolve<int>([=]( function_t<void,int> res ){
        timer::timeout([=](){ res(10); },1000);
    },[=]( int res ){
        console::log("first promise resolved:",res);
    });

    int res = promise::await<int>([=]( function_t<void,int> res ){
        timer::timeout([=](){ res(20); },5000);
    });

    console::log("second promise resolved:",res);

    int rej = promise::await<int>([=]( function_t<void,int> res ){
        timer::timeout([=](){ res(30); },10000);
    });

    console::log("wait for it"); timer::delay( 5000 );

    console::log("third promise resolved:",rej );

}