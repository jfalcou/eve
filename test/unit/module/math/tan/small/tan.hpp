//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/tan.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/function/prev.hpp>
#include <eve/function/ulpdist.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::small_(eve::tan) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::small_(eve::tan)(T(0)), (T));
}

TTS_CASE_TPL("Check eve::small_(eve::tan) behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::small_(eve::tan)(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::small_(eve::tan)(eve::inf(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::small_(eve::tan)(eve::Minf<T>()), eve::nan(eve::as<T>()) );
  }

  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::small_(eve::tan)(T( 1)), T(std::tan( 1.0)), 0.5);
  TTS_ULP_EQUAL(eve::small_(eve::tan)(T(-1)), T(std::tan(-1.0)), 0.5);

  TTS_IEEE_EQUAL( eve::small_(eve::tan)(T(0))   , T(0));
  TTS_IEEE_EQUAL( eve::small_(eve::tan)(T(-0.)) , T(0));

  TTS_EXPECT(eve::all(eve::is_negative(eve::small_(eve::tan)(T(-0.)))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::small_(eve::tan)(T( 0 )))));

  TTS_ULP_EQUAL(eve::small_(eve::tan)( eve::Pio_4<T>())  , T(std::tan( eve::Pio_4<v_t>()))  , 0.5);
  TTS_ULP_EQUAL(eve::small_(eve::tan)(-eve::Pio_4<T>())  , T(std::tan(-eve::Pio_4<v_t>()))  , 0.5);
  TTS_ULP_EQUAL(eve::small_(eve::tan)( eve::Pio_4<T>()/2), T(std::tan( eve::Pio_4<v_t>()/2)), 0.5);
  TTS_ULP_EQUAL(eve::small_(eve::tan)(-eve::Pio_4<T>()/2), T(std::tan(-eve::Pio_4<v_t>()/2)), 0.5);

  auto z = eve::Pio_2<v_t>();
  TTS_ULP_EQUAL( eve::small_(eve::tan)(T(z)), T(std::tan(eve::Pio_2<v_t>())), 5.5);

  z = eve::prev(z);
  TTS_ULP_EQUAL( eve::small_(eve::tan)(T(z)), T(std::tan(z)), 1);

  z = eve::prev(z);
  TTS_ULP_EQUAL( eve::small_(eve::tan)(T(z)), T(std::tan(z)), 1);

  z = eve::prev(z);
  TTS_ULP_EQUAL( eve::small_(eve::tan)(T(z)), T(std::tan(z)), 0.5);
}
