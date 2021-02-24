//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/diff/betainc_inv.hpp>
#include <eve/constant/log_2.hpp>
#include <type_traits>
#include <eve/detail/diff_div.hpp>

TTS_CASE_TPL("Check diff(betainc_inv) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::diff(eve::betainc_inv)(T(), T(), T()), T);
  }
}

TTS_CASE_TPL("Check eve::diff(eve::betainc_inv) behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    using elt_t = eve::element_type_t<T>;
    auto ulp =  (sizeof(elt_t) == 4) ? 1.0e4 : 1.0e8;
    auto df = [](auto f, auto x){return eve::detail::centered_diffdiv(f, x); };
    auto f1 = [](auto x){return eve::betainc_inv(x,T{0.3},T{2});};

    TTS_ULP_EQUAL(eve::diff_1st(eve::betainc_inv)(T{0.5},T{0.3},T{2}), df(f1, T(0.5)), ulp);
    TTS_ULP_EQUAL(eve::diff_1st(eve::betainc_inv)(T{0.2},T{0.3},T{2}), df(f1, T(0.2)), ulp);
  }
}
