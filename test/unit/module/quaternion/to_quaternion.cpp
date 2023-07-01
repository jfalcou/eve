//==================================================================================================
/**
  EVE - Logressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"
#include <eve/detail/meta.hpp>
#include <eve/module/complex.hpp>
#include <eve/module/quaternion.hpp>
#include <boost/math/quaternion.hpp>

TTS_CASE_WITH( "Check behavior of to_quaternion on scalar"
        , tts::bunch<eve::test::scalar::ieee_reals>
             , tts::generate( tts::randoms(-10, 10)
                            , tts::randoms(-10, 10)
                            , tts::randoms(-10, 10)
                            , tts::randoms(-10, 10)
                            )
        )
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3)
{
  using e_t = typename T::value_type;
  using eq_t = eve::quaternion<e_t>;
  using ec_t = eve::complex<e_t>;
  for(size_t i = 0; i < a0.size(); ++i)
  {
    eq_t z  = eq_t(a0[i]);
    auto tz = eve::to_quaternion(a0[i]);             //from scalar
    TTS_EQUAL(z, tz);
    eq_t z2  = eq_t(a0[i], a1[i], a2[i], a3[i]);
    auto tz3 = eve::to_quaternion(z2);               //from quaternion
    TTS_EQUAL(z2, tz3);
    ec_t c1  = ec_t(a0[i], a1[i]);
    eq_t z1  = eq_t(a0[i], a1[i], 0, 0);
    auto tz1 = eve::to_quaternion(c1);
    TTS_EQUAL(z1, tz1);
    ec_t c2  = ec_t(a2[i], a3[i]);
    auto tz2 = eve::to_quaternion(c1, c2);
    TTS_EQUAL(z2, tz2);
  }
};

TTS_CASE_WITH( "Check behavior of to_quaternion on wide"
        , eve::test::simd::ieee_reals
             , tts::generate( tts::randoms(-10, 10)
                            , tts::randoms(-10, 10)
                            , tts::randoms(-10, 10)
                            , tts::randoms(-10, 10)
                            )
        )
  <typename T>(T const& a0, T const& , T const& , T const& )
{
// using e_t = eve::element_type_t<T>;
  using eq_t = eve::as_quaternion<T>;
//  using ec_t = eve::as_complex<T>;
//  auto zero = eve::zero(eve::as(a0));
  eq_t z; //(a0, zero, zero, zero);
  eve::real(z) = a0;
  auto tz = eve::to_quaternion(a0);
  TTS_EQUAL(z, tz);
//  ec_t c1= eve::to_complex(a0, a1);
//   eq_t z1  = eve::as_quaternion<T>(a0, a1, zero, zero);
//    auto tz1 = eve::to_quaternion(c1);
//    TTS_EQUAL(tz1, tz1);
//   ec_t c2  = eve::as_complex<T>(a2, a3);
//   eq_t z2  = eve::as_quaternion<T>(a0, a1, a2, a3);
//   auto tz2 = eve::to_quaternion(c1, c2);
//   TTS_EQUAL(z2, tz2);
//   auto tz3 = eve::to_quaternion(z2);
//   TTS_EQUAL(z2, tz3);
};
