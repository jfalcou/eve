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

TTS_CASE("Check eve::pedantic(eve::arg) return type")
{
  TTS_EXPR_IS(eve::pedantic(eve::arg)(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::pedantic(eve::arg) behavior")
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_IEEE_EQUAL( (eve::pedantic(eve::arg)(eve::nan(eve::as<EVE_TYPE>()))), (eve::nan(eve::as<EVE_TYPE>())) );
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_EQUAL( (eve::arg(eve::inf(eve::as<EVE_TYPE>()))) , EVE_TYPE( 0 )         );
    TTS_EQUAL( (eve::arg(eve::minf(eve::as<EVE_TYPE>()))), (eve::pi(eve::as<EVE_TYPE>())) );
  }

  TTS_EQUAL( eve::arg(EVE_TYPE(-1 )), (eve::pi(eve::as<EVE_TYPE>())) );
  TTS_EQUAL( eve::arg(EVE_TYPE( 1 )), (EVE_TYPE( 0 ))       );
  TTS_EQUAL( eve::arg(EVE_TYPE( 0 )), (EVE_TYPE( 0 ))       );
  TTS_EQUAL( eve::arg(EVE_TYPE(-0.)), (eve::pi(eve::as<EVE_TYPE>())) );
}
