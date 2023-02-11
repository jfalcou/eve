//==================================================================================================
/**
  EVE - Expm1ressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include "../measures.hpp"
#include <eve/module/doublereal.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>



TTS_CASE_WITH( "Check behavior of expm1 on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-10, 10)
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
      auto z = doublereal_t(e, f);
      auto ac = eve::expm1(z);
      auto bmbc = bm::expm1(tts::uptype(z));
      auto bc = tts::to_doublereal<e_t>(bmbc);
      TTS_ULP_EQUAL(bc, ac, 2.5);
    }
  }
  TTS_ULP_EQUAL(eve::expm1(eve::inf(eve::as<doublereal_t>())), eve::inf(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::expm1(eve::minf(eve::as<doublereal_t>())), eve::mone(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::expm1(eve::zero(eve::as<doublereal_t>())), eve::zero(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::expm1(eve::mzero(eve::as<doublereal_t>())), eve::zero(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::expm1(eve::nan(eve::as<doublereal_t>())), eve::nan(eve::as<doublereal_t>()), 0.5);

};

TTS_CASE_WITH( "Check behavior of expm1 on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-1, 1)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = make_doublereal(a0,a1);
  auto az = decltype(z)(eve::detail::map(eve::expm1, z));
  TTS_ULP_EQUAL ( eve::expm1(z), az, 2.5);
};
