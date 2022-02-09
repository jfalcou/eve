//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/numeric.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/numeric/minabs.hpp>


namespace eve::detail
{
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto negminabs_(EVE_SUPPORTS(cpu_), numeric_type const &
                              , T const &a, U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(numeric(negminabs), a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE auto negminabs_(EVE_SUPPORTS(cpu_), numeric_type const &
                              , T const &a, T const &b) noexcept
  {
    return -numeric(minabs)(a, b);
  }

  //================================================================================================
  //N parameters
  //================================================================================================
  template<real_value T0, real_value T1, real_value ...Ts>
  auto negminabs_(EVE_SUPPORTS(cpu_), numeric_type const &, T0 a0, T1 a1, Ts... args)
  {
    return -numeric(eve::minabs)(a0, a1, args...);
  }

}
