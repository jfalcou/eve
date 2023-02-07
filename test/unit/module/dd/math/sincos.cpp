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


TTS_CASE_WITH( "Check behavior of sincos on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-1.544*20, 1.54*20)
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
      auto z = eve::dd<e_t>(e, f);
      auto s = eve::sin(z);
      auto c = eve::cos(z);
      auto[ss, cc] = eve::sincos(z);
      TTS_ULP_EQUAL(c, cc , 0.5);
      TTS_ULP_EQUAL(s, ss , 0.5);
    }
  }
};

TTS_CASE_WITH( "Check behavior of sincos on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-1.544, 1.54)
                             , tts::randoms(-0.001, +0.001)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  if constexpr(sizeof(e_t) == 8)
  {
    auto z = make_dd(a0,a1);
    auto sz = decltype(z)(eve::detail::map(eve::sin, z));
    auto cz = decltype(z)(eve::detail::map(eve::cos, z));
    auto [ssz, ccz] = eve::sincos(z);
    TTS_ULP_EQUAL(cz, ccz, 0.5);
    TTS_ULP_EQUAL(sz, ssz, 0.5);
  }
};
