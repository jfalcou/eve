//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/diff/logspace_sub.hpp>
#include <eve/function/diff/logspace_add.hpp>
#include <type_traits>

TTS_CASE_TPL("Check diff(logspace_sub) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::diff_nth<1>(eve::logspace_sub)(T(), T(), T()), T);
    TTS_EXPR_IS(eve::diff_nth<2>(eve::logspace_sub)(T(), T(),T()), T);
    TTS_EXPR_IS(eve::diff_nth<3>(eve::logspace_sub)(T(), T(),T()), T);
  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}

TTS_CASE_TPL("Check eve::diff(eve::logspace_sub) behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_ULP_EQUAL(eve::diff_1st(eve::logspace_sub)(T{3},T{1}), T(1.156517642749666), 1);
    TTS_ULP_EQUAL(eve::diff_2nd(eve::logspace_sub)(T{6},T{2}), T(-1.865736036377405e-02), 1);
    TTS_ULP_EQUAL(eve::diff_3rd(eve::logspace_sub)(T{10},T{-16}), T(0), 1);

    TTS_ULP_EQUAL(eve::diff_1st(eve::logspace_sub)(T{5},T{1},T{1}), T(1.038024151015572), 1);
    TTS_ULP_EQUAL(eve::diff_2nd(eve::logspace_sub)(T{-10},T{6},T{3}), T(9.525742289365767e-01), 1);
    TTS_ULP_EQUAL(eve::diff_3rd(eve::logspace_sub)(T{-10},T{6},T{3}), T(4.742587826153062e-02), 1);
    TTS_ULP_EQUAL(eve::diff_nth<4>(eve::logspace_sub)(T{-10},T{6},T{3}), T(0.0), 1);

    TTS_ULP_EQUAL(eve::diff_1st(eve::logspace_sub)(T{10},T{6},T{4},T{3}), T(1.022187889416613), 1);
    TTS_ULP_EQUAL(eve::diff_2nd(eve::logspace_sub)(T{-10},T{6},T{4},T{3}), T(8.437948146052159e-01), 1);
    TTS_ULP_EQUAL(eve::diff_3rd(eve::logspace_sub)(T{-10},T{6},T{4},T{3}), T(1.141952102281820e-01), 1);
    TTS_ULP_EQUAL(eve::diff_nth<4>(eve::logspace_sub)(T{-10},T{6},T{4},T{3}), T(4.201007012319897e-02), 1);
    TTS_ULP_EQUAL(eve::diff_nth<5>(eve::logspace_sub)(T{-10},T{6},T{4},T{3}), T(0), 0);

  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}
