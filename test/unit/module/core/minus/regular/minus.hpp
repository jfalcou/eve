//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/minus.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/all.hpp>

TTS_CASE("Check eve::minus return type")
{
  TTS_EXPR_IS(eve::minus(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::minus behavior")
{
  TTS_EQUAL(eve::minus(EVE_TYPE( 1)) , static_cast<EVE_TYPE>(-1));
  TTS_EQUAL(eve::minus(EVE_TYPE(-1)) , static_cast<EVE_TYPE>( 1));
  if (eve::floating_value<EVE_TYPE>)
  {
    TTS_EXPECT(eve::all(eve::is_negative(eve::minus(EVE_TYPE( 0 )))));
    TTS_EXPECT(eve::all(eve::is_positive(eve::minus(EVE_TYPE(-0.)))));
  }
}
