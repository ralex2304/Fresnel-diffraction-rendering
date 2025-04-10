# Fresnel diffraction rendering

> [!WARNING]
> Work in progress

## Dependencies

All Dependencies are managed with `CMake CPM` and listed in `/cmake/third-party.cmake`

### Build dependencies

- `C++ 20` and `C` compiler
- `CMake`
- `Python 3` (for `GLAD`):
    - `jinja2`

## Build

```bash
cmake -S . -B <build_dir> [-DGLFW_USE_WAYLAND=ON] [-DCMAKE_EXPORT_COMPILE_COMMANDS=1] -DCMAKE_BUILD_TYPE={Debug, Release} [-DUSE_SANITIZER='Address;Undefined']
cd <build_dir>
cmake --build .
./Fresnel-diffraction-rendering
```

E.g:

```bash
cmake -S . -B build -DGLFW_USE_WAYLAND=ON -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Debug
cd build
cmake --build .
./Fresnel-diffraction-rendering
```

