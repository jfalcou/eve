Change Log {#changelog}
==========

## Version 2022.09.0

Codename: [Rosalind Serendipitous](https://en.wikipedia.org/wiki/Rosalind_(As_You_Like_It))

### What's Changed

A lot. The main non-code changes is our move from MIT License to the BOOST SOFTWARE License.
Next to that, support for more algorithms and complex numbers has been added.

Starting this fall, we will also try to provide more regular release.

**This release is an API/ABI breaking changes release.**

* ABI/API changes
  - Promote module like includes by removing eve/function/ (See #1378)
  - EVE support for automatic differentiation has been moved to https://github.com/codereckons/fluxion (See #1309, #1324)
  - Reworked the basic concepts used to discriminate scalar and SIMD values (See #1144, #1306, #1307, #1314)
  - diff_of_prod/sum_of_prod are now more precise and propose a raw variant (See #1369)
  - Architecture tag and object names has been streamlined to be easier to use (See #1319)
  - category API was cleaned up (See #1399)

* New features
  - Added newest Boost.Constant support (See #1291)
  - Added support for EVE complex numbers type and functions (See #1289, #1308, #1310, #1301)
  - Implemented Jacobi polynomial (See #1284)
  - Implemented better Tchebytchev polynomial (See #1292)
  - First steps for SVE-fixed size support (See #1341, #1364, #1376, #1386)
  - Added support for more masked functions (See #1384)
  - Implemented last_true (See #1340)
  - Implemented predicated min/max (See #1337)
  - Implemented eve::algo::min_value and eve::algo::min_element (See #1345)
  - Implemented eve::algo::max_value and eve::algo::max_element (See #1372)
  - Implemented eve::algo::transform_reduce (See #1335)
  - Implemented eve::algo::find_last (See #1347, #1368)

* Performances fixes
  - Optimized is_ltz for g++ x86 (See #1302)
  - Better cleanup for functions sliding data in from incomplete wide (See #1315)
  - Improve conditional code-gen by replacing some lambda by FORCEINLINE callable (See #1383)
  - Better integral conversions (See #1408)
  - Calling zip with iota now use alignment (See #1322)

* Build system
  - Fix compilation for g++ 12.1 (See #1296)
  - Updated tests and infrastructure to use latest TTS to speedup compile times (See #1313)
  - Add find_package support (#1318)
  - Provide CMake machinery and example for multi-arch support (See #1321)
  - Refactored EVE's exported CMake target and installation by @justend29 in (See #1336)
  - Automated integration tests and correct their fetches by @justend29 in (See #1338)

* Documentation
  - Add link to EVE bibtex (See #1282)
  - Documentation style and layout changed to become more readable (See #1299)
  - README: Fix links to website by @Simran-B (See #1303)
  - Added more documentation for algorithms (See #1349)
  - Add a local doxygen generation target to simplify documentation works (See #1392)

* Other Fixes
  - Fixed ASAN checks (See #1305,  #1288)
  - Fix compile error when wide is included after some functions (See #1391)
  - Missing constexpr leads to constants in the output (See #1396)
  - Conversion from conditional to logical has been cleaned up (See #1374)

### New Contributors
Thanks to all our new contributor for this release!

  - @Simran-B made their first contribution in (See #1303)
  - @justend29 made their first contribution in (See #1338)

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
