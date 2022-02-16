//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of egamma"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS( eve::egamma(as<T>())  , T);
  TTS_EXPR_IS( eve::egamma(as<v_t>()), v_t);
};

//==================================================================================================
// e  tests
//==================================================================================================
EVE_TEST_TYPES( "Check behavior of e on wide"
        , eve::test::simd::ieee_reals
        )
<typename T>(eve::as<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;

  if constexpr(sizeof(long double) > sizeof(elt_t))
  {
    using elt_t = eve::element_type_t<T>;
    TTS_EXPECT(downward(eve::egamma)(as<elt_t>()) < 0.57721566490153286060651209008l);
    TTS_EXPECT(upward(eve::egamma)(as<elt_t>()) > 0.57721566490153286060651209008l);
  }
  TTS_EQUAL(eve::egamma(as<T>()), T(0.57721566490153286060651209008l));
  TTS_EXPECT(eve::all(downward(eve::egamma)(as<T>()) <= eve::egamma(as<T>())));
  TTS_EXPECT(eve::all(eve::egamma(as<T>()) <= upward(eve::egamma)(as<T>())));
  TTS_ULP_EQUAL(downward(eve::egamma)(as<T>()), upward(eve::egamma)(as<T>()), 0.5);
};
