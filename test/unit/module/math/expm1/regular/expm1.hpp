//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/expm1.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE("Check eve::expm1 return type")
{
  TTS_EXPR_IS(eve::expm1(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::expm1 behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::expm1(eve::nan(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()));
    TTS_IEEE_EQUAL(eve::expm1(eve::inf(eve::as<EVE_TYPE>())) , eve::inf(eve::as<EVE_TYPE>()));
    TTS_IEEE_EQUAL(eve::expm1(eve::minf(eve::as<EVE_TYPE>())), EVE_TYPE(-1)        );
  }

  TTS_EXPECT(eve::all(eve::is_negative(eve::expm1(EVE_TYPE(-0.)))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::expm1(EVE_TYPE( 0.)))));

  TTS_IEEE_EQUAL(eve::expm1(EVE_TYPE(0))   , EVE_TYPE(0) );
  TTS_IEEE_EQUAL(eve::expm1(EVE_TYPE(-0.)) , EVE_TYPE(0) );

  TTS_ULP_EQUAL(eve::expm1(EVE_TYPE(1))    , EVE_TYPE(std::expm1(EVE_VALUE(1))), 0.5);
  TTS_ULP_EQUAL(eve::expm1(EVE_TYPE(-1))   ,EVE_TYPE(std::expm1(EVE_VALUE(-1))), 0.5);
}
