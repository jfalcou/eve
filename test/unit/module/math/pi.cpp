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
TTS_CASE_TPL( "Check return types of pi"
            , eve::test::simd::ieee_reals
            )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS( eve::pi(as<T>())  , T);
  TTS_EXPR_IS( eve::pi(as<v_t>()), v_t);
};

//==================================================================================================
// pi  tests
//==================================================================================================
TTS_CASE_TPL( "Check behavior of pi on wide"
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
    TTS_EXPECT(downward(eve::pi)(as<elt_t>()) < 4*std::atan(1.0l));
    TTS_EXPECT(upward(eve::pi)(as<elt_t>())   > 4*std::atan(1.0l));
  }  TTS_EQUAL(eve::pi(as<T>()), T(4*std::atan(1.0l)));
  TTS_EXPECT(eve::all(downward(eve::pi)(as<T>()) <= eve::pi(as<T>())));
  TTS_EXPECT(eve::all(eve::pi(as<T>()) <= upward(eve::pi)(as<T>())));
  TTS_ULP_EQUAL(downward(eve::pi)(as<T>()), upward(eve::pi)(as<T>()), 0.5);
};
