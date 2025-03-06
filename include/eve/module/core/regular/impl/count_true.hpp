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
  EVE_FORCEINLINE std::ptrdiff_t count_true_(EVE_REQUIRES(cpu_), O const&, bool v) noexcept
  {
    return v ? 1 : 0;
  }

  template<callable_options O, conditional_expr C>
  EVE_FORCEINLINE std::ptrdiff_t count_true_(EVE_REQUIRES(cpu_), C const& cx, O const&, bool v) noexcept
  {
    return cx.mask(as(v)) && v ? 1 : 0;
  }

  template<callable_options O, value T>
  EVE_FORCEINLINE std::ptrdiff_t count_true_(EVE_REQUIRES(cpu_), O const&, logical<T> v) noexcept
  {
    if constexpr (scalar_value<T>) return v.value() ? 1 : 0;
    else                           return count_true(eve::top_bits {v});
  }

  template<callable_options O, conditional_expr C, simd_value T>
  EVE_FORCEINLINE std::ptrdiff_t count_true_(EVE_REQUIRES(cpu_),  C const& cx, O const&, logical<T> v) noexcept
  {
    return count_true(top_bits {v, cx});
  }

  template<callable_options O, logical_simd_value Logical>
  EVE_FORCEINLINE std::ptrdiff_t count_true_(EVE_REQUIRES(cpu_), O const&, top_bits<Logical> mmask) noexcept
  {
    if constexpr (!top_bits<Logical>::is_aggregated)
    {
      return std::popcount(mmask.as_int()) / top_bits<Logical>::bits_per_element;
    }
    else
    {
      return count_true(mmask.storage[0]) + count_true(mmask.storage[1]);
    }
  }

  template<callable_options O, conditional_expr C, logical_simd_value Logical>
  EVE_FORCEINLINE std::ptrdiff_t count_true_(EVE_REQUIRES(cpu_), C const& cx, O const&, top_bits<Logical> mmask) noexcept
  {
    if constexpr (!top_bits<Logical>::is_aggregated)
    {
      constexpr auto bitmask = mmask.as_int();
      return std::popcount(bitmask & cx.mask(as(bitmask))) / top_bits<Logical>::bits_per_element;
    }
    else
    {
      return count_true[cx](mmask.storage[0]) + count_true[cx](mmask.storage[1]);
    }
  }
}
