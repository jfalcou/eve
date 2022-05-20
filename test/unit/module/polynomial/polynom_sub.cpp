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
EVE_TEST_TYPES( "Check behavior of -"
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
    std::vector<elt_t> const c1{3, 0, 2};
    std::vector<elt_t> const c2{1, 2, 0, 4, 3};
    polynom_t p0(c0);
    polynom_t p1(c1);
    polynom_t p2(c2);
    TTS_EXPECT((p0-p1) == p2);
    monom_t threex2(3.0, 2);
    polynom_t p3{1, 2, 0, 4, 5};
    TTS_EXPECT((p0-threex2) == p3);
    TTS_EXPECT((threex2-p0)== -p3);
    polynom_t p4{1, 2, 3, 4, 3};
    elt_t two(2);
    TTS_EXPECT((p0-two) == p4);
    TTS_EXPECT((two-p0) == -p4);
  } else TTS_PASS("");
};

EVE_TEST_TYPES( "Check behavior of -= "
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
    std::vector<elt_t> const c1{3, 0, 2};
    std::vector<elt_t> const c2{1, 2, 0, 4, 3};
    polynom_t p0(c0);
    polynom_t p1(c1);
    polynom_t p2(c2);
    auto z = p0;
    z-= p1;
    TTS_EXPECT(z == p2);
    monom_t threex2(3.0, 2);
    polynom_t p3{1, 2, 0, 4, 5};
    z = p0;
    z-= threex2;
    TTS_EXPECT(z == p3);
    polynom_t p4{1, 2, 3, 4, 3};
    elt_t two(2);
    z = p0;
    z-= two;
    TTS_EXPECT(z == p4);
  } else TTS_PASS("");
};

EVE_TEST_TYPES( "Check behavior of - in special cases"
        , eve::test::simd::ieee_reals
        )
  <typename T>(eve::as<T>)
{
  if constexpr(eve::cardinal_v<T> == 1)
  {
    using elt_t = eve::element_type_t<T>;
    using polynom_t = eve::polynom<elt_t>;
    using monom_t   = eve::monom<elt_t>;
    polynom_t const p0{1, 2, 3, 4, 5};
    polynom_t const p1{2, 0, 0};
    monom_t m0(2.0, 2);
    auto pz1 = p0-p0;
    auto pz2 = p1-m0;
    auto pz3 = p1-p1;
    auto pz4 = m0-m0;
    TTS_EXPECT(is_null(pz1));
    TTS_EXPECT(is_null(pz2));
    std::cout << pz2 << std::endl;
    TTS_EXPECT(is_null(pz3));
    TTS_EXPECT(is_null(pz4));
  } else TTS_PASS("");
};
