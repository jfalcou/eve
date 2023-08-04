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

TTS_CASE_WITH( "Check behavior of csc on scalar"
             , tts::bunch<eve::test::scalar::ieee_reals>
             ,tts::generate(tts::randoms(0.5, 10)
                           ,tts::randoms(0.5, 10))
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  auto tol = 2000.0*eve::eps(eve::as<e_t>());
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      auto z = eve::quaternion<e_t>(e, f, e, f);
      TTS_RELATIVE_EQUAL(eve::csc(z),  eve::rec(eve::sin(z)), tol);
  }
}
};

TTS_CASE_WITH( "Check behavior of csc on wide"
             , eve::test::simd::ieee_reals
             ,tts::generate(tts::randoms(-10, 10)
                           ,tts::randoms(-10, 10))
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = eve::element_type_t<T>;
  auto tol = 2000.0*eve::eps(eve::as<e_t>());
  using z_t = eve::as_quaternion_t<T>;
  auto z = z_t{a0,a1,a0,a1};
  TTS_RELATIVE_EQUAL(eve::csc(z), eve::rec(eve::sin(z)), tol);
};
