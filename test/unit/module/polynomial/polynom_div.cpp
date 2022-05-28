//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/polynomial.hpp>
#include <cmath>
#include <array>
#include <vector>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check behavior of remquo"
        , eve::test::simd::ieee_reals
        )
  <typename T>(eve::as<T>)
{
  if constexpr(eve::cardinal_v<T> == 1)
  {
    using elt_t = eve::element_type_t<T>;
    using polynom_t = eve::polynom<elt_t>;
    using monom_t   = eve::monom<elt_t>;
    polynom_t p0{1, 2, 3, 4, 5};
    polynom_t p1{1, 0, 2};
    {
      auto [r, q] = remquo(p0, p1);
      auto a = p0/p1;
      auto b = p0%p1;
      TTS_EXPECT(q == a);
      TTS_EXPECT(r == b);
      monom_t x2(2, 3.0);
      auto [r1, q1] = remquo(p0, x2);
      auto a1 = p0/x2;
      auto b1 = p0%x2;
      TTS_EXPECT(q1 == a1);
      TTS_EXPECT(r1 == b1);
      elt_t two(2);
      auto [r2, q2] = remquo(p0, two);
      auto a2 = p0/two;
      auto b2 = p0%two;
      TTS_EXPECT(q2 == a2);
      TTS_EXPECT(r2 == b2);
      monom_t x4(4, 2.0);
      auto [r3, q3] = remquo(x4, x2);
      auto a3 = x4/x2;
      auto b3 = x4%x2;
      TTS_EXPECT(q3 == a3);
      TTS_EXPECT(r3 == b3);
    }
    {
      auto [r, q] = remquo(p1, p0);
      auto a = p1/p0;
      auto b = p1%p0;
      TTS_EXPECT(q == a);
      TTS_EXPECT(r == b);
      monom_t x2(2, 3.0);
      auto [r1, q1] = remquo(x2, p1);
      auto a1 = x2/p1;
      auto b1 = x2%p1;
      TTS_EXPECT(q1 == a1);
      TTS_EXPECT(r1 == b1);
      elt_t two(2);
      auto [r2, q2] = remquo(two, p1);
      auto a2 = two/p1;
      auto b2 = two%p1;
      TTS_EXPECT(q2 == a2);
      TTS_EXPECT(r2 == b2);
      monom_t x4(4, 2.0);
      auto [r3, q3] = remquo(x2, x4);
      auto a3 = x2/x4;
      auto b3 = x2%x4;
      TTS_EXPECT(q3 == a3);
      TTS_EXPECT(r3 == b3);
    }
  }
  else TTS_PASS("");
};

EVE_TEST_TYPES( "Check behavior of /= % = "
        , eve::test::simd::ieee_reals
        )
  <typename T>(eve::as<T>)
{
  if constexpr(eve::cardinal_v<T> == 1)
  {
    using elt_t = eve::element_type_t<T>;
    using polynom_t = eve::polynom<elt_t>;
    using monom_t   = eve::monom<elt_t>;
    elt_t two(2);
    polynom_t p1{1, 0, 2};
    {
      polynom_t p0{1, 2, 3, 4, 5};
      polynom_t p2(p0);
      auto [r, q] = remquo(p0, p1);
      p0 /= p1;
      p2 %= p1;
      TTS_EXPECT(q == p0);
      TTS_EXPECT(r == p2);
    }
    {
      polynom_t p0{1, 2, 3, 4, 5};
      polynom_t p2(p0);
      auto [r, q] = remquo(p0, two);
      p0 /= two;
      p2 %= two;
      TTS_EXPECT(q == p0);
      TTS_EXPECT(r == p2);
    }
    {
      monom_t x0(2, 3.0);
      monom_t m1(4, 2.0);
      monom_t x1(x0);
      auto [r1, q1] = remquo(x0, m1);
      x0 /= m1;
      x1 %= m1;
      TTS_EXPECT(q1 == x0);
      TTS_EXPECT(r1 == x1);
    }
 //    {
//       monom_t x0(2, 3.0);
//       monom_t x1(x0);
//       auto [r1, q1] = remquo(x0, two);
//       x0 /= two;
//       x1 %= two;
//       TTS_EXPECT(q1 == x0);
//       TTS_EXPECT(r1 == x1);
//     }
  }
  else TTS_PASS("");
};
