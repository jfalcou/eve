//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/sec.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::medium_(eve::sec) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::sec(T(0)), T);
}

TTS_CASE_TPL("Check eve::medium_(eve::sec) behavior", EVE_TYPE)
{
  auto my_stdsec =  [](auto x){return eve::rec(std::cos(double(x)));};

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::medium_(eve::sec)(eve::Nan<T>()) , (eve::Nan<T>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::sec)(eve::Inf<T>()) , (eve::Nan<T>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::sec)(eve::Minf<T>()), (eve::Nan<T>()) );
  }
  TTS_ULP_EQUAL(eve::medium_(eve::sec)(T(1)), T(my_stdsec(1.0)), 1.0);
  TTS_ULP_EQUAL(eve::medium_(eve::sec)(T(-1)),T(my_stdsec(-1.0)), 1.0);
  TTS_IEEE_EQUAL(eve::medium_(eve::sec)(T(0)), (eve::One<T>()));
  TTS_IEEE_EQUAL(eve::medium_(eve::sec)(T(-0.)), (eve::One<T>()));
  TTS_ULP_EQUAL((eve::medium_(eve::sec)(eve::Pio_4<T>())), (T(my_stdsec(eve::Pio_4<v_t>()))), 0.75);
  TTS_ULP_EQUAL((eve::medium_(eve::sec)(-eve::Pio_4<T>())),(T(my_stdsec(-eve::Pio_4<v_t>()))), 0.75);
  TTS_ULP_EQUAL((eve::medium_(eve::sec)(T(100.0))), T(my_stdsec(v_t(100.0))), 1.5);
  TTS_ULP_EQUAL((eve::medium_(eve::sec)(T(-100.0))),T(my_stdsec(v_t(-100.0))), 1.5);
  TTS_ULP_EQUAL((eve::medium_(eve::sec)(T(100000.0))), T(my_stdsec(v_t(100000.0))), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::sec)(T(-100000.0))),T(my_stdsec(v_t(-100000.0))), 0.5);
}

