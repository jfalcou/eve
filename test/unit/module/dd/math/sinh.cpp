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

auto maxi = []<typename T>(eve::as<T> const&)
{
  using v_t = eve::element_type_t<T>;
  v_t ovl   = eve::Ieee_constant<v_t, 0x42B0C0A4U, 0x40862E42FEFA39EFULL>()/2; // 88.376251220703125f,
                                                                             // 709.782712893384
  return T(ovl);
};

auto mini = []<typename T>(eve::as<T> const& tgt) { return -maxi(tgt); };


TTS_CASE_WITH( "Check behavior of sinh on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(tts::constant(mini), tts::constant(maxi))
                             , tts::randoms(tts::constant(mini), tts::constant(maxi))
                             )
             )
  <typename T>(T const& a0, T const& a1)
{
  namespace bm = boost::multiprecision;
  using e_t = typename T::value_type;
  using dd_t = eve::dd<e_t>;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto z = eve::dd<e_t>(e, f);
      auto ac = eve::sinh(z);
      auto bmbc = bm::sinh(tts::uptype(z));
      auto bc = tts::to_dd<e_t>(bmbc);
      TTS_ULP_EQUAL(bc, ac, 32);
    }
  }
  TTS_ULP_EQUAL(eve::sinh(eve::inf(eve::as<dd_t>())), eve::inf(eve::as<dd_t>()), 0.5);
  TTS_ULP_EQUAL(eve::sinh(eve::minf(eve::as<dd_t>())), eve::minf(eve::as<dd_t>()), 0.5);
  TTS_ULP_EQUAL(eve::sinh(eve::zero(eve::as<dd_t>())), eve::zero(eve::as<dd_t>()), 0.5);
  TTS_ULP_EQUAL(eve::sinh(eve::mzero(eve::as<dd_t>())), eve::mzero(eve::as<dd_t>()), 0.5);
  TTS_ULP_EQUAL(eve::sinh(eve::nan(eve::as<dd_t>())), eve::nan(eve::as<dd_t>()), 0.5);
};

TTS_CASE_WITH( "Check behavior of sinh on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(tts::constant(mini), tts::constant(maxi))
                             , tts::randoms(tts::constant(mini), tts::constant(maxi))
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
   auto z = make_dd(a0,a1);
    auto az = decltype(z)(eve::detail::map(eve::sinh, z));
    auto cz = eve::sinh(z);
    TTS_ULP_EQUAL(cz, az, 2.5);
};
