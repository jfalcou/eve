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

TTS_CASE_WITH( "Check behavior of negabsmin on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using doublereal_t = eve::doublereal<e_t>;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto z1 = doublereal_t(e, f/1000);
      auto z2 = doublereal_t(f, e/1000);
      auto am =  -bm::abs(tts::uptype(z1) <  tts::uptype(z2) ? tts::uptype(z1) : tts::uptype(z2));
      TTS_EQUAL ( tts::uptype(eve::negabsmin(z1, z2)), am);
    }
  }
};

TTS_CASE_WITH( "Check behavior of negabsmin on wide"
        , eve::test::simd::ieee_reals
        , tts::generate ( tts::randoms(-10, 10)
                              , tts::randoms(-10, 10)
                              )
        )
  <typename T>(T const& a0, T const& a1 )
{
  auto z1 = make_doublereal(a0,a1/1000);
  auto z2 = make_doublereal(a1,a0/1000);
  auto amz = decltype(z1)(eve::detail::map(eve::negabsmin, z1, z2));
  TTS_EQUAL ( eve::negabsmin(z1, z2), amz);
};
