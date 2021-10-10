//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

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
  //!   @code{.cpp}
  //!   // I - eve::algo::iterator
  //!
  //!   iterator_cardinal<I>::type
  //!   iterator_cardinal_t<I>
  //!   iterator_cardinal_v<I>;
  //!   @endcode
  //! @}

  template <typename I>
    requires requires { I::iterator_cardinal(); }
  struct iterator_cardinal
  {
    using type = decltype(I::iterator_cardinal());
  };

  template <typename I>
  using iterator_cardinal_t = typename iterator_cardinal<I>::type;

  template <typename I>
  constexpr std::ptrdiff_t iterator_cardinal_v = iterator_cardinal_t<I>{}();
}
