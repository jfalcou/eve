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
#include <eve/function/prev.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::small_(eve::csc) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::small_(eve::csc)(T()), T);
}

TTS_CASE_TPL("Check eve::small_(eve::csc) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  auto ref_csc =  [](auto x){return eve::rec(std::sin(double(x)));};

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::small_(eve::csc)(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::small_(eve::csc)(eve::Inf<T>()) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::small_(eve::csc)(eve::Minf<T>()), eve::nan(eve::as<T>()) );
  }

  TTS_IEEE_EQUAL(eve::small_(eve::csc)(T( 0 )), T(ref_csc(v_t(0.0))));
  TTS_IEEE_EQUAL(eve::small_(eve::csc)(T(-0.)), T(ref_csc(v_t(-0.0))));

  TTS_ULP_EQUAL(eve::small_(eve::csc)( T(1)              ), T(ref_csc(1.0))                   , 1.0 );
  TTS_ULP_EQUAL(eve::small_(eve::csc)(-T(1)              ), T(ref_csc(-1.0))                  , 1.0 );
  TTS_ULP_EQUAL(eve::small_(eve::csc)(-eve::Pio_2<T>()   ), T(ref_csc(-eve::Pio_2<v_t>()))    , 1.0 );
  TTS_ULP_EQUAL(eve::small_(eve::csc)(-eve::Pio_4<T>()   ), T(ref_csc(-eve::Pio_4<v_t>()))    , 0.75);
  TTS_ULP_EQUAL(eve::small_(eve::csc)(-eve::Pio_4<T>()/ 2), T(ref_csc(-eve::Pio_4<v_t>()/2))  , 0.5 );
  TTS_ULP_EQUAL(eve::small_(eve::csc)( eve::Pio_4<T>()   ), T(ref_csc(eve::Pio_4<v_t>()))     , 0.5 );
  TTS_ULP_EQUAL(eve::small_(eve::csc)( eve::Pio_4<T>()/ 2), T(ref_csc(eve::Pio_4<v_t>()/2))   , 0.75);
  TTS_ULP_EQUAL(eve::small_(eve::csc)(eve::Pio_2<T>()    ), T(ref_csc(eve::Pio_2<v_t>()))     , 1.0 );

  auto z = eve::Pio_2<v_t>();
  TTS_ULP_EQUAL(eve::small_(eve::csc)(T(z)), T(ref_csc(z)), 1);
  z = eve::prev(z);
  TTS_ULP_EQUAL(eve::small_(eve::csc)(T(z)), T(ref_csc(z)), 1);
  z = eve::prev(z);
  TTS_ULP_EQUAL(eve::small_(eve::csc)(T(z)), T(ref_csc(z)), 1);
  z = eve::prev(z);
  TTS_ULP_EQUAL(eve::small_(eve::csc)(T(z)), T(ref_csc(z)), 0.5);
}
