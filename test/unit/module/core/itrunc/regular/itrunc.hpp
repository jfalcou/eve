//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/itrunc.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check itrunc return type")
{
  TTS_EXPR_IS(eve::itrunc(EVE_TYPE()), (eve::detail::as_integer_t<EVE_TYPE>));
}

TTS_CASE("Check eve::itrunc behavior")
{
  using i_t = eve::detail::as_integer_t<EVE_TYPE>; 
  TTS_EQUAL(eve::itrunc(EVE_TYPE(0)), i_t(0));
  TTS_EQUAL(eve::itrunc(EVE_TYPE(1)), i_t(1));
  TTS_EQUAL(eve::itrunc(EVE_TYPE(2)), i_t(2));

  if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::itrunc(EVE_TYPE(-1)), i_t(-1));
    TTS_EQUAL(eve::itrunc(EVE_TYPE(-2)), i_t(-2));
  }

  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
   TTS_EQUAL(eve::itrunc(EVE_TYPE(-1.3)), i_t(-1));
   TTS_EQUAL(eve::itrunc(EVE_TYPE(-1.5)), i_t(-1));
   TTS_EQUAL(eve::itrunc(EVE_TYPE(-1.6)), i_t(-1));
   TTS_EQUAL(eve::itrunc(EVE_TYPE(1.3)) , i_t(1));
   TTS_EQUAL(eve::itrunc(EVE_TYPE(1.5)) , i_t(1));
   TTS_EQUAL(eve::itrunc(EVE_TYPE(1.6)) , i_t(1));
  }
}
