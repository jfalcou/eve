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
TTS_CASE_TPL("Check return types of pio_2", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::pio_2(as<T>()), T);
  TTS_EXPR_IS(eve::pio_2(as<v_t>()), v_t);
};
//==================================================================================================
// pio_2  tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of pio_2 on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;

  using elt_t = eve::element_type_t<T>;
  if constexpr( sizeof(long double) > sizeof(elt_t) )
  {
    TTS_EXPECT(eve::pio_2[eve::downward](as<elt_t>()) < 2 * std::atan(1.0l));
    TTS_EXPECT(eve::pio_2[eve::upward](as<elt_t>()) > 2 * std::atan(1.0l));
  }
  TTS_EQUAL(eve::pio_2(as<T>()), T(2 * std::atan(1.0l)));
};

//==================================================================================================
// pio_2  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of pio_2 on scalar", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::next(eve::pio_2[eve::downward](as<T>())), eve::pio_2[eve::upward](as<T>()))));
};


//==================================================================================================
// simd Tests for masked pio_2
//==================================================================================================
TTS_CASE_WITH("Check behavior of pio_2[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::pio_2[mask](eve::as(a0)), eve::if_else(mask, eve::pio_2(eve::as(a0)), eve::zero));
};
