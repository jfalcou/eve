//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/traits/common_value.hpp>
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
template<ordered_value T, ordered_value U>
EVE_FORCEINLINE auto
fdim_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept
-> common_value_t<T, U>
{
  return arithmetic_call(fdim, a, b);
}

template<ordered_value T>
EVE_FORCEINLINE auto
fdim_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept
requires has_native_abi_v<T>
{
  return if_else(a >= b, sub(a, b), eve::zero);
}

template<conditional_expr C, ordered_value T, ordered_value U>
EVE_FORCEINLINE auto
fdim_(EVE_SUPPORTS(cpu_),
      C const& cond,
      T const& a,
      U const& b) noexcept
->decltype(fdim(a, b))
{
  return mask_op(cond, eve::fdim, a, b);
}

}
