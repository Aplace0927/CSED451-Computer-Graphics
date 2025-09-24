# CSED451-Computer-Graphics

## Source codes

### Third-party libraries

-  Shared libraries for OpenGL and their family
    - `lib/[mac, win]`
    - `bin/[linux, mac, win]`

- Header files (OpenGL and their family)
  - `include/GL`
  - `include/glm`

### Source codes for assignments
  - `src/include/*.hpp`
  - `src/*.cpp`

#### Brief description of source files

| `.hpp` | `.cpp` | Description |
|--------|--------|-------------|
| - | `main.cpp` | Main program |
|`boundingbox.hpp` | - | Boundingbox for detecting collision |
| `bullet.hpp` | `bullet.cpp` | Bullet class |
| `config.hpp` | - | Configuration constants |
| `digit.hpp` | `digit.cpp` | Font rendering |
| `enemy.hpp` | `enemy.cpp` | Enemy class and behavior |
| `enemypatternss.hpp` | `enemypatternss.cpp` | Enemy attack patterns |
| `game.hpp` | `game.cpp` | Game class and callback registration |
| `graphicsmanager.hpp` | `graphicsmanager.cpp` | Object rendering management |
| `healthbar.hpp` | `healthbar.cpp` | Health bar and digit font rendering |
| `object.hpp` | - | Base class of game entities |
| `objectpool.hpp` | `objectpool.cpp` | Optimization helper for multiple homogenous objects |
| `physicsmanager.hpp` | `physicsmanager.cpp` | Physics simulation management |
| `player.hpp` | `player.cpp` | Player class and behavior |
| `shape.hpp` | `shape.cpp` | Shape representation and manipulation |
| `singleton.hpp` | `singleton.cpp`| Singleton template class |
| `utility.hpp` | - | Utility functions for graphics calculation |

## How to build
- Using CMake
    ```
    mkdir out && cd out
    cmake ..
    make
    ./build/touhou-postech
    ```
- Using Visual Studio
