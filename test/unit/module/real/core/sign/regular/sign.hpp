//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sign.hpp>

TTS_CASE_TPL("Check eve::sign return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::sign(T()), T);
}

TTS_CASE_TPL("Check eve::sign behavior", EVE_TYPE)
{
  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::sign(static_cast<T>(-2)), (T(-1)));
  }

  TTS_EQUAL(eve::sign(T(0)), T(0));
  TTS_EQUAL(eve::sign(T(2)), T(1));
}
