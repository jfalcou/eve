//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/coth.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/rec.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on coth", EVE_TYPE)
{
  auto std_coth = [](auto e) { return eve::rec(std::tanh(e)); };

  eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), EVE_VALUE(-1));
  TTS_RANGE_CHECK(p, std_coth, eve::coth);

  eve::uniform_prng<EVE_VALUE> p1(EVE_VALUE(1), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p1, std_coth, eve::coth);
}
