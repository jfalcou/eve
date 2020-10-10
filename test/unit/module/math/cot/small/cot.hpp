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
#include <eve/function/rec.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/platform.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::small(eve::cot) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::small(eve::cot)(T()), T);
}

TTS_CASE_TPL("Check eve::eve::small(eve::cot) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  auto ref_cot =  [](auto x) { return eve::rec(std::tan(double(x))); };

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::small(eve::cot)(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::small(eve::cot)(eve::inf(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::small(eve::cot)(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()) );
  }

  TTS_IEEE_EQUAL(eve::small(eve::cot)(T( 0 )), eve::inf(eve::as<T>())  );
  TTS_IEEE_EQUAL(eve::small(eve::cot)(T(-0.)), eve::minf(eve::as<T>()) );

  TTS_ULP_EQUAL(eve::small(eve::cot)( T(1))            , T(ref_cot(v_t(1.0)))          , 1  );
  TTS_ULP_EQUAL(eve::small(eve::cot)(-T(1))            , T(ref_cot(v_t(-1.0)))         , 1  );
  TTS_ULP_EQUAL(eve::small(eve::cot)( eve::pio_4(eve::as<T>())) , T(ref_cot( eve::pio_4(eve::as<v_t>()))), 1  );
  TTS_ULP_EQUAL(eve::small(eve::cot)(-eve::pio_4(eve::as<T>())) , T(ref_cot(-eve::pio_4(eve::as<v_t>()))), 1  );
  TTS_ULP_EQUAL(eve::small(eve::cot)( eve::pio_2(eve::as<T>())) , T(ref_cot( eve::pio_2(eve::as<v_t>()))), 3.5);
  TTS_ULP_EQUAL(eve::small(eve::cot)(-eve::pio_2(eve::as<T>())) , T(ref_cot(-eve::pio_2(eve::as<v_t>()))), 3.5);
}
