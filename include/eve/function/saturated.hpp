//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_SATURATED_HPP_INCLUDED
#define EVE_FUNCTION_SATURATED_HPP_INCLUDED

#include <type_traits>
#include <eve/detail/abi.hpp>
#include <iostream>
namespace eve
{
  //================================================================================================
  // Function decorators mark-up used in function overloads
  struct saturated_type
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) noexcept
    {
      return [f](auto const &... args) { return f(saturated_type{}, args...); };
    }
  };
  
  //================================================================================================
  // Function decorator - saturated mode
  template<typename Function>
  constexpr EVE_FORCEINLINE auto saturated_(Function f) noexcept
  {
    return saturated_type{}(f);
  }
}

#endif
