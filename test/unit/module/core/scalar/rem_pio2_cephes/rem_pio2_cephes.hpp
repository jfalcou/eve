//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef REM_PIO2_CEPHES_HPP
#define REM_PIO2_CEPHES_HPP

#include <eve/function/scalar/rem_pio2_cephes.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/inc.hpp>
#include <eve/traits/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check rem_pio2_cephes return type") { TTS_EXPR_IS(eve::rem_pio2_cephes(EVE_TYPE(0)), EVE_TYPE); }

TTS_CASE("Check eve::rem_pio2_cephes behavior")
{
  TTS_EQUAL(eve::rem_pio2_cephes(EVE_TYPE(1)), EVE_TYPE(1));
  TTS_EQUAL(eve::rem_pio2_cephes(EVE_TYPE(2)), EVE_TYPE(2));
  TTS_EQUAL(eve::rem_pio2_cephes(EVE_TYPE(3)), EVE_TYPE(3));
  TTS_EQUAL(eve::rem_pio2_cephes(EVE_TYPE(4)), EVE_TYPE(0));
  if constexpr(std::is_signed_v<EVE_TYPE>)
  {
    TTS_EQUAL(eve::rem_pio2_cephes(EVE_TYPE(-1)), EVE_TYPE(3));
    TTS_EQUAL(eve::rem_pio2_cephes(EVE_TYPE(-2)), EVE_TYPE(2));
    TTS_EQUAL(eve::rem_pio2_cephes(EVE_TYPE(-3)), EVE_TYPE(1));
    TTS_EQUAL(eve::rem_pio2_cephes(EVE_TYPE(-4)), EVE_TYPE(0));
  }
}

#endif
