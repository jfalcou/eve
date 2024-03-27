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
  EVE_FORCEINLINE wide<T, N> ceil_(EVE_SUPPORTS(sve_),
                                   O const&,
                                   wide<T, N> const& v) noexcept
  requires sve_abi<abi_t<T, N>>
  {
    return ceil[ignore_none][o](v);
  }

  template<conditional_expr C,floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE auto ceil_(EVE_REQUIRES(sve_),
                             O const&,
                             C const& cond,
                             wide<T, N> const& v) noexcept -> wide<T, N>
  requires sve_abi<abi_t<T, N>>
  {
    if constexpr( C::is_complete)
      return alternative(cond, v,as(v));
    else
    {
      if constexpr(O::contains(tolerance))
        return ceil_(EVE_TARGETS(cpu_), o, v);
      else
        return svrintp_m(alternative(cond, v, as(v)), cond.mask(as(v)), v);
    }
  }
}
