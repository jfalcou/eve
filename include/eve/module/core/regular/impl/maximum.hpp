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
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/max.hpp>

namespace eve::detail
{
  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> maximum_(EVE_REQUIRES(cpu_), O const& opts, wide<T, N> v) noexcept
    requires (O::contains(splat2))
  {
    if constexpr (match_option<condition_key, O, ignore_none_>)
    {
      if constexpr( N::value == 1 ) return v;
      else if constexpr( !is_aggregated_v<abi_t<T, N>> ) return butterfly_reduction(v, eve::max);
      else
      {
        auto [l, h] = v.slice();
        auto r      = maximum[splat](eve::max(l, h));
        return eve::combine(r, r);
      }
    }
    else
    {
      return maximum[splat](if_else(opts[condition_key], v, eve::minorant));
    }
  }

  template<callable_options O, arithmetic_value T>
  EVE_FORCEINLINE element_type_t<T> maximum_(EVE_REQUIRES(cpu_), O const& opts, T v) noexcept
    requires (!O::contains(splat2))
  {
    if constexpr (match_option<condition_key, O, ignore_none_>)
    {
      if constexpr (scalar_value<T>) return v;
      else
      {
        using N   = typename T::cardinal_type;
        using r_t = element_type_t<T>;

        if constexpr( N::value == 1 ) return v.get(0);
        else if constexpr( !is_aggregated_v<abi_t<r_t, N>> ) return butterfly_reduction(v, eve::max).get(0);
        else
        {
          auto [l, h] = v.slice();
          return maximum(eve::max(l, h));
        }
      }
    }
    else if constexpr (scalar_value<T>)
    {
      return if_else(opts[condition_key], v, eve::minorant);
    }
    else
    {
      return maximum(if_else(opts[condition_key], v, eve::minorant));
    }
  }
}
