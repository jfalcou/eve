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

TTS_CASE_TPL( "Check quaternion::mul", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using c_t   = eve::complex<T>;
  using q_t   = eve::quaternion<T>;
  using w_t   = eve::wide<T>;
  using wq_t  = eve::wide<q_t>;
  using eve::mul;

  auto fill_r = [](auto i, auto) { return T(1+i); };
  auto fill_i = [](auto i, auto) { return T(13-i); };
  auto fill   = [](auto i, auto) { return eve::quaternion<T>(T(1+i),T(13-i), T(0), T(1)); };

  q_t   z_s1(T{1}, T{2}, T{3}, {4}), z_s2(T{4}, T{3}, T{2}, {1});
  wq_t  z_v1(fill), z_v2(fill_i,fill_r);
  w_t   rv(fill_r);
  c_t   c_s1{1, 2};

  // quaternion * quaternion
  TTS_EQUAL(mul(z_s1   , z_s2), (q_t{-12, 6, 24, 12}));
  TTS_EQUAL(mul(z_s2   , z_s1), (q_t{-12,16,  4, 22}));

  // quaternion * complex complex*quaternion
//   TTS_EQUAL(mul(z_s1   , c_s1), (q_t{-2, 11, 4, -3}));
//   TTS_EQUAL(mul(c_s1   , z_s1), (q_t{-2, 11, 0, 5}));

  // quaternion * real / real * quaternion

  TTS_EQUAL(mul(z_s1   , 1     ) , z_s1);
  TTS_EQUAL(mul(z_s1   , 2.    ) , (q_t{2.0, 4., 6., 8. }));
  TTS_EQUAL(mul(z_s1   , 3.f   ) , (q_t{3.0, 6.0, 9.0, 12.0}));
//  TTS_EQUAL(mul(z_s1   , eve::i) , (q_t{-5.5, 1.5  }));

  TTS_EQUAL(mul(1      , z_s1  ) ,  z_s1);
  TTS_EQUAL(mul(2.     , z_s1  ) ,  (q_t{2.0, 4., 6., 8. }));
  TTS_EQUAL(mul(3.f    , z_s1  ) ,  (q_t{3.0, 6.0, 9.0, 12.0}));
//  TTS_EQUAL(mul(eve::i , z_s1  ) , (q_t{-5.5, 1.5  }));

  // quaternion * wide real / wide real * quaternion
  TTS_EQUAL(mul(z_s1   , rv    ) , (wq_t{[&](auto i, auto){ return z_s1 * rv.get(i);}}));
  TTS_EQUAL(mul(rv     , z_s1  ) , (wq_t{[&](auto i, auto){ return z_s1 * rv.get(i);}}));

  // quaternion * wide quaternion / wide quaternion * quaternion
  TTS_EQUAL(mul(z_s1 , z_v1) , (wq_t{[&](auto i, auto){ return z_s1 * z_v1.get(i);}}));
  TTS_EQUAL(mul(z_v1 , z_s1) , (wq_t{[&](auto i, auto){ return  z_v1.get(i)*z_s1;}}));

  // wide quaternion * wide quaternion
  TTS_EQUAL(mul(z_v1 , z_v2), (wq_t{[&](auto i, auto){ return q_t( z_v1.get(i) * z_v2.get(i));}}));

  // wide quaternion * real / real * wide quaternion
  TTS_EQUAL(mul(z_v1   , 1     ) , (wq_t{[&](auto i, auto){ return q_t( z_v1.get(i) * 1          );}}));
  TTS_EQUAL(mul(z_v1   , 2.    ) , (wq_t{[&](auto i, auto){ return q_t( z_v1.get(i) * 2.         );}}));
  TTS_EQUAL(mul(z_v1   , 3.f   ) , (wq_t{[&](auto i, auto){ return q_t( z_v1.get(i) * 3.f        );}}));
//  TTS_EQUAL(mul(z_v1   , eve::i) , (wq_t{[&](auto i, auto){ return q_t( z_v1.get(i) * eve::i     );}}));
  TTS_EQUAL(mul(1      , z_v1  ) , (wq_t{[&](auto i, auto){ return q_t( z_v1.get(i) * 1          );}}));
  TTS_EQUAL(mul(2.     , z_v1  ) , (wq_t{[&](auto i, auto){ return q_t( z_v1.get(i) * 2.         );}}));
  TTS_EQUAL(mul(3.f    , z_v1  ) , (wq_t{[&](auto i, auto){ return q_t( z_v1.get(i) * 3.f        );}}));
//  TTS_EQUAL(mul(eve::i , z_v1  ) , (wq_t{[&](auto i, auto){ return q_t( z_v1.get(i) * eve::i     );}}));

  // wide quaternion * wide real / wide real * wide quaternion
  TTS_EQUAL(mul(z_v1   , rv    ) , (wq_t{[&](auto i, auto){ return z_v1.get(i) * rv.get(i);}}));
  TTS_EQUAL(mul(rv     , z_v1  ) , (wq_t{[&](auto i, auto){ return z_v1.get(i) * rv.get(i);}}));
};

