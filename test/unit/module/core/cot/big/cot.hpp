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
#include <eve/function/all.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::big_(eve::cot) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::big_(eve::cot)(T(0)), T);
}

// TTS_CASE_TPL("Check eve::big_(eve::cot) behavior", EVE_TYPE)
// {
//   auto my_stdcot =  [](auto x){return eve::rec(std::tan(double(x)));};

//   if constexpr( eve::platform::supports_invalids )
//   {
//     TTS_IEEE_EQUAL(eve::big_(eve::cot)(eve::Nan<T>()) , (eve::Nan<T>()) );
//     TTS_IEEE_EQUAL(eve::big_(eve::cot)(eve::Inf<T>()) , (eve::Nan<T>()) );
//     TTS_IEEE_EQUAL(eve::big_(eve::cot)(eve::Minf<T>()), (eve::Nan<T>()) );
//   }
//   TTS_ULP_EQUAL(eve::big_(eve::cot)(T(1)), T(my_stdcot(1.0)), 1.0);
//   TTS_ULP_EQUAL(eve::big_(eve::cot)(T(-1)),T(my_stdcot(-1.0)), 1.0);
//   TTS_IEEE_EQUAL(eve::big_(eve::cot)(T(0)), (eve::Inf<T>()));
//   TTS_IEEE_EQUAL(eve::big_(eve::cot)(T(-0.)), (eve::Minf<T>()));
//   TTS_ULP_EQUAL((eve::big_(eve::cot)(eve::Pio_4<T>())), (T(my_stdcot(eve::Pio_4<v_t>()))), 1.5);
//   TTS_ULP_EQUAL((eve::big_(eve::cot)(-eve::Pio_4<T>())),(T(my_stdcot(-eve::Pio_4<v_t>()))), 1.5);
//   TTS_ULP_EQUAL((eve::big_(eve::cot)(T(100000.0))), T(my_stdcot(100000.0)), 0.5);
//   TTS_ULP_EQUAL((eve::big_(eve::cot)(T(-100000.0))),T(my_stdcot(-100000.0)), 0.5);
//   TTS_ULP_EQUAL((eve::big_(eve::cot)(T(100000000.0))), T(my_stdcot(100000000.0)), 0.5);
//   TTS_ULP_EQUAL((eve::big_(eve::cot)(T(-100000000.0))),T(my_stdcot(-100000000.0)), 0.5);
//   TTS_ULP_EQUAL((eve::big_(eve::cot)(T(eve::Valmax<T>()))),T(my_stdcot(eve::Valmax<v_t>())), 1.5);
//   TTS_ULP_EQUAL((eve::big_(eve::cot)(T(eve::Valmax<T>()))/10),T(my_stdcot(eve::Valmax<v_t>())/10), 1.5);
// }
