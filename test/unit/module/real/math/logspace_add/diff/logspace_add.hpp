//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/diff/logspace_add.hpp>
#include <type_traits>

TTS_CASE_TPL("Check diff(logspace_add) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::diff_nth<1>(eve::logspace_add)(T(), T(), T()), T);
    TTS_EXPR_IS(eve::diff_nth<2>(eve::logspace_add)(T(), T(),T()), T);
    TTS_EXPR_IS(eve::diff_nth<3>(eve::logspace_add)(T(), T(),T()), T);
  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}

TTS_CASE_TPL("Check eve::diff(eve::logspace_add) behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::diff_1st(eve::logspace_add)(T{1},T{1}), T(0.5));
    TTS_EQUAL(eve::diff_2nd(eve::logspace_add)(T{6},T{6}), T(0.5));
    TTS_EQUAL(eve::diff_3rd(eve::logspace_add)(T{-10},T{6}), T(0));

    TTS_EQUAL(eve::diff_1st(eve::logspace_add)(T{1},T{1},T{1}), T(1.0/3));
    TTS_ULP_EQUAL(eve::diff_2nd(eve::logspace_add)(T{-10},T{6},T{3}), T(9.525740247083118e-01), 0.5);
    TTS_EQUAL(eve::diff_3rd(eve::logspace_add)(T{-10},T{6},T{3}), T(4.742586809360403e-02));
    TTS_EQUAL(eve::diff_nth<4>(eve::logspace_add)(T{-10},T{6},T{3}), T(0.0));

    TTS_ULP_EQUAL(eve::diff_1st(eve::logspace_add)(T{10},T{6},T{4},T{3}), T(9.787548793582700e-01), 1);
    TTS_ULP_EQUAL(eve::diff_2nd(eve::logspace_add)(T{-10},T{6},T{4},T{3}), T(8.437946543574784e-01), 1);
    TTS_ULP_EQUAL(eve::diff_3rd(eve::logspace_add)(T{-10},T{6},T{4},T{3}), T(1.141951885410090e-01), 1);
    TTS_ULP_EQUAL(eve::diff_nth<4>(eve::logspace_add)(T{-10},T{6},T{4},T{3}), T(4.201006214493389e-02), 1);
    TTS_ULP_EQUAL(eve::diff_nth<5>(eve::logspace_add)(T{-10},T{6},T{4},T{3}), T(0), 0);
  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}
