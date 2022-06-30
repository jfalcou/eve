//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"
#include <eve/module/complex.hpp>
#include <complex>

TTS_CASE_WITH( "Check behavior of maxabs on wide"
        , eve::test::simd::ieee_reals
        ,tts::generate(tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             , tts::randoms(-10, 10)
                             , tts::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
  using z_t = eve::as_complex_t<T>;
  using eve::abs;
  auto a = z_t(a0, a1);
  auto b = z_t(a2, a3);
  TTS_ULP_EQUAL( eve::maxabs(a, b)  , eve::max(abs(a), eve::abs(b)), 0.5);
  TTS_ULP_EQUAL( eve::maxabs(a, a2) , eve::max(abs(a), eve::abs(a2)), 0.5);
  TTS_ULP_EQUAL( eve::maxabs(a0, b) , eve::max(abs(a0), eve::abs(b)), 0.5);
  TTS_ULP_EQUAL( eve::maxabs(1, b)  , eve::max(1, eve::abs(b)), 0.5);
};
