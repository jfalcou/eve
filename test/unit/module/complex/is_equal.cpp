//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"
#include <eve/module/complex.hpp>
#include <complex>

TTS_CASE_WITH( "Check behavior of is_equal on wide"
        , eve::test::simd::ieee_reals
        ,tts::generate(tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             , tts::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
  using z_t = eve::as_complex_t<T>;
  auto a = z_t(a0, a1);
  auto b = z_t(a2, a3);
  TTS_ULP_EQUAL( eve::is_equal(a, b), (eve::is_equal(a0, a2) && eve::is_equal(a1, a3)), 0.5);
  TTS_ULP_EQUAL( a == b , (eve::is_equal(a0, a2) && eve::is_equal(a1, a3)), 0.5);
  TTS_ULP_EQUAL( a == a , eve::is_not_nan(a), 0.5);
  auto z = eve::nan(eve::as(a));
  TTS_EQUAL(eve::is_equal(z, z) , eve::false_(eve::as(a)));
  TTS_EQUAL( eve::numeric(eve::is_equal)(z, z) , eve::true_(eve::as(a)));
};
