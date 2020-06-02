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
#include <eve/function/is_not_equal.hpp>
#include <eve/function/is_ordered.hpp>
#include <eve/function/logical_and.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/skeleton_calls.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<real_value T, real_value U>
  EVE_FORCEINLINE  auto is_lessgreater_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  //  requires compatible_values<T, U>
  {
    return arithmetic_call(is_lessgreater, a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE  auto is_lessgreater_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , T const &b) noexcept
  //  requires has_native_abi_v<T>
  {
    return  (is_not_equal(a, b) && is_ordered(a, b));
  }
}

