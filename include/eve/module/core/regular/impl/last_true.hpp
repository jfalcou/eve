//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch/top_bits.hpp>

#include <optional>

namespace eve::detail
{
  // Internal helper
  template <logical_simd_value Logical>
  EVE_FORCEINLINE std::ptrdiff_t last_true_guaranteed(top_bits<Logical> mmask)
  {
    if constexpr ( !top_bits<Logical>::is_aggregated )
    {
      auto raw_mmask = mmask.as_int();
      std::ptrdiff_t rbit_offset = std::countl_zero(raw_mmask);
      std::ptrdiff_t bit_offset = 8 * sizeof(raw_mmask) - 1 - rbit_offset;
      return bit_offset / top_bits<Logical>::bits_per_element;
    }
    else
    {
      auto half_mmask = mmask.storage[0];
      int offset = 0;

      // trying to make a cmove (otherwise does not cmove, I think I tested)
      if (mmask.storage[1])
      {
        offset = Logical::size() / 2;
        half_mmask = mmask.storage[1];
      }

      return last_true_guaranteed(half_mmask) + offset;
    }
  }

  template<logical_simd_value T, relative_conditional_expr C>
  EVE_FORCEINLINE std::optional<std::ptrdiff_t> last_true_(EVE_SUPPORTS(cpu_), C const &cond, T const &v) noexcept
  {
         if constexpr ( C::is_complete && !C::is_inverted ) return {};
    else if constexpr ( has_emulated_abi_v<T> )
    {
      std::ptrdiff_t first = cond.offset(eve::as<T>{});
      std::ptrdiff_t last = first + cond.count(eve::as<T>{});

      while (first != last) {
        if (v.get(--last)) return last;
      }

      return {};
    }
    // This is pretty good for aggreagted as well.
    else if constexpr ( !top_bits<T>::is_cheap )
    {
      // No ignore, we might luck out even if some elements should not be counted.
      if ( !eve::any(v) ) return {};

      top_bits mmask{v, cond};
      if constexpr ( C::is_complete ) return last_true_guaranteed(mmask);
      else                            return last_true(mmask);
    }
    else
    {
      top_bits mmask{v, cond};
      return last_true(mmask);
    }
  }

  EVE_FORCEINLINE std::optional<std::ptrdiff_t> last_true_(EVE_SUPPORTS(cpu_), bool v) noexcept
  {
    if (!v) return std::nullopt;
    return 0;
  }

  template<value T>
  EVE_FORCEINLINE std::optional<std::ptrdiff_t> last_true_(EVE_SUPPORTS(cpu_), T const &v) noexcept
  {
    if constexpr ( !scalar_value<T> ) return eve::last_true[ignore_none](v);
    else
    {
      if (!v) return std::nullopt;
      return 0;
    }
  }

  template <logical_simd_value Logical>
  EVE_FORCEINLINE std::optional<std::ptrdiff_t> last_true_(EVE_SUPPORTS(cpu_), top_bits<Logical> mmask) noexcept
  {
    if (!any(mmask)) return {};
    return last_true_guaranteed(mmask);
  }
}
