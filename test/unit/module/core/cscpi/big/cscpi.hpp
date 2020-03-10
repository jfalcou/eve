//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cscpi.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pi.hpp>
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
  TTS_EXPR_IS(eve::cscpi(Type(0)), (Type));
}

TTS_CASE("Check eve::eve::cscpi behavior")
{

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::big_(eve::cscpi)(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::big_(eve::cscpi)(eve::Inf<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::big_(eve::cscpi)(eve::Minf<Type>()), (eve::Nan<Type>()) );   
  }
  TTS_ULP_EQUAL(eve::big_(eve::cscpi)(Type(1)), (eve::Nan<Type>()), 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::cscpi)(Type(-1)),(eve::Nan<Type>()), 0.5);
  TTS_IEEE_EQUAL(eve::big_(eve::cscpi)(Type(0)), (eve::Inf<Type>()));
  TTS_IEEE_EQUAL(eve::big_(eve::cscpi)(eve::Mzero<Type>()), (eve::Minf<Type>()));
  TTS_ULP_EQUAL((eve::big_(eve::cscpi)(Type(22.5))), (Type(1)), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cscpi)(-Type(22.5))),(Type(-1)), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cscpi)(Type(100000.0))), eve::Nan<Type>(), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cscpi)(Type(-100000.0))),eve::Nan<Type>(), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cscpi)(Type(100000000.0))), eve::Nan<Type>(), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cscpi)(Type(-100000000.0))),eve::Nan<Type>(), 0.5);
}
