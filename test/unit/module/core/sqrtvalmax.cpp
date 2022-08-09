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
TTS_CASE_TPL("Check return types of sqrtvalmax", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::sqrtvalmax(as<T>()), T);
  TTS_EXPR_IS(eve::sqrtvalmax(as<v_t>()), v_t);
};

//==================================================================================================
// sqrtvalmax  tests
//==================================================================================================
TTS_CASE_TPL("Check behavior of sqrtvalmax on wide", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;

  using elt_t = eve::element_type_t<T>;
  TTS_EQUAL(eve::sqrtvalmax(as<T>()), T(eve::sqrt(eve::valmax(as<elt_t>()))));
  if constexpr( eve::floating_value<T> )
    TTS_EQUAL(eve::sqr(eve::next(eve::sqrtvalmax(as<T>()))), eve::inf(as<T>()));
  TTS_EXPECT(eve::all(downward(eve::sqrtvalmax)(as<T>()) <= eve::sqrt((eve::valmax(as<T>())))));
  TTS_EXPECT(eve::all(eve::sqrtvalmax(as<T>()) <= upward(eve::sqrtvalmax)(as<T>())));
  TTS_ULP_EQUAL(downward(eve::sqrtvalmax)(as<T>()), upward(eve::sqrtvalmax)(as<T>()), 0.5);
};
