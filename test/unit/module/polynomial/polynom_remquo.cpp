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
      polynom_t p2{1, 2, 1};
      polynom_t p3{3};
      auto [r, q] = remquo(p0, p1);
      TTS_EXPECT(q ==  p2);
      TTS_EXPECT(r ==  p3);
      TTS_EXPECT(p0 == (p1*q+r));
      monom_t x2(3.0, 2);
      auto [r1, q1] = remquo(p0, x2);
      polynom_t p4{1, 2, 3};
      polynom_t p5{4, 5};
      TTS_EXPECT(r1 ==  p5);
      TTS_EXPECT(q1 ==  p4/elt_t(3.0));
      elt_t two(2);
      auto [r2, q2] = remquo(p0, two);
      polynom_t p6 = p0/two;
      polynom_t p7;
      TTS_EXPECT(r2 ==  p7);
      TTS_EXPECT(q2 ==  p6);
      monom_t x4(2.0, 4);
      auto [r3, q3] = remquo(x4, x2);
      monom_t m2(2.0/3.0, 2);
      polynom_t p8;
      TTS_EXPECT(r3 ==  p8);
      TTS_EXPECT(q3 ==  m2);

   }
    {
      auto [r, q] = remquo(p1, p0);
      TTS_EXPECT(q ==  polynom_t());
      TTS_EXPECT(r ==  p1);
      TTS_EXPECT(p1 == (p0*q+r));
      monom_t x2(3.0, 2);
      auto [r1, q1] = remquo(x2, p0);
      TTS_EXPECT(q1 ==  polynom_t());
      TTS_EXPECT(r1 ==  polynom_t(x2));
      elt_t two(2);
      auto [r2, q2] = remquo(two, p0);
      TTS_EXPECT(q2 ==  polynom_t());
      TTS_EXPECT(r2 ==  polynom_t(two));
    }
  } else TTS_PASS("");
};

EVE_TEST_TYPES( "Check behavior of remquo in corner cases"
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
    polynom_t p2{1, 2, 1};
    polynom_t p3{3};
    auto [r, q] = remquo(p0, p1);
    TTS_EXPECT(q ==  p2);
    TTS_EXPECT(r ==  p3);
    TTS_EXPECT(p0 == (p1*q+r));
    monom_t x2(3.0, 2);
    auto [r1, q1] = remquo(p0, x2);
    polynom_t p4{1, 2, 3};
    polynom_t p5{4, 5};
    TTS_EXPECT(r1 ==  p5);
    TTS_EXPECT(q1 ==  p4/elt_t(3));
    elt_t two(2);
    auto [r2, q2] = remquo(p0, two);
    polynom_t p6 = p0/two;
    polynom_t p7;
    TTS_EXPECT(r2 ==  p7);
    TTS_EXPECT(q2 ==  p6);

  } else TTS_PASS("");
};
