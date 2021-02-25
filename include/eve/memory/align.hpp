//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/memory/power_of_2.hpp>
#include <eve/detail/concepts.hpp>
#include <eve/assert.hpp>
#include <cstdint>

namespace eve
{
  enum class over  : std::size_t {};
  enum class under : std::size_t {};

  constexpr inline std::size_t to_integer(over n)  noexcept { return static_cast<std::size_t>(n); }
  constexpr inline std::size_t to_integer(under n) noexcept { return static_cast<std::size_t>(n); }

  template<std::integral T> constexpr auto align(T value, over alignment) noexcept
  {
    auto a = to_integer(alignment);
    EVE_ASSERT(is_power_of_2(a), a << " is not a power of 2.");
    return (value + a - 1) & ~(a - 1);
  }

  template<std::integral T> constexpr auto align(T value, under alignment) noexcept
  {
    auto a = to_integer(alignment);
    EVE_ASSERT(is_power_of_2(a), a << " is not a power of 2.");
    return value & ~(a - 1);
  }

  template<typename T> constexpr auto align(T *ptr, over alignment) noexcept
  {
    return reinterpret_cast<T *>(align(reinterpret_cast<std::uintptr_t>(ptr), alignment));
  }

  template<typename T> constexpr auto align(T *ptr, under alignment) noexcept
  {
    return reinterpret_cast<T *>(align(reinterpret_cast<std::uintptr_t>(ptr), alignment));
  }
}
