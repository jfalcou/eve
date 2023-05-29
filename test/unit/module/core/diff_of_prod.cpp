//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>

TTS_CASE_TPL( "Check sum_of_prod", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using e_t   = T;
  using we_t  = eve::wide<e_t>;

  auto test = [](auto a,  auto b, auto c, auto d){return a*b-c*d; };
  auto dop = [](auto a,  auto b, auto c, auto d){return eve::diff_of_prod(a, b, c, d);};
  int i1 = 1;
  float f1 = 2.0f;
  double d1 = 1.0f;
  e_t e1(1);
  we_t  we1(e1);

  TTS_EQUAL(dop(e1, e1, e1, e1), test( e1, e1, e1, e1));
  TTS_EQUAL(dop(d1, d1, d1, d1), test( d1, d1, d1, d1));
  TTS_EQUAL(dop(d1, d1, d1, d1), test( d1, d1, d1, d1));
  TTS_EQUAL(dop(i1, i1, i1, i1), test( i1, i1, i1, i1));
  TTS_EQUAL(dop(we1, we1, we1, we1), test( we1, we1, we1, we1));
  TTS_EQUAL(dop(i1,  we1, we1, we1), test( we1, we1, we1, we1));
  TTS_EQUAL(dop(f1,  we1, we1, we1), test( f1,  we1, we1, we1));
  TTS_EQUAL(dop(d1,  we1, we1, we1), test( d1,  we1, we1, we1));
  TTS_EQUAL(dop(e1,  we1, we1, we1), test( we1, we1, we1, we1));
  TTS_EQUAL(dop(e1,  we1, we1, we1), test( we1, we1, we1, we1));

  TTS_EQUAL(dop(i1,  f1, d1, we1), test( i1, f1, d1, we1));
  TTS_EQUAL(dop(we1, i1,  f1, d1), test(we1, i1, f1, d1));


};
