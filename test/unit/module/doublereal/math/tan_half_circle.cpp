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
             , tts::generate ( tts::randoms(-1.54, 1.54)
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
//      auto bmbcs = bm::sin(tts::uptype(z));
//      auto bmbcc = bm::cos(tts::uptype(z));
        auto bmbc  = bm::tan(tts::uptype(z));
      auto bc = tts::to_doublereal<e_t>(bmbc);
//      auto bc = tts::to_doublereal<e_t>(bmbcs)/tts::to_doublereal<e_t>(bmbcc);
      auto soc = eve::half_circle(eve::sin)(z)/eve::half_circle(eve::cos)(z);
      auto t  = eve::half_circle(eve::tan)(z);
      TTS_ULP_EQUAL(soc, t , 1.0);
      TTS_ULP_EQUAL(bc , t , 1.0);
//      TTS_ULP_EQUAL(tts::to_doublereal<e_t>(bmbcs), eve::half_circle(eve::sin)(z), 1);
//      TTS_ULP_EQUAL(tts::to_doublereal<e_t>(bmbcc), eve::half_circle(eve::cos)(z), 1);
    }
  }
};

TTS_CASE_WITH( "Check behavior of tan on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-1.54, 1.54)
                             , tts::randoms(-0.001, +0.001)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = make_doublereal(a0,a1);
  auto az = decltype(z)(eve::detail::map(eve::half_circle(eve::tan), z));
  auto cz = eve::half_circle(eve::tan)(z);
  TTS_ULP_EQUAL(cz, az, 0.5);
};
