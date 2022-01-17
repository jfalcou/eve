//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/horizontal.hpp>
#include  <eve/module/arithmetic/detail/multi_div.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/add.hpp>
#include <eve/function/shr.hpp>
#include <eve/function/saturated/mul.hpp>

#ifdef EVE_COMP_IS_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4723) // potential divide by 0
#endif

#include <eve/module/arithmetic/regular/impl/div_downward.hpp>
#include <eve/module/arithmetic/regular/impl/div_tonearest.hpp>
#include <eve/module/arithmetic/regular/impl/div_upward.hpp>

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
                         T a,
                         T b) noexcept
  requires has_native_abi_v<T>
  {
    if constexpr(integral_value<T> )
    {
      EVE_ASSERT(eve::all((a!= 0) || (b!= 0)), "[eve] - saturated(div)(0, 0) is undefined");
    }

    if constexpr( floating_real_value<T> )
    {
      return div(a, b);
    }
    else if constexpr( signed_integral_value<T> )
    {
      constexpr int shft   = sizeof(element_type_t<T>) * 8 - 1;
      if constexpr( scalar_value<T> )
      {
        // case valmin/-1 is treated here
        if(b == -1 && a == eve::valmin(eve::as(a))) return eve::valmax(eve::as(a));
        if(b != 0) return div(a, b);
        // negative -> valmin,  positive -> valmax
        else       return bit_xor(eve::valmax(eve::as(a)), shr(a, shft));
      }
      else if constexpr( simd_value<T> )
      {
        auto a2 =  bit_xor(eve::valmax(eve::as(a)), shr(a, shft));
        // case valmin/-1 is treated here
        a = inc[logical_not(inc(b) | add(a, eve::valmin(eve::as(a))))](a);
        auto isnezb = is_nez(b);
        b = if_else(isnezb, b, mone);
        return if_else(isnezb, div(a, b), a2);
      }
    }
    else if constexpr( unsigned_value<T> )
    {
      if constexpr( scalar_value<T> )  {
        if (b != 0) return a / b;
        return eve::valmax(as(a));
      }
      else if constexpr( simd_value<T> ) return if_else(is_nez(b), div(a, b), allbits);
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
    return mask_op(  cond, saturated(div), t, f);
  }
}

#ifdef EVE_COMP_IS_MSVC
#  pragma warning(pop)
#endif
