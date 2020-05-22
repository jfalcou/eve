//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MEMORY_ALIGN_HPP_INCLUDED
#define EVE_MEMORY_ALIGN_HPP_INCLUDED

#include <eve/memory/power_of_2.hpp>
#include <concepts>
#include <eve/assert.hpp>
#include <cstdint>

namespace eve
{
  enum class over  : std::size_t {};
  enum class under : std::size_t {};

  std::size_t as_integer(over n)  { return static_cast<std::size_t>(n); }
  std::size_t as_integer(under n) { return static_cast<std::size_t>(n); }

  template<std::integral T> constexpr auto align(T value, over alignment) noexcept
  {
    auto a = as_integer(alignment);
    EVE_ASSERT(is_power_of_2(a), a << " is not a power of 2.");
    return (value + a - 1) & ~(a - 1);
  }

  template<std::integral T> constexpr auto align(T value, under alignment) noexcept
  {
    auto a = as_integer(alignment);
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

#endif
