//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/module/arithmetic/detail/next_kernel.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/sub.hpp>
#include <eve/function/next.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr auto prev_(EVE_SUPPORTS(cpu_)
                                      , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(floating_value<T>)
      {
        return bitfloating(dec(bitinteger(a)));
      }
      else if constexpr(integral_value<T>)
      {
        return dec(a);
      }
    }
    else
    {
      return apply_over(prev, a);
    }
  }

  //////////////////////////////////////////////////////////////
  // two parameters
  //////////////////////////////////////////////////////////////
  template<real_value T, integral_real_value U>
  EVE_FORCEINLINE constexpr auto prev_(EVE_SUPPORTS(cpu_)
                                      , T const &a
                                      , U const &n) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(floating_value<T>)
      {
        using i_t = as_integer_t<T>;
        return bitfloating(bitinteger(a)-to_<i_t>(n));
      }
      else if constexpr(integral_value<T>)
      {
        return sub(a, to_<T>(n));
      }
    }
    else  { return apply_over(prev, a, n);    }
  }

  // -----------------------------------------------------------------------------------------------
  // Masked cases
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto prev_(EVE_SUPPORTS(cpu_), C const &cond, U const &t) noexcept
  {
    return mask_op( cond, prev, t);
  }
    template<conditional_expr C, real_value U, integral_value V>
  EVE_FORCEINLINE auto prev_(EVE_SUPPORTS(cpu_), C const &cond
                                     , U const &t
                                     , V const &n) noexcept
  {
    return mask_op( cond, prev, t, n);
  }
}
