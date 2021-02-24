//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/detail/diff_div.hpp>
#include <eve/function/diff/cos.hpp>
#include <eve/function/diff/sin.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/inf.hpp>
#include <eve/function/sqrt.hpp>
#include <type_traits>

TTS_CASE_TPL("Check diff(cos) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::diff(eve::cos)(T()), T);
  }
}

TTS_CASE_TPL("Check eve::diff(eve::cos) behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    using elt_t = eve::element_type_t<T>;
    auto df = [](auto f, auto x){return eve::detail::centered_diffdiv(f, x); };
    auto ulp =  (sizeof(elt_t) == 4) ? 1.0e4 : 1.0e8;
    TTS_ULP_EQUAL(eve::diff(eve::cos)(T{2.0}), df(eve::cos, T(2.0))  , ulp);
    TTS_ULP_EQUAL(eve::diff(eve::cos)(T{1}), df(eve::cos, T(1.0))  , ulp);
  }
}
