//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
//// if TTS_CORRECTED is defined and tts is still not corrected
////  the test -s123456 fails with g++10.2
//// else the old reduction routine is taken and all is good...
//// see rempio2.hpp
//// #define TTS_CORRECTED
#include <eve/function/cos.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include "producers.hpp"
#include <cmath>

TTS_CASE("wide random check on cos")
{
  auto std_cos = [](auto e) { return std::cos(e); };

  eve::uniform_prng<EVE_VALUE> p(eve::valmin(eve::as<EVE_VALUE>()), eve::valmax(eve::as<EVE_VALUE>()));
  TTS_RANGE_CHECK(p, std_cos, eve::big(eve::cos));
}
