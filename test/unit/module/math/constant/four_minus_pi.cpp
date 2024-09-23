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
// four_minus_pi Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of four_minus_pi", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::four_minus_pi(as<T>()), T);
  TTS_EXPR_IS(eve::four_minus_pi(as<v_t>()), v_t);
};
//==================================================================================================
// four_minus_pi tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of four_minus_pi on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( sizeof(long double) > sizeof(T) )
  {
    TTS_EXPECT(eve::four_minus_pi[eve::lower](eve::as<T>()) <= 4.0l-3.141592653589793238462643l);
    TTS_EXPECT(eve::four_minus_pi[eve::upper](eve::as<T>()) >= 4.0l-3.141592653589793238462643l);
  }
  TTS_ULP_EQUAL(eve::four_minus_pi(eve::as<T>()), T(4.0l-3.141592653589793238462643l), 0.5);
};

//==================================================================================================
// four_minus_pi  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of four_minus_pi on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::four_minus_pi[eve::lower](as<T>()), eve::four_minus_pi[eve::upper](as<T>()))));
};


//==================================================================================================
// simd Tests for masked four_minus_pi
//==================================================================================================
TTS_CASE_WITH("Check behavior of four_minus_pi[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::four_minus_pi[mask](eve::as(a0)), eve::if_else(mask, eve::four_minus_pi(eve::as(a0)), eve::zero));
};
