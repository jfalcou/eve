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
  using u_t =  eve::underlying_type_t<T>;
  return (eve::maxlog(eve::as<u_t>())-eve::log_2(eve::as<u_t>()))/8;
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
  using u_t = typename T::value_type;
  std::cout << "mini" << mini(eve::as<u_t>()) << std::endl;
  std::cout << "maxi" << maxi(eve::as<u_t>()) << std::endl;
  namespace bm = boost::multiprecision;
  using e_t = typename T::value_type;
  using doublereal_t = eve::doublereal<e_t>;
  auto ep = (sizeof(e_t) == 4) ? 1.0e-10 : 1.0e-20;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto z = eve::doublereal<e_t>(e, f);
      auto ac = tts::uptype(eve::sinh(z));
      auto bmbc = bm::sinh(tts::uptype(z));
      auto diff = bmbc-ac;
      TTS_LESS_EQUAL(eve::abs(double(diff/ac)), ep);
    }
  }
  TTS_ULP_EQUAL(eve::sinh(eve::inf(eve::as<doublereal_t>())), eve::inf(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::sinh(eve::minf(eve::as<doublereal_t>())), eve::minf(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::sinh(eve::zero(eve::as<doublereal_t>())), eve::zero(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::sinh(eve::mzero(eve::as<doublereal_t>())), eve::zero(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::sinh(eve::nan(eve::as<doublereal_t>())), eve::nan(eve::as<doublereal_t>()), 0.5);

 };

TTS_CASE_WITH( "Check behavior of sinh on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(tts::constant(mini), tts::constant(maxi))
                             , tts::randoms(tts::constant(mini), tts::constant(maxi))
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = make_doublereal(a0,a1);
  auto az = decltype(z)(eve::detail::map(eve::sinh, z));
  auto cz = eve::sinh(z);
  TTS_ULP_EQUAL(cz, az, 2.5);
};
