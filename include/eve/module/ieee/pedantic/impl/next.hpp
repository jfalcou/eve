//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/module/real/core/detail/generic/next_kernel.hpp>
#include <eve/function/saturated.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/regular.hpp>
#include <eve/function/saturated/add.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/saturated/inc.hpp>
#include <eve/function/dec.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/concept/value.hpp>

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
