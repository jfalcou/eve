//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
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
// Internal helper
template<logical_simd_value Logical>
EVE_FORCEINLINE std::ptrdiff_t
                first_true_guaranteed(top_bits<Logical> mmask)
{
  if constexpr( !top_bits<Logical>::is_aggregated )
  {
    return std::countr_zero(mmask.as_int()) / top_bits<Logical>::bits_per_element;
  }
  else
  {
    auto half_mmask = mmask.storage[1];
    int  offset     = Logical::size() / 2;

    // trying to make a cmove (otherwise does not cmove, I think I tested)
    if( mmask.storage[0] )
    {
      offset     = 0;
      half_mmask = mmask.storage[0];
    }

    return first_true_guaranteed(half_mmask) + offset;
  }
}

template<logical_simd_value T, relative_conditional_expr C>
EVE_FORCEINLINE std::optional<std::ptrdiff_t>
                first_true_(EVE_SUPPORTS(cpu_), C const                &cond, T const                &v) noexcept
{
  if constexpr( C::is_complete && !C::is_inverted ) return {};
  else if constexpr( has_emulated_abi_v<T> )
  {
    std::ptrdiff_t first = cond.offset(eve::as<T> {});
    std::ptrdiff_t last  = first + cond.count(eve::as<T> {});

    while( first != last )
    {
      if( v.get(first) ) return first;
      ++first;
    }

    return {};
  }
  // This is pretty good for aggreagted as well.
  else if constexpr( !top_bits<T>::is_cheap )
  {
    // No ignore, we might luck out even if some elements should not be counted.
    if( !eve::any(v) ) return {};

    top_bits mmask {v, cond};
    if constexpr( C::is_complete ) return first_true_guaranteed(mmask);
    else return first_true(mmask);
  }
  else
  {
    top_bits mmask {v, cond};
    return first_true(mmask);
  }
}

EVE_FORCEINLINE std::optional<std::ptrdiff_t>
                first_true_(EVE_SUPPORTS(cpu_), bool v) noexcept
{
  if( !v ) return std::nullopt;
  return 0;
}

template<value T>
EVE_FORCEINLINE std::optional<std::ptrdiff_t>
                first_true_(EVE_SUPPORTS(cpu_), T const                &v) noexcept
{
  if constexpr( !scalar_value<T> ) return eve::first_true[ignore_none](v);
  else
  {
    if( !v ) return std::nullopt;
    return 0;
  }
}

template<logical_simd_value Logical>
EVE_FORCEINLINE std::optional<std::ptrdiff_t>
                first_true_(EVE_SUPPORTS(cpu_), top_bits<Logical> mmask) noexcept
{
  if( !any(mmask) ) return {};
  return first_true_guaranteed(mmask);
}

} // namespace eve
