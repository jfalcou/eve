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
#include <eve/module/core/decorator/numeric.hpp>
#include <eve/module/core/numeric/fnms.hpp>
#include <eve/module/core/regular/all.hpp>

#include <type_traits>

namespace eve::detail
{
template<ordered_value T, ordered_value U, ordered_value V>
EVE_FORCEINLINE auto
fsnm_(EVE_SUPPORTS(cpu_), numeric_type const&, T const& a, U const& b, V const& c) noexcept
-> common_value_t<T, U, V>
{
  return arithmetic_call(numeric(fsnm), a, b, c);
}

template<ordered_value T>
EVE_FORCEINLINE T
fsnm_(EVE_SUPPORTS(cpu_), numeric_type const&, T const& a, T const& b, T const& c) noexcept
requires has_native_abi_v<T>
{
  return numeric(fnms)(b, c, a);
}
}
