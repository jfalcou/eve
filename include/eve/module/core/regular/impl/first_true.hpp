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
#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/logical.hpp>
#include <eve/module/core/constant/true.hpp>
#include <eve/module/core/regular/any.hpp>

#include <optional>

namespace eve::detail
{
  template<logical_simd_value Logical>
  EVE_FORCEINLINE std::ptrdiff_t first_true_guaranteed(top_bits<Logical> mmask)
  {
    if constexpr (!top_bits<Logical>::is_aggregated)
    {
      return std::countr_zero(mmask.as_int()) / top_bits<Logical>::bits_per_element;
    }
    else
    {
      auto half_mmask = mmask.storage[1];
      int  offset     = Logical::size() / 2;

      // trying to make a cmove (otherwise does not cmove, I think I tested)
      if (mmask.storage[0])
      {
        offset     = 0;
        half_mmask = mmask.storage[0];
      }

      return first_true_guaranteed(half_mmask) + offset;
    }
  }

  /*
    booleans
  */
  template<callable_options O>
  EVE_FORCEINLINE std::optional<std::ptrdiff_t> first_true_(EVE_REQUIRES(cpu_), O const& opts, bool v) noexcept
  {
    if constexpr (match_option<condition_key, O, ignore_none_>)
    {
      return v ? std::make_optional(0) : std::nullopt;
    }
    else
    {
      return opts[condition_key].mask(as(v)) && v ? std::make_optional(0) : std::nullopt;
    }
  }

  /*
    top bits
  */
  template<callable_options O, logical_simd_value Logical>
  EVE_FORCEINLINE std::optional<std::ptrdiff_t> first_true_(EVE_REQUIRES(cpu_), O const& opts, top_bits<Logical> mmask) noexcept
  {
    if constexpr (!match_option<condition_key, O, ignore_none_>)
    {
      mmask &= top_bits{expand_mask(opts[condition_key], as<Logical>{})};
    }

    return any(mmask) ? std::make_optional(first_true_guaranteed(mmask)) : std::nullopt;
  }

  /*
    logicals
  */
  template<callable_options O, logical_value T>
  EVE_FORCEINLINE std::optional<std::ptrdiff_t> first_true_(EVE_REQUIRES(cpu_), O const& opts, T const& v) noexcept
  {
    using C = rbr::result::fetch_t<condition_key, O>;
    auto cx = opts[condition_key];

    if constexpr (scalar_value<T>)                        return first_true[cx](v.value());
    else if constexpr (C::is_complete && !C::is_inverted) return std::nullopt;
    else if constexpr (has_emulated_abi_v<T>)
    {
      if constexpr (relative_conditional_expr<C>)
      {
        const std::ptrdiff_t begin    = cx.offset(as(v));
        const std::ptrdiff_t end      = begin + cx.count(as(v));
        constexpr std::ptrdiff_t size = T::size();

        EVE_ASSUME((begin >= 0) && (begin <= end) && (end <= size));

        for (std::ptrdiff_t i = begin; i < end; ++i)
          if (v.get(i))
            return i;
      }
      else
      {
        auto mask = expand_mask(cx, as(v));
        for (std::ptrdiff_t i = 0; i < v.size(); ++i)
          if (v.get(i) && mask.get(i))
            return i;
      }

      return std::nullopt;
    }
    else
    {
      // No ignore, we might luck out even if some elements should not be counted.
      if constexpr (!top_bits<T>::is_cheap)
      {
        if (!eve::any(v))
        {
          return std::nullopt;
        }

        // any + ignore_none
        if constexpr (C::is_complete)
        {
          return first_true_guaranteed(top_bits{v, cx});
        }
      }

      if constexpr (relative_conditional_expr<C>) return first_true(top_bits{v, cx});
      else                                        return first_true[cx](top_bits{v});
    }
  }
}
