//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/modf.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/minexponent.hpp>
#include <eve/constant/nbmantissabits.hpp>
#include <utility>

TTS_CASE("Check pedantic_(modf) return type")
{
  TTS_EXPR_IS((eve::pedantic_(eve::modf)(EVE_TYPE())), (std::tuple<EVE_TYPE,EVE_TYPE>));
}

TTS_CASE("Check (eve::pedantic_(eve::modf) behavior")
{
  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    {
      auto [p0, p1] = eve::pedantic_(eve::modf)(EVE_TYPE(1.5));
      TTS_EQUAL(p0, EVE_TYPE(0.5));
      TTS_EQUAL(p1, EVE_TYPE(1));
    }
    {
      auto [p0, p1] = eve::pedantic_(eve::modf)(EVE_TYPE(-1.6));
      TTS_ULP_EQUAL (p0 , EVE_TYPE(-0.6), 0.5);
      TTS_EQUAL (p1, EVE_TYPE(-1));
    }
    if constexpr(eve::platform::supports_invalids)
    {
      {
        auto [p0, p1] = eve::pedantic_(eve::modf)(eve::Inf<EVE_TYPE>());
        TTS_IEEE_EQUAL (p0, (EVE_TYPE(0.0)));
        TTS_IEEE_EQUAL (p1, (eve::Inf<EVE_TYPE>()));
      }
      {
        auto [p0, p1] = eve::pedantic_(eve::modf)(eve::Nan<EVE_TYPE>());
        TTS_IEEE_EQUAL (p0 , (eve::Nan<EVE_TYPE>()));
        TTS_IEEE_EQUAL (p1,  (eve::Nan<EVE_TYPE>()));
      }
    }
  }
  else
  {
     auto [p0, p1] = eve::pedantic_(eve::modf)(EVE_TYPE(1));
      TTS_EQUAL (p0 , EVE_TYPE(0));
      TTS_EQUAL (p1, EVE_TYPE(1));
  }
}
