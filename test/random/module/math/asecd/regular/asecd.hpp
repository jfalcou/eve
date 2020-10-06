//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/asecd.hpp>
#include <eve/function/radindeg.hpp>
#include <eve/function/rec.hpp>

#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on asecd", EVE_TYPE)
{
  auto std_asecd = [](auto e) { return eve::radindeg(std::acos(eve::rec(e))); };

  eve::uniform_prng<EVE_VALUE> p1(eve::valmin(eve::as<EVE_VALUE>()), EVE_VALUE(-1));
  TTS_RANGE_CHECK(p1, std_asecd, eve::asecd);

  eve::uniform_prng<EVE_VALUE> p2(EVE_VALUE(1), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p2, std_asecd, eve::asecd);
}
