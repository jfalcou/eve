#error This file is for documentation only - DO NOT INCLUDE
/**

@page intro-02 Processing Data

@tableofcontents

[In the previous tutorial](@ref intro-01), we managed to convert a scalar function into a function
processing SIMD data using eve::wide. In general, such function is meant to be applied to a large
set of data instead of a single register. In this tutorial, we'll see how we can write a `for` loop
to process data from a `std::vector` by performing SIMD-aware iterations.

## Building a SIMD loop

## Handling extra-data

## Conclusion
In this tutorial, we managed to:
  - write a `for` loop to apply our SIMD function over data stored in a `std::vector`
  - adapt this first loop to handle left-overs in data
  - Compile the code for various platform and checks the results.

[In the next tutorial](@ref intro-03), we will use see how to turn this loop in a call to one of
**EVE** SIMD enabled algorithm.
**/