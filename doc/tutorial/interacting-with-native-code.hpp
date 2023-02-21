#error This file is for documentation only - DO NOT INCLUDE
/**

@page inter-with-native Interaction with native code.

In EVE we recognise that we cannot possibly cover all the
individual things you might want to do and it's necessery for
the users to be able to write intrinsics.

That's why eve::wide and eve::logical for native sizes are implicitly
convertible to and from the intrinsic type you'd expect.

* x86: __m128/256/512 for floats and double, __m128i/256i/512i for ints
* neon: int8x8_t, int8x16_t for int8s and similar for other types.
* sve, power: similar.

To combine this with algorithms, force a specific cardinal. All of algorithms
are designed to not require templated callbacks so that you are able to do this.
(unfortunately views still require you to provide a template).

@snippet tutorial/interacting_with_native_code.cpp interating_with_native_algo

# What about non-native sizes?

If the cardinal is less than can be natively represented, it's internally
still represented as a full register. For example wide<int, eve::fixed<2>>
on x86 is still __m128i. The data is at the first 2 elements, the rest can
be garbage.

If the cradinal is larger than the one natively representable, you can
use slice to get to the half the wide size.

@snippet tutorial/interacting_with_native_code.cpp slicing_aggregate

If you write something generally useful, maybe consider contributing?
**/
