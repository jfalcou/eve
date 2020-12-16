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

#include <eve/detail/implementation.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_less.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular
  template<real_value T, real_value U>
  EVE_FORCEINLINE  auto max_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(max, a, b);
  }

  template<real_scalar_value T>
  EVE_FORCEINLINE  auto max_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , T const &b) noexcept
  {
    return if_else(is_less(a, b), b, a);
  }

  template<real_simd_value T>
  EVE_FORCEINLINE  auto max_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , T const &b) noexcept
  {
    return apply_over(max, a, b);
  }
}
