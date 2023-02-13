#error This file is for documentation only - DO NOT INCLUDE
/**

@page intro-02 Algorithms

[In the previous tutorial](@ref intro-01), we managed to convert a sequential function into a function
using SIMD types and functions. In general, such function is meant to be applied to a large
set of data instead of a single register.

As for usual sequential computation, we want to lift ourselves from raw loops and think using
algorithms. **EVE** provides such ready-to-use SIMD aware algorithms and this tutorial will take
a look at how to handle them.

# Initial problem
Let's try to apply our sequential conversion function over data stored in `std::vector` using
standard algorithms.

@snippet tutorial/intro-02.cpp std-transform

Nothing really special here, we apply a given function over some `float` stored in a vector.
Since C++20, you may be accustomed to the range-based version of this code:

@snippet tutorial/intro-02.cpp std-transform-range

Very similar code, except for the fact the input data are passed directly without using iterators.

# Toward SIMD Algorithms
We can turn this range-based code into a SIMD-aware call to one of the algorithms defined in
eve::algo. All algorithms in **EVE** are range-based thus simplifying the transition from code
using standard algorithms.

@snippet tutorial/intro-02.cpp simd-transform

Let's unpack all the new components:

  - the SIMD algorithm used here is eve::algo::transform_to not just `eve::algo::transform`. This is due
    to the fact that discriminating operation between two distinct ranges and in-place operations
    leads to better code generation and performances. If you need to perform in-place computation,
    you can replace eve::algo::transform_to by eve::algo::transform_inplace, its in-place variant.

  - eve::algo::transform_to takes a single input range. To pass multiple parallel ranges, we use
    eve::views::zip that constructs a view over them.

  - as we consume a zipped range, the data passed to the lambda function behaves like a tuple.
    We will dive into details of this tuple later but for now just remember you can retrieve the
    data member exactly like with a regular tuple (using `get` or structured bindings).

# Tuning algorithms
In SIMD algorithms we by default assume that the provided operation is simple (a few instructions),
since this is the common case. This means we use aligned reads and do unrolling, which is an
important optimisation. However, for a complex case, like here, it is beneficial to opt out.

__EVE__ provides various traits to customize algorithms behavior. The traits we're
interested in are:
  - eve::algo::expensive_callable - let's **EVE** know that the passed callable is fairly large.
    By default **EVE** will assume that the passed callables are cheap and it will align loads/stores,
    and unroll the loop body. There are also individual `eve::algo::no_aligning`, `eve::algo::unrolling`

  - eve::algo::allow_frequency_scaling - tells **EVE** to use the maximum avaliable register size even
    if it can substentially temporary reduce processor's frequency. This only makes sense for really big
    arrays or if you spend most of your time doing simd operations.
    (At the moment this is only relevant for avx512). More details in frequency-scaling tutorial.

Algorithms in **EVE** being callable object, you can apply traits using their `[]` operators.
For example, the following code let's **EVE** know that the loop body is heavy.

@snippet tutorial/intro-02.cpp simd-transform-traits

Best strategy is always to benchmark your code and tune algorithms accordingly.

# Conclusion
In this tutorial, we managed to:
  - use a simple algorithms from **EVE** algorithms set
  - use a range view to handle multiple inputs into our algorithm
  - work with SIMD tuple of data
  - tune algorithm using traits

[In the next tutorial](@ref intro-03), we will complete this exercise by demonstrating how
to use all elements seen this far to work directly on user-defined types.
**/
