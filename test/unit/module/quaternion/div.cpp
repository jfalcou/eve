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


TTS_CASE_TPL( "Check quaternion::div", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using q_t   = eve::quaternion<T>;
  using w_t   = eve::wide<T>;
  using wq_t  = eve::wide<q_t>;
  using eve::div;

  auto fill_r = [](auto i, auto) { return T(1+i); };
  auto fill_i = [](auto i, auto) { return 2*T(1+i); };
  auto fill   = [](auto i, auto) { return eve::quaternion<T>(T(1+i),2*T(1+i), T(0), T(1)); };

  q_t   z_s1(T{1}, T{2}, T{3}, {4}), z_s2(T{4}, T{3}, T{2}, {1});
  wq_t  z_v1(fill), z_v2(fill_i,fill_r);
  w_t   rv(fill_r);

  // quaternion / quaternion
  TTS_EQUAL(div(z_s1  , z_s2  ) , (z_s1*eve::conj(z_s2)/eve::sqr_abs(z_s2)));

  // quaternion / real / real / quaternion
  TTS_EQUAL(div(z_s1   , 1     ) , (q_t{1., 2. , 3., 4.}));
  TTS_EQUAL(div(z_s1   , 4.    ) , (q_t{0.25, 0.5, +0.75, +1}));
  TTS_EQUAL(div(z_s1   , 8.f   ) , (q_t{0.125 , 0.25, 0.375, 0.5}));
//  TTS_EQUAL(div(z_s1   , eve::i) , (q_t{3.   ,-1. }));

  TTS_RELATIVE_EQUAL(div(1      , z_s2  ) , (q_t{2./15, -1./10, -1./15, -1./30}), eve::eps(eve::as<T>()));
  TTS_RELATIVE_EQUAL(div(2.     , z_s2  ) , (q_t{4./15, -2./10, -2./15, -1./15  }), eve::eps(eve::as<T>()));
  TTS_RELATIVE_EQUAL(div(4.f    , z_s2  ) , (q_t{8./15, -4./10, -4./15, -2./15  }),  eve::eps(eve::as<T>()));

//  TTS_EQUAL(div(eve::i,  z_s2  ) , (q_t{-0.25, 0.25}));

  // quaternion / wide real / wide real / quaternion
  TTS_RELATIVE_EQUAL(div(z_s1   , rv    ) , (wq_t{[&](auto i, auto){ return z_s1 / rv.get(i);}}), eve::eps(eve::as<T>()));
  TTS_RELATIVE_EQUAL(div(rv     , z_s1  ) , (wq_t{[&](auto i, auto){ return rv.get(i) / z_s1;}}), eve::eps(eve::as<T>()));

  // quaternion / wide quaternion / wide quaternion / quaternion
  TTS_RELATIVE_EQUAL(div(z_s1,  z_v1) , (wq_t{[&](auto i, auto){ return z_s1 / z_v1.get(i);}}), eve::eps(eve::as<T>()));
  TTS_RELATIVE_EQUAL(div(z_v1,  z_s1) , (wq_t{[&](auto i, auto){ return z_v1.get(i) / z_s1;}}), eve::eps(eve::as<T>()));

  // wide quaternion / wide quaternion
  TTS_RELATIVE_EQUAL(div(z_v1   , z_v2  ) , (wq_t{[&](auto i, auto){ return q_t( z_v1.get(i) / z_v2.get(i));}}), eve::eps(eve::as<T>()));

  // wide quaternion / real / real / wide quaternion
  TTS_RELATIVE_EQUAL(div(z_v1   , 1     ) , (wq_t{[&](auto i, auto){ return q_t( z_v1.get(i) / 1     );}}), 1e-4);
  TTS_RELATIVE_EQUAL(div(z_v1   , 2.    ) , (wq_t{[&](auto i, auto){ return q_t( z_v1.get(i) / 2.    );}}), 1e-4);
  TTS_RELATIVE_EQUAL(div(z_v1   , 3.f   ) , (wq_t{[&](auto i, auto){ return q_t( z_v1.get(i) / 3.f   );}}), 1e-4);
//  TTS_RELATIVE_EQUAL(div(z_v1   , eve::i) , (wq_t{[&](auto i, auto){ return q_t( z_v1.get(i) / eve::i);}}), 1e-4);
  TTS_RELATIVE_EQUAL(div(1      , z_v1  ) , (wq_t{[&](auto i, auto){ return q_t(1       / z_v1.get(i));}}), 1e-4);
  TTS_RELATIVE_EQUAL(div(2.     , z_v1  ) , (wq_t{[&](auto i, auto){ return q_t(2.      / z_v1.get(i));}}), 1e-4);
  TTS_RELATIVE_EQUAL(div(3.f    , z_v1  ) , (wq_t{[&](auto i, auto){ return q_t(3.f     / z_v1.get(i));}}), 1e-4);
//  TTS_RELATIVE_EQUAL(div(eve::i,  z_v1  ) , (wq_t{[&](auto i, auto){ return q_t(eve::i  / z_v1.get(i));}}), 1e-4);

  // wide quaternion / wide real / wide real / wide quaternion
  TTS_RELATIVE_EQUAL(div(z_v1   , rv    ) , (wq_t{[&](auto i, auto){ return z_v1.get(i) / rv.get(i);}}), 1e-4);
  TTS_RELATIVE_EQUAL(div(rv     , z_v1  ) , (wq_t{[&](auto i, auto){ return rv.get(i)   / z_v1.get(i);}}), 1e-4);
};

// TTS_CASE_WITH( "Check behavior of average on wide"
//              , eve::test::simd::ieee_reals
//              ,tts::generate(tts::randoms(-10, 10)
//                            , tts::randoms(-10, 10)
//                            , tts::randoms(-10, 10)
//                            , tts::randoms(-10, 10)
//                            , tts::randoms(-10, 10)
//                            , tts::randoms(-10, 10))
//              )
//   <typename T>(T const& a0, T const& a1, T const& a2, T const& a3, T const& a4 , T const& a5  )
// {
//   using z_t = eve::as_quaternion_t<T>;
//   auto a = z_t(a0, a1);
//   auto b = z_t(a2, a3);
//   auto c = z_t(a4, a5);
//   TTS_ULP_EQUAL( eve::div(a, b), a/b, 1.0);
//   TTS_ULP_EQUAL( eve::div(a, b, c), a/(b*c), 4.0);
//   TTS_ULP_EQUAL( eve::pedantic(eve::div)(a, b), a/b, 10);
//   {
//     z_t c(1, eve::inf(eve::as(a0)));
//     z_t rr(0, 0);
//     z_t  d = eve::pedantic(eve::div)(a, c);
//     TTS_ULP_EQUAL( d, rr, 0.5);
//     TTS_ULP_EQUAL( eve::div(a, c), a/c, 0.5);
//   }
//   {
//     z_t c(eve::inf(eve::as(a0)), 1);
//     z_t rp(0, 0);
//     z_t  d = eve::pedantic(eve::div)(a, c);
//     TTS_ULP_EQUAL( d, rp, 0.5);
//     TTS_ULP_EQUAL( eve::div(a, c), a/c, 0.5);
//   }
//   {
//     z_t c(eve::inf(eve::as(a0)), eve::inf(eve::as(a0)));
//     z_t rr(0, 0);
//     z_t  d = eve::pedantic(eve::div)(a, c);
//     TTS_ULP_EQUAL( d, rr, 0.5);
//     TTS_ULP_EQUAL( eve::div(a, c), a/c, 0.5);
//   }
// };
