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
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/fma.hpp>

namespace eve::detail
{
template<value T, value U, value V>
EVE_FORCEINLINE auto
fnma_(EVE_SUPPORTS(cpu_),
      T const& a,
      U const& b,
      V const& c) noexcept
-> common_value_t<U, V, T>
{
  using r_t = common_value_t<T, U, V>;
  return arithmetic_call(fnma, r_t(a), r_t(b), r_t(c));
}

template<value T>
EVE_FORCEINLINE T
fnma_(EVE_SUPPORTS(cpu_), T const& a, T const& b, T const& c) noexcept requires has_native_abi_v<T>
{
  return fma(T(-a), b, c);
}

//================================================================================================
// Masked case
//================================================================================================
template<conditional_expr C, value T, value U, value V>
EVE_FORCEINLINE auto
fnma_(EVE_SUPPORTS(cpu_), C const& cond, T const& a, U const& b, V const& c) noexcept
-> common_value_t<U, V, T>
{
  using r_t = common_value_t<T, U, V>;
  return mask_op(cond, eve::fnma, r_t(a), r_t(b), r_t(c));
}
}
