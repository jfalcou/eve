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
TTS_CASE_TPL("Check return types of log2_e", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::log2_e(as<T>()), T);
  TTS_EXPR_IS(eve::log2_e(as<v_t>()), v_t);
};

//==================================================================================================
// log2_e  tests
//==================================================================================================
TTS_CASE_TPL("Check behavior of log2_e on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;
  using elt_t = eve::element_type_t<T>;
  if constexpr( sizeof(long double) > sizeof(elt_t) )
  {
    TTS_EXPECT(eve::log2_e[eve::downward](as<elt_t>()) < std::log2(std::exp(1.0l)));
    TTS_EXPECT(eve::log2_e[eve::upward](as<elt_t>()) > std::log2(std::exp(1.0l)));
  }
  TTS_ULP_EQUAL(eve::log2_e(as<T>()), T(std::log2(std::exp(1.0l))), 0.0);
  TTS_EXPECT(eve::all(eve::log2_e[eve::downward](as<T>()) <= eve::log2_e(as<T>())));
  TTS_EXPECT(eve::all(eve::log2_e(as<T>()) <= eve::log2_e[eve::upward](as<T>())));
  TTS_ULP_EQUAL(eve::log2_e[eve::downward](as<T>()), eve::log2_e[eve::upward](as<T>()), 0.5);
  auto is_near = [](auto a, auto b){ return eve::if_else( a < b, (eve::next(a) == b) && (eve::prev(a) == b) , a == b); };
  TTS_EXPECT(eve::all(is_near(eve::next(eve::log2_e[eve::downward](as<T>())), eve::log2_e[eve::upward](as<T>()))));
  TTS_ULP_EQUAL(eve::log2_e[eve::downward](as<T>()), eve::log2_e[eve::upward](as<T>()), 0.5);
};
