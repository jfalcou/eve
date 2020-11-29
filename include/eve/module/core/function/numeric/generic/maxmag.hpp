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
#include <eve/function/abs.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/numeric.hpp>
#include <eve/platform.hpp>

#include <type_traits>

namespace eve::detail
{
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto maxmag_(EVE_SUPPORTS(cpu_), numeric_type const &, T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(numeric(maxmag), a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE auto maxmag_(EVE_SUPPORTS(cpu_), numeric_type const &, T const &a, T const &b) noexcept
  {
    auto aa = if_else(is_nan(a), b, a);
    auto bb = if_else(is_nan(b), a, b);
    auto z  = maxmag(aa, bb);
    return z;
  }
}
