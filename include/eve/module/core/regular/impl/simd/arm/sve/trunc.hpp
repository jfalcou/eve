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
                                    wide<T, N> w) noexcept
  requires sve_abi<abi_t<T, N>>
  {
    return trunc_(adl_helper_t{}, sve_{}, ignore_none, opts, w);
  }

  template<conditional_expr C,floating_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> trunc_(EVE_REQUIRES(sve_),
                                    C          const& cond,
                                    O          const& opts,
                                    wide<T, N> w) noexcept
  requires sve_abi<abi_t<T, N>>
  {
    auto alt = alternative(cond, w, as{w});

    if      constexpr(C::is_complete && !C::is_inverted)  return alt;
    else if constexpr(!O::contains(almost  ))            return svrintz_m(alt, cond.mask(as{w}), w);
    else                                                  return trunc.behavior(as<wide<T, N>>{}, cpu_{}, opts, w);
  }
}
