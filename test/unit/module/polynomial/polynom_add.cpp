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
EVE_TEST_TYPES( "Check behavior of +"
        , eve::test::simd::ieee_reals
        )
  <typename T>(eve::as<T>)
{
  if constexpr(eve::cardinal_v<T> == 1)
  {
    using elt_t = eve::element_type_t<T>;
    using polynom_t = eve::polynom<elt_t>;
    using monom_t   = eve::monom<elt_t>;
    std::vector<elt_t> const c0{1, 2, 3, 4, 5};
    std::vector<elt_t> const c1{1, 0, 2};
    std::vector<elt_t> const c2{1, 2, 4, 4, 7};
    elt_t two(2);
    monom_t m2(1.0, 2);
    monom_t m4(2.0, 4);
    polynom_t m6{2.0, 0.f, 1.0f, 0.f, 0.f};
    polynom_t p0(c0);
    polynom_t p1(c1);
    polynom_t p2b(c2);
    polynom_t p2 =  p0+two;
    polynom_t p3 =  p0+m2;
    polynom_t pt{1.0f, 0.0f, 2.0f};
    TTS_EXPECT((p2b) == (p0+p1));
    polynom_t p4 =  elt_t(2)+p0;
    polynom_t p5 =  m2+p0;
    TTS_EXPECT(p2 == p4);
    TTS_EXPECT(p3 == p5);
    polynom_t p6 =  p0+m2;
    polynom_t p7 =  p0+two;
    TTS_EXPECT(p6 == p5);
    TTS_EXPECT(p7 == p4);
    TTS_EXPECT((m2+m4) == m6);
    TTS_EXPECT((m2+m2) == polynom_t(two*m2));
    TTS_EXPECT((m2+two)== pt);
  } else TTS_PASS("");
};


EVE_TEST_TYPES( "Check behavior of += "
        , eve::test::simd::ieee_reals
        )
  <typename T>(eve::as<T>)
{
  if constexpr(eve::cardinal_v<T> == 1)
  {
    using elt_t = eve::element_type_t<T>;
    using polynom_t = eve::polynom<elt_t>;
    using monom_t   = eve::monom<elt_t>;
    std::vector<elt_t> const c0{1, 2, 3, 4, 5};
    std::vector<elt_t> const c1{1, 0, 2};
    elt_t two(2);
    monom_t m2(1.0, 2);
    monom_t m4(2.0, 4);
    monom_t m6(2.0, 6);
    polynom_t p0(c0);
    polynom_t p1(c1);
    polynom_t p2 =  p0+two;
    polynom_t p3 =  p2+m2;
    std::cout << "p0         " << p0 << std::endl;
    std::cout << "m2         " << polynom_t(m2) << std::endl;
    std::cout << "p3         " << p3 << std::endl;
    std::cout << std::endl;

    polynom_t p0b(p0);
    polynom_t p0c(p0);
    polynom_t p0d(p0);
    p0b += two;
    p0c +=  m2;
    std::cout << "p0         " << p0 << std::endl;
    std::cout << "p0d avant  " << p0d << std::endl;
    std::cout << "p1  avant  " << p1 << std::endl;
    p0d +=  p1;
    std::cout << "p0d apres  " << p0d << std::endl;
    polynom_t p4 =  elt_t(2)+p0;
    polynom_t p5 =  m2+p0;
    TTS_EXPECT(p0b == p4);
    TTS_EXPECT(p0c == p5);
    TTS_EXPECT((p3) == (p0d));
    std::cout << "p0d       " << p0d << std::endl;
    std::cout << "p1        " << p1 << std::endl;
    std::cout << "p2        " << p2  << std::endl;
    std::cout << "p3        " << p3  << std::endl;
    std::cout << "p2+p3     " << p2+p3 << std::endl;

  } else TTS_PASS("");
};


EVE_TEST_TYPES( "Check behavior of + in special cases"
        , eve::test::simd::ieee_reals
        )
  <typename T>(eve::as<T>)
{
  if constexpr(eve::cardinal_v<T> == 1)
  {
    using elt_t = eve::element_type_t<T>;
    using polynom_t = eve::polynom<elt_t>;
    using monom_t   = eve::monom<elt_t>;
    std::vector<elt_t> const c0{1, 2, 3, 4, 5};
    std::vector<elt_t> const c1{1, 0, 2};
    monom_t mz(1.0, 2);
    monom_t mz1(-1.0, 2);
    monom_t mx(2.0, 0);
    elt_t two(-2);
    polynom_t p0(c0);
    polynom_t p1 = -p0;
    polynom_t pz =  p0+p1;
    auto p2 =  mz1+mz;
    auto p3 =  mx+two;
    TTS_EXPECT(is_null(pz));
    TTS_EXPECT(is_null(p2));
    TTS_EXPECT(is_null(p3));
  } else TTS_PASS("");
};
