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
  //!   @struct iterator_cardinal
  //!   @brief Returns a cardinal for an `eve::algo::relaxed_iterator`
  //!
  //!   **Required header:** `#include <eve/algo/concepts.hpp>`
  //!
  //!   If the `iterator_cardinal()` static method is defined - it evaluates as
  //!   `decltype(I::iterator_cardinal())`. Otherwise it evaluates as
  //!   eve::expected_cardinal_t<eve::value_type_t<I>>.
  //!
  //!   @tparam I A type modeling eve::algo::iterator
  //!
  //!   @groupheader{Member types}
  //!
  //!   |Name   | Definition                                              |
  //!   |:------|:--------------------------------------------------------|
  //!   |`type` | A type equivalent to `decltype(I::iterator_cardinal())` |
  //!
  //!    @groupheader{Helper types}
  //!
  //!    @code{.cpp}
  //!    template<typename I>
  //!    using iterator_cardinal_t = typename iterator_cardinal_t<I>::type;
  //!    @endcode
  //!
  //!   @groupheader{Helper variable template}
  //!
  //!   @code{.cpp}
  //!   template<typenale I>
  //!   inline constexpr auto iterator_cardinal_v = iterator_cardinal<I>::value;
  //!   @endcode
  //! @}
  //================================================================================================
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
