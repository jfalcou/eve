//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asinpi.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::asinpi return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::asinpi(T(0)), T);
}

TTS_CASE_TPL("Check eve::eve::asinpi behavior", EVE_TYPE)
{
  using eve::all;
  using eve::is_negative;
  using eve::is_positive;

  if constexpr( eve::platform::supports_nans )
  {
    TTS_IEEE_EQUAL(eve::asinpi(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::asinpi(T(2))          , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::asinpi(T(-2))         , eve::nan(eve::as<T>()) );
  }

  TTS_ULP_EQUAL(eve::asinpi(T( 0.5)) , T(1./6)  , 0.5);
  TTS_ULP_EQUAL(eve::asinpi(T(-0.5)) , T(-1./6) , 0.5);
  TTS_ULP_EQUAL(eve::asinpi(T(-1. )) , T(-0.5)  , 0.5);
  TTS_ULP_EQUAL(eve::asinpi(T( 1. )) , T(0.5)   , 0.5);
  TTS_ULP_EQUAL(eve::asinpi(T( 0. )) , T(0)     , 0.5);

  TTS_ULP_EQUAL(eve::asinpi(T(-0.)), T(0), 0.5);

  TTS_EXPECT( all(is_negative(eve::asinpi(T(-0.)))) );
  TTS_EXPECT( all(is_positive(eve::asinpi(T(0))))   );
}
