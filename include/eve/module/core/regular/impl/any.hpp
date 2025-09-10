//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/top_bits.hpp>
#include <eve/concept/value.hpp>
#include <eve/conditional.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton.hpp>

namespace eve::detail
{
template <callable_options O, logical_simd_value T>
EVE_FORCEINLINE T any_(EVE_REQUIRES(cpu_), O const& opts, T v) noexcept
  requires (O::contains(splat))
{
  return T { any[opts.drop(splat)](v) };
}

template<callable_options O, logical_simd_value T>
EVE_FORCEINLINE bool
any_(EVE_REQUIRES(cpu_), O const& opts, T const& v) noexcept
  requires (!O::contains(splat))
{
  using C = rbr::result::fetch_t<condition_key, O>;
  auto cond = opts[condition_key];
  if constexpr( C::is_complete && !C::is_inverted ) return false;
  else if (C::is_complete) return eve::any(eve::top_bits { v });
  else if constexpr( has_emulated_abi_v<T> )
  {
    if constexpr (relative_conditional_expr<C>)
    {
      std::ptrdiff_t first = cond.offset(as<T>{});
      std::ptrdiff_t last   = first + cond.count(as<T> {});
      constexpr auto size = T::size();

      EVE_ASSUME((first >= 0) && (first <= last) && (last <= size));

      bool r = false;

      for (std::ptrdiff_t i = first; i < last; ++i)
        r = r || v.get(i);

      return r;
    }
    else
    {
      const auto mask = expand_mask(cond, as(v));
      for (std::ptrdiff_t i = 0; i < v.size(); ++i)
        if (v.get(i) && mask.get(i))
          return true;

      return false;
    }
  }
  else if constexpr( has_aggregated_abi_v<T> && C::is_complete )
  {
    auto [l, h] = v.slice();
    return eve::any[ignore_none](l || h);
  }
  else
  {
    if constexpr( !top_bits<T>::is_cheap && !C::is_complete )
    {
      if( !eve::any[ignore_none](v) ) return false;
    }

    if constexpr (relative_conditional_expr<C>) return eve::any(eve::top_bits {v, cond});
    else                                        return eve::any(top_bits{ v && expand_mask(cond, as(v)) });
  }
}

template<callable_options O, relaxed_logical_scalar_value T>
EVE_FORCEINLINE bool
any_(EVE_REQUIRES(cpu_), O const& opts, T v) noexcept
{
  if constexpr (match_option<condition_key, O, ignore_none_>)
  {
    return v;
  }
  else
  {
    return v && opts[condition_key].mask(as(v));
  }
}

template<callable_options O, logical_simd_value Logical>
EVE_FORCEINLINE bool
any_(EVE_REQUIRES(cpu_), O const& opts, top_bits<Logical> mmask) noexcept
{
  if constexpr (!match_option<condition_key, O, ignore_none_>)
  {
    using C = rbr::result::fetch_t<condition_key, O>;
    auto cx = opts[condition_key];

    if constexpr (relative_conditional_expr<C>) mmask &= top_bits<Logical>{ cx };
    else                                        mmask &= top_bits<Logical>{ expand_mask(cx, as<Logical>{}) };
  }

  return (bool)mmask;
}
}
