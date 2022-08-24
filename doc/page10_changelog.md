Change Log {#changelog}
==========

## Version 2022.03.0

Codename: [Miranda Numinous](https://en.wikipedia.org/wiki/Miranda_(The_Tempest))

### What's Changed

**This release is an API/ABI breaking changes release.**

A lot of improvements in QoL, QoI, and API have been made.
Some more breaking ABI changes are planned, including a passive move toward
an include file layout more amenable to future modularization.

A bunch of platform supports changes are also in to prepare for new platform
including WASM and **gasp** fixed size SVE.

* Improvements of documentation
 - Revamped docs to add basic 101 tutorials
 - Fixed most documentation to provide Compiler-Explorer-aware samples
 - Correct tutorial example code for if_else
 - Various proofreading by @pauljurczak and @toughengineer

* Improvements on compress (#947, #1013, #1037, #1213)
  - compress_store is a very important function that has been reimplemented to simplify
    its implementation in term of support for iterators
  - better implementation for X86 architectures (SSE2 and BMI).
  - provide an alternative implementation based on switch ()

* Improvements on algorithms
`@DenisYaroshevskiy` did a wonderful job on this front.
  - New algorithm: `reverse` (#1066, #1068)
  - New algorithm: `reverse_copy` (#1060)
  - New algorithm: `iota` (#1016)
  - New algorithm: `fill` (#1119)
  - New views    : `map`, `map_convert` (#889)
  - Fix `copy` backward (#1099, #1111)

* Improvements on wide handling
  - Fix the "no garbage after cardinal" for small wide (#815)
  - Fix aliasing issue in `wide::get` and `wide::set` (#1047)
  - `wide<product_type>` has correct `sizeof`
  - Adapt wide to handle more complex construction from `product_type`
  - Added an emulation layer for `std::experimental::simd` types

* Convert
  - Fixed missing code for `eve::convert`. All convert calls now produce optimal code.
  - More specifically and addition to global fixes, @aguinet contributed:
    - Improvement for u64 => u32 when using AVX2
    - Improvement for u16 => u8 when using AVX2
    - Improvement for u64=>u32 using AVX2 + clang

* Shuffle
  - Removed shuffling via operator[] and introduced `eve::shuffle` (#1103)
  - Added slide_left shuffle (#1088)
  - Added interleave_groups/interleave_groups_shuffle (#1170)
  - Added interleave_groups/interleave_groups_shuffle (#1170)
  - Fix swap_adjacent_group for AVX512 aggregated
  - Implement AVX512 logical pair interleave using BMI parallel bit deposit

* Build systems
  - Install directory fix (Thanks `@JPenuchot`)
  - Prevent CMake error if EVE_BUILD_TEST is set to OFF (#1032)
  - Fix bench compilation issues (#1136)
  - Add CI tests for clang++ with -std=libc++ (#614)
  - Remove dependency to `std::bit_cast` in tests

* Compiler/Platform supports
  - clang++ 13 is now the minimum clang version
  - Added minimum toolchain for WASM
  - Enable partial build on appveyor for MSVC for small test samples
  - Fixed usage of ARM v8 intrinsic in ARM v7 code
  - Fixed a bunch of ULPs boundaries in unit and random tests
  - rat tests use more convenient divisor (#1038)
  - Reactivate wide * scalar optimization for ARM (#993)
  - Removed support for XOP/FMA4
  - Enable compatibility with CPM
  -
* Other changes
  - Constants can now be queried as an interval
  - `eve::top_bits` is now public API (#586)
  - Implements `has_aggregated_component`
  - Implemented airy functions
  - Implemented Lambert function
  - Implemented the omega function
  - Implemented spherical legendre functions
  - Implemented spherical bessel functions
  - Implemented `sign_alternative`: a fast -1^N evaluation
  - Fixed codegen for aggregated operator<< and >>
  - Fixed issue with non-terminating gcd/lcm
  - Make write API consistent with store API
  - Replace `std::forward` by EVE_FWD

### New Contributors
Thanks to all our new contributor for this release!

  * `@aguinet` made their first contribution in https://github.com/jfalcou/eve/pull/1049
  * `@JPenuchot` made their first contribution in https://github.com/jfalcou/eve/pull/1028
  * `@pauljurczak` made their first contribution in https://github.com/jfalcou/eve/pull/1123
  * `@the-moisrex` made their first contribution in https://github.com/jfalcou/eve/pull/1025
  * `@toughengineer` made their first contribution in https://github.com/jfalcou/eve/pull/1182

## Version 2021.10.0

Codename: [Titania Unleashed](https://en.wikipedia.org/wiki/Titania_(A_Midsummer_Night%27s_Dream))

### What's Changed

* First tagged release for **EVE** which includes:
   - Fully functional x86 and AARCH64 supports
   - Standard-like SIMD algorithms
   - Support for adapting `struct` as vectorizable type
   - 389 ready to use numerical functions
   - [Documentation](https://jfalcou.github.io/eve/)

## Version beta.2020.09

Initial beta release
