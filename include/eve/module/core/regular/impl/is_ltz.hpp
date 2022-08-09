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
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/regular/is_less.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve::detail
{
template<real_value T>
EVE_FORCEINLINE constexpr as_logical_t<T>
is_ltz_(EVE_SUPPORTS(cpu_), T const& a) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    if constexpr( unsigned_value<T> ) return false_(eve::as(a));
    else return a < zero(eve::as(a));
  }
  else return apply_over(is_ltz, a);
}

// -----------------------------------------------------------------------------------------------
// logical masked case
template<conditional_expr C, real_value U>
EVE_FORCEINLINE auto
is_ltz_(EVE_SUPPORTS(cpu_), C const& cond, U const& u) noexcept
{
  return is_less[cond](u, zero(as(u)));
}
}
