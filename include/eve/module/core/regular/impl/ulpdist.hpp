//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/traits/common_value.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/constant/half.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <eve/module/core/decorator/numeric.hpp>
#include <eve/module/core/detail/next_kernel.hpp>
#include <eve/module/core/numeric/is_equal.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/converter.hpp>
#include <eve/module/core/regular/dist.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_unordered.hpp>
#include <eve/module/core/regular/nb_values.hpp>

namespace eve::detail
{
// -----------------------------------------------------------------------------------------------
// regular case
template<ordered_value T, ordered_value U>
EVE_FORCEINLINE auto
ulpdist_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept
-> common_value_t<T, U>
{
  return arithmetic_call(ulpdist, a, b);
}

template<ordered_value T>
EVE_FORCEINLINE T
ulpdist_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept
requires has_native_abi_v<T>
{
  if constexpr( integral_value<T> ) { return dist(a, b); }
  else if constexpr( scalar_value<T> )
  {
    if( numeric(is_equal)(a, b) ) return T(0);
    if( is_unordered(a, b) ) return inf(eve::as<T>());
    return nb_values(a, b) * half(eve::as(a));
  }
  else if constexpr( simd_value<T> )
  {
    return if_else(numeric(is_equal)(a, b),
                   eve::zero,
                   if_else(is_unordered(a, b)
                          , eve::inf(as(a))
                          , to_<T>(nb_values(a, b)))
                       * half(eve::as(a)));
  }
}
}
