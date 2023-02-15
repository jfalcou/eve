#error This file is for documentation only - DO NOT INCLUDE
/**

@page Frequency Scaling.

In SIMD programming there is a known issue of processor frequency scaling:
when working with wider registers, in order to avoid overheating, some processors
limit their CPU frequency. There are a lot of situations where this can happen
but it is a noticeable problem mostly for 64 byte registers on intel avx512 cpus.

This is why, for example, if you look at libc, it at most uses 32 byte registers:
sure you might speed up the strlen somewhat but then all the code after will be
slower.

For big datasets the price of lower frequency is often outweighed by processing
more numbers in open operation and seed ups of 15% are not unheard of.

This lead to a dilemma in the API design for us: if the user is on the AVX512 system,
most likely they expect the register to be 64 bytes. But we suspect this is not what
they actually want. So we decided that `eve::wide` on avx512 is by default 64 bytes
but algorithms by default use 32 bytes. If you want to get an algorithm to use 64 byte
you can pass `eve::algo::allow_frequency_scaling` trait.
There are also a typedefs `nofs_wide`, `nofs_logical` where `nofs` stands for
"no frequency scaling".

@note: other than on avx512 on intel we always use the maximum width of the register,
since we expect the compiler to do it anyways and it is usually accepted.
If you want to set a specific cardinal for an algorithm, you can always use
`eve::algo::force_cardinal`.

**/
