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
#include <boost/multiprecision/cpp_bin_float.hpp>

TTS_CASE_WITH( "Check behavior of exp on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-100, 100)
                             , tts::randoms(-1, 1)
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
      auto ac = eve::exp(z);
      auto bmbc = bm::exp(tts::uptype(z));
      auto bc = tts::to_doublereal<e_t>(bmbc);
      TTS_ULP_EQUAL(bc, ac, 10.0);
    }
  }
  TTS_ULP_EQUAL(eve::exp(eve::inf(eve::as<doublereal_t>())), eve::inf(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::exp(eve::minf(eve::as<doublereal_t>())), eve::zero(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::exp(eve::zero(eve::as<doublereal_t>())), eve::one(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::exp(eve::mzero(eve::as<doublereal_t>())), eve::one(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::exp(eve::nan(eve::as<doublereal_t>())), eve::nan(eve::as<doublereal_t>()), 0.5);
};

TTS_CASE_WITH( "Check behavior of exp on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = make_doublereal(a0,a1);
  auto az = decltype(z)(eve::detail::map(eve::exp, z));
  TTS_ULP_EQUAL ( eve::exp(z), az, 0.5);
};
