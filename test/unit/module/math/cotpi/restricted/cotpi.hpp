//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cotpi.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::restricted(eve::cotpi) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::restricted(eve::cotpi)(T()), T);
}

TTS_CASE_TPL("Check eve::restricted(eve::cotpi) behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::restricted(eve::cotpi)(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::restricted(eve::cotpi)(eve::inf(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::restricted(eve::cotpi)(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()) );
  }

  TTS_IEEE_EQUAL(eve::restricted(eve::cotpi)(T( 0      )), eve::inf(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::restricted(eve::cotpi)(T(-0.     )), eve::minf(eve::as<T>()));

  TTS_ULP_EQUAL(eve::restricted(eve::cotpi)(T( 0.125) ), T(2.414213562373095048801688724209698078569671875377  ), 0.5);
  TTS_ULP_EQUAL(eve::restricted(eve::cotpi)(T(-0.125) ), T(-2.414213562373095048801688724209698078569671875377 ), 0.5);
}
