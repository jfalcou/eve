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
#include <eve/detail/function/conditional.hpp>
#include <eve/traits/common_compatible.hpp>

namespace eve::detail
{
  //================================================================================================
  // Masked case
  //================================================================================================
  template<conditional_expr C, typename U, typename V>
  EVE_FORCEINLINE auto add_(EVE_SUPPORTS(cpu_), C const &cond, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    return mask_op(  cond, eve::add, t, f);
  }

  //================================================================================================
  //N parameters
  //================================================================================================
  template<decorator D, typename T0, typename ...Ts>
  auto add_(EVE_SUPPORTS(cpu_), D const &, T0 a0, Ts... args)
    requires (compatible_values<T0, Ts> && ...)
  {
    common_compatible_t<T0,Ts...> that(a0);
    ((that = D()(add)(that,args)),...);
    return that;
  }

  template<typename T0, typename ...Ts>
  auto add_(EVE_SUPPORTS(cpu_), T0 a0, Ts... args)
    requires (compatible_values<T0, Ts> && ...)
  {
    common_compatible_t<T0,Ts...> that(a0);
    ((that = add(that,args)),...);
    return that;
  }
}
