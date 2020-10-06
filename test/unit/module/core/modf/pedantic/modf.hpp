//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/modf.hpp>
#include <tuple>

TTS_CASE("Check modf return type")
{
  TTS_EXPR_IS(eve::pedantic(eve::modf)(EVE_TYPE()), (std::tuple<EVE_TYPE,EVE_TYPE>));
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
