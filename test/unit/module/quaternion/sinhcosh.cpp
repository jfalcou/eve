//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"
#include <eve/module/quaternion.hpp>

TTS_CASE_WITH( "Check behavior of sinhcoshon scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             ,tts::generate(tts::randoms(-10, 10)
                           ,tts::randoms(-10, 10))
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  auto tol = 2.0*eve::eps(eve::as<e_t>());
  using c_t = eve::quaternion<e_t>;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      c_t z(e, f, e, f);
      auto [s, c] = eve::sinhcosh(z);
      TTS_RELATIVE_EQUAL(s, eve::sinh(z), tol);
      TTS_RELATIVE_EQUAL(c, eve::cosh(z), tol);
    }
  }
};

TTS_CASE_WITH( "Check behavior of sinhcoshon wide"
             , eve::test::simd::ieee_reals
             ,tts::generate(tts::randoms(-10, 10)
                           ,tts::randoms(-10, 10))
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = eve::element_type_t<T>;
  auto tol = 2.0*eve::eps(eve::as<e_t>());
  using z_t = eve::as_quaternion_t<T>;
  z_t z = z_t{a0,a1};
  auto [s, c] = eve::sinhcosh(z);
  TTS_RELATIVE_EQUAL(s, eve::sinh(z), tol);
  TTS_RELATIVE_EQUAL(c, eve::cosh(z), tol);
};
