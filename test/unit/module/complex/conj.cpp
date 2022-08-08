//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"
#include <eve/module/complex.hpp>

TTS_CASE_WITH( "Check behavior of conj on scalar"
        , tts::bunch<eve::test::scalar::ieee_reals>
        , tts::generate(tts::randoms(-1000.0, 1000.0))
        )
<typename T>(T const& a0 )
{
  for(auto e : a0)
  {
    TTS_EQUAL( eve::conj(e), e );
    TTS_EQUAL( eve::conj(eve::complex(e, e)), eve::complex(e,-e) );
  }
};

TTS_CASE_WITH( "Check behavior of conj on wide"
        , eve::test::simd::ieee_reals
        , tts::generate(tts::randoms(-1000.0, 1000.0))
        )
<typename T>(T const& a0 )
{
  using z_t = eve::as_complex_t<T>;
  TTS_EQUAL( eve::conj(a0), a0 );
  TTS_EQUAL( eve::conj(z_t{a0,a0}), (z_t{a0,-a0}));
};
