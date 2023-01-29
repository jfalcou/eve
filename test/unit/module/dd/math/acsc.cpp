//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include "../measures.hpp"
#include <eve/module/dd.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>


TTS_CASE_WITH( "Check behavior of acsc on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(1, 10)
                              , tts::randoms(0, 1)
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
      auto z = eve::dd<e_t>(e, f);
      auto ac = eve::acsc(z);
      auto bmbc = bm::asin(tts::uptype(eve::rec(z)));
      eve::dd<e_t> bc(bmbc);
      TTS_ULP_EQUAL(bc, ac, 0.5);
    }
  }
};

TTS_CASE_WITH( "Check behavior of acsc on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(1, 10)
                             , tts::randoms(0, 1)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = make_dd(a0,a1);
  auto az = decltype(z)(eve::detail::map(eve::acsc, z));
  auto cz = eve::acsc(z);
  TTS_EQUAL ( cz, az);
  TTS_ULP_EQUAL(cz, az, 0.5);
};
