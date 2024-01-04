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
// egamma_sqr Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of egamma_sqr", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::egamma_sqr(as<T>()), T);
  TTS_EXPR_IS(eve::egamma_sqr(as<v_t>()), v_t);
};
//==================================================================================================
// egamma_sqr tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of egamma_sqr on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( sizeof(long double) > sizeof(T) )
  {
    TTS_EXPECT(eve::egamma_sqr[eve::downward](eve::as<T>()) <= 0.57721566490153286060651209008l*0.57721566490153286060651209008l);
    TTS_EXPECT(eve::egamma_sqr[eve::upward](eve::as<T>()) >= 0.57721566490153286060651209008l*0.57721566490153286060651209008l); 
  }
  TTS_EQUAL(eve::egamma_sqr(eve::as<T>()), T(0.57721566490153286060651209008l*0.57721566490153286060651209008l));
};

//==================================================================================================
// egamma_sqr  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of egamma_sqr on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::egamma_sqr[eve::downward](as<T>()), eve::egamma_sqr[eve::upward](as<T>()))));
};


//==================================================================================================
// simd Tests for masked egamma_sqr
//==================================================================================================
TTS_CASE_WITH("Check behavior of egamma_sqr[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::egamma_sqr[mask](eve::as(a0)), eve::if_else(mask, eve::egamma_sqr(eve::as(a0)), eve::zero));
};
