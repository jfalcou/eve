//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/popcount.hpp>
#include <eve/constant/valmax.hpp>

TTS_CASE("Check eve::popcount return type")
{
  TTS_EXPR_IS(eve::popcount(EVE_TYPE(0)), (eve::detail::as_integer_t<EVE_TYPE, unsigned>) );
}

TTS_CASE("Check eve::popcount behavior")
{
  using r_t = eve::detail::as_integer_t<EVE_TYPE, unsigned>;

  for(unsigned int a = 1, i=1; i < sizeof(EVE_VALUE) ; ++i)
  {
    TTS_EQUAL(eve::popcount(EVE_TYPE(a)) , r_t(1));
    a <<= 1;
  }

  TTS_EQUAL(eve::popcount( EVE_TYPE(0) ) , r_t(0));
  TTS_EQUAL(eve::popcount( EVE_TYPE(3) ) , r_t(2));
  TTS_EQUAL(eve::popcount( EVE_TYPE(11)) , r_t(3));

  for(EVE_VALUE a = ~EVE_VALUE(0), i=1; i < EVE_VALUE(sizeof(EVE_VALUE)) ; ++i)
  {
    TTS_EQUAL(eve::popcount(EVE_TYPE(a)) , r_t(sizeof(EVE_VALUE)*8-i+1));
    a <<= 1;
  }

  TTS_EQUAL ( eve::popcount( eve::valmax(eve::as<EVE_TYPE>()))
            , r_t(sizeof(EVE_VALUE)*8-eve::signed_value<EVE_TYPE>)
            );
}
