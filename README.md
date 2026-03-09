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

## Showcase
<img width="400" height="300" alt="image" src="https://github.com/user-attachments/assets/51235202-84ff-4fb7-a11e-aad7246b31bd" />
<br>
<img width="400" height="300" alt="image" src="https://github.com/user-attachments/assets/b9631a5a-b1ed-4d43-bd5d-da51996281cc" />



GNU General Public License 3.0
