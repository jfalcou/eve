//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_FDIM_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_FDIM_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/function/sub.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<real_value T, real_value U>
  EVE_FORCEINLINE  auto fdim_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(fdim, a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE  T fdim_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , T const &b) noexcept
  requires has_native_abi_v<T>
  {
    return if_else(is_not_less_equal(a, b),  a-b, eve::zero_);
  }
}

#endif
