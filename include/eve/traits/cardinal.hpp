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
  template<std::ptrdiff_t Cardinal> struct fixed;

  //================================================================================================
  //! @addtogroup eve_traits
  //! @{
  //!   @struct width
  //!   @brief Computes the width of a given type
  //!
  //!   **Required header:** `#include <eve/traits/cardinal.hpp>`
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
  //!   using cardinal_t = typename cardinal<Type>::type;
  //!   @endcode
  //!
  //!   @groupheader{Helper variable template}
  //!
  //!   @code{.cpp}
  //!   template<typename Type>
  //!   inline constexpr auto cardinal_v = cardinal<Type>::value;
  //!   @endcode
  //! @}
  //================================================================================================
  template<typename Type>
  struct cardinal : fixed<1>
  {};

  template<typename Type, std::ptrdiff_t Cardinal>
  struct cardinal<wide<Type, Cardinal>> : fixed<Cardinal>
  {
    using type = fixed<Cardinal>;
  };

  template<typename Type>
  struct cardinal<logical<Type>> : cardinal<Type>
  {
  };

  template<typename Type>
  using cardinal_t = typename cardinal<std::remove_cvref_t<Type>>::type;

  template<typename Type>
  inline constexpr cardinal_type cardinal_v = cardinal<std::remove_cvref_t<Type>>::value;
}
