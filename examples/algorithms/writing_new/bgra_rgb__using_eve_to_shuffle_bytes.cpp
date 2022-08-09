//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

//
// In this example we have a look at a problem of shuffling bytes around.
// EVE deals with objects spread out in parallel arrays, we do not a good have support
// for arrays of structs (AoS) at the moment.
//
// However, this specific usecase came up in Issue: #1020 and we can address it.
//
// Problem:
// We have a vector of uint8_t, representing BGRA BlueGreenRedAlpha chanes.
// We need to shuffle them into RGB.
//
// NOTE: for this problem the `eve::algo` machinery does not really bring anything and we will just
// use pointers.

#include <eve/conditional.hpp>
#include <eve/eve.hpp>
#include <eve/module/core.hpp>

#include <concepts>
#include <span>

// eve has a swizzles compiler inside:
//   you can move elements around inside a register using a compile time pattern.
//   we will try to find an optimal sequence of instructions to get there.
//
//   The interface looks like wide[eve::pattern<0, 1, 2, 3>].
//
//   Constructing such pattern can be achieved with metaprogramming or with a formula.
//   Here we are using a formula.
//   The output for 8 elements will be pattern<2, 1, 0, 6, 5, 4, 6, 7>.
//   The last 2 elements don't matter for this problem.
//   TODO: maybe we should have an indicator "an index does not matter".

template<std::ptrdiff_t Size>
constexpr eve::pattern_t bgra_to_rgb_pattern_v = eve::fix_pattern<Size>(
    [](int i, int size)
    {
      if( i >= size / 4 * 3 ) return i; // Filling in the same element should be fast.
      int in_base = i / 3 * 4;

      switch ( i % 3 )
      {
        case 0: return in_base + 2; // R
        case 1: return in_base + 1; // G
        case 2: return in_base;     // B
      }
      // unreacheable
      return 0;
    });

// bgra_to_rgb_unsafe/safe
// This will be our main operation.
// The unsafe version will do the bulk of our work, it's when we can load and store the whole n
// elements without needing to mask loads or stores.
// The same version will pass the ignore in to mask loads and stores.

// We don't have to mask load and store version
struct
{
  template<typename N>
  EVE_FORCEINLINE void operator()(std::uint8_t const *&f, std::uint8_t *&o, N n) const
  {
    eve::wide<std::uint8_t, N> loaded   = eve::load(f, n);
    eve::wide<std::uint8_t, N> shuffled = eve::shuffle(loaded,bgra_to_rgb_pattern_v<n()>);
    eve::store(shuffled, o);

    f += n();
    o += n() / 4 * 3;
  }
} inline constexpr bgra_to_rgb_unsafe;

// We have to mask load and store version
struct
{
  template<typename N>
  EVE_FORCEINLINE void operator()(eve::relative_conditional_expr auto ignore,
                                  std::uint8_t const                *&f,
                                  std::uint8_t                      *&o,
                                  N                                   n) const
  {
    eve::wide<std::uint8_t, N> loaded   = eve::load[ignore](f, n);
    eve::wide<std::uint8_t, N> shuffled = eve::shuffle(loaded,bgra_to_rgb_pattern_v<n()>);

    std::ptrdiff_t in_count  = ignore.count(eve::as(loaded));
    std::ptrdiff_t out_count = in_count / 4 * 3;

    eve::store[eve::keep_first(out_count)](shuffled, o);

    f += in_count;
    o += out_count;
  }
} inline constexpr bgra_to_rgb_safe;

