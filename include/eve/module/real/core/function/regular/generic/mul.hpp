//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/function/operators.hpp>
#include <eve/traits/common_compatible.hpp>

namespace eve::detail
{
  //================================================================================================
  // Masked case
  //================================================================================================
  template<conditional_expr C, real_value U, real_value V>
  EVE_FORCEINLINE auto mul_(EVE_SUPPORTS(cpu_), C const &cond, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    return mask_op(  cond, eve::mul, t, f);
  }

  //================================================================================================
  //N parameters
  //================================================================================================
  template<decorator D, real_value T0, real_value T1, real_value ...Ts>
  common_compatible_t<T0,T1,Ts...> mul_(EVE_SUPPORTS(cpu_), D const &, T0 a0, T1 a1, Ts... args)
  {
    common_compatible_t<T0,T1,Ts...> that(D()(mul)(a0,a1));
    ((that = D()(mul)(that,args)),...);
    return that;
  }

  template<real_value T0, real_value T1, real_value ...Ts>
  common_compatible_t<T0,T1,Ts...> mul_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args)
  {
    common_compatible_t<T0,T1,Ts...> that(mul(a0,a1));
    ((that = mul(that,args)),...);
    return that;
  }
}
