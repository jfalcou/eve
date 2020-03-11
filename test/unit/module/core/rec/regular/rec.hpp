//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rec.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/sequence.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::rec return type")
{
  TTS_EXPR_IS(eve::rec(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::rec behavior")
{
  if constexpr(std::is_floating_point_v<EVE_VALUE> && eve::platform::supports_infinites)
  {
    TTS_ULP_EQUAL(eve::rec( EVE_TYPE(0)), (eve::Inf<EVE_TYPE>()) , 0.5);
    TTS_ALL_ULP_EQUAL(eve::rec(eve::Mzero<EVE_TYPE>()), (eve::Minf<EVE_TYPE>()), 0.5);
    TTS_ULP_EQUAL(eve::rec( EVE_TYPE(1)), (EVE_TYPE(1))          , 0.5);
    TTS_ULP_EQUAL(eve::rec( EVE_TYPE(2)), (EVE_TYPE(1./2.))      , 0.5);
  }
  else
  {
    if constexpr(std::is_signed_v<EVE_VALUE>)
    {
      TTS_EQUAL(eve::rec(EVE_TYPE(- 1)), (EVE_TYPE(-1)));
      TTS_EQUAL(eve::rec(EVE_TYPE(-47)), (EVE_TYPE( 0)));
    }
    else
    {
      TTS_EQUAL(eve::rec(EVE_TYPE(1)) , (EVE_TYPE(1)));
      TTS_EQUAL(eve::rec(EVE_TYPE(47)), (EVE_TYPE(0)));
    }
  }
}
