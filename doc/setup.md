Installation & Quick Start {#setup}
==========================

# Pre-requisites

**EVE** requires a C++20 compliant compiler. Here is the current minimal compiler version supported:

| Compiler       | Version        |
| -------------- | -------------- |
| g++            | 11  or above   |
| clang++        | 13  or above   |

In term of SIMD extension sets, the supports status are as follows:

- Active Support  (ie code is optimized and regularly tested)

  - **Intel**
    - SSE2, SSSE3, SSE3, SSE4.1, SSE4.2
    - AVX, AVX2, FMA3
    - AVX512 in SKylake-AVX512 mode (F, CD, VL, DQ, BW)
  - **ARM**
    - NEON A32 (64 & 128 bits)
    - NEON A64 (64 & 128 bits)
    - ASIMD
    - SVE with fixed sizes of 128, 256 and 512 bits registers.

- Partial/In-progress support with minimal checks:
  - **PowerPC**
    - Altivec for Power7 to 9
    - VSX for Power9

- No Support
  - We **do not support** ARM SVE with dynamic size.
  - We **do not support** GPGPU, this is the job for another tool.

# Retrieving the source

## Github

**EVE** is available on GitHub and can be retrieved via the following command:
<br/>

```bash
git clone https://github.com/jfalcou/eve.git
```

This retrieves the `main` branch which contains the latest stable version. Development happens
live on `main` so if you need stability, use a tagged versions.

## CPM

You can install **EVE** directly via [CPM](https://github.com/cpm-cmake/CPM.cmake). After
[adding CPM to your CMake setup](https://github.com/cpm-cmake/CPM.cmake#adding-cpm), just
add the following commands:

```cmake
include(CPM)

CPMAddPackage(
        NAME eve
        URL https://github.com/jfalcou/eve/archive/refs/tags/v2022.03.00.zip
        VERSION 2022.03.00
        OPTIONS "EVE_BUILD_TEST OFF"
                "EVE_BUILD_BENCHMARKS OFF"
                "EVE_BUILD_DOCUMENTATION OFF"
)
```

## SPACK

**EVE** is [**available**](https://spack.readthedocs.io/en/latest/package_list.html#eve
) via [**SPACK**](https://spack.readthedocs.io/en/latest/getting_started.html):

```bash
spack install eve
```

Once installed, you can use **EVE** headers directly from your
[**SPACK**](https://spack.readthedocs.io/en/latest/getting_started.html) installation.

## AUR

**EVE** is available on Arch-Linux via an [**AUR package**](https://aur.archlinux.org/packages/eve-git/).

```bash
yay -S eve-git
```

# Installation from Source

If you didn't fetched **EVE** from a package manager, you'll need to install it via your CMake
system.

## Setting up the Library

With **CMake**, generate the build system for **EVE**. We recommend using
[Ninja](https://ninja-build.org/) but any build system is fine.

@verbatim
cmake -B build -G Ninja
@endverbatim

Since **EVE** is header only, once **CMake** completes, you can install **EVE** without building. By
default, the library will be installed globally to your system, in `/usr/local` for Linux, thus
requiring root privileges.

```bash
cmake --install build
```

An alternative installation prefix can be specified with the '--prefix' flag.

```bash
cmake --install build --prefix path/to/install
```

## Building the Documentation

You can rebuild **EVE** documentation if you have the latest version of Doxygen installed
using the `doxygen` target:
<br/>

@code
cmake --build build --target doxygen
@endcode

The resulting HTML files will be available in the `docs` folder inside your build folder.

# Using the library

## Compilation

To compile code using **EVE**, use your C++20 aware favorite compiler, for example g++.

@verbatim
$ g++ test.cpp -std=c++20  -march=native -O3 -DNDEBUG -I/path/to/install/include/eve-<version> -o output
@endverbatim

Don't forget the `--std=c++20` option to be sure to activate C++20 support. If you use a different compiler, check your compiler user's manual to use the proper option.

You can notice we use the `-O3 -DNDEBUG` options. This is required if you want to be sure to get the best performance out of **EVE**.

The `-DNDEBUG` setting can be omitted but then asserts will be inserted into the code to prevent logic errors.

## Instruction Set Selection

The SIMD instruction sets that **EVE** uses is decided at compile time. You can use `-march=native` if you're sure your code won't be executed anywhere else.

You can also select a specific instructions set by using the proper option(s) from your compiler. For example, let's compile for exactly SSE4.1.

@verbatim
$ g++ test.cpp -std=c++20  -msse4.1 -O3 -DNDEBUG -I/path/to/install/include/eve-<version> -o output
@endverbatim


## Execution

Once done, execute the binary. If you compiled for SSE4.1 for example, you'll end up with the
following results:

@godbolt{examples/quick-start/sanity-check.cpp}

That's it, **EVE** is properly installed and ready to use.

## Use with CMake

Once installed, **EVE** may be consumed through its config-file **CMake** package. Simply find and
link against **EVE's** **CMake** target, as you would any other **CMake** library, and then
configure and build your **CMake** project.

```cmake
add_executable(use-eve main.cpp)
find_package(eve CONFIG REQUIRED)
target_link_libraries(use-eve PRIVATE eve::eve)
```

If a custom installation prefix was used, ensure your **EVE** installation is within **CMake's**
search path with the use of the **CMake** variables **eve_ROOT**, **eve_DIR**, or
**CMAKE_PREFIX_PATH**.

# Advanced options

If you want to dig a bit further, you can pass additional options to `cmake` to
activate additional features.

|Option                     |Effect                                                       |Target        |
|---------------------------|:------------------------------------------------------------|:-------------|
| `EVE_BUILD_TEST`          |Enable unit tests for **EVE** (`ON` by default).             | `unit`       |
| `EVE_BUILD_BENCHMARKS`    |Enable benchmark tests for **EVE** (`OFF` by default).       | `benchmarks` |
| `EVE_BUILD_RANDOM`        |Enable random tests for **EVE** (`OFF` by default).          | `random`     |
| `EVE_BUILD_DOCUMENTATION` |Enable the generation of the documentation (`ON` by default).| `doxygen`|

There is currently over 2000 tests, so compiling all unit tests may require a large machine or some
time. We recommend compiling in parallel using `-j`.

All available **CMake** targets may be listed via `cmake --build build --target help`, each of which
may be built individually.

Some options are also available to control some other aspects

| Option                | Effect                                              | Comments                               |
|-----------------------|:----------------------------------------------------|:---------------------------------------|
| `EVE_USE_BMI_ON_AVX2` | Enables using bmi instructions on AVX2              | Beneficial on Intel, disastrous on AMD |
| `EVE_USE_PCH`         | Enable using precompiled headers for **EVE** tests. | This is `ON` by default                |
