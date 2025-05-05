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

namespace eve::detail
{
template <callable_options O, logical_value T>
EVE_FORCEINLINE bool
all_(EVE_REQUIRES(cpu_), O const& opts, T v) noexcept
{
  using C = rbr::result::fetch_t<condition_key, O>;
  auto cx = opts[condition_key];

  if constexpr (scalar_value<T>) return eve::all[cx](v.value());
  else
  if constexpr( C::is_complete && !C::is_inverted ) return true;
  else if constexpr( has_emulated_abi_v<T> )
  {
    if constexpr (relative_conditional_expr<C>)
    {
      const std::ptrdiff_t begin    = cx.offset(as(v));
      const std::ptrdiff_t end      = begin + cx.count(as(v));
      constexpr std::ptrdiff_t size = T::size();

      EVE_ASSUME((begin >= 0) && (begin <= end) && (end <= size));

      for (std::ptrdiff_t i = begin; i < end; ++i)
        if (!v.get(i))
          return false;

      return true;
    }
    else
    {
      const auto mask = expand_mask(cx, as(v));
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

    if constexpr (relative_conditional_expr<C>) mmask |= ~top_bits<T>{ cx };
    else                                        mmask |= ~top_bits<T>{ expand_mask(cx, as(v)) };

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
  auto cx = opts[condition_key];

  if constexpr (relative_conditional_expr<C>)
  {
    const auto mask = top_bits<T>{ cx };
    return (v & mask) == mask;
  }
  else
  {
    if constexpr (!top_bits<T>::is_cheap)
    {
      if (v == top_bits<T>{ ignore_none }) return true;
    }

    const auto mask = top_bits<T> { expand_mask(cx, as<T>{}) };
    return (v & mask) == mask;
  }
}
}
