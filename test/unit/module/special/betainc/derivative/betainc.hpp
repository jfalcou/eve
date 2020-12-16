//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//===========================pow=======================================================================
#include <eve/function/derivative/betainc.hpp>
#include <eve/constant/log_2.hpp>
#include <type_traits>
#include <eve/detail/diff_div.hpp>


TTS_CASE_TPL("Check derivative(betainc) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::derivative(eve::betainc)(T(), T(), T()), T);
  }
}

TTS_CASE_TPL("Check eve::derivative(eve::betainc) behavior", EVE_TYPE)
{

  if constexpr(eve::floating_value<T>)
  {
    using elt_t = eve::element_type_t<T>;
    auto ulp =  (sizeof(elt_t) == 4) ? 1.0e4 : 1.0e8;
    auto df = [](auto f, auto x){return eve::detail::centered_diffdiv(f, x); };
    auto f1 = [](auto x){return eve::betainc(x,T{0.3},T{2});};

    TTS_ULP_EQUAL(eve::derivative_1st(eve::betainc)(T{0.5},T{0.3},T{2}), df(f1, T(0.5)), ulp);
    TTS_ULP_EQUAL(eve::derivative_1st(eve::betainc)(T{0.2},T{0.3},T{2}), df(f1, T(0.2)), ulp);
  }
}
