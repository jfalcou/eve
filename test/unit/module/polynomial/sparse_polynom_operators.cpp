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
    using sparse_polynom_t = eve::sparse_polynom<elt_t>;
    polynom_t p0{1, 2, 3, 4, 5};
    polynom_t p1{1, 0, 2};
    sparse_polynom_t sp0(p0);
    sparse_polynom_t sp1(p1);
    TTS_EQUAL(p1(elt_t(1)), sp1(elt_t(1)));
    TTS_EQUAL(p0(elt_t(1)), sp0(elt_t(1)));
    TTS_EQUAL(p1(elt_t(2)), sp1(elt_t(2)));
    TTS_EQUAL(p1(elt_t(3)), sp1(elt_t(3)));
    std::vector<elt_t> z{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto z1 = z;
    auto z2 = z;
    std::vector<elt_t> pz{5,  15,  57,  179,  453,  975,  1865,  3267,  5349,  8303};
    auto p0z =  p0(z);
    auto sp0z =  sp0(z);
    auto zz1 = eve::polyval(p0, z);
    auto zz2 = eve::polyval(sp0, z);
    eve::inplace(eve::polyval)(sp0, z1);
    eve::inplace(eve::polyval)(p0, z2);
    for(int i=0; i < 10 ; ++i){
      TTS_EQUAL(p0z[i], sp0z[i]);
      TTS_EQUAL(z1, z2);
      TTS_EQUAL(zz1, zz2);
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
    using sparse_polynom_t = eve::sparse_polynom<elt_t>;
    eve::polynom<elt_t> p0{1, 2, 3, 4, 5};
    sparse_polynom_t sp0(p0);
    for(int i=0; i <= degree(p0) ; ++i) TTS_EQUAL(p0[i], sp0[i]);
  }
  else TTS_PASS("");
};

// EVE_TEST_TYPES( "Check behavior of opertor == ."
//         , eve::test::simd::ieee_reals
//         )
//   <typename T>(eve::as<T>)
// {
//   if constexpr(eve::cardinal_v<T> == 1)
//   {
//     using elt_t = eve::element_type_t<T>;
//     using sparse_polynom_t = eve::sparse_polynom<elt_t>;
//     sparse_polynom_t p0{1, 2, 3, 4, 5};
//     TTS_EXPECT(p0 == p0);
//     TTS_EXPECT(p0 != (p0+p0));
//   }
//   else TTS_PASS("");
// };
