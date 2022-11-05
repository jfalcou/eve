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

TTS_CASE_WITH( "Check behavior of geommean on wide"
             , eve::test::simd::ieee_reals
             ,tts::generate(tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10))
             )
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3, T const& a4, T const& a5 )
{
  using z_t = eve::as_complex_t<T>;
  using e_t = eve::element_type_t<T>;
  auto a = z_t(a0, a1);
  auto b = z_t(a2, a3);
  auto c = z_t(a4, a5);
  TTS_RELATIVE_EQUAL( eve::geommean(a, b), eve::sqrt(a*b), 0.005);
  TTS_RELATIVE_EQUAL( eve::geommean(a, b, c), eve::pow(a*b*c, eve::third(eve::as<e_t>())), 0.005);
};
