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
#include <eve/module/core/regular/signnz.hpp>

#include <concepts>

namespace eve::detail
{

template<real_value T, real_value U>
EVE_FORCEINLINE auto
negatenz_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept
-> common_value_t<T, U>
{
  return arithmetic_call(negatenz, a, b);
}

template<real_value T>
EVE_FORCEINLINE T
negatenz_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept
{
  if constexpr(has_native_abi_v<T>)
  {
    if constexpr( signed_value<T> )
      return a * signnz(b);
    else
      return a;
  }
  else return apply_over(negatenz, a, b);
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, real_value T, real_value U>
EVE_FORCEINLINE auto
negatenz_(EVE_SUPPORTS(cpu_), C const& cond, T const& a, U const& b) noexcept
-> common_value_t<T, U>
{
  return mask_op(cond, eve::negatenz, a, b);
}
}
