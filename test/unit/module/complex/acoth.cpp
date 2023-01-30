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

TTS_CASE_WITH ( "Check behavior of acoth on scalar"
              , tts::bunch<eve::test::scalar::ieee_reals>
              , tts::generate( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             )
              )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t =  typename T::value_type;
  for(auto e : a0)
  {
    TTS_ULP_EQUAL(eve::domain::complex(eve::acoth)(e), eve::acoth(eve::complex<e_t>(e, e_t(0))), 1.0);
    TTS_ULP_EQUAL(eve::domain::complex(eve::acoth)(e), eve::domain::complex(eve::acoth)(eve::complex<e_t>(e, e_t(0))), 1.0);
    for(auto f : a1)
    {
      auto z = eve::complex<e_t>(e, f);
      TTS_ULP_EQUAL(eve::acoth(z),  eve::atanh(eve::rec(z)), 2.0);
    }
  }
};

TTS_CASE_WITH( "Check behavior of acoth on wide"
             , eve::test::simd::ieee_reals
             , tts::generate( tts::randoms(-10, 10)
                            , tts::randoms(-10, 10))
             )
  <typename T>(T const& a0, T const&  a1)
{
  using z_t = eve::as_complex_t<T>;
  auto z = z_t{a0, a1};
  TTS_ULP_EQUAL(eve::acoth(z), eve::atanh(eve::rec(z)), 2.0);
  TTS_RELATIVE_EQUAL(eve::domain::complex(eve::acoth)(a0), eve::acoth(z_t(a0, eve::zero(eve::as(a0)))), 5.0e-3);
  TTS_RELATIVE_EQUAL(eve::domain::complex(eve::acoth)(a0), eve::domain::complex(eve::acoth)(z_t(a0, eve::zero(eve::as(a0)))), 5.0e-3);
};
