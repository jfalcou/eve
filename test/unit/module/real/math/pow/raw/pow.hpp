//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pow.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>

TTS_CASE_TPL("Check eve::raw(eve::pow) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::raw(eve::pow)(T(0), T(0)), T);
}

TTS_CASE_TPL("Check eve::raw(eve::pow) behavior", EVE_TYPE)
{
  if constexpr (eve::floating_value<T>)
  {
    TTS_ULP_EQUAL(eve::raw(eve::pow)(T(0), T(-1)), eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::raw(eve::pow)(-T(0), T(-2)), eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::raw(eve::pow)(T(0), T(-2)), eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::raw(eve::pow)(T(0),  eve::minf(eve::as<T>())),  eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::raw(eve::pow)(-T(0),  eve::minf(eve::as<T>())),  eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::raw(eve::pow)(T(0.5), eve::inf(eve::as<T>())),  T( 0 ), 0);
    TTS_ULP_EQUAL(eve::raw(eve::pow)(T(2), eve::inf(eve::as<T>())),  eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::raw(eve::pow)(T(0.5), eve::minf(eve::as<T>())),  eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::raw(eve::pow)(T(2), eve::minf(eve::as<T>())),  T( 0 ), 0);
    TTS_ULP_EQUAL(eve::raw(eve::pow)(eve::inf(eve::as<T>()), T(4) ),  eve::inf(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::raw(eve::pow)(eve::inf(eve::as<T>()), T(-4) ),  T( 0 ), 0);
  }

  TTS_EQUAL(eve::raw(eve::pow)(T(2),-3), T(1/8.0));
  TTS_EQUAL(eve::raw(eve::pow)(T(2),3) , T(8)    );
  TTS_EQUAL(eve::raw(eve::pow)(T(2),3u), T(8)    );
}
