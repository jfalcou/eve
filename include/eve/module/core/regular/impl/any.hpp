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
  template<callable_options O>
  EVE_FORCEINLINE bool any_(EVE_REQUIRES(cpu_), O const& opts, bool v) noexcept
  {
    if constexpr (match_option<condition_key, O, ignore_none_>)
    {
      return v;
    }
    else
    {
      return v && !opts[condition_key].mask(as(v));
    }
  }

  template<callable_options O, value T>
  EVE_FORCEINLINE bool any_(EVE_REQUIRES(cpu_), O const& opts, logical<T> v) noexcept
  {
    using C = rbr::result::fetch_t<condition_key, O>;
    auto cx = opts[condition_key];

    if      constexpr (C::is_complete && !C::is_inverted) return false;
    else if constexpr (scalar_value<T>)              return any.behavior(cpu_{}, opts, v.value());
    else if constexpr (has_emulated_abi_v<T>)
    {
      if constexpr (relative_conditional_expr<C>)
      {
        std::ptrdiff_t begin = cx.offset(as<T>{});
        std::ptrdiff_t end   = begin + cx.count(as<T> {});
        constexpr auto size = T::size();

        EVE_ASSUME((begin >= 0) && (begin <= end) && (end <= size));

        for (std::ptrdiff_t i = begin; i < end; ++i)
          if (v.get(i))
            return true;

        return false;
      }
      else
      {
        for (std::ptrdiff_t i = 0; i < v.size(); ++i)
          if (v.get(i) && cx.get(i))
            return true;

        return false;
      }
    }
    else if constexpr (has_aggregated_abi_v<T> && C::is_complete)
    {
      auto [l, h] = v.slice();
      return eve::any(l || h);
    }
    else
    {
      if constexpr (!top_bits<T>::is_cheap && !C::is_complete)
      {
        if (!eve::any(v)) return false;
      }

      if constexpr (relative_conditional_expr<C>) return eve::any(top_bits{ v, cx });
      else                                        return eve::any[opts](top_bits{ v });
    }
  }

  template<callable_options O, logical_simd_value T>
  EVE_FORCEINLINE bool any_(EVE_REQUIRES(cpu_), O const& opts, top_bits<T> mmask) noexcept
  {
    if constexpr (!match_option<condition_key, O, ignore_none_>)
    {
      using C = rbr::result::fetch_t<condition_key, O>;
      auto cx = opts[condition_key];

      if constexpr (relative_conditional_expr<C>) mmask |= ~top_bits<T>{ cx };
      else                                        mmask |= ~top_bits<T>{ expand_mask(cx, as<T>{}) };
    }

    return bool{mmask};
  }
}
