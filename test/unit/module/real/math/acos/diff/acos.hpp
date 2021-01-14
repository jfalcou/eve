//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/detail/diff_div.hpp>
#include <eve/function/diff/acos.hpp>
#include <eve/function/sqrt.hpp>
#include <type_traits>

TTS_CASE_TPL("Check diff(cos) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::diff(eve::acos)(T()), T);
  }
}

TTS_CASE_TPL("Check eve::diff(eve::acos) behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    using elt_t = eve::element_type_t<T>;
    auto ulp =  (sizeof(elt_t) == 4) ? 1.0e4 : 1.0e8;
    auto df = [](auto f, auto x){return eve::detail::centered_diffdiv(f, x); };
    TTS_ULP_EQUAL(eve::diff(eve::acos)(T{0.25}), df(eve::acos, T(0.25))  , ulp);
    TTS_ULP_EQUAL(eve::diff(eve::acos)(T{0}), df(eve::acos, T(0))        , ulp);
    TTS_ULP_EQUAL(eve::diff(eve::acos)(T{-0.25}), df(eve::acos, T(-0.25)), ulp);
  }
}
