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
  auto inf = eve::inf(eve::as<T>());
  auto nan = eve::nan(eve::as<T>());
  TTS_EQUAL( eve::i(eve::as<T>{})   , (z_t{0,1}) );
  TTS_EQUAL( eve::i(eve::as<z_t>{}) , (z_t{0,1}) );
  TTS_EQUAL( -eve::i(eve::as<z_t>{}) , (z_t{0,-1}) );
  TTS_EQUAL( (-eve::i(eve::as<z_t>{})*T(2)),  (z_t{0,-2}) );
  TTS_EQUAL( (-(eve::i*T(2))),  (z_t{0,-2}) );
  TTS_IEEE_EQUAL( (eve::i(eve::as<z_t>{})*inf), (z_t{nan,inf}));
  TTS_IEEE_EQUAL( (eve::i(eve::as<z_t>{})*z_t{inf, 0}), (z_t{nan,inf}));
  TTS_IEEE_EQUAL( (inf*eve::i(eve::as<z_t>{})), (z_t{nan,inf}));
  TTS_IEEE_EQUAL( (z_t{inf, 0}*eve::i(eve::as<z_t>{})), (z_t{nan,inf}));
  TTS_IEEE_EQUAL( (z_t{inf, 0}*eve::i), (z_t{0,inf}));
  TTS_IEEE_EQUAL( (inf*eve::i), (z_t{0,inf}));
  TTS_IEEE_EQUAL( eve::i*(z_t{0,inf}), (z_t{-inf,0}));
  TTS_EQUAL( (eve::i*eve::i(eve::as<z_t>{})), (z_t{-1, 0}));
  TTS_EQUAL( (eve::i(eve::as<z_t>{})*eve::i(eve::as<z_t>{})), (z_t{-1, 0}));
};
