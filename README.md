# C++ Web Server
A minimalistic, zero-dependency cross-platform HTTP server.

## Structure
- `include/`: Header
- `src/`: Implementation
- `example/`: Usage

## Build
```bash
cmake -S . -B build
cmake --build build
```

## Usage
```cpp
#include "http-server.hpp"
int main()
{
    WebServer server(8080);

    server.get("/", []()
    { 
        return "Hello World";
    });
    server.runserver();
}
```


GNU General Public License 3.0