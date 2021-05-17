//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <cstdint>
#include <eve/memory/power_of_2.hpp>
#include <eve/detail/concepts.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup memory
  //! @{
  //================================================================================================
  //! @brief Checks if a pointer satisfy an alignment constraint.
  //!
  //! @param  v           Integral value to check.
  //! @tparam Alignment   Alignment constraint to verify. Behavior is undefined if this constraint
  //!                     is not a power of 2.
  //!
  //! @return `true` if `ptr` is aligned over `Alignment`, `false` otherwise.
  //================================================================================================
  template<std::size_t Alignment, std::integral T>
  constexpr bool is_aligned(T v) noexcept
  {
    static_assert(is_power_of_2(Alignment), "[eve] Alignment must be a power of 2");
    return (v & (Alignment - 1)) == 0;
  }

  //================================================================================================
  //! @brief Checks if a pointer satisfy an alignment constraint.
  //!
  //! @param  ptr         Pointer to check
  //! @tparam Alignment   Alignment constraint to verify. Behavior is undefined if this constraint
  //!                     is not a power of 2.
  //!
  //! @return `true` if `ptr` is aligned over `Alignment`, `false` otherwise.
  //================================================================================================
  template<std::size_t Alignment, typename T>
  constexpr bool is_aligned(T *ptr) noexcept
  {
    static_assert(is_power_of_2(Alignment), "[eve] Alignment must be a power of 2");
    return is_aligned<Alignment>(reinterpret_cast<std::uintptr_t>(ptr));
  }
  //================================================================================================
  //! @}
  //================================================================================================
}

