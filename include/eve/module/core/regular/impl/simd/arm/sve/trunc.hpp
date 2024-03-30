//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/arm/sve/sve_true.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<floating_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> trunc_(EVE_REQUIRES(sve_),
                                    O          const& opts,
                                    wide<T, N> const& v) noexcept
  requires sve_abi<abi_t<T, N>>
  {
    if  constexpr(!O::contains(tolerance)) return svrintz_z(sve_true<T>(), v);
    else                                   return trunc.behavior(cpu_{}, opts, v);
  }

  template<conditional_expr C,floating_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> trunc_(EVE_REQUIRES(sve_),
                                    C          const& cond,
                                    O          const& opts,
                                    wide<T, N> const& v) noexcept
  requires sve_abi<abi_t<T, N>>
  {
    auto alt = alternative(cond, v, as(v));

    if      constexpr( C::is_complete)          return alt;
    else if constexpr(!O::contains(tolerance))  return svrintz_m(alt, cond.mask(as(v)), v);
    else                                        return trunc.behavior(cpu_{}, opts, v);
  }
}
