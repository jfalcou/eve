//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/algo/views/iota.hpp>
#include <eve/algo/copy.hpp>
#include <eve/algo/transform.hpp>
#include <eve/module/polynomial.hpp>
#include <cmath>
#include <array>
#include <vector>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check behavior of opertor() : evaluation"
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
    monom_t   m2(3.0, 4);
    TTS_EQUAL(p0(elt_t(1)), elt_t(15));
    TTS_EQUAL(p1(elt_t(1)), elt_t(3));
    TTS_EQUAL(p0(elt_t(1)), elt_t(15));
    TTS_EQUAL(p1(elt_t(2)), elt_t(6));
    TTS_EQUAL(p1(elt_t(3)), elt_t(11));
    TTS_EQUAL(m2(elt_t(1)), elt_t(3.0));
    TTS_EQUAL(m2(elt_t(2)), elt_t(48));
    std::vector<elt_t> z{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto z1 = z;
    std::vector<elt_t> pz{5,  15,  57,  179,  453,  975,  1865,  3267,  5349,  8303};
    std::vector<elt_t> mz{0, 3, 48, 243, 768, 1875, 3888, 7203, 12288, 19683};
    auto z2 = z;
    auto p0z =  p0(z);
    auto zz = eve::polyval(p0, z);
    eve::inplace(eve::polyval)(p0, z1);
    auto m2z = eve::polyval(m2, z);
    eve::inplace(eve::polyval)(m2, z2);
    for(int i=0; i < 10 ; ++i){
      TTS_EQUAL(p0z[i], pz[i]);
      TTS_EQUAL(zz[i],  pz[i]);
      TTS_EQUAL(z1[i],  pz[i]);
      TTS_EQUAL(m2z[i], mz[i]);
      TTS_EQUAL(z2[i],  mz[i]);
    }
  }
  else TTS_PASS("");
};

EVE_TEST_TYPES( "Check behavior of opertor[] : coefficients"
        , eve::test::simd::ieee_reals
        )
  <typename T>(eve::as<T>)
{
  if constexpr(eve::cardinal_v<T> == 1)
  {
    using elt_t = eve::element_type_t<T>;
    using polynom_t = eve::polynom<elt_t>;
    std::vector<elt_t> v{1, 2, 3, 4, 5};
    polynom_t p0(v);
    for(int i=0; i < degree(p0) ; ++i) TTS_EQUAL(p0[i], v[degree(p0)-i]);
  }
  else TTS_PASS("");
};

EVE_TEST_TYPES( "Check behavior of opertor == ."
        , eve::test::simd::ieee_reals
        )
  <typename T>(eve::as<T>)
{
  if constexpr(eve::cardinal_v<T> == 1)
  {
    using elt_t = eve::element_type_t<T>;
    using polynom_t = eve::polynom<elt_t>;
    polynom_t p0{1, 2, 3, 4, 5};
    TTS_EXPECT(p0 == p0);
    TTS_EXPECT(p0 != (p0+p0));
  }
  else TTS_PASS("");
};
