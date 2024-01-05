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
#include <iomanip>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of minlog2", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::minlog2(as<T>()), T);
  TTS_EXPR_IS(eve::minlog2(as<v_t>()), v_t);
};
//==================================================================================================
// minlog2  tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of minlog2 on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_IEEE_EQUAL(eve::exp2(eve::minlog2(as<T>())), eve::zero(as<T>()));
};

//==================================================================================================
// minlog2  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of minlog2 on scalar", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_IEEE_EQUAL(eve::exp2(eve::minlog2(as<T>())), eve::zero(as<T>()));
#ifdef SPY_ARCH_IS_ARM
  TTS_EXPECT(eve::all(eve::is_gtz(eve::exp2(eve::next(eve::minlog2(as<T>()))))));
#endif
};


//==================================================================================================
// simd Tests for masked minlog2
//==================================================================================================
TTS_CASE_WITH("Check behavior of minlog2[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::minlog2[mask](eve::as(a0)), eve::if_else(mask, eve::minlog2(eve::as(a0)), eve::zero));
};
