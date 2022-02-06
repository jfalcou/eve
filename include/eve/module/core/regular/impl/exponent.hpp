//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/arithmetic/regular/is_not_finite.hpp>
#include <eve/module/arithmetic/regular/is_nez.hpp>
#include <eve/module/arithmetic/regular/sub.hpp>
#include <eve/module/arithmetic/constant/exponentmask.hpp>
#include <eve/module/arithmetic/constant/maxexponent.hpp>
#include <eve/module/arithmetic/constant/nbmantissabits.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>


namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr as_integer_t<T> exponent_(EVE_SUPPORTS(cpu_)
                                                     , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto z = bit_and(exponentmask(as<T>()), a);
      if constexpr(scalar_value<T>)
      {
        if (is_not_finite(a)) return as_integer_t<T>(0);
        auto x = (z >> nbmantissabits(eve::as<T>()));
        return sub[is_nez(a)](x, maxexponent(eve::as<T>()));
      }
      else
      {
        auto x = (z >> nbmantissabits(eve::as<T>()));
        return if_else(is_not_finite(a), eve::zero, sub[is_nez(a)](x, maxexponent(eve::as<T>())));
      }
    }
    else return apply_over(exponent, a);
  }

  //================================================================================================
  // Masked case
  //================================================================================================
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto exponent_(EVE_SUPPORTS(cpu_), C const &cond, U const &t) noexcept
  {
    return conv_mask_op(  cond, eve::exponent, t);
  }
}
