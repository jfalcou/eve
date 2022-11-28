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
#include <eve/module/core/decorator/raw.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/fma.hpp>
#include <eve/module/core/regular/fnma.hpp>

#include <type_traits>

namespace eve::detail
{
template<value T, value U, value V>
EVE_FORCEINLINE auto
lerp_(EVE_SUPPORTS(cpu_),
      T const& a,
      U const& b,
      V const& t) noexcept
-> common_value_t<U, V, T>
{
  return arithmetic_call(lerp, a, b, t);
}

template<value T>
EVE_FORCEINLINE T
lerp_(EVE_SUPPORTS(cpu_), T const& a, T const& b, T const& t) noexcept
{
  return fma(t, b, fnma(t, a, a));
}

template<value T, value U, value V>
EVE_FORCEINLINE auto
lerp_(EVE_SUPPORTS(cpu_), raw_type const&, T const& a, U const& b, V const& t) noexcept
-> common_value_t<U, V, T>
{
  return arithmetic_call(raw(lerp), a, b, t);
}

template<value T>
EVE_FORCEINLINE T
lerp_(EVE_SUPPORTS(cpu_), raw_type const&, T const& a, T const& b, T const& t) noexcept
requires has_native_abi_v<T>
{
  return fma(t, b, fnma(t, a, a));
  ;
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, real_value T, value U, value V>
EVE_FORCEINLINE auto
lerp_(EVE_SUPPORTS(cpu_), C const& cond, T const& a, U const& b, V const& t) noexcept
{
  return mask_op(cond, eve::lerp, a, b, t);
}

template<conditional_expr    C,
         decorator           D,
         value T,
         value U,
         value V>
EVE_FORCEINLINE auto
lerp_(EVE_SUPPORTS(cpu_)
     , C const& cond, D const& d
     , T const& a, U const& b, V const& t) noexcept
-> decltype(lerp(a, b, t))
{
  return mask_op(cond, d(eve::lerp), a, b, t);
}

}
