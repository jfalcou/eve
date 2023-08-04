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

// TTS_CASE_WITH ( "Check behavior of to_euler on scalar"
//               , tts::bunch<eve::test::scalar::ieee_reals>
//               , tts::generate(tts::randoms(-1000.0, +1000.0)
//                              , tts::randoms(-1000.0, +1000.0)
//                              )
//               )
// <typename T>(T const& a0, T const& a1 )
// {
//   std::integral_constant<int, 1> _1;
//   std::integral_constant<int, 2> _2;
//   std::integral_constant<int, 3> _3;
//   using eve::pedantic;
//   for(auto e : a0)
//     for(auto f : a1)
//     {
//       auto z = eve::quaternion(e, f, e, f);
//       auto [t1, t2, t3] = eve::to_euler(z, _3, _2, _1);
//       std::cout << t1 << std::endl;
//       std::cout << t2 << std::endl;
//       std::cout << t3 << std::endl;
//     }
// };

TTS_CASE_WITH ( "Check behavior of to_euler on wide"
              , eve::test::simd::ieee_reals
              , tts::generate(tts::randoms(-1000.0, +1000.0)
                             , tts::randoms(-1000.0, +1000.0)
                             , tts::randoms(-1000.0, +1000.0)
                             , tts::randoms(-1000.0, +1000.0)
                             )
              )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
  std::integral_constant<int, 1> _1;
  std::integral_constant<int, 2> _2;
  std::integral_constant<int, 3> _3;
  using z_t = eve::as_quaternion_t<T>;
  auto z = z_t(a0, a1, a2, a3);
  auto [t1, t2, t3] = eve::to_euler(z, _3, _2, _1);
  std::cout << t1 << std::endl;
  std::cout << t2 << std::endl;
  std::cout << t3 << std::endl;
  {
    auto z1 = z_t(5, 0, 0, 0);
    auto [t1, t2, t3] = eve::to_euler(z1, _3, _2, _1);
    TTS_EQUAL(t1, eve::zero(eve::as(t1)));
    TTS_EQUAL(t2, eve::zero(eve::as(t2)));
    TTS_EQUAL(t3, eve::zero(eve::as(t3)));
  }
  {
    auto z1 = z_t(5, 5, 0, 0);
    auto [t1, t2, t3] = eve::to_euler(z1, _3, _2, _1);
    TTS_EQUAL(t1, eve::zero(eve::as(t1)));
    TTS_EQUAL(t2, eve::pio_2(eve::as(t2)));
    TTS_EQUAL(t3, -eve::pi(eve::as(t3)));
  }
  {
    auto z1 = z_t(5, 5, 0, 0);
    auto [t1, t2, t3] = eve::to_euler(1.0, _3, _2, _1);
    TTS_EQUAL(t1, eve::zero(eve::as(t1)));
    TTS_EQUAL(t2, eve::zero(eve::as(t2)));
    TTS_EQUAL(t3, eve::zero(eve::as(t3)));
  }
  {
    auto z1 = z_t();
    auto [t1, t2, t3] = eve::to_euler(1.0, _3, _2, _1);
    TTS_EQUAL(t1, eve::zero(eve::as(t1)));
    TTS_EQUAL(t2, eve::zero(eve::as(t2)));
    TTS_EQUAL(t3, eve::zero(eve::as(t3)));
  }
  {
    auto q = eve::euler_to_quaternion(0.2, 1.12, 0.31, _1, _2, _3);
    auto [t1, t2, t3] = eve::to_euler(q, _3, _2, _1);
    std::cout << t1 << std::endl;
    std::cout << t2 << std::endl;
    std::cout << t3 << std::endl;
    auto q1 = eve::euler_to_quaternion(t1, t2, t3, _1, _2, _3);
    std::cout << q << std::endl;
    std::cout << q1<< std::endl;
  }
};
