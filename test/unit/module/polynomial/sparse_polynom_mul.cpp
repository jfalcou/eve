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
EVE_TEST_TYPES( "Check behavior of *"
        , eve::test::simd::ieee_reals
        )
  <typename T>(eve::as<T>)
{
  if constexpr(eve::cardinal_v<T> == 1)
  {
    using elt_t = eve::element_type_t<T>;
    using sparse_polynom_t = eve::sparse_polynom<elt_t>;
    using polynom_t = eve::polynom<elt_t>;
    using monom_t   = eve::monom<elt_t>;
    polynom_t const c0{1, 2, 3}; //, 4, 5};
    polynom_t const c1{1, 0, 2};
    elt_t two(2);
    monom_t m2(3.0, 2);
    sparse_polynom_t p0(c0);
    sparse_polynom_t p1(c1);
    std::cout << "c0 " << c0 << std::endl;
    std::cout << "p0 " << p0 << std::endl;
    std::cout << "c1 " << c1 << std::endl;
    std::cout << "p1 "<< p1 << std::endl;
    std::cout << "p0*p1 " << p0*p1 << std::endl;
    std::cout << "c0*c1 " << c0*c1 << std::endl;
    std::cout << "p0*c1 " << p0*c1 << std::endl;
    std::cout << "m2    " << m2    << std::endl;
    std::cout << "c1*m2 " << c1*m2 << std::endl;
    std::cout << "p1*m2 " << p1*m2 << std::endl;
    TTS_EXPECT((p1*m2) == sparse_polynom_t(c1*m2));
    TTS_EXPECT((p0*p1) == sparse_polynom_t(c0*c1));
    TTS_EXPECT((p0*p1) == sparse_polynom_t(c0*c1));
    TTS_EXPECT((c0*p1) == sparse_polynom_t(c0*c1));
    TTS_EXPECT((p0*two) == sparse_polynom_t(c0*two));
    TTS_EXPECT((p0*m2)  == sparse_polynom_t(c0*m2));
    TTS_EXPECT((p0*two) == sparse_polynom_t(c0*two));
  } else TTS_PASS("");
};


EVE_TEST_TYPES( "Check behavior of *= "
        , eve::test::simd::ieee_reals
        )
  <typename T>(eve::as<T>)
{
  if constexpr(eve::cardinal_v<T> == 1)
  {
    using elt_t = eve::element_type_t<T>;
    using sparse_polynom_t = eve::sparse_polynom<elt_t>;
    using polynom_t = eve::polynom<elt_t>;
   using monom_t   = eve::monom<elt_t>;
    polynom_t const c0{1, 2, 3, 4, 5};
    polynom_t const c1{1, 0, 2};
   elt_t two(2);
   monom_t m2(1.0, 2);
    sparse_polynom_t p0(c0);
   sparse_polynom_t p1(c1);
    p0*= p1;
    TTS_EXPECT((p0) == (c0*c1));
    p0 = c0;
    p0*= two;
    TTS_EXPECT((p0) == (c0*two));
    p0 = c0;
    p0*= m2;
    TTS_EXPECT((p0) == (c0*m2));
    p0 = c0;
    p0*= c1;
    TTS_EXPECT((p0) == (c0*c1));
   } else TTS_PASS("");
};
