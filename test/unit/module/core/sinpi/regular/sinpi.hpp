//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sinpi.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/pi.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::sinpi return type")
{
  TTS_EXPR_IS(eve::sinpi(Type(0)), (Type));
}

TTS_CASE("Check eve::sinpi behavior")
{
  auto std_sinpi = [](auto e) { return std::sin(double(e)*eve::Pi<double>()); };
  
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::sinpi(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::sinpi(eve::Inf<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::sinpi(eve::Minf<Type>()), (eve::Nan<Type>()) );   
  }
  TTS_ULP_EQUAL(eve::sinpi(Type(1)), Type(std_sinpi(1.0)), 0.5);
  TTS_ULP_EQUAL(eve::sinpi(Type(-1)),Type(std_sinpi(-1.0)), 0.5);
  TTS_IEEE_EQUAL((eve::sinpi(Type(0))), (Type(1)));
  TTS_IEEE_EQUAL((eve::sinpi(eve::Mzero<Type>())), (Type(1)));
  TTS_ULP_EQUAL((eve::sinpi(Type(0.25))), (Type(std_sinpi(0.25))), 0.5);
  TTS_ULP_EQUAL((eve::sinpi(-Type(0.25))),(Type(std_sinpi(-0.25))), 0.5);
  TTS_ULP_EQUAL(eve::sinpi(Type(100000.0)), Type(std_sinpi(100000.0)), 0.5);
  TTS_ULP_EQUAL(eve::sinpi(Type(-100000.0)),Type(std_sinpi(-100000.0)), 0.5);
  TTS_ULP_EQUAL(((eve::sinpi)(Type(-100000000.0))),Type(0), 0.5);
  TTS_ULP_EQUAL(((eve::sinpi)(Type(100000000.0))),Type(0), 0.5);   
}
