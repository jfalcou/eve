#error This file is for documentation only - DO NOT INCLUDE
/**

@page process Manual Data Processing

@tableofcontents

[In a previous tutorial](@ref intro-03), we managed to convert a function using standard algorithm
into a function using SIMD algorithm using `eve::algo`. In general, such function is meant to be applied to a large
set of data instead of a single register. In this tutorial, we'll see how we can write a `for` loop
to process data from a `std::vector` by performing SIMD-aware iterations.

## Building a SIMD loop
Let's consider the code from [the previous tutorial](@ref intro-01) is available. We can write a
short scalar function that will iterate over data and call `to_polar` over each of them.

@snippet tutorial/process.cpp scalar-loop

The process is classic: we iterate over every indexes of both vectors and compute the results to be
stored in the pre-allocated output vectors.

When moving to a SIMD version of this loops, we have to solve two issues:
  - Iteration over data using `eve::wide` instead of `float`
  - Iteration over data which size is not a perfect multiple of SIMD register width

The principles behind turning a loop over scalars to a loop over SIMD registers needs 3 steps:
  - load data from memory into SIMD registers and advance the address by an amount of elements
    equal to the SIMD register width
  - perform the SIMD operation over loaded registers
  - store results back in memory

We already see that `eve::wide` has a constructor to read data from memory into itself and the SIMD
version of our functions. So how do we proceed with the other steps ?

## Iteration steps

`eve::wide` provides an abstraction for accessing informations about the underlying SIMD register
type. To access the number of scalar values stored in an instance of `eve::wide`, one
can use the `size()` class member.

If you need to generically access the more general **cardinal** notion, ie the number of value
stored in a given type including scalar ones, you can use the `eve::cardinal` traits or its
helper variable `eve::cardinal_v`.

## Storing data to memory

Loading data from memory fits nicely as a constructor (even if `eve::load` is a thing for more
complex scenarios), storing data from a `eve::wide` back to memory requires a dedicated function:
`eve::store`.

`eve::store` takes two parameters: the value to store to memory and the pointer to where the value
must be stored.

The complete SIMD loop then looks this way:

@snippet tutorial/process.cpp simd-loop

## Handling extra-data
Looks good but an actual issue has been swept under the rug: what if our vector of data contains
an number of values which is not exactly a multiple of our SIMD register cardinal ?

One strategy is to stop iteration when we loaded the last comple `eve::wide`. This can be done
by computing the first index multiple of `eve::wide<float>::size()` lesser than the size of the
vector.

To do so, you can use `eve::align` to compute such a value by requesting an alignment **under** the
cardinal of the register:

@code
auto last_simd_index = eve::align(x.size(), eve::under{eve::wide<float>::size()});
@endcode

Once done, we need to run a second loop dealing with the remaining data in a scalar way.
The final code then looks like:

@snippet tutorial/process.cpp simd-loop-exact

## Conclusion
In this tutorial, we managed to:
  - write a `for` loop to manually apply our SIMD function over data stored in a `std::vector`
  - adapt this first loop to handle left-overs in data
**/