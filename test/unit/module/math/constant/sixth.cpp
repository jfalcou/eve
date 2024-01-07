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
// sixth Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of sixth", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::sixth(as<T>()), T);
  TTS_EXPR_IS(eve::sixth(as<v_t>()), v_t);
};
//==================================================================================================
// sixth tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of sixth on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( sizeof(long double) > sizeof(T) )
  {
    TTS_EXPECT(eve::sixth[eve::downward](eve::as<T>()) <= 1.0l/6);
    TTS_EXPECT(eve::sixth[eve::upward](eve::as<T>()) >= 1.0l/6);
  }
  TTS_EQUAL(eve::sixth(eve::as<T>()), T(1.0l/6));
};

//==================================================================================================
// sixth  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of sixth on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::sixth[eve::downward](as<T>()), eve::sixth[eve::upward](as<T>()))));
};


//==================================================================================================
// simd Tests for masked sixth
//==================================================================================================
TTS_CASE_WITH("Check behavior of sixth[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::sixth[mask](eve::as(a0)), eve::if_else(mask, eve::sixth(eve::as(a0)), eve::zero));
};
