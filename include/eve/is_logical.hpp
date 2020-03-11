//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_IS_LOGICAL_HPP_INCLUDED
#define EVE_IS_LOGICAL_HPP_INCLUDED

#include <eve/forward.hpp>
#include <type_traits>

namespace eve
{
  template<typename T>
  struct is_logical : std::false_type
  {
  };

  template<typename T>
  struct is_logical<logical<T>> : std::true_type
  {
  };

  template<typename T>
  using is_logical_t = typename is_logical<T>::type;

  template<typename T>
  static inline constexpr bool is_logical_v = is_logical<T>::value;

  template<typename T>
  using Logical = std::enable_if_t<is_logical_v<T>>;
}

#endif
