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
#include <eve/conditional.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton.hpp>

namespace eve::detail
{
template<logical_simd_value T, relative_conditional_expr C>
EVE_FORCEINLINE bool
any_(EVE_SUPPORTS(cpu_), C const& cond, T const& v) noexcept
{
  if constexpr( C::is_complete && !C::is_inverted ) return false;
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

EVE_FORCEINLINE bool
any_(EVE_SUPPORTS(cpu_), bool v) noexcept
{
  return v;
}

template<value T>
EVE_FORCEINLINE bool
any_(EVE_SUPPORTS(cpu_), logical<T> const& v) noexcept
{
  if constexpr( scalar_value<T> ) return bool(v);
  else return eve::any[ignore_none](v);
}

template<logical_simd_value Logical>
EVE_FORCEINLINE bool
any_(EVE_SUPPORTS(cpu_), top_bits<Logical> mmask) noexcept
{
  return (bool)mmask;
}
}
