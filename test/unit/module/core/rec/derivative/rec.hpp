//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/derivative/rec.hpp>
#include <type_traits>

TTS_CASE_TPL("Check derivative(rec) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::derivative(eve::rec)(T()), T);
  }
}

TTS_CASE_TPL("Check eve::derivative(eve::rec) behavior", EVE_TYPE)
{

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::derivative(eve::rec)(T{10}), T(-1.0/100));
    TTS_EQUAL(eve::derivative(eve::rec)(T{-10}), T(-1.0/100));
  }
}
