//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/complex.hpp>

TTS_CASE_TPL( "Check eve::i constant", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  TTS_EQUAL( eve::i(eve::as<T>{})               , (eve::complex<T>{0,1}) );
  TTS_EQUAL( eve::i(eve::as<eve::complex<T>>{}) , (eve::complex<T>{0,1}) );
};

TTS_CASE_TPL( "Check eve::i constant", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using z_t = eve::as_complex_t<T>;

  TTS_EQUAL( eve::i(eve::as<T>{})   , (z_t{0,1}) );
  TTS_EQUAL( eve::i(eve::as<z_t>{}) , (z_t{0,1}) );
  TTS_EQUAL( -eve::i(eve::as<z_t>{}) , (z_t{0,-1}) );
  TTS_EQUAL( (-eve::i(eve::as<z_t>{})*T(2)),  (z_t{0,-2}) );
};
