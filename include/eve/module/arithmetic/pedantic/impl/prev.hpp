//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic/detail/next_kernel.hpp>
#include <eve/module/arithmetic/regular/next.hpp>
#include <eve/module/arithmetic/saturated/dec.hpp>
#include <eve/module/arithmetic/saturated/sub.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr auto prev_(EVE_SUPPORTS(cpu_)
                                      , pedantic_type const &
                                      , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(floating_value<T>)
      {
        auto nz = bitinteger(a);
        auto z  = bitfloating( dec(nz) );
        auto test = is_negative(z) && is_positive(a);
        if constexpr(scalar_value<T>)
        {
          if (is_nan(a)) return a;
          return test ? (a == 0 ? T(-0.) : bitfloating(nz)) : z;
        }
        else
        {
          return if_else(is_nan(a), allbits, if_else(test, if_else(is_eqz(a), mzero(eve::as(a)), bitfloating(nz)), z));
        }
      }
      else if constexpr(integral_value<T>)
      {
        return saturated(dec)(a);
      }
    }
    else  { return apply_over(pedantic(prev), a);    }
  }

  //////////////////////////////////////////////////////////////
  // two parameters
  //////////////////////////////////////////////////////////////
  template<real_value T, integral_real_value U>
  EVE_FORCEINLINE constexpr auto prev_(EVE_SUPPORTS(cpu_)
                                      ,  pedantic_type const &
                                      , T const &a
                                      , U const &n) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(floating_value<T>)
      {
        using iT = as_integer_t<T>;
        auto nz = inc(bitinteger(a) -  to_<iT>(n));
        auto z  = bitfloating( dec(nz) );
        auto test = is_negative(z) && is_positive(a);
        if constexpr(scalar_value<T> && scalar_value<U>)
        {
          if (is_nan(a)) return a;
          return test ? (nz == 0 ? T(-0.) : bitfloating(nz)) : z;
        }
        else
        {
          return  if_else(is_nan(a), allbits, if_else(test, if_else(is_eqz(nz), mzero(eve::as<T>()), bitfloating(nz)), z));
        }
      }
      else if constexpr(integral_value<T>)
      {
        return saturated(sub)(a, to_<T>(n));
      }
    }
    else  { return apply_over(pedantic(prev), a, n);    }
  }
}
