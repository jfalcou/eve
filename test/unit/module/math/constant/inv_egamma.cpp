//revised
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
// inv_egamma Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of inv_egamma", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::inv_egamma(as<T>()), T);
  TTS_EXPR_IS(eve::inv_egamma(as<v_t>()), v_t);
};
//==================================================================================================
// inv_egamma tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of inv_egamma on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( sizeof(long double) > sizeof(T) )
  {
    TTS_EXPECT(eve::inv_egamma[eve::downward](eve::as<T>()) <= 1.0l/0.57721566490153286060651209008l);
    TTS_EXPECT(eve::inv_egamma[eve::upward](eve::as<T>()) >= 1.0l/0.57721566490153286060651209008l); 
  }
  TTS_EQUAL(eve::inv_egamma(eve::as<T>()), T(1.0l/0.57721566490153286060651209008l));
};

//==================================================================================================
// inv_egamma  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of inv_egamma on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::inv_egamma[eve::downward](as<T>()), eve::inv_egamma[eve::upward](as<T>()))));
};


//==================================================================================================
// simd Tests for masked inv_egamma
//==================================================================================================
TTS_CASE_WITH("Check behavior of inv_egamma[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::inv_egamma[mask](eve::as(a0)), eve::if_else(mask, eve::inv_egamma(eve::as(a0)), eve::zero));
};
