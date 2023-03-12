//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include <eve/module/doublereal.hpp>

TTS_CASE_WITH( "Check behavior of frexp on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
     auto x = eve::doublereal<e_t>(e, f);
     auto [m, n] = eve::frexp(x);

     TTS_EQUAL (x, m*pow(2, int(n)));
    }
  }
};

TTS_CASE_WITH( "Check behavior of frexp on wide"
        , eve::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, 10)
                              , tts::randoms(-10, 10)
                              )
        )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = make_doublereal(a0,a1);
  using r_t =  std::decay_t<decltype(eve::low(z))>;
  auto [m, n] = eve::frexp(z);
  TTS_EQUAL (z, m*eve::pow(r_t(2), eve::int32(n)));
};
