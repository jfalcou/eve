//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/decorator/saturated.hpp>
#include <eve/module/core/regular/add.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/bit_and.hpp>
#include <eve/module/core/regular/bit_mask.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_gez.hpp>
#include <eve/module/core/regular/is_less.hpp>
#include <eve/module/core/regular/is_less_equal.hpp>
#include <eve/module/core/regular/is_lez.hpp>
#include <eve/module/core/regular/is_ltz.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/module/core/regular/saturate.hpp>
#include <eve/module/core/regular/sub.hpp>

#include <limits>

namespace eve::detail
{
//================================================================================================
// saturated case
//================================================================================================
template<ordered_value T, ordered_value U>
EVE_FORCEINLINE auto
sub_(EVE_SUPPORTS(cpu_),
     saturated_type const&,
     T const& a,
     U const& b) noexcept
-> decltype(sub(a, b))
{
  return arithmetic_call(saturated(sub), a, b);
}

template<real_scalar_value T>
EVE_FORCEINLINE auto
sub_(EVE_SUPPORTS(cpu_), saturated_type const&, T const& a, T const& b) noexcept
{
  if constexpr( floating_value<T> ) { return a - b; }
  else if constexpr( signed_integral_value<T> )
  {
    if constexpr( sizeof(T) >= 4 )
    {
      auto test = is_ltz(b);
      auto pos  = min(add(valmax(as(a)), b), a);
      auto neg  = max(add(valmin(as(a)), b), a);
      return sub(if_else(test, pos, neg), b);
    }
    else
    {
      // small signed integral case
      auto r = a - b;
      return static_cast<T>(saturate(r, as<T>()));
    }
  }
  else if constexpr( unsigned_value<T> )
  {
    T r = a - b;
    return static_cast<T>(r & -(r <= a));
  }
}

template<real_simd_value T>
EVE_FORCEINLINE auto
sub_(EVE_SUPPORTS(cpu_),
     saturated_type const&,
     T const& a,
     T const& b) noexcept requires has_native_abi_v<T>
{
  if constexpr( floating_value<T> ) { return a - b; }
  else if constexpr( integral_value<T> )
  {
    if constexpr( signed_integral_value<T> )
    {
      auto test = is_lez(b);
      auto pos  = min(add(valmax(as(a)), b), a);
      auto neg  = max(add(valmin(as(a)), b), a);
      return sub(if_else(test, pos, neg), b);
    }
    else if constexpr( unsigned_value<T> )
    {
      T r = a - b;
      return bit_and(r, bit_mask(is_less_equal(r, a)));
    }
  }
}

//================================================================================================
// Masked case
//================================================================================================
template<conditional_expr C, ordered_value U, ordered_value V>
EVE_FORCEINLINE auto
sub_(EVE_SUPPORTS(cpu_),
     C const& cond,
     saturated_type const&,
     U const& t,
     V const& f) noexcept
-> decltype(sub(t, f))
{
  return mask_op(cond, saturated(sub), t, f);
}
}
