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
#include <eve/module/core/constant/nan.hpp>
#include <eve/module/core/constant/true.hpp>
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/regular/is_gez.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/is_nez.hpp>
#include <eve/module/core/regular/is_not_less.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve::detail
{
template<real_value T>
EVE_FORCEINLINE constexpr as_logical_t<T>
is_nltz_(EVE_SUPPORTS(cpu_), T const& a) noexcept
{
  if constexpr( unsigned_value<T> ) return true_(eve::as(a));
  if constexpr( has_native_abi_v<T> )
  {
    if constexpr( scalar_value<T> )
    {
      if constexpr( integral_value<T> ) return is_gez(a);
      else if constexpr( floating_value<T> ) return is_gez(a) || is_nan(a);
    }
    else return is_not_less(a, zero(eve::as(a)));
  }
  else return apply_over(is_nltz, a);
}

// -----------------------------------------------------------------------------------------------
// logical masked case
template<conditional_expr C, real_value U>
EVE_FORCEINLINE auto
is_nltz_(EVE_SUPPORTS(cpu_), C const& cond, U const& u) noexcept
{
  return is_not_less[cond](u, zero(as(u)));
}
}
