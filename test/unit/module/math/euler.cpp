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
TTS_CASE_TPL("Check return types of euler", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::euler(as<T>()), T);
  TTS_EXPR_IS(eve::euler(as<v_t>()), v_t);
};

//==================================================================================================
// e  tests
//==================================================================================================
TTS_CASE_TPL("Check behavior of e on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;

  using elt_t = eve::element_type_t<T>;
  if constexpr( sizeof(long double) > sizeof(elt_t) )
  {
    TTS_EXPECT(eve::euler[eve::downward](as<elt_t>()) < std::exp(1.0l));
    TTS_EXPECT(eve::euler[eve::upward](as<elt_t>()) > std::exp(1.0l));
   }
  TTS_EQUAL(eve::euler(as<T>()), T(std::exp(1.0l)));
  TTS_EXPECT(eve::all(eve::euler[eve::downward](as<T>()) <= eve::euler(as<T>())));
  TTS_EXPECT(eve::all(eve::euler(as<T>()) <= eve::euler[eve::upward](as<T>())));
  auto is_near = [](auto a, auto b){ return eve::if_else( a < b, (eve::next(a) == b) && (eve::prev(a) == b) , a == b); };
  TTS_EXPECT(eve::all(is_near(eve::next(eve::euler[eve::downward](as<T>())), eve::euler[eve::upward](as<T>()))));
};
