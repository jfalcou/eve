//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/bit_and.hpp>
#include <eve/module/core/regular/bit_andnot.hpp>
#include <eve/module/core/regular/bit_or.hpp>

namespace eve::detail
{
template<value T, value U, value V>
EVE_FORCEINLINE auto
bit_select_(EVE_SUPPORTS(cpu_),
            T const& a,
            U const& b,
            V const& c) noexcept requires bit_compatible_values<T, U> && bit_compatible_values<T, V>
{
  return bit_call(bit_select, a, b, c);
}

template<ordered_value T>
EVE_FORCEINLINE auto
bit_select_(EVE_SUPPORTS(cpu_), T const& a, T const& b, T const& c) noexcept
{
  if constexpr(scalar_value<T>)
    return bit_or(bit_and(b, a), bit_andnot(c, a));
  else  // fallback never taken if proper intrinsics are at hand
    return (b & a) | bit_andnot(c, a);
}
}
