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
  namespace _
  {
    template <typename T>
    constexpr auto iterator_width_impl()
    {
      if constexpr ( requires { T::iterator_width(); } ) return decltype(T::iterator_width()){};
      else                                                  return expected_width_t<value_type_t<T>>{};
    }
  }

  //================================================================================================
  //! @addtogroup eve_traits
  //! @{
  //!  @typedef iterator_width_t
  //!
  //!  @tparam T Type to process
  //!
  //!  @brief A meta-function that returns a width for a relaxed iterator/range.
  //!         If T defines a nested static function `iterator_width()` (which should return eve::fixed)
  //!         - returns it's return type.
  //!         Otherwise returns `expected_width_t<value_type_t<T>>`.
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

  template <typename T>
  using iterator_width_t = decltype(_::iterator_width_impl<T>());

  template <typename T>
  constexpr width_type iterator_width_v = iterator_width_t<T>::value;
}
