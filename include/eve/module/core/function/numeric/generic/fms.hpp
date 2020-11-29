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
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/numeric.hpp>


namespace eve::detail
{
  template<real_value T, real_value U, real_value V>
  EVE_FORCEINLINE auto fms_(EVE_SUPPORTS(cpu_), numeric_type const &
                           , T const &a, U const &b, V const &c) noexcept
  requires compatible_values<T, U> &&compatible_values<T, V>
  {
    return arithmetic_call(numeric(fms), a, b, c);
  }

  template<real_value T>
  EVE_FORCEINLINE T fms_(EVE_SUPPORTS(cpu_), numeric_type const &
                        , T const &a, T const &b, T const &c) noexcept
  requires has_native_abi_v<T>
  {
    return numeric(fma)(a, b, T(-c));
  }
}
