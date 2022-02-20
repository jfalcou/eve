Building and Testing {#dev_cmake}
====================

@tableofcontents

From now on, we make the assumption your Docker instance is running and that you're logged into
its interactive shell as per [the protocol previously defined](@ref dev_environment).
In this tutorial, we will go over the process to configure the tests and run them properly.

@section dev_cmake_setup CMake setup

First, you'd need to create a build directory and cd into it

@verbatim
mkdir build_arch && cd build_arch
@endverbatim

**EVE** provides a set of CMake toolchain files configured for each compiler present in the Docker
instance. You can simply use them to configure your CMake. If you want to pass additional options,
like specific architecture or optimization settings, you can use the `-DEVE_OPTIONS` CMake arguments.

The following table provides the CMake command line used for our classic CI setup using the Ninja
generator.

| Configuration        | CMake command                                                                                                           |
|----------------------|-------------------------------------------------------------------------------------------------------------------------|
| Emulated             | cmake .. -G Ninja -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain/clang.x86.cmake -DEVE_OPTIONS='-DEVE_NO_SIMD'               |
| X86_sse2             | cmake .. -G Ninja -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain/clang.x86.cmake -DEVE_OPTIONS='-msse2'                      |
| X86_sse2-asan        | cmake .. -G Ninja -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain/clang.x86.asan.cmake -DEVE_OPTIONS='-msse2'                 |
| X86_sse4             | cmake .. -G Ninja -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain/clang.x86.cmake  -DEVE_OPTIONS='-msse4'                     |
| X86_avx              | cmake .. -G Ninja -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain/clang.x86.cmake  -DEVE_OPTIONS='-mavx'                      |
| X86_avx2             | cmake .. -G Ninja -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain/clang.x86.cmake  -DEVE_OPTIONS='-mavx2'                     |
| X86_fma              | cmake .. -G Ninja -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain/clang.x86.cmake  -DEVE_OPTIONS='-mavx2 -mfma'               |
| X86_avx512           | cmake .. -G Ninja -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain/clang.x86.cmake  -DEVE_OPTIONS='-march=skylake-avx512'      |
| X86_avx512_no_native | cmake .. -G Ninja -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain/clang.x86.sde.cmake  -DEVE_OPTIONS='-march=skylake-avx512'  |
| Aarch64(arm-v8)      | cmake .. -G Ninja -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain/gcc.aarch64.cmake                                           |
| Arm (arm-v7)         | cmake .. -G Ninja -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchain/gcc.arm.cmake                                               |
| wasm                 | emcmake cmake .. -G Ninja  -DCMAKE_TOOLCHAIN_FILE='../cmake/toolchain/emcc.cmake'                                       |

Once run, your build folder should contain all the necessary artifact to compile and run **EVE**
test suite.

@section dev_build_test Compiling EVE Unit Tests

**EVE** provides a large number of test targets that are grouped by theme. Each of these themes
and tests with a theme can be compiled with a proper target.

In term of options, we encourage you to use the `-DEVE_NO_FORCEINLINE` macro that prevents
costly optimization to be used during the compilation of tests.

The following table list the main high-level themed target.

| Target                        | Content                                       |
|-------------------------------|-----------------------------------------------|
| `doc.exe`                     | Target for all documentation examples         |
| `doc.core.exe`                | Target for functions documentation examples   |
| `examples.exe`                | Target for all tutorials                      |
| `examples.algo.exe`           | Target for algorithms related tutorials       |
| `examples.oop.exe`            | Target for UDT related tutorials              |
| `unit.exe`                    | Target for all unit tests                     |
| `unit.algo.exe`               | Target for standard algorithm unit tests      |
| `unit.api.exe`                | Target for base API unit tests                |
| `unit.arch.exe`               | Target for architecture detection unit tests  |
| `unit.constant.exe`           | Target for constant unit tests                |
| `unit.internals.exe`          | Target for internal components unit tests     |
| `unit.memory.exe`             | Target for memory handling unit tests         |
| `unit.meta.exe`               | Target for traits unit tests                  |
| `unit.real.exe`               | Target for all functions unit tests           |
| `unit.real.algorithm.exe`     | Target for SIMD algorithms unit tests         |
| `unit.real.combinatorial.exe` | Target for combinatorics functions unit tests |
| `unit.real.core.exe`          | Target for arithmetic functions unit tests    |
| `unit.real.elliptic.exe`      | Target for elliptic functions unit tests      |
| `unit.real.math.exe`          | Target for math functions unit tests          |
| `unit.real.polynomial.exe`    | Target for polynomial functions unit tests    |
| `unit.real.probas.exe`        | Target for probability functions unit tests   |
| `unit.real.special.exe`       | Target for special functions unit tests       |

For example, the test for the `abs` function, which is a member of the arithmetic
module, can be compiled via:

@verbatim
ninja unit.real.core.abs.exe
@endverbatim

Once compiled, the test executable are located in the `unit` folder and can be run via:

@verbatim
./unit/unit.real.core.abs.exe
@endverbatim

The `unit.exe` target is very large and requires a comfortable amount of CPUs to be compiled in
parallel.

@section dev_build_random Compiling EVE Random Tests

Random tests run a given function over a samples of random values to test its relative precision.
The following table list the main high-level random target.

| Target                          | Content                                         |
|---------------------------------|-------------------------------------------------|
| `random.exe`                    | Target for all random tests                     |
| `random.algo.exe`               | Target for standard algorithm random tests      |
| `random.api.exe`                | Target for base API random tests                |
| `random.arch.exe`               | Target for architecture detection random tests  |
| `random.constant.exe`           | Target for constant random tests                |
| `random.internals.exe`          | Target for internal components random tests     |
| `random.memory.exe`             | Target for memory handling random tests         |
| `random.meta.exe`               | Target for traits random tests                  |
| `random.real.exe`               | Target for all functions random tests           |
| `random.real.algorithm.exe`     | Target for SIMD algorithms random tests         |
| `random.real.combinatorial.exe` | Target for combinatorics functions random tests |
| `random.real.core.exe`          | Target for arithmetic functions random tests    |
| `random.real.elliptic.exe`      | Target for elliptic functions random tests      |
| `random.real.math.exe`          | Target for math functions random tests          |
| `random.real.polynomial.exe`    | Target for polynomial functions random tests    |
| `random.real.probas.exe`        | Target for probability functions random tests   |
| `random.real.special.exe`       | Target for special functions random tests       |

For example, all the random tests for the `abs` function, which is a member of the arithmetic
module, can be compiled via:

@verbatim
ninja random.real.core.abs.exe
@endverbatim

Once compiled, the test executable are located in the `unit` folder and can be run via:

@verbatim
./unit/unit.real.core.abs.exe
@endverbatim
