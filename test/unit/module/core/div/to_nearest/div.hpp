//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/div.hpp>

TTS_CASE("Check div return type")
{
  TTS_EXPR_IS(eve::to_nearest(eve::div)(EVE_TYPE()  , EVE_TYPE()   ), EVE_TYPE);
  TTS_EXPR_IS(eve::to_nearest(eve::div)(EVE_TYPE()  , EVE_VALUE() ), EVE_TYPE);
  TTS_EXPR_IS(eve::to_nearest(eve::div)(EVE_VALUE(), EVE_TYPE()   ), EVE_TYPE);
}

TTS_CASE("Check eve::to_nearest(eve::div) behavior")
{
  if constexpr(eve::signed_value<EVE_TYPE>)
  {
    TTS_EQUAL(eve::to_nearest(eve::div)(   EVE_TYPE(-1) ,   EVE_TYPE(2)), EVE_TYPE(0));
    TTS_EQUAL(eve::to_nearest(eve::div)( EVE_VALUE(-1) ,   EVE_TYPE(2)), EVE_TYPE(0));
    TTS_EQUAL(eve::to_nearest(eve::div)(   EVE_TYPE(-1) , EVE_VALUE(2)), EVE_TYPE(0));
  }

  TTS_EQUAL(eve::to_nearest(eve::div)(EVE_TYPE(12), EVE_TYPE(4)), EVE_TYPE(3));
  TTS_EQUAL(eve::to_nearest(eve::div)(EVE_TYPE(1) , EVE_TYPE(2)), EVE_TYPE(0));
  TTS_EQUAL(eve::to_nearest(eve::div)(EVE_TYPE(3) , EVE_TYPE(2)), EVE_TYPE(2));
  TTS_EQUAL(eve::to_nearest(eve::div)(EVE_TYPE(5) , EVE_TYPE(2)), EVE_TYPE(2));
  TTS_EQUAL(eve::to_nearest(eve::div)(EVE_TYPE(4) , EVE_TYPE(3)), EVE_TYPE(1));

  TTS_EQUAL(eve::to_nearest(eve::div)(EVE_VALUE(12), EVE_TYPE(4)), EVE_TYPE(3));
  TTS_EQUAL(eve::to_nearest(eve::div)(EVE_VALUE(1) , EVE_TYPE(2)), EVE_TYPE(0));
  TTS_EQUAL(eve::to_nearest(eve::div)(EVE_VALUE(3) , EVE_TYPE(2)), EVE_TYPE(2));
  TTS_EQUAL(eve::to_nearest(eve::div)(EVE_VALUE(5) , EVE_TYPE(2)), EVE_TYPE(2));
  TTS_EQUAL(eve::to_nearest(eve::div)(EVE_VALUE(4) , EVE_TYPE(3)), EVE_TYPE(1));

  TTS_EQUAL(eve::to_nearest(eve::div)(EVE_TYPE(12), EVE_VALUE(4)), EVE_TYPE(3));
  TTS_EQUAL(eve::to_nearest(eve::div)(EVE_TYPE(1) , EVE_VALUE(2)), EVE_TYPE(0));
  TTS_EQUAL(eve::to_nearest(eve::div)(EVE_TYPE(3) , EVE_VALUE(2)), EVE_TYPE(2));
  TTS_EQUAL(eve::to_nearest(eve::div)(EVE_TYPE(5) , EVE_VALUE(2)), EVE_TYPE(2));
  TTS_EQUAL(eve::to_nearest(eve::div)(EVE_TYPE(4) , EVE_VALUE(3)), EVE_TYPE(1));
}
