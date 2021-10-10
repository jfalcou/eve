//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/concepts/detail.hpp>
#include <eve/algo/concepts/iterator_cardinal.hpp>

#include <eve/traits.hpp>

#include <type_traits>

namespace eve::algo
{
  //================================================================================================
  //! @addtogroup eve.algo.concepts
  //! @{
  //!  @struct value_type
  //!  @brief for an instance of `eve::algo::relaxed_iterator`, `eve::algo::relaxed_range`
  //!         compute the value_type.
  //!
  //!   **Required header:** `#include <eve/algo/concepts.hpp>`
  //! @}
  //================================================================================================

  namespace detail
  {
    template <typename T>
    constexpr auto value_type_impl()
    {
           if constexpr ( has_begin_end<T>            ) return value_type_impl<decltype(std::declval<T>().begin())>();
      else if constexpr ( std::contiguous_iterator<T> ) return std::type_identity<typename std::iterator_traits<T>::value_type>{};
      else                                              return std::type_identity<typename eve::pointer_traits<T>::value_type>{};
    }
  }

  template <typename T>
  struct value_type
  {
    using type = typename decltype(detail::value_type_impl<T>())::type;
  };

  template <typename T>
  using value_type_t = typename value_type<T>::type;

  //================================================================================================
  //! @addtogroup eve.algo.concepts
  //! @{
  //!  @struct wide_value_type
  //!  @brief for an instance of `eve::algo::iterator` a shortcut: wide<value_type_t<I>, iterator_cardinal_t<I>>
  //!
  //!   **Required header:** `#include <eve/algo/concepts.hpp>`
  //! @}
  //================================================================================================

  template <typename I>
  struct wide_value_type
  {
    using type = eve::wide<value_type_t<I>, iterator_cardinal_t<I>>;
  };

  template <typename I>
  using wide_value_type_t = typename wide_value_type<I>::type;
}
