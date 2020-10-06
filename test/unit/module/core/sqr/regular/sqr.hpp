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
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <type_traits>

TTS_CASE("Check eve::sqr return type")
{
  TTS_EXPR_IS(eve::sqr(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::sqr behavior")
{
  TTS_EQUAL(eve::sqr(EVE_TYPE(1)), EVE_TYPE(1) );
  TTS_EQUAL(eve::sqr(EVE_TYPE(2)), EVE_TYPE(4) );

  if constexpr(eve::signed_value<EVE_VALUE>)
  {
    TTS_EQUAL(eve::sqr(static_cast<EVE_TYPE>(-2)), EVE_TYPE(4));
  }

  if constexpr(eve::floating_value<EVE_VALUE>)
  {
    TTS_EQUAL(eve::sqr(EVE_TYPE(-0.)), EVE_TYPE(0));
  }
}

