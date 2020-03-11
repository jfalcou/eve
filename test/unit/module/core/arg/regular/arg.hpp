//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/arg.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/pi.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::arg return type")
{
  TTS_EXPR_IS(eve::arg(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::arg behavior")
{
  if constexpr( eve::platform::supports_infinites )
  {
    TTS_EQUAL( (eve::arg(eve::Inf<EVE_TYPE>())) , (eve::Zero<EVE_TYPE>()) );
    TTS_EQUAL( (eve::arg(eve::Minf<EVE_TYPE>())), (eve::Pi<EVE_TYPE>())   );
  }

  TTS_EQUAL( (eve::arg(eve::Mone<EVE_TYPE>()))  , (eve::Pi<EVE_TYPE>())   );
  TTS_EQUAL( (eve::arg(eve::One<EVE_TYPE>()))   , (eve::Zero<EVE_TYPE>()) );
  TTS_EQUAL( (eve::arg(eve::Zero<EVE_TYPE>()))  , (eve::Zero<EVE_TYPE>()) );
  TTS_EQUAL( (eve::arg(eve::Mzero<EVE_TYPE>())) , (eve::Pi<EVE_TYPE>())   );
}
