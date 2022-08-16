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
TTS_CASE_TPL("Check return types of invsqrtpi", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::invsqrtpi(as<T>()), T);
  TTS_EXPR_IS(eve::invsqrtpi(as<v_t>()), v_t);
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
    TTS_EXPECT(downward(eve::invsqrtpi)(as<elt_t>())
               < 0.564189583547756286948079451560772585844050629329l);
    TTS_EXPECT(upward(eve::invsqrtpi)(as<elt_t>())
               > 0.564189583547756286948079451560772585844050629329l);
  }
  TTS_EQUAL(eve::invsqrtpi(as<T>()), T(0.564189583547756286948079451560772585844050629329l));
  TTS_EXPECT(eve::all(downward(eve::invsqrtpi)(as<T>()) <= eve::invsqrtpi(as<T>())));
  TTS_EXPECT(eve::all(eve::invsqrtpi(as<T>()) <= upward(eve::invsqrtpi)(as<T>())));
  TTS_ULP_EQUAL(downward(eve::invsqrtpi)(as<T>()), upward(eve::invsqrtpi)(as<T>()), 0.5);
};
