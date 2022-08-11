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
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/regular/bit_notand.hpp>
#include <eve/module/core/regular/inc.hpp>

namespace eve::detail
{

template<integral_real_value T>
EVE_FORCEINLINE constexpr T
firstbitunset_(EVE_SUPPORTS(cpu_), T const& a0) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    if constexpr( scalar_value<T> ) { return ~a0 & inc(a0); }
    else { return bit_notand(a0, inc(a0)); }
  }
  else return apply_over(firstbitunset, a0);
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, unsigned_value U>
EVE_FORCEINLINE auto
firstbitunset_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, firstbitunset, t);
}
}
