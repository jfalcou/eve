//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cospi.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>


TTS_CASE_TPL("Check eve::restricted(eve::cospi) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::restricted(eve::cospi)(T(0)), T);
}

TTS_CASE_TPL("Check eve::restricted(eve::cospi) behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T> )
  {
    if constexpr( eve::platform::supports_invalids )
    {
      TTS_IEEE_EQUAL(eve::restricted(eve::cospi)(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
      TTS_IEEE_EQUAL(eve::restricted(eve::cospi)(eve::inf(eve::as<T>())) , eve::nan(eve::as<T>()) );
      TTS_IEEE_EQUAL(eve::restricted(eve::cospi)(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()) );
    }

    TTS_IEEE_EQUAL(eve::restricted(eve::cospi)(T(-0.)), T(1) );
    TTS_IEEE_EQUAL(eve::restricted(eve::cospi)(T(0))  , T(1) );
    TTS_ULP_EQUAL(eve::restricted(eve::cospi)( T(0.0625)),T(0.98078528040323044912618223613423903697393373089333), 0.5);
    TTS_ULP_EQUAL(eve::restricted(eve::cospi)(-T(0.0625)),T(0.98078528040323044912618223613423903697393373089333), 0.5);
  }
  else if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::restricted(eve::cospi)(T( 1)) , T(-1));
    TTS_EQUAL(eve::restricted(eve::cospi)(T(-1)) , T(-1));
    TTS_EQUAL(eve::restricted(eve::cospi)(T( 2)) , T( 1));
    TTS_EQUAL(eve::restricted(eve::cospi)(T(-2)) , T( 1));
  }
}
