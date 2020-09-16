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

#include <eve/detail/abi.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  // Function decorators mark-up used in function overloads
  struct musl_type : decorator_
  {
    template<typename Function> constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return
          [f](auto &&... args) { return f(musl_type {}, std::forward<decltype(args)>(args)...); };
    }
  };

  //================================================================================================
  // Function decorator - musl mode
  template<typename Function> constexpr EVE_FORCEINLINE auto musl_(Function f) noexcept
  {
    return musl_type {}(f);
  }
}

