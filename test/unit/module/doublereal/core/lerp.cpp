//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include "../measures.hpp"
#include <eve/module/doublereal.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>

TTS_CASE_WITH( "Check behavior of lerp on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             , tts::randoms(0, 1)
                             )
             )
  <typename T>(T const& a0, T const& a1, T const& a3 )
{
  using e_t = typename T::value_type;
  using doublereal_t = eve::doublereal<e_t>;
  for(auto tt : a3)
  {
    auto t = doublereal_t(tt, e_t(0));
    for(auto e : a0)
    {
      for(auto f : a1)
      {
        auto z1 = doublereal_t(e, f/1000);
        auto z2 = doublereal_t(f, e/1000);
        auto lp = [](auto a,  auto b,  auto t){ return a+(b-a)*t; };
        auto r = eve::lerp(z1, z2, t);
//        std::cout << "r " << r << std::endl;
        auto ref = tts::to_doublereal<e_t>(lp(tts::uptype(z1), tts::uptype(z2), tts::uptype(t)));
//        std::cout << "ref " << ref << std::endl;
        TTS_ULP_EQUAL ( r, ref, 2);
      }
    }
  }
};

TTS_CASE_WITH( "Check behavior of lerp on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             , tts::randoms(0, 0.5)
                             , tts::randoms(0, 0.5)
                             )
             )
  <typename T>(T const& a0, T const& a1, T const & a2, T const & a3)
{

  auto z1 = make_doublereal(a0,a1/1000);
  auto z2 = make_doublereal(a1,a0/1000);
  auto t = make_doublereal(a2, a3);
  auto amz = decltype(z1)(eve::detail::map(eve::lerp, z1, z2, t));
  TTS_EQUAL ( eve::lerp(z1, z2, t), amz);
};
