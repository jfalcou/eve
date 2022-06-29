//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"
#include <eve/module/complex.hpp>
#include <complex>

template < typename T >
auto cv(std::complex < T > sc)
{
  return eve::complex<T>(sc.real(), sc.imag());
}

TTS_CASE_WITH( "Check behavior of polar on scalar"
        , tts::bunch<eve::test::scalar::ieee_reals>
        , tts::generate(tts::randoms(0, 100)
                             , tts::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      TTS_ULP_EQUAL( eve::polar(e, f), cv(std::polar(e, f)), 2);
    }
  }
};

TTS_CASE_WITH( "Check behavior of polar on wide"
        , eve::test::simd::ieee_reals
        , tts::generate(tts::randoms(0, 100)
                             , tts::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using z_t = eve::as_complex_t<T>;
  auto [s, c] = eve::sincos(a1);
  z_t z(c, s);
  TTS_ULP_EQUAL( eve::polar(a0,a1), a0*z, 2);
};
