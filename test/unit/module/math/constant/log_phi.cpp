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
// log_phi Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of log_phi", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::log_phi(as<T>()), T);
  TTS_EXPR_IS(eve::log_phi(as<v_t>()), v_t);
};
//==================================================================================================
// log_phi tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of log_phi on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( sizeof(long double) > sizeof(T) )
  {
    TTS_EXPECT(eve::log_phi[eve::downward](eve::as<T>()) <= std::log(1.618033988749894848204586l));
    TTS_EXPECT(eve::log_phi[eve::upward](eve::as<T>()) >= std::log(1.618033988749894848204586l)); 
  }
  TTS_EQUAL(eve::log_phi(eve::as<T>()), T(std::log(1.618033988749894848204586l)));
};

//==================================================================================================
// log_phi  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of log_phi on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::log_phi[eve::downward](as<T>()), eve::log_phi[eve::upward](as<T>()))));
};


//==================================================================================================
// simd Tests for masked log_phi
//==================================================================================================
TTS_CASE_WITH("Check behavior of log_phi[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::log_phi[mask](eve::as(a0)), eve::if_else(mask, eve::log_phi(eve::as(a0)), eve::zero));
};
