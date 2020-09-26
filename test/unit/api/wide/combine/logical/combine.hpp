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
#include <eve/function/combine.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE("Check combining for logical values")
{
  using eve::logical;
  using eve::wide;

  logical<wide<EVE_VALUE, fixed<2>>> ref(true, false);

  TTS_EQUAL((eve::combine(logical<EVE_VALUE>(true), logical<EVE_VALUE>(false))), ref);
}

TTS_CASE("Check combining for logical wide")
{
  using eve::logical;
  using eve::wide;
  using combined_cardinal = typename T::cardinal_type::combined_type;

  logical<T>                         low([](auto i, auto) { return i % 2 < 2; });
  logical<T>                         high([](auto i, auto) { return i % 2 > 3; });
  logical<wide<EVE_VALUE, combined_cardinal>> ref([](auto i, auto c) { return i < int(c) / 2; });

  TTS_EQUAL((logical<wide<EVE_VALUE, combined_cardinal>>(low, high)), ref);
  TTS_EQUAL((eve::combine(low, high)), ref);
}
