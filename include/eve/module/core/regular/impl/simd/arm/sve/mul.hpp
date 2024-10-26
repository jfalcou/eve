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
  EVE_FORCEINLINE auto mul_(EVE_REQUIRES(sve_), O const& opts, wide<T, N> a, wide<T, N> b) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    if constexpr(((O::contains(lower) || O::contains(upper)) && floating_value<T>)||
                 O::contains(widen))
    {
      return mul.behavior(cpu_{}, opts, a, b);
    }
    else if constexpr (O::contains(saturated) && std::integral<T>) return mul.behavior(cpu_{}, opts, a, b);
    else                                                            return wide<T,N>(svmul_x(sve_true<T>(), a, b));
  }

  template<callable_options O, conditional_expr C, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE auto mul_(EVE_REQUIRES(sve_), C const& mask, O const& opts, wide<T, N> a, wide<T, N> b) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    if constexpr(O::contains(widen))
    {
      return mul.behavior(cpu_{}, opts, a, b);
    }
    else
    {
      auto const alt = alternative(mask, a, as{a});

      // ignore all just return alternative
      if constexpr( C::is_complete ) return alt;
      if constexpr(((O::contains(lower) || O::contains(upper)) && floating_value<T>) ||
                   (O::contains(saturated) && std::integral<T>) || O::contains(widen))
      {
        return mul.behavior(cpu_{}, opts, a, b);
      }
      else
      {
        //  if saturated on integer, we don't have masked op so we delegate
        if        constexpr (O::contains(saturated) && std::integral<T>)
          return mul.behavior(cpu_{}, opts, a, b);
        //  If not, we can mask if there is no alterative value
        else  if  constexpr (!C::has_alternative && (sizeof(T) > 1))
        {
          auto m = expand_mask(mask, as{a});
          return wide<T,N>(svmul_m(m, a, b));
        }
        // If not, we delegate to the automasking
        else
        {
          return mul.behavior(cpu_{}, opts, a, b);
        }

      }
    }
  }
}
