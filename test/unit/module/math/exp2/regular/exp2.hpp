//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/exp2.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/concept/value.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::exp2 return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::exp2(T(0)), T);
}


TTS_CASE_TPL("Check eve::exp2 behavior", EVE_TYPE)
{
  TTS_ULP_EQUAL (eve::exp2(T(1)), T(2), 0.5);
  TTS_IEEE_EQUAL(eve::exp2(T(0)), T(1));
  TTS_IEEE_EQUAL(eve::exp2(T(4)), T(16));
  if constexpr(eve::signed_integral_value<T>)
  {
    TTS_IEEE_EQUAL(eve::exp2(T(-4)), T(0));
  }

  if constexpr(eve::floating_value<T>)
  {
    if constexpr( eve::platform::supports_invalids )
    {
      TTS_IEEE_EQUAL(eve::exp2(eve::Nan<T>()) , eve::Nan<T>() );
      TTS_IEEE_EQUAL(eve::exp2(eve::Inf<T>()) , eve::Inf<T>() );
      TTS_IEEE_EQUAL(eve::exp2(eve::Minf<T>()), T( 0 ) );
    }

    TTS_IEEE_EQUAL(eve::exp2(T(-0.)), T(1));
    TTS_ULP_EQUAL (eve::exp2(T(-1)) , T(0.5), 0.5);
  }
}

TTS_CASE_TPL("Check single_(eve::exp2) behavior", EVE_TYPE)
{
  if constexpr(eve::integral_value<T>)
  {
    if constexpr(eve::scalar_value<T>)
    {
      TTS_EXPR_IS(eve::double_(eve::exp2)(T(0)), double);
      TTS_EXPR_IS(eve::single_(eve::exp2)(T(0)), float);
      TTS_IEEE_EQUAL(eve::single_(eve::exp2)(T(37)), exp2(T(37)));
      TTS_IEEE_EQUAL(eve::single_(eve::exp2)(T(127)), exp2(T(127)));
      TTS_IEEE_EQUAL(eve::single_(eve::exp2)(T(128)), eve::Inf<float>());
      TTS_IEEE_EQUAL(eve::single_(eve::exp2)(T(129)), eve::Inf<float>());

      TTS_IEEE_EQUAL(eve::double_(eve::exp2)(T(37)), exp2(T(37)));
      TTS_IEEE_EQUAL(eve::double_(eve::exp2)(T(127)), exp2(T(127)));
      TTS_IEEE_EQUAL(eve::double_(eve::exp2)(T(128)), eve::Inf<float>());
      TTS_IEEE_EQUAL(eve::double_(eve::exp2)(T(129)), eve::Inf<float>());
    }
    else
    {
      using f_t = eve::wide<float, eve::cardinal_t<T>>;
      using d_t = eve::wide<double, eve::cardinal_t<T>>;
      TTS_EXPR_IS(eve::double_(eve::exp2)(T(0)), d_t);
      TTS_EXPR_IS(eve::single_(eve::exp2)(T(0)), f_t);
      TTS_IEEE_EQUAL(eve::single_(eve::exp2)(T(37)), f_t(eve::exp2(37.0)));
      TTS_IEEE_EQUAL(eve::single_(eve::exp2)(T(127)), f_t(eve::exp2(127.0)));
      TTS_IEEE_EQUAL(eve::single_(eve::exp2)(T(128)), f_t(eve::Inf<float>()));
      TTS_IEEE_EQUAL(eve::single_(eve::exp2)(T(129)), f_t(eve::Inf<float>()));
    }
  }
  else
    TTS_EQUAL(0, 0);
}
