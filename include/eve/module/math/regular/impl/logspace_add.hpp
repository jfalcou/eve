//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math/regular/exp.hpp>
#include <eve/module/math/regular/log1p.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE  auto logspace_add_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(logspace_add, a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE  T logspace_add_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , T const &b) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto tmp = -eve::abs(a-b);
      auto r = eve::max(a,b)+eve::log1p(eve::exp(tmp));
      if constexpr(eve::platform::supports_invalids)
        r = if_else(is_nan(tmp), a+b, r);
      return r;
    }
    else
    {
      return apply_over(logspace_add, a, b);
    }
  }

  //===============================================================================================
  // Multi case
  //================================================================================================
  template<floating_real_value T0, floating_real_value T1, real_value ...Ts>
  common_compatible_t<T0,T1, Ts...> logspace_add_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args)
  {
    using r_t = common_compatible_t<T0,T1,Ts...>;
    if constexpr(has_native_abi_v<r_t>)
    {
      r_t that(logspace_add(a0, a1));
      auto ladd = [](auto that, auto next)->r_t{
        that = logspace_add(that, next);
        return that;
      };
      ((that = ladd(that,args)),...);
      return that;
    }
    else
    {
      return apply_over(logspace_add, a0, a1, args...);
    }
  }


  //================================================================================================
  // Masked case
  //================================================================================================
  template<conditional_expr C, floating_real_value U, floating_real_value V>
  EVE_FORCEINLINE auto logspace_add_(EVE_SUPPORTS(cpu_), C const &cond, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    return mask_op(  cond, eve::logspace_add, t, f);
  }

  template<conditional_expr C, real_value T0, real_value T1, real_value ...Ts>
  auto logspace_add_(EVE_SUPPORTS(cpu_), C const &cond
                    , T0 a0, T1 a1, Ts... args)
  requires floating_value<common_compatible_t<T0, T1, Ts...>>
  {
    return mask_op(  cond, eve::logspace_add, a0, a1, args...);
  }

}
