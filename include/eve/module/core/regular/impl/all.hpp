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
#include <eve/detail/function/to_logical.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/logical_and.hpp>

namespace eve::detail
{
template <callable_options O, logical_simd_value T>
EVE_FORCEINLINE T all_(EVE_REQUIRES(cpu_), O const&, T v) noexcept
  requires (O::contains(splat))
{
  return T { all[opts.drop(splat)](v) };
}

template <callable_options O, logical_value T>
EVE_FORCEINLINE bool
all_(EVE_REQUIRES(cpu_), O const& opts, T v) noexcept
  requires (!O::contains(splat))
{
  using C = rbr::result::fetch_t<condition_key, O>;
  auto cond = opts[condition_key];

  if constexpr (scalar_value<T>) return eve::all[cond](v.value());
  else if constexpr( C::is_complete && !C::is_inverted ) return true;
  else if constexpr( has_emulated_abi_v<T> )
  {
    if constexpr (relative_conditional_expr<C>)
    {
      bool res = true;

      std::ptrdiff_t first = cond.offset(eve::as<T> {});
      std::ptrdiff_t last  = first + cond.count(eve::as<T> {});
      constexpr std::ptrdiff_t size = T::size();
      EVE_ASSUME((first >= 0) && (first <= last) && (last <= size));
      while( first != last ) res = res && v.get(first++);

      return res;
    }
    else
    {
      const auto mask = expand_mask(cond, as(v));
      for (std::ptrdiff_t i = 0; i < v.size(); ++i)
        if (mask.get(i) && !v.get(i))
          return false;

      return true;
    }
  }
  else if constexpr( has_aggregated_abi_v<T> && C::is_complete )
  {
    auto [l, h] = v.slice();
    return eve::all(l && h);
  }
  else
  {
    if constexpr( !top_bits<T>::is_cheap && !C::is_complete )
    {
      if( eve::all(v) ) return true;
    }

    top_bits    mmask {v};

    if constexpr (relative_conditional_expr<C>) mmask |= ~top_bits<T>{ cond };
    else                                        mmask |= ~top_bits<T>{ expand_mask(cond, as(v)) };

    return all(mmask);
  }
}

template <callable_options O>
EVE_FORCEINLINE bool
all_(EVE_REQUIRES(cpu_), O const& opts, bool v) noexcept
{
  if constexpr (match_option<condition_key, O, ignore_none_>)
  {
    return v;
  }
  else
  {
    return v || !opts[condition_key].mask(as(v));
  }
}

template <callable_options O, logical_value T>
EVE_FORCEINLINE bool
all_(EVE_REQUIRES(cpu_), O const& opts, top_bits<T> v) noexcept
{
  using C = rbr::result::fetch_t<condition_key, O>;
  auto cond = opts[condition_key];

  if constexpr (relative_conditional_expr<C>)
  {
    const auto mask = top_bits<T>{ cond };
    return (v & mask) == mask;
  }
  else
  {
    if constexpr (!top_bits<T>::is_cheap)
    {
      if (v == top_bits<T>{ ignore_none }) return true;
    }

    const auto mask = top_bits<T> { expand_mask(cond, as<T>{}) };
    return (v & mask) == mask;
  }
}
}
