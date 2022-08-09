//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/false.hpp>
#include <eve/module/core/regular/frac.hpp>
#include <eve/module/core/regular/is_nez.hpp>

namespace eve::detail
{
template<real_value T>
EVE_FORCEINLINE constexpr auto
is_not_flint_(EVE_SUPPORTS(cpu_), T const& a) noexcept
{
  if constexpr( integral_value<T> ) return false_(eve::as<T>());
  else if constexpr( has_native_abi_v<T> ) return is_nez(frac(a));
  else return apply_over(is_not_flint, a);
}
// -----------------------------------------------------------------------------------------------
// logical masked case
template<conditional_expr C, real_value U>
EVE_FORCEINLINE auto
is_not_flint_(EVE_SUPPORTS(cpu_), C const& cond, U const& u) noexcept
{
  return logical_mask_op(cond, is_not_flint, u);
}
}
