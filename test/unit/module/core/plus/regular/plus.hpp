//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/plus.hpp>

TTS_CASE("Check eve::plus return type")
{
  TTS_EXPR_IS(eve::plus(EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::plus behavior")
{
  TTS_EQUAL(eve::plus(EVE_TYPE(1)), EVE_TYPE(1));
}

TTS_CASE("Check eve::plus with 2 parameters behavior")
{
  TTS_EQUAL(eve::plus(EVE_TYPE(1), EVE_TYPE(1)), EVE_TYPE(2));
}

TTS_CASE("Check eve::plus with 3 parameters behavior")
{
  TTS_EQUAL(eve::plus[EVE_TYPE(1) > EVE_TYPE(2)](EVE_TYPE(1), EVE_TYPE(1)), EVE_TYPE(1));
  TTS_EQUAL(eve::plus[EVE_TYPE(1) < EVE_TYPE(2)](EVE_TYPE(1), EVE_TYPE(1)), EVE_TYPE(2));
}
