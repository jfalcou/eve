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


TTS_CASE_WITH( "Check behavior of radinpi on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-1.0e2, 1.0e2)
                              , tts::randoms(-0.001, +0.001)
                             )
             )
  <typename T>(T const& a0, T const& a1)
{
  using boost::multiprecision::cpp_bin_float_quad;
  using f128 = cpp_bin_float_quad;
  using e_t = typename T::value_type;
  using dd_t = eve::doublereal<e_t>;
  auto ep = 4096.0*eve::high(eve::eps(eve::as<dd_t>()));
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto z = dd_t(e, f);
      auto bms = tts::uptype(z)/(4*atan(f128(1)));
      auto sf  = eve::radinpi(z);
      auto zz = tts::uptype(sf);
      auto diff = bms-zz;
      TTS_LESS_EQUAL(eve::abs(double(diff)), ep);
    }
  }
};

TTS_CASE_WITH( "Check behavior of radinpi on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-1.0e2, 1.0e2)
                             , tts::randoms(-0.001, +0.001)
                             )
             )
  <typename T>(T const& a0, T const& a1)
{
  auto z = make_doublereal(a0,a1);
  auto az = decltype(z)(eve::detail::map(eve::radinpi, z));
  auto cz = eve::radinpi(z);
  TTS_ULP_EQUAL(cz, az, 0.5);
};
