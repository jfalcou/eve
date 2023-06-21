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

TTS_CASE_WITH( "Check behavior of sqr_abs on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate(tts::randoms(-1000.0, 1000.0)
                            , tts::randoms(-1000.0, 1000.0)
                            , tts::randoms(-1000.0, 1000.0)
                            , tts::randoms(-1000.0, 1000.0)
                            )
             )
  <typename T>(T const& a0,  T const & a1, T const& a2, T const& a3)
{
  using e_t = typename T::value_type;
  using q_t = eve::quaternion<e_t>;
  for(auto e : a0)
  {
    TTS_EQUAL( eve::sqr_abs(e), eve::sqr(eve::abs(e)) );
    for(auto f : a1)
    {
      for(auto g : a2)
      {
        for(auto h : a3)
        {
          auto z1= q_t(e, f, g, h);
          TTS_ULP_EQUAL( eve::sqr_abs(z1), eve::sqr(eve::abs(z1)), 2.0);
        }
      }
    }
  }
};


TTS_CASE_WITH( "Check behavior of sqr_abs on wide"
             , eve::test::simd::ieee_reals
             , tts::generate(tts::randoms(-1000.0, 1000.0)
                            , tts::randoms(-1000.0, 1000.0)
                            , tts::randoms(-1000.0, 1000.0)
                            , tts::randoms(-1000.0, 1000.0))
             )
  <typename T>(T const& a0, T const & a1, T const& a2, T const& a3 )
{
  using e_t = typename T::value_type;
  using z_t = eve::wide<eve::quaternion<e_t>, typename T::cardinal_type>;

  z_t z{a0,a1, a2, a3};
  TTS_ULP_EQUAL( eve::sqr_abs(z), eve::sqr(eve::abs(z)), 2.0);
//   TTS_ULP_EQUAL( eve::pedantic(eve::sqr_abs)(a0), eve::sqr(eve::abs(a0)), 2.0);
//   TTS_ULP_EQUAL( eve::pedantic(eve::sqr_abs)(z), eve::sqr(eve::abs(z)), 6.0);
};
