//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/csch.hpp>
#include <eve/function/all.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/zero.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <cmath>

TTS_CASE("Check eve::csch return type")
{
  TTS_EXPR_IS(eve::csch(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::csch behavior")
{
  
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::csch(eve::Nan<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::csch(eve::Inf<EVE_TYPE>()) , (eve::Zero<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::csch(eve::Minf<EVE_TYPE>()), (eve::Zero<EVE_TYPE>()) ); 
    TTS_EXPECT(eve::all(eve::is_positive(eve::csch(eve::Inf<EVE_TYPE>()))));
    TTS_EXPECT(eve::all(eve::is_negative(eve::csch(eve::Minf<EVE_TYPE>()))));
  }
  TTS_ULP_EQUAL(eve::csch(EVE_TYPE(1)), EVE_TYPE(eve::rec(std::sinh(EVE_VALUE(1)))), 0.5);
  TTS_ULP_EQUAL(eve::csch(EVE_TYPE(-1)),EVE_TYPE(eve::rec(std::sinh(EVE_VALUE(-1)))), 0.5); 
  TTS_IEEE_EQUAL((eve::csch(EVE_TYPE(0))), (eve::Inf<EVE_TYPE>()));
  TTS_IEEE_EQUAL((eve::csch(eve::Mzero<EVE_TYPE>())), (eve::Minf<EVE_TYPE>()));
  }
