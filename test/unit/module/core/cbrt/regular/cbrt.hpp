//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cbrt.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>

TTS_CASE("Check eve::cbrt return type")
{
  TTS_EXPR_IS(eve::cbrt(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::eve::cbrt behavior")
{
  using eve::all;
  using eve::is_negative;
  using eve::is_positive;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::cbrt(eve::nan(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::cbrt(eve::inf(eve::as<EVE_TYPE>())) , eve::inf(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::cbrt(eve::minf(eve::as<EVE_TYPE>())), eve::minf(eve::as<EVE_TYPE>()));
  }

  TTS_ULP_EQUAL(eve::cbrt(EVE_TYPE(1))   , EVE_TYPE( 1), 0.5);
  TTS_ULP_EQUAL(eve::cbrt(EVE_TYPE(-1))  , EVE_TYPE(-1), 0.5);
  TTS_ULP_EQUAL(eve::cbrt(EVE_TYPE(8))   , EVE_TYPE( 2), 0.5);
  TTS_ULP_EQUAL(eve::cbrt(EVE_TYPE(-8))  , EVE_TYPE(-2), 0.5);
  TTS_ULP_EQUAL(eve::cbrt(EVE_TYPE(0))   , EVE_TYPE( 0), 0  );
  TTS_ULP_EQUAL(eve::cbrt(EVE_TYPE(-0.)) , EVE_TYPE( 0), 0.5);

  TTS_EXPECT( all(is_negative(eve::cbrt(EVE_TYPE(-0.)))) );
  TTS_EXPECT( all(is_positive(eve::cbrt(EVE_TYPE(0)))  ) );
}
