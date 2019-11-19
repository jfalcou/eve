//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_PLAIN_HPP_INCLUDED
#define EVE_FUNCTION_PLAIN_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>

namespace eve
{
  //================================================================================================
  // Function decorators mark-up used in function overloads
  struct plain_type : decorator_
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return  [f](auto&&... args)
              {
                return f(plain_type{}, std::forward<decltype(args)>(args)...);
              };
    }
  };

  //================================================================================================
  // Function decorator - plain mode
  template<typename Function> constexpr EVE_FORCEINLINE auto plain_(Function f) noexcept
  {
    return plain_type{}(f);
  }
}

#endif
