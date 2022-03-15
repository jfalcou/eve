//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/decorator/pedantic.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/saturated/abs.hpp>
#include <eve/module/core/pedantic/absmin.hpp>
#include <eve/platform.hpp>

#include <type_traits>

namespace eve::detail
{
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto negabsmin_(EVE_SUPPORTS(cpu_), pedantic_type const &, T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(pedantic(negabsmin), a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE auto negabsmin_(EVE_SUPPORTS(cpu_), pedantic_type const &, T const &a, T const &b) noexcept
  {
    return -pedantic(absmin)(a, b);
  }


  //================================================================================================
  //N parameters
  //================================================================================================
  template<real_value T0, real_value T1, real_value ...Ts>
  auto negabsmin_(EVE_SUPPORTS(cpu_), pedantic_type const &, T0 a0, T1 a1, Ts... args)
  {
    return -pedantic(eve::absmin)(a0, a1, args...);
  }
}
