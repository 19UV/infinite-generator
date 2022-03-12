# Infinite Generator

## Cloning
Be sure to run the following:
```
git clone --recursive https://github.com/19UV/infinite-generator.git
```

Or if cloned non-recursively:
```
git submodule update --init
```

## Building
Currently, this is only being developed and tested on Windows, but I'm using
libraries that should allow it to be easily ported to other OSes.

### Windows (CMake + MSVC)
```batch
cmake -B build
cmake --build build
build\Debug\Infinite_Generator.exe
```

## Dependencies (all located in ```extern/```)
 * GLAD [[Github](https://github.com/Dav1dde/glad)]
 * GLFW [[Github](https://github.com/glfw/glfw)] [[Website](https://www.glfw.org/)]
 * GLM [[Github](https://github.com/g-truc/glm)]
 * Dear ImGui [[Github](https://github.com/ocornut/imgui)]