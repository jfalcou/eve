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

TTS_CASE_WITH ( "Check behavior of gd on scalar"
              , tts::bunch<eve::test::scalar::ieee_reals>
              , tts::generate(tts::randoms(-10.0, +10.0)
                             , tts::randoms(-10.0, +10.0))
              )
<typename T>(T const& a0, T const& a1 )
{
  for(auto e : a0)
    for(auto f : a1)
    {
      auto z = eve::complex(e, f);
      TTS_ULP_EQUAL( eve::gd(z), 2*eve::atan(eve::tanh(eve::half(eve::as(e))*z)), 700.0);
    }
};

TTS_CASE_WITH ( "Check behavior of gd on wide"
              , eve::test::simd::ieee_reals
              , tts::generate(tts::randoms(-10, +10.0)
                             , tts::randoms(-10.0, +10.0))
              )
<typename T>(T const& a0, T const& a1 )
{
  using z_t = eve::as_complex_t<T>;
  auto z = z_t{a0,a1};
  TTS_ULP_EQUAL( eve::gd(z), 2*eve::atan(eve::tanh(eve::half(eve::as(a0))*z)), 100.0);
};
