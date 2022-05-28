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
EVE_TEST( "Check behavior of horner on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::ramp(0))
        )
<typename T>(T const& )
{
  using elt_t = eve::element_type_t<T>;
  using sparse_polynom_t = eve::sparse_polynom<elt_t>;
  using        polynom_t = eve::polynom<elt_t>;
  using pair_t           = typename eve::sparse_polynom<elt_t>::pair_t;
  using monom_t   = eve::monom<elt_t>;
  std::vector<pair_t> c0{{5, 1.5}, {2, 2.3}, {1, 4.1}, {0, -7}};
  sparse_polynom_t p0(c0);
  std::cout<< "p0  "  << p0 << std::endl;
  polynom_t p1{1, 2, 0, 4};
  sparse_polynom_t sp1(p1);
  std::cout << "p1  " << p1 << std::endl;
  std::cout << "sp1 " << sp1 << std::endl;

//   sparse_polynom_t p2(c0, eve::upward);
//   sparse_polynom_t p3{4, 3, 2, 1};
  sparse_polynom_t p4(monom_t(3, 5.0));
  sparse_polynom_t p4b{{3, 5.0f}};
  TTS_EXPECT((p4 == p4b));
  std::cout << p4 << std::endl;
  std::cout << p4b<< std::endl;
//   sparse_polynom_t p5{5.0f, 0, 0, 0};
//   TTS_EQUAL(p1(a0), p0(a0));
//   TTS_EQUAL(p3(a0), p2(a0));

//   auto d = degree(p0);
//   TTS_EQUAL(d, degree(p2));
//   for(int i=0; i <= degree(p0) ; ++i)
//   {
//     TTS_EQUAL(p0[i], elt_t(d-i+1));
//   }
//   for(int i=0; i <= degree(p2) ; ++i)
//   {
//     TTS_EQUAL(p2[i], c0[i]);
//   }
//   for(int i=0; i <= degree(p5) ; ++i)
//   {
//     TTS_EQUAL(p4[i], p5[i]);
//   }
};
