//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//===========================pow=======================================================================
#include <eve/function/derivative/clamp.hpp>
#include <eve/constant/log_2.hpp>
#include <type_traits>
#include <eve/detail/diff_div.hpp>

TTS_CASE_TPL("Check derivative(clamp) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::derivative(eve::clamp)(T(), T(), T()), T);
  }
}

TTS_CASE_TPL("Check eve::derivative(eve::clamp) behavior", EVE_TYPE)
{

  if constexpr(eve::floating_value<T>)
  {
    using elt_t = eve::element_type_t<T>;
    auto ulp =  (sizeof(elt_t) == 4) ? 1.0e4 : 1.0e8;
    auto df = [](auto f, auto x){return eve::detail::centered_diffdiv(f, x); };
    auto z1 = [](auto x){return (eve::clamp)(x,T{3},T{4}); };
    auto z2 = [](auto y){return (eve::clamp)(T{2},T{y},T{4}); };
    auto z3 = [](auto z){return (eve::clamp)(T{2},T{3},T{z}); };
    TTS_EQUAL(eve::derivative_1st(eve::clamp)(T{2},T{3},T{4}), df(z1, T{2}));
    TTS_EQUAL(eve::derivative_2nd(eve::clamp)(T{2},T{3},T{4}), df(z2, T{3}));
    TTS_EQUAL(eve::derivative_3rd(eve::clamp)(T{2},T{3},T{4}), df(z3, T{4}));
 }
}
