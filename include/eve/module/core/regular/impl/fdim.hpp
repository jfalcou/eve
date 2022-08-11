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
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/sub.hpp>
#include <eve/platform.hpp>

namespace eve::detail
{
// -----------------------------------------------------------------------------------------------
// regular case
template<real_value T, real_value U>
EVE_FORCEINLINE auto
fdim_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept requires compatible_values<T, U>
{
  return arithmetic_call(fdim, a, b);
}

template<real_value T>
EVE_FORCEINLINE auto
fdim_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept requires has_native_abi_v<T>
{
  auto r = if_else(a >= b, sub(a, b), eve::zero);
  return r;
}

template<conditional_expr C, real_value T, real_value U>
EVE_FORCEINLINE auto
fdim_(EVE_SUPPORTS(cpu_),
      C const& cond,
      T const& a,
      U const& b) noexcept requires compatible_values<T, U>
{
  return mask_op(cond, eve::fdim, a, b);
}

}
