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
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/min.hpp>

namespace eve::detail
{
template<real_value T, real_value U, real_value V>
EVE_FORCEINLINE auto
clamp_(EVE_SUPPORTS(cpu_),
       T const& a,
       U const& b,
       V const& c) noexcept requires compatible_values<T, U> && compatible_values<T, V>
{
  return arithmetic_call(clamp, a, b, c);
}

template<real_value T>
EVE_FORCEINLINE auto
clamp_(EVE_SUPPORTS(cpu_), T const& a, T const& b, T const& c) noexcept requires has_native_abi_v<T>
{
  return eve::min(eve::max(a, b), c);
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, real_value T, real_value U, real_value V>
EVE_FORCEINLINE auto
clamp_(EVE_SUPPORTS(cpu_), C const& cond, T const& a, U const& b, V const& c) noexcept requires
    compatible_values<T, U> && compatible_values<T, V>
{
  return mask_op(cond, eve::clamp, a, b, c);
}

}
