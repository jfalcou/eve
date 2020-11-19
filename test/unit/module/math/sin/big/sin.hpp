//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sin.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>


TTS_CASE_TPL("Check eve::big(eve::sin) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::big(eve::sin)(T()), T);
}

TTS_CASE_TPL("Check eve::big(eve::sin) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::big(eve::sin)(eve::nan(eve::as<T>())) , (eve::nan(eve::as<T>())) );
    TTS_IEEE_EQUAL(eve::big(eve::sin)(eve::inf(eve::as<T>())) , (eve::nan(eve::as<T>())) );
    TTS_IEEE_EQUAL(eve::big(eve::sin)(eve::minf(eve::as<T>())), (eve::nan(eve::as<T>())) );
  }

  TTS_IEEE_EQUAL(eve::big(eve::sin)(T( 0 )), T(0));
  TTS_IEEE_EQUAL(eve::big(eve::sin)(T(-0.)), T(0));

  TTS_EXPECT(eve::all(eve::is_negative(eve::big(eve::sin)(T(-0.)))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::big(eve::sin)(T( 0 )))));

  TTS_ULP_EQUAL(eve::big(eve::sin)(T(1))                   , T(std::sin(1.0))                  , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::sin)(T(-1))                  , T(std::sin(-1.0))                 , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::sin)(-eve::pio_4(eve::as<T>()))       , T(std::sin(-eve::pio_4(eve::as<v_t>())))   , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::sin)(eve::pio_4(eve::as<T>()))        , T(std::sin(eve::pio_4(eve::as<v_t>())))    , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::sin)(T(100000.0))            , T(std::sin(100000.0))             , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::sin)(T(-100000.0))           , T(std::sin(-100000.0))            , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::sin)(T(100000000.0))         , T(std::sin(100000000.0))          , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::sin)(T(-100000000.0))        , T(std::sin(-100000000.0))         , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::sin)(T(eve::valmax(eve::as<T>())))    , T(std::sin(eve::valmax(eve::as<v_t>())))   , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::sin)(T(eve::valmax(eve::as<T>())/10)) , T(std::sin(eve::valmax(eve::as<v_t>())/10)), 0.5);
  if constexpr(std::is_same_v<v_t, double>)
  {
    TTS_ULP_EQUAL(eve::big(eve::sin)(T(+2.8481994e+271)), T(std::sin(+2.8481994e+271)), 1.0);
  }
}
