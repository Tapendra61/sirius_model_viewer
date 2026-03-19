# Sirius Model Viewer

A lightweight 3D model viewer built with C++ and OpenGL. Load and inspect `.obj`, `.fbx`, and `.gltf` models with real-time transform controls, camera navigation, and UV options — all through an immediate-mode ImGui interface.

## Demo

![Demo](resources/demo/demo.gif)

## Build

### Requirements

| Tool | Version |
|------|---------|
| [CMake](https://cmake.org/) | 3.5+ |
| [Clang](https://clang.llvm.org/) | C++20 support required |
| [Ninja](https://ninja-build.org/) | Any recent version |

### Build Steps

```bash
# 1. Configure the project with the Ninja generator in Release mode
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=clang++

# 2. Build the project
cmake --build build --config Release
```

The compiled binary (`model_viewer`) will be located in the `build/` directory.

Optionally, pass a model path as a command-line argument to load it on startup:

```bash
./build/model_viewer path/to/model.obj
```
