//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/arch/arm/sve/sve_true.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> ceil_(EVE_REQUIRES(sve_),
                                   O const& opts,
                                   wide<T, N> const& v) noexcept
  requires sve_abi<abi_t<T, N>>
  {
    return ceil_(adl_helper_t{}, sve_{}, ignore_none, opts, v);
  }

  template<conditional_expr C,floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE auto ceil_(EVE_REQUIRES(sve_),
                             O const& opts,
                             C const& cond,
                             wide<T, N> const& v) noexcept -> wide<T, N>
  requires sve_abi<abi_t<T, N>>
  {
    auto alt = alternative(cond, v, as(v));

    if      constexpr(C::is_complete && !C::is_inverted) return alt;
    else if constexpr(!O::contains(tolerance))           return svrintp_m(alt, cond.mask(as(v)), v);
    else                                                 return ceil.behavior(cpu_{}, opts, v);
  }
}
