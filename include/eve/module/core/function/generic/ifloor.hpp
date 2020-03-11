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

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/floor.hpp>
#include <eve/function/toint.hpp>
#include <type_traits>

namespace eve::detail
{
  ////////////////////////////////////////////////
  // saturated_
  template<typename T>
  EVE_FORCEINLINE constexpr auto ifloor_(EVE_SUPPORTS(cpu_)
                                      , T const &a) noexcept
  {
    if constexpr(std::is_floating_point_v<value_type_t<T>>)
    {
      return saturated_(toint)(eve::floor(a));

    }
    else // if constexpr(std::is_integral_v<value_type_t<T>>)
    {
      return a; 
    }
  }
}

#endif
