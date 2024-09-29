//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>

TTS_CASE_TPL( "Check diff_of_prod", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using e_t   = T;
  using we_t  = eve::wide<e_t>;

  auto test = [](auto a,  auto b, auto c, auto d){return a*b-c*d; };
  auto rdop = [](auto a,  auto b, auto c, auto d){return eve::diff_of_prod[eve::raw](a, b, c, d);};
  auto dop = [](auto a,  auto b, auto c, auto d){return eve::diff_of_prod(a, b, c, d);};
  auto pdop = [](auto a,  auto b, auto c, auto d){return eve::diff_of_prod[eve::pedantic](a, b, c, d);};
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

  TTS_EQUAL(rdop(e1, e1, e1, e1), test( e1, e1, e1, e1));
  TTS_EQUAL(rdop(d1, d1, d1, d1), test( d1, d1, d1, d1));
  TTS_EQUAL(rdop(d1, d1, d1, d1), test( d1, d1, d1, d1));
  TTS_EQUAL(rdop(i1, i1, i1, i1), test( i1, i1, i1, i1));
  TTS_EQUAL(rdop(we1, we1, we1, we1), test( we1, we1, we1, we1));
  TTS_EQUAL(rdop(i1,  we1, we1, we1), test( we1, we1, we1, we1));
  TTS_EQUAL(rdop(f1,  we1, we1, we1), test( f1,  we1, we1, we1));
  TTS_EQUAL(rdop(d1,  we1, we1, we1), test( d1,  we1, we1, we1));
  TTS_EQUAL(rdop(e1,  we1, we1, we1), test( we1, we1, we1, we1));
  TTS_EQUAL(rdop(e1,  we1, we1, we1), test( we1, we1, we1, we1));

  TTS_EQUAL(rdop(i1,  f1, d1, we1), test( i1, f1, d1, we1));
  TTS_EQUAL(rdop(we1, i1,  f1, d1), test(we1, i1, f1, d1));

  TTS_EQUAL(pdop(e1, e1, e1, e1), test( e1, e1, e1, e1));
  TTS_EQUAL(pdop(d1, d1, d1, d1), test( d1, d1, d1, d1));
  TTS_EQUAL(pdop(d1, d1, d1, d1), test( d1, d1, d1, d1));
  TTS_EQUAL(pdop(i1, i1, i1, i1), test( i1, i1, i1, i1));
  TTS_EQUAL(pdop(we1, we1, we1, we1), test( we1, we1, we1, we1));
  TTS_EQUAL(pdop(i1,  we1, we1, we1), test( we1, we1, we1, we1));
  TTS_EQUAL(pdop(f1,  we1, we1, we1), test( f1,  we1, we1, we1));
  TTS_EQUAL(pdop(d1,  we1, we1, we1), test( d1,  we1, we1, we1));
  TTS_EQUAL(pdop(e1,  we1, we1, we1), test( we1, we1, we1, we1));
  TTS_EQUAL(pdop(e1,  we1, we1, we1), test( we1, we1, we1, we1));

  TTS_EQUAL(pdop(i1,  f1, d1, we1), test( i1, f1, d1, we1));
  TTS_EQUAL(pdop(we1, i1,  f1, d1), test(we1, i1, f1, d1));
};

//==================================================================================================
// diff_of_prod upper lower tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of diff_of_prod lower upper on real types",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-1000, 1000),
                            tts::randoms(-1000, 1000),
                            tts::randoms(-1000, 1000),
                            tts::randoms(-1000, 1000))
             )
  <typename T>(T const& a0, T const& a1, T const& a2 , T const& a3 )
{
  using eve::as;
  using eve::fma;
  using eve::diff_of_prod;
  using eve::lower;
  using eve::upper;
  using eve::strict;
  TTS_EXPECT(eve::all(diff_of_prod[upper](a0, a1, a2, a3) >= diff_of_prod(a0, a1, a2, a3)));
  TTS_EXPECT(eve::all(diff_of_prod[lower](a0, a1, a2, a3) <= diff_of_prod(a0, a1, a2, a3)));
  TTS_EXPECT(eve::all(diff_of_prod[upper][strict](a0, a1, a2, a3) > diff_of_prod(a0, a1, a2, a3)));
  TTS_EXPECT(eve::all(diff_of_prod[lower][strict](a0, a1, a2, a3) < diff_of_prod(a0, a1, a2, a3)));
  TTS_EXPECT(eve::all(diff_of_prod[strict][upper](a0, a1, a2, a3) >= diff_of_prod[upper](a0, a1, a2, a3)));
  TTS_EXPECT(eve::all(diff_of_prod[strict][lower](a0, a1, a2, a3) <= diff_of_prod[lower](a0, a1, a2, a3)));
};
