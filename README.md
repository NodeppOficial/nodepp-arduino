# Nodepp-Arduino

**Nodepp** is an innovative open source project that aims to make it easier to create applications in **C++**. This project introduces a high-level abstraction layer that allows developers to write **C++** code in a way that is similar to how they would write code in **NodeJS**. With **Nodepp**, developers can leverage the advantages of the **C++** language while benefiting from the ease of use and flexibility that **NodeJS** offers. This unique combination of features makes **Nodepp** a powerful tool for creating high-performance and scalable applications. Additionally, since it is an open source project, anyone can contribute and improve **Nodepp** to fit their specific needs.

## Features

- 📌: Allows writing **C++** code as if writing in **NodeJS** or **Javascript**
- 📌: Adds a high-level abstraction layer to simplify **C++** application development
- 📌: Compatible with several devices like Arduino UNO | Esp8266 | Esp32 | Stm32
- 📌: Supports **Coroutines**, which allows running multiple tasks concurrently on a single thread

## Bateries Included

- 📌: Include a **build-in JSON** parser / stringify system.
- 📌: Include a **build-in RegExp** engine for processing text strings.
- 📌: Include a **build-in System** that make every object **Async Task** safety.
- 📌: Include a **Smart Pointer** base **Garbage Collector** to avoid **Memory Leaks**.
- 📌: Include support for **Reactive Programming** based on **Events** and **Observers**.
- 📌: Include an **Event Loop** that can handle multiple events and tasks on a single thread.

## Hello world
```cpp
#include <nodepp.h>

using namespace nodepp;

void onMain() {
    console::enable(9600);
    console::log("Hello World!");
}
```

## Events
```cpp
#include <nodepp/nodepp.h>
#include <nodepp/event.h>

using namespace nodepp;

event_t<> ev;

void onMain(){

    pinMode( 13, OUTPUT );

    ev.on([](){
        static bool b=0; b=!b;
        digitalWrite( 13, b );
    });

    ev.emit();

}
```

## Timer
```cpp
#include <nodepp/nodepp.h>
#include <nodepp/timer.h>

using namespace nodepp;

void onMain(){

    pinMode( 13, OUTPUT );    
    
    timer::interval([=](){ 
        static bool b=0; b=!b;
        digitalWrite( 13, b );
    }, 1000 );

}
```


### More Examples [here](https://github.com/NodeppOficial/Nodepp/tree/main/examples)

## FAQ
- reddit : [/r/Nodepp/](https://www.reddit.com/r/Nodepp/comments/1eaq1pu/faq_ask_anything_about_nodepp/)
  
## Contribution

If you want to contribute to **Nodepp**, you are welcome to do so! You can contribute in several ways:

- ☕ Buying me a Coffee
- 📢 Reporting bugs and issues
- 📝 Improving the documentation
- 📌 Adding new features or improving existing ones
- 🧪 Writing tests and ensuring compatibility with different platforms
- 🔍 Before submitting a pull request, make sure to read the contribution guidelines.

**NOTE:** We don't use STD here, just Pure C++.

## License

**Nodepp** is distributed under the MIT License. See the LICENSE file for more details.
