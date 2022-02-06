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
#include <eve/platform.hpp>
#include <eve/module/core/regular/is_not_finite.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/logical_or.hpp>
#include <eve/module/core/regular/logical_not.hpp>
#include <eve/module/core/constant/mantissamask.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>


namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T mantissa_(EVE_SUPPORTS(cpu_)
                                       , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(scalar_value<T>)
      {
        if(!a) return a;
        if constexpr(eve::platform::supports_invalids)
        {
          if(is_not_finite(a)) return a;
        }
        return bit_or(bit_and(a, mantissamask(eve::as<T>())),one(eve::as(a)));
      }
      else if constexpr(simd_value<T>)
      {
        auto test =  is_eqz(a);
        if constexpr(eve::platform::supports_invalids)
        {
          test =  test || is_not_finite(a);
        }
        return if_else(test, a, bit_or(bit_and(a,mantissamask(eve::as<T>())),one(eve::as<T>())));
      }
    }
    else return apply_over(mantissa, a);
  }

  //================================================================================================
  // Masked case
  //================================================================================================
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto mantissa_(EVE_SUPPORTS(cpu_), C const &cond, U const &t) noexcept
  {
    return mask_op(  cond, eve::mantissa, t);
  }
}
