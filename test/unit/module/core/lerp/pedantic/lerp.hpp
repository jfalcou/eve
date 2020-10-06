//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/lerp.hpp>
#include <eve/function/average.hpp>
#include <eve/function/next.hpp>
#include <eve/function/prev.hpp>
#include <eve/constant/eps.hpp>

TTS_CASE("Check eve::lerp return type")
{
  TTS_EXPR_IS(eve::pedantic(eve::lerp)(EVE_TYPE(), EVE_TYPE(), EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::pedantic(eve::lerp) behavior")
{
  TTS_ULP_EQUAL ( eve::pedantic(eve::lerp)(EVE_TYPE(12.73), EVE_TYPE(27.6666), EVE_TYPE(1)), EVE_TYPE(27.6666), 0);
  TTS_ULP_EQUAL ( eve::pedantic(eve::lerp)(EVE_TYPE(12.73), EVE_TYPE(27.6666), EVE_TYPE(0)), EVE_TYPE(12.73), 0);
  TTS_ULP_EQUAL ( eve::pedantic(eve::lerp)(EVE_TYPE(12.73), EVE_TYPE(27.6666), EVE_TYPE(0.5))
                , eve::average(EVE_TYPE(12.73), EVE_TYPE(27.6666)),0
                );

  // test monotonicity
  auto e0 = eve::pedantic(eve::lerp)(EVE_VALUE(1), EVE_VALUE(2), eve::prev(1 - 10 * eve::eps(eve::as<EVE_VALUE>())));

  for ( EVE_VALUE i = 1 - 10 * eve::eps(eve::as<EVE_VALUE>())
      ; i <= 1 + 10 * eve::eps(eve::as<EVE_VALUE>())
      ; i     = eve::next(i)
      )
  {
    auto e1 = eve::pedantic(eve::lerp)(EVE_VALUE(1), EVE_VALUE(2), i);
    TTS_LESS_EQUAL(e0, e1);
    e0 = e1;
  }
}
