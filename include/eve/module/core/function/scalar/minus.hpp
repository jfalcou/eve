//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_MINUS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_MINUS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/sub.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr T minus_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    return -a;
  }
  
  // -----------------------------------------------------------------------------------------------
  // conditionnal  case
  template<typename T,  typename U>
  EVE_FORCEINLINE constexpr T minus_(EVE_SUPPORTS(cpu_)
                                          , U const &cond 
                                          , T const &a) noexcept
  {
    return cond ? -a : a;
  }

}

#endif
