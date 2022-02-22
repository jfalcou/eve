//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/abs.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include "producers.hpp"
#include "generator.hpp"
#include <cmath>

EVE_TEST_TYPES("Random check for eve::abs", eve::test::scalar::all_types)
<typename T>(eve::as<T>)
{
  if constexpr(eve::floating_value<T>)
  {
    auto std_abs = [](auto e) { return (e < 0) ? -e : e; };
    EVE_RANGE_CHECK( T, eve::uniform_prng<T>(-1,1),  std_abs, eve::abs );
  }
  else if constexpr(eve::signed_value<T>)
  {
    auto vmin = eve::valmin(eve::as<T>());
    auto vmax = eve::valmax(eve::as<T>());

    auto std_abs = [](auto e)
    {
      T z = (e < 0) ? -e : e;
      return z < 0 ? eve::valmax(eve::as(e)) : z;
    };

    EVE_RANGE_CHECK ( T, eve::uniform_prng<T>( eve::inc(vmin), vmax ), std_abs, eve::abs );
  }
  else
  {
    auto vmin = eve::valmin(eve::as<T>());
    auto vmax = eve::valmax(eve::as<T>());

    auto std_abs = [](auto e) { return e; };
    EVE_RANGE_CHECK ( T, eve::uniform_prng<T>(vmin,vmax), std_abs, eve::abs );
  }
};
