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
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_gtz.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/minus.hpp>
#include <eve/module/core/regular/shl.hpp>
#include <eve/module/core/regular/shr.hpp>

namespace eve::detail
{
template<unsigned_scalar_value T, integral_simd_value U>
EVE_FORCEINLINE auto
rshr_(EVE_SUPPORTS(cpu_), T const& a0, U const& a1) noexcept
{
  using w_t = wide<T, cardinal_t<U>>;
  return rshr(w_t(a0), a1);
}

template<unsigned_scalar_value T, integral_scalar_value U>
EVE_FORCEINLINE auto
rshr_(EVE_SUPPORTS(cpu_), T const& a0, U const& a1) noexcept
{
  if constexpr( unsigned_value<U> ) { return T(a0 >> a1); }
  else
  {
#ifndef NDEBUG
    return is_gtz(a1) ? T(a0 >> max(zero(eve::as(a1)), a1))
                      : T(a0 << max(zero(eve::as(a1)), minus(a1)));
#else
    return is_gtz(a1) ? T(a0 >> a1) : T(a0 << minus(a1));
#endif
  }
}

template<unsigned_simd_value T, integral_value U>
EVE_FORCEINLINE auto
rshr_(EVE_SUPPORTS(cpu_), T const& a0, U const& a1) noexcept
{
  if constexpr( unsigned_value<U> ) { return T(a0 >> a1); }
  else if constexpr( scalar_value<U> ) { return (a1 > 0) ? T(shr(a0, a1)) : T(shl(a0, minus(a1))); }
  else
  {
    if constexpr( has_native_abi_v<T> && has_native_abi_v<U> )
    {
#ifndef NDEBUG
      return if_else(
          is_gtz(a1), T(a0 >> max(zero(eve::as(a1)), a1)), T(a0 << max(zero(eve::as(a1)), -a1)));
#else
      return if_else(is_gtz(a1), T(a0 >> a1), T(a0 << minus(a1)));
#endif
    }
    else { return apply_over(rshr, a0, a1); }
  }
}
// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, unsigned_simd_value T, integral_value U>
EVE_FORCEINLINE auto
rshr_(EVE_SUPPORTS(cpu_), C const& cond, T const& a0, U const& a1) noexcept
{
  return mask_op(cond, eve::rshr, a0, a1);
}
}
