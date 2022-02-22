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

EVE_TEST_TYPES("Random check for eve::prev", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  using e_t = eve::element_type_t<T>;
  auto vmin = eve::valmin(eve::as<e_t>());
  auto vmax = eve::valmax(eve::as<e_t>());

  if constexpr(eve::floating_value<e_t>)
  {
    auto std_prev = [](auto e)
      {
        return    (e == eve::minf(eve::as<e_t>()))
        ? eve::nan(eve::as<e_t>())
        : std::nextafter(e, eve::minf(eve::as<e_t>()));
      };
    EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_prev, eve::prev );
  }
  else
  {
    auto std_prev = [](auto e) -> e_t{ return e == eve::valmin(eve::as<e_t>()) ? eve::valmax(eve::as<e_t>()): e-1; };
    EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_prev, eve::prev );
  }
};
