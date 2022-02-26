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

EVE_TEST_TYPES("Random check for eve::cosd", eve::test::simd::ieee_reals)
<typename T>(eve::as<T>)
{
  using e_t = eve::element_type_t<T>;
  auto vmin = e_t(-90.);
  auto vmax = e_t(90.);
//  auto std_cosd = [](auto e) -> e_t{ return std::cos(1.7453292519943295769236907684886127134428718885417e-2l*(long double)e); };
  auto std_cosd = [](auto e) -> e_t{ return boost::math::cos_pi(e/180.0l); };
  EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_cosd, eve::cosd );
};
