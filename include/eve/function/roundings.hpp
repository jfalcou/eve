//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_FUNCTION_ROUNDINGS_HPP_INCLUDED
#define EVE_FUNCTION_ROUNDINGS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>

namespace eve
{
  //================================================================================================
  // Function decorator - upward mode
  struct upward_type : decorator_
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return  [f](auto&&... args)
              {
                return f(upward_type{}, std::forward<decltype(args)>(args)...);
              };
    }
  };

  template<typename Function> constexpr EVE_FORCEINLINE auto upward_(Function f) noexcept
  {
    return upward_type{}(f);
  }


  //================================================================================================
  // Function decorator - downward mode
  struct downward_type : decorator_
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return  [f](auto&&... args)
              {
                return f(downward_type{}, std::forward<decltype(args)>(args)...);
              };
    }
  };

  template<typename Function> constexpr EVE_FORCEINLINE auto downward_(Function f) noexcept
  {
    return downward_type{}(f);
  }

  //================================================================================================
  // Function decorator - to_nearest mode
  struct to_nearest_type : decorator_
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return  [f](auto&&... args)
              {
                return f(to_nearest_type{}, std::forward<decltype(args)>(args)...);
              };
    }
  };

  template<typename Function> constexpr EVE_FORCEINLINE auto to_nearest_(Function f) noexcept
  {
    return to_nearest_type{}(f);
  }

  //================================================================================================
  // Function decorator - toward_zero mode
  struct toward_zero_type : decorator_
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) const noexcept
    {
      return  [f](auto&&... args)
              {
                return f(toward_zero_type{}, std::forward<decltype(args)>(args)...);
              };
    }
  };

  template<typename Function> constexpr EVE_FORCEINLINE auto toward_zero_(Function f) noexcept
  {
    return toward_zero_type{}(f);
  }
}

#endif
