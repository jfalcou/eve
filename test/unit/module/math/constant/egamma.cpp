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
TTS_CASE_TPL("Check return types of egamma", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::egamma(as<T>()), T);
  TTS_EXPR_IS(eve::egamma(as<v_t>()), v_t);
};
//==================================================================================================
// e  tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of e on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;

  using elt_t = eve::element_type_t<T>;
  if constexpr( sizeof(long double) > sizeof(elt_t) )
  {
    TTS_EXPECT(eve::egamma[eve::downward](as<elt_t>()) < 0.57721566490153286060651209008l);
    TTS_EXPECT(eve::egamma[eve::upward](as<elt_t>()) > 0.57721566490153286060651209008l);
  }
  TTS_EQUAL(eve::egamma(as<T>()), T(0.57721566490153286060651209008l));
};

//==================================================================================================
// e  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of e on scalar", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::egamma[eve::downward](as<T>()), eve::egamma[eve::upward](as<T>()))));
};


//==================================================================================================
// simd Tests for masked egamma
//==================================================================================================
TTS_CASE_WITH("Check behavior of egamma[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::egamma[mask](eve::as(a0)), eve::if_else(mask, eve::egamma(eve::as(a0)), eve::zero));
};
