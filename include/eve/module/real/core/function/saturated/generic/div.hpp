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
#include <eve/detail/implementation.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/function/operators.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/roundings.hpp>
#include <eve/function/saturate.hpp>
#include <eve/function/saturated.hpp>

#ifdef EVE_COMP_IS_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4723) // potential divide by 0
#endif

#include <eve/module/real/core/function/regular/generic/div_downward.hpp>
#include <eve/module/real/core/function/regular/generic/div_tonearest.hpp>
#include <eve/module/real/core/function/regular/generic/div_upward.hpp>

namespace eve::detail
{
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto
  div_(EVE_SUPPORTS(cpu_), saturated_type const &, T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(saturated(div), a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE T div_(EVE_SUPPORTS(cpu_),
                         saturated_type const &,
                         T const &a,
                         T const &b) noexcept requires has_native_abi_v<T>
  {
    if constexpr( floating_real_value<T> )
      return div(a, b);
    else if constexpr( signed_integral_value<T> )
    {
      if constexpr( scalar_value<T> )
      {
        using ui_t = as_integer_t<T, unsigned>;
        auto aa    = a + !((b + one(eve::as(a))) | ((ui_t)a + valmin(eve::as(a))));
        if( b )
          return aa / b;
        else if( a )
          return valmax(eve::as(a)) + ((ui_t)a >> (sizeof(T) * 8 - 1));
        else
          return zero(eve::as(a));
      }
      else if constexpr( simd_value<T> )
      {
        constexpr int shft   = sizeof(element_type_t<T>) * 8 - 1;
        auto          iseqzb = is_eqz(b);
        // replace valmin/-1 by (valmin+1)/-1
        auto x = inc[logical_not(inc(b) | (a + valmin(eve::as<T>())))](a);
        // negative -> valmin
        // positive -> valmax
        auto x2 = valmax(eve::as<T>()) ^ (x >> shft);
        x       = if_else(logical_and(iseqzb, is_nez(x)), x2, x);
        auto y  = if_else(iseqzb, one(eve::as<T>()), b);
        return div(x, y);
      }
    }
    else if constexpr( unsigned_value<T> )
    {
      if constexpr( scalar_value<T> )
      {
        return b ? a / b : bit_mask(a);
      }
      else if constexpr( simd_value<T> )
      {
        auto iseqzb = is_eqz(b);
        auto bb     = if_else(iseqzb, one(eve::as(a)), b);
        auto aa     = if_else(iseqzb, bit_mask(a), a);
        return div(aa, bb);
      }
    }
  }

  //================================================================================================
  // Masked case
  //================================================================================================
  template<conditional_expr C, saturated_type const &, real_value U, real_value V>
  EVE_FORCEINLINE auto
  div_(EVE_SUPPORTS(cpu_), C const &cond, saturated_type const &, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    return mask_op( EVE_CURRENT_API{}, cond, saturated(div), t, f);
  }
}

#ifdef EVE_COMP_IS_MSVC
#  pragma warning(pop)
#endif
