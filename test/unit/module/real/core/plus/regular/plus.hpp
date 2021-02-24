//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/plus.hpp>

TTS_CASE_TPL("Check eve::plus return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::plus(T()), T);
}

TTS_CASE_TPL("Check eve::plus behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::plus(T(1)), T(1));
}

TTS_CASE_TPL("Check eve::plus with 2 parameters behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::plus(T(1), T(1)), T(2));
}

TTS_CASE_TPL("Check eve::plus with 3 parameters behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::plus[T(1) > T(2)](T(1), T(1)), T(1));
  TTS_EQUAL(eve::plus[T(1) < T(2)](T(1), T(1)), T(2));
}
