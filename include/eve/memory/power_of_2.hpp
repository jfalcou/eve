//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/concepts.hpp>
#include <climits>
#include <cstdint>

namespace eve
{
  template<std::integral T> constexpr bool is_power_of_2(T value) noexcept
  {
    return (!(value & (value - 1)) && value);
  }

  template<std::integral T> constexpr T next_power_of_2(T value) noexcept
  {
    value--;
    for(std::size_t i = 1; i < sizeof(value) * CHAR_BIT; i *= 2) value |= value >> i;

    return ++value;
  }

  template<std::integral T> constexpr T prev_power_of_2(T value) noexcept
  {
    for(std::size_t i = 1; i < sizeof(value) * CHAR_BIT; i *= 2) value |= value >> i;

    return value ? (value >> 1) + 1 : value;
  }
}

