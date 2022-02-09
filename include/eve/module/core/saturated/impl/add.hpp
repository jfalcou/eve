//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/bit_or.hpp>
#include <eve/module/core/regular/bit_mask.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/saturated.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/function/operators.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/regular/is_gez.hpp>
#include <eve/module/core/regular/is_lez.hpp>
#include <eve/module/core/regular/is_less.hpp>
#include <eve/module/core/regular/saturate.hpp>
#include <eve/module/core/regular/sub.hpp>
#include <eve/module/core/regular/add.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/module/core/regular/is_ltz.hpp>

#include <limits>

namespace eve::detail
{
  //================================================================================================
  // saturated case
  //================================================================================================
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto
  add_(EVE_SUPPORTS(cpu_), saturated_type const &, T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(saturated(add), a, b);
  }

  template<real_scalar_value T>
  EVE_FORCEINLINE auto
  add_(EVE_SUPPORTS(cpu_), saturated_type const &, T const &a, T const &b) noexcept
  {
    if constexpr( floating_value<T> )
    {
     return a + b;
    }
    else if constexpr( signed_integral_value<T> )
    {
      auto test = is_ltz(b);
      auto pos  = min(sub(valmax(as(a)), b), a);
      auto neg  = max(sub(valmin(as(a)), b), a);
      return add(b, if_else(test, neg, pos));
    }
    else // if constexpr( std::is_unsigned_v<T> )
    {
       if constexpr( sizeof(T) >= 4 )
      {
        // large unsigned integral case
        T r = a + b;
        return r | -(r < a);
      }
      else
      {
        // small unsigned integral case - use C promotion then clamp
        auto        r  = a + b;
        decltype(r) mx = std::numeric_limits<T>::max();
        return static_cast<T>(std::min(mx, r));
      }
    }
  }

  template<real_simd_value T>
  EVE_FORCEINLINE auto
  add_(EVE_SUPPORTS(cpu_), saturated_type const &, T const &a, T const &b) noexcept
      requires has_native_abi_v<T>
  {
    if constexpr( floating_value<T> )
    {
      return a + b;
    }
    else if constexpr( integral_value<T> )
    {
      if constexpr( signed_integral_value<T> )
      {
        auto test = is_ltz(b);
        auto pos  = min(sub(valmax(as(a)), b), a);
        auto neg  = max(sub(valmin(as(a)), b), a);
        return add(b, if_else(test, neg, pos));
      }
      else if constexpr( unsigned_value<T> )
      {
        T r = a + b;
        return bit_or(r, bit_mask(is_less(r, a)));
      }
    }
  }

  //================================================================================================
  // Masked case
  //================================================================================================
  template<conditional_expr C, real_value U, real_value V>
  EVE_FORCEINLINE auto
  add_(EVE_SUPPORTS(cpu_), C const &cond, saturated_type const &, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    return mask_op(  cond, saturated(add), t, f);
  }

}
