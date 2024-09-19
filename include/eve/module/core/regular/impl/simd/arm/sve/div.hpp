//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T,N> div_(EVE_REQUIRES(sve_), O const& opts, wide<T, N> a, wide<T, N> b) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    if constexpr (O::contains(saturated))
    {
      return div.behavior(cpu_{}, opts, a, b);
    }
    else if constexpr(O::contains(toward_zero) || O::contains(upward) || O::contains(downward) || O::contains(to_nearest))
    {
      if (floating_value<T>) return round[opts](div(a, b));
      else                   return div.behavior(cpu_{}, opts, a, b);
    }
    else
    {
      if constexpr (sizeof(T) >= 4) return svdiv_x(sve_true<T>(), a, b);
      else                          return div.behavior(cpu_{}, opts, a, b);
    }
  }

  template<callable_options O, conditional_expr C, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T,N> div_(EVE_REQUIRES(sve_), C const& cx, O const& opts, wide<T, N> a, wide<T, N> b) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    if constexpr (O::contains(saturated))
    {
      return div.behavior(cpu_{}, opts, a, b);
    }
    else if constexpr(O::contains(toward_zero) || O::contains(upward) || O::contains(downward) || O::contains(to_nearest))
    {
      if (floating_value<T>) return round[opts](div[cx](a, b));
      else                   return div.behavior(cpu_{}, opts, a, b);
    }
    else
    {
      if constexpr(sizeof(T) >= 4)
      {
        auto alt = alternative(cx, a, as<wide<T, N>> {});
        if constexpr (C::is_complete) return alt;
        else
        {
          if constexpr( !C::has_alternative)
          {
            auto m = expand_mask(cx, as<wide<T, N>> {});
            return svdiv_m(m, a, b);
          }
          else return div.behavior(cpu_{}, opts, a, b);
        }
      }
      else
      {
        return div.behavior(cpu_{}, opts, a, b);
      }
    }
  }
}
