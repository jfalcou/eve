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

TTS_CASE_WITH ( "Check behavior of angle on scalar"
              , tts::bunch<eve::test::scalar::ieee_reals>
              , tts::generate(tts::randoms(-10.0, +10.0)
                             , tts::randoms(-10.0, +10.0)
                             , tts::randoms(-10.0, +10.0)
                             , tts::randoms(-10.0, +10.0)
                             )
              )
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
  for(size_t i = 0; i <= a0.size(); ++i)
  {
    auto z = eve::sign(eve::quaternion(a0[i], a1[i], a2[i], a3[i]));
    TTS_RELATIVE_EQUAL( eve::angle(z), 2*eve::acos(eve::real(z)), 0.02);
  }
};

TTS_CASE_WITH ( "Check behavior of angle on wide"
              , eve::test::simd::ieee_reals
              , tts::generate(tts::randoms(-10.0, +10.0)
                             , tts::randoms(-10.0, +10.0)
                             , tts::randoms(-10.0, +10.0)
                             , tts::randoms(-10.0, +10.0)
                             )
              )
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
  using z_t = eve::as_quaternion_t<T>;
  auto z = eve::sign(z_t(a0, a1, a2, a3));
  TTS_RELATIVE_EQUAL( eve::angle(z), 2*eve::acos(eve::real(z)), 0.025);
};
