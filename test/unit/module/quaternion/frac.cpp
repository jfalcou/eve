//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/quaternion.hpp>

TTS_CASE_WITH ( "Check behavior of frac on scalar"
              , tts::bunch<eve::test::scalar::ieee_reals>
              , tts::generate(tts::randoms(-1000.0, +1000.0), tts::randoms(-1000.0, +1000.0))
              )
<typename T>(T const& a0, T const& a1 )
{
  for(auto e : a0)
    for(auto f : a1)
    {
      TTS_EQUAL( eve::frac(eve::quaternion(e, f, e, f)), eve::quaternion(eve::frac(e), eve::frac(f)
                                                                         , eve::frac(e), eve::frac(f)));
    }
};

TTS_CASE_WITH ( "Check behavior of frac on wide"
              , eve::test::simd::ieee_reals
              , tts::generate(tts::randoms(-1000.0, +1000.0), tts::randoms(-1000.0, +1000.0))
              )
<typename T>(T const& a0, T const& a1 )
{
  using z_t = eve::as_quaternion_t<T>;
  TTS_EQUAL( eve::frac(z_t{a0,a1,a0,a1 }),z_t(eve::frac(a0), eve::frac(a1), eve::frac(a0), eve::frac(a1)) );
  auto zz = z_t{a0,a1,a0, a1};
  TTS_EQUAL( eve::frac[a0 > 0](zz), eve::if_else(a0 > 0, eve::frac(zz), zz));

};
