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


TTS_CASE_TPL( "Check complex::div", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using c_t   = eve::complex<T>;
  using w_t   = eve::wide<T>;
  using wc_t  = eve::wide<c_t>;
  using eve::div;

  auto fill_r = [](auto i, auto) { return T(1+i); };
  auto fill_i = [](auto i, auto) { return 2*T(1+i); };
  auto fill   = [](auto i, auto) { return eve::complex<T>(T(1+i),2*T(1+i)); };

  c_t   z_s1(T{1}, T{3}), z_s2(T{2}, T{-2});
  wc_t  z_v1(fill), z_v2(fill_i,fill_r);
  w_t   rv(fill_r);

  // complex / complex
  TTS_EQUAL(div(z_s1  , z_s2  ) , (c_t{-0.5,1}));

  // i and real
  TTS_EQUAL(div(1   , eve::i) , (c_t{0.f,-1.f }));
  TTS_EQUAL(div(2.  , eve::i) , (c_t{0. ,-2.  }));
  TTS_EQUAL(div(3.f,  eve::i) , (c_t{0.f,-3.f }));
  TTS_EQUAL(div(eve::i,  1  ) , (c_t{0.f,1.f  }));
  TTS_EQUAL(div(eve::i,  2. ) , (c_t{0. ,0.5  }));
  TTS_EQUAL(div(eve::i,  3.f) , (c_t{0.f,1.f/3}));

  TTS_EQUAL(div(rv  , eve::i) , (wc_t{0.f,-rv  }));
  TTS_EQUAL(div(eve::i,  rv ) , (wc_t{0.f,1./rv}));

  // complex / real / real / complex
  TTS_EQUAL(div(z_s1   , 1     ) , (c_t{1.   , 3. }));
  TTS_EQUAL(div(z_s1   , 2.    ) , (c_t{0.5  , 1.5}));
  TTS_EQUAL(div(z_s1   , 3.f   ) , (c_t{1./3 , 1. }));
  TTS_EQUAL(div(z_s1   , eve::i) , (c_t{3.   ,-1. }));

  TTS_EQUAL(div(1      , z_s2  ) , (c_t{0.25 , 0.25 }));
  TTS_EQUAL(div(2.     , z_s2  ) , (c_t{0.5  , 0.5  }));
  TTS_EQUAL(div(4.f    , z_s2  ) , (c_t{1    , 1    }));
  TTS_EQUAL(div(eve::i,  z_s2  ) , (c_t{-0.25, 0.25}));

  // complex / wide real / wide real / complex
  TTS_EQUAL(div(z_s1   , rv    ) , (wc_t{[&](auto i, auto){ return z_s1 / rv.get(i);}}));
  TTS_EQUAL(div(rv     , z_s1  ) , (wc_t{[&](auto i, auto){ return rv.get(i) / z_s1;}}));

  // complex / wide complex / wide complex / complex
  TTS_RELATIVE_EQUAL(div(z_s1,  z_v1) , (wc_t{[&](auto i, auto){ return z_s1 / z_v1.get(i);}}), 1e-4);
  TTS_RELATIVE_EQUAL(div(z_v1,  z_s1) , (wc_t{[&](auto i, auto){ return z_v1.get(i) / z_s1;}}), 1e-4);

  // wide complex / wide complex
  TTS_RELATIVE_EQUAL(div(z_v1   , z_v2  ) , (wc_t{[&](auto i, auto){ return c_t( z_v1.get(i) / z_v2.get(i));}}), 1e-4);

  // wide complex / real / real / wide complex
  TTS_RELATIVE_EQUAL(div(z_v1   , 1     ) , (wc_t{[&](auto i, auto){ return c_t( z_v1.get(i) / 1     );}}), 1e-4);
  TTS_RELATIVE_EQUAL(div(z_v1   , 2.    ) , (wc_t{[&](auto i, auto){ return c_t( z_v1.get(i) / 2.    );}}), 1e-4);
  TTS_RELATIVE_EQUAL(div(z_v1   , 3.f   ) , (wc_t{[&](auto i, auto){ return c_t( z_v1.get(i) / 3.f   );}}), 1e-4);
  TTS_RELATIVE_EQUAL(div(z_v1   , eve::i) , (wc_t{[&](auto i, auto){ return c_t( z_v1.get(i) / eve::i);}}), 1e-4);
  TTS_RELATIVE_EQUAL(div(1      , z_v1  ) , (wc_t{[&](auto i, auto){ return c_t(1       / z_v1.get(i));}}), 1e-4);
  TTS_RELATIVE_EQUAL(div(2.     , z_v1  ) , (wc_t{[&](auto i, auto){ return c_t(2.      / z_v1.get(i));}}), 1e-4);
  TTS_RELATIVE_EQUAL(div(3.f    , z_v1  ) , (wc_t{[&](auto i, auto){ return c_t(3.f     / z_v1.get(i));}}), 1e-4);
  TTS_RELATIVE_EQUAL(div(eve::i,  z_v1  ) , (wc_t{[&](auto i, auto){ return c_t(eve::i  / z_v1.get(i));}}), 1e-4);

  // wide complex / wide real / wide real / wide complex
  TTS_RELATIVE_EQUAL(div(z_v1   , rv    ) , (wc_t{[&](auto i, auto){ return z_v1.get(i) / rv.get(i);}}), 1e-4);
  TTS_RELATIVE_EQUAL(div(rv     , z_v1  ) , (wc_t{[&](auto i, auto){ return rv.get(i)   / z_v1.get(i);}}), 1e-4);
};

TTS_CASE_WITH( "Check behavior of average on wide"
             , eve::test::simd::ieee_reals
             ,tts::generate(tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10)
                           , tts::randoms(-10, 10))
             )
  <typename T>(T const& a0, T const& a1, T const& a2, T const& a3, T const& a4 , T const& a5  )
{
  using z_t = eve::as_complex_t<T>;
  auto a = z_t(a0, a1);
  auto b = z_t(a2, a3);
  auto c = z_t(a4, a5);
  TTS_ULP_EQUAL( eve::div(a, b), a/b, 1.0);
  TTS_ULP_EQUAL( eve::div(a, b, c), a/(b*c), 4.0);
  TTS_ULP_EQUAL( eve::pedantic(eve::div)(a, b), a/b, 10);
  {
    z_t c(1, eve::inf(eve::as(a0)));
    z_t rr(0, 0);
    z_t  d = eve::pedantic(eve::div)(a, c);
    TTS_ULP_EQUAL( d, rr, 0.5);
    TTS_ULP_EQUAL( eve::div(a, c), a/c, 0.5);
  }
  {
    z_t c(eve::inf(eve::as(a0)), 1);
    z_t rp(0, 0);
    z_t  d = eve::pedantic(eve::div)(a, c);
    TTS_ULP_EQUAL( d, rp, 0.5);
    TTS_ULP_EQUAL( eve::div(a, c), a/c, 0.5);
  }
  {
    z_t c(eve::inf(eve::as(a0)), eve::inf(eve::as(a0)));
    z_t rr(0, 0);
    z_t  d = eve::pedantic(eve::div)(a, c);
    TTS_ULP_EQUAL( d, rr, 0.5);
    TTS_ULP_EQUAL( eve::div(a, c), a/c, 0.5);
  }
};
