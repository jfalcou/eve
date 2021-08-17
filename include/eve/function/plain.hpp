//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  // Function decorators mark-up used in function overloads
  struct plain_type : decorator_
  {
    template<typename Function> constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return
          [f](auto &&... args) { return f(plain_type {}, std::forward<decltype(args)>(args)...); };
    }
  };

  //================================================================================================
  // Function decorator - plain mode
  template<typename Function> constexpr EVE_FORCEINLINE auto plain(Function f) noexcept
  {
    return plain_type {}(f);
  }
}

