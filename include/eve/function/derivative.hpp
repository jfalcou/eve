//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>

namespace eve
{
  //================================================================================================
  // Function decorators mark-up used in function overloads
  template < unsigned PARAM = 1u>
  struct derivative_type : decorator_
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return  [f](auto&&... args)
              {
                return f(derivative_type<PARAM>{}, std::forward<decltype(args)>(args)...);
              };
    }
  };

  //================================================================================================
  // Function decorator - derivative mode
  inline constexpr derivative_type<1>  const derivative = {};
  inline constexpr derivative_type<1> const derivative_1st = {};
  inline constexpr derivative_type<2> const derivative_2nd = {};
  inline constexpr derivative_type<3> const derivative_3rd
}
