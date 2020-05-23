//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_ICEIL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_ICEIL_HPP_INCLUDED

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/ceil.hpp>
#include <eve/function/toint.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr auto iceil_(EVE_SUPPORTS(cpu_)
                                       , T const &a) noexcept
  {
         if constexpr(floating_value<T>)  return saturated_(toint)(eve::ceil(a));
    else if constexpr(integral_value<T>)  return a;
  }
}

#endif
