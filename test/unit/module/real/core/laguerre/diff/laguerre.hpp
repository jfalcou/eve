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
#include <eve/function/diff/laguerre.hpp>
#include <type_traits>

TTS_CASE_TPL("Check diff(laguerre) return type", EVE_TYPE)
{
    TTS_EXPR_IS(eve::diff(eve::laguerre)((unsigned int)(0), T()), T);
}

TTS_CASE_TPL("Check eve::diff(eve::laguerre) behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    using elt_t = eve::element_type_t<T>;
    auto df2 = [](auto n, auto x){
      auto cy =  [&n](auto a){ return eve::laguerre(n, a);  };
      return eve::detail::centered_diffdiv(cy, x);
    };
    auto ulp =  (sizeof(elt_t) == 4) ? 1.0e4 : 1.0e9;
    TTS_ULP_EQUAL(eve::diff(eve::laguerre)(2u, T{2.0}), df2(2, T(2.0))  , ulp);
    TTS_ULP_EQUAL(eve::diff(eve::laguerre)(2u, T{1.0}), df2(2, T(1.0))  , ulp);
    TTS_ULP_EQUAL(eve::diff(eve::laguerre)(3u, T{2.0}), df2(3, T(2.0))  , ulp);
    TTS_ULP_EQUAL(eve::diff(eve::laguerre)(3u, T{1.0}), df2(3, T(1.0))  , ulp);
  }
}
