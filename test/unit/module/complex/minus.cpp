//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"
#include <eve/module/complex.hpp>

TTS_CASE_WITH ( "Check behavior of minus on scalar"
              , tts::bunch<eve::test::scalar::ieee_reals>
              , tts::generate(tts::randoms(-1000.0, +1000.0), tts::randoms(-1000.0, +1000.0))
              )
  <typename T>(T const& a0, T const& a1 )
{
  using eve::pedantic;
  for(auto e : a0)
    for(auto f : a1)
    {
      auto z = eve::complex(e, f);
      auto mz = eve::complex(-e, -f);
      TTS_EQUAL( eve::minus(z), mz );
      TTS_EQUAL( pedantic(eve::minus)(z), mz );
    }
};

TTS_CASE_WITH ( "Check behavior of minus on wide"
              , eve::test::simd::ieee_reals
              , tts::generate(tts::randoms(-1000.0, +1000.0), tts::randoms(-1000.0, +1000.0))
              )
  <typename T>(T const& a0, T const& a1 )
{
  using eve::pedantic;
  using z_t = eve::as_complex_t<T>;
  auto z = z_t(a0, a1);
  auto mz = z_t(-a0, -a1);
  TTS_EQUAL( eve::minus(z), mz );
  TTS_EQUAL( eve::pedantic(eve::minus)(z), mz);
};
