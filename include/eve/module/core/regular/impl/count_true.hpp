//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/top_bits.hpp>
#include <eve/concept/conditional.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/true.hpp>
#include <eve/module/core/regular/popcount.hpp>

namespace eve::detail
{
  template<callable_options O>
  EVE_FORCEINLINE std::ptrdiff_t count_true_(EVE_REQUIRES(cpu_), O const& opts, bool v) noexcept
  {
    if constexpr (match_option<condition_key, O, ignore_none_>)
    {
      return v ? 1 : 0;
    }
    else
    {
      return opts[condition_key].mask(as(v)) && v ? 1 : 0;
    }
  }

  template<callable_options O, value T>
  EVE_FORCEINLINE std::ptrdiff_t count_true_(EVE_REQUIRES(cpu_), O const& opts, logical<T> v) noexcept
  {
    using C = rbr::result::fetch_t<condition_key, O>;
    const auto cx = opts[condition_key];

    constexpr bool relative_nonignore = relative_conditional_expr<C> && !std::same_as<C, ignore_none_>;

    if      constexpr (scalar_value<T>)                   return count_true[cx](v.value());
    else if constexpr (C::is_complete && !C::is_inverted) return 0;
    else if constexpr (has_emulated_abi_v<T>)
    {
      std::ptrdiff_t count = 0;

      if constexpr (relative_conditional_expr<C>)
      {
        const std::ptrdiff_t begin    = cx.offset(as(v));
        const std::ptrdiff_t end      = begin + cx.count(as(v));
        constexpr std::ptrdiff_t size = T::size();

        EVE_ASSUME((begin >= 0) && (begin <= end) && (end <= size));
        
        for (std::ptrdiff_t i = begin; i < end; ++i)
        {
          count += v.get(i);
        }
      }
      else
      {
        auto mask = expand_mask(cx, as(v));
        for (std::ptrdiff_t i = 0; i < v.size(); ++i)
        {
          count += (v.get(i) && mask.get(i));
        }
      }

      return count;
    }
    else if constexpr (relative_nonignore) return count_true(top_bits{v, cx});
    else                                   return count_true[cx](eve::top_bits{v});
  }

  template<callable_options O, logical_simd_value Logical>
  EVE_FORCEINLINE std::ptrdiff_t count_true_(EVE_REQUIRES(cpu_), O const& opts, top_bits<Logical> mmask) noexcept
  {
    if constexpr (match_option<condition_key, O, ignore_none_>)
    {
      if constexpr (top_bits<Logical>::is_aggregated)
      {
        return count_true(mmask.storage[0]) + count_true(mmask.storage[1]);
      }
      else
      {
        return std::popcount(mmask.as_int()) / top_bits<Logical>::bits_per_element;
      }
    }
    else
    {
      auto cx = opts[condition_key];

      if constexpr (top_bits<Logical>::is_aggregated)
      {
        auto [cx_l, cx_h] = expand_mask(cx, as<Logical>()).slice();
        return count_true[cx_l](mmask.storage[0]) + count_true[cx_h](mmask.storage[1]);
      }
      else
      {
        auto vm = mmask.as_int();
        vm &= top_bits{expand_mask(cx, as<Logical>())}.as_int();
        return std::popcount(vm) / top_bits<Logical>::bits_per_element;
      }
    }
  }
}
