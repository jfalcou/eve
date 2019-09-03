//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef COMBINE_HPP
#define COMBINE_HPP

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

  logical<wide<Type, fixed<2>>> ref(true, false);

  TTS_EQUAL((eve::combine(logical<Type>(true), logical<Type>(false))), ref);
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

  logical<wide<Type, T>>                         low([](auto i, auto) { return i % 2 < 2; });
  logical<wide<Type, T>>                         high([](auto i, auto) { return i % 2 > 3; });
  logical<wide<Type, typename T::combined_type>> ref([](auto i, auto c) { return i < int(c) / 2; });

  TTS_EQUAL((logical<wide<Type, typename T::combined_type>>(low, high)), ref);
  TTS_EQUAL((eve::combine(low, high)), ref);
}

#endif
