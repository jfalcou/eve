//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/sqrtvalmax.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/mul.hpp>

#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::mul return type")
{
  TTS_EXPR_IS(eve::mul(EVE_TYPE(), EVE_TYPE()), (EVE_TYPE));
}

TTS_CASE("Check eve::mul behavior")
{
  TTS_EQUAL(eve::mul(EVE_TYPE(0), EVE_TYPE(1)), (EVE_TYPE(0)));
  TTS_EQUAL(eve::mul(EVE_TYPE(1), EVE_TYPE(1)), (EVE_TYPE(1)));
  TTS_EQUAL(eve::mul(EVE_TYPE(12), EVE_TYPE(4)), (EVE_TYPE(48)));

  TTS_EQUAL(eve::mul(EVE_VALUE(0), EVE_TYPE(1)), (EVE_TYPE(0)));
  TTS_EQUAL(eve::mul(EVE_VALUE(1), EVE_TYPE(1)), (EVE_TYPE(1)));
  TTS_EQUAL(eve::mul(EVE_VALUE(12), EVE_TYPE(4)), (EVE_TYPE(48)));

  TTS_EQUAL(eve::mul(EVE_TYPE(0), EVE_VALUE(1)), (EVE_TYPE(0)));
  TTS_EQUAL(eve::mul(EVE_TYPE(1), EVE_VALUE(1)), (EVE_TYPE(1)));
  TTS_EQUAL(eve::mul(EVE_TYPE(12), EVE_VALUE(4)), (EVE_TYPE(48)));
  if constexpr( std::is_signed_v<EVE_VALUE> )
  {
    TTS_EQUAL(eve::mul(EVE_TYPE(-1), EVE_TYPE(1)), (EVE_TYPE(-1)));
    TTS_EQUAL(eve::mul(EVE_TYPE(-6), EVE_TYPE(-2)), (EVE_TYPE(12)));

    TTS_EQUAL(eve::mul(EVE_VALUE(-1), EVE_TYPE(1)), (EVE_TYPE(-1)));
    TTS_EQUAL(eve::mul(EVE_VALUE(-6), EVE_TYPE(-2)), (EVE_TYPE(12)));

    TTS_EQUAL(eve::mul(EVE_TYPE(-1), EVE_VALUE(1)), (EVE_TYPE(-1)));
    TTS_EQUAL(eve::mul(EVE_TYPE(-6), EVE_VALUE(-2)), (EVE_TYPE(12)));
  }
}
