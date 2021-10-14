//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================


//
// In this example we have a look at a problem of shuffling bytes around.
// EVE deals with objects spread out in parallel arrays, we do not a good have support
// for arrays of structs (AoS) at the moment.
//
// However, this specific usecase came up in Issue: #1020
//
// Problem:
// We have a vector of uint8_t, representing BGRA BlueGreenRedAlpha chanes.
// We need to shuffle them into RGB.
//

#include <eve/eve.hpp>
#include <eve/conditional.hpp>
#include <eve/algo/for_each.hpp>

#include <concepts>
#include <span>

// We need to construct a formula on how to get from an old index to a new.
// 2, 1, 0, duplicated for each 4 elements.
//
// If we didn't want to use a formula, we could genenerate `eve::pattern<indexes...>`
// with some meta programming.
template <std::ptrdiff_t Size>
constexpr auto bgra_to_rgb_pattern_v = eve::fix_pattern<Size>(
  [] (int i, int size) {
    if (i >= size / 4 * 3) return i;  // Filling in the same element should be fast.
    int in_base = i / 3 * 4;
    // R index is 2
    if (i % 3 == 0) return in_base + 2;
    // G index is 1
    if (i % 3 == 1) return in_base + 1;
    // B index is 0
    /*i % 3 == 2 */
    return in_base;
  }
);


// The working horse of our algorithm.
// Shuffle the input and store it to the output.

struct
{
  template <typename N, eve::relative_conditional_expr C>
  EVE_FORCEINLINE
  std::uint8_t* operator()(C ignore,
                           eve::wide<std::uint8_t, N> in,
                           std::uint8_t* out
                          ) const
  // We can't just support arbitrary ignore,
  // it makes no sense to ignore some number of bytes from the beginning.
  // We don't have a good concept for that unfortunatly.
  requires std::same_as<C, eve::ignore_none_> ||
           std::same_as<C, eve::ignore_last> ||
           std::same_as<C, eve::keep_first>
  {
    auto cvted_ignore = [&]{
      if constexpr ( C::is_complete ) return ignore;
      else return eve::keep_first(ignore.count(eve::as(in)) / 4 * 3);
    }();

    auto shuffled = in[bgra_to_rgb_pattern_v<N{}()>];

    eve::store[cvted_ignore](shuffled, out);
    return out + ignore.count(eve::as(in));
  }
} inline constexpr bgra_to_rgb_swizzle_store;

std::span<std::uint8_t>::iterator
convert_bgra_to_rgb(std::span<std::uint8_t const> in, std::span<std::uint8_t> out)
{
  // Disable aligning.
  // We should probably also tweak unrolling since how well the shuffle will do
  // Depends on what's avaliable

  eve::algo::traits basic_traits{
    eve::algo::no_aligning, // can't align in this algorithm
    eve::algo::unroll<4>
  };

  // On avx/avx2 there is no good 32 byte shuffle.
  // So we are going to use 16 byte registers.
  //
  // The sse2 byte shuffles are fairly awful all over the place.
  // For now we will just use 8 bytes of chars but if we think about it we can do better.
  auto tweaks = [&] {
    if constexpr (eve::current_api == eve::avx || eve::current_api == eve::avx2)
    {
      return eve::algo::traits{eve::algo::force_cardinal<16>};
    }
    else if constexpr (eve::current_api == eve::sse2)
    {
      return eve::algo::traits{eve::algo::force_cardinal<8>};
    }
    else
    {
      return eve::algo::traits{};
    }
  }();

  auto traits = eve::algo::default_to(tweaks, basic_traits);

  std::uint8_t* out_ptr = out.data();

  eve::algo::for_each[traits](in, [&](auto it, auto ignore) {
    auto loaded = eve::load[ignore](it);
    out_ptr = bgra_to_rgb_swizzle_store(ignore, loaded, out_ptr);
  });

  return out.begin() + (out_ptr - out.data());
}

// --------------------------------------------

#include "test.hpp"

TTS_CASE("pattern test")
{
  TTS_EQUAL(bgra_to_rgb_pattern_v<4>, (eve::pattern<2, 1, 0, 3>));
  TTS_EQUAL(bgra_to_rgb_pattern_v<8>, (eve::pattern<2, 1, 0, 6, 5, 4, 6, 7>));
}

TTS_CASE("very simple cases")
{
  {
    std::array<std::uint8_t, 4> in       {0, 1, 2, 3};
    std::array<std::uint8_t, 3> expected {2, 1, 0 };
    std::array<std::uint8_t, 3> actual;
    convert_bgra_to_rgb(in, actual);
    TTS_EQUAL(actual, expected);
  }
  {
    std::array<std::uint8_t, 8> in       {0, 1, 2, 3, 4, 5, 6, 7};
    std::array<std::uint8_t, 6> expected {2, 1, 0, 6, 5, 4 };
    std::array<std::uint8_t, 6> actual;
    convert_bgra_to_rgb(in, actual);
    TTS_EQUAL(actual, expected);
  }
}
