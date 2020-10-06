//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/frac.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>

TTS_CASE("Check eve::frac return type")
{
  TTS_EXPR_IS(eve::frac(EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::frac behavior")
{
  TTS_EQUAL(eve::frac(EVE_TYPE(0)), EVE_TYPE(0));
  TTS_EQUAL(eve::frac(EVE_TYPE(2)), EVE_TYPE(0));

  if constexpr(eve::signed_value<EVE_TYPE>)
  {
    TTS_EQUAL(eve::frac(static_cast<EVE_TYPE>(-2)), EVE_TYPE(0) );
    TTS_EQUAL(eve::frac(static_cast<EVE_TYPE>(1)) , EVE_TYPE(0) );
  }

  if constexpr(eve::floating_value<EVE_TYPE>)
  {
    TTS_EQUAL(eve::frac(EVE_TYPE(-3/2.)), EVE_TYPE(-0.5));
    TTS_EQUAL(eve::frac(EVE_TYPE( 3/2.)), EVE_TYPE( 0.5));

    TTS_ULP_EQUAL(eve::frac(EVE_TYPE( 4/3.)), EVE_TYPE( 1/3.), 0.5);
    TTS_ULP_EQUAL(eve::frac(EVE_TYPE(-4/3.)), EVE_TYPE(-1/3.), 0.5);
    TTS_EXPECT(eve::all(eve::is_negative(eve::frac(EVE_TYPE(-0.0)))));
    TTS_EXPECT(eve::all(eve::is_positive(eve::frac(EVE_TYPE(0.0)))));
  }
}
