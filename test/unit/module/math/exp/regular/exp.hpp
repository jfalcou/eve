//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/exp.hpp>
#include <eve/function/next.hpp>
#include <eve/function/prev.hpp>
#include <eve/function/is_denormal.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/minlog.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE("Check eve::exp return type")
{
  TTS_EXPR_IS(eve::exp(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::exp behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::exp(eve::nan(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::exp(eve::inf(eve::as<EVE_TYPE>())) , eve::inf(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::exp(eve::minf(eve::as<EVE_TYPE>())), EVE_TYPE( 0 ) );
  }

  TTS_ULP_EQUAL(eve::exp(EVE_TYPE(1)), EVE_TYPE(std::exp(EVE_VALUE(1))), 0.5);
  TTS_ULP_EQUAL(eve::exp(EVE_TYPE(-1)),EVE_TYPE(std::exp(EVE_VALUE(-1))), 0.5);

  TTS_IEEE_EQUAL( eve::exp(EVE_TYPE( 0.)), EVE_TYPE(1));
  TTS_IEEE_EQUAL( eve::exp(EVE_TYPE(-0.)), EVE_TYPE(1));
  TTS_ULP_EQUAL (eve::exp(eve::minlog(eve::as<EVE_TYPE>())), EVE_TYPE(0), 0.5);
  TTS_ULP_EQUAL (eve::exp(eve::next(eve::minlog(eve::as<EVE_TYPE>()))),EVE_TYPE(std::exp(eve::minlog(eve::as<EVE_VALUE>()))), 256.5);
}
