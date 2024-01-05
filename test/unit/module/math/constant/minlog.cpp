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
TTS_CASE_TPL("Check return types of minlog", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::minlog(as<T>()), T);
  TTS_EXPR_IS(eve::minlog(as<v_t>()), v_t);
};
//==================================================================================================
// minlog  tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of minlog on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_IEEE_EQUAL(eve::exp(eve::minlog(as<T>())), eve::zero(as<T>()));
};

//==================================================================================================
// minlog  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of minlog on scalar", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_IEEE_EQUAL(eve::exp(eve::minlog(as<T>())), eve::zero(as<T>()));
#ifndef SPY_ARCH_IS_ARM
  TTS_EXPECT(eve::all(eve::is_gtz(eve::exp(eve::next(eve::minlog(as<T>()))))));
#endif
  TTS_EXPECT(eve::all(eve::test::is_near(eve::minlog[eve::downward](as<T>()), eve::minlog[eve::upward](as<T>()))));
};


//==================================================================================================
// simd Tests for masked minlog
//==================================================================================================
TTS_CASE_WITH("Check behavior of minlog[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::minlog[mask](eve::as(a0)), eve::if_else(mask, eve::minlog(eve::as(a0)), eve::zero));
};
