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
#include <eve/traits/overload/supports.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/module/core/regular/reduce.hpp>
#include <eve/module/core/regular/splat.hpp>
#include <eve/module/core/constant/valmax.hpp>

namespace eve::detail
{
  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> minimum_(EVE_REQUIRES(cpu_), O const& opts, wide<T, N> v) noexcept
    requires (O::contains(splat2))
  {
    using C = rbr::result::fetch_t<condition_key, O>;

    if constexpr (std::same_as<C, ignore_none_>)
    {
      if constexpr( N::value == 1 ) return v;
      else if constexpr( !is_aggregated_v<abi_t<T, N>> ) return butterfly_reduction(v, eve::min);
      else
      {
        auto [l, h] = v.slice();
        auto r      = minimum[splat](eve::min(l, h));
        return eve::combine(r, r);
      }
    }
    else
    {
      return minimum[splat](if_else(opts[condition_key], v, eve::valmax));
    }
  }

  template<callable_options O, arithmetic_value T>
  EVE_FORCEINLINE element_type_t<T> minimum_(EVE_REQUIRES(cpu_), O const& opts, T v) noexcept
    requires (!O::contains(splat2))
  {
    using C = rbr::result::fetch_t<condition_key, O>;

    if constexpr (std::same_as<C, ignore_none_>)
    {
      if constexpr (arithmetic_scalar_value<T>)
      {
        return v;
      }
      else
      {
        using N = typename T::cardinal_type;

        if      constexpr (N::value == 1) return v.get(0);
        else if constexpr (!is_aggregated_v<abi_t<element_type_t<T>, N>>)
        {
          return butterfly_reduction(v, eve::min).get(0);
        }
        else
        {
          auto [l, h] = v.slice();
          return minimum(eve::min(l, h));
        }
      }
    }
    else if constexpr (arithmetic_scalar_value<T>)
    {
      return if_else(opts[condition_key], v, eve::valmax(eve::as(v)));
    }
    else
    {
      return minimum(if_else(opts[condition_key], v, eve::valmax));
    }
  }
}
