# Conway's Game of Life (SDL3)

A simple implementation of Conway's Game of Life using C++ and SDL3.

## Prerequisites

- **CMake** (3.16 or higher)
- **C++ Compiler** (supporting C++17 or higher)
- **Git**

```

## Getting Started

### 1. Clone the repository
```bash
git clone https://github.com/gsiri007/conways-game-of-life.git
cd conways-game-of-life
```

### 2. Clone vendored dependencies
This project uses SDL3 and SDL3_ttf as vendored dependencies. Clone them into the `vendored` directory:

```bash
mkdir -p vendored
git clone https://github.com/libsdl-org/SDL.git vendored/SDL
git clone https://github.com/libsdl-org/SDL_ttf.git vendored/SDL_ttf
```

## Building the Project

```bash
# Configure the project
cmake -B build

# Build the project
cmake --build build
```

## Running the Application

The application expects the `fonts/` directory to be present in the working directory from which it is launched.

```bash
# Run from the project root
./build/conways-game-of-life
```

## Controls

- **Mouse Click**: Set a cell as alive.
- **Return (Enter)**: Toggle simulation start/stop.
- **Esc / Q**: Quit the application.
