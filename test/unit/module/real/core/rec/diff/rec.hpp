//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/diff/rec.hpp>
#include <type_traits>

TTS_CASE_TPL("Check diff(rec) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::diff(eve::rec)(T()), T);
  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}

TTS_CASE_TPL("Check eve::diff(eve::rec) behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::diff(eve::rec)(T{10}), T(-1.0/100));
    TTS_EQUAL(eve::diff(eve::rec)(T{-10}), T(-1.0/100));
  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}
