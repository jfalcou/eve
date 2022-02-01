//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/bit_floor.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/ifrexp.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/is_less_equal.hpp>
#include <eve/function/ldexp.hpp>
#include <eve/function/max.hpp>
#include <eve/module/core/constant/one.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

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
