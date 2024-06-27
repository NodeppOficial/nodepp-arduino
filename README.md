# Nodepp-Arduino

**Nodepp** is an innovative open source project that aims to make it easier to create applications in **C++**. This project introduces a high-level abstraction layer that allows developers to write **C++** code in a way that is similar to how they would write code in **NodeJS**. With **Nodepp**, developers can leverage the advantages of the **C++** language while benefiting from the ease of use and flexibility that **NodeJS** offers. This unique combination of features makes **Nodepp** a powerful tool for creating high-performance and scalable applications. Additionally, since it is an open source project, anyone can contribute and improve **Nodepp** to fit their specific needs.

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

void onMain() {
    console::log("Hello World!");
}
```

## Examples
- [here](https://github.com/NodeppOficial/nodepp-arduino/tree/main/examples/)

## FAQ
- reddit : [/r/Cplusplus/](https://www.reddit.com/r/Cplusplus/comments/19e2kw3/write_asynchronous_code_with_c_nodepp/)
  
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
