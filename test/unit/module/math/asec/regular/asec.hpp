//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asec.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>


TTS_CASE_TPL("Check eve::asec return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::asec(T(0)), T);
}

TTS_CASE_TPL("Check eve::asec behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_infinites )
  {
    TTS_IEEE_EQUAL(eve::asec(eve::inf(eve::as<T>())),  eve::pio_2(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::asec(eve::minf(eve::as<T>())), eve::pio_2(eve::as<T>()) );
  }

  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::asec(T(0))   , eve::nan(eve::as<T>()), 1);
    TTS_ULP_EQUAL(eve::asec(T(-0.)) , eve::nan(eve::as<T>()), 1);
    TTS_IEEE_EQUAL(eve::asec(eve::nan(eve::as<T>()))  , (eve::nan(eve::as<T>())) );
  }

  TTS_ULP_EQUAL(eve::asec(T(-2)) , 2*eve::pi(eve::as<T>())/3 , 1   );
  TTS_ULP_EQUAL(eve::asec(T( 2)) , eve::pi(eve::as<T>())/3   , 1   );
  TTS_ULP_EQUAL(eve::asec(T(-1)) , eve::pi(eve::as<T>())     , 0.5 );
  TTS_ULP_EQUAL(eve::asec(T( 1)) , (T(0))           , 0.5 );
}
