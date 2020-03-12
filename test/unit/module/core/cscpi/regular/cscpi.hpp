//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cscpi.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/rec.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::cscpi return type")
{
  TTS_EXPR_IS(eve::cscpi(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::eve::cscpi behavior")
{
 
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL((eve::cscpi)(eve::Nan<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL((eve::cscpi)(eve::Inf<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL((eve::cscpi)(eve::Minf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()) );   
  }
  TTS_ULP_EQUAL((eve::cscpi)(EVE_TYPE(1)), (eve::Nan<EVE_TYPE>()), 0.5);
  TTS_ULP_EQUAL((eve::cscpi)(EVE_TYPE(-1)),(eve::Nan<EVE_TYPE>()), 0.5);
  TTS_IEEE_EQUAL((eve::cscpi)(EVE_TYPE(0)), (eve::Inf<EVE_TYPE>()));
  TTS_IEEE_EQUAL((eve::cscpi)(eve::Mzero<EVE_TYPE>()), (eve::Minf<EVE_TYPE>()));
  TTS_ULP_EQUAL(((eve::cscpi)(EVE_TYPE(22.5))), (EVE_TYPE(1)), 0.5);
  TTS_ULP_EQUAL(((eve::cscpi)(-EVE_TYPE(22.5))),(EVE_TYPE(-1)), 0.5);
  TTS_ULP_EQUAL(((eve::cscpi)(EVE_TYPE(100000.0))), eve::Nan<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(((eve::cscpi)(EVE_TYPE(-100000.0))),eve::Nan<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(((eve::cscpi)(EVE_TYPE(100000000.0))), eve::Nan<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(((eve::cscpi)(EVE_TYPE(-100000000.0))),eve::Nan<EVE_TYPE>(), 0.5);
}
