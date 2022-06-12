//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/complex.hpp>

TTS_CASE_WITH( "Check behavior of abs on scalar"
        , tts::bunch<eve::test::scalar::ieee_reals>
        , tts::generate ( tts::randoms(-1000.0, +1000.0)
                              , tts::randoms(-1000.0, +1000.0)
                              )
        )
<typename T>(T const& a0, T const& a1 )
{
  using eve::pedantic;
  for(auto e : a0)
    for(auto f : a1)
    {
      TTS_EQUAL( eve::abs(eve::complex(e, f)), eve::hypot(e,f) );
      TTS_EQUAL( pedantic(eve::abs)(eve::complex(e, f)), pedantic(eve::hypot)(e,f) );
    }
};

TTS_CASE_WITH( "Check behavior of abs on wide"
        , eve::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-1000.0, +1000.0)
                              , tts::randoms(-1000.0, +1000.0)
                              )
        )
<typename T>(T const& a0, T const& a1 )
{
  using eve::pedantic;
  using z_t = eve::as_complex_t<T>;
  TTS_EQUAL( eve::abs(z_t{a0,a1}), eve::hypot(a0,a1) );
  TTS_EQUAL( pedantic(eve::abs)(z_t{a0,a1}), pedantic(eve::hypot)(a0,a1) );
};
