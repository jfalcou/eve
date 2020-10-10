//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sqr.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/saturated.hpp>
#include <eve/constant/sqrtvalmax.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::saturated(eve::sqr) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::saturated(eve::sqr)(T(0)), T);
}

TTS_CASE_TPL("Check eve::sqr behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::saturated(eve::sqr)(T(1)), T(1));
  TTS_EQUAL(eve::saturated(eve::sqr)(T(2)), T(4));

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::saturated(eve::sqr)(static_cast<T>(-2)), T(4));
  }

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::saturated(eve::sqr)(T(-0.)), T(0));
  }

  if constexpr(eve::integral_value<T>)
  {
    TTS_EQUAL(eve::saturated(eve::sqr)(eve::inc(eve::sqrtvalmax(eve::as<T>()))), eve::valmax(eve::as<T>()));
  }
}
