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

TTS_CASE_WITH( "Check behavior of conj on scalar"
        , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate( tts::randoms(-1000.0, 1000.0)
                            , tts::randoms(-1000.0, 1000.0)
                            )
             )
<typename T>(T const& a0, T const& a1)
{
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      TTS_EQUAL( eve::conj(eve::quaternion(e, f, f, e)), eve::quaternion(e,-f, -f, -e) );
    }
  }
};

TTS_CASE_WITH( "Check behavior of conj on wide"
             , eve::test::simd::ieee_reals
             , tts::generate(tts::randoms(-1000.0, 1000.0)
                            , tts::randoms(-1000.0, 1000.0)
                            , tts::randoms(-1000.0, 1000.0)
                            , tts::randoms(-1000.0, 1000.0)
                            )
             )
  <typename T>(T const& a0 , T const& a1, T const& a2, T const& a3)
{
  using z_t = eve::as_quaternion_t<T>;
  TTS_EQUAL( eve::conj(z_t{a0, a1, a2, a3}), (z_t{a0, -a1, -a2, -a3}));
};
