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
| `game.hpp` | `game.cpp` | Game class and callback registration |

| `utility.hpp` | - | Utility functions for graphics calculation |
| `config.hpp` | - | Configuration constants |

| `singleton.hpp` | `singleton.cpp`| Singleton template class |
| `objfileloader.hpp` | `objfileloader.cpp` | covert obj file to mesh |
| `objectpool.hpp` | - | Optimization helper for multiple homogenous objects |

| `gameobject.hpp` | `gameobject.cpp` | GameObject |
| `component.hpp` | `component.cpp` | Base Ability of GameObject |
| `scene.hpp` | `scene.cpp`| SceneGraph of Game Project |

| `boundingbox2d.hpp` | - | Boundingbox2d for detecting collision |
| `boundingbox3d.hpp` | - | Boundingbox3d for detecting collision |
| `mesh2d.hpp` | `mesh2d.cpp` | Mesh2d for rendering |
| `mesh3d.hpp` | `mesh2d.cpp` | Mesh3d for rendering |

| `transform.hpp` | `transform.cpp` | Component for coordinate system |
| `collider2d.hpp` | - | Component for detecting collision2d |
| `collider3d.hpp` | `collider3d.cpp` | Component for detecting collision3d |
| `renderer2d.hpp` | `renderer2d.cpp` | Component for rendering 2d mesh |
| `renderer3d.hpp` | `renderer3d.cpp` | Component for rendering 3d mesh |

| `collisionmanager.hpp` | `collisionmanager.cpp` | Collision checking management |
| `graphicsmanager.hpp` | `graphicsmanager.cpp` | GameObject rendering management |
| `physicsmanager.hpp` | `physicsmanager.cpp` | Physics simulation management |
| `inputmanager.hpp` | `inputmanager.cpp` | Input management |

| `backgroundboundingbox.hpp` | - | Component for Backgound Boundingbox |
| `bullet.hpp` | - | Component for Bullet behavior |
| `enemy.hpp` | `enemy.cpp` | Component for Enemy behavior |
| `enemypatternss.hpp` | `enemypatternss.cpp` | Data for Enemy attack patterns |
| `healthbar.hpp` | - | Data for Health bar mesh |
| `player.hpp` | `player.cpp` | Component for Player behavior |

## How to build

### Prerequisites
  - CMake 3.8 or higher
  - Proper OpenGL development environment
    - MacOS: `glew`, `freeglut`
    - Linux: `libgl1-mesa-dev`, `libglu1-mesa-dev`, `freeglut3-dev`
    - Windows: Visual Studio **with C++ and CMake support**

- Windows (build CMake with Visual Studio)
  1. Open project with Visual Studio
  2. Set build type to **`x64 Release`**
  3. Build solution (`Ctrl + Shift + B`)
  
- MacOS / Linux (using CMake on terminal)
    ```
    mkdir out && cd out
    cmake ..
    make
    ./build/touhou-postech
    ```

