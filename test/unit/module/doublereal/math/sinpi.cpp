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

auto maxi = []<typename T>(eve::as<T> const&)
{
  using u_t = eve::underlying_type_t<T>;
  return (sizeof(u_t) == 4) ? 1.0e3 : 1.0e15;
};

auto mini = []<typename T>(eve::as<T> const& tgt) { return -maxi(tgt); };


TTS_CASE_WITH( "Check behavior of sin on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(tts::constant(mini), tts::constant(maxi))
                             , tts::randoms(tts::constant(mini), tts::constant(maxi))
                             )
             )
  <typename T>(T const& a0, T const& a1)
{
  namespace bm = boost::multiprecision;
  using e_t = typename T::value_type;
  using dd_t = eve::doublereal<e_t>;
  auto pi = bm::atan(tts::uptype(eve::one(eve::as<dd_t>())))*4;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto z = dd_t(e, f);
      auto sf  = eve::sinpi(z);
      auto s   = tts::to_doublereal<e_t>((bm::sin)(tts::uptype(z)*pi));
      TTS_ULP_EQUAL(sf, s , 16)<< std::setprecision(40) << tts::uptype(z) << '\n';
    }
  }
};

TTS_CASE_WITH( "Check behavior of sin on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-1.0e15, 1.0e15)
                             , tts::randoms(-0.001, +0.001)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = make_doublereal(a0,a1);
  auto az = decltype(z)(eve::detail::map(eve::sinpi, z));
  auto cz = eve::sinpi(z);
  TTS_ULP_EQUAL(cz, az, 0.5);
};
