//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

// regression test for selection of broadcast_group where Size < Cardinal
TTS_CASE("Shuffle broadcast_group down select")
{
    eve::wide<unsigned char, eve::fixed<32>> w = [](auto i) { return i; };
    eve::wide<unsigned char, eve::fixed<4>> res = eve::shuffle(w,eve::fix_pattern<4>(eve::as_pattern([](auto i, auto) { return i + 8; })));
    eve::wide<unsigned char, eve::fixed<4>> ref{8, 9, 10, 11};
    TTS_EQUAL(res, ref);
};
