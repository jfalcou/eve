#error This file is for documentation only - DO NOT INCLUDE
/**

@page intro-01 SIMD Basic Operations

@tableofcontents

## Initial problem

Let's say we want to convert  2D cartesian coordinates to 2D polar coordinates.
This is a rather common exercise and will only require basic arithmetic and trigonometric functions.

Cartesian coordinates are usually represented by a pair of floating point values \f$(x,y)\f$.
In a similar way, polar coordinate can be represented as a pair \f$(\rho,\theta)\f$ where
\f$\rho\f$ represents the length of the ray and \f$\theta\f$ represents the angle with the X axis.

A bit of geometry in the unit circle leads to a relationship between the cartesian and the polar
coordinate :

<center>
<a  title="WillowW, CC BY-SA 3.0 &lt;https://creativecommons.org/licenses/by-sa/3.0&gt;, via Wikimedia Commons"
    href="https://commons.wikimedia.org/wiki/File:Polar_coordinate_components.svg">
<img width="23%" alt="Polar coordinate components"  class="center"
     src="https://upload.wikimedia.org/wikipedia/commons/thumb/2/23/Polar_coordinate_components.svg/512px-Polar_coordinate_components.svg.png">
</a>
</center>

@snippet tutorial/intro-01.cpp empty

Therefore, we can derive the following C++ functions that perform this conversion:

@snippet tutorial/intro-01.cpp scalar-function

As expected, the code only requires arithmetic operations and some trigonometry.
Fellow mathematicians in the audience may have some remarks on this code. For now, we will
deal with the fact that it requires \f$\theta\f$ to be in radians and that the accuracy of
computing \f$\rho\f$ this way is maybe sub-optimal. We will address those concerns later.

## From scalar to SIMD using eve::wide

The next step is to work a SIMD version of those function. When dealing with SIMD data types,
one has to remember that a single operation has to be performed on multiple value. There, we will
be working on multiple `x`and `y` to computes multiple \f$\rho\f$ and \f$\theta\f$.

SIMD instructions sets provides architecture-specific types for SIMD register along with ISA
specific functions. Of course, handling such types and functions is highly non-portable. To
overcome this issue, **EVE** provides a generic, architecture agnostic type for SIMD computation:
eve::wide.

As **EVE** provides SIMD implementation of all basic operators and all the common math functions
(among others), the conversion from scalar to SIMD is done by:
  - including the proper header files
  - replacing `float` with `eve::wide<float>`
  - calling function from namespace `eve` instead of `std`.

The SIMD version of our convertion functions are then given by:

@snippet tutorial/intro-01.cpp simd-function

eve::wide behaves like a regular type and can just be dropped as a replacement for any C++
arithmetic types.

## Handling eve::wide

The remaining question is how to put data inside an instance of eve::wide so we can write tests
for our SIMD cartesian to polar conversion function.

@snippet tutorial/intro-01.cpp simd-test

There, we construct two instances of eve::wide using three different constructors:

  - `x1` is constructed from a single scalar value. The result is a register with a 4 in every lane.
  - `y1` is constructed from a callable object taking two parameters. The first parameter is the
    current lane to compute, the second is the actual width of the register. The callable object is
    called once per lane with the corresponding lane index. Here, we use a lambda function that
    store `1.5 * (1 + i)` in the \f$i^{th}\f$ lane.
  - `y2` is constructed from a pointer to `float`. This will perform a memory-to-register transfer
    and read `eve::wide<float>::size()` contiguous elements starting from `&data[0]`.

An important detail is to note that neither the eve::wide type nor any of those constructors
requires an *a priori* knowledge of the actual CPU architecture nor the actual number of lane
in the register. This architecture-agnostic style is the main advantage of **EVE** as it guarantees
the portability of the code.

Let's compile this small test using g++:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
g++ intro-01.cpp -O3 -DNDEBUG -I/path/to/eve
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

By default, if you're compiling on a Intel X86_64 machine, the SSE2 SIMD extension set will be used
by the compiler. Under SSE2, SIMD register of `float` have four lanes. So the expected result is:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
(4, 4, 4, 4) (1.5, 3, 4.5, 6) => (4.272, 5, 6.0208, 7.2111)
(4, 4, 4, 4) (1.5, 3, 4.5, 6) => (0.358771, 0.643501, 0.844154, 0.982794)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

But what if we want to use a SIMD extension with larger registers, say AVX2 for example? In this
case, you need to pass the appropriate option to your compiler. For g++, this means using `-mavx2`.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
g++ intro-01.cpp -O3 -DNDEBUG -mavx2 -I/path/to/eve
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

As AVX2 registers are twice as big, the output should now contains 8 values:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
(4, 4, 4, 4, 4, 4, 4, 4) (1.5, 3, 4.5, 6, 7.5, 9, 10.5, 12) => (4.272, 5, 6.0208, 7.2111, 8.5, 9.84886, 11.2361, 12.6491)
(4, 4, 4, 4, 4, 4, 4, 4) (1.5, 3, 4.5, 6, 7.5, 9, 10.5, 12) => (0.358771, 0.643501, 0.844154, 0.982794, 1.08084, 1.15257, 1.20682, 1.24905)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

As expected, **EVE** code scales naturally with the selected architecture at compile time.

## Conclusion
In this first tutorial, we managed to:
  - get familiar with eve::wide, the main SIMD enabling type from **EVE**
  - take a simple scalar operation and turn it into a SIMD function using eve::wide
  - compile the code for various platform and checks the results.
  - be aware of the architecture agnostic style of coding with eve::wide

[In the next tutorial](@ref intro-02), we will use this SIMD function as it should by applying it
over multiple data.
**/
