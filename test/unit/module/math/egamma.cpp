//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL( "Check return types of egamma"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS( eve::egamma(as<T>())  , T);
  TTS_EXPR_IS( eve::egamma(as<v_t>()), v_t);
};

//==================================================================================================
// e  tests
//==================================================================================================
TTS_CASE_TPL( "Check behavior of e on wide"
        , eve::test::simd::ieee_reals
        )
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;

  using elt_t = eve::element_type_t<T>;
  if constexpr(sizeof(long double) > sizeof(elt_t))
  {
    TTS_EXPECT(downward(eve::egamma)(as<elt_t>()) < 0.57721566490153286060651209008l);
    TTS_EXPECT(upward(eve::egamma)(as<elt_t>()) > 0.57721566490153286060651209008l);
  }
  TTS_EQUAL(eve::egamma(as<T>()), T(0.57721566490153286060651209008l));
  TTS_EXPECT(eve::all(downward(eve::egamma)(as<T>()) <= eve::egamma(as<T>())));
  TTS_EXPECT(eve::all(eve::egamma(as<T>()) <= upward(eve::egamma)(as<T>())));
  TTS_ULP_EQUAL(downward(eve::egamma)(as<T>()), upward(eve::egamma)(as<T>()), 0.5);
};
