cmake_minimum_required(VERSION 3.31.6)

# Name of the executable
set(EXE_NAME "My_Test_App")
project("${EXE_NAME}" VERSION 1.0.0 LANGUAGES C CXX)
file(WRITE "executable_name.txt" "${EXE_NAME}\n")


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Binary output directories
set(BIN_DIR_LINUX_GCC     "bin/linux-gcc")
set(BIN_DIR_LINUX_CLANG   "bin/linux-clang")
set(BIN_DIR_WINDOWS_MSVC  "bin/windows-msvc")

# Conig.h.in + placeholder => congfig.h + Cmake Variables
configure_file(
    ${CMAKE_SOURCE_DIR}/include/config/AppInfo.h.in
    ${CMAKE_SOURCE_DIR}/include/config/AppInfo.h
    @ONLY
)

# Compiler-specific warnings
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-Wall -Wextra -Wpedantic)
elseif(MSVC)
    add_compile_options(/W4)
endif()

include(${CMAKE_SOURCE_DIR}/external/vcpkg/scripts/buildsystems/vcpkg.cmake)
find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# Sources and headers
add_subdirectory(src)
add_subdirectory(include)

# Output directories by platform/compiler
if(MSVC)
    set(RUNTIME_OUT "${CMAKE_SOURCE_DIR}/bin/windows-msvc")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(RUNTIME_OUT "${CMAKE_SOURCE_DIR}/bin/linux-gcc")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(RUNTIME_OUT "${CMAKE_SOURCE_DIR}/bin/linux-clang")
endif()

# Place executable in the correct directory
set_target_properties(MAIN PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${RUNTIME_OUT}"
    OUTPUT_NAME "${EXE_NAME}"
)