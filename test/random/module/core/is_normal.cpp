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
#include <cmath>

EVE_TEST_TYPES("Random check for eve::is_normal", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  using e_t = eve::element_type_t<T>;
  auto vmin = eve::valmin(eve::as<e_t>());
  auto vmax = eve::valmax(eve::as<e_t>());
  if constexpr(eve::floating_value<e_t>)
  {
    auto std_is_normal = [](auto e) -> eve::logical<e_t>{ return std::fpclassify(e) == FP_NORMAL; };
    EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_is_normal, eve::is_normal );
  }
  else
  {
    auto std_is_normal = [](auto e) -> eve::logical<e_t> { return e != 0; };
    EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_is_normal, eve::is_normal );
  }
};
