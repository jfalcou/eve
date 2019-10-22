//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_PEDANTIC_HPP_INCLUDED
#define EVE_FUNCTION_PEDANTIC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>

namespace eve
{
  //================================================================================================
  // Function decorators mark-up used in function overloads
  struct pedantic_type : decorator_
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return  [f](auto&&... args)
              {
                return f(pedantic_type{}, std::forward<decltype(args)>(args)...);
              };
    }
  };

  //================================================================================================
  // Function decorator - pedantic mode
  template<typename Function> constexpr EVE_FORCEINLINE auto pedantic_(Function f) noexcept
  {
    return pedantic_type{}(f);
  }
}

#endif
