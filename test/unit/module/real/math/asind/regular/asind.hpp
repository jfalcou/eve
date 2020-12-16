//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asind.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>

TTS_CASE_TPL("Check eve::asind return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::asind(T(0)), T);
}

TTS_CASE_TPL("Check eve::eve::asind behavior", EVE_TYPE)
{
  using eve::all;
  using eve::is_negative;
  using eve::is_positive;

  if constexpr( eve::platform::supports_nans )
  {
    TTS_IEEE_EQUAL(eve::asind(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::asind(T(2))          , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::asind(T(-2))         , eve::nan(eve::as<T>()) );
  }

  TTS_ULP_EQUAL(eve::asind(T( 0.5)) , T(30) , 0.5);
  TTS_ULP_EQUAL(eve::asind(T(-0.5)) , T(-30), 0.5);
  TTS_ULP_EQUAL(eve::asind(T(-1. )) , T(-90), 0.5);
  TTS_ULP_EQUAL(eve::asind(T( 1. )) , T(90) , 0.5);
  TTS_ULP_EQUAL(eve::asind(T( 0. )) , T(0)  , 0.5);

  TTS_ULP_EQUAL(eve::asind(T(-0.)), T(0), 0.5);

  TTS_EXPECT( all(is_negative(eve::asind(T(-0.)))) );
  TTS_EXPECT( all(is_positive(eve::asind(T(0))))   );
}
