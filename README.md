# My\_SDL\_Master\_Template

**Description**

This project is a **cross-platform SDL3 C++ projects**. It allows you to quickly create and compile applications on **Linux, Windows**. Using the provided **Makefile shortcuts**, required packages are automatically installed via **vcpkg**, and the **build process via CMake** is simplified.

---

## Used Tools & Terms

* **SDL3** – A C++ library for building cross-platform multimedia applications. With SDL3, programs can be compiled for **Linux, macOS, Windows, and more** ([platforms](https://wiki.libsdl.org/SDL3/README-platforms)).
* **vcpkg** – A C++ package manager for easily downloading and managing libraries like SDL3.
* **Makefile** – Provides shortcuts to automatically execute build and run commands for different platforms.
* **CMakeLists.txt** – Configuration file for CMake that defines how the project is built, including sources, dependencies, and compiler settings.

---

## Project Progress / Current Tasks

```
Windows                         ██████░░░░ 60%  🟡
Linux                           ██████████ 100% 🟢
Mac                             ░░░░░░░░░░ 0%   🔴

Program Loop                    ██████░░░░ 60%  🟡
Texture Manager                 █████████░ 90%  🟢
PythonBundleAssetsMaker         ██████████ 100% 🟢
BuildAssetsHandler              ████████░░ 80%  🟢
Lazy Loader                     ████████░░ 80%  🟢
JSON Config Loader              ███████░░░ 70%  🟡
Instance Manager                ███░░░░░░░ 30%  🔴
Makefile Shortcuts              ████████░░ 70%  🟢
Graphical Representation        █░░░░░░░░░ 10%  🔴
Scene Editor                    ░░░░░░░░░░ 0%   🔴
Event Manager                   ░░░░░░░░░░ 0%   🔴
```

---

## Creating `.pak` Files

Assets are automatically bundled into `.pak` files during the build process. Each folder inside the assets directory becomes a separate `.pak` file. The build system goes **recursively through all subfolders** of the `assets` folder. For each folder:

* All files **directly inside that folder** are bundled into a `.pak` named after the folder (e.g., `hero.pak`).
* Subfolders **inside a folder are not included** in the parent folder's `.pak`; they generate their **own `.pak` files** with the same rules.
* No `.pak` files are created at the **top level** of the `assets` directory.

The `.pak` files are stored in the build folder under the same relative path, for example:

```
bin/<Build-tool>/sprites/mid/hero.pak
```

---

### Structure of a `.pak` File

```
+----------------------------+
| Header                     |
| - Signature "PACK"         |
| - Directory Offset         |
| - Directory Size           |
+----------------------------+
| Data Section               |
| - File 1                   |
| - File 2                   |
| - ...                      |
+----------------------------+
| Directory at the End       |
| - Path to File 1 + Offset + Size |
| - Path to File 2 + Offset + Size |
| - ...                      |
+----------------------------+
```

**Example of a `.pak` File**

Suppose you have the following files in `assets/sprites/mid/hero/`:

```
walk.png  (Size: 4557 Bytes)
stay.png  (Size: 4557 Bytes)
```

The `.pak` directory entries would look like this:

```
Added file: path: assets/sprites/mid/hero/walk.png, Offset: 12, Size: 4557
Added file: path: assets/sprites/mid/hero/stay.png, Offset: 4569, Size: 4557
```

The `.pak` file name would be `hero.pak` and the path in the build folder would be:

```
bin/<Build-tool>/sprites/mid/hero.pak
```

---

**Explanation**

* **Offset** – Position of the file in the data section of the `.pak` file
* **Size** – Size of the file in bytes
* **Path** – Path of the file inside the `.pak` file

This recursive structure allows the program to load each `.pak` file independently, ensuring that subfolders create separate `.pak` files and no files are included from other folders.

---

## Installing vcpkg (C++ Package Manager)

Clone and bootstrap vcpkg:

```bash
git clone https://github.com/microsoft/vcpkg.git external/vcpkg
cd external/vcpkg
./bootstrap-vcpkg.sh
cd ../..
```

### Note for Debian 13 Users

On Debian 13, the `dbus` dependency for SDL3 does not work correctly and must be disabled.

**How to fix:**

1. Open the following file:
   `external/vcpkg/ports/sdl3/vcpkg.json`

2. Replace the dependencies section:

**Original**

```json
"dependencies": [
    { "name": "dbus", "default-features": false, "platform": "linux" },
    { "name": "vcpkg-cmake", "host": true },
    { "name": "vcpkg-cmake-config", "host": true }
]
```

**Change to**

```json
"dependencies": [
    { "name": "vcpkg-cmake", "host": true },
    { "name": "vcpkg-cmake-config", "host": true }
]
```

---

## Using the Makefile Shortcuts

A `Makefile` is provided in the project root to simplify common build and run tasks:

| Command                  | Description                               |
| ------------------------ | ----------------------------------------- |
| `make build-linux-gcc`   | Build the project using GCC on Linux      |
| `make build-linux-clang` | Build the project using Clang on Linux    |
| `make build-windows`     | Build the project for Windows (MSVC only) |
| `make clean`             | Remove all build and binary directories   |
| `make clean-linux-gcc`   | Clean only GCC build and binaries         |
| `make clean-linux-clang` | Clean only Clang build and binaries       |
| `make clean-windows`     | Clean only Windows build and binaries     |
| `make run-linux-gcc`     | Run the GCC-built executable on Linux     |
| `make run-linux-clang`   | Run the Clang-built executable on Linux   |
| `make run-windows`       | Run the Windows executable (Windows only) |

These shortcuts help you quickly build, clean, and run your project without manually invoking CMake or copying assets.

---
