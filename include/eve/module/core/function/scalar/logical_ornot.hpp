//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_LOGICAL_ORNOT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_LOGICAL_ORNOT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/logical.hpp>
#include <eve/function/logical_not.hpp>
#include <eve/function/logical_or.hpp>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr as_logical_t<T>
  logical_ornot_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  {
    return (a || !b);
  }

  
  template<typename T>
  EVE_FORCEINLINE constexpr as_logical_t<T>
  logical_ornot_(EVE_SUPPORTS(cpu_), logical<T> const &a, logical<T> const &b) noexcept
  {
    return logical_or(a, logical_not(b));
  }    
}

#endif
