//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/complex.hpp>
#include <complex>

TTS_CASE_WITH( "Check behavior of dot on wide"
             , eve::test::simd::ieee_reals
             ,tts::generate( tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           )
             )
  <typename T>(T const& a0, T const& a1)
{
  auto tol = 0.001;
  using e_t = eve::element_type_t<T>;
  TTS_RELATIVE_EQUAL(eve::dot(a0, a0), eve::sqr_abs(a0), tol);
  TTS_RELATIVE_EQUAL(eve::dot(a0, a1), eve::real(a0)*eve::real(a1), tol);
  TTS_RELATIVE_EQUAL(eve::dot(a0, e_t(2)), e_t(2)*a0, tol);
  TTS_RELATIVE_EQUAL(eve::dot(e_t(2), a0), e_t(2)*a0, tol);
};
