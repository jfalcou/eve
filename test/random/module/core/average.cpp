//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/average.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include "producers.hpp"
#include "generator.hpp"
#include <cmath>

EVE_TEST_TYPES("Random check for eve::average", eve::test::scalar::all_types)
<typename T>(eve::as<T>)
{
  auto std_average = [](auto e) { return std::midpoint(e, eve::one(eve::as(e))); };
  auto  my_average = [](auto e) { return eve::average (e, eve::one(eve::as(e))); };

  eve::uniform_prng<T> p(eve::valmin(eve::as<T>()), eve::valmax(eve::as<T>()));

  if constexpr(eve::floating_value<T>)  EVE_RANGE_CHECK(T, p, std_average, my_average );
  else                                  EVE_RANGE_CHECK_WITH(T, p, std_average, my_average, 0.5);
};
