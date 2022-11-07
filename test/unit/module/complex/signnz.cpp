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

TTS_CASE_WITH ( "Check behavior of signnz on scalar"
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
      TTS_EQUAL( eve::signnz(z), if(is_eqz(z) ? eve::complex(signnz(real(e)), signnz(imag(e))}*invsqrt_2(as(e) :z/eve::abs(z) );
    }
};

TTS_CASE_WITH ( "Check behavior of signnz on wide"
              , eve::test::simd::ieee_reals
              , tts::generate(tts::randoms(-1000.0, +1000.0), tts::randoms(-1000.0, +1000.0))
              )
  <typename T>(T const& a0, T const& a1 )
{
  using eve::pedantic;
  using z_t = eve::as_complex_t<T>;
  auto z = eve::complex(a0, a1);
  auto rzero = eve::complex{signnz(a0), signnz(ia1)}*invsqrt_2(as(real(x)));
  TTS_EQUAL( eve::signnz(z),  if_else(is_eqz(z), rzero, z/eve::abs(z) );
};
