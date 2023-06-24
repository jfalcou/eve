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

TTS_CASE_WITH( "Check behavior of manhattan on wide"
             , eve::test::simd::ieee_reals
             ,tts::generate(tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10))
             )
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
  using z_t = eve::as_quaternion_t<T>;
  auto a = z_t(a0, a1, a0, a3);
  auto b = z_t(a2, a3, a0, a0);
  TTS_ULP_EQUAL( eve::manhattan(a, b),      eve::manhattan(eve::abs(a), eve::abs(b)), 0.5);
  TTS_ULP_EQUAL( eve::manhattan(a, a2),     eve::manhattan(eve::abs(a), eve::abs(a2)), 0.5);
  TTS_ULP_EQUAL( eve::manhattan(a0, b),     eve::manhattan(eve::abs(a0), eve::abs(b)), 0.5);
  TTS_ULP_EQUAL( eve::manhattan(a, T(1.0)), eve::manhattan(eve::abs(a), T(1)), 0.5);
};
