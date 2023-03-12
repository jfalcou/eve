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

TTS_CASE_WITH( "Check behavior of acot on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-10000, 10000)
                              , tts::randoms(-0.0001, 0.0001)
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
      auto ac = eve::acot(z);
      auto bmbc = bm::atan(tts::uptype(eve::rec(z)));
      auto bc = tts::to_doublereal<e_t>(bmbc);
      TTS_RELATIVE_EQUAL(bc, ac, eve::eps(eve::as(e)));
    }
  }
};

TTS_CASE_WITH( "Check behavior of acot on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-1, 1)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = eve::underlying_type_t<T>;
  auto z = make_doublereal(a0,a1);
  auto az = decltype(z)(eve::detail::map(eve::acot, z));
  auto cz = eve::acot(z);
  TTS_RELATIVE_EQUAL(cz, az, eve::eps(eve::as<e_t>()));
};
