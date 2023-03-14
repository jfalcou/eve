//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/regular/acos.hpp>
#include <eve/module/math/regular/radinpi.hpp>

namespace eve::detail
{
template<ordered_value T, decorator D>
EVE_FORCEINLINE constexpr auto
acospi_(EVE_SUPPORTS(cpu_), D const& d, T const& a) noexcept
    requires(is_one_of<D>(types<regular_type, raw_type> {}))
{
  if constexpr( has_native_abi_v<T> ) { return radinpi(d(acos)(a)); }
  else { return apply_over(d(acospi), a); }
}

template<value T>
EVE_FORCEINLINE constexpr auto
acospi_(EVE_SUPPORTS(cpu_), T const& a) noexcept
{
  if constexpr( has_native_abi_v<T> ) { return radinpi(acos(a)); }
  else { return apply_over(acospi, a); }
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, value U>
EVE_FORCEINLINE auto
acospi_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, eve::acospi, t);
}

template<conditional_expr C, decorator D, value U>
EVE_FORCEINLINE auto
acospi_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, U const& t) noexcept
{
  return mask_op(cond, d(eve::acospi), t);
}
}
