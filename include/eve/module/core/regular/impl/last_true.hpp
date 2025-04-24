//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/top_bits.hpp>

#include <optional>

namespace eve::detail
{
// Internal helper
template<logical_simd_value Logical>
EVE_FORCEINLINE std::ptrdiff_t
                last_true_guaranteed(top_bits<Logical> mmask)
{
  if constexpr( !top_bits<Logical>::is_aggregated )
  {
    auto           raw_mmask   = mmask.as_int();
    std::ptrdiff_t rbit_offset = std::countl_zero(raw_mmask);
    std::ptrdiff_t bit_offset  = 8 * sizeof(raw_mmask) - 1 - rbit_offset;
    return bit_offset / top_bits<Logical>::bits_per_element;
  }
  else
  {
    auto half_mmask = mmask.storage[0];
    int  offset     = 0;

    // trying to make a cmove (otherwise does not cmove, I think I tested)
    if( mmask.storage[1] )
    {
      offset     = Logical::size() / 2;
      half_mmask = mmask.storage[1];
    }

    return last_true_guaranteed(half_mmask) + offset;
  }
}

template<callable_options O, logical_simd_value T>
EVE_FORCEINLINE std::optional<std::ptrdiff_t> last_true_(EVE_REQUIRES(cpu_), O const& opts, T v) noexcept
{
  using C = rbr::result::fetch_t<condition_key, O>;
  auto cond = opts[condition_key];

  if      constexpr (scalar_value<T>)                   return last_true[cond](v.value());
  else if constexpr (C::is_complete && !C::is_inverted) return std::nullopt;
  else if constexpr (has_emulated_abi_v<T>)
  {
    if constexpr (relative_conditional_expr<C>)
    {
      std::ptrdiff_t begin = T::size() - cond.roffset(as<T>{});
      std::ptrdiff_t end   = begin - cond.count(as<T>{});
      constexpr std::ptrdiff_t size = T::size();

      EVE_ASSUME((end >= 0) && (begin <= size) && (end <= begin));

      for (std::ptrdiff_t i = begin; i > end; --i)
          if (v.get(i - 1))
            return i - 1;

      return std::nullopt;
    }
    else
    {
      auto mask = expand_mask(cond, as(v));

      for (std::ptrdiff_t i = T::size(); i > 0; --i)
        if (v.get(i - 1) && mask.get(i - 1))
          return i - 1;

      return std::nullopt;
    }
  }
  else
  {
    // This is pretty good for aggreagted as well.
    if constexpr (!top_bits<T>::is_cheap)
    {
      // No ignore, we might luck out even if some elements should not be counted.
      if (!any(v)) return std::nullopt;

      // any + ignore_none
      if constexpr (C::is_complete)
      {
        return last_true_guaranteed(top_bits{v, cond});
      }
    }

    if constexpr (relative_conditional_expr<C>) return last_true(top_bits{v, cond});
    else                                        return last_true[cond](top_bits{v});
  }
}

template<callable_options O>
EVE_FORCEINLINE std::optional<std::ptrdiff_t> last_true_(EVE_REQUIRES(cpu_), O const& opts, bool v) noexcept
{
  if constexpr (match_option<condition_key, O, ignore_none_>)
  {
    return v ? std::optional{0} : std::nullopt;
  }
  else
  {
    return opts[condition_key].mask(as(v)) && v ? std::optional{0} : std::nullopt;
  }
}

template<callable_options O, logical_simd_value Logical>
EVE_FORCEINLINE std::optional<std::ptrdiff_t> last_true_(EVE_REQUIRES(cpu_), O const& opts, top_bits<Logical> mmask) noexcept
{
  if constexpr (!match_option<condition_key, O, ignore_none_>)
  {
    mmask &= top_bits{expand_mask(opts[condition_key], as<Logical>{})};
  }

  return any(mmask) ? std::optional{last_true_guaranteed(mmask)} : std::nullopt;
}
}
