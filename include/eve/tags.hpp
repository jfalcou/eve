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

namespace eve
{
  struct pedantic_type{};
  inline constexpr pedantic_type pedantic_ = {};

  struct raw_type{};
  inline constexpr raw_type raw_ = {};

  struct saturated_type{};
  inline constexpr saturated_type saturated_ = {};

  struct numeric_type{};
  inline constexpr numeric_type numeric_ = {};
}

#endif
