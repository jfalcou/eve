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

TTS_CASE_WITH( "Check behavior of is_pure on wide"
             , eve::test::simd::ieee_reals
             , tts::generate(tts::randoms(-10, 10)
                            , tts::randoms(-10, 10)
                            , tts::randoms(-10, 10)
                            , tts::randoms(-10, 10)
                            )
             )
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using z_t = eve::as_quaternion_t<T>;
  auto a = z_t(a0, a1, a2, a3);
  TTS_EQUAL( eve::is_pure(a), eve::is_eqz(a0));
};
