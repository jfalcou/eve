//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cos.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::small(eve::cos) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::small(eve::cos)(T(0)), T);
}

TTS_CASE_TPL("Check eve::small(eve::cos) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::small(eve::cos)(eve::nan(eve::as<T>())) , (eve::nan(eve::as<T>())) );
    TTS_IEEE_EQUAL(eve::small(eve::cos)(eve::inf(eve::as<T>())) , (eve::nan(eve::as<T>())) );
    TTS_IEEE_EQUAL(eve::small(eve::cos)(eve::minf(eve::as<T>())), (eve::nan(eve::as<T>())) );
  }

  auto std_cos = [](auto e) { return std::cos(double(e)); };

  TTS_IEEE_EQUAL( eve::small(eve::cos)(T(-0.)), T(1) );
  TTS_IEEE_EQUAL( eve::small(eve::cos)(T( 0.)), T(1) );

  TTS_ULP_EQUAL(eve::small(eve::cos)( T(1)           )         , T(std_cos(1.0))                   , 0.5);
  TTS_ULP_EQUAL(eve::small(eve::cos)(-T(1)           )         , T(std_cos(-1.0))                  , 0.5);
  TTS_ULP_EQUAL(eve::small(eve::cos)( eve::pio_4(eve::as<T>()))         , T(std_cos( eve::pio_4(eve::as<v_t>())))    , 0.5);
  TTS_ULP_EQUAL(eve::small(eve::cos)(-eve::pio_4(eve::as<T>()))         , T(std_cos(-eve::pio_4(eve::as<v_t>())))    , 0.5);
}
