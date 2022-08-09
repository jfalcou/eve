//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
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
TTS_CASE_TPL( "Check return types of twopi"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS( eve::twopi(as<T>())  , T);
  TTS_EXPR_IS( eve::twopi(as<v_t>()), v_t);
};

//==================================================================================================
// twopi  tests
//==================================================================================================
TTS_CASE_TPL( "Check behavior of twopi on wide"
        , eve::test::simd::ieee_reals
        )
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;

  TTS_EQUAL(eve::twopi(as<T>()), T(8*std::atan(1.0l)));
  TTS_EXPECT(eve::all(downward(eve::twopi)(as<T>()) <= eve::twopi(as<T>())));
  TTS_EXPECT(eve::all(eve::twopi(as<T>()) <= upward(eve::twopi)(as<T>())));
  TTS_ULP_EQUAL(downward(eve::twopi)(as<T>()), upward(eve::twopi)(as<T>()), 0.5);
};
