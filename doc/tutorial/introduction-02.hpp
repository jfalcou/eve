#error This file is for documentation only - DO NOT INCLUDE
/**

@page intro-02 SIMD Algorithms

@tableofcontents

[In the previous tutorial](@ref intro-01), we managed to apply a SIMD function over data stored
into some `std::vector`. The implementation of the loop was rather straightforwad but rewriting
all those boundaries computations and other preparatory works can be seen as cumbersome.

As for usual sequential computation, we want to lift ourselves from raw loops and think using
algorithms. **EVE** provides such ready-to-use SIMD aware algorithms and this tutorial will take
a look at how to handle them.

## Simple algorithm transformation
Before modifying our existing code, let's see how the transition from standard to **EVE** algorithm
is performed.

Consider a simple function using `std::transform`:

@snippet tutorial/intro-02.cpp std-transform

Nothing really special here, we apply a given function over some `float` stored in a vector.
Since C++20, you may be accustomed to the range-based version of this code:

@snippet tutorial/intro-02.cpp std-transform-range

Very similar code, except for the fact the input data are passed directly without using iterators.

We can turn this range-based code into a SIMD-aware calls to one of the algorithms defined in
eve::algo. In a manner similar to [how we turned a function into a SIMD version of itself](@ref intro-01),
we can convert this code to its SIMD version:

@snippet tutorial/intro-02.cpp simd-transform

All algorithms in **EVE** are range-based, making the transition direct from std code. One may
notice here that the SIMD algorithm is `eve::algo::transform_to` not just `eve::transform`. This is due
to the fact that discriminating operation between two distinct ranges and in-place operations leads
to better code generation and optimization. For transform, `eve::algo::transform_to` is associated with
`eve::algo::transform_inplace`, its in-place variant.

Note how the lambda function passed to `eve::algo::transform_to` can explicitly take an instance of
`eve::wide`. You can of course use `auto` or template parameter but the 1:1 type substitution works
right out of the box.

## From multiple ranges to zipped ranges
This first example was tailored made to fit in a single call to one algorithm. But what if we want
to use **EVE** algorithms to apply our `to_polar` and `to_cartesian` function over a block of data.
Clearly, we need to have a way to gather the two input vector of data and return a tuple-like
entity for the results.

First, we need to adapt the way we return data from our functions as a `std::tuple` is clearly not
something you can store directly into a `std::vector<float>`.

@snippet tutorial/intro-02.cpp simd-tuple

@snippet tutorial/intro-02.cpp simd-transform_zip

## Conclusion
In this tutorial, we managed to:
  - use a simple algorithms from **EVE** algorithms set
  - use an iterator wrapper to implement a non-trivial transformation
  - define SIMD version of tuples and how to compute and return them

[In the next tutorial](@ref intro-03), we will complete this exercise by demonstrating how
to use all elements seen this far to work directly on user-defined types and SIMD-aware containers
for such types.
**/