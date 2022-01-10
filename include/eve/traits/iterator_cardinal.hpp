//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/traits/cardinal.hpp>
#include <eve/traits/value_type.hpp>

namespace eve
{
  namespace detail
  {
    template <typename T>
    constexpr auto iterator_cardinal_impl()
    {
      if constexpr ( requires { T::iterator_cardinal(); } ) return decltype(T::iterator_cardinal()){};
      else                                                  return expected_cardinal_t<value_type_t<T>>{};
    }
  }

  //================================================================================================
  //! @addtogroup tratis
  //! @{
  //!  @typedef iterator_cardinal_t
  //!
  //!  @tparam T Type to process
  //!
  //!  @brief A meta-function that returns a cardinal for a relaxed iterator/range.
  //!         If T defines a nested static function `iterator_cardinal()` (which should return eve::fixed)
  //!         - returns it's return type.
  //!         Otherwise returns `expected_cardinal_t<value_type_t<T>>`.
  //!
  //!  *NOTE*: for aligned_ptr we return expected_cardinal.
  //!
  //!  **Required header**: `#include <eve/traits/iterator_cardinal.hpp>`,
  //!                       `#include <eve/traits.hpp>`
  //!   @code{.cpp}
  //!   template<typename T>
  //!   inline constexpr auto iterator_cardinal_v = iterator_cardinal<T>::value;
  //!   @endcode
  //! @}
  //================================================================================================

  template <typename T>
  using iterator_cardinal_t = decltype(detail::iterator_cardinal_impl<T>());

  template <typename T>
  constexpr std::ptrdiff_t iterator_cardinal_v = iterator_cardinal_t<T>::value;
}
