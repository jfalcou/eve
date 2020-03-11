//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/minmag.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::pedantic_(eve::minmag) return type")
{
  TTS_EXPR_IS(eve::pedantic_(eve::minmag)(EVE_TYPE(0)  , EVE_TYPE(0) ) , (EVE_TYPE));
  TTS_EXPR_IS(eve::pedantic_(eve::minmag)(EVE_VALUE(0) , EVE_TYPE(0) ) , (EVE_TYPE));
  TTS_EXPR_IS(eve::pedantic_(eve::minmag)(EVE_TYPE(0)  , EVE_VALUE(0)) , (EVE_TYPE));
}

TTS_CASE("Check eve::pedantic_(eve::minmag) behavior")
{
  TTS_EQUAL(eve::pedantic_(eve::minmag)((EVE_TYPE(0)), (EVE_TYPE(0))), (EVE_TYPE(0)));
  TTS_EQUAL(eve::pedantic_(eve::minmag)((EVE_TYPE(0)), (EVE_TYPE(1))), (EVE_TYPE(0)));
  TTS_EQUAL(eve::pedantic_(eve::minmag)((EVE_TYPE(1)), (EVE_TYPE(0))), (EVE_TYPE(0)));
  TTS_EQUAL(eve::pedantic_(eve::minmag)((EVE_TYPE(1)), (EVE_TYPE(1))), (EVE_TYPE(1)));

  TTS_EQUAL(eve::pedantic_(eve::minmag)((EVE_VALUE(0)), (EVE_TYPE(0))), (EVE_TYPE(0)));
  TTS_EQUAL(eve::pedantic_(eve::minmag)((EVE_VALUE(0)), (EVE_TYPE(1))), (EVE_TYPE(0)));
  TTS_EQUAL(eve::pedantic_(eve::minmag)((EVE_VALUE(1)), (EVE_TYPE(0))), (EVE_TYPE(0)));
  TTS_EQUAL(eve::pedantic_(eve::minmag)((EVE_VALUE(1)), (EVE_TYPE(1))), (EVE_TYPE(1)));

  TTS_EQUAL(eve::pedantic_(eve::minmag)((EVE_TYPE(0)), (EVE_VALUE(0))), (EVE_TYPE(0)));
  TTS_EQUAL(eve::pedantic_(eve::minmag)((EVE_TYPE(0)), (EVE_VALUE(1))), (EVE_TYPE(0)));
  TTS_EQUAL(eve::pedantic_(eve::minmag)((EVE_TYPE(1)), (EVE_VALUE(0))), (EVE_TYPE(0)));
  TTS_EQUAL(eve::pedantic_(eve::minmag)((EVE_TYPE(1)), (EVE_VALUE(1))), (EVE_TYPE(1)));

  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    TTS_IEEE_EQUAL(eve::pedantic_(eve::minmag)((eve::Nan<EVE_TYPE>() ), (EVE_TYPE(1))) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::pedantic_(eve::minmag)((eve::Nan<EVE_VALUE>()), (EVE_TYPE(1))) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::pedantic_(eve::minmag)((eve::Nan<EVE_TYPE>() ), (EVE_VALUE(1))), (eve::Nan<EVE_TYPE>()) );

    TTS_IEEE_EQUAL(eve::pedantic_(eve::minmag)((EVE_TYPE(1)) , (eve::Nan<EVE_TYPE>())  ), (EVE_TYPE(1)) );
    TTS_IEEE_EQUAL(eve::pedantic_(eve::minmag)((EVE_VALUE(1)), (eve::Nan<EVE_TYPE>())  ), (EVE_TYPE(1)) );
    TTS_IEEE_EQUAL(eve::pedantic_(eve::minmag)((EVE_TYPE(1)) , (eve::Nan<EVE_VALUE>()) ), (EVE_TYPE(1)) );
  }

  if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::pedantic_(eve::minmag)(static_cast<EVE_TYPE>(-3), (EVE_TYPE(2))), (EVE_TYPE(2)));
    TTS_EQUAL(eve::pedantic_(eve::minmag)(static_cast<EVE_TYPE>(-1), (EVE_TYPE(2))), static_cast<EVE_TYPE>(-1));
    TTS_EQUAL(eve::pedantic_(eve::minmag)(static_cast<EVE_TYPE>(-2), (EVE_TYPE(2))), static_cast<EVE_TYPE>(-2));

    TTS_EQUAL(eve::pedantic_(eve::minmag)(static_cast<EVE_TYPE>(-3), (EVE_TYPE(2))), (EVE_TYPE(2)));
    TTS_EQUAL(eve::pedantic_(eve::minmag)(static_cast<EVE_TYPE>(-1), (EVE_TYPE(2))), static_cast<EVE_TYPE>(-1));
    TTS_EQUAL(eve::pedantic_(eve::minmag)(static_cast<EVE_TYPE>(-2), (EVE_TYPE(2))), static_cast<EVE_TYPE>(-2));

    TTS_EQUAL(eve::pedantic_(eve::minmag)(static_cast<EVE_TYPE>(-3), (EVE_TYPE(2))), (EVE_TYPE(2)));
    TTS_EQUAL(eve::pedantic_(eve::minmag)(static_cast<EVE_TYPE>(-1), (EVE_TYPE(2))), static_cast<EVE_TYPE>(-1));
    TTS_EQUAL(eve::pedantic_(eve::minmag)(static_cast<EVE_TYPE>(-2), (EVE_TYPE(2))), static_cast<EVE_TYPE>(-2));
  }
}
