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

TTS_CASE_WITH( "Check behavior of atan2pi on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using doublereal_t = eve::doublereal<e_t>;
  using boost::multiprecision::cpp_bin_float_quad;
  using f128 = cpp_bin_float_quad;
  auto invpi = 1/(4*bm::atan(f128(1)));
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto z1 = doublereal_t(e, f);
      auto z2 = doublereal_t(f, e);
      doublereal_t am =  tts::to_doublereal<e_t>(invpi*bm::atan2(tts::uptype(z1), tts::uptype(z2)));
      TTS_ULP_EQUAL ( eve::atan2pi(z1, z2), am, 0.5);
    }
  }
};

TTS_CASE_WITH( "Check behavior of atan2pi on wide"
        , eve::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, 10)
                        , tts::randoms(-10, 10)
                        )
        )
  <typename T>(T const& a0, T const& a1 )
{
  auto z1 = make_doublereal(a0,a1);
  auto z2 = make_doublereal(a1,a0);
  auto amz = decltype(z1)(eve::detail::map(eve::atan2pi, z1, z2));
  TTS_ULP_EQUAL ( eve::atan2pi(z1, z2), amz, 0.5);
};
