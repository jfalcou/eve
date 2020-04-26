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
#include <eve/function/bit_cast.hpp>
#include <eve/function/cosd.hpp>
#include <eve/function/cospi.hpp>
#include <eve/function/exp2.hpp>
#include <eve/function/frexp.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/platform.hpp>

#include <cmath>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::cosd return type") { TTS_EXPR_IS(eve::cosd(EVE_TYPE(0)), (EVE_TYPE)); }

TTS_CASE("Check eve::cosd behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::cosd(eve::Nan<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()));
    TTS_IEEE_EQUAL(eve::cosd(eve::Inf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()));
    TTS_IEEE_EQUAL(eve::cosd(eve::Minf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()));
  }
  auto std_cosd = [](auto e) { return eve::cospi(double(e) / 180); };

  TTS_ULP_EQUAL(eve::cosd(EVE_TYPE(1)), EVE_TYPE(std_cosd(1.0)), 2.0);
  TTS_ULP_EQUAL(eve::cosd(EVE_TYPE(-1)), EVE_TYPE(std_cosd(-1.0)), 2.0);
  TTS_IEEE_EQUAL(eve::cosd(EVE_TYPE(0)), (EVE_TYPE(1)));
  TTS_IEEE_EQUAL(eve::cosd(eve::Mzero<EVE_TYPE>()), (EVE_TYPE(1)));
  TTS_ULP_EQUAL((eve::cosd(EVE_TYPE(45.0))), (EVE_TYPE(std_cosd(EVE_VALUE(45.0)))), 2.0);
  TTS_ULP_EQUAL((eve::cosd(-EVE_TYPE(45.0))), (EVE_TYPE(std_cosd(-EVE_VALUE(45.0)))), 2.0);
  TTS_ULP_EQUAL((eve::cosd(EVE_TYPE(100.0))), EVE_TYPE(std_cosd(100.0)), 3);
  TTS_ULP_EQUAL((eve::cosd(EVE_TYPE(-100.0))), EVE_TYPE(std_cosd(-100.0)), 3);
}
