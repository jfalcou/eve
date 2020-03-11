//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

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
