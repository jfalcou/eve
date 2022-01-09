//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/traits.hpp>

#include <type_traits>

namespace eve::algo
{
  //================================================================================================
  //! @addtogroup algo_concepts
  //! @{
  //!   @struct wide_value_type
  //!   @brief Computes an eve::simd_value from an iterator
  //!
  //!   **Required header:** `#include <eve/algo/concepts.hpp>`
  //!
  //!   For a given iterator type `I`, computes the eve::simd_value type associate to the value
  //!   type referenced byt the iterator `I`.
  //!
  //!   @tparam I A type modeling  eve::iterator
  //!
  //!   #### Member types
  //!
  //!   |Name   | Definition                                                                |
  //!   |:------|:--------------------------------------------------------------------------|
  //!   |`type` | A type equivalent to `eve::wide<value_type_t<I>, iterator_cardinal_t<I>>` |
  //!
  //!    #### Helper types
  //!
  //!    @code{.cpp}
  //!    template<typename I>
  //!    using wide_value_type_t = typename wide_value_type_t<I>::type;
  //!    @endcode
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
