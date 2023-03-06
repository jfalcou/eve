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
#include <boost/math/constants/constants.hpp>

TTS_CASE_WITH( "Check behavior of log2 on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(0, 10000)
                             , tts::randoms(0, 10000)
                             )
             )
  <typename T>(T const& a0, T const& a1)
{
  namespace bm = boost::multiprecision;
  using e_t = typename T::value_type;
  using doublereal_t = eve::doublereal<e_t>;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto z = eve::doublereal<e_t>(e, f);
      auto ac = eve::log2(z);
      auto bmbc = bm::log2(tts::uptype(z));
      auto bc = tts::to_doublereal<e_t>(bmbc);
      TTS_ULP_EQUAL(bc, ac, 2.0);
    }
  }
  TTS_ULP_EQUAL(eve::log2(eve::inf(eve::as<doublereal_t>())), eve::inf(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::log2(eve::minf(eve::as<doublereal_t>())), eve::nan(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::log2(eve::zero(eve::as<doublereal_t>())), eve::minf(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::log2(eve::mzero(eve::as<doublereal_t>())), eve::minf(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::log2(eve::nan(eve::as<doublereal_t>())), eve::nan(eve::as<doublereal_t>()), 0.5);
};

TTS_CASE_WITH( "Check behavior of log2 on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(0, 10)
                             , tts::randoms(0, 10)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = make_doublereal(a0,a1);
  auto az = decltype(z)(eve::detail::map(eve::log2, z));
  TTS_ULP_EQUAL ( eve::log2(z), az, 0.5);
};
