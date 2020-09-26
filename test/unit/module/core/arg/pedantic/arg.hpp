//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/arg.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>

TTS_CASE_TPL("Check eve::pedantic(eve::arg) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::pedantic(eve::arg)(T(0)), T);
}

TTS_CASE_TPL("Check eve::pedantic(eve::arg) behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_IEEE_EQUAL( (eve::pedantic(eve::arg)(eve::nan(eve::as<T>()))), (eve::nan(eve::as<T>())) );
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_EQUAL( (eve::arg(eve::inf(eve::as<T>()))) , T( 0 )         );
    TTS_EQUAL( (eve::arg(eve::minf(eve::as<T>()))), (eve::pi(eve::as<T>())) );
  }

  TTS_EQUAL( eve::arg(T(-1 )), (eve::pi(eve::as<T>())) );
  TTS_EQUAL( eve::arg(T( 1 )), (T( 0 ))       );
  TTS_EQUAL( eve::arg(T( 0 )), (T( 0 ))       );
  TTS_EQUAL( eve::arg(T(-0.)), (eve::pi(eve::as<T>())) );
}
