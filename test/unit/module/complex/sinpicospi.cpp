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
#include <complex>


TTS_CASE_WITH( "Check behavior of sinpicospi on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             ,tts::generate(tts::randoms(-10, 10)
                           ,tts::randoms(-10, 10))
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using c_t = eve::complex<e_t>;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      c_t z(e, f);
      auto [s, c] = eve::sinpicospi(z);
      TTS_ULP_EQUAL(s, eve::sinpi(z), 2.0);
      TTS_ULP_EQUAL(c, eve::cospi(z), 2.0);
    }
  }
};

TTS_CASE_WITH( "Check behavior of sinpicospi on wide"
             , eve::test::simd::ieee_reals
             ,tts::generate(tts::randoms(-10, 10)
                           ,tts::randoms(-10, 10))
             )
  <typename T>(T const& a0, T const& a1 )
{
  using z_t = eve::as_complex_t<T>;
  z_t z = z_t{a0,a1};
  auto [s, c] = eve::sinpicospi(z);
  TTS_ULP_EQUAL(s, eve::sinpi(z), 2);
  TTS_ULP_EQUAL(c, eve::cospi(z), 2);
};
