//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/saturated/inc.hpp>
#include <eve/constant/valmax.hpp>

TTS_CASE_TPL("Check inc return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::saturated(eve::inc)(T()), T);
}

TTS_CASE_TPL("Check saturated(inc) behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::saturated(eve::inc)(eve::valmax(eve::as<T>())), eve::valmax(eve::as<T>()) );
  TTS_EQUAL(eve::saturated(eve::inc)(T(1)            ), T(2)             );
  TTS_EQUAL(eve::saturated(eve::inc)(T(2)            ), T(3)             );

if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::saturated(eve::inc)(T(-2)), T(-1));
  }

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::saturated(eve::inc)( T(-0.)), T(1));
    TTS_EQUAL(eve::saturated(eve::inc)( T( 0 )), T(1));
  }
}
