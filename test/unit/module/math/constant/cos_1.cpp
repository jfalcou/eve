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
// cos_1 Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of cos_1", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::cos_1(as<T>()), T);
  TTS_EXPR_IS(eve::cos_1(as<v_t>()), v_t);
};
//==================================================================================================
// cos_1 tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of cos_1 on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( sizeof(long double) > sizeof(T) )
  {
    TTS_EXPECT(eve::cos_1[eve::downward](eve::as<T>()) <= std::cos(1.0l));
    TTS_EXPECT(eve::cos_1[eve::upward](eve::as<T>()) >= std::cos(1.0l)); 
  }
  TTS_EQUAL(eve::cos_1(eve::as<T>()), T(std::cos(1.0l)));
};

//==================================================================================================
// cos_1  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of cos_1 on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::cos_1[eve::downward](as<T>()), eve::cos_1[eve::upward](as<T>()))));
};


//==================================================================================================
// simd Tests for masked cos_1
//==================================================================================================
TTS_CASE_WITH("Check behavior of cos_1[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::cos_1[mask](eve::as(a0)), eve::if_else(mask, eve::cos_1(eve::as(a0)), eve::zero));
};
