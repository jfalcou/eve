//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic/regular/abs.hpp>
#include <eve/module/arithmetic/regular/is_nan.hpp>
#include <eve/module/arithmetic/regular/is_not_greater_equal.hpp>
#include <eve/module/arithmetic/regular/min.hpp>
#include <eve/module/arithmetic/regular/minus.hpp>

namespace eve::detail
{
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto negabsmin_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(negabsmin, a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE auto negabsmin_(EVE_SUPPORTS(cpu_), T const &a, T const &b) noexcept
  requires has_native_abi_v<T>
  {
    return  minus(eve::abs(eve::min(a, b)));
  }

  //================================================================================================
  // Masked case
  //================================================================================================
  template<decorator D, conditional_expr C, real_value U, real_value V>
  EVE_FORCEINLINE auto negabsmin_(EVE_SUPPORTS(cpu_), C const &cond, D const &
                              , U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    return mask_op(  cond, D()(eve::negabsmin), t, f);
  }

  template<conditional_expr C, real_value U, real_value V>
  EVE_FORCEINLINE auto negabsmin_(EVE_SUPPORTS(cpu_), C const &cond, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    return mask_op(  cond, eve::negabsmin, t, f);
  }

  //================================================================================================
  // N parameters
  //================================================================================================
  template<real_value T0, real_value T1, real_value ...Ts>
  common_compatible_t<T0,T1,Ts...> negabsmin_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args)
  {
    return minus(eve::abs(eve::min(a0, a1, args...)));
  }
}
