## Index

- [Nodepp](#nodepp)
- [Features](#features)
    - [Hello World](#hello-world)
    - [Smart Pointers](#smart-pointers)
        - [Basic Pointer](#basic-pointer)
        - [Array Pointer](#array-pointers)
        - [Overload Pointer](#overload-pointers)
    - [Array](#array)
    - [String](#string)
    - [Tasks](#tasks)
    - [Coroutines](#coroutines)
    - [Generators](#generators)
    - [Asynchronous Timers](#asynchronous-timers)
        - [Timer Interval](#timer-interval)
        - [Timer Timeout](#timer-timeout)
        - [Timer clear](#timer-clear)
    - [Events](#events)
    - [Observer](#observers)
    - [Promises](#promises)
    - [Examples](#more-examples-here)
    - [FAQ](#faq)
    - [Contribution](#contribution)
    - [License](#license)


# Nodepp-Arduino

**Nodepp** is an innovative open source project that aims to make it easier to create applications in **C++**. This project introduces a high-level abstraction layer that allows developers to write **C++** code in a way that is similar to how they would write code in **NodeJS**. With **Nodepp**, developers can leverage the advantages of the **C++** language while benefiting from the ease of use and flexibility that **NodeJS** offers. This unique combination of features makes **Nodepp** a powerful tool for creating high-performance and scalable applications. Additionally, since it is an open source project, anyone can contribute and improve **Nodepp** to fit their specific needs.

- **Nodepp:** compatible with Arduino [here](https://github.com/NodeppOficial/nodepp-arduino)
- **Nodepp:** compatible with PC      [here](https://github.com/NodeppOficial/Nodepp)

## Features

- Open source project, meaning anyone can contribute and improve it
- Allows writing **C++** code as if writing in **NodeJS** or **Javascript**
- Adds a high-level abstraction layer to simplify **C++** application development
- Includes an **Event Loop** that can handle multiple events and tasks on a single thread
- Supports **Coroutines**, which allows running multiple tasks concurrently on a single thread

## Hello world
```cpp
#include <nodepp.h>

using namespace nodepp;

void _main_() {
    console::start(9600);
    console::log("Hello World!");
}
```
```
Hello World!
```

## Smart Pointers
### Basic Pointer
```cpp
#include <nodepp>

using namespace nodepp;

void _main_() {
    console::start(9600);
    ptr_t<int> ptr = new int(10);
    console::log( ":>", *ptr );
}
```
```
:> 10
```

### Array Pointers
```cpp
#include <nodepp>

using namespace nodepp;

void _main_() {
    console::start(9600);
    ptr_t<int> ptr ({ 10, 20, 30, 40, 50 });
    for( auto x : ptr ) console::log( ":>", x );
}
```
```
:> 10
:> 20
:> 30
:> 40
:> 50
```

### Overload Pointers
```cpp
#include <nodepp>

using namespace nodepp;

void _main_() {
    console::start(9600);

    ptr_t<int> ptr = new int(10);
    console::log( ":>", *ptr );

    console::log("----");

    ptr = ptr_t<int>({ 10, 20, 30, 40, 50 });
    for( auto x : ptr ) console::log( ":>", x );
}
```
```
:> 10
----
:> 10
:> 20
:> 30
:> 40
:> 50
```

## Array
```cpp
#include <nodepp>

using namespace nodepp;

void _main_() {
    console::start(9600);
    array_t<int> arr ({ 10, 20, 30, 40, 50 });
    for( auto x : arr ) console::log( ":>", x );
}
```
```
:> 10
:> 20
:> 30
:> 40
:> 50
```

## String
```cpp
#include <nodepp>

using namespace nodepp;

void _main_() {
    console::start(9600);
    string_t str = "Hello World!";
    console::log( ":>", str );
}
```
```
Hello World!
```

## Tasks
```cpp
#include <nodepp.h>

using namespace nodepp;

void _main_() {
    console::start(9600);

    //return 1 -> will repeat the task
    process::loop::add([=](){
        console::done("repeat mode");
        return  1;
    });

    //return -1 -> will kill the task
    process::loop::add([=](){
        console::error("once mode");
        return -1;
    });

    //return 0 -> will block until != 0
    process::loop::add([=](){
        console::error("block mode");
        return  0;
    });

}
```

## Coroutines
```cpp
#include <nodepp.h>

using namespace nodepp;

void _main_() {
    console::start(9600);

    process::add([=](){ 
        static int x = 3;
    _Start
        while( x --> 0 ){
            console::log("A: x =",x); _Next;
        }
    _Stop
    });

    process::add([=](){ 
        static int x = 3;
    _Start
        while( x --> 0 ){
            console::log("B: x =",x); _Next;
        }
    _Stop
    });

}
```
```
A: x = 2
B: x = 2
A: x = 1
B: x = 1
A: x = 0
B: x = 0
```

## Generators
```cpp
#include <nodepp.h>

using namespace nodepp;

_Generator( gen ) {
    console::start(9600);
    
    int x = 3;

    _Emit(){ 
    _GStart;
        while( x-->0 ){
            console::log("x:>",x); 
            _Next;
        }
    _GStop;
    }

};

void _main_() { 
    gen A; process::add(A); 
}
```
```
x:> 2
x:> 1
x:> 0
```

## Asynchronous Timers
### Timer Interval
```cpp
#include <nodepp.h>
#include <nodepp/timer.h>

using namespace nodepp;

void _main_() {
    console::start(9600);

    timer::interval([=](){ 
        static int i=0; i++; i %= 1000;
        console::done("interval every: 1 second - ",i," seconds");
    },1000);

    console::log("Hello World!");

}
```
```
Hello World!
interval every: 1 second - 1 seconds
interval every: 1 second - 2 seconds
interval every: 1 second - 3 seconds
interval every: 1 second - 4 seconds
...
```

### Timer Timeout
```cpp
#include <nodepp.h>
#include <nodepp/timer.h>

using namespace nodepp;

void _main_() {
    console::start(9600);

    timer::timeout([=](){
        console::error("timeout after: 10 seconds");
    },10000);

    console::log("Hello World!");

}
```
```
Hello World!
timeout after: 10 seconds
```

### Timer Clear
```cpp
#include <nodepp.h>
#include <nodepp/timer.h>

using namespace nodepp;

void _main_() {
    console::start(9600);

    auto x = timer::timeout([=](){
        console::error("timeout after: 10 seconds");
    },10000);

    console::log("Hello World!");

    timer::clear( x );

}
```
```
Hello World!
```

## Events
```cpp
#include <nodepp.h>
#include <nodepp/event.h>

using namespace nodepp;

event_t<> ev; 

void _main_() {
    console::start(9600);

    ev.on([](){ console::log("Hello World!"); });
    ev.emit();

}
```
```
Hello World!
```

## Observers
```cpp
#include <nodepp.h>
#include <nodepp/observer.h>

using namespace nodepp;

observer_t obj ({
    { "a", 0 },
    { "b", 0 }
});

void _main_() {
    console::start(9600);

    obj.on( "b", []( any_t A, any_t B ){
        console::done( " B:>", (int)A, "|", (int)B, "changed" );
    });

    obj.on( "a", []( any_t A, any_t B ){
        console::error( "A:>", (int)A, "|", (int)B, "changed" );
    });
    
    obj.set( "a", 20 );
    obj.set( "b", 10 );

}
```
```
A:> 0 | 20 changed
B:> 0 | 10 changed
```

## Promises
```cpp
#include <nodepp.h>
#include <nodepp/timer.h>
#include <nodepp/promise.h>

using namespace nodepp;

void _main_() {
    console::start(9600);

    promise_t<int,int>([=]( auto res, auto rej ){
        timer::delay(1000); res(10);
    })
    
    .then([=]( int res ){
        console::log( ":>", res );
    })
    
    .fail([=]( int rej ){
        console::log( ":>", rej );
    });

    console::log("Hello World!");

}
```
```
Hello World!
:> 10
```

## More Examples Here
- Examples : [here](https://github.com/NodeppOficial/nodepp-arduino/tree/main/examples)

## FAQ
- reddit : [/r/Cplusplus/](https://www.reddit.com/r/Cplusplus/comments/19e2kw3/write_asynchronous_code_with_c_nodepp/) 
- reddit : [/r/cpp/](https://www.reddit.com/r/cpp/comments/19camli/write_asynchronously_code_with_c_nodepp/)
  
## Contribution

If you want to contribute to **Nodepp**, you are welcome to do so! You can contribute in several ways:

- Improving the documentation
- Reporting bugs and issues
- Adding new features or improving existing ones
- Writing tests and ensuring compatibility with different platforms
- Before submitting a pull request, make sure to read the contribution guidelines.

## License

**Nodepp** is distributed under the MIT License. See the LICENSE file for more details.
