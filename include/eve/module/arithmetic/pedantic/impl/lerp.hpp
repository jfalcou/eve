//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic/pedantic/fma.hpp>
#include <eve/module/arithmetic/pedantic/fnma.hpp>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U, floating_real_value V>
  EVE_FORCEINLINE auto lerp_(EVE_SUPPORTS(cpu_), pedantic_type const &
                            , T const &a, U const &b, V const &t) noexcept
      requires compatible_values<T, U> &&compatible_values<T, V>
  {
    return arithmetic_call(pedantic(lerp), a, b, t);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T lerp_(EVE_SUPPORTS(cpu_), pedantic_type const &
                         , T const &a, T const &b, T const &t) noexcept
  {
    return pedantic(fma)(t, b, pedantic(fnma)(t, a, a));
  }
}
