#error This file is for documentation only - DO NOT INCLUDE
/**

@page multiarch Handling Multiple Architecture Targets

# The Issue
The **EVE** library uses compile-time code generation process to ensure a high-level of performance.
However, there can be many reasons why your application or library maybe run on unknown systems.
Thus, you may want to be able to write your SIMD kernel once but be able to adapt to your end-user's
hardware.

A first solution could be to just recompile a given kernel with different architecture settings and
link everything. Then, at runtime, use eve::is_supported to choose the correct implementation
between the available ones. If the premise of this idea is correct, you'll face issues as the
core of **EVE** is based on templated callable object, you may end up violating the One Definition
Rule and ends up with a binary containing the incorrect symbols and implementations.

# From static to dynamic dispatch
The correct process is based on the same premisses but avoids those pitfalls. The idea will be to
isolate the various version of a given kernel into separate binaries. In this case, no multiple
definition can happen. This means using **dynamic libraries** to store your code and use
**dynamic loading**.

Dynamic loading in itself is a large topic mostly due to its OS specific components so
[a good read on the subject is maybe in order](https://en.wikipedia.org/wiki/Dynamic_loading).
Once you are acquainted with dynamic loading, let's start building our own SIMD dynamic system.

## Writing the kernel
Let's write a small function that will consume a pointer to a data block containing `float` values
and the size of the data block to process. Inside this kernel, we'll use some algorithms to
vectorise this process.

@snippet test/integration/multi-arch/kernel.cpp kernel

The code breaks down this way:
  + We start by including all the necessary include files for the algorithm, functions and types we
    will use.
  + We define the `compute_kernel` function. This function takes a pointer and a size as parameters
    and is declared `extern "C"` to prevent unwanted C++ mangling of the symbol. This is a classical
    process for dynamic library. Remark we use the `"compute_kernel"` symbol directly. This is possible
    because the `compute_kernel` function has been compiled with `extern "C"`, thus preventing
    C++ mangling to occur.
  + Inside `compute_kernel`, we display some informations about the SIMD API we will be using and
    proceed to the computation. As a quick way to handle the data, we pass a `std::span` to our
    algorithm.

Nothing special is required except for the `extern "C"` attribute. If we want to get around this
limitation and have arbitrary function taking arbitrary C++ types as parameters, there is different
strategies discussed in various place from arbitrarily use the mangled name to just export a function
returning an array or a structure containing all the pre-computed function pointer from the .so.

## Writing the dynamic function hub
We now need to write an actual `compute` function that our users will call. This is the place where
most of the OS dependent code will be written. The example we give is made to work on Linux. For a
more OS independent way to handle dynamic loading, you can give a shot at
[libltdl](https://www.gnu.org/software/libtool/manual/html_node/Using-libltdl.html) or use your
preferred OS API.

The code looks like this:

@snippet test/integration/multi-arch/compute.cpp compute

What is going on inside `compute` ?
  + We first open the correct dynamic library depending on the actual SIMD support detected at
    runtime via eve::is_supported. Notice the names of the .so files, we will go back to those
    afterward but understand that they are arbitrary. To do so, we use *Immediately Invoked Lambda
    Expressions* to perform this initialisation.
  + Next, we load the `compute_kernel` symbol from the handle we just loaded. As opening and fetching
    pointer to symbol can be costly, we will make it so those tasks are done once by storing both
    results in static variables.
  + Once everything is loaded and setup, we call the function pointer with the appropriate parameters.

Obviously, in realistic settings you would actually care about runtime issues, check that every pointers
are non-null, and use functions like `dlerror` to find out what would have caused an issue. This is
left as an exercice for the reader.

## Compiling and Using Dynamic Kernels
THe next part is much more down-to-earth. We need to compile the kernel function inside multiple
dynamic libraries with different set of options. Then, we need to compile the main binary.
To simplify this process, **EVE** provides a CMake function named `eve_build_variants` that you can
access directly when using `find_package` or that can be included manually in your CMake after
installing the library via `include(eve-multiarch)`.

Its synopsis is:
```cmake
eve_build_variants( NAME <name>
                    TARGET      <target suffix>...
                    OPTIONS     <architecture specific options>...
                    [INTERFACE] <name>
                    [QUIET]
                    SOURCES  <source files>...
                  )
```

`eve_build_variants` adds multiple dynamic libraries targets for compiling the source file specified
via `SOURCES`. The generated target will be named by combining the `NAME` and each of the `TARGET`
suffix. For each suffixes, the corresponding options will be used from [OPTIONS].

Optionally, you can pass an `INTERFACE` name to be used for compiling each of the targets.
Optionally, the `QUIET` flag will remove error messages.

OK, let's say we want to compile our kernel for SSE2, SSE4.1 and AVX2.
The CMake code will be looking like:

```cmake
cmake_minimum_required(VERSION 3.19)
project(eve-multi-arch LANGUAGES CXX)

find_package(eve)

eve_build_variants( NAME        compute
                    INTERFACE   ${EVE_LIBRARIES}
                    TARGET      sse2 sse4 haswell
                    OPTIONS     "-msse2"  "-msse4.1" "-mavx2"
                    SOURCES     kernel.cpp
                  )

add_executable(multi-arch main.cpp compute.cpp)
add_dependencies(multi-arch ${eve_compute_variants})
target_link_libraries(multi-arch PUBLIC ${EVE_LIBRARIES})
```

Let's get into the details:
  + After the classical CMake basics, we use `find_package` to grab **EVE**. Depending on where your
    **EVE** installation path, you may have to specify `CMAKE_PREFIX_PATH` for CMake to find it.
  + We call `eve_build_variants` to build a set of targets. The base name will be `compute` and there
    is three different target suffix: `sse2`, `sse4`, `haswell`. For each of those, the following
    options will be used:  `-msse2`, `-msse4.1`, `-mavx2`. Each target is compiled with its corresponding
    options. In the end, we expect three libraries to be compiled: `libcompute_sse2.so`, `libcompute_sse4.so`,
    and `libcompute_haswell.so`. Notice how the suffixes are arbitrary. They just need to correspond
    to any naming scheme you see fit and those names will have to be used in the dynamic loading function.
  + To perform this compilation, we use the `EVE_LIBRARIES` interface that contains all the proper
    setup for compiling **EVE** code.
  + We add out executable target that just compiles a main file and the compute function. To be sure
    we don't forget to compile the libraries when we compile the main executable, we use the exported
    `eve_compute_variants` macro that contains the list of targets created by `eve_build_variants`.

That's all. Once generated, this CMake file will let you compile the `multi-arch` target that will
trigger the compilation of the three libraries. Once compiled, the execution of the multi-arch
executable will produce some output:

```bash
Before:
1 2 3 4 5 6 7 8 10 20 30 40 50 60 70 80 90 100 1000 10000
>> compute with: X86 AVX2
>> eve::wide is: 8 elements large.
After:
2 2.82843 3.4641 4 4.47214 4.89898 5.2915 5.65685 6.32456 8.94427 10.9545 12.6491 14.1421 15.4919 16.7332 17.8885 18.9737 20 63.2456 200
```

The complete project is available as a test in `test\integration\multi-arch`. As an exercice,
try to modify the code to handle AVX512 and checks everything still works.

# Conclusion
Handling multiple architecture within a single application is not trivial. It requires some scaffolding,
much of those being provided by **EVE** itself at both the CMake and C++ level.

**/
