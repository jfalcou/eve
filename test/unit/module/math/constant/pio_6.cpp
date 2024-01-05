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
// pio_6 Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of pio_6", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::pio_6(as<T>()), T);
  TTS_EXPR_IS(eve::pio_6(as<v_t>()), v_t);
};
//==================================================================================================
// pio_6 tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of pio_6 on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( sizeof(long double) > sizeof(T) )
  {
    TTS_EXPECT(eve::pio_6[eve::downward](eve::as<T>()) <= 3.141592653589793238462643l/6);
    TTS_EXPECT(eve::pio_6[eve::upward](eve::as<T>()) >= 3.141592653589793238462643l/6);
  }
  TTS_ULP_EQUAL(eve::pio_6(eve::as<T>()), T(3.141592653589793238462643l/6), 0.5);
};

//==================================================================================================
// pio_6  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of pio_6 on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::pio_6[eve::downward](as<T>()), eve::pio_6[eve::upward](as<T>()))));
};


//==================================================================================================
// simd Tests for masked pio_6
//==================================================================================================
TTS_CASE_WITH("Check behavior of pio_6[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::pio_6[mask](eve::as(a0)), eve::if_else(mask, eve::pio_6(eve::as(a0)), eve::zero));
};
