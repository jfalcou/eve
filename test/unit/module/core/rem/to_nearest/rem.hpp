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
#include <eve/constant/nan.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>

TTS_CASE("Check eve::to_nearest(eve::rem) return type")
{
  TTS_EXPR_IS(eve::to_nearest(eve::rem)(EVE_TYPE() , EVE_TYPE()  ), EVE_TYPE);
  TTS_EXPR_IS(eve::to_nearest(eve::rem)(EVE_TYPE() , EVE_VALUE()), EVE_TYPE);
  TTS_EXPR_IS(eve::to_nearest(eve::rem)(EVE_VALUE(), EVE_TYPE()  ), EVE_TYPE);
}

TTS_CASE_TPL("Check eve::to_nearest(eve::rem) behavior", EVE_TYPE)
{
  if constexpr(eve::integral_value<T> && eve::signed_value<T>)
  {
    TTS_EQUAL(eve::to_nearest(eve::rem)(T(-1)  , T(2) ), T(-1));
    TTS_EQUAL(eve::to_nearest(eve::rem)(EVE_VALUE(-1) , T(2) ), T(-1));
    TTS_EQUAL(eve::to_nearest(eve::rem)(T(-1)  , EVE_VALUE(2)), T(-1));
    TTS_EQUAL(eve::to_nearest(eve::rem)(T(-4)  , T(3) ), T(-1));
    TTS_EQUAL(eve::to_nearest(eve::rem)(EVE_VALUE(-4) , T(3) ), T(-1));
    TTS_EQUAL(eve::to_nearest(eve::rem)(T(-4)  , EVE_VALUE(3)), T(-1));
  }

  TTS_EQUAL(eve::to_nearest(eve::rem)(T(12), T(4)), T(0));
  TTS_EQUAL(eve::to_nearest(eve::rem)(T( 1), T(2)), T(1));
  TTS_EQUAL(eve::to_nearest(eve::rem)(T( 4), T(3)), T(1));

  TTS_EQUAL(eve::to_nearest(eve::rem)(EVE_VALUE(12), T(4)), T(0));
  TTS_EQUAL(eve::to_nearest(eve::rem)(EVE_VALUE( 1), T(2)), T(1));
  TTS_EQUAL(eve::to_nearest(eve::rem)(EVE_VALUE( 4), T(3)), T(1));

  TTS_EQUAL(eve::to_nearest(eve::rem)(T(12), EVE_VALUE(4)), T(0));
  TTS_EQUAL(eve::to_nearest(eve::rem)(T( 1), EVE_VALUE(2)), T(1));
  TTS_EQUAL(eve::to_nearest(eve::rem)(T( 4), EVE_VALUE(3)), T(1));

  if constexpr(eve::floating_value<T>)
  {
    TTS_IEEE_EQUAL(eve::to_nearest(eve::rem)(  T(1),   T(0)), eve::nan(eve::as<T>()));
    TTS_EXPECT(eve::all(eve::is_negative(eve::to_nearest(eve::rem)(  -T(1), T(1)))));
    TTS_EXPECT(eve::all(eve::is_positive(eve::to_nearest(eve::rem)(  T(1) , T(1)))));
  }
}
