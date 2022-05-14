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
EVE_TEST_TYPES( "Check behavior of primitive"
        , eve::test::simd::ieee_reals
        )
  <typename T>(eve::as<T>)
{
  if constexpr(eve::cardinal_v<T> == 1)
  {
    using elt_t = eve::element_type_t<T>;
    using polynom_t = eve::polynom<elt_t>;
    std::vector<elt_t> const c0{1, 2, 3, 4, 5};
    polynom_t p0(c0);
    polynom_t prim = p0;
    for(size_t i=0; i < 8u; ++i)
    {
      prim = eve::primitive(prim);
      eve::inplace(eve::primitive)(p0);
      TTS_EXPECT(prim == p0);
    }
  } else TTS_PASS("");
};

// EVE_TEST_TYPES( "Check behavior of primitive(p, m)"
//               , eve::test::simd::ieee_reals
//               )
//   <typename T>(eve::as<T>)
// {
//   if constexpr(eve::cardinal_v<T> == 1)
//   {
//     using elt_t = eve::element_type_t<T>;
//     using polynom_t = eve::polynom<elt_t>;
//     std::vector<elt_t> const c0{1, 2, 3, 4, 5};
//     polynom_t p0(c0);
//     polynom_t prim = p0;
//     for(size_t i=0; i < 8u; ++i)
//     {
//       prim = eve::primitive(prim);
//       auto primb =  eve::primitive(p0, i+1);
//       TTS_EXPECT(prim == primb);
//     }
//   } else TTS_PASS("");
// };

// EVE_TEST_TYPES( "Check behavior of primitive(p, m, all_)"
//               , eve::test::simd::ieee_reals
//               )
//   <typename T>(eve::as<T>)
// {
//   if constexpr(eve::cardinal_v<T> == 1)
//   {
//     using elt_t = eve::element_type_t<T>;
//     using polynom_t = eve::polynom<elt_t>;
//     std::vector<elt_t> const c0{1, 2, 3, 4, 5};
//     polynom_t p0(c0);
//     polynom_t prim = p0;
//     auto prims = eve::primitive(p0, 7, eve::all);
//       for(size_t i=0; i < prims.size()-1; ++i)
//     {
//       prim = eve::primitive(prim);
//       TTS_EXPECT(prim == prims[i+1]);
//     }
//   } else TTS_PASS("");
// };
