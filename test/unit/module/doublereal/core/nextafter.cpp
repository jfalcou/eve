//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include <eve/module/doublereal.hpp>

TTS_CASE_WITH( "Check behavior of nextafter on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             )
             )
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  std::cout << "icitte" << std::endl;
  using e_t = typename T::value_type;
  using doublereal_t = eve::doublereal<e_t>;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto z1 = doublereal_t(e, f);
      for(auto g : a2)
      {
        for(auto h : a3)
        {
          auto z2 = doublereal_t(g, h);
          auto na = (z1 < z2) ? eve::next(z1) : ((z1 >  z2) ? eve::prev(z1) : z1);
          TTS_EQUAL ( eve::nextafter(z1, z2), na);
        }
      }
    }
  }
};

TTS_CASE_WITH( "Check behavior of nextafter on wide"
        , eve::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, 10)
                        , tts::randoms(-10, 10)
                        , tts::randoms(-10, 10)
                        , tts::randoms(-10, 10)                              )
             )
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
  auto z1 = make_doublereal(a0,a1);
  auto z2 = make_doublereal(a2,a3);
  auto na = eve::if_else(z1 < z2, eve::next(z1), eve::if_else(z1 >  z2, eve::prev(z1), z1));
  TTS_EQUAL ( eve::nextafter(z1, z2), na);
};
