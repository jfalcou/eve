//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <bit>
#include <concepts>
#include <cstdint>

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
    static_assert(std::has_single_bit(Alignment), "[eve] Alignment must be a power of 2");
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
    static_assert(std::has_single_bit(Alignment), "[eve] Alignment must be a power of 2");
    return is_aligned<Alignment>(reinterpret_cast<std::uintptr_t>(ptr));
  }

  //================================================================================================
  //! @brief Checks if a pointer satisfy an alignment constraint.
  //!
  //! @param  ptr   Pointer to check
  //! @param  lanes Alignment constraint to verify expressed as a SIMD register number of lanes.
  //!
  //! @return `true` if `ptr` is aligned over the alignment implied by `lanes`, `false` otherwise.
  //================================================================================================
  template<typename T, typename Lanes>
#if !defined(EVE_DOXYGEN_INVOKED)
  constexpr bool is_aligned(T *ptr, Lanes) noexcept
#else
  constexpr bool is_aligned(T *ptr, Lanes lanes) noexcept
#endif
  {
    return is_aligned<sizeof(T) * Lanes::value>(ptr);
  }
  //================================================================================================
  //! @}
  //================================================================================================
}
