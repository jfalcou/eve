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
TTS_CASE_TPL("Check return types of maxlog", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::maxlog(as<T>()), T);
  TTS_EXPR_IS(eve::maxlog(as<v_t>()), v_t);
};
//==================================================================================================
// maxlog  tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of maxlog on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_IEEE_EQUAL(eve::exp(eve::maxlog(as<T>())), eve::inf(as<T>()));
};

//==================================================================================================
// maxlog  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of maxlog on scalar", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_IEEE_EQUAL(eve::exp(eve::maxlog(as<T>())), eve::inf(as<T>()));
  TTS_EXPECT(eve::all(eve::is_finite(eve::exp(eve::prev(eve::maxlog(as<T>()))))));
  TTS_EXPECT(eve::all(eve::test::is_near(eve::maxlog[eve::lower](as<T>()), eve::maxlog[eve::upper](as<T>()))));
  TTS_EXPECT(eve::all(eve::is_finite(eve::exp(eve::prev(eve::maxlog(as<T>()))))));
};


//==================================================================================================
// simd Tests for masked maxlog
//==================================================================================================
TTS_CASE_WITH("Check behavior of maxlog[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::maxlog[mask](eve::as(a0)), eve::if_else(mask, eve::maxlog(eve::as(a0)), eve::zero));
};
