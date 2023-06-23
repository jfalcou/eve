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

TTS_CASE_WITH( "Check behavior of average on wide quaternion"
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
  auto b = z_t(a0*2, a1*3, a2*4, a3*5);
  auto m = z_t(a0*1.5, a1*2, a2*2.5, a3*3);
  auto c = z_t(a2, 0, 0, 0);
  TTS_EXPECT( eve::all(eve::abs(eve::average(a, b)- m) <= 20.*eve::eps(eve::as<T>())));
  TTS_EXPECT( eve::all(eve::abs( eve::average(a, a2)-  eve::average(a, c))<= 2.*eve::eps(eve::as<T>())));
  TTS_RELATIVE_EQUAL(eve::average(a, b),  m, 20.*eve::eps(eve::as<T>()));
};
