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


TTS_CASE_WITH( "Check behavior of pow on wide"
             , eve::test::simd::ieee_reals
             , tts::generate( tts::randoms(-5, 5)
                            , tts::randoms(-5, 5)
                            , tts::randoms(-5, 5)
                            , tts::randoms(-5, 5)
                            )
             )
  <typename T>(T const& a0, T const&  a1, T const& a2, T const&  a3)
{
  auto tol = 0.1;
  using e_t =  eve::element_type_t<T>;
  using z_t = eve::as_quaternion_t<T>;
  z_t z(a0, a1, a2, a3);
  TTS_RELATIVE_EQUAL(eve::pow(z, 1),z, tol);
  TTS_RELATIVE_EQUAL(eve::pow(z, 2),eve::sqr(z), tol);
  TTS_RELATIVE_EQUAL(eve::pow(z, 3),eve::sqr(z)*z, tol);
  TTS_RELATIVE_EQUAL(eve::pow(z, 4),eve::sqr(eve::sqr(z)), tol);

  auto z1 = eve::pow(z, e_t(0.5));
  TTS_RELATIVE_EQUAL(z,eve::sqr(z1), tol);

};
