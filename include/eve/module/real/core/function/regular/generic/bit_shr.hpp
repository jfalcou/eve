//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/traits/as_integer.hpp>

#include <type_traits>

namespace eve::detail
{
  template<integral_value T, integral_value U>
  EVE_FORCEINLINE auto bit_shr_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  {
    if constexpr( has_native_abi_v<T> && has_native_abi_v<U> )
    {
      using u_t = eve::as_integer_t<T, unsigned>;
      if constexpr( scalar_value<U> )
      {
        if constexpr( scalar_value<T> )
          return static_cast<T>(u_t(a) >> b);
        else if constexpr( simd_value<T> )
          return bit_cast(bit_cast(a, as<u_t>()) >> int(b), as(a));
      }
      else //U wide
      {
        if constexpr( scalar_value<T> )
        {
          using w_t = as_wide_t<T, cardinal_t<U>>;
          return bit_shr(w_t(a), b);
       }
        else if constexpr( simd_value<T> )
        {
          return bit_cast(map(bit_shr, a, b), as(a));
        }
      }
    }
    else
      return apply_over(bit_shr, a, b);
  }

  //================================================================================================
  // Masked case
  //================================================================================================
  template<conditional_expr C, integral_value T, integral_value U>
  EVE_FORCEINLINE auto bit_shr_(EVE_SUPPORTS(cpu_), C const &cond, T const &a, U const &b) noexcept
  {
    // TODO in case cond is a logical
    // return eve::bit_shr, a, if_else(cond, b, eve::zero));
    // would be better
    return mask_op(  cond, eve::bit_shr, a, b);
  }

}
