//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/detail/diff_div.hpp>
#include <eve/function/diff/acosd.hpp>
#include <eve/function/diff/sin.hpp>
#include <eve/constant/eps.hpp>
#include <eve/function/sqrt.hpp>
#include <type_traits>

TTS_CASE_TPL("Check diff(cos) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::diff(eve::acosd)(T()), T);
  }
}

TTS_CASE_TPL("Check eve::diff(eve::acosd) behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    using elt_t = eve::element_type_t<T>;
    auto ulp =  (sizeof(elt_t) == 4) ? 1.0e4 : 1.0e8;
    auto df = [](auto f, auto x){return eve::detail::centered_diffdiv(f, x); };
    TTS_ULP_EQUAL(eve::diff(eve::acosd)(T{0.25}), df(eve::acosd, T(0.25))  , ulp);
    TTS_ULP_EQUAL(eve::diff(eve::acosd)(T{0}), df(eve::acosd, T(0))        , ulp);
    TTS_ULP_EQUAL(eve::diff(eve::acosd)(T{-0.25}), df(eve::acosd, T(-0.25)), ulp);
  }
}
