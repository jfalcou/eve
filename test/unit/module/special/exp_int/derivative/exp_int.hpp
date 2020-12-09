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
#include <eve/function/derivative/exp_int.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/inf.hpp>
#include <eve/function/sqrt.hpp>
#include <type_traits>

TTS_CASE_TPL("Check derivative(exp_int) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::derivative(eve::exp_int)(int(), T()), T);
  }
}

// TTS_CASE_TPL("Check eve::derivative(eve::exp_int) behavior", EVE_TYPE)
// {
//   if constexpr(eve::floating_value<T>)
//   {
//     using elt_t = eve::element_type_t<T>;
//     auto ulp =  (sizeof(elt_t) == 4) ? 1.0e4 : 1.0e8;
    auto df = [](auto f, auto x){return eve::detail::centered_diffdiv(f, x); };
//     TTS_ULP_EQUAL(eve::derivative(eve::exp_int)(1, T{2.0}), df(eve::exp_int, 1, T(2.0))  , ulp);
//     TTS_ULP_EQUAL(eve::derivative(eve::exp_int)(2, T{1.0}), df(eve::exp_int, 2, T(1.0))  , ulp);
//   }
// }
