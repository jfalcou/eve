//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_NUMERIC_HPP_INCLUDED
#define EVE_FUNCTION_NUMERIC_HPP_INCLUDED

#include <type_traits>
#include <eve/detail/abi.hpp>

namespace eve
{
  //================================================================================================
  // Function decorators mark-up used in function overloads
  struct numeric_type
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) noexcept
    {
      return [f](auto const &... args) { return f(numeric_type{}, args...); };
    }
  };
  
  //================================================================================================
  // Function decorator - numeric mode
  template<typename Function>
  constexpr EVE_FORCEINLINE auto numeric_(Function f) noexcept
  {
    return numeric_type{}(f);
  }
}

#endif
