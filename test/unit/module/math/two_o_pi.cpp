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
TTS_CASE_TPL( "Check return types of two_o_pi"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS( eve::two_o_pi(as<T>())  , T);
  TTS_EXPR_IS( eve::two_o_pi(as<v_t>()), v_t);
};

//==================================================================================================
// two_o_pi  tests
//==================================================================================================
TTS_CASE_TPL( "Check behavior of two_o_pi on wide"
        , eve::test::simd::ieee_reals
        )
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;

  TTS_EQUAL(eve::two_o_pi(as<T>()), T(2)/T(4*std::atan(1.0l)));
  TTS_EXPECT(eve::all(downward(eve::two_o_pi)(as<T>()) <= eve::two_o_pi(as<T>())));
  TTS_EXPECT(eve::all(eve::two_o_pi(as<T>()) <= upward(eve::two_o_pi)(as<T>())));
  TTS_ULP_EQUAL(downward(eve::two_o_pi)(as<T>()), upward(eve::two_o_pi)(as<T>()), 0.5);
};
