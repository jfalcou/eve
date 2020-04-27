//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sin.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::small_(eve::sin) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::small_(eve::sin)(T(0)), T);
}

TTS_CASE_TPL("Check eve::small_(eve::sin) behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::small_(eve::sin)(eve::Nan<T>()) , (eve::Nan<T>()) );
    TTS_IEEE_EQUAL(eve::small_(eve::sin)(eve::Inf<T>()) , (eve::Nan<T>()) );
    TTS_IEEE_EQUAL(eve::small_(eve::sin)(eve::Minf<T>()), (eve::Nan<T>()) );
  }
  TTS_ULP_EQUAL(eve::small_(eve::sin)(T(1)),  T(std::sin(1.0)), 0.5);
  TTS_ULP_EQUAL(eve::small_(eve::sin)(T(-1)), T(std::sin(-1.0)), 0.5);
  TTS_IEEE_EQUAL((eve::small_(eve::sin)(T(0))), (T(0)));
  TTS_IEEE_EQUAL((eve::small_(eve::sin)(T(-0.))), (T(0)));
  TTS_EXPECT(eve::all(eve::is_negative(eve::small_(eve::sin)(T(-0.)))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::small_(eve::sin)(T( 0 )))));
  TTS_ULP_EQUAL((eve::small_(eve::sin)(eve::Pio_2<T>())), (T(std::sin(eve::Pio_2<v_t>()))), 0.5);
  TTS_ULP_EQUAL((eve::small_(eve::sin)(-eve::Pio_2<T>())),(T(std::sin(-eve::Pio_2<v_t>()))), 0.5);
  TTS_ULP_EQUAL((eve::small_(eve::sin)(eve::Pio_4<T>())), (T(std::sin(eve::Pio_4<v_t>()))), 0.5);
  TTS_ULP_EQUAL((eve::small_(eve::sin)(-eve::Pio_4<T>())),(T(std::sin(-eve::Pio_4<v_t>()))), 0.5);
  TTS_ULP_EQUAL((eve::small_(eve::sin)(eve::Pio_4<T>()/2)), (T(std::sin(eve::Pio_4<v_t>()/2))), 0.5);
  TTS_ULP_EQUAL((eve::small_(eve::sin)(-eve::Pio_4<T>()/2)),(T(std::sin(-eve::Pio_4<v_t>()/2))), 0.5);
}
