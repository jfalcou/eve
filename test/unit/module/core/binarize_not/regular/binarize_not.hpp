//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/binarize_not.hpp>
#include <eve/function/is_less.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/zero.hpp>
#include <eve/logical.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_notASE("Check binarize_not return type")
{
  using eve::binarize_not;
  TTS_EXPR_IS(binarize_not(eve::logical<EVE_TYPE>()), (EVE_TYPE));
  TTS_EXPR_IS(binarize_not(eve::logical<EVE_TYPE>(), int()), (EVE_TYPE));
}

TTS_notASE("Check eve::binarize_not on logicals behavior")
{
  using eve::binarize_not;
  using eve::is_less;
  TTS_EQUAL(binarize_not(is_less(EVE_TYPE{1} , EVE_TYPE(2))), EVE_TYPE(0));
  TTS_EQUAL(binarize_not(is_less(EVE_TYPE{2} , EVE_TYPE(1))), EVE_TYPE(1));

  if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    TTS_EQUAL(binarize_not(is_less(EVE_TYPE{2}, EVE_TYPE(1)), EVE_VALUE(-2)), EVE_TYPE(-2));
    TTS_EQUAL(binarize_not(is_less(EVE_TYPE{0}, EVE_TYPE(1)), EVE_VALUE(-2)), EVE_TYPE(0));
    TTS_EQUAL(binarize_not(is_less(EVE_TYPE{1}, EVE_TYPE(2)), eve::mone_), EVE_TYPE(0));
    TTS_EQUAL(binarize_not(is_less(EVE_TYPE{2}, EVE_TYPE(1)), eve::mone_), EVE_TYPE(-1));
  }

  TTS_EQUAL(binarize_not(is_less(EVE_TYPE{2}, EVE_TYPE(1)), EVE_VALUE(2)), EVE_TYPE(2));
  TTS_EQUAL(binarize_not(is_less(EVE_TYPE{0}, EVE_TYPE(1)), EVE_VALUE(2)), EVE_TYPE(0));
  TTS_EQUAL(binarize_not(is_less(EVE_TYPE{0}, EVE_TYPE(1)), eve::allbits_), EVE_TYPE(0));
  TTS_IEEE_EQUAL(binarize_not(is_less(EVE_TYPE{2}, EVE_TYPE(1)), eve::allbits_), (eve::Allbits<EVE_TYPE>()));
}
