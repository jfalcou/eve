//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/gamma.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>

#include <cmath>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::gamma return type") { TTS_EXPR_IS(eve::gamma(EVE_TYPE(0)), (EVE_TYPE)); }

TTS_CASE("Check eve::gamma behavior")
{
  using eve::gamma;
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(gamma(eve::Nan<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()));
    TTS_IEEE_EQUAL(gamma(eve::Inf<EVE_TYPE>()), (eve::Inf<EVE_TYPE>()));
    TTS_IEEE_EQUAL(gamma(eve::Minf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()));
  }
  TTS_ULP_EQUAL(gamma(eve::Zero<EVE_TYPE>()), eve::Inf<EVE_TYPE>(), 0);
  TTS_ULP_EQUAL(gamma(eve::Mzero<EVE_TYPE>()), eve::Minf<EVE_TYPE>(), 0);
  TTS_ULP_EQUAL(gamma(eve::Half<EVE_TYPE>()), EVE_TYPE(std::tgamma(eve::Half<EVE_VALUE>())), 0.5);
  TTS_ULP_EQUAL(gamma(EVE_TYPE(-35)), EVE_TYPE(std::tgamma(EVE_VALUE(-35))), 0.5);
  TTS_ULP_EQUAL(gamma(EVE_TYPE(1)), EVE_TYPE(1), 0);
  TTS_ULP_EQUAL(gamma(EVE_TYPE(2)), EVE_TYPE(1), 0);
  TTS_ULP_EQUAL(gamma(EVE_TYPE(3)), EVE_TYPE(2), 0);
  TTS_ULP_EQUAL(gamma(EVE_TYPE(5)), EVE_TYPE(24), 0);
}
