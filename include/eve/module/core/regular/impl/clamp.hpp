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
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/min.hpp>

namespace eve::detail
{
template<ordered_value T, ordered_value U, ordered_value V>
EVE_FORCEINLINE auto
clamp_(EVE_SUPPORTS(cpu_),
       T const& a,
       U const& b,
       V const& c) noexcept
-> common_value_t<T, U, V>{
  return arithmetic_call(clamp, a, b, c);
}

template<ordered_value T>
EVE_FORCEINLINE auto
clamp_(EVE_SUPPORTS(cpu_)
      , T const& a, T const& b, T const& c) noexcept
requires has_native_abi_v<T>
{
  return eve::min(eve::max(a, b), c);
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, ordered_value T, ordered_value U, ordered_value V>
EVE_FORCEINLINE auto
clamp_(EVE_SUPPORTS(cpu_), C const& cond, T const& a, U const& b, V const& c) noexcept
-> decltype(clamp(a, b, c))
{
  return mask_op(cond, eve::clamp, a, b, c);
}

}
