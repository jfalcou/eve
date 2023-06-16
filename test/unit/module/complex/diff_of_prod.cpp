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

TTS_CASE_TPL( "Check complex::diff_of_prod", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using e_t   = T;
  using c_t   = eve::complex<e_t>;
  using we_t  = eve::wide<e_t>;
  using wc_t  = eve::wide<c_t>;

  auto test = [](auto a,  auto b, auto c, auto d){return a*b-c*d; };
  auto dop = [](auto a,  auto b, auto c, auto d){return eve::diff_of_prod(a, b, c, d);};
  int i1 = 1;
  float f1 = 2.0f;
  double d1 = 1.0;
  e_t e1(1);
  c_t c1(1, 1);
  wc_t  wc1(c1);
  we_t  we1(e1);

  TTS_EQUAL(dop(e1, e1, e1, e1), test( e1, e1, e1, e1));
  TTS_EQUAL(dop(we1, we1, we1, we1), test( we1, we1, we1, we1));
  TTS_EQUAL(dop(c1, c1, c1, c1), test( c1, c1, c1, c1));
  TTS_EQUAL(dop(wc1, wc1, wc1, wc1), test( wc1, wc1, wc1, wc1));
  TTS_EQUAL(dop(i1, i1, i1, i1), test( i1, i1, i1, i1));
  TTS_EQUAL(dop(i1, we1, we1, we1), test( i1, we1, we1, we1));
  TTS_EQUAL(dop(e1, we1, we1, we1), test( e1, we1, we1, we1));
  TTS_EQUAL(dop(f1, we1, we1, we1), test( f1, we1, we1, we1));
  TTS_EQUAL(dop(d1, we1, we1, we1), test( d1, we1, we1, we1));

  TTS_EQUAL(dop(i1, wc1, wc1, wc1), test( i1, wc1, wc1, wc1));
  TTS_EQUAL(dop(e1, wc1, wc1, wc1), test( e1, wc1, wc1, wc1));
  TTS_EQUAL(dop(f1, wc1, wc1, wc1), test( f1, wc1, wc1, wc1));
  TTS_EQUAL(dop(d1, wc1, wc1, wc1), test( d1, wc1, wc1, wc1));
  TTS_EQUAL(dop(d1, f1, i1, wc1), test( d1, f1, i1, wc1));

//  TTS_EQUAL(dop(eve::i, f1, i1, wc1), test(eve::i, f1, i1, wc1));
//  TTS_EQUAL(dop(eve::i, wc1, wc1, wc1), test(eve::i, wc1, wc1, wc1));
};
