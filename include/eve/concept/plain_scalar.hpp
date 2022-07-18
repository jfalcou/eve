//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <type_traits>

namespace eve
{
namespace detail
{
  template<typename T> struct is_natural : std::false_type {};

  template<typename T>
  requires(std::integral<T> && (sizeof(T) <= 8) && !detail::one_of<T, bool, char>)
  struct is_natural<T> : std::true_type {};

  template<typename T>
  inline constexpr bool is_natural_v = is_natural<T>::value;
}

template<typename T>
concept plain_scalar_value = detail::one_of<T, float, double> || detail::is_natural_v<T>;
}
