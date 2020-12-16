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
#include <eve/function/derivative/acot.hpp>
#include <eve/function/derivative/sin.hpp>
#include <eve/constant/eps.hpp>
#include <eve/function/sqrt.hpp>
#include <type_traits>

TTS_CASE_TPL("Check derivative(cos) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::derivative(eve::acot)(T()), T);
  }
}

TTS_CASE_TPL("Check eve::derivative(eve::acot) behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    using elt_t = eve::element_type_t<T>;
    auto ulp =  (sizeof(elt_t) == 4) ? 1.0e4 : 1.0e8;
    auto df = [](auto f, auto x){return eve::detail::centered_diffdiv(f, x); };
    TTS_ULP_EQUAL(eve::derivative(eve::acot)(T{0.25}), df(eve::acot, T(0.25))  , ulp);
    TTS_ULP_EQUAL(eve::derivative(eve::acot)(T{0}), T(-1)        , 0);
    TTS_ULP_EQUAL(eve::derivative(eve::acot)(T{-0.25}), df(eve::acot, T(-0.25)), ulp);

  }
}
