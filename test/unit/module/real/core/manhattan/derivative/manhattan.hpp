//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/derivative/manhattan.hpp>
#include <type_traits>

TTS_CASE_TPL("Check derivative(manhattan) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::derivative(eve::manhattan)(T(), T()), T);
    TTS_EXPR_IS(eve::derivative(eve::manhattan)(T(), T()), T);
  }
}

TTS_CASE_TPL("Check eve::derivative(eve::manhattan) behavior", EVE_TYPE)
{

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::derivative_1st(eve::manhattan)(T{10},T{5}), T(1));
    TTS_EQUAL(eve::derivative_1st(eve::manhattan)(T{-10},T{5}), T(-1));
    TTS_EQUAL(eve::derivative_2nd(eve::manhattan)(T{-10},T{5}), T(1));
    TTS_EQUAL(eve::derivative_2nd(eve::manhattan)(T{-10},T{-5}), T(-1));
    TTS_EQUAL(eve::derivative_3rd(eve::manhattan)(T{-10},T{5}), T(0));
    TTS_EQUAL(eve::derivative_3rd(eve::manhattan)(T{-10},T{5}), T(0));
    TTS_EQUAL(eve::derivative_1st(eve::manhattan)(T{10},T{5},T{5}), T(1));
    TTS_EQUAL(eve::derivative_1st(eve::manhattan)(T{-10},T{5},T{5}), T(-1));
    TTS_EQUAL(eve::derivative_2nd(eve::manhattan)(T{-10},T{5},T{5}), T(1));
    TTS_EQUAL(eve::derivative_2nd(eve::manhattan)(T{-10},T{-5},T{5}), T(-1));
    TTS_EQUAL(eve::derivative_3rd(eve::manhattan)(T{-10},T{5},T{5}), T(1));
    TTS_EQUAL(eve::derivative_3rd(eve::manhattan)(T{-10},T{5},T{-5}), T(-1));
  }
}
