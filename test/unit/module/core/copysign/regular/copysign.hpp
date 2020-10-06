//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/copysign.hpp>

TTS_CASE("Check eve::copysign return type")
{
  TTS_EXPR_IS(eve::copysign(EVE_TYPE(), EVE_TYPE()  ), EVE_TYPE);
  TTS_EXPR_IS(eve::copysign(EVE_TYPE(), EVE_VALUE() ), EVE_TYPE);
}

TTS_CASE("Check eve::copysign behavior")
{
  TTS_EQUAL(eve::copysign(EVE_TYPE( 1.) , EVE_TYPE(-0.)) , EVE_TYPE(-1.));
  TTS_EQUAL(eve::copysign(EVE_TYPE( 1.) , EVE_VALUE(-0.)) , EVE_TYPE(-1.));
  TTS_EQUAL(eve::copysign(EVE_VALUE( 1.), EVE_TYPE(-0.)) , EVE_TYPE(-1.));

  TTS_EQUAL(eve::copysign(EVE_TYPE( 1.) , EVE_TYPE( 0.)) , EVE_TYPE( 1.));
  TTS_EQUAL(eve::copysign(EVE_TYPE( 1.) , EVE_VALUE( 0.)) , EVE_TYPE( 1.));
  TTS_EQUAL(eve::copysign(EVE_VALUE( 1.), EVE_TYPE( 0.)) , EVE_TYPE( 1.));

  TTS_EQUAL(eve::copysign(EVE_TYPE(-1.) , EVE_TYPE(-0.)) , EVE_TYPE(-1.));
  TTS_EQUAL(eve::copysign(EVE_TYPE(-1.) , EVE_VALUE(-0.)) , EVE_TYPE(-1.));
  TTS_EQUAL(eve::copysign(EVE_VALUE(-1.), EVE_TYPE(-0.)) , EVE_TYPE(-1.));

  TTS_EQUAL(eve::copysign(EVE_TYPE(-1.) , EVE_TYPE( 0.)) , EVE_TYPE( 1.));
  TTS_EQUAL(eve::copysign(EVE_TYPE(-1.) , EVE_VALUE( 0.)) , EVE_TYPE( 1.));
  TTS_EQUAL(eve::copysign(EVE_VALUE(-1.), EVE_TYPE( 0.)) , EVE_TYPE( 1.));
}
