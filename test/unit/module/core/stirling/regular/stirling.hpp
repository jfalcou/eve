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
#include <eve/constant/one.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/round.hpp>
#include <eve/function/stirling.hpp>
#include <eve/platform.hpp>

#include <cmath>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::stirling return type") { TTS_EXPR_IS(eve::stirling(EVE_TYPE(0)), (EVE_TYPE)); }

TTS_CASE("Check eve::stirling behavior")
{
  using eve::stirling;
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(stirling(eve::Inf<EVE_TYPE>()), eve::Inf<EVE_TYPE>(), 0.5);
    TTS_ULP_EQUAL(stirling(eve::Minf<EVE_TYPE>()), eve::Nan<EVE_TYPE>(), 0.5);
    TTS_ULP_EQUAL(stirling(eve::Mone<EVE_TYPE>()), eve::Nan<EVE_TYPE>(), 0.5);
    TTS_ULP_EQUAL(stirling(eve::Nan<EVE_TYPE>()), eve::Nan<EVE_TYPE>(), 0.5);
  }

  TTS_ULP_EQUAL(eve::round(stirling(eve::One<EVE_TYPE>())), eve::One<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::round(stirling(EVE_TYPE(2))), eve::One<EVE_TYPE>(), 0.5);
}
