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

EVE_TEST_TYPES("Random check for eve::is_not_denormal", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  using e_t = eve::element_type_t<T>;
  auto vmin = eve::valmin(eve::as<e_t>());
  auto vmax = eve::valmax(eve::as<e_t>());
  if constexpr(eve::floating_value<e_t>)
  {
    auto std_is_not_finite = [](auto e) -> eve::logical<e_t>
      { return  (std::fpclassify(e) == FP_INFINITE) ||  (std::fpclassify(e) == FP_NAN); };
    EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_is_not_finite, eve::is_not_finite );
  }
  else
  {
    auto std_is_not_finite = [](auto e) { return eve::false_(eve::as(e)); };
    EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_is_not_finite, eve::is_not_finite );
  }
};
