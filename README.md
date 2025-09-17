# 

## Packages

```bash
sudo apt update
sudo apt install make gdb gcc g++ clang cmake doxygen python3 python3-pip mingw-w64 autoconf automake autoconf-archive libltdl-dev build-essential ninja-build pkg-config libtool libcap-dev liblzma-dev libx11-dev libxext-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev

```

## Installing vcpkg (C++ Package Manager)

Clone and bootstrap vcpkg:

```bash
git clone https://github.com/microsoft/vcpkg.git external/vcpkg
cd external/vcpkg
./bootstrap-vcpkg.sh
cd ../..
```

## Note for Debian 13 Users

On Debian 13, the `dbus` dependency for SDL3 does not work correctly and must be disabled.

**How to fix:**

1. Open the following file:  
   `external/vcpkg/ports/sdl3/vcpkg.json`

2. Replace the dependencies section:

**Original:**
```json
"dependencies": [
    { "name": "dbus", "default-features": false, "platform": "linux" },
    { "name": "vcpkg-cmake", "host": true },
    { "name": "vcpkg-cmake-config", "host": true }
]
```

**Change to:**
```json
"dependencies": [
    { "name": "vcpkg-cmake", "host": true },
    { "name": "vcpkg-cmake-config", "host": true }
]
```

---

## Using the Makefile Shortcuts

A `Makefile` is provided in the project root to simplify common build and run tasks. You can use the following commands:

| Command                | Description                                 |
|------------------------|---------------------------------------------|
| `make build-linux-gcc`   | Build the project using GCC on Linux        |
| `make build-linux-clang` | Build the project using Clang on Linux      |
| `make build-windows`     | Build the project for Windows (MSVC, on Windows only) |
| `make clean`             | Remove all build and binary directories     |
| `make clean-linux-gcc`   | Clean only GCC build and binaries           |
| `make clean-linux-clang` | Clean only Clang build and binaries         |
| `make clean-windows`     | Clean only Windows build and binaries       |
| `make run-linux-gcc`     | Run the GCC-built executable on Linux       |
| `make run-linux-clang`   | Run the Clang-built executable on Linux     |
| `make run-windows`       | Run the Windows executable (on Windows only)|

These shortcuts help you quickly build, clean, and run your project without manually invoking CMake or copying assets.

---