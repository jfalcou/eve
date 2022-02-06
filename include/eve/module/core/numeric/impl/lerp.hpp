//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/numeric/fma.hpp>
#include <eve/module/core/numeric/fnma.hpp>
#include <type_traits>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U, floating_real_value V>
  EVE_FORCEINLINE auto lerp_(EVE_SUPPORTS(cpu_), numeric_type const&
                            , T const &a, U const &b, V const &t) noexcept
      requires compatible_values<T, U> &&compatible_values<T, V>
  {
    return arithmetic_call(numeric(lerp), a, b, t);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T lerp_(EVE_SUPPORTS(cpu_), numeric_type const&
                         , T const &a, T const &b, T const &t) noexcept
  {
    return numeric(fma)(t, b, numeric(fnma)(t, a, a));
  }
}
