#error This file is for documentation only - DO NOT INCLUDE
/**

@page inter-with-native Interaction with native code.

In EVE we recognise that we cannot possibly cover all the
individual things you might want to do and it is necessary for
the users to be able to write intrinsics.

That is why eve::wide and eve::logical for native sizes are implicitly
convertible to and from the intrinsic type you would expect.

  * x86: __m128/256/512 for floats and double, __m128i/256i/512i for ints
  * neon: int8x8_t, int8x16_t for int8s etc.
  * sve, powerpc: ....

To combine this with `eve::algorithm`s we have to force a specific cardinal. All algorithms
are designed to do not require templated callbacks so this remains possible.
But, unfortunately views still require a templated callback.

@snippet tutorial/interacting_with_native.cpp interacting_with_native_algo

# What about non-native sizes?

If the number is less than the one that can be natively represented, it's internally
still represented as a full register. For example wide<int, eve::fixed<2>>
on x86 is still __m128i. The relevant data just occupy the first 2 elements, the others can
be garbage.

If the cardinal is larger than the one that can be natively represented, you can
use slice to get to the half the wide size.

@snippet tutorial/interacting_with_native.cpp slicing_aggregate

If you write something generally useful, maybe consider contributing?
**/
