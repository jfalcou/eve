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

TTS_CASE_WITH( "Check behavior of average on wide"
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
  TTS_ULP_EQUAL( eve::average(a, b), (z_t{eve::average(a0, a2), eve::average(a1, a3)}), 0.5);
  TTS_ULP_EQUAL( eve::average(a, a2), (z_t{eve::average(a0, a2), eve::average(a1, eve::zero(eve::as(a1)))}), 0.5);
  TTS_ULP_EQUAL( eve::average(a0, b), (z_t{eve::average(a0, a2), eve::average(eve::zero(eve::as(a1)), a3)}), 0.5);
  TTS_ULP_EQUAL( eve::average(a0, T(1.0)), eve::average(a0,eve::one(eve::as(a1))), 0.5);
};
