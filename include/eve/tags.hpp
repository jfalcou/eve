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
  struct restricted_type
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) noexcept
    {
      return [f](auto const &... args) { return f(restricted_type{}, args...); };
    }
  };
  struct small_type
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) noexcept
    {
      return [f](auto const &... args) { return f(small_type{}, args...); };
    }
  };
  struct cephes_type
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) noexcept
    {
      return [f](auto const &... args) { return f(cephes_type{}, args...); };
    }
  };
  struct medium_type
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) noexcept
    {
      return [f](auto const &... args) { return f(medium_type{}, args...); };
    }
  };
  struct big_type
  {
    template<typename Function>
    constexpr EVE_FORCEINLINE auto operator()(Function f) noexcept
    {
      return [f](auto const &... args) { return f(big_type{}, args...); };
    }
  };

  //================================================================================================
  // Function decorator - restricted mode
  template<typename Function>
  constexpr EVE_FORCEINLINE auto restricted_(Function f) noexcept
  {
    return restricted_type{}(f);
  }

  //================================================================================================
  // Function decorator - small mode
  template<typename Function>
  constexpr EVE_FORCEINLINE auto small_(Function f) noexcept
  {
    return small_type{}(f);
  }

   //================================================================================================
  // Function decorator - cephes mode
  template<typename Function>
  constexpr EVE_FORCEINLINE auto cephes_(Function f) noexcept
  {
    return cephes_type{}(f);
  }

    //================================================================================================
  // Function decorator - medium mode
  template<typename Function>
  constexpr EVE_FORCEINLINE auto medium_(Function f) noexcept
  {
    return medium_type{}(f);
  }
    //================================================================================================
  // Function decorator - big mode
  template<typename Function>
  constexpr EVE_FORCEINLINE auto big_(Function f) noexcept
  {
    return big_type{}(f);
  }
  
  //================================================================================================
  // Option types and objects
  struct upward_type
  {
  };
  struct downward_type
  {
  };
  struct toward_zero_type
  {
  };
  struct to_nearest_type
  {
  };

  inline constexpr upward_type      upward_      = {};
  inline constexpr downward_type    downward_    = {};
  inline constexpr toward_zero_type toward_zero_ = {};
  inline constexpr to_nearest_type  to_nearest_  = {};
}

#endif
