//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/maxmag.hpp>
#include <eve/function/numeric.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::numeric_(eve::maxmag) return type")
{
  TTS_EXPR_IS(eve::numeric_(eve::maxmag)(EVE_TYPE(0)  , EVE_TYPE(0) ) , (EVE_TYPE));
  TTS_EXPR_IS(eve::numeric_(eve::maxmag)(EVE_VALUE(0) , EVE_TYPE(0) ) , (EVE_TYPE));
  TTS_EXPR_IS(eve::numeric_(eve::maxmag)(EVE_TYPE(0)  , EVE_VALUE(0)) , (EVE_TYPE));
}

TTS_CASE("Check eve::numeric_(eve::maxmag) behavior")
{
  TTS_EQUAL(eve::numeric_(eve::maxmag)((EVE_TYPE(0)), (EVE_TYPE(0))), (EVE_TYPE(0)));
  TTS_EQUAL(eve::numeric_(eve::maxmag)((EVE_TYPE(0)), (EVE_TYPE(1))), (EVE_TYPE(1)));
  TTS_EQUAL(eve::numeric_(eve::maxmag)((EVE_TYPE(1)), (EVE_TYPE(0))), (EVE_TYPE(1)));
  TTS_EQUAL(eve::numeric_(eve::maxmag)((EVE_TYPE(1)), (EVE_TYPE(1))), (EVE_TYPE(1)));

  TTS_EQUAL(eve::numeric_(eve::maxmag)((EVE_VALUE(0)), (EVE_TYPE(0))), (EVE_TYPE(0)));
  TTS_EQUAL(eve::numeric_(eve::maxmag)((EVE_VALUE(0)), (EVE_TYPE(1))), (EVE_TYPE(1)));
  TTS_EQUAL(eve::numeric_(eve::maxmag)((EVE_VALUE(1)), (EVE_TYPE(0))), (EVE_TYPE(1)));
  TTS_EQUAL(eve::numeric_(eve::maxmag)((EVE_VALUE(1)), (EVE_TYPE(1))), (EVE_TYPE(1)));

  TTS_EQUAL(eve::numeric_(eve::maxmag)((EVE_TYPE(0)), (EVE_VALUE(0))), (EVE_TYPE(0)));
  TTS_EQUAL(eve::numeric_(eve::maxmag)((EVE_TYPE(0)), (EVE_VALUE(1))), (EVE_TYPE(1)));
  TTS_EQUAL(eve::numeric_(eve::maxmag)((EVE_TYPE(1)), (EVE_VALUE(0))), (EVE_TYPE(1)));
  TTS_EQUAL(eve::numeric_(eve::maxmag)((EVE_TYPE(1)), (EVE_VALUE(1))), (EVE_TYPE(1)));

  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    TTS_IEEE_EQUAL(eve::numeric_(eve::maxmag)((eve::Nan<EVE_TYPE>() ), (EVE_TYPE(1)))  , (EVE_TYPE(1)) );
    TTS_IEEE_EQUAL(eve::numeric_(eve::maxmag)((eve::Nan<EVE_VALUE>()), (EVE_TYPE(1)))  , (EVE_TYPE(1)) );
    TTS_IEEE_EQUAL(eve::numeric_(eve::maxmag)((eve::Nan<EVE_TYPE>() ), (EVE_VALUE(1))) , (EVE_TYPE(1)) );

    TTS_IEEE_EQUAL(eve::numeric_(eve::maxmag)((EVE_TYPE(1))  , (eve::Nan<EVE_TYPE>())  ), (EVE_TYPE(1)) );
    TTS_IEEE_EQUAL(eve::numeric_(eve::maxmag)((EVE_VALUE(1)) , (eve::Nan<EVE_TYPE>())  ), (EVE_TYPE(1)) );
    TTS_IEEE_EQUAL(eve::numeric_(eve::maxmag)((EVE_TYPE(1))  , (eve::Nan<EVE_VALUE>()) ), (EVE_TYPE(1)) );
  }

  if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::numeric_(eve::maxmag)(static_cast<EVE_TYPE>(-1), (EVE_TYPE(2))), (EVE_TYPE(2)));
    TTS_EQUAL(eve::numeric_(eve::maxmag)(static_cast<EVE_TYPE>(-2), (EVE_TYPE(1))), static_cast<EVE_TYPE>(-2));
    TTS_EQUAL(eve::numeric_(eve::maxmag)(static_cast<EVE_TYPE>(-2), (EVE_TYPE(2))), (EVE_TYPE(2)));

    TTS_EQUAL(eve::numeric_(eve::maxmag)(static_cast<EVE_TYPE>(-1), (EVE_VALUE(2))), (EVE_TYPE(2)));
    TTS_EQUAL(eve::numeric_(eve::maxmag)(static_cast<EVE_TYPE>(-2), (EVE_VALUE(1))), static_cast<EVE_TYPE>(-2));
    TTS_EQUAL(eve::numeric_(eve::maxmag)(static_cast<EVE_TYPE>(-2), (EVE_VALUE(2))), (EVE_TYPE(2)));

    TTS_EQUAL(eve::numeric_(eve::maxmag)(static_cast<EVE_VALUE>(-1), (EVE_TYPE(2))), (EVE_TYPE(2)));
    TTS_EQUAL(eve::numeric_(eve::maxmag)(static_cast<EVE_VALUE>(-2), (EVE_TYPE(1))), static_cast<EVE_TYPE>(-2));
    TTS_EQUAL(eve::numeric_(eve::maxmag)(static_cast<EVE_VALUE>(-2), (EVE_TYPE(2))), (EVE_TYPE(2)));
  }
}
