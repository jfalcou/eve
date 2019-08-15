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
  struct regular_type   {
    template<typename Function> constexpr EVE_FORCEINLINE auto operator()(Function f) noexcept
    {
      return [f](auto const&... args) { return f(args...); };
    }
  };
  struct raw_type       {
    template<typename Function> constexpr EVE_FORCEINLINE auto operator()(Function f) noexcept
    {
      return [f](auto const&... args) { return f(raw_type{}, args...); };
    }

  };
  struct pedantic_type  {
    template<typename Function> constexpr EVE_FORCEINLINE auto operator()(Function f) noexcept
    {
      return [f](auto const&... args) { return f(pedantic_type{}, args...); };
    }
  };
  struct saturated_type {
    template<typename Function> constexpr EVE_FORCEINLINE auto operator()(Function f) noexcept
    {
      return [f](auto const&... args) { return f(saturated_type{}, args...); };
    }
  };
  struct numeric_type   {
    template<typename Function> constexpr EVE_FORCEINLINE auto operator()(Function f) noexcept
    {
      return [f](auto const&... args) { return f(numeric_type{}, args...); };
    }
  };

  //================================================================================================
  // Function decorator - regular mode
  template<typename Function> constexpr EVE_FORCEINLINE auto regular_(Function f) noexcept
  {
    return regular_type{}(f); 
  }

  //================================================================================================
  // Function decorator - raw mode
  template<typename Function> constexpr EVE_FORCEINLINE auto raw_(Function f) noexcept
  {
    return raw_type{}(f); 
  }

  //================================================================================================
  // Function decorator - pedantic mode
  template<typename Function> constexpr EVE_FORCEINLINE auto pedantic_(Function f) noexcept
  {
    return pedantic_type{}(f); 
  }

  //================================================================================================
  // Function decorator - saturated mode
  template<typename Function> constexpr EVE_FORCEINLINE auto saturated_(Function f) noexcept
  {
    return saturated_type{}(f); 
  }

  //================================================================================================
  // Function decorator - numeric mode
  template<typename Function> constexpr EVE_FORCEINLINE auto numeric_(Function f) noexcept
  {
    return numeric_type{}(f); 
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
