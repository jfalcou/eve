//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/minmag.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::minmag return type")
{
  TTS_EXPR_IS(eve::minmag(EVE_TYPE(0)  , EVE_TYPE(0) ) , (EVE_TYPE));
  TTS_EXPR_IS(eve::minmag(EVE_VALUE(0) , EVE_TYPE(0) ) , (EVE_TYPE));
  TTS_EXPR_IS(eve::minmag(EVE_TYPE(0)  , EVE_VALUE(0)) , (EVE_TYPE));
}

TTS_CASE("Check eve::minmag behavior")
{
  TTS_EQUAL(eve::minmag((EVE_TYPE(0)), (EVE_TYPE(0))), (EVE_TYPE(0)));
  TTS_EQUAL(eve::minmag((EVE_TYPE(0)), (EVE_TYPE(1))), (EVE_TYPE(0)));
  TTS_EQUAL(eve::minmag((EVE_TYPE(1)), (EVE_TYPE(0))), (EVE_TYPE(0)));
  TTS_EQUAL(eve::minmag((EVE_TYPE(1)), (EVE_TYPE(1))), (EVE_TYPE(1)));

  TTS_EQUAL(eve::minmag((EVE_VALUE(0)), (EVE_TYPE(0))), (EVE_TYPE(0)));
  TTS_EQUAL(eve::minmag((EVE_VALUE(0)), (EVE_TYPE(1))), (EVE_TYPE(0)));
  TTS_EQUAL(eve::minmag((EVE_VALUE(1)), (EVE_TYPE(0))), (EVE_TYPE(0)));
  TTS_EQUAL(eve::minmag((EVE_VALUE(1)), (EVE_TYPE(1))), (EVE_TYPE(1)));

  TTS_EQUAL(eve::minmag((EVE_TYPE(0)), (EVE_VALUE(0))), (EVE_TYPE(0)));
  TTS_EQUAL(eve::minmag((EVE_TYPE(0)), (EVE_VALUE(1))), (EVE_TYPE(0)));
  TTS_EQUAL(eve::minmag((EVE_TYPE(1)), (EVE_VALUE(0))), (EVE_TYPE(0)));
  TTS_EQUAL(eve::minmag((EVE_TYPE(1)), (EVE_VALUE(1))), (EVE_TYPE(1)));

  if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::minmag(static_cast<EVE_TYPE>(-3), (EVE_TYPE(2))), (EVE_TYPE(2)));
    TTS_EQUAL(eve::minmag(static_cast<EVE_TYPE>(-1), (EVE_TYPE(2))), static_cast<EVE_TYPE>(-1));
    TTS_EQUAL(eve::minmag(static_cast<EVE_TYPE>(-2), (EVE_TYPE(2))), static_cast<EVE_TYPE>(-2));

    TTS_EQUAL(eve::minmag(static_cast<EVE_TYPE>(-3), (EVE_TYPE(2))), (EVE_TYPE(2)));
    TTS_EQUAL(eve::minmag(static_cast<EVE_TYPE>(-1), (EVE_TYPE(2))), static_cast<EVE_TYPE>(-1));
    TTS_EQUAL(eve::minmag(static_cast<EVE_TYPE>(-2), (EVE_TYPE(2))), static_cast<EVE_TYPE>(-2));

    TTS_EQUAL(eve::minmag(static_cast<EVE_TYPE>(-3), (EVE_TYPE(2))), (EVE_TYPE(2)));
    TTS_EQUAL(eve::minmag(static_cast<EVE_TYPE>(-1), (EVE_TYPE(2))), static_cast<EVE_TYPE>(-1));
    TTS_EQUAL(eve::minmag(static_cast<EVE_TYPE>(-2), (EVE_TYPE(2))), static_cast<EVE_TYPE>(-2));
  }
}
