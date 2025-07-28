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
#include <eve/detail/function/reduce.hpp>
#include <eve/module/core/regular/splat.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/any.hpp>
#include <eve/module/core/regular/add.hpp>
#include <eve/module/core/constant/zero.hpp>

namespace eve::detail
{
  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> sum_(EVE_REQUIRES(cpu_), O const& opts, wide<T, N> v
                            ) noexcept
    requires (O::contains(splat2))
  {
    using C = rbr::result::fetch_t<condition_key, O>;

    if constexpr (std::same_as<C, ignore_none_>)
    {
            if constexpr( N::value == 1 )               return v;
      else  if constexpr( is_emulated_v<abi_t<T, N>>  ) return wide<T,N>( eve::detail::sum(v) );
      else  if constexpr( is_aggregated_v<abi_t<T, N>>)
      {
        auto[l,h] = v.slice();
        const auto r = sum[splat](l + h);
        return eve::combine(r,r);
      }
      else return butterfly_reduction(v, eve::add);
    }
    else
    {
      return sum[splat](if_else(opts[condition_key], v, zero(as(v))));
    }
  }

  template<callable_options O, arithmetic_value T>
  EVE_FORCEINLINE element_type_t<T> sum_(EVE_REQUIRES(cpu_), O const& opts, T v) noexcept
    requires (!O::contains(splat2))
  {
    using C = rbr::result::fetch_t<condition_key, O>;

    if constexpr (std::same_as<C, ignore_none_>)
    {
      if constexpr (scalar_value<T>) return v;
      else
      {
        using N   = typename T::cardinal_type;
        using r_t = element_type_t<T>;

          if constexpr( N::value == 1 )         return v.get(0);
        else  if constexpr( is_emulated_v<abi_t<r_t, N>> )
        {
          r_t r = v.get(0);

          for_<1, 1, N::value>([&](auto i) {
            r += v.get(i);
          });

          return r;
        }
        else  if constexpr( is_aggregated_v<abi_t<r_t, N>> )
        {
          auto[l,h] = v.slice();
          return  sum( l+h );
        }
        else return butterfly_reduction(v, eve::add).get(0);
      }
    }
    else
    {
      const auto cx = opts[condition_key];

      if constexpr (scalar_value<T>) return expand_mask(cx, as(v)) ? v : zero(as(v));
      else                           return sum(if_else(cx, v, zero(as(v))));
    }
  }
}
