//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cot.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_denormal.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::restricted_(eve::cot) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::restricted_(eve::cot)(T(0)), T);
}

TTS_CASE_TPL("Check eve::restricted_(eve::cot) behavior", EVE_TYPE)
{
  auto my_stdcot =  [](auto x){return eve::rec(std::tan(double(x)));};

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::restricted_(eve::cot)(eve::Nan<T>()) , (eve::Nan<T>()) );
    TTS_IEEE_EQUAL(eve::restricted_(eve::cot)(eve::Inf<T>()) , (eve::Nan<T>()) );
    TTS_IEEE_EQUAL(eve::restricted_(eve::cot)(eve::Minf<T>()), (eve::Nan<T>()) );
  }
  TTS_ULP_EQUAL(eve::restricted_(eve::cot)(T(1)), eve::Nan<T>(), 0.5);
  TTS_ULP_EQUAL(eve::restricted_(eve::cot)(T(-1)),eve::Nan<T>(), 0.5);
  TTS_IEEE_EQUAL(eve::restricted_(eve::cot)(T(0)), (eve::Inf<T>()));
  TTS_IEEE_EQUAL(eve::restricted_(eve::cot)(T(-0.)), (eve::Minf<T>()));
  TTS_ULP_EQUAL((eve::restricted_(eve::cot)(eve::Pio_4<T>())), (T(my_stdcot(eve::Pio_4<v_t>()))), 0.5);
  TTS_ULP_EQUAL((eve::restricted_(eve::cot)(-eve::Pio_4<T>())),(T(my_stdcot(-eve::Pio_4<v_t>()))), 0.5);

  TTS_ULP_EQUAL((eve::restricted_(eve::cot)(eve::Pio_4<T>()/2)), (T(my_stdcot(eve::Pio_4<v_t>()/2))), 0.5);
  TTS_ULP_EQUAL((eve::restricted_(eve::cot)(-eve::Pio_4<T>()/2)),(T(my_stdcot(-eve::Pio_4<v_t>()/2))), 0.5);
}
