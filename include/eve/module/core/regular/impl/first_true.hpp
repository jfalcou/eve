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
  EVE_FORCEINLINE std::optional<std::ptrdiff_t> first_true_(EVE_REQUIRES(cpu_), O const&, bool v) noexcept
  {
    return v ? std::make_optional(0) : std::nullopt;
  }

  template<callable_options O, conditional_expr C>
  EVE_FORCEINLINE std::optional<std::ptrdiff_t> first_true_(EVE_REQUIRES(cpu_), C const& cx, O const&, bool v) noexcept
  {
    return cx.mask(as(v)) && v ? std::make_optional(0) : std::nullopt;
  }

  /*
    top bits
  */
 template<callable_options O, logical_simd_value Logical>
 EVE_FORCEINLINE std::optional<std::ptrdiff_t> first_true_(EVE_REQUIRES(cpu_), O const&, top_bits<Logical> mmask) noexcept
 {
   return any(mmask) ? std::make_optional(first_true_guaranteed(mmask)) : std::nullopt;
 }

 template<callable_options O, conditional_expr C, logical_simd_value Logical>
 EVE_FORCEINLINE std::optional<std::ptrdiff_t> first_true_(EVE_REQUIRES(cpu_), C const& cx, O const&, top_bits<Logical> mmask) noexcept
 {
    mmask &= top_bits{cx.mask(as<Logical>{})};
    return any(mmask) ? std::make_optional(first_true_guaranteed(mmask)) : std::nullopt;
 }

  /*
    logicals
  */
  template<callable_options O, conditional_expr C, logical_value T>
  EVE_FORCEINLINE std::optional<std::ptrdiff_t> first_true_(EVE_REQUIRES(cpu_), C const& cx, O const&, T const& v) noexcept
  {
    if constexpr (scalar_value<T>)                   return count_true[cx](v.value());
    if constexpr (C::is_complete && !C::is_inverted) return std::nullopt;
    else if constexpr (has_emulated_abi_v<T>)
    {
      std::ptrdiff_t first = cx.offset(eve::as<T> {});
      std::ptrdiff_t last  = first + cx.count(eve::as<T> {});

      while (first != last)
      {
        if (v.get(first)) return first;
        ++first;
      }

      return std::nullopt;
    }
    // This is pretty good for aggreagted as well.
    else if constexpr (!top_bits<T>::is_cheap)
    {
      // No ignore, we might luck out even if some elements should not be counted.
      if (!eve::any(v)) return std::nullopt;

      if      constexpr (C::is_complete)               return first_true_guaranteed(top_bits{v, cx});
      else if constexpr (relative_conditional_expr<C>) return first_true(top_bits{v, cx});
      else                                             return first_true[cx](top_bits{v});
    }
    else
    {
      if constexpr (relative_conditional_expr<C>) return first_true(top_bits{v, cx});
      else                                        return first_true[cx](top_bits{v});
    }
  }

  template<callable_options O, logical_value T>
  EVE_FORCEINLINE std::optional<std::ptrdiff_t> first_true_(EVE_REQUIRES(cpu_), O const& opts, T const& v) noexcept
  {
    if constexpr (scalar_value<T>) return first_true(v.value());
    else                           return first_true_(EVE_TARGETS(cpu_), ignore_none, opts, v);
  }
}
