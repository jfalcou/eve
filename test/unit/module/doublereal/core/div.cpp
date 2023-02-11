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

TTS_CASE_WITH( "Check behavior of div on scalar"
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
      auto z1 = doublereal_t(e, f);
      auto z2 = doublereal_t(f, e);
      auto am =  z1/z2;
      TTS_EQUAL ( tts::uptype(eve::div(z1, z2)), tts::uptype(am));
    }
  }
  TTS_ULP_EQUAL(eve::div(eve::inf(eve::as<doublereal_t>()), eve::inf(eve::as<doublereal_t>())), eve::nan(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::div(eve::minf(eve::as<doublereal_t>()), eve::inf(eve::as<doublereal_t>())), eve::nan(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::div(eve::nan(eve::as<doublereal_t>()), eve::inf(eve::as<doublereal_t>())), eve::nan(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::div(eve::minf(eve::as<doublereal_t>()), eve::nan(eve::as<doublereal_t>())), eve::nan(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::div(eve::inf(eve::as<doublereal_t>()), eve::zero(eve::as<doublereal_t>())), eve::inf(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::div(eve::minf(eve::as<doublereal_t>()), eve::zero(eve::as<doublereal_t>())), eve::minf(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::div(eve::inf(eve::as<doublereal_t>()), eve::mzero(eve::as<doublereal_t>())), eve::minf(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::div(eve::minf(eve::as<doublereal_t>()), eve::mzero(eve::as<doublereal_t>())), eve::inf(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::div(eve::zero(eve::as<doublereal_t>()) ,eve::inf(eve::as<doublereal_t>())),   eve::zero(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::div(eve::zero(eve::as<doublereal_t>()) ,eve::minf(eve::as<doublereal_t>())),  eve::mzero(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::div(eve::mzero(eve::as<doublereal_t>()),eve::inf(eve::as<doublereal_t>())),   eve::mzero(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::div(eve::mzero(eve::as<doublereal_t>()),eve::minf(eve::as<doublereal_t>())),  eve::zero(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::div(eve::inf(eve::as<doublereal_t>()), eve::one(eve::as<doublereal_t>())), eve::inf(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::div(eve::minf(eve::as<doublereal_t>()), eve::one(eve::as<doublereal_t>())), eve::minf(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::div(eve::one(eve::as<doublereal_t>()) ,eve::inf(eve::as<doublereal_t>())),   eve::zero(eve::as<doublereal_t>()), 0.5);
  TTS_ULP_EQUAL(eve::div(eve::one(eve::as<doublereal_t>()) ,eve::minf(eve::as<doublereal_t>())),  eve::mzero(eve::as<doublereal_t>()), 0.5);
 };

TTS_CASE_WITH( "Check behavior of div on wide"
             , eve::test::simd::ieee_reals
             , tts::generate ( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             )
             )
  <typename T>(T const& a0, T const& a1 )
{

  auto z1 = make_doublereal(a0,a1);
  auto z2 = make_doublereal(a1,a0);
  auto amz = decltype(z1)(eve::detail::map(eve::div, z1, z2));
  TTS_EQUAL ( eve::div(z1, z2), amz);
};
