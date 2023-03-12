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


TTS_CASE_WITH( "Check behavior of tan on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-1.54/2, 1.54/2)
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
      auto bmbc = bm::tan(tts::uptype(z));
      auto bc = tts::to_doublereal<e_t>(bmbc);
      auto s  = eve::quarter_circle(eve::tan)(z);
      TTS_ULP_EQUAL(bc, s , 1.0);
    }
  }
};

TTS_CASE_WITH( "Check behavior of tan on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-1.544/2, 1.54/2)
                             , tts::randoms(-0.001, +0.001)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = make_doublereal(a0,a1);
  auto az = decltype(z)(eve::detail::map(eve::quarter_circle(eve::tan), z));
  auto cz = eve::quarter_circle(eve::tan)(z);
  TTS_ULP_EQUAL(cz, az, 0.5);
};
