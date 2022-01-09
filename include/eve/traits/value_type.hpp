//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/range.hpp>

#include <iterator>
#include <type_traits>

namespace eve
{
  namespace detail
  {
    template <typename T>
    constexpr auto value_type_impl()
    {
      if constexpr (range<T>)
      {
        using ref = std::add_lvalue_reference_t<T>;
        return value_type_impl<decltype(std::begin(std::declval<ref>()))>();
      }
      else if constexpr (std::input_or_output_iterator<T>)
      {
        return std::type_identity<typename std::iterator_traits<T>::value_type>{};
      }
      else
      {
        return std::type_identity<typename T::value_type>{};
      }
    }
  }

  //================================================================================================
  //! @addtogroup tratis
  //! @{
  //!  @typedef value_type_t
  //!
  //!  @tparam T Type to process
  //!
  //!  @brief A meta function for getting an associated value_type for a relaxed iterator/range.
  //!
  //!         If T has begin/end - value_type_t for return type of begin
  //!         If T is std::iterator -> returns iterator_traits<T>::value_type
  //!         If T has nested `value_type` -> returns it
  //!         Otherwise it's undefined.
  //!
  //!   **Required header:** `#include <eve/traits/value_type.hpp>`,
  //!                        `#include <eve/traits.hpp>`
  //! @}
  //================================================================================================

  template <typename T>
  using value_type_t = typename decltype(detail::value_type_impl<T>())::type;
}
