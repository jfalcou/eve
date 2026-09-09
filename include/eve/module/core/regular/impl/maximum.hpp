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

namespace eve::_
{
  template<callable_options O, arithmetic_scalar_value T, width_type N>
   wide<T, N> maximum_(EVE_REQUIRES(cpu_), O const& opts, wide<T, N> v) noexcept
    requires (O::contains(splat))
  {
    if constexpr (match_option<condition_key, O, ignore_none_>)
    {
      if constexpr( N == 1 ) return v;
      else if constexpr( !aggregated_abi<abi_t<T, N>> ) return butterfly_reduction(v, eve::max);
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
   element_type_t<T> maximum_(EVE_REQUIRES(cpu_), O const& opts, T v) noexcept
    requires (!O::contains(splat))
  {
    if constexpr (match_option<condition_key, O, ignore_none_>)
    {
      if constexpr (scalar_value<T>) return v;
      else
      {
        constexpr auto N = T::size();
        using r_t = element_type_t<T>;

        if constexpr( N == 1 ) return v.get(0);
        else if constexpr( !aggregated_abi<abi_t<r_t, N>> ) return butterfly_reduction(v, eve::max).get(0);
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
