//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_CLAMP_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_CLAMP_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/function/min.hpp>
#include <eve/function/max.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<real_value T, real_value U, real_value V>
  EVE_FORCEINLINE auto clamp_(EVE_SUPPORTS(cpu_)
                                  , T const &a
                                  , U const &b
                                  , V const &c) noexcept
  requires compatible_values<T,U> && compatible_values<T,V>
  {
    return arithmetic_call(clamp, a, b, c);
  }

  template<real_value T>
  EVE_FORCEINLINE auto clamp_(EVE_SUPPORTS(cpu_)
                                  , T const &a
                                  , T const &b
                                  , T const &c) noexcept
  requires has_native_abi_v<T>
  {
    return eve::min(eve::max(a, b), c);
  }
}

#endif
