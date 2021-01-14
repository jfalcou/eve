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

TTS_CASE_TPL("Check diff(manhattan) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::diff(eve::manhattan)(T(), T()), T);
    TTS_EXPR_IS(eve::diff(eve::manhattan)(T(), T()), T);
  }
}

TTS_CASE_TPL("Check eve::diff(eve::manhattan) behavior", EVE_TYPE)
{

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::diff_1st(eve::manhattan)(T{10},T{5}), T(1));
    TTS_EQUAL(eve::diff_1st(eve::manhattan)(T{-10},T{5}), T(-1));
    TTS_EQUAL(eve::diff_2nd(eve::manhattan)(T{-10},T{5}), T(1));
    TTS_EQUAL(eve::diff_2nd(eve::manhattan)(T{-10},T{-5}), T(-1));
    TTS_EQUAL(eve::diff_3rd(eve::manhattan)(T{-10},T{5}), T(0));
    TTS_EQUAL(eve::diff_3rd(eve::manhattan)(T{-10},T{5}), T(0));
    TTS_EQUAL(eve::diff_1st(eve::manhattan)(T{10},T{5},T{5}), T(1));
    TTS_EQUAL(eve::diff_1st(eve::manhattan)(T{-10},T{5},T{5}), T(-1));
    TTS_EQUAL(eve::diff_2nd(eve::manhattan)(T{-10},T{5},T{5}), T(1));
    TTS_EQUAL(eve::diff_2nd(eve::manhattan)(T{-10},T{-5},T{5}), T(-1));
    TTS_EQUAL(eve::diff_3rd(eve::manhattan)(T{-10},T{5},T{5}), T(1));
    TTS_EQUAL(eve::diff_3rd(eve::manhattan)(T{-10},T{5},T{-5}), T(-1));
  }
}
