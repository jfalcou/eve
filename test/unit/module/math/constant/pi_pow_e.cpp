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
// pi_pow_e Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of pi_pow_e", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::pi_pow_e(as<T>()), T);
  TTS_EXPR_IS(eve::pi_pow_e(as<v_t>()), v_t);
};
//==================================================================================================
// pi_pow_e tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of pi_pow_e on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( sizeof(long double) > sizeof(T) )
  {
    TTS_EXPECT(eve::pi_pow_e[eve::downward](eve::as<T>()) <= std::pow(3.141592653589793238462643l,std::exp(1.0l)));
    TTS_EXPECT(eve::pi_pow_e[eve::upward](eve::as<T>()) >= std::pow(3.141592653589793238462643l,std::exp(1.0l))); 
  }
  TTS_EQUAL(eve::pi_pow_e(eve::as<T>()), T(std::pow(3.141592653589793238462643l,std::exp(1.0l))));
};

//==================================================================================================
// pi_pow_e  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of pi_pow_e on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::pi_pow_e[eve::downward](as<T>()), eve::pi_pow_e[eve::upward](as<T>()))));
};


//==================================================================================================
// simd Tests for masked pi_pow_e
//==================================================================================================
TTS_CASE_WITH("Check behavior of pi_pow_e[mask] on :wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::pi_pow_e[mask](eve::as(a0)), eve::if_else(mask, eve::pi_pow_e(eve::as(a0)), eve::zero));
};
