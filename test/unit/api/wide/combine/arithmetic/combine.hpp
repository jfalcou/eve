//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/function/combine.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE("Check combining for arithmetic values")
{
  using eve::wide;

  wide<EVE_VALUE, fixed<2>> ref(13, 37);

  TTS_EQUAL((eve::combine(EVE_VALUE(13), EVE_VALUE(37))), ref);
}

TTS_CASE("Check combining for arithmetic wide")
{
  using eve::wide;
  using combined_cardinal = typename EVE_TYPE::cardinal_type::combined_type;

  EVE_TYPE                            low([](auto i, auto) { return 1 + i; });
  EVE_TYPE                            high([](auto i, auto) { return EVE_CARDINAL + 1 + i; });
  wide<EVE_VALUE, combined_cardinal>  ref([](auto i, auto) { return 1 + i; });

  TTS_EQUAL((wide<EVE_VALUE, combined_cardinal>(low, high)), ref);
  TTS_EQUAL((eve::combine(low, high)), ref);
}
