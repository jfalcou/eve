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

namespace eve
{
  //================================================================================================
  // Rounding decorator types
  struct upward_type : decorator_
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return  [f](auto const&... args)
              {
                return f(upward_type{}, args...);
              };
    }
  };

  struct downward_type : decorator_
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return  [f](auto const&... args)
              {
                return f(downward_type{}, args...);
              };
    }
  };

  struct to_nearest_type : decorator_
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return  [f](auto const&... args)
              {
                return f(to_nearest_type{}, args...);
              };
    }
  };

  struct toward_zero_type : decorator_
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return  [f](auto const&... args)
              {
                return f(toward_zero_type{}, args...);
              };
    }
  };

  //================================================================================================
  // Rounding decorator objects
  inline constexpr upward_type      const upward       = {};
  inline constexpr downward_type    const downward     = {};
  inline constexpr to_nearest_type  const to_nearest   = {};
  inline constexpr toward_zero_type const toward_zero  = {};
}

