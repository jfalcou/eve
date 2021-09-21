//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/sqrt.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on sqrt", EVE_TYPE)
{
  auto std_sqrt = [](auto e) { return std::sqrt(e); };

  eve::uniform_prng<EVE_VALUE> p(EVE_VALUE(0), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_sqrt, eve::sqrt);
}
