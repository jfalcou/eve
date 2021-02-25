//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/arg.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/pi.hpp>
#include <eve/platform.hpp>

TTS_CASE_TPL("Check eve::arg return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::arg(T(0)), T);
}

TTS_CASE_TPL("Check eve::arg behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_infinites )
  {
    TTS_EQUAL( eve::arg(eve::inf(eve::as<T>()))  , T( 0 )       );
    TTS_EQUAL( eve::arg(eve::minf(eve::as<T>())) , eve::pi(eve::as<T>()) );
  }

  TTS_EQUAL( eve::arg(T(-1 )), eve::pi(eve::as<T>()) );
  TTS_EQUAL( eve::arg(T(-0.)), eve::pi(eve::as<T>()) );
  TTS_EQUAL( eve::arg(T( 0 )), T( 0 ) );
  TTS_EQUAL( eve::arg(T( 1 )), T( 0 ) );
}
