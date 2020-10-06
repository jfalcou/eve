//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rem.hpp>

TTS_CASE("Check eve::upward(eve::rem) return type")
{
  TTS_EXPR_IS(eve::upward(eve::rem)(EVE_TYPE()  , EVE_TYPE()  ), EVE_TYPE);
  TTS_EXPR_IS(eve::upward(eve::rem)(EVE_TYPE()  , EVE_VALUE() ), EVE_TYPE);
  TTS_EXPR_IS(eve::upward(eve::rem)(EVE_VALUE() , EVE_TYPE()  ), EVE_TYPE);
}

TTS_CASE("Check eve::upward(eve::rem) behavior")
{
  if constexpr(eve::integral_value<EVE_TYPE> && eve::signed_value<EVE_TYPE>)
  {
    TTS_EQUAL(eve::upward(eve::rem)(  EVE_TYPE(-1),   EVE_TYPE(2)), EVE_TYPE(-1));
    TTS_EQUAL(eve::upward(eve::rem)(EVE_VALUE(-1),   EVE_TYPE(2)), EVE_TYPE(-1));
    TTS_EQUAL(eve::upward(eve::rem)(  EVE_TYPE(-1), EVE_VALUE(2)), EVE_TYPE(-1));
    TTS_EQUAL(eve::upward(eve::rem)(  EVE_TYPE(-4),   EVE_TYPE(3)), EVE_TYPE(-1));
    TTS_EQUAL(eve::upward(eve::rem)(EVE_VALUE(-4),   EVE_TYPE(3)), EVE_TYPE(-1));
    TTS_EQUAL(eve::upward(eve::rem)(  EVE_TYPE(-4), EVE_VALUE(3)), EVE_TYPE(-1));
  }

  TTS_EQUAL(eve::upward(eve::rem)(EVE_TYPE(12), EVE_TYPE(4)), EVE_TYPE( 0));
  TTS_EQUAL(eve::upward(eve::rem)(EVE_TYPE( 1), EVE_TYPE(2)), EVE_TYPE(-1));
  TTS_EQUAL(eve::upward(eve::rem)(EVE_TYPE( 4), EVE_TYPE(3)), EVE_TYPE(-2));

  TTS_EQUAL(eve::upward(eve::rem)(EVE_VALUE(12), EVE_TYPE(4)), EVE_TYPE( 0));
  TTS_EQUAL(eve::upward(eve::rem)(EVE_VALUE( 1), EVE_TYPE(2)), EVE_TYPE(-1));
  TTS_EQUAL(eve::upward(eve::rem)(EVE_VALUE( 4), EVE_TYPE(3)), EVE_TYPE(-2));

  TTS_EQUAL(eve::upward(eve::rem)(EVE_TYPE(12), EVE_VALUE(4)), EVE_TYPE( 0));
  TTS_EQUAL(eve::upward(eve::rem)(EVE_TYPE( 1), EVE_VALUE(2)), EVE_TYPE(-1));
  TTS_EQUAL(eve::upward(eve::rem)(EVE_TYPE( 4), EVE_VALUE(3)), EVE_TYPE(-2));
}
