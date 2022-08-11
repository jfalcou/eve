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
#include <eve/module/core/decorator/roundings.hpp>
#include <eve/module/core/regular/ceil.hpp>
#include <eve/module/core/regular/derivative.hpp>
#include <eve/module/core/regular/floor.hpp>
#include <eve/module/core/regular/nearest.hpp>
#include <eve/module/core/regular/trunc.hpp>

namespace eve::detail
{
template<real_value T, decorator D>
EVE_FORCEINLINE constexpr T
round_(EVE_SUPPORTS(cpu_), D const&, T const& a) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type, toward_zero_type, to_nearest_type> {}))
{
  if constexpr( std::is_same_v<D, eve::upward_type> ) return eve::ceil(a);
  else if constexpr( std::is_same_v<D, eve::downward_type> ) return eve::floor(a);
  else if constexpr( std::is_same_v<D, eve::toward_zero_type> ) return eve::trunc(a);
  else if constexpr( std::is_same_v<D, eve::to_nearest_type> ) return eve::nearest(a);
}

template<real_value T>
EVE_FORCEINLINE constexpr T
round_(EVE_SUPPORTS(cpu_), T const& a) noexcept
{
  return eve::nearest(a);
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, real_value U>
EVE_FORCEINLINE auto
round_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::round, t);
}

template<conditional_expr C, decorator D, real_value U>
EVE_FORCEINLINE auto
round_(EVE_SUPPORTS(cpu_), C const& cond, D const& d, U const& t) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type, toward_zero_type, to_nearest_type> {}))
{
  return mask_op(cond, d(eve::round), t);
}

}
