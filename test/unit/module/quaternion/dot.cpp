//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"
#include <eve/module/quaternion.hpp>
#include <complex>

TTS_CASE_WITH( "Check behavior of dot on wide quaternion"
             , eve::test::simd::ieee_reals
             ,tts::generate( tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           )
             )
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
  using z_t = eve::as_quaternion_t<T>;
  auto aa = z_t(a0, a1, a2, a3);
  auto bb = z_t(a0*2, a1*3, a2*4, a3*5);
  using e_t = eve::element_type_t<T>;
  using c_t = eve::wide<eve::complex<e_t>, eve::cardinal_t<T>>;
  auto tol = 0.001;
  TTS_RELATIVE_EQUAL(eve::dot(aa, aa), eve::sqr_abs(aa), tol);
  TTS_RELATIVE_EQUAL(eve::dot(aa, bb), eve::real(aa)*eve::real(bb)+eve::ipart(aa)*eve::ipart(bb)+
                     eve::jpart(aa)*eve::jpart(bb)+eve::kpart(aa)*eve::kpart(bb), tol);
  TTS_RELATIVE_EQUAL(eve::dot(aa, e_t(2)), e_t(2)*eve::real(aa), tol);
  TTS_RELATIVE_EQUAL(eve::dot(e_t(2), aa), e_t(2)*eve::real(aa), tol);
  TTS_RELATIVE_EQUAL(eve::dot(aa, c_t(e_t(2), e_t(3))), e_t(2)*eve::real(aa)+e_t(3)*eve::ipart(aa), tol);
  TTS_RELATIVE_EQUAL(eve::dot(c_t(e_t(2), e_t(3)), aa), e_t(2)*eve::real(aa)+e_t(3)*eve::ipart(aa), tol);

};
