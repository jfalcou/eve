//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special.hpp>
#include <cmath>

TTS_CASE_TPL("wide random check on gamma", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  auto std_tgamma = [](auto e) { return std::tgamma(e); };

  eve::uniform_prng<T>  p ( eve::minlog(eve::as<EVE_VALUE>()) + 1
                          , eve::maxlog(eve::as<EVE_VALUE>()) - 1
                          );

  TTS_RANGE_CHECK(p, std_tgamma, eve::pedantic(eve::tgamma));
};