std::uint8_t* convert_bgra_to_rgb(std::span<std::uint8_t const> in, std::uint8_t *o)
{
  EVE_ASSERT((in.size() % 4) == 0, "bgra uses 4 bytes per element");

  // Due to not having perfect shuffles, we are going to tweak how many elements we use.
  eve::fixed n = []
  {
    // On avx/avx2 there is no good 32 byte shuffle.
    // So we are going to use 16 byte registers.
    if constexpr( eve::current_api == eve::avx || eve::current_api == eve::avx2 ) return eve::lane<16>;
    // On sse2 the byte shuffles are very poor, so we are going to use 8 bytes at a time.
    // This can be done better with some effort
    else if constexpr( eve::current_api == eve::sse2 ) return eve::lane<8>;
    else                                               return eve::lane<eve::expected_cardinal_v<std::uint8_t>>;
  }();

  // Algorithm works like this:
  // We shuffle an store a register until we can both load a full register and store a full
  // register. Then we have to do masked load/stores in the end.
  //
  // Because the output has less space then the input, we will always do a masked store on the last
  // full register. This is enough because we can store n elements if the output has n / 4 extra
  // space and here we'll have at least n * 3 / 4 extra space.

  std::uint8_t const *f = in.data();
  std::uint8_t const *l = in.data() + in.size();

  // main loop
  if( (l - f) >= 2 * n() )
  {
    std::uint8_t const *precise_l = l - n();
    precise_l                     = f + (precise_l - f) / n() * n();

    // Here we can use `eve::algo::for_each` with no_aligning and divisible_by_cardinal.
    // This could be useful to ask eve to unroll the loop for us.
    // But compiler seems perfectly OK unrolling this so it won't give us anything.

    while( f != precise_l ) bgra_to_rgb_unsafe(f, o, n);
  }

  // The register buffer we left
  // ignore_none is applied to load (which won't do any masking).
  // But for store the operation will compute `keep_first` mask.
  if( (l - f) >= n() ) bgra_to_rgb_safe(eve::ignore_none, f, o, n);

  // The tail
  if( l != f ) bgra_to_rgb_safe(eve::keep_first(l - f), f, o, n);

  return o;
}

// --------------------------------------------

#include <eve/algo/as_range.hpp>

#include "test.hpp"
#include "unit/algo/algo_test.hpp"
#include <numeric>

TTS_CASE("pattern test")
{
  TTS_EQUAL(bgra_to_rgb_pattern_v<4>, (eve::pattern<2, 1, 0, 3>));
  TTS_EQUAL(bgra_to_rgb_pattern_v<8>, (eve::pattern<2, 1, 0, 6, 5, 4, 6, 7>));
};

TTS_CASE("very simple cases")
{
  {
    std::array<std::uint8_t, 4> in {0, 1, 2, 3};
    std::array<std::uint8_t, 3> expected {2, 1, 0};
    std::array<std::uint8_t, 3> actual;
    convert_bgra_to_rgb(in, actual.data());
    TTS_EQUAL(actual, expected);
  }
  {
    std::array<std::uint8_t, 8> in {0, 1, 2, 3, 4, 5, 6, 7};
    std::array<std::uint8_t, 6> expected {2, 1, 0, 6, 5, 4};
    std::array<std::uint8_t, 6> actual;
    convert_bgra_to_rgb(in, actual.data());
    TTS_EQUAL(actual, expected);
  }
};

std::uint8_t*
convert_bgra_to_rgb_scalar(std::span<std::uint8_t const> in, std::uint8_t* o)
{
  for( auto f = in.begin(); f != in.end(); f += 4 )
  {
    o[0] = f[2];
    o[1] = f[1];
    o[2] = f[0];
    o += 3;
  }
  return o;
}

// ---------------
// push data through test

struct convert_bgra_to_rgb_generic_test
{
  std::vector<std::uint8_t> expected;

  void init(auto *, auto *f, auto *l, auto *) { std::iota(f, l, 0); }

  void run(auto rng_)
  {
    auto                    f = eve::unalign(rng_.begin());
    auto                    l = f + ((eve::unalign(rng_.end()) - f) / 4) * 4;
    std::span<std::uint8_t> rng {std::to_address(f), std::to_address(l)};

    std::vector<std::uint8_t> expected(rng.end() - rng.begin());
    std::vector<std::uint8_t> actual(rng.end() - rng.begin());

    int expected_r = convert_bgra_to_rgb_scalar(rng, expected.data()) - expected.data();
    int actual_r   = convert_bgra_to_rgb(rng, actual.data()) - actual.data();

    TTS_EQUAL(expected, actual);
    TTS_EQUAL(expected_r, actual_r);
  }

  void adjust(auto *, auto *f, auto *l, auto *page_end) const
  {
    *f = 1;
    if( l != page_end )
      *l = 1;
  }
};

TTS_CASE("convert_bgra_to_rgb, lots")
{
  algo_test::page_ends_test(eve::as<eve::wide<std::uint8_t>> {},
                            convert_bgra_to_rgb_generic_test {});
};
