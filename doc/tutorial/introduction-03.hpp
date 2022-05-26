#error This file is for documentation only - DO NOT INCLUDE
/**

@page intro-03 Tuples

In the previous tutorials, we built a SIMD function to compute those cartesian-polar conversions
and we used them in the context of a SIMD algorithm to apply them over an arbitrary set of data.
While doing so, we introduced the eve::views::zip component that helped us gather multiple ranges
into a single one. This worked by feeding eve::algo::transform_to's lambda a tuple of eve::wide.

This interaction between SIMD register and tuple-like types is very interesting and **EVE** provides
different ways to take advantage of these interactions. In this tutorial, we'll go over how **EVE**
can help you design SIMD-aware tuple to write higher level SIMD code.

# Tuple of SIMD registers
If we go back to the initial scalar conversion functions, we can actually merge both `rho` and
`theta` functions in a single `to_polar` function that will return a tuple of float containing
both results of the conversion.

@snippet tutorial/intro-03.cpp  scalar-tuple

This is a classical use case of `std::tuple` to return multiple values from a single function.

The question now is how to turn this code into a SIMD compatible function. A trivial solution
is to just return a `std::tuple<eve::wide<float>, eve::wide<float>>`.

@snippet tutorial/intro-03.cpp  simd-std-tuple

This version of the code just works out of the box. eve::wide is just a C++ type and thus
interacts normally with other standard components.

# SIMD register of tuples
If the previous code is fine, it has the disadvantage of not being compatible to the general SIMD
principle of **EVE**. Indeed, `std::tuple` is not a eve::simd_value even when it contains eve::wide.

A better model should allow us to use eve::wide of tuples. To do so, we use
[**kumi::tuple**](https://jfalcou.github.io/kumi/) instead of `std::tuple`. This change is due to the
higher flexibility of [kumi::tuple](https://jfalcou.github.io/kumi/) and its system of extension.
[**kumi**](https://jfalcou.github.io/kumi/), as a library is integrated within **EVE** through the
`eve/product_type.hpp` header file and does not need any special setup.

Therefore, we can write such a code:

@snippet tutorial/intro-03.cpp  simd-kumi-tuple

The key element is the type of the return value of the function: `eve::wide<kumi::tuple<float,float>>`.
By design, [**kumi::tuple**](https://jfalcou.github.io/kumi/) is able to be used as a template parameter for
eve::wide. How do we interpret this type ? It logically behaves a SIMD register where each lane is
an instance of the [**kumi::tuple**](https://jfalcou.github.io/kumi/). Internally, it is stored as
a [**kumi::tuple**](https://jfalcou.github.io/kumi/) of eve::wide of each tuple's element. In other
words, it performs automatic Array of Structure to Structure of Array conversion.

Now that our function is able to return a type compatible with **EVE** SIMD model, we can amend the
SIMD algorithm call to use eve::views::zip for both the input and output ranges.

@snippet tutorial/intro-03.cpp  simd-transform_zip

# Conclusion
In this tutorial, we managed to:
  - handle tuple in SIMD context using eve::wide and [**kumi::tuple**](https://jfalcou.github.io/kumi/)
  - process SIMD-aware tuple with **EVE** algorithms

[In the next tutorial](@ref intro-04), we'll investigate how such tuples can be replaced by SIMD
aware user-defined types which can then be efficiently stored and processed.
**/