// TTS_CASE_WITH( "Check pedantic(quaternion::mul)"
//              , eve::test::simd::ieee_reals
//              ,tts::generate(tts::randoms(-10, 10)
//                            , tts::randoms(-10, 10)
//                            , tts::randoms(-10, 10)
//                            , tts::randoms(-10, 10)
//                            , tts::randoms(-10, 10)
//                            , tts::randoms(-10, 10))
//              )
//   <typename T>(T const& a0, T const& a1, T const& a2 , T const& a3, T const& a4 , T const& a5 )
// {
//   using z_t = eve::as_quaternion_t<T>;
//   auto a = z_t(a0, a1);
//   auto b = z_t(a2, a3);
//   auto c = z_t(a4, a5);

//   TTS_ULP_EQUAL( eve::mul(a, b), a*b, 0.5);
//   TTS_ULP_EQUAL( eve::mul(a, b, c), a*b*c, 0.5);
//   TTS_ULP_EQUAL( eve::pedantic(eve::mul)(a, b), a*b, 4.5);
//   {
//     z_t c(1, eve::inf(eve::as(a0)));
//     z_t a(2.0, 3.0);
//     z_t rr(eve::minf(eve::as(a0)), eve::inf(eve::as(a0)));
//     z_t ac = a*c;
//     z_t  d = eve::pedantic(eve::mul)(a, c);
//     TTS_ULP_EQUAL( d, rr, 0.5);
//     TTS_ULP_EQUAL( eve::mul(a, c), rr, 0.5);
//     TTS_ULP_EQUAL( ac, rr, 0.5);
//   }
//   {
//     z_t c(eve::inf(eve::as(a0)), a0);
//     z_t rr(eve::inf(eve::as(a0)), eve::nan(eve::as(a0)));
//     z_t a(1, 0);
//     z_t  d = eve::pedantic(eve::mul)(a, c);
//     TTS_ULP_EQUAL( d, c, 0.5);
//     TTS_ULP_EQUAL( eve::mul(a, c), rr, 0.5);
//   }
//   {
//     z_t c(eve::inf(eve::as(a0)), 1.5);
//     z_t rr(eve::inf(eve::as(a0)), eve::inf(eve::as(a0)));
//     z_t a(eve::inf(eve::as(a0)), 1.5);
//     z_t  d = eve::pedantic(eve::mul)(a, c);
//     TTS_ULP_EQUAL( d, rr, 0.5);
//     TTS_ULP_EQUAL( eve::mul(a, c), rr, 0.5);
//   }
//   {
//     z_t a(eve::inf(eve::as(a0)), 1.5);
//     z_t c(1, 0);
//     z_t rr(eve::inf(eve::as(a0)), eve::nan(eve::as(a0)));
//     z_t  d = eve::pedantic(eve::mul)(a, c);
//     TTS_ULP_EQUAL( d, a, 0.5);
//     TTS_ULP_EQUAL( eve::mul(a, c), rr, 0.5);
//   }
// };
