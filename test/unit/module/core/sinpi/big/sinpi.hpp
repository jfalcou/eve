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
#include <eve/function/all.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/pi.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE("Check eve::big_(eve::sinpi) return type")
{
  TTS_EXPR_IS(eve::big_(eve::sinpi)(Type(0)), (Type));
}

TTS_CASE("Check eve::big_(eve::sinpi) behavior")
{

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::big_(eve::sinpi)(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::big_(eve::sinpi)(eve::Inf<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::big_(eve::sinpi)(eve::Minf<Type>()), (eve::Nan<Type>()) );   
  }
  auto std_sinpi = [](auto e) { return std::sin(double(e)*eve::Pi<double>()); };
  
  TTS_ULP_EQUAL(eve::big_(eve::sinpi)(Type(1)), Type(0), 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::sinpi)(Type(-1)),Type(0), 0.5);
  TTS_IEEE_EQUAL(eve::big_(eve::sinpi)(Type(0)), (Type(0)));
  TTS_IEEE_EQUAL(eve::big_(eve::sinpi)(eve::Mzero<Type>()), (Type(0)));
  TTS_ULP_EQUAL((eve::big_(eve::sinpi)(Type(0.25))), (Type(std_sinpi(0.25))), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::sinpi)(-Type(0.25))),(Type(std_sinpi(-0.25))), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::sinpi)(Type(100000.0))), Type(0)), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::sinpi)(Type(-100000.0))),Type(0)), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::sinpi)(Type(100000000.0))), Type(0), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::sinpi)(Type(-100000000.0))),Type(0), 0.5);
  }
