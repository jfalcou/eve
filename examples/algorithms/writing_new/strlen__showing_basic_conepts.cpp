//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================

// In this example we will have a look at how some of the eve's concepts
// come together to implement strlen.
//
// This strlen implementation:
//  * Was discussed in this StackOverflow: https://stackoverflow.com/questions/25566302/vectorized-strlen-getting-away-with-reading-unallocated-memory
//  * Is very close to is very close to MacOs x86 strlen: https://opensource.apple.com/source/Libc/Libc-997.90.3/x86_64/string/strlen.s
//  * Also is very close to this glibc arm-v8 implementation: https://code.woboq.org/userspace/glibc/sysdeps/aarch64/multiarch/strlen_asimd.S.html
//  * You can find this example in this talk (with an outdated syntax): https://youtu.be/d6NcnyXjc3I
//
// NOTE: we are not advocating rewriting strlen with EVE, it's just a nice example
//       to show the interfaces and demonstrate high quality codegen.
//
// Idea:
//
// SIMD allows us to test multiple chars at once for zero and that what will do with EVE.
// However, how can we read multiple bytes if the string can be less that what we try to read?
// We are just going to state the solution here, due to a memory being allocated in pages,
// reading from an ALIGNED address will always result in all data being OK to read.
// Details in StackOverflow and a YouTube viedoe mentioned.

#include <eve/conditional.hpp>
#include <eve/module/core.hpp>

std::size_t strlen_(const char* s_) {
  // char in C++ is not guarantied to be a int8_t or a uint8_t.
  // We need to reinterpret cast.
  const auto* s = reinterpret_cast<const std::uint8_t*>(s_);

  // `eve::wide<std::uint8_t>` is a wrapper around the register of the native size.
  // On my machine (avx2 native) this is 32 uint8_ts.
  // So we will be processing 32 chars at one go.
  using wide = eve::wide<std::uint8_t>;

  const wide zeroes{0};  // Just some zeroes to compare against

  // Find the previous aligned address before `s`. This just masks some bits from the bottom.
  // `aligned_ptr` is a wrapper around a pointer that will tell `eve` to use special
  //  instructions for aligned reads. (NOTE: it's a template, we just use CTAD).
  eve::aligned_ptr aligned_s = eve::previous_aligned_address(s);

  // `eve::unsafe(eve::load)` is the same as `eve::load` but it disables sanitizers for it.
  // The machine/OS etc are OK with us reading from an address before `s` but sanitizers consider
  // it to be out of bounds. This an intended usage of the sanitizer disablement.
  wide cur = eve::unsafe(eve::load)(aligned_s);

  // `cur == zeroes` - returns an `eve::logical<wide>`, a register of boolean like values.
  // `first_true`    - given `eve::logical`, returns a position of a first one set (nullopt if none are).
  // `ignore_first`  - between `aligned_s` and `s` there might be a zero.
  //                   This zero would not be in our string, we need to skip it.
  //                   `first_true[ignore_first]` will achieve that.

  eve::ignore_first ignore{s - aligned_s.get()};
  std::optional match = eve::first_true[ignore](cur == zeroes);

  while (!match) {
    aligned_s += wide::size();               // Go to the next position.
    cur = eve::unsafe(eve::load)(aligned_s);
    match = eve::first_true(cur == zeroes);  // No ignore here, since the first value is what we want.
  }

  // Compute the return value:
  //  aligned_s.get() + *match is the position of the 0.
  return static_cast<std::size_t>(aligned_s.get() + *match - s);
}

// The code above closely resembles MacOs x86 strlen, when compiled with sse2.
// The differences are minimal: clang handles the bit and address manipulations slightly differently.

// When comparing against glibc arm-v8, the interesting differences are:
//  * they do not immediatly load from the previous aligned address for the first block.
//    Instead they check if they load from s, and only if not,
//    they start dealing with the previous address.
//  * they compute position of the first match differently.
//  * we compare with 0 and then look for `true` using `umaxv` instruction.
//    They rely on 0 being unsigned minimum and use `uminv` on the register directly.
//    Unfortunatly this trick only works for looking for 0 and we can look for arbitraty value.
//    At least on x86 this made no difference in perf but maybe on arm it's different.

// There are some substantial improvements one can make to this `strlen`,
// like unrolling which can be found in glibc avx2 implementation:
// https://code.woboq.org/userspace/glibc/sysdeps/x86_64/multiarch/strlen-avx2.S.html


// ---------------------------------

#include "test.hpp"

#include <eve/eve.hpp>
#include <eve/memory/aligned_allocator.hpp>

TTS_CASE( "Check strlen, basic")
{
  TTS_EQUAL(strlen_("abc"), 3u);
  TTS_EQUAL(strlen_(""), 0u);
  TTS_EQUAL(strlen_("0000"), 4u);
};

TTS_CASE( "Check strlen_ example exchaustive" )
{
 std::vector<char, eve::aligned_allocator<char, eve::fixed<4096>>> page(4096, 'a');

  // 50 from the beginning
  auto* f = page.data();
  auto* l = f + 50;

  auto run = [&] {
    *l = 0;
    for (auto* it = f; it < l; ++it) {
      std::size_t expected = static_cast<std::size_t>(l - it);
      TTS_EQUAL(expected, strlen_(it));
    }
    *l = 'a';
  };

  while (f < l) {
    run();
    --l;
    *f = 1;
    ++f;
  }

  // 50 from the end
  f = page.data() + page.size() - 50;
  l = page.data() + page.size() - 1;

  while (f < l) {
    run();
    --l;
    ++f;
  }
};
