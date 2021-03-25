//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/hermite.hpp>
#include <eve/function/diff/hermite.hpp>
#include <type_traits>
#include <cmath>
#include <boost/math/special_functions/hermite.hpp>
#include <eve/detail/diff_div.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of hermite on wide"
        , eve::test::simd::ieee_reals
        )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::hermite(0u, T(0)), T);
  TTS_EXPR_IS( eve::hermite(0u, v_t()), v_t);

  TTS_EXPR_IS( eve::diff(eve::hermite)(0, T())  , T);
  TTS_EXPR_IS( eve::diff(eve::hermite)(0, v_t()), v_t);
};


//==================================================================================================
// hermite tests
//==================================================================================================
EVE_TEST( "Check behavior of hermite on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::ramp(0))
        )
  <typename T>( T const& a0 )
{
  for(unsigned int n=0; n < 10; ++n)
  {
    auto ref = [&](auto i, auto ){ return boost::math::hermite(n, a0.get(i)); };
    TTS_ULP_EQUAL(eve::hermite(n, a0), T(ref), 2);
  }

  // derivative : this is an approximate test with centerd rough diff estimation
  using elt_t = eve::element_type_t<T>;
  auto df2 = [](auto n, auto x){
    auto cy =  [&n](auto a){ return eve::hermite(n, a);  };
    return eve::detail::centered_diffdiv(cy, x);
  };
  auto ulp =  (sizeof(elt_t) == 4) ? 1.0e4 : 1.0e9;
  TTS_ULP_EQUAL(eve::diff(eve::hermite)(2u, T{2.0}), df2(2, T(2.0))  , ulp);
  TTS_ULP_EQUAL(eve::diff(eve::hermite)(2u, T{1.0}), df2(2, T(1.0))  , ulp);
  TTS_ULP_EQUAL(eve::diff(eve::hermite)(3u, T{2.0}), df2(3, T(2.0))  , ulp);
  TTS_ULP_EQUAL(eve::diff(eve::hermite)(3u, T{1.0}), df2(3, T(1.0))  , ulp);
};
