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

EVE_TEST_TYPES("Random check for eve::next", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  using e_t = eve::element_type_t<T>;
  auto vmin = eve::valmin(eve::as<e_t>());
  auto vmax = eve::valmax(eve::as<e_t>());

  if constexpr(eve::floating_value<e_t>)
  {
    auto std_next = [](auto e)
      {
        return    (e ==  eve::inf(eve::as<e_t>()))
        ? eve::nan(eve::as<e_t>())
        : std::nextafter(e, eve::inf(eve::as<e_t>()));
      };
    EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_next, eve::next );
  }
  else
  {
    auto std_next = [](auto e) -> e_t{ return e == eve::valmax(eve::as<e_t>()) ? eve::valmin(eve::as<e_t>()): e+1; };
    EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_next, eve::next );
  }

  auto std_pedantic_next = [](auto e) -> e_t{
    if constexpr(eve::floating_value<T>)
    {
      return (e == 0) && eve::is_negative(e) ?
      e_t(0)
      : ( e ==  eve::inf(eve::as<e_t>())) ?
      eve::nan(eve::as<e_t>())
      : std::nextafter(e, eve::inf(eve::as<e_t>()));
    }
    else
    {
      return e == eve::valmax(eve::as(e)) ? e : e+1;
    }
  };
  EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax),  std_pedantic_next, eve::pedantic(eve::next) );

  auto std_saturated_next = [](auto e) -> e_t {
    if constexpr(eve::floating_value<T>)
    {
      return (e ==  eve::inf(eve::as<e_t>()))
      ?  eve::nan(eve::as<e_t>())
      : std::nextafter(e, eve::inf(eve::as<e_t>()));
    }
    else
    {
      return e == eve::valmax(eve::as(e)) ? e : e+1;
    }
  };
  EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(vmin, vmax), std_saturated_next, eve::saturated(eve::next));
};
