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




TTS_CASE_WITH( "Check behavior of atanpi on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-10, 10)
                              , tts::randoms(-0.0001, 0.0001)
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
      auto ac = eve::atanpi(z);
      auto bmbc = bm::atan(tts::uptype(z))*invpi;;
      auto bc = tts::to_doublereal<e_t>(bmbc);
      TTS_ULP_EQUAL(bc, ac, 16);
    }
  }
};

TTS_CASE_WITH( "Check behavior of atanpi on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-1, 1)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = make_doublereal(a0,a1);
  auto az = decltype(z)(eve::detail::map(eve::atanpi, z));
  auto cz = eve::atanpi(z);
  TTS_ULP_EQUAL(cz, az, 0.5);
};
