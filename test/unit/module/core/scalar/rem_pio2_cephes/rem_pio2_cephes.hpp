//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

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
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check rem_pio2_cephes return type") { TTS_EXPR_IS(eve::rem_pio2_cephes(Type(0)), Type); }

TTS_CASE("Check eve::rem_pio2_cephes behavior")
{
  TTS_EQUAL(eve::rem_pio2_cephes(Type(1)), Type(1));
  TTS_EQUAL(eve::rem_pio2_cephes(Type(2)), Type(2));     
  TTS_EQUAL(eve::rem_pio2_cephes(Type(3)), Type(3));     
  TTS_EQUAL(eve::rem_pio2_cephes(Type(4)), Type(0));
  if constexpr(std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::rem_pio2_cephes(Type(-1)), Type(3));
    TTS_EQUAL(eve::rem_pio2_cephes(Type(-2)), Type(2));     
    TTS_EQUAL(eve::rem_pio2_cephes(Type(-3)), Type(1));     
    TTS_EQUAL(eve::rem_pio2_cephes(Type(-4)), Type(0));     
  }
}

#endif
