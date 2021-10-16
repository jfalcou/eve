//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/concepts/value_type.hpp>

#include <type_traits>

namespace eve::algo
{
  //================================================================================================
  //! @addtogroup eve.algo.concepts
  //! @{
  //!   @struct iterator_cardinal
  //!   @brief Returns a cardinal for an `eve::algo::iterator`
  //!
  //!   **Required header:** `#include <eve/algo/concepts.hpp>`
  //!
  //!   For a given `eve::algo::iterator` returns a `cardinal`.
  //!   In order to provide this, the `iterator` has to define a static method: `iterator_cardinal() -> fixed`
  //!
  //!   This is often used as a helper to define iterators and because of how C++ works, it's useful to default
  //!   to `expected_cardinal`
  //!
  //!   @code{.cpp}
  //!   // I - eve::algo::iterator
  //!
  //!   iterator_cardinal<I>::type
  //!   iterator_cardinal_t<I>
  //!   iterator_cardinal_v<I>;
  //!   @endcode
  //! @}

  template <typename I>
  struct iterator_cardinal
  {
    using type = fixed<expected_cardinal_v<value_type_t<I>>>;
  };

  template <typename I>
    requires requires { I::iterator_cardinal(); }
  struct iterator_cardinal<I>
  {
    using type = decltype(I::iterator_cardinal());
  };

  template <typename I>
  using iterator_cardinal_t = typename iterator_cardinal<I>::type;

  template <typename I>
  constexpr std::ptrdiff_t iterator_cardinal_v = iterator_cardinal_t<I>{}();


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
