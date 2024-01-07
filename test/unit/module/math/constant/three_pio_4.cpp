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
// three_pio_4 Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of three_pio_4", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::three_pio_4(as<T>()), T);
  TTS_EXPR_IS(eve::three_pio_4(as<v_t>()), v_t);
};
//==================================================================================================
// three_pio_4 tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of three_pio_4 on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( sizeof(long double) > sizeof(T) )
  {
    TTS_EXPECT(eve::three_pio_4[eve::downward](eve::as<T>()) <= 3.0*3.141592653589793238462643l/4);
    TTS_EXPECT(eve::three_pio_4[eve::upward](eve::as<T>()) >= 3.0*3.141592653589793238462643l/4); 
  }
  TTS_EQUAL(eve::three_pio_4(eve::as<T>()), T(3.0*3.141592653589793238462643l/4));
};

//==================================================================================================
// three_pio_4  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of three_pio_4 on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::three_pio_4[eve::downward](as<T>()), eve::three_pio_4[eve::upward](as<T>()))));
};


//==================================================================================================
// simd Tests for masked three_pio_4
//==================================================================================================
TTS_CASE_WITH("Check behavior of three_pio_4[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::three_pio_4[mask](eve::as(a0)), eve::if_else(mask, eve::three_pio_4(eve::as(a0)), eve::zero));
};
