#include <node++/node++.h>
#include <node++/event.h>
#include <node++/timer.h>

using namespace nodepp;

event_t<> ev; 

void _Ready() {
  console::start(9600);

  timer::timeout([=](){ ev.emit(); },1000);

  ev.on([](){ console::log("hello world"); });

  console::log("before event");

}
