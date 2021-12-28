#error This file is for documentation only - DO NOT INCLUDE
/**

@page intro-03 SIMD User-Defined Types

@tableofcontents

In the previous tutorials, we built a SIMD function to computes those cartesian-polar conversions
and we used them in the context of a SIMD algorithm to apply them over an arbitrary set of data.
While doing so, we introduced the eve::views::zip component that helped us gather multiple ranges
into a single one. This worked by feeding eve::algo::transform_to's lambda a tuple of eve::wide.

This interaction between SIMD register and tuple-like types is very interesting and **EVE** provides
different ways to take advantage of these interactions. In this tutorial, we'll go over how **EVE**
can help you design SIMD-aware tuple and user-defined type to write high level SIMD code.

@snippet tutorial/intro-03.cpp  empty

## Tuple of SIMD registers
If we go back to the initial scalar conversion function, we can actually merge both `rho` and
`theta` functions in a single `to_polar` function that will return a tuple of float containing
both result of the conversion.

@snippet tutorial/intro-03.cpp  scalar-tuple

This is a classical use case of `std::tuple` to return multiple values from a single function.

The question now is how to turn this code into a SIMD compatible function. A trivial solution
is to just return a `std::tuple<eve::wide<float>, eve::wide<float>>`.

@snippet tutorial/intro-03.cpp  simd-std-tuple

This version of the code just works out of the box. eve::wide are just regular types and thus
interacts normally with other standard component.

## SIMD register of tuples
If the previous code is fine, it has the disadvantage to not be compatible of the general SIMD
principle of **EVE**. Indeed, `std::tuple` is not a eve::simd_value even when it contains eve::wide.

A better model should allow us to use eve::wide of tuples. To do so, we use
[kumi::tuple](https://jfalcou.github.io/kumi/) instead of `std::tuple`. This change is due to the
higher flexibility of[kumi::tuple](https://jfalcou.github.io/kumi/) and its system of extension.
[kumi](https://jfalcou.github.io/kumi/), as a library is integrated within **EVE** through the
`eve/product_type.hpp` header file and does not need any special setup.

Therefore, we can write such a code:

@snippet tutorial/intro-03.cpp  simd-kumi-tuple

The key element is the return type of the function: `eve::wide<kumi::tuple<float,float>>`.
TODO FINISH HERE

## SIMD register of UDT
Using tuples as a random bag of values returned from functions is sometimes lackluster. Indeed, one
may need to return data structure with proper semantic or which members have a proper semantic.
User-defined types with named members is then preferred.

Following this trend, we can rewrite our scalar `to_polar` function to return a proper structure.

@snippet tutorial/intro-03.cpp scalar-udt

### Adapting existing UDT
traits + operators

### Creating a SIMD-aware UDT

eve::struct_support

## Conclusion
In this tutorial, we managed to:
**/
