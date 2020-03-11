//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/signnz.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::signnz return type")
{
  TTS_EXPR_IS(eve::signnz(EVE_TYPE()), (EVE_TYPE));
}

TTS_CASE("Check eve::signnz behavior")
{
  TTS_EQUAL(eve::signnz(EVE_TYPE{0}), EVE_TYPE(1));
  TTS_EQUAL(eve::signnz(EVE_TYPE{2}), EVE_TYPE(1));
  if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    if constexpr(std::is_floating_point_v<EVE_VALUE>)
    {
      TTS_EQUAL(eve::signnz(static_cast<EVE_TYPE>(-0.0)), (EVE_TYPE(-1)));
    }
    TTS_EQUAL(eve::signnz(static_cast<EVE_TYPE>(-2)), (EVE_TYPE(-1)));
  }
}
