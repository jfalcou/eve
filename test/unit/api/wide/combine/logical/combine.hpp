//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/combine.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE("Check combining for logical values")
{
  using eve::logical;
  using eve::wide;

  logical<wide<EVE_TYPE, fixed<2>>> ref(true, false);

  TTS_EQUAL((eve::combine(logical<EVE_TYPE>(true), logical<EVE_TYPE>(false))), ref);
}

TTS_CASE_TPL("Check combining for logical wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::logical;
  using eve::wide;

  logical<wide<EVE_TYPE, T>>                         low([](auto i, auto) { return i % 2 < 2; });
  logical<wide<EVE_TYPE, T>>                         high([](auto i, auto) { return i % 2 > 3; });
  logical<wide<EVE_TYPE, typename T::combined_type>> ref([](auto i, auto c) { return i < int(c) / 2; });

  TTS_EQUAL((logical<wide<EVE_TYPE, typename T::combined_type>>(low, high)), ref);
  TTS_EQUAL((eve::combine(low, high)), ref);
}
