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
TTS_CASE_TPL("Check return types of two_o_pi", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::two_o_pi(as<T>()), T);
  TTS_EXPR_IS(eve::two_o_pi(as<v_t>()), v_t);
};
//==================================================================================================
// two_o_pi  tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of two_o_pi on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;

  TTS_EQUAL(eve::two_o_pi(as<T>()), T(2) / T(4 * std::atan(1.0l)));
};

//==================================================================================================
// two_o_pi  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of two_o_pi on scalar", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::next(eve::two_o_pi[eve::downward](as<T>())), eve::two_o_pi[eve::upward](as<T>()))));
};


//==================================================================================================
// simd Tests for masked two_o_pi
//==================================================================================================
TTS_CASE_WITH("Check behavior of two_o_pi[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::two_o_pi[mask](eve::as(a0)), eve::if_else(mask, eve::two_o_pi(eve::as(a0)), eve::zero));
};
