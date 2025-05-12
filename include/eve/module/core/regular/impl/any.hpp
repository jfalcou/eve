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
template<callable_options O, logical_simd_value T>
EVE_FORCEINLINE bool
any_(EVE_REQUIRES(cpu_), O const& opts, T const& v) noexcept
{
  using C = rbr::result::fetch_t<condition_key, O>;
  auto cond = opts[condition_key];
  if constexpr( C::is_complete && !C::is_inverted ) return false;
  else if (C::is_complete) return eve::any(eve::top_bits { v });
  else if constexpr( has_emulated_abi_v<T> )
  {
    bool res = false;

    std::ptrdiff_t first = cond.offset(eve::as<T> {});
    std::ptrdiff_t last  = first + cond.count(eve::as<T> {});
    while( first != last ) res = res || v.get(first++);

    return res;
  }
  else if constexpr( has_aggregated_abi_v<T> && C::is_complete )
  {
    auto [l, h] = v.slice();
    return eve::any[ignore_none](l || h);
  }
  else
  {
    if constexpr( !top_bits<T>::is_cheap && !C::is_complete )
    {
      if( !eve::any[ignore_none](v) ) return false;
    }

    return eve::any(eve::top_bits {v, cond});
  }
}

template<callable_options O, relaxed_logical_scalar_value T>
EVE_FORCEINLINE bool
any_(EVE_REQUIRES(cpu_), O const&, T v) noexcept
{
  return bool(v);
}

template<callable_options O, logical_simd_value Logical>
EVE_FORCEINLINE bool
any_(EVE_REQUIRES(cpu_), O const&, top_bits<Logical> mmask) noexcept
{
  return (bool)mmask;
}
}
