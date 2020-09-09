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
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::restricted_(eve::cot) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::restricted_(eve::cot)(T()), T);
}

TTS_CASE_TPL("Check eve::eve::restricted_(eve::cot) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  auto ref_cot =  [](auto x) { return eve::rec(std::tan(double(x))); };

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::restricted_(eve::cot)(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::restricted_(eve::cot)(eve::Inf<T>()) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::restricted_(eve::cot)(eve::Minf<T>()), eve::nan(eve::as<T>()) );
  }

  TTS_IEEE_EQUAL(eve::restricted_(eve::cot)(T( 0 )) , eve::Inf<T>() );
  TTS_IEEE_EQUAL(eve::restricted_(eve::cot)(T(-0.)) , eve::Minf<T>());
  TTS_IEEE_EQUAL(eve::restricted_(eve::cot)( T(1 )) , eve::nan(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::restricted_(eve::cot)(-T(1 )) , eve::nan(eve::as<T>()) );

  TTS_ULP_EQUAL(eve::restricted_(eve::cot)( eve::Pio_4<T>())  , T(ref_cot( eve::Pio_4<v_t>())), 1  );
  TTS_ULP_EQUAL(eve::restricted_(eve::cot)(-eve::Pio_4<T>())  , T(ref_cot(-eve::Pio_4<v_t>())), 1  );
  TTS_ULP_EQUAL(eve::restricted_(eve::cot)( eve::Pio_4<T>()/2), T(ref_cot( eve::Pio_4<v_t>()/2)), 0.5);
  TTS_ULP_EQUAL(eve::restricted_(eve::cot)(-eve::Pio_4<T>()/2), T(ref_cot(-eve::Pio_4<v_t>()/2)), 0.5);
}
