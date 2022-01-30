//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic/pedantic/fms.hpp>

namespace eve::detail
{
  template<real_value T, real_value U, real_value V>
  EVE_FORCEINLINE auto
  fsm_(EVE_SUPPORTS(cpu_), pedantic_type const &
      , T const &a, U const &b, V const &c) noexcept
      requires compatible_values<T, U> && compatible_values<T, V>
  {
    return arithmetic_call(pedantic(fsm), a, b, c);
  }

  template<real_value T>
  EVE_FORCEINLINE T fsm_(EVE_SUPPORTS(cpu_), pedantic_type const &
                        , T const &a, T const &b, T const &c) noexcept
  requires has_native_abi_v<T>
  {
    return pedantic(fms)(b, c, a);
  }
}
