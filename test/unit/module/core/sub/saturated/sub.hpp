//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sub.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <type_traits>

TTS_CASE("Check eve::saturated(eve::sub) return type")
{
  TTS_EXPR_IS(eve::saturated(eve::sub)(EVE_TYPE(), EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::saturated(eve::sub) behavior")
{
  TTS_EQUAL(eve::saturated(eve::sub)(EVE_TYPE(0), EVE_TYPE(0)), EVE_TYPE(0));
  TTS_EQUAL(eve::saturated(eve::sub)(EVE_TYPE(3), EVE_TYPE(1)), EVE_TYPE(2));
  TTS_EQUAL(eve::saturated(eve::sub)(EVE_TYPE(6), EVE_TYPE(2)), EVE_TYPE(4));

  TTS_EQUAL(eve::saturated(eve::sub)(EVE_VALUE(0), EVE_TYPE(0)), EVE_TYPE(0));
  TTS_EQUAL(eve::saturated(eve::sub)(EVE_VALUE(3), EVE_TYPE(1)), EVE_TYPE(2));
  TTS_EQUAL(eve::saturated(eve::sub)(EVE_VALUE(6), EVE_TYPE(2)), EVE_TYPE(4));

  TTS_EQUAL(eve::saturated(eve::sub)(EVE_TYPE(0), EVE_VALUE(0)), EVE_TYPE(0));
  TTS_EQUAL(eve::saturated(eve::sub)(EVE_TYPE(3), EVE_VALUE(1)), EVE_TYPE(2));
  TTS_EQUAL(eve::saturated(eve::sub)(EVE_TYPE(6), EVE_VALUE(2)), EVE_TYPE(4));

  if constexpr(eve::integral_value<EVE_VALUE>)
  {
    auto vmin = eve::valmin(eve::as<EVE_TYPE>());

    TTS_EQUAL( (eve::saturated(eve::sub)(eve::valmin(eve::as<EVE_TYPE>()) , EVE_TYPE(1))) , vmin );
    TTS_EQUAL( (eve::saturated(eve::sub)(eve::valmin(eve::as<EVE_VALUE>()), EVE_TYPE(1))) , vmin );
    TTS_EQUAL( (eve::saturated(eve::sub)(eve::valmin(eve::as<EVE_TYPE>()) , EVE_VALUE(1))), vmin );

    if constexpr(std::is_signed_v<EVE_VALUE>)
    {
      auto vmax = eve::valmax(eve::as<EVE_TYPE>());

      TTS_EQUAL((eve::saturated(eve::sub)(eve::valmax(eve::as<EVE_TYPE>())  , EVE_TYPE(-1))) ,vmax);
      TTS_EQUAL((eve::saturated(eve::sub)(eve::valmax(eve::as<EVE_VALUE>()) , EVE_TYPE(-1))) ,vmax);
      TTS_EQUAL((eve::saturated(eve::sub)(eve::valmax(eve::as<EVE_TYPE>())  , EVE_VALUE(-1))),vmax);

      TTS_EQUAL(eve::saturated(eve::sub)(  EVE_TYPE(-1) ,   EVE_TYPE( 1)), EVE_TYPE(-2));
      TTS_EQUAL(eve::saturated(eve::sub)(  EVE_TYPE(-2) ,   EVE_TYPE(-6)), EVE_TYPE( 4));
      TTS_EQUAL(eve::saturated(eve::sub)(EVE_VALUE(-1) ,   EVE_TYPE( 1)), EVE_TYPE(-2));
      TTS_EQUAL(eve::saturated(eve::sub)(EVE_VALUE(-2) ,   EVE_TYPE(-6)), EVE_TYPE( 4));
      TTS_EQUAL(eve::saturated(eve::sub)(  EVE_TYPE(-1) , EVE_VALUE( 1)), EVE_TYPE(-2));
      TTS_EQUAL(eve::saturated(eve::sub)(  EVE_TYPE(-2) , EVE_VALUE(-6)), EVE_TYPE( 4));
    }
  }
}
