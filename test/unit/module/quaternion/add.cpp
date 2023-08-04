//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"
#include <eve/module/quaternion.hpp>

TTS_CASE_TPL( "Check quaternion::add", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using q_t   = eve::quaternion<T>;
  using w_t   = eve::wide<T>;
  using wq_t  = eve::wide<q_t>;
  using eve::add;

  auto fill_r = [](auto i, auto) { return T(1+i); };
  auto fill_i = [](auto i, auto) { return T(1)/(1+i); };
  auto fill   = [](auto i, auto) { return eve::quaternion<T>(T(1+i),T(1)/(1+i), T(1), T(0)); };

  q_t   z_s1(T{1.234}, T(0), T{5.678}, T(0)), z_s2(T{2.468}, T(1), T{1.357}, T(2));
  wq_t  z_v1(fill), z_v2(fill_i,fill_r);
  w_t   rv(fill_r);

  // quaternion + quaternion
  TTS_EQUAL(add(z_s1, z_s2  ) , (q_t{3.702,T(1), 7.035, T(2)}));

  // quaternion + real / real + quaternion
  TTS_EQUAL(add(z_s1   , 1     ) , (q_t{2.234,0, 5.678, 0}));
  TTS_EQUAL(add(z_s1   , 2.    ) , (q_t{3.234,0, 5.678, 0}));
  TTS_EQUAL(add(z_s1   , 3.f   ) , (q_t{4.234,0, 5.678, 0}));
//  TTS_EQUAL(add(z_s1   , eve::i) , (q_t{1.234,6.678}));

  TTS_EQUAL(add(1      , z_s1  ) , (q_t{2.234, 0,5.678, 0}));
  TTS_EQUAL(add(2.     , z_s1  ) , (q_t{3.234, 0,5.678, 0}));
  TTS_EQUAL(add(3.f    , z_s1  ) , (q_t{4.234, 0,5.678, 0}));
//  TTS_EQUAL(add(eve::i , z_s1  ) , (q_t{1.234,6.678}));

  // quaternion + wide real / wide real + quaternion
  TTS_EQUAL(add(z_s1   , rv    ) , (wq_t{[&](auto i, auto){ return z_s1 + rv.get(i);}}));
  TTS_EQUAL(add(rv     , z_s1  ) , (wq_t{[&](auto i, auto){ return z_s1 + rv.get(i);}}));

  // quaternion + wide quaternion / wide quaternion + quaternion
  TTS_EQUAL(add(z_s1 , z_v1) , (wq_t{[&](auto i, auto){ return z_s1 + z_v1.get(i);}}));
  TTS_EQUAL(add(z_v1 , z_s1) , (wq_t{[&](auto i, auto){ return z_s1 + z_v1.get(i);}}));

  // wide quaternion + wide quaternion
  TTS_EQUAL(add(z_v1   , z_v2  ) , (wq_t{[&](auto i, auto){ return q_t( z_v1.get(i) + z_v2.get(i));}}));

  // wide quaternion + real / real + wide quaternion
  TTS_EQUAL(add(z_v1   , 1     ) , (wq_t{[&](auto i, auto){ return q_t( z_v1.get(i) + 1          );}}));
  TTS_EQUAL(add(z_v1   , 2.    ) , (wq_t{[&](auto i, auto){ return q_t( z_v1.get(i) + 2.         );}}));
  TTS_EQUAL(add(z_v1   , 3.f   ) , (wq_t{[&](auto i, auto){ return q_t( z_v1.get(i) + 3.f        );}}));
//  TTS_EQUAL(add(z_v1   , eve::i) , (wq_t{[&](auto i, auto){ return q_t( z_v1.get(i) + eve::i     );}}));
  TTS_EQUAL(add(1      , z_v1  ) , (wq_t{[&](auto i, auto){ return q_t( z_v1.get(i) + 1          );}}));
  TTS_EQUAL(add(2.     , z_v1  ) , (wq_t{[&](auto i, auto){ return q_t( z_v1.get(i) + 2.         );}}));
  TTS_EQUAL(add(3.f    , z_v1  ) , (wq_t{[&](auto i, auto){ return q_t( z_v1.get(i) + 3.f        );}}));
//  TTS_EQUAL(add(eve::i , z_v1  ) , (wq_t{[&](auto i, auto){ return q_t( z_v1.get(i) + eve::i     );}}));

  // wide quaternion + wide real / wide real + wide quaternion
  TTS_EQUAL(add(z_v1   , rv    ) , (wq_t{[&](auto i, auto){ return z_v1.get(i) + rv.get(i);}}));
  TTS_EQUAL(add(rv     , z_v1  ) , (wq_t{[&](auto i, auto){ return z_v1.get(i) + rv.get(i);}}));
};
