//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/function/operators.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/function/derivative.hpp>

namespace eve::detail
{

  //================================================================================================
  // Masked case
  //================================================================================================
  template<conditional_expr C, real_value U, real_value V>
  EVE_FORCEINLINE auto sub_(EVE_SUPPORTS(cpu_), C const &cond, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    return mask_op(  cond, eve::sub, t, f);
  }


  //================================================================================================
  //N parameters
  //================================================================================================
  template<decorator D, real_value T0, real_value ...Ts>
  auto sub_(EVE_SUPPORTS(cpu_), D const &, T0 a0, Ts... args)
    requires (compatible_values<T0, Ts> && ...)
  {
    common_compatible_t<T0,Ts...> that(a0);
    ((that = D()(sub)(that,args)),...);
    return that;
  }

  template<real_value T0, real_value ...Ts>
  auto sub_(EVE_SUPPORTS(cpu_), T0 a0, Ts... args)
    requires (compatible_values<T0, Ts> && ...)
  {
    common_compatible_t<T0,Ts...> that(a0);
    ((that = sub(that,args)),...);
    return that;
  }
}
