//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/platform.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/mone.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/module/core/regular/signnz.hpp>

namespace eve::detail
{
template<ordered_value T>
EVE_FORCEINLINE T
sign_(EVE_SUPPORTS(cpu_), T const& a) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    if constexpr( unsigned_value<T> ) return one[is_nez(a)](eve::as(a));
    else  if constexpr( floating_value<T> ) return signnz[is_nez(a)](a);
    else
    {
      constexpr auto tgt = as<T>{};
      auto that = eve::max(eve::min(a,one(tgt)), mone(tgt));
      return that;
    }
  }
  else { return apply_over(sign, a); }
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, ordered_value U>
EVE_FORCEINLINE auto
sign_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
{
  return mask_op(cond, sign, t);
}
}
