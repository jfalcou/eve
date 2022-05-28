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
EVE_TEST_TYPES( "Check behavior of polynom constructors"
        , eve::test::simd::ieee_reals
        )
<typename T>(eve::as<T>)
{
//   auto print = [](std::string const & title, auto v1){

//     auto s = v1.size()-1;
//     std::cout << title << " = {";
//     if (s > 1) for(size_t i=0; i < s; ++i) std::cout << v1[i] << ", ";
//     if (s >= 1) std::cout << v1[s];
//     std::cout << "}" << std::endl; ;
//   };
  using elt_t = eve::element_type_t<T>;
  using polynom_t = eve::polynom<elt_t>;
//  using monom_t   = eve::monom<elt_t>;
  std::vector<elt_t> c0{1, 2, 0, 4};
  std::vector<elt_t> c1{4, 0, 2, 1};
  std::vector<elt_t> coef0{1, 2, 4};
  std::vector<int>   expo0{3, 2, 0};
  polynom_t p0(c0);
  polynom_t p1(c1, eve::upward);
  TTS_EXPECT(p0 == p1);
  polynom_t p2(expo0, coef0);
  TTS_EXPECT(p0 == p2);
//   polynom_t p4(monom_t(3, 5.0));
//   polynom_t p5{5.0f, 0, 0, 0};
//   TTS_EXPECT(p5 == p4);
};
