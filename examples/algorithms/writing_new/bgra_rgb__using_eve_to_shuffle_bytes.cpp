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

// We need to construct a formula on how to get from an old index to a new.
// You can allso fill in `eve::pattern<indexes...>` with some meta programming.

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

/*
struct
{
  template <typename N>
  eve::wide<std::uint8_t, N> operator()(eve::wide<std::uint8_t, N> in) const
  {
    return in;
  }
} bgra_to_rgb_swizzle;
*/

// --------------------------------------------

#include "test.hpp"

TTS_CASE("pattern test")
{
  TTS_EQUAL(bgra_to_rgb_pattern_v<4>, (eve::pattern<2, 1, 0, 3>));
  TTS_EQUAL(bgra_to_rgb_pattern_v<8>, (eve::pattern<2, 1, 0, 6, 5, 4, 6, 7>));
}
