//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pow_abs.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::raw_(eve::pow_abs) return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::pedantic_(eve::pow_abs)(T(0)   , T(0)  ), T);
  TTS_EXPR_IS(eve::pedantic_(eve::pow_abs)(T(0)   , v_t(0)), T);
  TTS_EXPR_IS(eve::pedantic_(eve::pow_abs)(v_t(0) , T(0)  ), T);
}

TTS_CASE_TPL("Check eve::pedantic_(eve::pow_abs) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::pedantic_(eve::pow_abs)(eve::minf(eve::as<T>()), eve::minf(eve::as<T>())), T(0) );

    TTS_IEEE_EQUAL(eve::pedantic_(eve::pow_abs)(eve::inf(eve::as<T>()) , T(-0.5)       ), T(0)         );
    TTS_IEEE_EQUAL(eve::pedantic_(eve::pow_abs)(eve::inf(eve::as<T>()) , T(0.5)        ), eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pedantic_(eve::pow_abs)(eve::inf(eve::as<T>()) , eve::inf(eve::as<T>()) ), eve::inf(eve::as<T>()));

    TTS_IEEE_EQUAL(eve::pedantic_(eve::pow_abs)(eve::nan(eve::as<T>()) , eve::nan(eve::as<T>()) ), eve::nan(eve::as<T>()));

    TTS_IEEE_EQUAL(eve::pedantic_(eve::pow_abs)(T(0)  , T(-1)         ), eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pedantic_(eve::pow_abs)(T(0)  , T(-2)         ), eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pedantic_(eve::pow_abs)(T(0.5), eve::inf(eve::as<T>()) ), T(0)         );
    TTS_IEEE_EQUAL(eve::pedantic_(eve::pow_abs)(T(0.5), eve::minf(eve::as<T>())), eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::pedantic_(eve::pow_abs)(T(2)  , eve::minf(eve::as<T>())), T(0)         );
    TTS_IEEE_EQUAL(eve::pedantic_(eve::pow_abs)(T(2)  , eve::inf(eve::as<T>()) ), eve::inf(eve::as<T>()));
  }

  TTS_IEEE_EQUAL(eve::pedantic_(eve::pow_abs)(T(-1)  , T(-1))  , T(1));
  TTS_IEEE_EQUAL(eve::pedantic_(eve::pow_abs)(T( 1)  , T( 1))  , T(1));
  TTS_IEEE_EQUAL(eve::pedantic_(eve::pow_abs)(T(-1)  , T( 5))  , T(1));
  TTS_IEEE_EQUAL(eve::pedantic_(eve::pow_abs)(T(-1)  , T( 6))  , T(1));
  TTS_ULP_EQUAL(eve::pedantic_(eve::pow_abs)(T(0.5) , T(0.25)), T(0.840896415253715)            , 2);
  TTS_ULP_EQUAL(eve::pedantic_(eve::pow_abs)(T(0.5) , T(0.25)), T(std::pow(v_t(0.5), v_t(0.25))), 2);
}
