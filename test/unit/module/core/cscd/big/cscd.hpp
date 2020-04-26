//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cscd.hpp>
#include <eve/function/cscpi.hpp>
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

TTS_CASE("Check eve::big_(eve::cscd) return type")
{
  TTS_EXPR_IS(eve::big_(eve::cscd)(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::big_(eve::cscd) behavior")
{

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::big_(eve::cscd)(eve::Nan<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::big_(eve::cscd)(eve::Inf<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::big_(eve::cscd)(eve::Minf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()) );
  }
  auto std_cscd = [](auto e) { return eve::cscpi(double(e)/180); };

  TTS_ULP_EQUAL(eve::big_(eve::cscd)(EVE_TYPE(1)), EVE_TYPE(std_cscd(1.0)), 3);
  TTS_ULP_EQUAL(eve::big_(eve::cscd)(EVE_TYPE(-1)),EVE_TYPE(std_cscd(-1.0)), 3);
  TTS_IEEE_EQUAL(eve::big_(eve::cscd)(EVE_TYPE(0)),  (eve::Inf<EVE_TYPE>()) );
  TTS_IEEE_EQUAL(eve::big_(eve::cscd)(eve::Mzero<EVE_TYPE>()),  (eve::Minf<EVE_TYPE>()) );
  TTS_ULP_EQUAL((eve::big_(eve::cscd)(EVE_TYPE(45.0))), (EVE_TYPE(std_cscd(EVE_VALUE(45.0)))), 3);
  TTS_ULP_EQUAL((eve::big_(eve::cscd)(-EVE_TYPE(45.0))),(EVE_TYPE(std_cscd(-EVE_VALUE(45.0)))), 3);
  TTS_ULP_EQUAL((eve::big_(eve::cscd)(EVE_TYPE(500.0))), EVE_TYPE(std_cscd(500.0)), 3);
  TTS_ULP_EQUAL((eve::big_(eve::cscd)(EVE_TYPE(-500.0))),EVE_TYPE(std_cscd(-500.0)), 3);

}
