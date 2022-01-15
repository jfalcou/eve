//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/arithmetic/saturated/inc.hpp> // SUPPRESS why not found in arithmetic ?
#include <eve/module/arithmetic.hpp>
#include <eve/module/ieee/regular/is_negative.hpp>
#include <eve/module/ieee/regular/is_positive.hpp>
#include <eve/module/ieee/detail/next_kernel.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr auto next_(EVE_SUPPORTS(cpu_)
                                      , pedantic_type const &
                                      , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(floating_value<T>)
      {
        auto pz = bitinteger(a);
        auto z  = bitfloating( inc(pz) );
        auto test = is_negative(a) && is_positive(z);
        if constexpr(scalar_value<T>)
        {
          return test ? (z == 0 ? T(-0.) : bitfloating(pz)) : z;
        }
        else
        {
          return if_else(test, if_else(is_eqz(z), mzero(eve::as<T>()), bitfloating(pz)), z);
        }
      }
      else if constexpr(integral_value<T>)
      {
        return saturated(inc)(a);
      }
    }
    else
    {
      return apply_over(pedantic(next), a);
    }
  }

  //////////////////////////////////////////////////////////////
  // two parameters
  //////////////////////////////////////////////////////////////

  template<real_value T, integral_real_value U>
  EVE_FORCEINLINE constexpr auto next_(EVE_SUPPORTS(cpu_)
                                     ,  pedantic_type const &
                                      , T const &a
                                      , U const &n) noexcept
  {
    if constexpr(has_native_abi_v<T> && has_native_abi_v<U>)
    {
      if constexpr(floating_value<T>)
      {
        using i_t = as_integer_t<T>;
        auto pz = dec(bitinteger(a) +  to_<i_t>(n));
        auto z  = bitfloating( inc(pz) );
        auto test = is_negative(a) && is_positive(z);
        if constexpr(scalar_value<T> && scalar_value<U>)
        {
          if (is_nan(a)) return a;
          return test ? (z == 0 ? T(-0.) : bitfloating(pz)) : z;
        }
        else
        {
          return if_else(test, if_else(is_eqz(z), mzero(eve::as<T>()), bitfloating(pz)), z);
        }
      }
      else if constexpr(integral_value<T>)
      {
        return saturated(add)(a, to_<T>(n));
      }
   }
    else
    {
      return apply_over(pedantic(next), a, n);
    }
  }
}
