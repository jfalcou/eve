//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/fms.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/zero.hpp>

TTS_CASE("Check eve::fms return type")
{
  TTS_EXPR_IS(eve::pedantic_(eve::fms)(EVE_TYPE(), EVE_TYPE(), EVE_TYPE()), (EVE_TYPE));
}

TTS_CASE("Check eve::pedantic_(eve::fms) behavior")
{
  TTS_EQUAL(eve::pedantic_(eve::fms)(EVE_TYPE(0), EVE_TYPE(0), EVE_TYPE(0)), (EVE_TYPE(0)));
  TTS_EQUAL(eve::pedantic_(eve::fms)(EVE_TYPE(0), EVE_TYPE(0), EVE_TYPE(-7)), (EVE_TYPE(7)));
  TTS_EQUAL(eve::pedantic_(eve::fms)(EVE_TYPE(2), EVE_TYPE(0), EVE_TYPE(-7)), (EVE_TYPE(7)));
  TTS_EQUAL(eve::pedantic_(eve::fms)(EVE_TYPE(0), EVE_TYPE(5), EVE_TYPE(-7)), (EVE_TYPE(7)));
  TTS_EQUAL(eve::pedantic_(eve::fms)(EVE_TYPE(2), EVE_TYPE(5), EVE_TYPE(-7)), (EVE_TYPE(17)));
  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    EVE_TYPE e = eve::Eps<EVE_TYPE>();
    TTS_EQUAL(eve::pedantic_(eve::fms)(eve::inc(e), eve::oneminus(e), eve::One<EVE_TYPE>()), (-eve::sqr(e)));
  }
}
