//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  //================================================================================================
  // Masked case
  //================================================================================================
  template<conditional_expr C, real_value U, real_value V>
  EVE_FORCEINLINE auto add_(EVE_SUPPORTS(cpu_), C const &cond, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    return mask_op( EVE_CURRENT_API{}, cond, eve::add, t, f);
  }

  //================================================================================================
  //N parameters
  //================================================================================================
  template<decorator D, real_value T0, real_value T1, real_value ...Ts>
  auto add_(EVE_SUPPORTS(cpu_), D const &, T0 a0, T1 a1, Ts... args)
  {
    auto that = D()(add)(a0,a1);
    ((that = D()(add)(that,args)),...);
    return that;
  }

  template<real_value T0, real_value T1, real_value ...Ts>
  auto add_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args)
  {
    auto that = add(a0,a1);
    ((that = add(that,args)),...);
    return that;
  }
}
