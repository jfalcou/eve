Installation & Quick Start {#install}
==========================

@tableofcontents

# Retrieving the source

**EVE** is available on GitHub and can be retrieved via the following command:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 $ git clone -b main https://github.com/jfalcou/eve.git
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This retrieves the `main` branch which contains the latest stable version. You can also use the `develop` branch if you prefer using bleeding edge unstable version or any tagged versions. Once retrieved, you should have a ``eve`` folder which contains the whole source code.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 $ cd eve
 $ ls
   benchmarks  cmake  CMakeLists.txt  docs include  LICENSE.md  README.md  test  tools
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# Installing

Create a ``build`` directory here and enter it. Once in the ``build`` directory, you can use  **CMake** to generate the build system for **EVE**. We recommend using Ninja but any build system is fine.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 $ mkdir build
 $ cd build
 $ cmake .. -G Ninja
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Once **CMake** completes, you can use the ``install`` target to build and install **EVE**. By default, the library will be installed in the ``/usr/local`` directory, thus requiring root privileges.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 $ sudo ninja install
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You can select an alternative installation path by specifying the ``CMAKE_INSTALL_PREFIX`` option at configuration time.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 $ cmake .. -G Ninja -DCMAKE_INSTALL_PREFIX=path/to/install
 $ ninja install
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# Quick Start

## Compilation

Once installed, you can compile the following code to check if everything is alright.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
#include <iostream>
#include <eve/wide.hpp>
#include <eve/function/sqrt.hpp>

int main()
{
  eve::wide<float> x( [](auto i, auto) { return 1.f+i; } );
  std::cout << "x     = " << x << "\n";
  std::cout << "2*x   = " << x + x << "\n";
  std::cout << "x^0.5 = " << eve::sqrt(x) << "\n";

  return 0;
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To do so, use your C++20 aware favorite compiler, for example g++.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 $ g++-10 test.cpp -std=c++20  -march=native -O3 -DNDEBUG -I/path/to/install/include -o output
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Don't forget the `--std=c++20` option to be sure to activate C++20 support. If you use a different
compiler, check your compiler user's manual to use the proper option.

You can notice we use the `-O3 -DNEDBUG` options. This is required if you want to be sure to
get the best performance out of **EVE**.

The `-DNDEBUG` setting can be omitted but then asserts will be inserted into the code to prevent logic errors.

## Instruction Set Selection

The SIMD instruction sets that **EVE** uses is decided at compile time. You can use `-march=native`
if you're sure your code won't be executed anywhere else. You can also select a specific instructions
set by using the proper option(s) from your compiler. For example, let's compile for exactly SSE4.1.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 $ g++-10 test.cpp -std=c++20  -msse4.1 -O3 -DNDEBUG -I/path/to/install/include -o output
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

## Execution

Once done, execute the binary. If you compiled for SSE4.1 for example, you'll end up with the
following results:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 $ ./output
  x     = (1, 2, 3, 4)
  2*x   = (2, 4, 6, 8)
  x^0.5 = (1, 1.41421, 1.73205, 2)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

That's it, **EVE** is properly installed and ready to use.

# Advanced options

If you want to dig a bit further, you can pass additional options to `cmake` to activate additional features.

| Option                    | Effect                                                                 | Target              |
|:--------------------------|:-----------------------------------------------------------------------|:--------------------|
| `EVE_USE_PCH`             | Enable using precompiled headers for **EVE**. This is `ON` by default  |                     |
| `EVE_BUILD_TEST`          | Enable unit tests for **EVE**. This is `ON` by default                 | `ninja unit`        |
| `EVE_BUILD_BENCHMARKS`    | Enable benchmark tests for **EVE**. This is `OFF` by default           | `ninja benchmarks`  |
| `EVE_BUILD_RANDOM`        | Enable random tests for **EVE**. This is `OFF` by default              | `ninja random`      |
| `EVE_BUILD_DOCUMENTATION` | Enable generation of the HTML documentation cpp files                  | `ninja doxygen`     |

There is currently over 2000 tests, so compiling all unit tests may require a large machine or some time.
