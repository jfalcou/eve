//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cospi.hpp>
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

TTS_CASE("Check eve::big_(eve::cospi) return type")
{
  TTS_EXPR_IS(eve::big_(eve::cospi)(Type(0)), (Type));
}

TTS_CASE("Check eve::big_(eve::cospi) behavior")
{

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::big_(eve::cospi)(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::big_(eve::cospi)(eve::Inf<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::big_(eve::cospi)(eve::Minf<Type>()), (eve::Nan<Type>()) );   
  }
  auto std_cospi = [](auto e) { return std::cos(double(e)*eve::Pi<double>()); };
  
  TTS_ULP_EQUAL(eve::big_(eve::cospi)(Type(1)), Type(std_cospi(1.0)), 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::cospi)(Type(-1)),Type(std_cospi(-1.0)), 0.5);
  TTS_IEEE_EQUAL(eve::big_(eve::cospi)(Type(0)), (Type(1)));
  TTS_IEEE_EQUAL(eve::big_(eve::cospi)(eve::Mzero<Type>()), (Type(1)));
  TTS_ULP_EQUAL((eve::big_(eve::cospi)(Type(0.25))), (Type(std_cospi(0.25))), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cospi)(-Type(0.25))),(Type(std_cospi(-0.25))), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cospi)(Type(100000.0))), Type(std_cospi(100000.0)), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cospi)(Type(-100000.0))),Type(std_cospi(-100000.0)), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cospi)(Type(100000000.0))), Type(1), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cospi)(Type(-100000000.0))),Type(1), 0.5);
  }
