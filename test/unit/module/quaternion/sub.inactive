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

TTS_CASE_TPL( "Check complex::sub", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using c_t   = eve::complex<T>;
  using w_t   = eve::wide<T>;
  using wc_t  = eve::wide<c_t>;
  using eve::sub;

  auto fill_ur = [](auto i, auto) { return -T(1+i); };
  auto fill_ui = [](auto i, auto) { return -T(1)/(1+i); };
  auto fill_u   = [](auto i, auto) { return eve::complex<T>(T(1+i),T(1)/(1+i)); };

  c_t   z_s(T{1.234}, T{5.678});
  wc_t  z_v(fill_u);

  TTS_EQUAL( -z_s, (c_t{-1.234, -5.678}));
  TTS_EQUAL( -z_v, (wc_t{fill_ur,fill_ui}));

  auto fill_r = [](auto i, auto) { return T(1+i); };
  auto fill_i = [](auto i, auto) { return 13+(1+i); };
  auto fill   = [](auto i, auto) { return eve::complex<T>(T(1+i),13+(1+i)); };

  c_t   z_s1(T{1.5}, T{5.5}), z_s2(T{2.5}, T{1.25});
  wc_t  z_v1(fill), z_v2(fill_i,fill_r);
  w_t   rv(fill_r);

  // complex - complex
  TTS_EQUAL(sub(z_s1   , z_s2  ) , (c_t{-1.,4.25}));

  // i and real
  TTS_EQUAL(sub(1   , eve::i) , (c_t{1.f,-1.f }));
  TTS_EQUAL(sub(2.  , eve::i) , (c_t{2. ,-1.  }));
  TTS_EQUAL(sub(3.f , eve::i) , (c_t{3.f,-1.f }));
  TTS_EQUAL(sub(eve::i , 1  ) , (c_t{-1.f,1.f }));
  TTS_EQUAL(sub(eve::i , 2. ) , (c_t{-2.,1.   }));
  TTS_EQUAL(sub(eve::i , 3.f) , (c_t{-3.f,1.f }));

  TTS_EQUAL(sub(rv  , eve::i) , (wc_t{rv,-1.f }));
  TTS_EQUAL(sub(eve::i , rv ) , (wc_t{-rv,1.f }));

  // complex - real / real - complex
  TTS_EQUAL(sub(z_s1   , 1     ) , (c_t{ 0.5,5.5}));
  TTS_EQUAL(sub(z_s1   , 2.    ) , (c_t{-0.5,5.5}));
  TTS_EQUAL(sub(z_s1   , 3.f   ) , (c_t{-1.5,5.5}));
  TTS_EQUAL(sub(z_s1   , eve::i) , (c_t{ 1.5,4.5}));

  TTS_EQUAL(sub(1      , z_s1  ) , (c_t{-0.5,-5.5}));
  TTS_EQUAL(sub(2.     , z_s1  ) , (c_t{ 0.5,-5.5}));
  TTS_EQUAL(sub(3.f    , z_s1  ) , (c_t{ 1.5,-5.5}));
  TTS_EQUAL(sub(eve::i , z_s1  ) , (c_t{-1.5,-4.5}));

  // complex - wide real / wide real - complex
  TTS_EQUAL(sub(z_s1   , rv    ) , (wc_t{[&](auto i, auto){ return z_s1 - rv.get(i);}}));
  TTS_EQUAL(sub(rv     , z_s1  ) , (wc_t{[&](auto i, auto){ return rv.get(i) - z_s1;}}));

  // complex - wide complex / wide complex - complex
  TTS_EQUAL(sub(z_s1 , z_v1) , (wc_t{[&](auto i, auto){ return z_s1 - z_v1.get(i);}}));
  TTS_EQUAL(sub(z_v1 , z_s1) , (wc_t{[&](auto i, auto){ return z_v1.get(i) - z_s1;}}));

  // wide complex - wide complex
  TTS_EQUAL(sub(z_v1   , z_v2  ) , (wc_t{[&](auto i, auto){ return c_t( z_v1.get(i) - z_v2.get(i));}}));

  // wide complex - real / real - wide complex
  TTS_EQUAL(sub(z_v1   , 1     ) , (wc_t{[&](auto i, auto){ return c_t( z_v1.get(i) - 1          );}}));
  TTS_EQUAL(sub(z_v1   , 2.    ) , (wc_t{[&](auto i, auto){ return c_t( z_v1.get(i) - 2.         );}}));
  TTS_EQUAL(sub(z_v1   , 3.f   ) , (wc_t{[&](auto i, auto){ return c_t( z_v1.get(i) - 3.f        );}}));
  TTS_EQUAL(sub(z_v1   , eve::i) , (wc_t{[&](auto i, auto){ return c_t( z_v1.get(i) - eve::i     );}}));
  TTS_EQUAL(sub(1      , z_v1  ) , (wc_t{[&](auto i, auto){ return c_t(1      - z_v1.get(i));}}));

  TTS_EQUAL(sub(2.     , z_v1  ) , (wc_t{[&](auto i, auto){ return c_t(2.     - z_v1.get(i));}}));
  TTS_EQUAL(sub(3.f    , z_v1  ) , (wc_t{[&](auto i, auto){ return c_t(3.f    - z_v1.get(i));}}));
  TTS_EQUAL(sub(eve::i , z_v1  ) , (wc_t{[&](auto i, auto){ return c_t(eve::i - z_v1.get(i));}}));

  // wide complex - wide real / wide real - wide complex
  TTS_EQUAL(sub(z_v1   , rv    ) , (wc_t{[&](auto i, auto){ return z_v1.get(i) - rv.get(i);}}));
  TTS_EQUAL(sub(rv     , z_v1  ) , (wc_t{[&](auto i, auto){ return rv.get(i)   - z_v1.get(i);}}));
};
