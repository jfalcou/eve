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

TTS_CASE_WITH( "Check behavior of sqr on scalar"
        , tts::bunch<eve::test::scalar::ieee_reals>
        , tts::generate(tts::randoms(-1000.0, 1000.0)
                             , tts::randoms(-1000.0, 1000.0))
        )
<typename T>(T const& a0,  T const & a1)
{
  using e_t = typename T::value_type;
  using c_t = eve::complex<e_t>;
  for(auto e : a0)
  {
    TTS_EQUAL( eve::sqr(e), e*e );
    for(auto f : a1)
    {
      auto z1= c_t(e, f);
      TTS_ULP_EQUAL( eve::sqr(z1), z1*z1, 2.0);
    }
  }
};


TTS_CASE_WITH( "Check behavior of sqr on wide"
        , eve::test::simd::ieee_reals
        , tts::generate(tts::randoms(-1000.0, 1000.0)
                             , tts::randoms(-1000.0, 1000.0))
        )
<typename T>(T const& a0, T const & a1 )
{
  using e_t = typename T::value_type;
  using z_t = eve::wide<eve::complex<e_t>, typename T::cardinal_type>;

  TTS_ULP_EQUAL( eve::sqr(a0), a0*a0, 2.0);
  TTS_ULP_EQUAL( eve::sqr(z_t{a0,a1}), (z_t{a0,a1}*z_t{a0,a1}), 2.0);
};
