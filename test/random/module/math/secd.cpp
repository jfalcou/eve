//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/module/math.hpp>
#include "producers.hpp"
#include "generator.hpp"
#include <cmath>
#include <eve/detail/function/tmp/boost_math_cospi.hpp>


// EVE_TEST_TYPES("Random check for eve::secd", eve::test::simd::ieee_reals)
// <typename T>(eve::as<T>)
// {
//   using e_t = eve::element_type_t<T>;
//   auto vmin = e_t(-45.);
//   auto vmax = e_t(45.);
//   auto std_secd = [](auto e) -> e_t { return eve::rec(std::cos(1.7453292519943295769236907684886127134428718885417e-2l*(long double)e)); };
//   EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_secd, eve::secd );
// };

EVE_TEST_TYPES("Random check for eve::secd", eve::test::simd::ieee_reals)
<typename T>(eve::as<T>)
{
  using e_t = eve::element_type_t<T>;
  auto std_secd = [](auto e) -> e_t{ return 1.0l/(boost::math::cos_pi(((long double)e)/180.0l)); };
  {
    auto vmin = e_t(-45.);
    auto vmax = e_t(45.);
    EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_secd, eve::secd );
  }
  {
    auto vmin = e_t(-90.);
    auto vmax = e_t(90.);
    EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_secd, eve::secd );
  }
  {
    auto vmin = e_t(-180.);
    auto vmax = e_t(180.);
    EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_secd, eve::secd );
  }
  {
    auto vmin = e_t(-5000.);
    auto vmax = e_t(5000.);
    EVE_ULP_RANGE_CHECK_WITH( T, eve::uniform_prng<e_t>(vmin, vmax),  std_secd, eve::secd,  32);
  }

};
