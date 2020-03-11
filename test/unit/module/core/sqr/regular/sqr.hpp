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
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::sqr return type")
{
  TTS_EXPR_IS(eve::sqr(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::sqr behavior")
{
  TTS_EQUAL(eve::sqr(EVE_TYPE(1)), (EVE_TYPE(1)));
  TTS_EQUAL(eve::sqr(EVE_TYPE(2)), (EVE_TYPE(4)));

  if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::sqr(static_cast<EVE_TYPE>(-2)), (EVE_TYPE(4)));
  }

  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::sqr(eve::Mzero<EVE_TYPE>()), (EVE_TYPE(0)));
  }
}

