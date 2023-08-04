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

TTS_CASE_WITH( "Check behavior of dot on wide complex"
             , eve::test::simd::ieee_reals
             ,tts::generate( tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           )
             )
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
  using z_t = eve::as_complex_t<T>;
  auto aa = z_t(a0, a1);
  auto bb = z_t(a2, a3);
  using e_t = eve::element_type_t<T>;
  auto tol = 0.001;
  TTS_RELATIVE_EQUAL(eve::dot(aa, aa), eve::sqr_abs(aa), tol);
  TTS_RELATIVE_EQUAL(eve::dot(aa, bb), eve::real(aa)*eve::real(bb)+eve::imag(aa)*eve::imag(bb), tol);
  TTS_RELATIVE_EQUAL(eve::dot(aa, e_t(2)), e_t(2)*eve::real(aa), tol);
  TTS_RELATIVE_EQUAL(eve::dot(e_t(2), aa), e_t(2)*eve::real(aa), tol);
};
