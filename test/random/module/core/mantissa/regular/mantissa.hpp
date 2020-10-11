//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/mantissa.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on mantissa", EVE_TYPE)
{
  auto internal_f = [](auto e){  int exp; return std::frexp(e, &exp);  };
  auto std_mantissa = [ internal_f ](auto e) { return internal_f(e)*2; };

  eve::uniform_prng<EVE_VALUE> p(eve::smallestposval(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_mantissa, eve::mantissa);
}
