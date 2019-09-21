//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_REGULAR_HPP_INCLUDED
#define EVE_FUNCTION_REGULAR_HPP_INCLUDED

#include <type_traits>
#include <eve/detail/abi.hpp>

namespace eve
{
  //================================================================================================
  // Function decorators mark-up used in function overloads
  struct regular_type
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) noexcept
    {
      return [f](auto const &... args) { return f(args...); };
    }
  };
  
  //================================================================================================
  // Function decorator - regular mode
  template<typename Function>
  constexpr EVE_FORCEINLINE auto regular_(Function f) noexcept
  {
    return regular_type{}(f);
  }
}

#endif
