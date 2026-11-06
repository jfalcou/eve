//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/traits/width.hpp>
#include <eve/traits/value_type.hpp>

namespace eve
{
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
  //!   Returns a width for a relaxed iterator/range.
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
