//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_TAGS_HPP_INCLUDED
#define EVE_TAGS_HPP_INCLUDED

#include <type_traits>
#include <eve/detail/abi.hpp>

namespace eve
{
  //================================================================================================
  // Function decorators mark-up used in function overloads
  struct raw_type       {};
  struct pedantic_type  {};
  struct saturated_type {};
  struct numeric_type   {};

  //================================================================================================
  // Function decorator - raw mode
  template<typename Function> constexpr EVE_FORCEINLINE auto raw_(Function f) noexcept
  {
    return [f](auto const&... args) { return f(raw_type{}, args...); };
  }

  //================================================================================================
  // Function decorator - pedantic mode
  template<typename Function> constexpr EVE_FORCEINLINE auto pedantic_(Function f) noexcept
  {
    return [f](auto const&... args) { return f(pedantic_type{}, args...); };
  }

  //================================================================================================
  // Function decorator - saturated mode
  template<typename Function> constexpr EVE_FORCEINLINE auto saturated_(Function f) noexcept
  {
    return [f](auto const&... args) { return f(saturated_type{}, args...); };
  }

  //================================================================================================
  // Function decorator - numeric mode
  template<typename Function> constexpr EVE_FORCEINLINE auto numeric_(Function f) noexcept
  {
    return [f](auto const&... args) { return f(numeric_type{}, args...); };
  }

  //================================================================================================
  // Option types and objects
  struct upward_type      {};
  struct downward_type    {};
  struct toward_zero_type {};
  struct to_nearest_type  {};

  inline constexpr upward_type      upward_       = {};
  inline constexpr downward_type    downward_     = {};
  inline constexpr toward_zero_type toward_zero_  = {};
  inline constexpr to_nearest_type  to_nearest_   = {};
}

#endif
