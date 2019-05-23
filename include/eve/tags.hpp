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

  struct up_type{};
  inline constexpr up_type up_ = {};

  struct down_type{};
  inline constexpr down_type down_ = {};

  struct to_zero_type{};
  inline constexpr to_zero_type to_zero_ = {};

  struct nearest_int_type{};
 inline constexpr  nearest_int_type nearest_int_ = {};
}

#endif
