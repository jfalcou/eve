//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/wide_cast.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check wide_cast behavior when casting to uint16",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>
            )
{
  using eve::as;
  using eve::wide;

  wide<Type , T> arg([](auto i, auto c) { return i+1; });
  wide<std::uint16_t, T> ref([&](auto i, auto c) { return static_cast<std::uint16_t>(arg[i]); });

  TTS_EQUAL(ref, eve::wide_cast(arg, as<std::uint16_t>()));
}
