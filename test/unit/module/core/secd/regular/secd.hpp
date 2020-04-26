//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/secd.hpp>
#include <eve/function/secpi.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>
#include <eve/function/frexp.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/exp2.hpp>

TTS_CASE("Check _(eve::secd) behavior")
{

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL((eve::secd)(eve::Nan<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL((eve::secd)(eve::Inf<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL((eve::secd)(eve::Minf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()) );
  }
  auto std_secd = [](auto e) { return eve::secpi(double(e)/180); };

  TTS_ULP_EQUAL((eve::secd)(EVE_TYPE(1)), EVE_TYPE(std_secd(1.0)), 3);
  TTS_ULP_EQUAL((eve::secd)(EVE_TYPE(-1)),EVE_TYPE(std_secd(-1.0)), 3);
  TTS_IEEE_EQUAL((eve::secd)(EVE_TYPE(0)), (EVE_TYPE(1)));
  TTS_IEEE_EQUAL((eve::secd)(eve::Mzero<EVE_TYPE>()), (EVE_TYPE(1)));
  TTS_ULP_EQUAL(((eve::secd)(EVE_TYPE(45.0))), (EVE_TYPE(std_secd(EVE_VALUE(45.0)))), 3);
  TTS_ULP_EQUAL(((eve::secd)(-EVE_TYPE(45.0))),(EVE_TYPE(std_secd(-EVE_VALUE(45.0)))), 3);
  TTS_ULP_EQUAL(((eve::secd)(EVE_TYPE(500.0))), EVE_TYPE(std_secd(500.0)), 3);
  TTS_ULP_EQUAL(((eve::secd)(EVE_TYPE(-500.0))),EVE_TYPE(std_secd(-500.0)), 3);

}
