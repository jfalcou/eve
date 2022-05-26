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
    using sparse_polynom_t = eve::sparse_polynom<elt_t>;
    using monom_t   = eve::monom<elt_t>;
    polynom_t p0{1, 2, 3, 0, 5};
    polynom_t p1{1, -3, 2, 4};
    elt_t two(2);
    monom_t m2(1.0, 2);
    sparse_polynom_t sp0(p0);
    sparse_polynom_t sp1(p1);
    std::cout << "p0  " << p0 << std::endl;
    std::cout << "sp0 " << sp0 << std::endl;
    std::cout << "p1  " << p1 << std::endl;
    std::cout << "sp1 " << sp1 << std::endl;
    std::cout << "sp1-sp0" << sp1-sp0 << std::endl;
    std::cout << " ====================================== " << std::endl; 
    TTS_EXPECT(sparse_polynom_t(p0-p1) == (sp0-sp1));
    TTS_EXPECT(sparse_polynom_t(p0-m2) == (sp0-m2));
    TTS_EXPECT(sparse_polynom_t(p0-two) == (sp0-two));
    TTS_EXPECT((sp1-sp0) == -(sp0-sp1));
    TTS_EXPECT((m2-sp0) == -(sp0-m2));
    TTS_EXPECT((two-sp0) == -(sp0-two));
  } else TTS_PASS("");
};


// EVE_TEST_TYPES( "Check behavior of -= "
//         , eve::test::simd::ieee_reals
//         )
//   <typename T>(eve::as<T>)
// {
//   if constexpr(eve::cardinal_v<T> == 1)
//   {
//     using elt_t = eve::element_type_t<T>;
//     using polynom_t = eve::polynom<elt_t>;
//     using sparse_polynom_t = eve::sparse_polynom<elt_t>;
//     using monom_t   = eve::monom<elt_t>;
//     polynom_t p0{1, 2, 3, 0, 5};
//     polynom_t p1{1, -3, 2, 4};
//     elt_t two(2);
//     monom_t m2(1.0, 2);
//     sparse_polynom_t sp0(p0);
//     sparse_polynom_t sp1(p1);
//     auto sum(sp0);
//     sum -= sp1;
//     TTS_EXPECT(sparse_polynom_t(p0-p1) == sum);
//     sum = p0;
//     sum -= m2;
//     TTS_EXPECT(sparse_polynom_t(p0-m2) == sum);
//     sum = p0;
//     sum -= two;
//     TTS_EXPECT(sparse_polynom_t(p0-two) ==sum);
//   } else TTS_PASS("");
// };


// EVE_TEST_TYPES( "Check behavior of - in special cases"
//         , eve::test::simd::ieee_reals
//         )
//   <typename T>(eve::as<T>)
// {
//   if constexpr(eve::cardinal_v<T> == 1)
//   {
//     using elt_t = eve::element_type_t<T>;
//     using sparse_polynom_t = eve::sparse_polynom<elt_t>;
//     using polynom_t = eve::polynom<elt_t>;
//     polynom_t  p0{1, 2, 3, 4, 5};
//     polynom_t  p1(p0);

//     sparse_polynom_t pz =  p0-p1;
//     TTS_EXPECT(is_null(pz));
//   } else TTS_PASS("");
// };
