//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"
#include <eve/module/complex.hpp>
#include <complex>

TTS_CASE_WITH( "Check behavior of lpnorm on wide"
             , eve::test::simd::ieee_reals
             ,tts::generate(tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10))
             )
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
  using e_t =  eve::element_type_t<T>;
  using z_t = eve::as_complex_t<T>;
  auto a = z_t(a0, a1);
  auto b = z_t(a2, a3);
  TTS_ULP_EQUAL( eve::lpnorm(e_t(3),a, b),      eve::lpnorm(3, eve::abs(a), eve::abs(b)), 0.5);
  TTS_ULP_EQUAL( eve::lpnorm(3,a, a2),     eve::lpnorm(3, eve::abs(a), eve::abs(a2)), 0.5);
  TTS_ULP_EQUAL( eve::lpnorm(3,a0, b),     eve::lpnorm(3,eve::abs(a0), eve::abs(b)), 0.5);
  TTS_ULP_EQUAL( eve::lpnorm(3,a, T(1.0)), eve::lpnorm(3,eve::abs(a), T(1)), 0.5);
};
