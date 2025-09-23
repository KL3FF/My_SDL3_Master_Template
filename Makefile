# -------------------------
# Root Settings
PROJECT_ROOT := $(CURDIR)

# -------------------------
# Build-Directories
BUILD_DIR_LINUX_GCC   	:= $(PROJECT_ROOT)/build/build-linux-gcc
BUILD_DIR_LINUX_CLANG	:= $(PROJECT_ROOT)/build/build-linux-clang
BUILD_DIR_WINDOWS_MSVC	:= $(PROJECT_ROOT)/build/build-windows

# Bin-Directories
BIN_DIR_LINUX_GCC		:= $(PROJECT_ROOT)/bin/linux-gcc
BIN_DIR_LINUX_CLANG		:= $(PROJECT_ROOT)/bin/linux-clang
BIN_DIR_WINDOWS_MSVC	:= $(PROJECT_ROOT)/bin/windows

# Compiler / Generator
GEN_LINUX 				:= "Unix Makefiles"
GEN_WINDOWS 			:= "NMake Makefiles"

# Assets Quelle
ASSETS_SRC := $(PROJECT_ROOT)/assets

# VCPKG TOOLCHAIN
VCPKG_TOOLCHAIN := $(PROJECT_ROOT)/external/vcpkg/scripts/buildsystems/vcpkg.cmake

# -------------------------
# Default Target
all: build-linux-gcc build-linux-clang build-windows

# -------------------------
# Python-Script BundleAssetsMaker
build-bundle:
	@echo "=== Building Bundle ==="
	@python3 BundleAssetsMaker.py $(ASSETS_SRC) $(PROJECT_ROOT)

# -------------------------
# Linux Builds
build-linux-gcc:
	@echo "=== Building Linux (GCC) ==="
	@mkdir -p $(BUILD_DIR_LINUX_GCC)
	cmake -S $(PROJECT_ROOT) -B $(BUILD_DIR_LINUX_GCC) -G $(GEN_LINUX) \
		-DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ \
		-DCMAKE_TOOLCHAIN_FILE=$(VCPKG_TOOLCHAIN) \
		-DVCPKG_TARGET_TRIPLET=x64-linux
	cmake --build $(BUILD_DIR_LINUX_GCC) --config Release
	@echo ">>> Copying assets folder to $(BIN_DIR_LINUX_GCC)"
	@echo ">>> Building Python bundle"
	@python3 BundleAssetsMaker.py $(ASSETS_SRC) $(BIN_DIR_LINUX_GCC)

build-linux-clang:
	@echo "=== Building Linux (Clang) ==="
	@mkdir -p $(BUILD_DIR_LINUX_CLANG)
	cmake -S $(PROJECT_ROOT) -B $(BUILD_DIR_LINUX_CLANG) -G $(GEN_LINUX) \
		-DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ \
		-DCMAKE_TOOLCHAIN_FILE=$(VCPKG_TOOLCHAIN) \
		-DVCPKG_TARGET_TRIPLET=x64-linux
	cmake --build $(BUILD_DIR_LINUX_CLANG) --config Release
	@echo ">>> Copying assets folder to $(BIN_DIR_LINUX_CLANG)"
	@echo ">>> Building Python bundle"
	@python3 BundleAssetsMaker.py $(ASSETS_SRC) $(BIN_DIR_LINUX_CLANG)

# -------------------------
# Windows Builds
build-windows:
	@echo "=== Building Windows (MSVC) ==="
	@mkdir -p $(BUILD_DIR_WINDOWS_MSVC)
ifeq ($(OS),Windows_NT)
	cmake -S $(PROJECT_ROOT) -B $(BUILD_DIR_WINDOWS_MSVC) -G $(GEN_WINDOWS) \
		-DCMAKE_TOOLCHAIN_FILE=$(VCPKG_TOOLCHAIN) -DVCPKG_TARGET_TRIPLET=x64-windows -A x64
	cmake --build $(BUILD_DIR_WINDOWS_MSVC) --config Release
	@echo ">>> Copying assets folder to $(BIN_DIR_WINDOWS_MSVC)"
	$(MAKE) copy-vcpkg-dlls-msvc
	@echo ">>> Building Python bundle"
	@python BundleAssetsMaker.py "$(ASSETS_SRC)" "$(BIN_DIR_WINDOWS_MSVC)"
else
	@echo "MSVC Build nur auf Windows möglich!"
endif

# -------------------------
# vcpkg DLL Copy Targets
copy-vcpkg-dlls-msvc:
ifeq ($(OS),Windows_NT)
	@echo ">>> Copying vcpkg DLLs for MSVC"
	@vcpkg_root=$(PROJECT_ROOT)/external/vcpkg; \
	vcpkg_exe=$$vcpkg_root/vcpkg; \
	$$vcpkg_exe copy dlls $(BIN_DIR_WINDOWS_MSVC)
else
	@echo "Skipping DLL copy for MSVC, running on non-Windows host"
endif

# -------------------------
# Clean Targets
clean:
	@echo "=== Cleaning all build and bin directories ==="
	@rm -rf $(PROJECT_ROOT)/build/* $(PROJECT_ROOT)/bin/*

clean-linux-gcc:
	@rm -rf $(BUILD_DIR_LINUX_GCC) $(BIN_DIR_LINUX_GCC)

clean-linux-clang:
	@rm -rf $(BUILD_DIR_LINUX_CLANG) $(BIN_DIR_LINUX_CLANG)

clean-windows:
	@rm -rf $(BUILD_DIR_WINDOWS_MSVC) $(BIN_DIR_WINDOWS_MSVC)

# -------------------------
# Run Targets
run-linux-gcc:
	@echo "=== Running Executable (Linux GCC) ==="
	@exe_name=$$(cat executable_name.txt); \
	$(PROJECT_ROOT)/bin/linux-gcc/$$exe_name

run-linux-clang:
	@echo "=== Running Executable (Linux Clang) ==="
	@exe_name=$$(cat executable_name.txt); \
	$(PROJECT_ROOT)/bin/linux-clang/$$exe_name

run-windows:
	@echo "=== Running Executable (Windows MSVC) ==="
ifeq ($(OS),Windows_NT)
	@exe_name=$$(cat executable_name.txt); \
	$(PROJECT_ROOT)/bin/windows/$$exe_name.exe
else
	@echo "MSVC Build nur auf Windows möglich"
endif
