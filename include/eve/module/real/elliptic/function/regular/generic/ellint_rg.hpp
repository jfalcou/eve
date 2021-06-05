//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/ellint_rd.hpp>
#include <eve/function/ellint_rf.hpp>
#include <eve/function/is_nltz.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/detail/hz_device.hpp>


namespace eve::detail
{
  template<floating_real_value T, floating_real_value U,  floating_real_value V>
  EVE_FORCEINLINE auto ellint_rg_(EVE_SUPPORTS(cpu_)
                              , T x
                              , U y
                              , V z) noexcept
  -> decltype(arithmetic_call(ellint_rg, x, y, z))
  {
    return arithmetic_call(ellint_rg, x, y, z);
  }

  template<floating_real_value T, floating_real_value U,  floating_real_value V>
  EVE_FORCEINLINE T ellint_rg_(EVE_SUPPORTS(cpu_)
                              , raw_type const &
                              , T x
                              , U y
                              , V z) noexcept
  requires compatible_values<T, U> &&  compatible_values<V, U>
  {
    return arithmetic_call(raw(ellint_rg), x, y, z);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T ellint_rg_(EVE_SUPPORTS(cpu_)
                              , raw_type const &
                              , T x
                              , T y
                              , T z) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto cond_swap = [](auto cond, auto &a,  auto &b){
        auto aa = if_else(cond, a, b);
        auto bb = if_else(cond, b, a);
        a = aa;
        b = bb;
      };
      cond_swap(x < y, x, y);
      cond_swap(x < z, x, z);
      cond_swap(y > z, y, z);
      // now all(x >= z) and all(z >= y)
      return (z * ellint_rf(x, y, z)
              - (x-z)*(y-z)*ellint_rd(x, y, z)/3
              + sqrt(x * y / z))*half(as(x));
    }
    else
      return apply_over(raw(ellint_rg), x, y, z);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T ellint_rg_(EVE_SUPPORTS(cpu_)
                              , T x
                              , T y
                              , T z) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto r = nan(as(x));
      auto notdone = is_nltz(x) && is_nltz(y) && is_nltz(z);
      // any parameter nan or less than zero implies nan
      auto br0 = [x, y, z](){return raw(ellint_rg)(x, y, z);};
      last_interval(br0, notdone, r);
      return r;
    }
     else
      return apply_over(ellint_rg, x, y, z);
   }



}
