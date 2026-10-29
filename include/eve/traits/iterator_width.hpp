//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/width.hpp>
#include <eve/traits/value_type.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup eve_traits
  //! @{
  //!  @tparam T Type to process
  //!
  //!  @brief A meta-function that returns a width for a relaxed iterator/range.
  //!         If T defines a nested static function `iterator_width()` (which should return eve::lanes_t)
  //!         - returns it's return type.
  //!         Otherwise returns `lanes_t<expected_width_v<value_type_t<T>>>`.
  //!
  //!  *NOTE*: for aligned_ptr we return expected_width.
  //!
  //!  **Required header**: `#include <eve/traits/iterator_width.hpp>`,
  //!                       `#include <eve/traits.hpp>`
  //!   @code{.cpp}
  //!   template<typename T>
  //!   inline constexpr auto iterator_width_v = iterator_width<T>::value;
  //!   @endcode
  //! @}
  //================================================================================================

  //================================================================================================
  //! @addtogroup eve_traits 
  //! @{
  //!   @brief Computes the fundamental width of a given type
  //!
  //!   **Required header:** `#include <eve/traits/iteartor_width.hpp>`
  //!
  //!   @note For aligned_ptr we return expected_width.
  //!
  //!
  //!   @ref eve::iterator_width_v returns a width for a relaxed iterator/range.
  //!         If T defines a nested static constexpr function `iterator_width()` (which should return a eve::width_type)
  //!         - returns the value.
  //!         - returns `expected_width_v<value_type_t<T>>` otherwise.
  //!
  //!   @tparam Type  Type of value to assess
  //!
  //! @}
  //================================================================================================

  template <typename T>
  inline constexpr width_type iterator_width_v = expected_width_v<value_type_t<T>>;

  template<typename T>
  requires requires{ typename std::integral_constant<width_type, T::iterator_width()>; }
  inline constexpr width_type iterator_width_v<T> = T::iterator_width();
}
