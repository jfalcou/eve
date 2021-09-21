//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/acscd.hpp>
#include <eve/function/radindeg.hpp>
#include <eve/function/rec.hpp>

#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on acscd", EVE_TYPE)
{
  auto std_acscd = [](auto e) { return eve::radindeg(std::asin(eve::rec(e))); };

  eve::uniform_prng<EVE_VALUE> p1(eve::valmin(eve::as<EVE_VALUE>()), EVE_VALUE(-1));
  TTS_RANGE_CHECK_WITH(p1, std_acscd, eve::acscd, 4.);

  eve::uniform_prng<EVE_VALUE> p2(EVE_VALUE(1), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK_WITH(p2, std_acscd, eve::acscd, 4.);
}
