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
  // Trigonometric decorators
  struct restricted_type : decorator_
  {
    template<typename Function> constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return [f](auto const &... args) { return f(restricted_type {}, args...); };
    }
  };

  struct small_type : decorator_
  {
    template<typename Function> constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return [f](auto const &... args) { return f(small_type {}, args...); };
    }
  };

  struct medium_type : decorator_
  {
    template<typename Function> constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return [f](auto const &... args) { return f(medium_type {}, args...); };
    }
  };

  struct big_type : decorator_
  {
    template<typename Function> constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return [f](auto const &... args) { return f(big_type {}, args...); };
    }
  };

  //================================================================================================
  // Trigonometric decorator objects
  inline constexpr restricted_type  const restricted = {};
  inline constexpr small_type       const small      = {};
  inline constexpr medium_type      const medium     = {};
  inline constexpr big_type         const big        = {};
}
