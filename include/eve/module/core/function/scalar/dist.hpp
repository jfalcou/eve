//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_DIST_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_DIST_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <type_traits>
#include <eve/function/scalar/abs.hpp>
#include <eve/function/scalar/max.hpp>
#include <eve/function/scalar/min.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/tags.hpp>
#include <eve/concept/vectorizable.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto dist_(EVE_SUPPORTS(cpu_)
                                     , T const &a0
                                     , T const &a1) noexcept
  requires(T, Arithmetic<T>)
  {
    if constexpr(std::is_integral_v<T>)
      return max(a0, a1)-min(a0, a1);
    else
      return eve::abs(a1-a0); 
  }
  
  // -----------------------------------------------------------------------------------------------
  // saturated case
  template<typename T>
  EVE_FORCEINLINE constexpr auto dist_(EVE_SUPPORTS(cpu_)
                                     , saturated_type const &
                                     , T const &a0
                                     , T const &a1) noexcept
  requires(T, Arithmetic<T>)
  {
    if constexpr(std::is_integral_v<T> && std::is_signed_v<T>)
    {
      auto tmp = dist(a0, a1);
      return bool(is_ltz(tmp)) ? Valmax(as(a0)) : tmp;
    }
    else
      return dist(a0, a1); 
  }  
    
}

#endif
