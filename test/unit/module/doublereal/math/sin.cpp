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


TTS_CASE_WITH( "Check behavior of sin on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-1.544*20, 1.54*20)
                              , tts::randoms(-0.001, +0.001)
                             )
             )
  <typename T>(T const& a0, T const& a1)
{
  namespace bm = boost::multiprecision;
  using e_t = typename T::value_type;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto z = eve::doublereal<e_t>(e, f);
      std::cout << "e,  f " << e << " --- " << f << std::endl;
      if constexpr(sizeof(e_t) == 8)
      {
        auto bmbc = bm::sin(tts::uptype(z));
        auto bc = tts::to_doublereal<e_t>(bmbc);
        auto s  = eve::sin(z);
        TTS_ULP_EQUAL(bc, s , 0.5);
      }
    }
  }
};

TTS_CASE_WITH( "Check behavior of sin on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-1.544, 1.54)
                             , tts::randoms(-0.001, +0.001)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  if constexpr(sizeof(e_t) == 8)
  {
    auto z = make_doublereal(a0,a1);
    auto az = decltype(z)(eve::detail::map(eve::sin, z));
    auto cz = eve::sin(z);
    TTS_EQUAL ( cz, az);
    TTS_ULP_EQUAL(cz, az, 0.5);
  }
};
