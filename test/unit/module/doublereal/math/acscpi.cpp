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

TTS_CASE_WITH( "Check behavior of acscpi on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(0, 1000)
                              , tts::randoms(0, 0.1)
                             )
             )
  <typename T>(T const& a0, T const& a1)
{
  using boost::multiprecision::cpp_bin_float_quad;
  using f128 = cpp_bin_float_quad;
  auto invpi = 1/(4*bm::atan(f128(1)));
  using e_t = typename T::value_type;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto z = eve::doublereal<e_t>(e, f);
      auto ac = eve::acscpi(z);
      auto bmbc = bm::asin(1/tts::uptype(z))*invpi;
      auto bc = tts::to_doublereal<e_t>(bmbc);
      TTS_ULP_EQUAL(bc, ac, 1.0);
    }
  }
};

TTS_CASE_WITH( "Check behavior of acscpi on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(1, 1000)
                             , tts::randoms(0, 0.1)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = make_doublereal(a0,a1);
  auto az = decltype(z)(eve::detail::map(eve::acscpi, z));
  auto cz = eve::acscpi(z);
  TTS_ULP_EQUAL(cz, az, 1.0);
};
