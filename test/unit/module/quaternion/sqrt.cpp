//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"
#include <eve/detail/meta.hpp>
#include <eve/module/core.hpp>
#include <eve/module/quaternion.hpp>

TTS_CASE_WITH ( "Check behavior of sqr on scalar"
              , tts::bunch<eve::test::scalar::ieee_reals>
              , tts::generate( tts::randoms(-1000.0, +1000.0)
                             , tts::randoms(-1000.0, +1000.0))
              )
<typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  std::cout << tts::typename_<e_t> << std::endl;
  auto tol = 2000.0*eve::eps(eve::as<e_t>());
  for(auto e : a0)
    for(auto f : a1)
    {
      auto z = eve::quaternion(e, f, e, f);
      TTS_RELATIVE_EQUAL( eve::sqr(eve::sqrt(z)), z, tol);
    }
};

TTS_CASE_WITH ( "Check behavior of sqr on wide"
              , eve::test::simd::ieee_reals
              , tts::generate(tts::randoms(-100.0, +100.0)
                             , tts::randoms(-100.0, +100.0)
                             , tts::randoms(-100.0, +100.0)
                             , tts::randoms(-100.0, +100.0)
                             )
              )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
  using e_t = eve::element_type_t<T>;
  auto tol = 4000.0*eve::eps(eve::as<e_t>());
   using z_t = eve::as_quaternion_t<T>;
  auto z = z_t(a0, a1, a2, a3);
  TTS_RELATIVE_EQUAL( eve::sqr(eve::sqrt(z)), z, tol);
};
