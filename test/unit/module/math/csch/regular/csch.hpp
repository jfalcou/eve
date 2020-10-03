//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/csch.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE("Check eve::csch return type")
{
  TTS_EXPR_IS(eve::csch(EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::csch behavior")
{

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::csch(eve::nan(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::csch(eve::inf(eve::as<EVE_TYPE>())) , EVE_TYPE(0) );
    TTS_IEEE_EQUAL(eve::csch(eve::minf(eve::as<EVE_TYPE>())), EVE_TYPE(0) );

    TTS_EXPECT(eve::all(eve::is_positive(eve::csch(eve::inf(eve::as<EVE_TYPE>())))) );
    TTS_EXPECT(eve::all(eve::is_negative(eve::csch(eve::minf(eve::as<EVE_TYPE>())))));
  }

  TTS_ULP_EQUAL(eve::csch(EVE_TYPE(1)) , EVE_TYPE(eve::rec(std::sinh(EVE_VALUE(1))) ), 0.5);
  TTS_ULP_EQUAL(eve::csch(EVE_TYPE(-1)), EVE_TYPE(eve::rec(std::sinh(EVE_VALUE(-1)))), 0.5);

  TTS_IEEE_EQUAL(eve::csch(EVE_TYPE( 0 )), eve::inf(eve::as<EVE_TYPE>())  );
  TTS_IEEE_EQUAL(eve::csch(EVE_TYPE(-0.)), eve::minf(eve::as<EVE_TYPE>()) );
}
