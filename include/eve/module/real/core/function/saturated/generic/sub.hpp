//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/bit_mask.hpp>
#include <eve/function/bit_ornot.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_gez.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/is_less_equal.hpp>
#include <eve/function/is_ltz.hpp>
#include <eve/function/is_lez.hpp>
#include <eve/function/saturate.hpp>
#include <eve/function/saturated.hpp>
#include <eve/function/add.hpp>
#include <eve/function/sub.hpp>
#include <eve/function/min.hpp>
#include <eve/function/max.hpp>

#include <limits>

namespace eve::detail
{
  //================================================================================================
  // saturated case
  //================================================================================================
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto
  sub_(EVE_SUPPORTS(cpu_), saturated_type const &, T const &a, U const &b) noexcept
  -> decltype(arithmetic_call(sub, a, b))
  {
    return arithmetic_call(saturated(sub), a, b);
  }

  template<real_scalar_value T>
  EVE_FORCEINLINE auto
  sub_(EVE_SUPPORTS(cpu_), saturated_type const &, T const &a, T const &b) noexcept
  {
    if constexpr( floating_value<T> )
    {
      return a - b;
    }
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
        return static_cast<T>(saturate(r, as_<T>()));
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
  sub_(EVE_SUPPORTS(cpu_), saturated_type const &, T const &a, T const &b) noexcept
      requires has_native_abi_v<T>
  {
    if constexpr( floating_value<T> )
    {
      return a - b;
    }
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
  template<conditional_expr C, real_value U, real_value V>
  EVE_FORCEINLINE auto
  sub_(EVE_SUPPORTS(cpu_), C const &cond, saturated_type const &, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    return mask_op(  cond, saturated(sub), t, f);
  }
}
