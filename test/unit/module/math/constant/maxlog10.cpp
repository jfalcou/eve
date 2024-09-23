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
TTS_CASE_TPL("Check return types of maxlog10", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::maxlog10(as<T>()), T);
  TTS_EXPR_IS(eve::maxlog10(as<v_t>()), v_t);
};
//==================================================================================================
// maxlog10  tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of maxlog10 on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_IEEE_EQUAL(eve::exp10(eve::maxlog10(as<T>())), eve::inf(as<T>()));
};

//==================================================================================================
// maxlog10  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of maxlog10 on scalar", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_IEEE_EQUAL(eve::exp10(eve::maxlog10(as<T>())), eve::inf(as<T>()));
  TTS_EXPECT(eve::all(eve::is_finite(eve::exp(eve::prev(eve::maxlog10(as<T>()))))));
  TTS_EXPECT(eve::all(eve::test::is_near(eve::maxlog10[eve::lower](as<T>()), eve::maxlog10[eve::upper](as<T>()))));
  TTS_EXPECT(eve::all(eve::is_finite(eve::exp(eve::prev(eve::maxlog10(as<T>()))))));
};


//==================================================================================================
// simd Tests for masked maxlog10
//==================================================================================================
TTS_CASE_WITH("Check behavior of maxlog10[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::maxlog10[mask](eve::as(a0)), eve::if_else(mask, eve::maxlog10(eve::as(a0)), eve::zero));
};
