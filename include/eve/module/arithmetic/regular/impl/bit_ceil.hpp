//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic/regular/bit_floor.hpp>
#include <eve/module/arithmetic/regular/dec.hpp>
#include <eve/module/arithmetic/regular/ifrexp.hpp>
#include <eve/module/arithmetic/regular/is_less.hpp>
#include <eve/module/arithmetic/regular/is_less_equal.hpp>
#include <eve/module/arithmetic/regular/ldexp.hpp>
#include <eve/module/arithmetic/regular/max.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE auto bit_ceil_(EVE_SUPPORTS(cpu_)
                                , T const &v) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto vle1 = v <= one(eve::as(v));
      if constexpr(scalar_value<T>) if (vle1) return one(eve::as(v));
      if constexpr(floating_real_value<T>)
      {
        auto [m, e] = ifrexp(v);
        e = dec(e);
        auto tmp = ldexp(one(eve::as(v)), e);
        auto tmpltv = tmp < v;
        if constexpr(scalar_value<T>)
        {
          return tmpltv ? tmp+tmp : tmp;
        }
        else
        {
          return if_else(vle1, one(eve::as(v)), if_else(tmpltv,  tmp+tmp, tmp));
        }
      }
      else
      {
        auto tmp =  bit_floor(v);
        auto tmpltv = tmp < v;
        if constexpr(scalar_value<T>) return T(tmpltv ? tmp+tmp:  tmp);
        else                          return if_else(vle1, one, if_else(tmpltv, tmp+tmp,  tmp));
      }
    }
    else return apply_over(bit_ceil, v);
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto bit_ceil_(EVE_SUPPORTS(cpu_), C const &cond, U const &t) noexcept
  {
    return mask_op( cond, eve::bit_ceil, t);
  }

}
