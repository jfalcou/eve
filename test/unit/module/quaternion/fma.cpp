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

TTS_CASE_WITH( "Check behavior of fma on wide quaternion"
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
  auto a = z_t(a0, a1, a2, a3);
  auto b = z_t(a1*2, a0*3, a2*4, a3*5);
  auto c = z_t(a3*1.5, a1*2, a0*2.5, a3*3);
  using e_t = eve::element_type_t<T>;
  auto tol = 100.0*eve::eps(eve::as<e_t>());
  TTS_RELATIVE_EQUAL(eve::fma(a, b, c),  a*b+c, tol);
  TTS_RELATIVE_EQUAL(eve::fma(a, a2, c), a*a2+c,tol);
};
