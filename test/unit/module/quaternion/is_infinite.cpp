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

TTS_CASE_WITH( "Check behavior of is_infinite on wide"
             , eve::test::simd::ieee_reals
             , tts::generate(tts::randoms(-10, 10)
                            , tts::randoms(-10, 10)
                            )
             )
  <typename T>(T a0, T const& a1 )
{
  using z_t = eve::as_quaternion_t<T>;
  auto a = z_t(a0, a1, a0, a1);
  TTS_EQUAL( eve::is_infinite(a), (eve::is_infinite(a0) && eve::is_infinite(a1)));
  auto inf = eve::inf(eve::as(eve::element_type_t<T>()));
  a0.set(0, inf);
  auto b = z_t(a0, a1, a0, a1);
  TTS_EQUAL( eve::is_infinite(b), eve::is_infinite(a0)||eve::is_infinite(a1));
};
