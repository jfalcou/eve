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
TTS_CASE_TPL("Check return types of pi", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::pi(as<T>()), T);
  TTS_EXPR_IS(eve::pi(as<v_t>()), v_t);
};

//==================================================================================================
// pi  tests
//==================================================================================================
TTS_CASE_TPL("Check behavior of pi on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;
  using elt_t = eve::element_type_t<T>;
  if constexpr( sizeof(long double) > sizeof(elt_t) )
  {
    TTS_EXPECT(eve::pi[eve::downward](as<elt_t>()) < 4 * std::atan(1.0l));
    TTS_EXPECT(eve::pi[eve::upward](as<elt_t>()) > 4 * std::atan(1.0l));
  }
  TTS_EQUAL(eve::pi(as<T>()), T(4 * std::atan(1.0l)));
  TTS_EXPECT(eve::all(eve::pi[eve::downward](as<T>()) <= eve::pi(as<T>())));
  TTS_EXPECT(eve::all(eve::pi(as<T>()) <= eve::pi[eve::upward](as<T>())));
  TTS_ULP_EQUAL(eve::pi[eve::downward](as<T>()), eve::pi[eve::upward](as<T>()), 0.5);
  auto is_near = [](auto a, auto b){ return eve::if_else( a < b, (eve::next(a) == b) && (eve::prev(a) == b) , a == b); };
  TTS_EXPECT(eve::all(is_near(eve::next(eve::pi[eve::downward](as<T>())), eve::pi[eve::upward](as<T>()))));
  TTS_ULP_EQUAL(eve::pi[eve::downward](as<T>()), eve::pi[eve::upward](as<T>()), 0.5);
};
