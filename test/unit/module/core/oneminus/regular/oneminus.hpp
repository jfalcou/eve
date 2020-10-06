//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/oneminus.hpp>
#include <type_traits>

TTS_CASE("Check eve::oneminus return type")
{
  TTS_EXPR_IS(eve::oneminus(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::oneminus behavior")
{
  TTS_EQUAL(eve::oneminus(EVE_TYPE(1)), EVE_TYPE(0));

  if constexpr(eve::signed_value<EVE_TYPE>)
  {
    TTS_EQUAL(eve::oneminus(EVE_TYPE(2))              , EVE_TYPE(-1));
    TTS_EQUAL(eve::oneminus(static_cast<EVE_TYPE>(-2)), EVE_TYPE( 3));
  }

  if constexpr(eve::floating_value<EVE_TYPE>)
  {
    TTS_EQUAL(eve::oneminus(EVE_TYPE(-0.)) , EVE_TYPE(1));
    TTS_EQUAL(eve::oneminus((EVE_TYPE(0))) , EVE_TYPE(1));
  }
}
