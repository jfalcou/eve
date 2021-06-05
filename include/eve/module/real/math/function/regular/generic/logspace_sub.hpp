//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/constant/log_2.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/expm1.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/max.hpp>
#include <eve/function/log.hpp>
#include <eve/function/log1p.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE  auto logspace_sub_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  -> decltype(arithmetic_call(logspace_sub, a, b))
  {
    return arithmetic_call(logspace_sub, a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE  T logspace_sub_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , T const &b) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto x = if_else(a == b, zero, b-a);
      auto test = x > -log_2(as(x));
      if (eve::all(test)) return  a+eve::log(-expm1(x));
      else if (eve::any(test)) return a+if_else(test, log(-expm1(x)), log1p(-exp(x)));
      else return a + log1p(-exp(x));
    }
    else
    {
      return apply_over(logspace_sub, a, b);
    }
  }

  //===============================================================================================
  // Multi case
  //================================================================================================
  template<floating_real_value T0, floating_real_value T1, real_value ...Ts>
  common_compatible_t<T0,T1, Ts...> logspace_sub_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args)
  {
    using r_t = common_compatible_t<T0,T1,Ts...>;
    if constexpr(has_native_abi_v<r_t>)
    {
      r_t that(logspace_sub(a0, a1));
      auto lsub = [](auto that, auto next)->r_t{
        that = logspace_sub(that, next);
        return that;
      };
      ((that = lsub(that,args)),...);
      return that;
    }
    else
    {
      return apply_over(logspace_sub, a0, a1, args...);
    }
  }

  //================================================================================================
  // Masked case
  //================================================================================================
  template<conditional_expr C, floating_real_value U, floating_real_value V>
  EVE_FORCEINLINE auto logspace_sub_(EVE_SUPPORTS(cpu_), C const &cond, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    return mask_op(  cond, eve::logspace_sub, t, f);
  }

}
