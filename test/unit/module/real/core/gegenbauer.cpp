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
#include <eve/function/gegenbauer.hpp>
#include <eve/function/diff/gegenbauer.hpp>
#include <type_traits>
#include <cmath>
#include <boost/math/special_functions/gegenbauer.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of gegenbauer on wide"
        , eve::test::simd::ieee_reals
        )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::gegenbauer(0u, T(0), T(0)), T);
  TTS_EXPR_IS( eve::gegenbauer(0u, v_t(), v_t()), v_t);

  TTS_EXPR_IS( eve::diff(eve::gegenbauer)(0, T(), T())  , T);
  TTS_EXPR_IS( eve::diff(eve::gegenbauer)(0, v_t(), v_t()), v_t);
};


//==================================================================================================
// gegenbauer tests
//==================================================================================================
EVE_TEST( "Check behavior of gegenbauer on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::ramp(0))
        )
  <typename T>( T const& a0 )
{
  using v_t = eve::element_type_t<T>;
  v_t l(-3.0/8.0);
  for(unsigned int n=0; n < 10; ++n)
  {
    auto ref = [&](auto i, auto ){ return boost::math::gegenbauer(n, l, a0.get(i)); };
    TTS_ULP_EQUAL(eve::gegenbauer(n, l, a0), T(ref), 2);
  }
};
