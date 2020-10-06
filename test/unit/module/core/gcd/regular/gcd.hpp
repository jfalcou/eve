//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/gcd.hpp>
#include <numeric>

TTS_CASE("Check eve::gcd return type")
{
  TTS_EXPR_IS(eve::gcd(EVE_TYPE(0), EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::gcd behavior")
{
  TTS_EQUAL(eve::gcd(EVE_TYPE(22), EVE_TYPE( 10)) , EVE_TYPE(eve::gcd(EVE_TYPE(22), EVE_TYPE(10))) );
  TTS_EQUAL(eve::gcd(EVE_TYPE(22), EVE_TYPE(-10)) , EVE_TYPE(eve::gcd(EVE_TYPE(22), EVE_TYPE(10))) );
}
