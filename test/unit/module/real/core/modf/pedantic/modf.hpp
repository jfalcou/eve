//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pedantic/modf.hpp>

TTS_CASE_TPL("Check modf return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::pedantic(eve::modf)(T()), (kumi::tuple<T,T>));
}

TTS_CASE_TPL("Check (eve::pedantic(eve::modf) behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    {
      auto [p0, p1] = eve::pedantic(eve::modf)(T(1.5));
      TTS_EQUAL(p0, T(0.5));
      TTS_EQUAL(p1, T(1));
    }
    if constexpr(eve::signed_value<T>)
    {
      auto [p0, p1] = eve::pedantic(eve::modf)(T(-1.6));
      TTS_ULP_EQUAL (p0 , T(-0.6), 0.5);
      TTS_EQUAL (p1, T(-1));
    }
  }
  else
  {
     auto [p0, p1] = eve::pedantic(eve::modf)(T(1));
      TTS_EQUAL (p0 , T(0));
      TTS_EQUAL (p1, T(1));
  }
}
