//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/wide_forward.hpp>
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
}
