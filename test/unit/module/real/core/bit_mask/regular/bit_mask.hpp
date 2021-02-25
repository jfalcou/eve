//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_mask.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>

TTS_CASE_TPL("Check eve::bit_mask return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::bit_mask(T()), T);
}

TTS_CASE_TPL("Check eve::bit_mask behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::bit_mask( T(0))           , T(0));
  TTS_EQUAL(eve::bit_mask(-T(0))           , T(0));
  TTS_EQUAL(eve::bit_mask(eve::false_(eve::as<T>())) , T(0));

  TTS_IEEE_EQUAL(eve::bit_mask(T(1))           , (eve::allbits(eve::as<T>())));
  TTS_IEEE_EQUAL(eve::bit_mask(eve::true_(eve::as<T>())) , (eve::allbits(eve::as<T>())));
}
