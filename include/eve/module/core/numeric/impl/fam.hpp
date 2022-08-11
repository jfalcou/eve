//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/decorator/numeric.hpp>
#include <eve/module/core/numeric/fma.hpp>
#include <eve/module/core/regular/all.hpp>

#include <type_traits>

namespace eve::detail
{
template<real_value T, real_value U, real_value V>
EVE_FORCEINLINE auto
fam_(EVE_SUPPORTS(cpu_), numeric_type const&, T const& a, U const& b, V const& c) noexcept requires
    compatible_values<T, U> && compatible_values<T, V>
{
  return arithmetic_call(numeric(fam), a, b, c);
}

template<real_value T>
EVE_FORCEINLINE T
fam_(EVE_SUPPORTS(cpu_), numeric_type const&, T const& a, T const& b, T const& c) noexcept requires
    has_native_abi_v<T>
{
  return numeric(fma)(b, c, a);
}
}
