//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include "producers.hpp"
#include "generator.hpp"
#include <bit>

EVE_TEST_TYPES("Random check for eve::minus", eve::test::simd::signed_types)
<typename T>(eve::as<T>)
{
  using e_t = eve::element_type_t<T>;
  auto vmin = eve::valmin(eve::as<e_t>());
  auto vmax = eve::valmax(eve::as<e_t>());
  auto std_minus = [vmin, vmax](auto e) -> e_t { return (e == vmin) ? vmax :-e; };
  auto std_saturated_minus = [](auto e) -> e_t { return -e; };
  EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin+1, vmax), std_minus, eve::minus );
  EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin,   vmax), std_saturated_minus, eve::saturated(eve::minus) );
 };
