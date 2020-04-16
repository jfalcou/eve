//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_IFLOOR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_IFLOOR_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/concept/value.hpp>
#include <eve/function/floor.hpp>
#include <eve/function/toint.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr auto ifloor_(EVE_SUPPORTS(cpu_)
                                       , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
              if constexpr(floating_value<T>)  return saturated_(toint)(eve::floor(a));
         else if constexpr(integral_value<T>)  return a;
    }
    else                                       return apply_over(ifloor, a);
  }
}

#endif
