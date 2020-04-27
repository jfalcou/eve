//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/csc.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/function/any.hpp>
#include <eve/function/ulpdist.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>


TTS_CASE_TPL("Check eve::csc return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::csc(T(0)), T);
}

TTS_CASE_TPL("Check eve::csc behavior", EVE_TYPE)
{
  auto my_stdcsc =  [](auto x){return eve::rec(std::sin(double(x)));};

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::csc(eve::Nan<T>()) , (eve::Nan<T>()) );
    TTS_IEEE_EQUAL(eve::csc(eve::Inf<T>()) , (eve::Nan<T>()) );
    TTS_IEEE_EQUAL(eve::csc(eve::Minf<T>()), (eve::Nan<T>()) );
  }
  TTS_ULP_EQUAL(eve::csc(T(1)), T(my_stdcsc(v_t(1.0))), 0.5);
  TTS_ULP_EQUAL(eve::csc(T(-1.0)),T(my_stdcsc(v_t(-1.0))), 0.5);
  TTS_IEEE_EQUAL((eve::csc(T(0))), (T(my_stdcsc(v_t(0.0)))));
  TTS_IEEE_EQUAL((eve::csc(T(-0.))), (T(my_stdcsc(v_t(-0.0)))));
  TTS_ULP_EQUAL((eve::csc(eve::Pio_4<T>())), (T(my_stdcsc(eve::Pio_4<v_t>()))), 0.5);
  TTS_ULP_EQUAL((eve::csc(-eve::Pio_4<T>())),(T(my_stdcsc(-eve::Pio_4<v_t>()))), 0.5);
  TTS_ULP_EQUAL(eve::csc(T(100000.0)), T(my_stdcsc(100000.0)), 0.5);
  TTS_ULP_EQUAL(eve::csc(T(-100000.0)),T(my_stdcsc(-100000.0)), 0.5);
  TTS_ULP_EQUAL(((eve::csc)(T(-100000000.0))),T(my_stdcsc(-100000000.0)), 0.5);
  TTS_ULP_EQUAL(((eve::csc)(T(eve::Valmax<T>()))),T(my_stdcsc(eve::Valmax<v_t>())), 1.5);
}
