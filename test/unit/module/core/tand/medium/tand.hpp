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
#include <eve/function/all.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/tand.hpp>
#include <eve/function/tanpi.hpp>
#include <eve/platform.hpp>

#include <cmath>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::medium_(eve::tand) return type")
{
  TTS_EXPR_IS(eve::medium_(eve::tand)(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::medium_(eve::tand) behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::medium_(eve::tand)(eve::Nan<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()));
    TTS_IEEE_EQUAL(eve::medium_(eve::tand)(eve::Inf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()));
    TTS_IEEE_EQUAL(eve::medium_(eve::tand)(eve::Minf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()));
  }
  auto std_tand = [](auto e) { return eve::tanpi(double(e) / 180); };

  TTS_ULP_EQUAL(eve::medium_(eve::tand)(EVE_TYPE(1)), EVE_TYPE(std_tand(1.0)), 3.0);
  TTS_ULP_EQUAL(eve::medium_(eve::tand)(EVE_TYPE(-1)), EVE_TYPE(std_tand(-1.0)), 3.0);
  TTS_IEEE_EQUAL(eve::medium_(eve::tand)(EVE_TYPE(0)), (EVE_TYPE(0)));
  TTS_IEEE_EQUAL(eve::medium_(eve::tand)(eve::Mzero<EVE_TYPE>()), (EVE_TYPE(0)));
  TTS_ULP_EQUAL(
      (eve::medium_(eve::tand)(EVE_TYPE(45.0))), (EVE_TYPE(std_tand(EVE_VALUE(45.0)))), 3.0);
  TTS_ULP_EQUAL(
      (eve::medium_(eve::tand)(-EVE_TYPE(45.0))), (EVE_TYPE(std_tand(-EVE_VALUE(45.0)))), 3.0);
  TTS_ULP_EQUAL((eve::medium_(eve::tand)(EVE_TYPE(500.0))), EVE_TYPE(std_tand(500.0)), 6.0);
  TTS_ULP_EQUAL((eve::medium_(eve::tand)(EVE_TYPE(-500.0))), EVE_TYPE(std_tand(-500.0)), 6.0);
}
