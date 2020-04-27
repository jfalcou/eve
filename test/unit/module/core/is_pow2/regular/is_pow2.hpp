//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_pow2.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::is_pow2 return type", EVE_TYPE)
{
  using eve::logical;

  TTS_EXPR_IS((eve::is_pow2(T() )), (eve::logical<T>));
}

TTS_CASE_TPL("Check eve::is_pow2 behavior", EVE_TYPE)
{
  if constexpr(std::is_signed_v<T>)
  {
    TTS_EQUAL(eve::is_pow2(T(-1)), eve::False<T>());
  }

  TTS_EQUAL(eve::is_pow2(T(0)), eve::False<T>());
  TTS_EQUAL(eve::is_pow2(T(1)), eve::True<T>());
  TTS_EQUAL(eve::is_pow2(T(3)), eve::False<T>());
  TTS_EQUAL(eve::is_pow2(T(4)), eve::True<T>());
  TTS_EQUAL(eve::is_pow2(eve::Valmax<T>()/2+1), eve::True<T>());
}
