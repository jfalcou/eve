//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/assert.hpp>
#include <bit>
#include <concepts>
#include <cstdint>

namespace eve
{
  //================================================================================================
  //! @addtogroup memory
  //! @{
  //! @enum over
  //! **Required header:**
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/memory/align.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  enum class over : std::size_t {};
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //! <br/>
  //! Strong integral type that represents the notion of over-alignment constraints.
  //!
  //! #### Non-Member Function
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  constexpr inline std::size_t to_integer(over n)  noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! Equivalent to: `return std::size_t(n);`
  //!
  //! @see under
  //! @}
  //================================================================================================
  enum class over : std::size_t {};
  constexpr inline  std::size_t to_integer(over n)  noexcept { return static_cast<std::size_t>(n); }

  //================================================================================================
  //! @addtogroup memory
  //! @{
  //! @enum under
  //! **Required header:**
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/memory/align.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  enum class under : std::size_t {};
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //! <br/>
  //! Strong integral type that represents the notion of under-alignment constraints.
  //!
  //! #### Non-Member Function
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  constexpr inline std::size_t to_integer(under n)  noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! Equivalent to: `return std::size_t(n);`
  //!
  //! @see over
  //! @}
  //================================================================================================
  enum class under : std::size_t {};
  constexpr inline std::size_t to_integer(under n) noexcept { return static_cast<std::size_t>(n); }

  //================================================================================================
  //! @addtogroup memory
  //! @{
  //================================================================================================
  //! @brief Realigns integral value over a given power-of-2 alignment constraint.
  //!
  //! @param v          Integral value to realign
  //! @param alignment  Alignment constraint to apply. Behavior is undefined if this constraint
  //!                   is not a power of 2.
  //!
  //! @return An integer value greater or equal to `v` which is a multiple of `alignment`
  //!
  //! @see align(T  v, under alignment)
  //! @see align(T* v, over alignment)
  //! @see align(T* v, under alignment)
  //================================================================================================
  template<std::integral T> constexpr auto align(T v, over alignment) noexcept
  {
    auto const a = to_integer(alignment);
    EVE_ASSERT(std::has_single_bit(a), a << " is not a power of 2.");
    return (v + a - 1) & ~(a - 1);
  }

  //================================================================================================
  //! @brief Realigns integral value under a given power-of-2 alignment constraint.
  //!
  //! @param v          Integral value to realign
  //! @param alignment  Alignment constraint to apply. Behavior is undefined if this constraint
  //!                   is not a power of 2.
  //!
  //! @return An integer value lesser or equal to `v` which is a multiple of `alignment`
  //!
  //! @see align(T  v, over alignment)
  //! @see align(T* v, over alignment)
  //! @see align(T* v, under alignment)
  //================================================================================================
  template<std::integral T> constexpr auto align(T v, under alignment) noexcept
  {
    auto const a = to_integer(alignment);
    EVE_ASSERT(std::has_single_bit(a), a << " is not a power of 2.");
    return v & ~(a - 1);
  }

  //================================================================================================
  //! @brief Realigns a pointer over a given power-of-2 alignment constraint.
  //!
  //! @param ptr        Pointer to realign
  //! @param alignment  Alignment constraint to apply. Behavior is undefined if this constraint
  //!                   is not a power of 2.
  //!
  //! @return A pointer to `T` which address is greater or equal to `ptr` and which value is a
  //!         multiple of `alignment`.
  //!
  //! @see align(T  v, over alignment)
  //! @see align(T  v, under alignment)
  //! @see align(T* v, under alignment)
  //================================================================================================
  template<typename T> constexpr auto align(T *ptr, over alignment) noexcept
  {
    return reinterpret_cast<T *>(align(reinterpret_cast<std::uintptr_t>(ptr), alignment));
  }

  //================================================================================================
  //! @brief Realigns a pointer under a given power-of-2 alignment constraint.
  //!
  //! @param ptr        Pointer to realign
  //! @param alignment  Alignment constraint to apply. Behavior is undefined if this constraint
  //!                   is not a power of 2.
  //!
  //! @return A pointer to `T` which address is lesser or equal to `ptr` and which value is a
  //!         multiple of `alignment`.
  //!
  //! @see align(T  v, over alignment)
  //! @see align(T  v, under alignment)
  //! @see align(T* v, over alignment)
  //================================================================================================
  template<typename T> constexpr auto align(T *ptr, under alignment) noexcept
  {
    return reinterpret_cast<T *>(align(reinterpret_cast<std::uintptr_t>(ptr), alignment));
  }
  //================================================================================================
  //! @}
  //================================================================================================
}
