//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/detail/diff_div.hpp>
#include <eve/function/diff/cyl_bessel_y.hpp>
#include <eve/function/diff/sin.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/inf.hpp>
#include <eve/function/sqrt.hpp>
#include <type_traits>

TTS_CASE_TPL("Check diff(cyl_bessel_y) return type", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::diff(eve::cyl_bessel_y)(int(), T()), T);
  }
}

TTS_CASE_TPL("Check eve::diff(eve::cyl_bessel_y) behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    using elt_t = eve::element_type_t<T>;
    auto df2 = [](auto n, auto x){
      auto cy =  [&n](auto a){ return eve::cyl_bessel_y(n, a);  };
      return eve::detail::centered_diffdiv(cy, x);
    };
    auto ulp =  (sizeof(elt_t) == 4) ? 1.0e4 : 1.0e9;
    TTS_ULP_EQUAL(eve::diff(eve::cyl_bessel_y)(2, T{2.0}), df2(2, T(2.0))  , ulp);
    TTS_ULP_EQUAL(eve::diff(eve::cyl_bessel_y)(2, T{1.0}), df2(2, T(1.0))  , ulp);
    TTS_ULP_EQUAL(eve::diff(eve::cyl_bessel_y)(3, T{2.0}), df2(3, T(2.0))  , ulp);
    TTS_ULP_EQUAL(eve::diff(eve::cyl_bessel_y)(3, T{1.0}), df2(3, T(1.0))  , ulp);
  }
}
