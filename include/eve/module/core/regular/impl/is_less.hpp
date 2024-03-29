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
#include <eve/module/core/regular/all.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve::detail
{
// -----------------------------------------------------------------------------------------------
// regular case
template<ordered_value T, ordered_value U>
EVE_FORCEINLINE auto
is_less_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept
-> common_logical_t<T, U>
{
  return arithmetic_call(is_less, a, b);
}

template<ordered_value T>
EVE_FORCEINLINE auto
is_less_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept
{
  if constexpr(scalar_value<T>)
    return as_logical_t<T>(a < b);
  else
    return apply_over(is_less, a, b);
}


namespace eve
{
template<value T, value U>
EVE_FORCEINLINE auto
operator<(T const& v0, U const& v1) noexcept
    -> decltype(eve::is_less(v0, v1))
{
  return eve::is_less(v0, v1);
}

// This is needed to prevent clang using an internal operator of comparison over simd vector
// types with different value types, as some architectures are not
// aware of the accurate element type in the storage
template<ordered_value T, ordered_value U>
EVE_FORCEINLINE auto
operator<(T const& a, U const& b) noexcept requires different_value_type<T, U>
requires (simd_value<T>
= delete;
}
