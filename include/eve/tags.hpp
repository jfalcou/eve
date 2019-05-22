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

#include <eve/detail/abi.hpp>
#include <type_traits>

namespace eve
{
  struct pedantic_type{};

  pedantic_type pedantic_{};

  struct raw_type{};

  raw_type raw_{};

  struct saturated_type{};

  saturated_type saturated_{};

  
}

#endif
