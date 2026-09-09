//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/wide_forward.hpp>
#include <cstddef>

namespace eve
{
  template<std::ptrdiff_t Width> struct fixed;

  //================================================================================================
  //! @addtogroup eve_traits
  //! @{
  //!   @struct width
  //!   @brief Computes the width of a given type
  //!
  //!   **Required header:** `#include <eve/traits/width.hpp>`
  //!
  //!   For a given type `T`, computes the type of its width.
  //!
  //!   @tparam T Type to process
  //!
  //!   #### Member types
  //!
  //!   |Name   | Definition               |
  //!   |:------|:-------------------------|
  //!   |`type` | The width type of `T` |
  //!
  //!    <br/>
  //!
  //!   @groupheader{Helper types}
  //!
  //!   @code{.cpp}
  //!   template<typename Type>
  //!   using width_t = typename width<Type>::type;
  //!   @endcode
  //!
  //!   @groupheader{Helper variable template}
  //!
  //!   @code{.cpp}
  //!   template<typename Type>
  //!   inline constexpr auto width_v = width<Type>::value;
  //!   @endcode
  //! @}
  //================================================================================================
  template<typename Type>
  struct width : fixed<1>
  {};

  template<typename Type, std::ptrdiff_t Width>
  struct width<wide<Type, Width>> : fixed<Width>
  {
    using type = fixed<Width>;
  };

  template<typename Type>
  struct width<logical<Type>> : width<Type>
  {
  };

  template<typename Type>
  using width_t = typename width<std::remove_cvref_t<Type>>::type;

  template<typename Type>
  inline constexpr width_type width_v = width<std::remove_cvref_t<Type>>::value;
}
