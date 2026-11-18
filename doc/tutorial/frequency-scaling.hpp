#error This file is for documentation only - DO NOT INCLUDE
/**

@page freqscale Frequency Scaling.

In SIMD programming there is a known issue of processor frequency scaling:
when working with wider registers, in order to avoid overheating, some processors
limit their CPU frequency. There are a lot of situations where this can happen
but it is a noticeable problem mostly for 64 byte registers on intel avx512 cpus.

This is why, for example, if you look at libc, it at most uses 32 byte registers:
sure you might speed up the strlen somewhat but then all the code after will be
slower.

For big datasets the price of lower frequency is often outweighed by processing
more numbers in one operation, and speed-ups of 15% are not unheard of.

This was a sticking point in the API design, but we decided to go with 32 byte
registers by default on AVX512. You can override that default with the
`EVE_AVX512_DEFAULT_64_BYTES` define. The wider registers are always available through
the `eve::max_native_wide` and `eve::max_native_logical` typedefs.
For algorithms, there is the `eve::algo::allow_frequency_scaling` trait.

@note Other than on intel avx512 we always use the maximum register width, since we
expect the compiler to do so anyway and it is generally accepted.
If you want to set a specific width for an algorithm, you can always use
`eve::algo::force_width`.

@snippet tutorial/frequency_scaling.cpp  frequency_scaling_code

**/
