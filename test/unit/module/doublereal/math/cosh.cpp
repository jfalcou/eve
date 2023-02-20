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
  using v_t = eve::element_type_t<T>;
  v_t ovl   = eve::Ieee_constant<v_t, 0x42B0C0A4U, 0x40862E42FEFA39EFULL>()/10; // 88.376251220703125f,
                                                                             // 709.782712893384
  return T(ovl);
};

auto mini = []<typename T>(eve::as<T> const& tgt) { return -maxi(tgt); };


TTS_CASE_WITH( "Check behavior of cosh on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate ( tts::randoms(-30, 30)
                             , tts::randoms(-30, 30)
                             )
             )
  <typename T>(T const& a0, T const& a1)
{
  namespace bm = boost::multiprecision;
  using e_t = typename T::value_type;
  using doublereal_t = eve::doublereal<e_t>;
  auto ep = (sizeof(e_t) == 4) ? 1.0e-10 : 1.0e-28;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto z = eve::doublereal<e_t>(e, f);
//       std::cout << "z " << z << std::endl;
//       std::cout << "uz" << tts::uptype(z) << std::endl;
      auto ac = tts::uptype(eve::cosh(z));
      auto bmbc = bm::cosh(tts::uptype(z));
      auto diff = bmbc-ac;
      TTS_LESS_EQUAL(eve::abs(double(diff)/double(ac)), ep);
//       std::cout << "bmbc " << bmbc << std::endl;
//       auto bc = tts::to_doublereal<e_t>(bmbc);
//      TTS_ULP_EQUAL(bc, ac, 100);
    }
  }
  TTS_ULP_EQUAL(eve::cosh(eve::inf(eve::as<doublereal_t>())), eve::inf(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::cosh(eve::minf(eve::as<doublereal_t>())), eve::inf(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::cosh(eve::zero(eve::as<doublereal_t>())), eve::one(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::cosh(eve::mzero(eve::as<doublereal_t>())), eve::one(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::cosh(eve::nan(eve::as<doublereal_t>())), eve::nan(eve::as<doublereal_t>()), 0.5);
 };

TTS_CASE_WITH( "Check behavior of cosh on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(tts::constant(mini), tts::constant(maxi))
                             , tts::randoms(tts::constant(mini), tts::constant(maxi))
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{
  auto z = make_doublereal(a0,a1);
  auto az = decltype(z)(eve::detail::map(eve::cosh, z));
  auto cz = eve::cosh(z);
  TTS_EQUAL ( cz, az);
  TTS_ULP_EQUAL(cz, az, 2.5);
};
