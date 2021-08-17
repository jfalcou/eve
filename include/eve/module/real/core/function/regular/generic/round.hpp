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
#include <eve/function/ceil.hpp>
#include <eve/function/floor.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/roundings.hpp>
#include <eve/function/trunc.hpp>

namespace eve::detail
{
  template<real_value T, decorator D>
  EVE_FORCEINLINE constexpr T round_(EVE_SUPPORTS(cpu_), D const &, T const &a) noexcept
  {
    if constexpr( std::is_same_v<D, eve::upward_type> )
      return eve::ceil(a);
    else if constexpr( std::is_same_v<D, eve::downward_type> )
      return eve::floor(a);
    else if constexpr( std::is_same_v<D, eve::toward_zero_type> )
      return eve::trunc(a);
    else if constexpr( std::is_same_v<D, eve::to_nearest_type> )
      return eve::nearest(a);
  }

  template<real_value T> EVE_FORCEINLINE constexpr T round_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    return eve::nearest(a);
  }

}

