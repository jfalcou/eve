//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/ceil.hpp>
#include <eve/module/core/regular/floor.hpp>
#include <eve/module/core/regular/nearest.hpp>
#include <eve/module/core/regular/trunc.hpp>
#include <eve/module/core/regular/roundings.hpp>
#include <eve/module/core/regular/derivative.hpp>

namespace eve::detail
{
  template<real_value T, decorator D>
  EVE_FORCEINLINE constexpr T round_(EVE_SUPPORTS(cpu_), D const &, T const &a) noexcept
  requires(is_one_of<D>(types<upward_type, downward_type, toward_zero_type, to_nearest_type, diff_type<1>> {}))
  {
    if constexpr( std::is_same_v<D, eve::upward_type> )
      return eve::ceil(a);
    else if constexpr( std::is_same_v<D, eve::downward_type> )
      return eve::floor(a);
    else if constexpr( std::is_same_v<D, eve::toward_zero_type> )
      return eve::trunc(a);
    else if constexpr( std::is_same_v<D, eve::to_nearest_type> )
      return eve::nearest(a);
    else return zero(as(a));
  }

  template<real_value T> EVE_FORCEINLINE constexpr T round_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    return eve::nearest(a);
  }

}
