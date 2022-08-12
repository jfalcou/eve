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
#include <iomanip>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of inv_pi", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::inv_pi(as<T>()), T);
  TTS_EXPR_IS(eve::inv_pi(as<v_t>()), v_t);
};

//==================================================================================================
// inv_pi  tests
//==================================================================================================
TTS_CASE_TPL("Check behavior of inv_pi on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;
  using elt_t = eve::element_type_t<T>;
  if constexpr( sizeof(long double) > sizeof(elt_t) )
  {
    TTS_EXPECT(downward(eve::inv_pi)(as<elt_t>()) <= (1.0 / (4 * std::atan(1.0l))));
    TTS_EXPECT(upward(eve::inv_pi)(as<elt_t>()) >= (1.0 / (4 * std::atan(1.0l))));
  }
  TTS_ULP_EQUAL(eve::inv_pi(as<T>()), T(1.0 / (4 * std::atan(1.0l))), 0.0);
  TTS_EXPECT(eve::all(downward(eve::inv_pi)(as<T>()) <= eve::inv_pi(as<T>())));
  TTS_EXPECT(eve::all(eve::inv_pi(as<T>()) <= upward(eve::inv_pi)(as<T>())));
  TTS_ULP_EQUAL(downward(eve::inv_pi)(as<T>()), upward(eve::inv_pi)(as<T>()), 0.5);
};
