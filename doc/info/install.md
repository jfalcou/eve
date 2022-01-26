Installation & Quick Start {#install}
==========================

@tableofcontents

# Getting Started

## Retrieving the source

**EVE** is available on GitHub and can be retrieved via the following command:
<br/>

@verbatim
$ git clone -b main https://github.com/jfalcou/eve.git
@endverbatim

This retrieves the `main` branch which contains the latest stable version.

You can also use the `develop` branch if you prefer using bleeding edge unstable version or any tagged versions.

Once retrieved, you should have a `eve` folder which contains the whole source code, this documentation, assorted examples and the unit test suite.

@verbatim
$ cd eve
$ ls
  benchmarks  cmake  CODE_OF_CONDUCT.md  CONTRIBUTORS  LICENSE.md
  README.md   tools  CMakeLists.txt      doc           examples
  include     test
@endverbatim

## Installing

Create a `build` directory here and enter it. Once in the `build` directory, you can use  **CMake** to generate the build system for **EVE**.

We recommend using [Ninja](https://ninja-build.org/) but any build system
is fine.

@verbatim
$ mkdir build
$ cd build
$ cmake .. -G Ninja
@endverbatim

Once **CMake** completes, you can use the `install` target to build and install **EVE**. By default, the library will be installed in the `/usr/local`directory, thus requiring root privileges on Linux.

@verbatim
$ ninja install
@endverbatim

You can select an alternative installation path by specifying the `CMAKE_INSTALL_PREFIX` option at configuration time.

@verbatim
$ cmake .. -G Ninja -DCMAKE_INSTALL_PREFIX=path/to/install
$ ninja install
@endverbatim

## Building the Documentation
You can rebuild **EVE** documentation if you have the latest version of Doxygen installed using the `doxygen` target:
<br/>

@code
ninja doxygen
@endcode

The resulting HTML files will be available in the `doc` folder.

# Quick Start

## Supported compilers/architectures.

**EVE** requires a C++20 compliant compiler. Here is the current minimal compiler version supported:

<center>
| Compiler       | Version        |
| -------------- | -------------- |
| g++            | 11  or above   |
| clang++        | 12  or above   |
</center>
<br/>

In term of SIMD extension sets, we actively supports (ie code is optimized and regularly tested) the following:

  - **Intel**
    - SSE2, SSSE3, SSE3, SSE4.1, SSE4.2
    - AVX, AVX2, FMA3
    - AVX512 in SKylake-AVX512 mode (F, CD, VL, DQ, BW)
  - **ARM**
    - NEON A32 (64 & 128 bits)
    - NEON A64 (64 & 128 bits)
    - ASIMD

The following instructions are tentatively supported (ie code is incomplete and not tested in depth):

- **PowerPC**
  - Altivec for Power7 to 9
  - VSX for Power9

## Compilation

Once installed, you can compile the following code to check if everything is alright.

@godbolt{examples/quick-start/sanity-check.cpp}

To do so, use your C++20 aware favorite compiler, for example g++.

@verbatim
$ g++ test.cpp -std=c++20  -march=native -O3 -DNDEBUG -I/path/to/install/include -o output
@endverbatim

Don't forget the `--std=c++20` option to be sure to activate C++20 support. If you use a different compiler, check your compiler user's manual to use the proper option.

You can notice we use the `-O3 -DNEDBUG` options. This is required if you want to be sure to get the best performance out of **EVE**.

The `-DNDEBUG` setting can be omitted but then asserts will be inserted into the code to prevent logic errors.

## Instruction Set Selection

The SIMD instruction sets that **EVE** uses is decided at compile time. You can use `-march=native` if you're sure your code won't be executed anywhere else.

You can also select a specific instructions set by using the proper option(s) from your compiler. For example, let's compile for exactly SSE4.1.

@verbatim
$ g++ test.cpp -std=c++20  -msse4.1 -O3 -DNDEBUG -I/path/to/install/include -o output
@endverbatim

## Execution

Once done, execute the binary. If you compiled for SSE4.1 for example, you'll end up with the
following results:

@verbatim
$ ./output
 x     = (1, 2, 3, 4)
 2*x   = (2, 4, 6, 8)
 x^0.5 = (1, 1.41421, 1.73205, 2)
@endverbatim

That's it, **EVE** is properly installed and ready to use.

# Advanced options

If you want to dig a bit further, you can pass additional options to `cmake` to activate additional features.

| Option | Effect     | Target              |
|:-------|:-----------|:--------------------|
| `EVE_USE_BMI_ON_AVX2` | Enables using bmi instructions on avx2: for intel it's benefitial, for amd it is a disaster |
| `EVE_USE_PCH`    | Enable using precompiled headers for **EVE**. This is `ON` by default  |                     |
| `EVE_BUILD_TEST` | Enable unit tests for **EVE** (`ON` by default).  | `ninja unit`        |
| `EVE_BUILD_BENCHMARKS`    | Enable benchmark tests for **EVE** (`OFF` by default). | `ninja benchmarks`  |
| `EVE_BUILD_RANDOM`        | Enable random tests for **EVE** (`OFF` by default). | `ninja random`      |

There is currently over 2000 tests, so compiling all unit tests may require a large machine or some time. We recommend compiling in parallel using `-j`.
