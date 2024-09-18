//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<callable_options O, arithmetic_scalar_value T, typename N, conditional_expr C>
  EVE_FORCEINLINE wide<T, N> add_(EVE_REQUIRES(sve_), C const& mask, O const& opts, wide<T, N> v, wide<T, N> w) noexcept
  requires sve_abi<abi_t<T, N>>
  {
    auto const alt = alternative(mask, v, as(v));

    // ignore all just return alternative
    if constexpr( C::is_complete ) return alt;

    if constexpr(((O::contains(downward) || O::contains(upward)) && floating_value<T>) ||
                 (O::contains(saturated2) && std::integral<T>))
    {
      return add.behavior(cpu_{}, opts, v, w);
    }
    else
    {
      //  if saturated on integer, we don't have masked op so we delegate
      if        constexpr (O::contains(saturated) && std::integral<T>) return add.behavior(cpu_{}, opts, v, w);
      //  If not, we can mask if there is no alterative value
      else  if  constexpr (!C::has_alternative)
      {
        auto m = expand_mask(mask, as(v));
        return svadd_m(m,v,w);
      }
      // If not, we delegate to the automasking
      else
      {
        return add.behavior(cpu_{}, opts, v, w);
      }
    }
  }

  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> add_(EVE_REQUIRES(sve_), O const& opts, wide<T, N> v, wide<T, N> w) noexcept
  requires sve_abi<abi_t<T, N>>
  {
    // We call the saturated add if required or we just go to the common case of doing v+w
    if constexpr(((O::contains(downward) || O::contains(upward)) && floating_value<T>))
    {
      return add.behavior(cpu_{}, opts, v, w);
    }
    else if constexpr(O::contains(saturated2) && std::integral<T>)
    {
      return svqadd(v, w);
    }
    else
    {
      return svadd_x(sve_true<T>(), v, w);
    }
  }

}
