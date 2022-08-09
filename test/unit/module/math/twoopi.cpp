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
TTS_CASE_TPL( "Check return types of twoopi"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS( eve::twoopi(as<T>())  , T);
  TTS_EXPR_IS( eve::twoopi(as<v_t>()), v_t);
};

//==================================================================================================
// twoopi  tests
//==================================================================================================
TTS_CASE_TPL( "Check behavior of twoopi on wide"
        , eve::test::simd::ieee_reals
        )
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;

  TTS_EQUAL(eve::twoopi(as<T>()), T(2)/T(4*std::atan(1.0l)));
  TTS_EXPECT(eve::all(downward(eve::twoopi)(as<T>()) <= eve::twoopi(as<T>())));
  TTS_EXPECT(eve::all(eve::twoopi(as<T>()) <= upward(eve::twoopi)(as<T>())));
  TTS_ULP_EQUAL(downward(eve::twoopi)(as<T>()), upward(eve::twoopi)(as<T>()), 0.5);
};
